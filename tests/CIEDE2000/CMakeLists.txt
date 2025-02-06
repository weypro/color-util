add_executable(test-CIEDE2000 main.cpp)
target_link_libraries(test-CIEDE2000 color-util)

find_package(GTest)
find_package(benchmark)

if (GTest_FOUND AND benchmark_FOUND)
    add_executable(test-CIEDE2000-benchmark benchmark.cpp)
    target_link_libraries(test-CIEDE2000-benchmark PRIVATE color-util)
    target_link_libraries(test-CIEDE2000-benchmark PRIVATE
            GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main
            benchmark::benchmark
    )
else()
    message(WARNING "GTest or Benchmark not found, skipping test-CIEDE2000-benchmark target.")
endif()
