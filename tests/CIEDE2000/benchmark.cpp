#include <benchmark/benchmark.h>
#include <color-util/CIEDE2000.hpp>
#include <iostream>
#include <vector>

namespace test_data {
    constexpr std::array<std::array<double, 7>, 34> color_pairs = {{
        {{50.0000, 2.6772, -79.7751, 50.0000, 0.0000, -82.7485, 2.0425}},
        {{50.0000, 3.1571, -77.2803, 50.0000, 0.0000, -82.7485, 2.8615}},
        {{50.0000, 2.8361, -74.0200, 50.0000, 0.0000, -82.7485, 3.4412}},
        {{50.0000, -1.3802, -84.2814, 50.0000, 0.0000, -82.7485, 1.0000}},
        {{50.0000, -1.1848, -84.8006, 50.0000, 0.0000, -82.7485, 1.0000}},
        {{50.0000, -0.9009, -85.5211, 50.0000, 0.0000, -82.7485, 1.0000}},
        {{50.0000, 0.0000, 0.0000, 50.0000, -1.0000, 2.0000, 2.3669}},
        {{50.0000, -1.0000, 2.0000, 50.0000, 0.0000, 0.0000, 2.3669}},
        {{50.0000, 2.4900, -0.0010, 50.0000, -2.4900, 0.0009, 7.1792}},
        {{50.0000, 2.4900, -0.0010, 50.0000, -2.4900, 0.0010, 7.1792}},
        {{50.0000, 2.4900, -0.0010, 50.0000, -2.4900, 0.0011, 7.2195}},
        {{50.0000, 2.4900, -0.0010, 50.0000, -2.4900, 0.0012, 7.2195}},
        {{50.0000, -0.0010, 2.4900, 50.0000, 0.0009, -2.4900, 4.8045}},
        {{50.0000, -0.0010, 2.4900, 50.0000, 0.0010, -2.4900, 4.8045}},
        {{50.0000, -0.0010, 2.4900, 50.0000, 0.0011, -2.4900, 4.7461}},
        {{50.0000, 2.5000, 0.0000, 50.0000, 0.0000, -2.5000, 4.3065}},
        {{50.0000, 2.5000, 0.0000, 73.0000, 25.0000, -18.0000, 27.1492}},
        {{50.0000, 2.5000, 0.0000, 61.0000, -5.0000, 29.0000, 22.8977}},
        {{50.0000, 2.5000, 0.0000, 56.0000, -27.0000, -3.0000, 31.9030}},
        {{50.0000, 2.5000, 0.0000, 58.0000, 24.0000, 15.0000, 19.4535}},
        {{50.0000, 2.5000, 0.0000, 50.0000, 3.1736, 0.5854, 1.0000}},
        {{50.0000, 2.5000, 0.0000, 50.0000, 3.2972, 0.0000, 1.0000}},
        {{50.0000, 2.5000, 0.0000, 50.0000, 1.8634, 0.5757, 1.0000}},
        {{50.0000, 2.5000, 0.0000, 50.0000, 3.2592, 0.3350, 1.0000}},
        {{60.2574, -34.0099, 36.2677, 60.4626, -34.1751, 39.4387, 1.2644}},
        {{63.0109, -31.0961, -5.8663, 62.8187, -29.7946, -4.0864, 1.2630}},
        {{61.2901, 3.7196, -5.3901, 61.4292, 2.2480, -4.9620, 1.8731}},
        {{35.0831, -44.1164, 3.7933, 35.0232, -40.0716, 1.5901, 1.8645}},
        {{22.7233, 20.0904, -46.6940, 23.0331, 14.9730, -42.5619, 2.0373}},
        {{36.4612, 47.8580, 18.3852, 36.2715, 50.5065, 21.2231, 1.4146}},
        {{90.8027, -2.0831, 1.4410, 91.1528, -1.6435, 0.0447, 1.4441}},
        {{90.9257, -0.5406, -0.9208, 88.6381, -0.8985, -0.7239, 1.5381}},
        {{6.7747, -0.2908, -2.4247, 5.8714, -0.0985, -2.2286, 0.6377}},
        {{2.0776, 0.0795, -1.1350, 0.9033, -0.0636, -0.5514, 0.9082}}
    }};

}

// Single color difference calculation
static void BM_SingleColorDifference(benchmark::State& state) {
    // Use the first set of test data
    const colorutil::Lab color_1{
        test_data::color_pairs[0][0],
        test_data::color_pairs[0][1],
        test_data::color_pairs[0][2]
    };
    const colorutil::Lab color_2{
        test_data::color_pairs[0][3],
        test_data::color_pairs[0][4],
        test_data::color_pairs[0][5]
    };
    
    for (auto _ : state) {
        benchmark::DoNotOptimize(
            colorutil::calculate_CIEDE2000(color_1, color_2)
        );
    }
}
BENCHMARK(BM_SingleColorDifference);

// Average performance across multiple test data sets
static void BM_AllTestData(benchmark::State& state) {
    // Preconstruct Lab object array to avoid redundant construction
    std::array<std::pair<colorutil::Lab, colorutil::Lab>, 34> test_pairs;
    for (size_t i = 0; i < test_data::color_pairs.size(); ++i) {
        test_pairs[i].first = colorutil::Lab{
            test_data::color_pairs[i][0],
            test_data::color_pairs[i][1],
            test_data::color_pairs[i][2]
        };
        test_pairs[i].second = colorutil::Lab{
            test_data::color_pairs[i][3],
            test_data::color_pairs[i][4],
            test_data::color_pairs[i][5]
        };
    }

    for (auto _ : state) {
        for (const auto& pair : test_pairs) {
            benchmark::DoNotOptimize(
                colorutil::calculate_CIEDE2000(pair.first, pair.second)
            );
        }
    }
    state.SetItemsProcessed(state.iterations() * test_data::color_pairs.size());
}
BENCHMARK(BM_AllTestData);

// Batch processing performance (reusing test data)
static void BM_BatchProcessing(benchmark::State& state) {
    const int batch_size = state.range(0);
    std::vector<std::pair<colorutil::Lab, colorutil::Lab>> color_pairs;
    color_pairs.reserve(batch_size);

    // Populate with test data by looping through repeatedly until target size is reached
    for (int i = 0; i < batch_size; ++i) {
        const auto& test_pair = test_data::color_pairs[i % test_data::color_pairs.size()];
        color_pairs.emplace_back(
            colorutil::Lab{test_pair[0], test_pair[1], test_pair[2]},
            colorutil::Lab{test_pair[3], test_pair[4], test_pair[5]}
        );
    }

    for (auto _ : state) {
        for (const auto& pair : color_pairs) {
            benchmark::DoNotOptimize(
                colorutil::calculate_CIEDE2000(pair.first, pair.second)
            );
        }
    }
    state.SetItemsProcessed(state.iterations() * batch_size);
}
// Test different batch sizes: 8 to 8192
BENCHMARK(BM_BatchProcessing)
    ->Range(8, 8<<10);

BENCHMARK_MAIN();
