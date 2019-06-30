#ifndef _QRATOR_K_SORT_H
#define _QRATOR_K_SORT_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "common/defines.h"

#define K_SORT_METHOD_1	0
#define K_SORT_METHOD_2	1

int	k_sort(element_t* array, size_t size, int method);

#ifdef __cplusplus
} // extern "C"
#endif

#endif

