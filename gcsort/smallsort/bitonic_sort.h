#ifndef BITONIC_SORT_H
#define BITONIC_SORT_H

#include <stdint.h>
namespace gcsort {
namespace smallsort {
template <typename T>
class bitonic {
 public:
  static void sort(T* ptr, int length);
};
}  // namespace smallsort
}  // namespace gcsort
#endif