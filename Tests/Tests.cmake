include(FetchContent)

set(TESTS_SRC
        Tests/Queue.cpp
)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest
        GIT_TAG v1.14.0
)
enable_testing()

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
set(UNIT_TESTS_BIN_NAME unit_tests)

add_executable(${UNIT_TESTS_BIN_NAME} ${SRC} ${TESTS_SRC})
target_link_libraries(${UNIT_TESTS_BIN_NAME} PRIVATE asio GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(${UNIT_TESTS_BIN_NAME})
