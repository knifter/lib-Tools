
#include "driver/rmt.h"

class RemoteRx
{
	public:
		bool setup(gpio_num_t pin);
		uint32_t getPacket();
			
	private:
		bool decodePacket(const rmt_item32_t*, const size_t, uint32_t* target);
		void debugPacket(const rmt_item32_t*, const size_t);
		
		RingbufHandle_t _rb = NULL;
};
