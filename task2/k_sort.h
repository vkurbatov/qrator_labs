#ifndef _QRATOR_K_SORT_H
#define _QRATOR_K_SORT_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "common/defines.h"

int	k_sort(element_t* array, size_t size, int method);

int n_swaps(const element_t* array, size_t size);

#ifdef __cplusplus
} // extern "C"
#endif

#endif

