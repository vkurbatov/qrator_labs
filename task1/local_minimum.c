/*
	Дан массив различных целых чисел. Надо найти индекс локального минимума в этом массиве.
	Необходимо реализовать алгоритм с минимальной асимптотической сложностью.

	Локальный минимум - это такой элемент массива a_i, что a_{i-1} > a_i < a_{i+1}.
	Для начала и конца массива, соответственно: a0 < a1 и a_n < a_{n-1}.
*/

#include "local_minimum.h"

static int simple_method(const element_t* array, size_t size)
{
	int result = NOINDEX;

	if (array[0] < array[1])
	{
		result = 0;
	}
	else if (array[size - 1] < array[size - 2])
	{
		result = size - 1;
	}
	else
	{
		for (int i = 1; i < size - 2; ++i)
		{
			if (array[i - 1] > array[i] && array[i] < array[i + 1])
			{
				result = i;
				break;
			}
		}
	}

	return result;
}

static int extended_method(const element_t* array, size_t size)
{
	int result = NOINDEX;

	int l_idx = 1;
	int h_idx = size - 2;

	while(l_idx < h_idx)
	{
		while(l_idx < h_idx && array[l_idx - 1] <= array[l_idx])
		{
			l_idx++;
		}

		while (l_idx < h_idx && array[h_idx] >= array[h_idx + 1])
		{
			h_idx--;
		}

		if (l_idx < h_idx)
		{
			if (array[l_idx] < array[l_idx + 1])
			{
				result = l_idx;
				break;
			}
			else if (array[h_idx - 1] > array[h_idx])
			{
				result = h_idx;
				break;
			}
		}
		l_idx++;
		h_idx--;
	}

	if (result == NOINDEX)
	{
		if (array[0] < array[1])
		{
			result = 0;
		}
		else if (array[size - 1] < array[size - 2])
		{
			result = size - 1;
		}
	}

	return result;
}

int get_index_of_local_minimum(const element_t* array, size_t size, int method)
{
	static int(*k_local_min_methods[])(const element_t*, size_t) = { simple_method, extended_method };


	return size > 1 ? k_local_min_methods[method](array, size) : NOINDEX;
}
