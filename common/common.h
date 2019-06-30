#ifndef _QRATOR_COMMON_H
#define _QRATOR_COMMON_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "defines.h"

//! print to stdout int array
void print_array(const element_t* int_array, size_t size, const char* separator);

//! fill int array random values between min and max
void fill_array(element_t* int_array, size_t size, element_t min_value, element_t max_value);

int get_random(int min_value, int max_value);

#ifdef __cplusplus
} // extern "C"
#endif

#endif
