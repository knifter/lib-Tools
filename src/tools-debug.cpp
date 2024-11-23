#include "tools-debug.h"

#include <unordered_map>
#include <string>
#include <stdlib.h>

#include "tools-log.h"

std::unordered_map<void*, std::string> _ptr_map;
char _tmp_str[16];

bool dbg_ptr_register(void* ptr, const char* name)
{
	if(_ptr_map.find(ptr) != _ptr_map.end())
	{
		WARNING("dbg_ptr: %s(%p) is already registered.", name, ptr);
		return false;
	};

	// DBG("Registering ptr %p as '%s'", ptr, name);
	_ptr_map[ptr] = name;
	
	return true;
};

const char* dbg_ptr_lookup(void* ptr)
{
	if(_ptr_map.find(ptr) == _ptr_map.end())
	{
		snprintf(_tmp_str, 16, "<%p>", ptr);
		return _tmp_str;
	};

	return _ptr_map[ptr].c_str();
};

const char *hexdump(void *data, size_t len)
{
	static char* buf = nullptr; // accesible after function call
	static size_t buf_size = 0;

	// no buffer? allocate one
	if(!buf)
	{
		buf = (char*) malloc(len*3+1);
		buf_size = len;
	};
	// too small? resize
	if(buf_size < len)
	{
		buf = (char *) realloc(buf, len * 3 + 1);
		buf_size = len;
	};
	// nullptr means free buffer
	if(data == nullptr)
	{
		buf = nullptr;
		buf_size = 0;
		return nullptr;
	};

	for(int i = 0; i<len; i++)
	{
		sprintf(buf+i*3, "%02X ", ((char*) data)[i] );
	};
	buf[len*3] = '\0';

	return buf;
};
