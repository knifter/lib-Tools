// IDF 5.x RMT driver implementation (driver/rmt_rx.h)
#include "esp_idf_version.h"
#if ESP_IDF_VERSION_MAJOR >= 5
#pragma message "This file (remote-rx for id5) needs testing!"

#include "tools-remoterx.h"

#include "config.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/rmt_rx.h"

#include "tools-log.h"

#ifndef RMX_BITS_PER_PACKET
	#define RMX_BITS_PER_PACKET		25
	#define DEBUG_RMX_PACKET
#endif
#ifndef RMX_PULSE_SHORT_US
	#define RMX_PULSE_SHORT_US		25
#endif
#ifndef RMX_PULSE_LONG_US
	#define RMX_PULSE_LONG_US		25
#endif
#ifndef RMX_PULSE_ERROR_PERC
	#define RMX_PULSE_ERROR_PERC	10
#endif

#ifdef DEBUG_RMX_PACKET
	#define DEBUG_RMX
#endif

#if RMX_PULSE_SHORT_US > 768
	#define _RMT_US_PER_TICK	3
#elif RMX_PULSE_SHORT_US > 511
	#define _RMT_US_PER_TICK	2
#else
	#define _RMT_US_PER_TICK	1
#endif
#if RMX_PULSE_SHORT_US > 1023
	#define _RMT_FILTER_US		255
#else
	#define _RMT_FILTER_US		(RMX_PULSE_SHORT_US/2)
#endif
#define _RMT_IDLE_THRESHOLD_US	(RMX_PULSE_LONG_US*3)

#define PULSE_SHORT_MIN		(RMX_PULSE_SHORT_US*(1.0-RMX_PULSE_ERROR_PERC/100.0)/_RMT_US_PER_TICK)
#define PULSE_SHORT_MAX		(RMX_PULSE_SHORT_US*(1.0+RMX_PULSE_ERROR_PERC/100.0)/_RMT_US_PER_TICK)
#define PULSE_LONG_MIN		(RMX_PULSE_LONG_US *(1.0-RMX_PULSE_ERROR_PERC/100.0)/_RMT_US_PER_TICK)
#define PULSE_LONG_MAX		(RMX_PULSE_LONG_US *(1.0+RMX_PULSE_ERROR_PERC/100.0)/_RMT_US_PER_TICK)


static bool IRAM_ATTR _rmt_rx_done_cb(rmt_channel_handle_t channel,
    const rmt_rx_done_event_data_t* edata, void* user_data)
{
    BaseType_t woken = pdFALSE;
    xQueueSendFromISR((QueueHandle_t)user_data, edata, &woken);
    return woken == pdTRUE;
}

bool RemoteRx::setup(gpio_num_t pin)
{
    rmt_rx_channel_config_t cfg = {};
    cfg.gpio_num          = pin;
    cfg.clk_src           = RMT_CLK_SRC_DEFAULT;
    cfg.resolution_hz     = 1000000u / _RMT_US_PER_TICK;
    cfg.mem_block_symbols = 64;

    if(rmt_new_rx_channel(&cfg, &_channel) != ESP_OK)
    {
        ERROR("rmt_new_rx_channel failed");
        return false;
    }

    _queue = xQueueCreate(1, sizeof(rmt_rx_done_event_data_t));

    rmt_rx_event_callbacks_t cbs = {};
    cbs.on_recv_done = _rmt_rx_done_cb;
    rmt_rx_register_event_callbacks(_channel, &cbs, _queue);

    rmt_enable(_channel);

    _rx_config.signal_range_min_ns = (uint32_t)(_RMT_FILTER_US)         * 1000u;
    _rx_config.signal_range_max_ns = (uint32_t)(_RMT_IDLE_THRESHOLD_US) * 1000u;

    rmt_receive(_channel, _symbols, sizeof(_symbols), &_rx_config);
    return true;
}

uint32_t RemoteRx::getPacket()
{
    rmt_rx_done_event_data_t rx_data;
    uint32_t packet = 0;
    if(xQueueReceive(_queue, &rx_data, 1) == pdTRUE)
    {
        if(!decodePacket(rx_data.received_symbols, rx_data.num_symbols, &packet))
            packet = 0;
        rmt_receive(_channel, _symbols, sizeof(_symbols), &_rx_config);
    }
    return packet;
}

