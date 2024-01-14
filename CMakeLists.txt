cmake_minimum_required(VERSION 3.27)
project(42cursus_cub3d C)

set(CMAKE_C_STANDARD 11)

add_executable(42cursus_cub3d
        srcs/parse/map_attr_add_data.c
        srcs/parse/ft_parse.c
        srcs/parse/ft_parse_2.c
        srcs/main.c)
