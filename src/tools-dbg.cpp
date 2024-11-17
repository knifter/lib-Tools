#include "tools-dbg.h"

#include <stdlib.h>

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
