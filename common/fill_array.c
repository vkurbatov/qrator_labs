#include "common.h"

void fill_array(element_t* int_array, size_t size, element_t min_value, element_t max_value)
{

	while (size-- > 0)
	{
		int_array[size] = get_random(min_value, max_value);
	}
}
