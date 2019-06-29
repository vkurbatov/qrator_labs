/*
	Дан массив различных целых чисел. Надо найти индекс локального минимума в этом массиве.
	Необходимо реализовать алгоритм с минимальной асимптотической сложностью.

	Локальный минимум - это такой элемент массива a_i, что a_{i-1} > a_i < a_{i+1}.
	Для начала и конца массива, соответственно: a0 < a1 и a_n < a_{n-1}.
*/

#include "local_minimum.h"

static int last_cycles_count = 0;

int get_last_cycles_count()
{
	return last_cycles_count;
}

static int simple_method(const element_t* array, size_t size)
{
	int result = NOINDEX;

	if (array[0] < array[1])
	{
		last_cycles_count = 1;
		result = 0;
	}
	else if (array[size - 1] < array[size - 2])
	{
		last_cycles_count = 1;
		result = size - 1;
	}
	else
	{

		int delta[] = { 0, 0 };

		for (int i = 0; i < size - 1; ++i)
		{
			delta[1] = array[i + 1] - array[i];

			if (delta[0] < 0 && delta[1] > 0)
			{
				result = i;
				break;
			}

			delta[0] = delta[1];
		}
	}

	return result;
}

static int extended_method(const element_t* array, size_t size)
{
	int result = NOINDEX;

	int lo_idx = size / 2;
	int hi_idx = lo_idx;

	while (lo_idx > 0 || (hi_idx < size - 1))
	{
		last_cycles_count++;
		if (lo_idx > 0)
		{
			int delta = array[lo_idx] - array[lo_idx + 1];

			if (delta < 0 && (array[lo_idx - 1] > array[lo_idx]))
			{
				result = lo_idx;
				break;
			}

			lo_idx -= delta > 0 ? 2 : 1;
		}

		if (hi_idx < (size - 1))
		{
			int delta = array[hi_idx] - array[hi_idx + 1];

			if (delta < 0 && array[hi_idx - 1] > array[hi_idx])
			{
				result = hi_idx;
				break;
			}

			hi_idx += delta > 0 ? 2 : 1;
		}
	}

	if (result == NOINDEX)
	{
		if (array[0] < array[1])
		{
			last_cycles_count = 1;
			result = 0;
		}
		else if (array[size - 1] < array[size - 2])
		{
			last_cycles_count = 1;
			result = size - 1;
		}
	}

	return result;
}

int get_index_of_local_minimum(const element_t* array, size_t size, int method)
{
	static int(*k_local_min_methods[])(const element_t*, size_t) = { simple_method, extended_method };

	last_cycles_count = 0;

	return size > 1 ? k_local_min_methods[method](array, size) : NOINDEX;
}
