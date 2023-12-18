#include "tools-remoterx.h"

#include "config.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/rmt.h"
#include "driver/periph_ctrl.h"
#include "soc/rmt_reg.h"

#include "tools-log.h"

// Defaults, set in CONFIG.H:
// #define DEBUG_RMX
// #define DEBUG_RMX_PACKET
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
#define RMT_RX_BUFFER_SIZE		256

// Calculate clock divider, filter. for long pulses we need to slow the RMT down
#if RMX_PULSE_SHORT_US > 768
	#define _RMT_US_PER_TICK			3
#elif RMX_PULSE_SHORT_US > 511
	#define _RMT_US_PER_TICK			2
#else
	#define _RMT_US_PER_TICK			1
#endif
#if RMX_PULSE_SHORT_US > 1023
	#define _RMT_FILTER_US	255
#else
	#define _RMT_FILTER_US			(RMX_PULSE_SHORT_US/2)
#endif
#define _RMT_IDLE_THRESHOLD_US	(RMX_PULSE_LONG_US*3)

// Calculate Pulse windows from avg & percentage
#define PULSE_SHORT_MIN		(RMX_PULSE_SHORT_US*(1.0-RMX_PULSE_ERROR_PERC/100.0)/_RMT_US_PER_TICK)
#define PULSE_SHORT_MAX		(RMX_PULSE_SHORT_US*(1.0+RMX_PULSE_ERROR_PERC/100.0)/_RMT_US_PER_TICK)
#define PULSE_LONG_MIN		(RMX_PULSE_LONG_US *(1.0-RMX_PULSE_ERROR_PERC/100.0)/_RMT_US_PER_TICK)
#define PULSE_LONG_MAX		(RMX_PULSE_LONG_US *(1.0+RMX_PULSE_ERROR_PERC/100.0)/_RMT_US_PER_TICK)


bool RemoteRx::setup(gpio_num_t pin)
{
	rmt_rx_config_t rxconfig =
	{
		.idle_threshold = (uint16_t)_RMT_IDLE_THRESHOLD_US / _RMT_US_PER_TICK,
		.filter_ticks_thresh = (uint16_t) _RMT_FILTER_US / _RMT_US_PER_TICK, // must not exceed 255
		.filter_en = true,
	};
	rmt_config_t rmtcfg = 
	{
		.rmt_mode = RMT_MODE_RX,
		.channel = RMT_CHANNEL_0,
		.gpio_num = pin,
		.clk_div = 80 * _RMT_US_PER_TICK,
		.mem_block_num = 1,
		.flags = 0,
		.rx_config = rxconfig
	};

	rmt_config(&rmtcfg);
	rmt_driver_install(rmtcfg.channel, RMT_RX_BUFFER_SIZE, /*flags*/ 0);
	rmt_get_ringbuf_handle(rmtcfg.channel, &_rb);
	rmt_rx_start(rmtcfg.channel, 1);

	if(!_rb)
	{
		ERROR("No ringbuffer.");
		return false;
	};

	return true;
};

uint32_t RemoteRx::getPacket()
{
	size_t rx_size = 0;
	rmt_item32_t* item = (rmt_item32_t*) xRingbufferReceive(_rb, &rx_size, 1);
	uint32_t packet = 0;
	if(item)
	{
		if(!decodePacket(item, rx_size >> 2, &packet))
			 packet = 0;

		vRingbufferReturnItem(_rb, (void*) item);
	};
	
	return packet;
};

bool RemoteRx::decodePacket(const rmt_item32_t* items, const size_t length, uint32_t* target)
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
	};

	// DBG("Processing %d bit packet.", BITS_PER_PACKET);
	uint32_t val = 0;
	for (int i = 0; i < length; i++)
	{
		int high = (items+i)->duration0;
		int low = (items+i)->duration1;

		if(high > PULSE_SHORT_MIN && high < PULSE_SHORT_MAX)
		{
			val <<= 1;
			val |= 1;
			continue;
		};
		if(high > PULSE_LONG_MIN && high < PULSE_LONG_MAX)
		{
			val <<= 1;
			continue;
		};

#ifdef DEBUG_RMX
		DBG("Bit %d size out of range: h:%d l:%d. Discarding packet.", i + 1, high * _RMT_US_PER_TICK, low * _RMT_US_PER_TICK);
		debugPacket(items, length);
#endif
		return false;
	};

	*target = val;
	return true;
};

#ifdef DEBUG_RMX
void RemoteRx::debugPacket(const rmt_item32_t* item, const size_t length)
{
	time_t now = millis();
	static time_t last;
	printf("+%ld ms: %d bit packet: ", now - last, length);
	last = now;

	int short_min = 0x7FFFFFFF;
	int short_max = 0;
	float short_sum = 0;
	int short_cnt = 0;

	int long_min = 0x7FFFFFFF;
	int long_max = 0;
	float long_sum = 0;
	int long_cnt = 0;

	uint32_t val = 0;
	int sum = 0;
	bool fault = false;
	for (int i = 0; i < length; i++)
	{
		int high = (item+i)->duration0 * _RMT_US_PER_TICK;
		int low = (item+i)->duration1 * _RMT_US_PER_TICK;

		// printf("%d:%dus %d:%dus\n", (item+i)->level0, (item+i)->duration0, (item+i)->level1, (item+i)->duration1);
		if(high > PULSE_SHORT_MIN*_RMT_US_PER_TICK && high < PULSE_SHORT_MAX*_RMT_US_PER_TICK)
		{
			printf("1 ");
			val <<= 1;
			val |= 1;
		}else if(high > PULSE_LONG_MIN*_RMT_US_PER_TICK && high < PULSE_LONG_MAX*_RMT_US_PER_TICK)
		{
			printf("0 ");
			val <<= 1;
		} else {
			printf("\nBit %d = UNKNOWN, high:%dus low:%dus sum:%dus\n", i, high, low, high+low);
			fault = true;
		};

		if(high < ((PULSE_SHORT_MAX+PULSE_LONG_MIN)*_RMT_US_PER_TICK)/2)
		{
			short_min = min(short_min, high);
			short_max = max(short_max, high);
			short_sum += high;
			short_cnt++;
		} else {
			long_min = min(long_min, high);
			long_max = max(long_max, high);
			long_sum += high;
			long_cnt++;
		};
		sum += high+low;
	};
	if(!fault)
		printf(" = 0x%x = %d\n", val, val);
	else
		printf("\n");

	if(short_cnt == 0 ) short_cnt = 0x7FFFFFFF;
	if(long_cnt == 0 ) long_cnt = 0x7FFFFFFF;	
	int short_avg = (uint)(short_sum / short_cnt);
	int long_avg = (uint)(long_sum / long_cnt);
	if(short_avg == 0) short_avg=1;
	if(long_avg == 0) long_avg=1;
	int short_perc = max(ceil((short_avg-short_min)*100/short_avg), ceil((short_max-short_avg)*100/short_avg));
	int long_perc = max(ceil((long_avg-long_min)*100/long_avg), ceil((long_max-long_avg)*100/long_avg));

	DBG("Short = [%u .. %u] ~%u (%u%%), Long = [%u .. %u] ~%d (%u%%), ~sum = %u, %u%% error\n" , 
		short_min, short_max, short_avg, short_perc,
		long_min, long_max, long_avg, long_perc,
		sum / length, max(short_perc, long_perc)
		);
};
#endif

