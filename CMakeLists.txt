cmake_minimum_required(VERSION 3.1.0)
project(finals C)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(${CMAKE_SOURCE_DIR} include)

add_library(lib include/lib/encoding.c include/lib/encoding.h 
                include/lib/compression.c include/lib/compression.h
                include/lib/ecc.c include/lib/ecc.h
                include/lib/utils.c include/lib/utils.h)

add_executable(encoder.out src/encoder.c)
target_link_libraries(encoder.out lib)

add_executable(decoder.out src/decoder.c)
target_link_libraries(decoder.out lib)