bool RemoteRx::decodePacket(const rmt_symbol_word_t* items, const size_t length, uint32_t* target)
{
#ifdef DEBUG_RMX_PACKET
    if(length > 5)
        debugPacket(items, length);
#endif
    if(length != RMX_BITS_PER_PACKET)
    {
#ifdef DEBUG_RMX
        DBG("Ignoring %d bit packet.", length);
#endif
        return false;
    }

    uint32_t val = 0;
    for(int i = 0; i < (int)length; i++)
    {
        int high = (items+i)->duration0;
        int low  = (items+i)->duration1;
        (void)low;

        if(high > PULSE_SHORT_MIN && high < PULSE_SHORT_MAX)
        {
            val <<= 1; val |= 1;
            continue;
        }
        if(high > PULSE_LONG_MIN && high < PULSE_LONG_MAX)
        {
            val <<= 1;
            continue;
        }
#ifdef DEBUG_RMX
        DBG("Bit %d size out of range: h:%d l:%d. Discarding.", i+1, high*_RMT_US_PER_TICK, low*_RMT_US_PER_TICK);
        debugPacket(items, length);
#endif
        return false;
    }
    *target = val;
    return true;
}

#ifdef DEBUG_RMX
void RemoteRx::debugPacket(const rmt_symbol_word_t* item, const size_t length)
{
    time_t now = millis();
    static time_t last;
    printf("+%ld ms: %d bit packet: ", now - last, length);
    last = now;

    int short_min = 0x7FFFFFFF, short_max = 0, short_cnt = 0;
    int long_min  = 0x7FFFFFFF, long_max  = 0, long_cnt  = 0;
    float short_sum = 0, long_sum = 0;
    uint32_t val = 0;
    int sum = 0;
    bool fault = false;

    for(int i = 0; i < (int)length; i++)
    {
        int high = (item+i)->duration0 * _RMT_US_PER_TICK;
        int low  = (item+i)->duration1 * _RMT_US_PER_TICK;

        if(high > PULSE_SHORT_MIN*_RMT_US_PER_TICK && high < PULSE_SHORT_MAX*_RMT_US_PER_TICK)
        {
            printf("1 "); val <<= 1; val |= 1;
        } else if(high > PULSE_LONG_MIN*_RMT_US_PER_TICK && high < PULSE_LONG_MAX*_RMT_US_PER_TICK)
        {
            printf("0 "); val <<= 1;
        } else {
            printf("\nBit %d = UNKNOWN, high:%dus low:%dus\n", i, high, low);
            fault = true;
        }

        if(high < ((PULSE_SHORT_MAX+PULSE_LONG_MIN)*_RMT_US_PER_TICK)/2)
        {
            short_min = min(short_min, high); short_max = max(short_max, high);
            short_sum += high; short_cnt++;
        } else {
            long_min = min(long_min, high); long_max = max(long_max, high);
            long_sum += high; long_cnt++;
        }
        sum += high+low;
    }
    if(!fault) printf(" = 0x%x = %d\n", val, val); else printf("\n");

    if(short_cnt == 0) short_cnt = 0x7FFFFFFF;
    if(long_cnt  == 0) long_cnt  = 0x7FFFFFFF;
    int short_avg  = (int)(short_sum / short_cnt);
    int long_avg   = (int)(long_sum  / long_cnt);
    if(short_avg == 0) short_avg = 1;
    if(long_avg  == 0) long_avg  = 1;
    int short_perc = max((int)ceil((short_avg-short_min)*100/short_avg), (int)ceil((short_max-short_avg)*100/short_avg));
    int long_perc  = max((int)ceil((long_avg-long_min)*100/long_avg),   (int)ceil((long_max-long_avg)*100/long_avg));
    DBG("Short=[%u..%u]~%u(%u%%) Long=[%u..%u]~%d(%u%%) ~sum=%u %u%%err",
        short_min, short_max, short_avg, short_perc,
        long_min, long_max, long_avg, long_perc,
        sum/length, max(short_perc, long_perc));
}
#else
void RemoteRx::debugPacket(const rmt_symbol_word_t*, size_t) {}
#endif

#endif // ESP_IDF_VERSION_MAJOR >= 5
