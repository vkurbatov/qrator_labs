#include "common.h"

#include <stdlib.h>
#include <time.h>

static int rand_init_flag = 0;

void fill_array(element_t* int_array, size_t size, element_t min_value, element_t max_value)
{
	if (rand_init_flag == 0)
	{
		srand(time(NULL));
		rand_init_flag = 1;
	}

	while (size-- > 0)
	{
		int_array[size] = min_value + rand() % (max_value - min_value + 1);
	}
}
