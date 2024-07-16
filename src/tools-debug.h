#ifndef __TOOLS_PTRDBG_H
#define __TOOLS_PTRDBG_H

#ifdef DEBUG

bool 		dbg_ptr_register(void* ptr, const char* name);
const char* dbg_ptr_lookup(void* ptr);


	#define DBG_PTR_REGISTER(ptr, name)		dbg_ptr_register(ptr, name)
	#define DBG_PTR_NAME(ptr)				dbg_ptr_lookup(ptr)

#endif

#endif // __TOOLS_PTRDBG_H
