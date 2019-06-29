cmake_minimum_required(VERSION 2.8)

project(qrator_labs)

set(SOURCES
    "common/print_array.c"
    "common/fill_array.c"
    "task1/local_minimum.c"
    "task2/k_sort.c"
    "task3/thread_pool.cpp"
    "task3/tools/thread.cpp"
    "task1/task1.cpp"
    "task2/task2.cpp"
    "task3/task3.cpp"
    "main.cpp"
    )

set(HEADERS
    "common/defines.h"
    "common/common.h"
    "tasks.h"
    "task3/tools/i_worker.h"
    "task3/tools/i_thread.h"
    "task3/tools/thread.h"
    "task3/tools/tools_types.h"
    "task1/local_minimum.h"
    "task2/k_sort.h"
    "task3/thread_pool.h"
    )

include_directories(
    "."
    )

add_executable(${PROJECT_NAME}
               ${SOURCES}
               ${HEADERS}
                )

target_link_libraries(${PROJECT_NAME}
                        pthread
                        )

