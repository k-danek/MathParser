set(BINARY parser_test)

set(TEST_SOURCES "../tst/main.cc")

list(APPEND TEST_SOURCES "../tst/parsertest.cc")

set(SOURCES ${TEST_SOURCES})

add_executable(${BINARY} ${TEST_SOURCES})

add_test(NAME ${BINARY} COMMAND ${BINARY})

target_link_libraries(${BINARY} PUBLIC gtest parser)

