cmake_minimum_required(VERSION 3.1.0)
project(finals C)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(${CMAKE_SOURCE_DIR} include)

add_library(lib src/text.c include/text.h 
                src/encoding.c include/encoding.h 
                src/compression.c include/compression.h
                src/ecc.c include/ecc.h
                src/bit.c include/bit.h
                src/utils.c include/utils.h)

add_executable(encoder.out src/encoder.c)
target_link_libraries(encoder.out lib)

add_executable(decoder.out src/decoder.c)
target_link_libraries(decoder.out lib)
