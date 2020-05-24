#include <random>
#include <algorithm>
#include <benchmark/benchmark.h>

#include "util.h"
#include <bitonic_sort.h>
#include <gcsort.h>
#include <introsort.h>

#include "util.h"
#include <algorithm>
#include <random>

extern void generate_unique_ptrs_vec(std::vector<uint8_t *>& vec, size_t n) {
  std::iota(vec.begin(), vec.end(), (uint8_t *) 0x1000);

  std::random_device rd;
  std::mt19937 g(rd());

  std::shuffle(vec.begin(), vec.end(), g);
}
extern void generate_unique_ptrs_vec(std::vector<int64_t>& vec, size_t n) {
  std::iota(vec.begin(), vec.end(), (int64_t) 0x1000);

  std::random_device rd;
  std::mt19937 g(rd());

  std::shuffle(vec.begin(), vec.end(), g);
}
extern void generate_unique_ptrs_vec(std::vector<int32_t>& vec, size_t n) {
  std::iota(vec.begin(), vec.end(), (int32_t) 0x1000);

  std::random_device rd;
  std::mt19937 g(rd());

  std::shuffle(vec.begin(), vec.end(), g);
}
template <typename T>
extern std::vector<T *> generate_array_beginnings(const std::vector<std::vector<T> *> &copies) {
  std::vector<T *> begins(copies.size());
  for (auto i = 0; i < copies.size(); i++)
    begins[i] = copies[i]->data();
  return begins;
}
template <typename T>
extern void refresh_copies(const std::vector<std::vector<T> *> &copies,
                           std::vector<T>& orig) {
  auto begin = orig.begin();
  auto end = orig.end();
  for (auto i = 0; i < copies.size(); i++)
    copies[i]->assign(begin, end);
}
template <typename T>
extern std::vector<std::vector<T> *> generate_copies(int num_copies,  int32_t n, std::vector<T>& orig) {
  std::vector<std::vector<T>*> copies(num_copies);
  for (auto i = 0; i < num_copies; i++)
    copies[i] = new std::vector<T>(n);
  refresh_copies(copies, orig);
  return copies;
}
template <typename T> extern void delete_copies(std::vector<std::vector<T> *> &copies)
{
  for (auto c : copies)
    delete c;
}

static void BM_introsort(benchmark::State &state) {
    auto n = state.range(0);
    auto v = std::vector<uint8_t*>(n);
    auto begin = v.data();
    auto end = v.data() + v.size() - 1;

    for (auto _ : state) {
        state.PauseTiming();
        generate_unique_ptrs_vec(v, n);
        state.ResumeTiming();
        sort_introsort(begin, end);
    }

    state.counters["Time/N"] = benchmark::Counter(
            n,
            benchmark::Counter::Flags::kIsIterationInvariantRate | benchmark::Counter::Flags::kInvert,
            benchmark::Counter::kIs1000);
}
BENCHMARK(BM_introsort)->RangeMultiplier(2)->Range(4096, 1 << 18)->Unit(benchmark::kMillisecond);

static const int ITERATIONS = 1024;

static void BM_insertionsort(benchmark::State &state) {
  auto n = state.range(0);
  auto v = std::vector<int64_t>(n);
  generate_unique_ptrs_vec(v, n);

  auto copies = generate_copies(ITERATIONS, n, v);
  auto begins = generate_array_beginnings(copies);
  auto ends = generate_array_beginnings(copies);
  for (auto i = 0; i < copies.size(); i++)
    ends[i] = begins[i] + n - 1;

  for (auto _ : state) {
    state.PauseTiming();
    refresh_copies(copies, v);
    state.ResumeTiming();
    for (auto i = 0; i < ITERATIONS; i++)
      sort_insertionsort((uint8_t **) begins[i], (uint8_t **) ends[i]);
  }

  delete_copies(copies);

  state.counters["Time/N"] = benchmark::Counter(
      n * ITERATIONS,
      benchmark::Counter::Flags::kIsIterationInvariantRate | benchmark::Counter::Flags::kInvert,
      benchmark::Counter::kIs1000);
}
BENCHMARK(BM_insertionsort)->DenseRange(4, 128, 4)->Unit(benchmark::kNanosecond);


static void BM_bitonic_sort_int64(benchmark::State &state) {
  auto n = state.range(0);
  auto v = std::vector<int64_t>(n);
  generate_unique_ptrs_vec(v, n);

  auto copies = generate_copies(ITERATIONS, n, v);
  auto begins = generate_array_beginnings(copies);

  for (auto _ : state) {
    state.PauseTiming();
    refresh_copies(copies, v);
    state.ResumeTiming();
    for (auto i = 0; i < ITERATIONS; i++)
      gcsort::smallsort::bitonic_sort_int64_t(begins[i], n);
  }

  delete_copies(copies);

  state.counters["Time/N"] = benchmark::Counter(
      n * ITERATIONS,
      benchmark::Counter::Flags::kIsIterationInvariantRate | benchmark::Counter::Flags::kInvert,
      benchmark::Counter::kIs1000);
}
BENCHMARK(BM_bitonic_sort_int64)->DenseRange(4, 128, 4)->Unit(benchmark::kNanosecond);


static void BM_bitonic_sort_int32(benchmark::State &state) {
  auto n = state.range(0);
  auto v = std::vector<int32_t>(n);
  generate_unique_ptrs_vec(v, n);

  auto copies = generate_copies(ITERATIONS, n, v);
  auto begins = generate_array_beginnings(copies);

  for (auto _ : state) {
    state.PauseTiming();
    refresh_copies(copies, v);
    state.ResumeTiming();
    for (auto i = 0; i < ITERATIONS; i++)
      gcsort::smallsort::bitonic_sort_int32_t(begins[i], n);
  }

  delete_copies(copies);

  state.counters["Time/N"] = benchmark::Counter(
      n * ITERATIONS,
      benchmark::Counter::Flags::kIsIterationInvariantRate | benchmark::Counter::Flags::kInvert,
      benchmark::Counter::kIs1000);
}
BENCHMARK(BM_bitonic_sort_int32)->DenseRange(8, 256, 8)->Unit(benchmark::kNanosecond);
