# CMake file for source directory

set(CMAKE_FOLDER "${CMAKE_FOLDER}/src")

add_executable(tsk_1545 1545.cpp)
add_executable(tsk_1496 1496.cpp)
add_executable(tsk_1196 1196.cpp)
add_executable(tsk_1837 1837.cpp)

## Set property
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(-Wall -Werror -Wextra -Wpedantic -g -O0)
