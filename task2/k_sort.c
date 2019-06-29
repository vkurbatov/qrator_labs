/*
	Дан массив различных целых чисел.

	Мы хотим отсортировать его следующим образом: a0 > a1 > a2 > … > a_{k-1} > a_k < a_{k+1} < a_{k+2} < … a_N, 0 <= k <= N.

	При этом единственная допустимая операция: поменять местами два соседних элемента.

	Необходимо написать функцию вида int n_swaps(int *a, size_t size), возвращающую минимально необходимое количество операций,
	которые приводят массив к данному виду.

	Обратите внимание, что индекс k может быть с краю (то есть, отсортированный список уже обладает нужным порядком элементов),
	а также что k не является параметром функции, а должен получаться в результате работы алгоритма.
*/

#include "k_sort.h"
#include "task1/local_minimum.h"

static void swap(element_t* array, int idx_a, int idx_b)
{
	element_t b_val = array[idx_b];
	array[idx_b] = array[idx_a];
	array[idx_a] = b_val;
}

static int get_index_of_min_element(const element_t* array, size_t size)
{
	int result = 0;

	element_t min_value = array[size - 1];

	while(size-- > 0)
	{
		if (array[size] < min_value)
		{
			result = size;
			min_value = array[size];
		}
	}

	return result;
}

static int simple_k_sort(element_t* array, size_t size)
{
	int result = 0;

	int lo_idx = 0;
	int hi_idx = size - 2;

	while (lo_idx < hi_idx)
	{
		if (array[lo_idx] < array[lo_idx + 1])
		{
			swap(array, lo_idx, lo_idx + 1);
			result++;
		}

		if (array[hi_idx] > array[hi_idx + 1])
		{
			swap(array, hi_idx, hi_idx + 1);
			result++;
		}

		hi_idx--;
		lo_idx++;
	}

	if (result > 0)
	{
		result += simple_k_sort(array, size);
	}

	return result;
}

static int get_min_index(const element_t* array, int start_index, int end_index)
{
	int result = 0;

	int direction;

	int delta[] = { 0, 0 };

	while ((direction = end_index - start_index) != 0)
	{
		if (direction > 0)
		{
			delta[1] = array[start_index + 1] - array[start_index];

			if (delta[0] <= 0 && delta[1] > 0)
			{
				result = start_index;
				break;
			}

			start_index++;
		}
		else
		{
			delta[1] = array[start_index - 1] - array[start_index];

			if (delta[0] <= 0 && delta[1] > 0)
			{
				result = start_index;
				break;
			}

			start_index--;
		}

		delta[0] = delta[1];
	}

	return result;
}

static int k_sort_3(element_t* array, size_t size)
{
	int result = 0;

	int done = 0;

	int h_idx = 1;
	int t_idx = size - 1;

	while (done == 0)
	{
		done = 1;

		h_idx = get_min_index(array, 0, size - 1);
		t_idx = get_min_index(array, size - 1, 0);

		if (h_idx < t_idx)
		{
			if (h_idx < (size - t_idx))
			{
				swap(array, h_idx, h_idx + 1);
			}
			else
			{
				swap(array, t_idx, t_idx - 1);
			}

			result += 1;

			done = 0;
		}

	}

	return result;
}

int	k_sort(element_t* array, size_t size, int method)
{
	static int(*k_sort_methods[])(element_t*, size_t) = { simple_k_sort, k_sort_3 };

	return k_sort_methods[method](array, size);
}

int n_swaps(const element_t* array, size_t size)
{
	return 0;
}
