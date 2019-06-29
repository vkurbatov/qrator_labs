#include "tasks.h"
#include "common/common.h"
#include "k_sort.h"

#include <iostream>

namespace qrator_labs
{

namespace task2
{

const std::size_t default_array_size = 50;
const element_t default_min_value = 0;
const element_t default_max_value = 100;

std::int32_t test1()
{

	std::cout << "Task 2: k-sort demonstration:" << std::endl << std::endl;


	element_t source_array[default_array_size];

	fill_array(source_array, default_array_size, default_min_value, default_max_value);

	//element_t source_array[default_array_size] = { 9, 8, 7, 6, 5, 4, 3, 2, 4, 2};

	std::cout << "Source array:" << std::endl;

	print_array(source_array, default_array_size, ", ");

	for (int i = 0; i < 2; i++)
	{
		std::cout << "STEP" << i + 1 << ":" << std::endl;

		auto swap_count = k_sort(source_array, default_array_size, 1);

		std::cout << "Array after k-sort: " << std::endl;

		print_array(source_array, default_array_size, ", ");

		std::cout << "Swap count = " << swap_count << std::endl;
	}

	return 0;

	/*

	auto local_minimum_index = get_index_of_local_minimum(source_array, default_array_size);

	if (local_minimum_index == NOINDEX)
	{
		std::cout << "Local minimum index not found" << std::endl;
	}
	else
	{
		std::cout << "Local minimum index = " << local_minimum_index << std::endl;
	}

	return 0;*/
}

} // task1

} // qrator_labs
