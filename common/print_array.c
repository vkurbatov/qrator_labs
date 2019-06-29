#include "common.h"
#include "stdio.h"

void print_array(const element_t* int_array, size_t size, const char* separator)
{
	while (size-- > 0)
	{
		printf("%d", *int_array);

		if(size == 0)
		{
			break;
		}

		printf(separator);
		int_array++;
	}
	printf("\n");
}
