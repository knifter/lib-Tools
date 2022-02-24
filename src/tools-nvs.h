#ifndef __TOOLS_NVS_H
#define __TOOLS_NVS_H

#include <stdint.h>
#include <nvs.h>

#include "config.h"

#ifndef NVS_DELAY_SAVE
	#define NVS_DELAY_SAVE		5000
#endif

#define NVS_NAMESPACE           "NVSETTINGS"
#define NVS_KEY_DATA            "NVS_DATA"
#define NVS_KEY_METADATA        "NVS_META"

class NVSettings
{
	public:
        NVSettings(void* data, const size_t data_size);

		bool begin(bool initialize_on_fail = true);
		void loop();
		void save();
		bool erase();
		void saveDelayed(time_t when = NVS_DELAY_SAVE);
		void setDefaults();
		
	protected:
        virtual bool set_defaults_since(const uint32_t data_version) = 0;
        virtual bool read_blob(void* blob, const size_t blob_size, const uint32_t blob_version) = 0;

		bool write_flash(bool testmode = false);
		bool read_flash();
		bool initialize_flash();

		bool        _init = false;
		nvs_handle  _handle = 0;
        void        *_data;
        const size_t _data_size;
		uint32_t	_data_version = 0;
		time_t      _saveat = 0;
		bool        _dirty = true;
};

#endif // __TOOLS_NVS_H