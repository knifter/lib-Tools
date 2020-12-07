#ifndef __LOG_H
#define __LOG_H

#include "config.h"

#ifdef ARDUINO
    #include <Arduino.h>
#endif

// Helpers
#ifndef __STRINGIFY
#  define __STRINGIFY(x)    #x
#endif
#define ___STRINGIFY(x) __STRINGIFY(x)
#define __LINESTR__ ___STRINGIFY(__LINE__)

#ifdef TOOLS_LOG_DEBUG
#endif // LOG_DEBUG

#ifdef DEBUG_REMOTE
    #define DBG(msg, ...)		rdebugD(msg "\n", ##__VA_ARGS__);
	#define INFO(msg, ...)		rdebugI(msg "\n", ##__VA_ARGS__);
	#define WARNING(msg, ...)	rdebugW(__FILE__ ".%s(" __LINESTR__ "): " msg "\n", __FUNCTION__, ##__VA_ARGS__);
	#define ERROR(msg, ...)		rdebugE(__FILE__ ".%s(" __LINESTR__ "): " msg "\n", __FUNCTION__, ##__VA_ARGS__);
#elif defined(DEBUG)
    #ifdef ESP_IDF
        #include <esp_log.h>
        #define DBG(msg, ...)       ESP_LOGD(__FUNCTION__, msg, ##__VA_ARGS__);
        #define VERBOSE(msb, ...)   ESP_LOGV("", msg, ##__VA_ARGS__)
        #define INFO(msg, ...)	    ESP_LOGI(__FUNCTION__, msg, ##__VA_ARGS__);
        #define WARNING(msg, ...)   ESP_LOGW(__FILE__ "." __FUNCTION__ "(" __LINESTR__ ")" , msg, ##__VA_ARGS__);
        #define ERROR(msg, ...)     ESP_LOGW(__FILE__ "." __FUNCTION__ "(" __LINESTR__ ")" , msg, ##__VA_ARGS__);
    #endif

    #ifdef ARDUINO
        #define DEBUG_DEVICE        Serial
        #define DBG(msg, ...)      DEBUG_DEVICE.printf("%s.%s: " msg "\n", __FILE__, __FUNCTION__, ##__VA_ARGS__)
        #define INFO(msg, ...)	   DEBUG_DEVICE.printf("%s: " msg "\n", __FUNCTION__, ##__VA_ARGS__)
        #define WARNING(msg, ...)  DEBUG_DEVICE.printf("WARN :" __FILE__ ".%s(" __LINESTR__ "): " msg "\n", __FUNCTION__, ##__VA_ARGS__)
        #define ERROR(msg, ...)    DEBUG_DEVICE.printf("ERROR:" __FILE__ ".%s(" __LINESTR__ "): " msg "\n", __FUNCTION__, ##__VA_ARGS__)
    #endif // ARDUINO
#else
    #define DBG(msg, ...)
	#define INFO(msg, ...)
	#define WARNING(msg, ...)
	#define ERROR(msg, ...)
#endif

#endif // __LOG_H