#include "common.h"

#include <stdlib.h>
#include <time.h>

static int random_init_flag = 0;

int get_random(int min_value, int max_value)
{
	if (random_init_flag == 0)
	{
		srand(time(NULL));
		random_init_flag = 1;
	}

	return min_value + rand() % (max_value - min_value + 1);
}
