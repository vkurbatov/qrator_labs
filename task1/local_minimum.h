#ifndef _QRATOR_LOCAL_MIMINUM_H
#define _QRATOR_LOCAL_MIMINUM_H


#ifdef __cplusplus
extern "C"
{
#endif

#include "common/defines.h"

#define LOCAL_MINIMUN_METHOD_SIMPLE		0
#define LOCAL_MINIMUN_METHOD_EXTENDED	1

//! return index of local index between 0 and {size-1}, otherwise -1 
int get_index_of_local_minimum(const element_t* array, size_t size, int method);


#ifdef __cplusplus
} // extern "C"
#endif

#endif
