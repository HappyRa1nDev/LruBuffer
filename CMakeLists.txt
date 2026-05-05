cmake_minimum_required(VERSION 3.14)
project(LruBuffer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
    add_compile_options($<$<CONFIG:Debug>:/MTd> $<$<CONFIG:Release>:/MT>)
    set(gtest_force_shared_crt OFF CACHE BOOL "" FORCE)
endif()

add_executable(main main.cpp)

option(BUILD_TESTS "Build tests" ON)
if(BUILD_TESTS)
    include(FetchContent)
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
    )
    FetchContent_MakeAvailable(googletest)

    enable_testing()

    add_executable(tests tests/test.cpp)
    target_include_directories(tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
    target_link_libraries(tests PRIVATE GTest::gtest GTest::gtest_main)

    add_test(NAME LruBufferTests COMMAND tests)
endif()
