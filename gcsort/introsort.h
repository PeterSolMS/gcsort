#ifndef GCSORT_INTROSORT_H
#define GCSORT_INTROSORT_H

#include <cstddef>
#include <cstdint>

namespace gcsort {
class introsort {
 private:
  static const int size_threshold = 64;
  static const int max_depth = 100;

  inline static void swap_elements(uint8_t** i, uint8_t** j) {
    uint8_t* t = *i;
    *i = *j;
    *j = t;
  }

 public:
  static void sort(uint8_t** begin, uint8_t** end, int ignored) {
    ignored = 0;
    introsort_loop(begin, end, max_depth);
    insertionsort(begin, end);
  }

  static void introsort_loop(uint8_t** lo, uint8_t** hi, int depth_limit) {
    while (hi - lo >= size_threshold) {
      if (depth_limit == 0) {
        heapsort(lo, hi);
        return;
      }
      uint8_t** p = median_partition(lo, hi);
      depth_limit = depth_limit - 1;
      introsort_loop(p, hi, depth_limit);
      hi = p - 1;
    }
  }

  static uint8_t** median_partition(uint8_t** low, uint8_t** high) {
    uint8_t *pivot, **left, **right;

    // sort low middle and high
    if (*(low + ((high - low) / 2)) < *low)
      swap_elements((low + ((high - low) / 2)), low);
    if (*high < *low)
      swap_elements(low, high);
    if (*high < *(low + ((high - low) / 2)))
      swap_elements((low + ((high - low) / 2)), high);

    swap_elements((low + ((high - low) / 2)), (high - 1));
    pivot = *(high - 1);
    left = low;
    right = high - 1;
    while (1) {
      while (*(--right) > pivot)
        ;
      while (*(++left) < pivot)
        ;
      if (left < right) {
        swap_elements(left, right);
      } else
        break;
    }
    swap_elements(left, (high - 1));
    return left;
  }

  static void insertionsort(uint8_t** lo, uint8_t** hi) {
    for (uint8_t** i = lo + 1; i <= hi; i++) {
      uint8_t** j = i;
      uint8_t* t = *i;
      while ((j > lo) && (t < *(j - 1))) {
        *j = *(j - 1);
        j--;
      }
      *j = t;
    }
  }

  static void heapsort(uint8_t** lo, uint8_t** hi) {
    size_t n = hi - lo + 1;
    for (size_t i = n / 2; i >= 1; i--) {
      downheap(i, n, lo);
    }
    for (size_t i = n; i > 1; i--) {
      swap_elements(lo, lo + i - 1);
      downheap(1, i - 1, lo);
    }
  }

  static void downheap(size_t i, size_t n, uint8_t** lo) {
    uint8_t* d = *(lo + i - 1);
    size_t child;
    while (i <= n / 2) {
      child = 2 * i;
      if (child < n && *(lo + child - 1) < (*(lo + child))) {
        child++;
      }
      if (!(d < *(lo + child - 1))) {
        break;
      }
      *(lo + i - 1) = *(lo + child - 1);
      i = child;
    }
    *(lo + i - 1) = d;
  }
};
}  // namespace gcsort

extern "C" void sort_introsort(uint8_t** begin, uint8_t** end);

extern "C" void sort_insertionsort(uint8_t** begin, uint8_t** end);

#endif