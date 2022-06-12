cmake_minimum_required(VERSION 3.5.0)
project(finals C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

enable_testing()

add_library(core src/core.h src/text.c src/text.h
                            src/queue.c src/queue.h
                            src/bit.c src/bit.h
                            src/utils.c src/utils.h
                            src/correction.c src/correction.h
                            src/fivot.c src/fivot.h
                            src/protocol.c src/protocol.h)

add_executable(encoder.out src/encoder.c)
target_link_libraries(encoder.out core)
add_executable(decoder.out src/decoder.c)
target_link_libraries(decoder.out core)

add_executable(test_text test/test_text.c)
target_link_libraries(test_text core)
target_include_directories(test_text PUBLIC ${PROJECT_SOURCE_DIR}/src)

add_test(test_read_text sh -c "./test_text ../data/data.txt")
add_test(encoder.out sh -c "./encoder.out ../data/data.txt")
add_test(decoder.out sh -c "./decoder.out data.encoded")
