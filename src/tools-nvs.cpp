#include "tools-nvs.h"

// #include <Arduino.h>
#include <nvs.h>

#include "config.h"
#include "tools-log.h"

typedef struct
{
	uint32_t app_version;
    uint32_t data_version;
    uint32_t data_size;
} nvs_metadata_t;

NVSettings::NVSettings(void* data, const size_t data_size)
    :_data(data), _data_size(data_size)
{
    
};

bool NVSettings::begin(bool initialize_on_fail)
{	
	if(_init)
	{
		DBG("Re-init: close prv handle.");
		nvs_close(_handle);
	};

	esp_err_t err = nvs_open(NVS_NAMESPACE, NVS_READWRITE, &_handle);
	if(err != ESP_OK) 
	{
		ERROR("Unable to open NVS namespace: %s", esp_err_to_name(err));
		return false;
	};

	_data_version = 0;

	if(!read_flash())
	{
		if(!initialize_on_fail)
		{
			INFO("Reading settings from flash failed.");
			return false;
		};

	    set_defaults_since(0);

		if(!write_flash())
		{
			ERROR("Writing initial settings to flash failed: %s", esp_err_to_name(err));
			return _init = false;
		};
	};

	INFO("Read settings from flash.");
	return _init = true;
};

void NVSettings::setDefaults()
{
	if(!_init)
		return;
    set_defaults_since(0);
};

void NVSettings::loop()
{
	if(!_init)
		return;
	time_t now = millis();
	if(now > _saveat && _dirty)
	{
		INFO("Saving settings to NVS");
		write_flash();
	};
};

void NVSettings::save()
{
	write_flash(false);
};

void NVSettings::saveDelayed(time_t later)
{
	time_t when = millis() + later;
	if(when > _saveat)
		_saveat = when;
	_dirty = true;
	DBG("%lu: Will save settings at %lu", millis(), when);
};

bool NVSettings::write_flash(bool testmode)
{
	nvs_metadata_t meta;
    meta.app_version = VERSION;
    meta.data_version = _data_version;
    meta.data_size = _data_size;

	if(testmode)
	{
		DBG("write_flash testmode: app_vesion: %d, data_version: %d, data_size: %d", meta.app_version, meta.data_version, meta.data_size);
		_dirty = false;
		return true;
	};

	esp_err_t err = nvs_set_blob(_handle, NVS_KEY_METADATA, &meta, sizeof(nvs_metadata_t));
	if(err != OK)
	{
		ERROR("Failed to save meta-data to NVS: %s", esp_err_to_name(err));
		return false;
	};
	err = nvs_set_blob(_handle, NVS_KEY_DATA, _data, _data_size);
	if(err != OK)
	{
		ERROR("Failed to save settings to NVS: %s", esp_err_to_name(err));
		return false;
	};

	nvs_commit(_handle);
	INFO("Settings saved to NVS.");
	_dirty = false;
	return true;
};

bool NVSettings::read_flash()
{
	// get settings
	nvs_metadata_t meta;
    size_t blobsize = sizeof(nvs_metadata_t);
    esp_err_t err = nvs_get_blob(_handle, NVS_KEY_METADATA, &meta, &blobsize);
	if(err == ESP_ERR_NVS_NOT_FOUND) 
	{
	    WARNING("Pristine flash. No data.");
		return false;
	};
	if(err != ESP_OK) 
	{
		ERROR("Cannot read NVS-Settings meta-data: %s", esp_err_to_name(err));
		return false;
  	};
    if(blobsize != sizeof(nvs_metadata_t))
    {
        ERROR("NVS-Settings meta-data size not correct. Other data?");
        return false;
    };
    if(meta.data_size > _data_size)
    {
        WARNING("NVS-Settings data-size larger than my currently known data. Cannot migrate this.");
        return false;
    };

    DBG("NVSettings meta-data found. app_version: %d, data_version: %d, %d bytes", meta.app_version, meta.data_version, meta.data_size);

    // Now we know the data blob is equal or smaller than _data_size and we can load it
    blobsize = meta.data_size;
	uint8_t blob[meta.data_size];
    err = nvs_get_blob(_handle, NVS_KEY_DATA, &blob, &blobsize);
	if(err == ESP_ERR_NVS_NOT_FOUND) 
	{
		return false;
	};
	if(err != ESP_OK) 
	{
		ERROR("Cannot read data after meta-data was obtained: %s", esp_err_to_name(err));
		return false;
  	};
	if(blobsize != meta.data_size)
	{
		ERROR("NVS Data size (%u) does not equal meta-data.size(%u)", blobsize, sizeof(nvs_metadata_t));
		return false;
	};

	// migrate possibly old config data to the newest version
	if(!read_blob(blob, blobsize, meta.data_version))
	{
		ERROR("read_blob failed to read or upgrade this data.");

		// FIXME: reset to 0?

		return false;
	};

	return true;
};

bool NVSettings::erase()
{
	esp_err_t err = nvs_erase_all(_handle);
	if(err == ESP_ERR_NVS_NOT_FOUND)
	{
		WARNING("NVS key '%s' not present. Nothing meta-data to erase.", NVS_KEY_METADATA);
		return false;
	};
	ESP_ERROR_CHECK(err);

	nvs_commit(_handle);
	INFO("NVM Settings erased.");
	return true;
};
