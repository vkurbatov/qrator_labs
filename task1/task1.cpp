#include "tasks.h"
#include "common/common.h"
#include "local_minimum.h"

#include <iostream>

namespace qrator_labs
{

namespace task1
{

const std::size_t default_array_size = 50;
const element_t default_min_value = 0;
const element_t default_max_value = 100;

std::int32_t test1()
{
	std::cout << "Task 1: local minimum demonstration:" << std::endl << std::endl;

	element_t source_array[default_array_size];

	fill_array(source_array, default_array_size, default_min_value, default_max_value);

	std::cout << "Source array:" << std::endl;

	print_array(source_array, default_array_size, ", ");

	auto local_minimum_index = get_index_of_local_minimum(source_array, default_array_size, LOCAL_MINIMUN_METHOD_EXTENDED);

	if (local_minimum_index == NOINDEX)
	{
		std::cout << "Local minimum index not found" << std::endl;
	}
	else
	{
		std::cout << "Local minimum index = " << local_minimum_index << std::endl;
	}

	return 0;
}

} // task1

} // qrator_labs
