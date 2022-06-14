cmake_minimum_required(VERSION 3.5.0)
project(finals C)

enable_testing()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(core src/core.h src/text.c src/text.h
                            src/queue.c src/queue.h
                            src/bit.c src/bit.h
                            src/new_bit.c src/new_bit.h
                            src/utils.c src/utils.h
                            src/ecc.c src/ecc.h
                            src/bwt.c src/bwt.h
                            src/mtf.c src/mtf.h
                            src/rle.c src/rle.h
                            src/pivot.c src/pivot.h
                            src/bin.c src/bin.h)

add_executable(encoder.out src/encoder.c)
target_link_libraries(encoder.out core)
add_executable(decoder.out src/decoder.c)
target_link_libraries(decoder.out core)

add_executable(test_text test/test_text.c)
target_link_libraries(test_text core)
target_include_directories(test_text PUBLIC ${PROJECT_SOURCE_DIR}/src)

add_executable(test_bwt test/test_bwt.c)
target_link_libraries(test_bwt core)
target_include_directories(test_bwt PUBLIC ${PROJECT_SOURCE_DIR}/src)

add_executable(test_mtf test/test_mtf.c)
target_link_libraries(test_mtf core)
target_include_directories(test_mtf PUBLIC ${PROJECT_SOURCE_DIR}/src)

add_executable(test_rle test/test_rle.c)
target_link_libraries(test_rle core)
target_include_directories(test_rle PUBLIC ${PROJECT_SOURCE_DIR}/src)

add_test(test_bwt, ./test_bwt)
add_test(test_mtf, ./test_mtf)
add_test(test_rle, ./test_rle)
