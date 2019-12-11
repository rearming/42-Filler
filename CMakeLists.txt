cmake_minimum_required(VERSION 3.15)
project(filler C)

set(CMAKE_C_STANDARD 11)

include_directories(
        includes
        libft/includes
)

link_directories(
        libft
        libft/ft_printf
)

set(sources
        sources/main.c
        sources/algo.c
        sources/error.c
        sources/safe_malloc.c
        sources/map_processing.c sources/parsing.c sources/debug.c)

add_executable(sleonard.filler
        ${sources}
        )

target_link_libraries(sleonard.filler
        "ft"
        "ftprintf"
)
