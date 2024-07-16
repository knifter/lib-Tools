#include "tools-debug.h"

#include <unordered_map>
#include <string>

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
