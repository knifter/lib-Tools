#ifndef __TOOLS_PTRDBG_H
#define __TOOLS_PTRDBG_H

bool 		dbg_ptr_register(void* ptr, const char* name);
const char* dbg_ptr_lookup(void* ptr);

#define DBG_PTR_REG(ptr, name)		dbg_ptr_register(ptr, name)
#define DBG_PTR_LOOKUP(ptr, name)	dbg_ptr_lookup(ptr, name)

#endif // __TOOLS_PTRDBG_H
