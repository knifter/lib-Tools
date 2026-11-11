#ifdef TOOLS_REMOTERX

#ifndef __TOOLS_REMOTERX
#define __TOOLS_REMOTERX

#include "esp_idf_version.h"

#if ESP_IDF_VERSION_MAJOR < 5
    #error "this tools-remoterx-legacy is meant for IDF 5. Use remoterx-legacy for IDF 4"
#endif

#warning "Untested IDF5 code for remoterx"

#include "freertos/FreeRTOS.h"
#include "driver/rmt_rx.h"
#include "freertos/queue.h"

class RemoteRx
{
    public:
        bool setup(gpio_num_t pin);
        uint32_t getPacket();

    private:
        bool decodePacket(const rmt_symbol_word_t*, size_t, uint32_t* target);

        #ifdef DEBUG_RMX
        void debugPacket(const rmt_symbol_word_t*, size_t);
        #endif // DEBUG_RMX
        rmt_channel_handle_t    _channel = NULL;
        QueueHandle_t           _queue = NULL;
        rmt_symbol_word_t       _symbols[64];
        rmt_receive_config_t    _rx_config = {};
};

#endif // __TOOLS_REMOTERX

#endif // TOOLS_REMOTERX
