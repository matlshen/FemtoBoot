set(TEST_APP_NAME ${CMAKE_PROJECT_NAME}_tests)

# Download Google Test
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Text executable build instructions
set(TEST_SOURCES
    Crc32Test.cpp)
set(TEST_LIBRARIES
    bootutil)
add_executable(${TEST_APP_NAME} ${TEST_SOURCES})
target_link_libraries(${TEST_APP_NAME} ${TEST_LIBRARIES} GTest::gtest_main)

# Add tests to Google Test
include(GoogleTest)
gtest_discover_tests(${TEST_APP_NAME})

# Run test executable
add_custom_command(TARGET ${TEST_APP_NAME}
                    COMMAND "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${TEST_APP_NAME}"
                    POST_BUILD)