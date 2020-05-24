
#include <immintrin.h>

namespace gcsort {
namespace smallsort {


static inline void bitonic_sort_float_01v_ascending(__m256& d01) {
    __m256  min, max, s;
    __m256 topBit = _mm256_set1_epi64x(1LLU << 63);

    s = _mm256_shuffle_epi32(d01, 0xB1);
    
    min = _mm256_min_ps(s, d01);
    max = _mm256_max_ps(s, d01);
    d01 = _mm256_blend_epi32(min, max, 0xAA);

    s = _mm256_shuffle_epi32(d01, 0x1B);
    
    min = _mm256_min_ps(s, d01);
    max = _mm256_max_ps(s, d01);
    d01 = _mm256_blend_epi32(min, max, 0xCC);

    s = _mm256_shuffle_epi32(d01, 0xB1);
    
    min = _mm256_min_ps(s, d01);
    max = _mm256_max_ps(s, d01);
    d01 = _mm256_blend_epi32(min, max, 0xAA);

    s = _mm256_permute4x64_pd((__m256d) _mm256_shuffle_epi32(d01, 0x1B), 0x4E);
    min = _mm256_min_ps(s, d01);
    max = _mm256_max_ps(s, d01);
    d01 = _mm256_blend_epi32(min, max, 0xF0);

    s = _mm256_shuffle_epi32(d01, 0x4E);
    min = _mm256_min_ps(s, d01);
    max = _mm256_max_ps(s, d01);
    d01 = _mm256_blend_epi32(min, max, 0xCC);

    s = _mm256_shuffle_epi32(d01, 0xB1);
    min = _mm256_min_ps(s, d01);
    max = _mm256_max_ps(s, d01);
    d01 = _mm256_blend_epi32(min, max, 0xAA);
}

static inline void bitonic_sort_float_01v_merge_ascending(__m256& d01) {
    __m256  min, max, s;
    __m256 topBit = _mm256_set1_epi64x(1LLU << 63);

    s = _mm256_permute4x64_pd((__m256d) d01, 0x4E);
    min = _mm256_min_ps(s, d01);
    max = _mm256_max_ps(s, d01);
    d01 = _mm256_blend_epi32(min, max, 0xF0);

    s = _mm256_shuffle_epi32(d01, 0x4E);
    
    min = _mm256_min_ps(s, d01);
    max = _mm256_max_ps(s, d01);
    d01 = _mm256_blend_epi32(min, max, 0xCC);

    s = _mm256_shuffle_epi32(d01, 0xB1);
    
    min = _mm256_min_ps(s, d01);
    max = _mm256_max_ps(s, d01);
    d01 = _mm256_blend_epi32(min, max, 0xAA);
}

static inline void bitonic_sort_float_01v_descending(__m256& d01) {
    __m256  min, max, s;
    __m256 topBit = _mm256_set1_epi64x(1LLU << 63);

    s = _mm256_shuffle_epi32(d01, 0xB1);
    
    min = _mm256_min_ps(s, d01);
    max = _mm256_max_ps(s, d01);
    d01 = _mm256_blend_epi32(max, min, 0xAA);

    s = _mm256_shuffle_epi32(d01, 0x1B);
    
    min = _mm256_min_ps(s, d01);
    max = _mm256_max_ps(s, d01);
    d01 = _mm256_blend_epi32(max, min, 0xCC);

    s = _mm256_shuffle_epi32(d01, 0xB1);
    
    min = _mm256_min_ps(s, d01);
    max = _mm256_max_ps(s, d01);
    d01 = _mm256_blend_epi32(max, min, 0xAA);

    s = _mm256_permute4x64_pd((__m256d) _mm256_shuffle_epi32(d01, 0x1B), 0x4E);
    min = _mm256_min_ps(s, d01);
    max = _mm256_max_ps(s, d01);
    d01 = _mm256_blend_epi32(max, min, 0xF0);

    s = _mm256_shuffle_epi32(d01, 0x4E);
    min = _mm256_min_ps(s, d01);
    max = _mm256_max_ps(s, d01);
    d01 = _mm256_blend_epi32(max, min, 0xCC);

    s = _mm256_shuffle_epi32(d01, 0xB1);
    min = _mm256_min_ps(s, d01);
    max = _mm256_max_ps(s, d01);
    d01 = _mm256_blend_epi32(max, min, 0xAA);
}

static inline void bitonic_sort_float_01v_merge_descending(__m256& d01) {
    __m256  min, max, s;
    __m256 topBit = _mm256_set1_epi64x(1LLU << 63);

    s = _mm256_permute4x64_pd((__m256d) d01, 0x4E);
    min = _mm256_min_ps(s, d01);
    max = _mm256_max_ps(s, d01);
    d01 = _mm256_blend_epi32(max, min, 0xF0);

    s = _mm256_shuffle_epi32(d01, 0x4E);
    
    min = _mm256_min_ps(s, d01);
    max = _mm256_max_ps(s, d01);
    d01 = _mm256_blend_epi32(max, min, 0xCC);

    s = _mm256_shuffle_epi32(d01, 0xB1);
    
    min = _mm256_min_ps(s, d01);
    max = _mm256_max_ps(s, d01);
    d01 = _mm256_blend_epi32(max, min, 0xAA);
}

static inline void bitonic_sort_float_02v_ascending(__m256& d01, __m256& d02) {
    __m256  tmp;
    __m256 topBit = _mm256_set1_epi64x(1LLU << 63);

    bitonic_sort_float_01v_ascending(d01);
    bitonic_sort_float_01v_descending(d02);

    tmp = d02;
    
    d02 = _mm256_max_ps(d01, d02);
    d01 = _mm256_min_ps(d01, tmp);

    bitonic_sort_float_01v_merge_ascending(d01);
    bitonic_sort_float_01v_merge_ascending(d02);
}

static inline void bitonic_sort_float_02v_descending(__m256& d01, __m256& d02) {
    __m256  tmp;
    __m256 topBit = _mm256_set1_epi64x(1LLU << 63);

    bitonic_sort_float_01v_descending(d01);
    bitonic_sort_float_01v_ascending(d02);

    tmp = d02;
    
    d02 = _mm256_max_ps(d01, d02);
    d01 = _mm256_min_ps(d01, tmp);

    bitonic_sort_float_01v_merge_descending(d01);
    bitonic_sort_float_01v_merge_descending(d02);
}

static inline void bitonic_sort_float_02v_merge_ascending(__m256& d01, __m256& d02) {
    __m256  tmp;
    __m256 topBit = _mm256_set1_epi64x(1LLU << 63);

    tmp = d01;
    
    d01 = _mm256_min_ps(d02, d01);
    
    d02 = _mm256_max_ps(d02, tmp);

    bitonic_sort_float_01v_merge_ascending(d01);
    bitonic_sort_float_01v_merge_ascending(d02);
}

static inline void bitonic_sort_float_02v_merge_descending(__m256& d01, __m256& d02) {
    __m256  tmp;
    __m256 topBit = _mm256_set1_epi64x(1LLU << 63);

    tmp = d01;
    
    d01 = _mm256_min_ps(d02, d01);
    
    d02 = _mm256_max_ps(d02, tmp);

    bitonic_sort_float_01v_merge_descending(d01);
    bitonic_sort_float_01v_merge_descending(d02);
}

static inline void bitonic_sort_float_03v_ascending(__m256& d01, __m256& d02, __m256& d03) {
    __m256  tmp;
    __m256 topBit = _mm256_set1_epi64x(1LLU << 63);

    bitonic_sort_float_02v_ascending(d01, d02);
    bitonic_sort_float_01v_descending(d03);

    tmp = d03;
    
    d03 = _mm256_max_ps(d02, d03);
    d02 = _mm256_min_ps(d02, tmp);

    bitonic_sort_float_02v_merge_ascending(d01, d02);
    bitonic_sort_float_01v_merge_ascending(d03);
}

static inline void bitonic_sort_float_03v_descending(__m256& d01, __m256& d02, __m256& d03) {
    __m256  tmp;
    __m256 topBit = _mm256_set1_epi64x(1LLU << 63);

    bitonic_sort_float_02v_descending(d01, d02);
    bitonic_sort_float_01v_ascending(d03);

    tmp = d03;
    
    d03 = _mm256_max_ps(d02, d03);
    d02 = _mm256_min_ps(d02, tmp);

    bitonic_sort_float_02v_merge_descending(d01, d02);
    bitonic_sort_float_01v_merge_descending(d03);
}

static inline void bitonic_sort_float_03v_merge_ascending(__m256& d01, __m256& d02, __m256& d03) {
    __m256  tmp;
    __m256 topBit = _mm256_set1_epi64x(1LLU << 63);

    tmp = d01;
    
    d01 = _mm256_min_ps(d03, d01);
    
    d03 = _mm256_max_ps(d03, tmp);

    bitonic_sort_float_02v_merge_ascending(d01, d02);
    bitonic_sort_float_01v_merge_ascending(d03);
}

static inline void bitonic_sort_float_03v_merge_descending(__m256& d01, __m256& d02, __m256& d03) {
    __m256  tmp;
    __m256 topBit = _mm256_set1_epi64x(1LLU << 63);

    tmp = d01;
    
    d01 = _mm256_min_ps(d03, d01);
    
    d03 = _mm256_max_ps(d03, tmp);

    bitonic_sort_float_02v_merge_descending(d01, d02);
    bitonic_sort_float_01v_merge_descending(d03);
}

static inline void bitonic_sort_float_04v_ascending(__m256& d01, __m256& d02, __m256& d03, __m256& d04) {
    __m256  tmp;
    __m256 topBit = _mm256_set1_epi64x(1LLU << 63);

    bitonic_sort_float_02v_ascending(d01, d02);
    bitonic_sort_float_02v_descending(d03, d04);

    tmp = d03;
    
    d03 = _mm256_max_ps(d02, d03);
    d02 = _mm256_min_ps(d02, tmp);

    tmp = d04;
    
    d04 = _mm256_max_ps(d01, d04);
    d01 = _mm256_min_ps(d01, tmp);

    bitonic_sort_float_02v_merge_ascending(d01, d02);
    bitonic_sort_float_02v_merge_ascending(d03, d04);
}

static inline void bitonic_sort_float_04v_descending(__m256& d01, __m256& d02, __m256& d03, __m256& d04) {
    __m256  tmp;
    __m256 topBit = _mm256_set1_epi64x(1LLU << 63);

    bitonic_sort_float_02v_descending(d01, d02);
    bitonic_sort_float_02v_ascending(d03, d04);

    tmp = d03;
    
    d03 = _mm256_max_ps(d02, d03);
    d02 = _mm256_min_ps(d02, tmp);

    tmp = d04;
    
    d04 = _mm256_max_ps(d01, d04);
    d01 = _mm256_min_ps(d01, tmp);

    bitonic_sort_float_02v_merge_descending(d01, d02);
    bitonic_sort_float_02v_merge_descending(d03, d04);
}

static inline void bitonic_sort_float_04v_merge_ascending(__m256& d01, __m256& d02, __m256& d03, __m256& d04) {
    __m256  tmp;
    __m256 topBit = _mm256_set1_epi64x(1LLU << 63);

    tmp = d01;
    
    d01 = _mm256_min_ps(d03, d01);
    
    d03 = _mm256_max_ps(d03, tmp);

    tmp = d02;
    
    d02 = _mm256_min_ps(d04, d02);
    
    d04 = _mm256_max_ps(d04, tmp);

    bitonic_sort_float_02v_merge_ascending(d01, d02);
    bitonic_sort_float_02v_merge_ascending(d03, d04);
}

static inline void bitonic_sort_float_04v_merge_descending(__m256& d01, __m256& d02, __m256& d03, __m256& d04) {
    __m256  tmp;
    __m256 topBit = _mm256_set1_epi64x(1LLU << 63);

    tmp = d01;
    
    d01 = _mm256_min_ps(d03, d01);
    
    d03 = _mm256_max_ps(d03, tmp);

    tmp = d02;
    
    d02 = _mm256_min_ps(d04, d02);
    
    d04 = _mm256_max_ps(d04, tmp);

    bitonic_sort_float_02v_merge_descending(d01, d02);
    bitonic_sort_float_02v_merge_descending(d03, d04);
}

static inline void bitonic_sort_float_05v_ascending(__m256& d01, __m256& d02, __m256& d03, __m256& d04, __m256& d05) {
    __m256  tmp;
    __m256 topBit = _mm256_set1_epi64x(1LLU << 63);

    bitonic_sort_float_04v_ascending(d01, d02, d03, d04);
    bitonic_sort_float_01v_descending(d05);

    tmp = d05;
    
    d05 = _mm256_max_ps(d04, d05);
    d04 = _mm256_min_ps(d04, tmp);

    bitonic_sort_float_04v_merge_ascending(d01, d02, d03, d04);
    bitonic_sort_float_01v_merge_ascending(d05);
}

static inline void bitonic_sort_float_05v_descending(__m256& d01, __m256& d02, __m256& d03, __m256& d04, __m256& d05) {
    __m256  tmp;
    __m256 topBit = _mm256_set1_epi64x(1LLU << 63);

    bitonic_sort_float_04v_descending(d01, d02, d03, d04);
    bitonic_sort_float_01v_ascending(d05);

    tmp = d05;
    
    d05 = _mm256_max_ps(d04, d05);
    d04 = _mm256_min_ps(d04, tmp);

    bitonic_sort_float_04v_merge_descending(d01, d02, d03, d04);
    bitonic_sort_float_01v_merge_descending(d05);
}

static inline void bitonic_sort_float_05v_merge_ascending(__m256& d01, __m256& d02, __m256& d03, __m256& d04, __m256& d05) {
    __m256  tmp;
    __m256 topBit = _mm256_set1_epi64x(1LLU << 63);

    tmp = d01;
    
    d01 = _mm256_min_ps(d05, d01);
    
    d05 = _mm256_max_ps(d05, tmp);

    bitonic_sort_float_04v_merge_ascending(d01, d02, d03, d04);
    bitonic_sort_float_01v_merge_ascending(d05);
}

static inline void bitonic_sort_float_05v_merge_descending(__m256& d01, __m256& d02, __m256& d03, __m256& d04, __m256& d05) {
    __m256  tmp;
    __m256 topBit = _mm256_set1_epi64x(1LLU << 63);

    tmp = d01;
    
    d01 = _mm256_min_ps(d05, d01);
    
    d05 = _mm256_max_ps(d05, tmp);

    bitonic_sort_float_04v_merge_descending(d01, d02, d03, d04);
    bitonic_sort_float_01v_merge_descending(d05);
}

static inline void bitonic_sort_float_06v_ascending(__m256& d01, __m256& d02, __m256& d03, __m256& d04, __m256& d05, __m256& d06) {
    __m256  tmp;
    __m256 topBit = _mm256_set1_epi64x(1LLU << 63);

    bitonic_sort_float_04v_ascending(d01, d02, d03, d04);
    bitonic_sort_float_02v_descending(d05, d06);

    tmp = d05;
    
    d05 = _mm256_max_ps(d04, d05);
    d04 = _mm256_min_ps(d04, tmp);

    tmp = d06;
    
    d06 = _mm256_max_ps(d03, d06);
    d03 = _mm256_min_ps(d03, tmp);

    bitonic_sort_float_04v_merge_ascending(d01, d02, d03, d04);
    bitonic_sort_float_02v_merge_ascending(d05, d06);
}

static inline void bitonic_sort_float_06v_descending(__m256& d01, __m256& d02, __m256& d03, __m256& d04, __m256& d05, __m256& d06) {
    __m256  tmp;
    __m256 topBit = _mm256_set1_epi64x(1LLU << 63);

    bitonic_sort_float_04v_descending(d01, d02, d03, d04);
    bitonic_sort_float_02v_ascending(d05, d06);

    tmp = d05;
    
    d05 = _mm256_max_ps(d04, d05);
    d04 = _mm256_min_ps(d04, tmp);

    tmp = d06;
    
    d06 = _mm256_max_ps(d03, d06);
    d03 = _mm256_min_ps(d03, tmp);

    bitonic_sort_float_04v_merge_descending(d01, d02, d03, d04);
    bitonic_sort_float_02v_merge_descending(d05, d06);
}

static inline void bitonic_sort_float_06v_merge_ascending(__m256& d01, __m256& d02, __m256& d03, __m256& d04, __m256& d05, __m256& d06) {
    __m256  tmp;
    __m256 topBit = _mm256_set1_epi64x(1LLU << 63);

    tmp = d01;
    
    d01 = _mm256_min_ps(d05, d01);
    
    d05 = _mm256_max_ps(d05, tmp);

    tmp = d02;
    
    d02 = _mm256_min_ps(d06, d02);
    
    d06 = _mm256_max_ps(d06, tmp);

    bitonic_sort_float_04v_merge_ascending(d01, d02, d03, d04);
    bitonic_sort_float_02v_merge_ascending(d05, d06);
}

static inline void bitonic_sort_float_06v_merge_descending(__m256& d01, __m256& d02, __m256& d03, __m256& d04, __m256& d05, __m256& d06) {
    __m256  tmp;
    __m256 topBit = _mm256_set1_epi64x(1LLU << 63);

    tmp = d01;
    
    d01 = _mm256_min_ps(d05, d01);
    
    d05 = _mm256_max_ps(d05, tmp);

    tmp = d02;
    
    d02 = _mm256_min_ps(d06, d02);
    
    d06 = _mm256_max_ps(d06, tmp);

    bitonic_sort_float_04v_merge_descending(d01, d02, d03, d04);
    bitonic_sort_float_02v_merge_descending(d05, d06);
}

static inline void bitonic_sort_float_07v_ascending(__m256& d01, __m256& d02, __m256& d03, __m256& d04, __m256& d05, __m256& d06, __m256& d07) {
    __m256  tmp;
    __m256 topBit = _mm256_set1_epi64x(1LLU << 63);

    bitonic_sort_float_04v_ascending(d01, d02, d03, d04);
    bitonic_sort_float_03v_descending(d05, d06, d07);

    tmp = d05;
    
    d05 = _mm256_max_ps(d04, d05);
    d04 = _mm256_min_ps(d04, tmp);

    tmp = d06;
    
    d06 = _mm256_max_ps(d03, d06);
    d03 = _mm256_min_ps(d03, tmp);

    tmp = d07;
    
    d07 = _mm256_max_ps(d02, d07);
    d02 = _mm256_min_ps(d02, tmp);

    bitonic_sort_float_04v_merge_ascending(d01, d02, d03, d04);
    bitonic_sort_float_03v_merge_ascending(d05, d06, d07);
}

static inline void bitonic_sort_float_07v_descending(__m256& d01, __m256& d02, __m256& d03, __m256& d04, __m256& d05, __m256& d06, __m256& d07) {
    __m256  tmp;
    __m256 topBit = _mm256_set1_epi64x(1LLU << 63);

    bitonic_sort_float_04v_descending(d01, d02, d03, d04);
    bitonic_sort_float_03v_ascending(d05, d06, d07);

    tmp = d05;
    
    d05 = _mm256_max_ps(d04, d05);
    d04 = _mm256_min_ps(d04, tmp);

    tmp = d06;
    
    d06 = _mm256_max_ps(d03, d06);
    d03 = _mm256_min_ps(d03, tmp);

    tmp = d07;
    
    d07 = _mm256_max_ps(d02, d07);
    d02 = _mm256_min_ps(d02, tmp);

    bitonic_sort_float_04v_merge_descending(d01, d02, d03, d04);
    bitonic_sort_float_03v_merge_descending(d05, d06, d07);
}

static inline void bitonic_sort_float_07v_merge_ascending(__m256& d01, __m256& d02, __m256& d03, __m256& d04, __m256& d05, __m256& d06, __m256& d07) {
    __m256  tmp;
    __m256 topBit = _mm256_set1_epi64x(1LLU << 63);

    tmp = d01;
    
    d01 = _mm256_min_ps(d05, d01);
    
    d05 = _mm256_max_ps(d05, tmp);

    tmp = d02;
    
    d02 = _mm256_min_ps(d06, d02);
    
    d06 = _mm256_max_ps(d06, tmp);

    tmp = d03;
    
    d03 = _mm256_min_ps(d07, d03);
    
    d07 = _mm256_max_ps(d07, tmp);

    bitonic_sort_float_04v_merge_ascending(d01, d02, d03, d04);
    bitonic_sort_float_03v_merge_ascending(d05, d06, d07);
}

static inline void bitonic_sort_float_07v_merge_descending(__m256& d01, __m256& d02, __m256& d03, __m256& d04, __m256& d05, __m256& d06, __m256& d07) {
    __m256  tmp;
    __m256 topBit = _mm256_set1_epi64x(1LLU << 63);

    tmp = d01;
    
    d01 = _mm256_min_ps(d05, d01);
    
    d05 = _mm256_max_ps(d05, tmp);

    tmp = d02;
    
    d02 = _mm256_min_ps(d06, d02);
    
    d06 = _mm256_max_ps(d06, tmp);

    tmp = d03;
    
    d03 = _mm256_min_ps(d07, d03);
    
    d07 = _mm256_max_ps(d07, tmp);

    bitonic_sort_float_04v_merge_descending(d01, d02, d03, d04);
    bitonic_sort_float_03v_merge_descending(d05, d06, d07);
}

static inline void bitonic_sort_float_08v_ascending(__m256& d01, __m256& d02, __m256& d03, __m256& d04, __m256& d05, __m256& d06, __m256& d07, __m256& d08) {
    __m256  tmp;
    __m256 topBit = _mm256_set1_epi64x(1LLU << 63);

    bitonic_sort_float_04v_ascending(d01, d02, d03, d04);
    bitonic_sort_float_04v_descending(d05, d06, d07, d08);

    tmp = d05;
    
    d05 = _mm256_max_ps(d04, d05);
    d04 = _mm256_min_ps(d04, tmp);

    tmp = d06;
    
    d06 = _mm256_max_ps(d03, d06);
    d03 = _mm256_min_ps(d03, tmp);

    tmp = d07;
    
    d07 = _mm256_max_ps(d02, d07);
    d02 = _mm256_min_ps(d02, tmp);

    tmp = d08;
    
    d08 = _mm256_max_ps(d01, d08);
    d01 = _mm256_min_ps(d01, tmp);

    bitonic_sort_float_04v_merge_ascending(d01, d02, d03, d04);
    bitonic_sort_float_04v_merge_ascending(d05, d06, d07, d08);
}

static inline void bitonic_sort_float_08v_descending(__m256& d01, __m256& d02, __m256& d03, __m256& d04, __m256& d05, __m256& d06, __m256& d07, __m256& d08) {
    __m256  tmp;
    __m256 topBit = _mm256_set1_epi64x(1LLU << 63);

    bitonic_sort_float_04v_descending(d01, d02, d03, d04);
    bitonic_sort_float_04v_ascending(d05, d06, d07, d08);

    tmp = d05;
    
    d05 = _mm256_max_ps(d04, d05);
    d04 = _mm256_min_ps(d04, tmp);

    tmp = d06;
    
    d06 = _mm256_max_ps(d03, d06);
    d03 = _mm256_min_ps(d03, tmp);

    tmp = d07;
    
    d07 = _mm256_max_ps(d02, d07);
    d02 = _mm256_min_ps(d02, tmp);

    tmp = d08;
    
    d08 = _mm256_max_ps(d01, d08);
    d01 = _mm256_min_ps(d01, tmp);

    bitonic_sort_float_04v_merge_descending(d01, d02, d03, d04);
    bitonic_sort_float_04v_merge_descending(d05, d06, d07, d08);
}

static inline void bitonic_sort_float_08v_merge_ascending(__m256& d01, __m256& d02, __m256& d03, __m256& d04, __m256& d05, __m256& d06, __m256& d07, __m256& d08) {
    __m256  tmp;
    __m256 topBit = _mm256_set1_epi64x(1LLU << 63);

    tmp = d01;
    
    d01 = _mm256_min_ps(d05, d01);
    
    d05 = _mm256_max_ps(d05, tmp);

    tmp = d02;
    
    d02 = _mm256_min_ps(d06, d02);
    
    d06 = _mm256_max_ps(d06, tmp);

    tmp = d03;
    
    d03 = _mm256_min_ps(d07, d03);
    
    d07 = _mm256_max_ps(d07, tmp);

    tmp = d04;
    
    d04 = _mm256_min_ps(d08, d04);
    
    d08 = _mm256_max_ps(d08, tmp);

    bitonic_sort_float_04v_merge_ascending(d01, d02, d03, d04);
    bitonic_sort_float_04v_merge_ascending(d05, d06, d07, d08);
}

static inline void bitonic_sort_float_08v_merge_descending(__m256& d01, __m256& d02, __m256& d03, __m256& d04, __m256& d05, __m256& d06, __m256& d07, __m256& d08) {
    __m256  tmp;
    __m256 topBit = _mm256_set1_epi64x(1LLU << 63);

    tmp = d01;
    
    d01 = _mm256_min_ps(d05, d01);
    
    d05 = _mm256_max_ps(d05, tmp);

    tmp = d02;
    
    d02 = _mm256_min_ps(d06, d02);
    
    d06 = _mm256_max_ps(d06, tmp);

    tmp = d03;
    
    d03 = _mm256_min_ps(d07, d03);
    
    d07 = _mm256_max_ps(d07, tmp);

    tmp = d04;
    
    d04 = _mm256_min_ps(d08, d04);
    
    d08 = _mm256_max_ps(d08, tmp);

    bitonic_sort_float_04v_merge_descending(d01, d02, d03, d04);
    bitonic_sort_float_04v_merge_descending(d05, d06, d07, d08);
}

static inline void bitonic_sort_float_09v_ascending(__m256& d01, __m256& d02, __m256& d03, __m256& d04, __m256& d05, __m256& d06, __m256& d07, __m256& d08, __m256& d09) {
    __m256  tmp;
    __m256 topBit = _mm256_set1_epi64x(1LLU << 63);

    bitonic_sort_float_08v_ascending(d01, d02, d03, d04, d05, d06, d07, d08);
    bitonic_sort_float_01v_descending(d09);

    tmp = d09;
    
    d09 = _mm256_max_ps(d08, d09);
    d08 = _mm256_min_ps(d08, tmp);

    bitonic_sort_float_08v_merge_ascending(d01, d02, d03, d04, d05, d06, d07, d08);
    bitonic_sort_float_01v_merge_ascending(d09);
}

static inline void bitonic_sort_float_09v_descending(__m256& d01, __m256& d02, __m256& d03, __m256& d04, __m256& d05, __m256& d06, __m256& d07, __m256& d08, __m256& d09) {
    __m256  tmp;
    __m256 topBit = _mm256_set1_epi64x(1LLU << 63);

    bitonic_sort_float_08v_descending(d01, d02, d03, d04, d05, d06, d07, d08);
    bitonic_sort_float_01v_ascending(d09);

    tmp = d09;
    
    d09 = _mm256_max_ps(d08, d09);
    d08 = _mm256_min_ps(d08, tmp);

    bitonic_sort_float_08v_merge_descending(d01, d02, d03, d04, d05, d06, d07, d08);
    bitonic_sort_float_01v_merge_descending(d09);
}

static inline void bitonic_sort_float_09v_merge_ascending(__m256& d01, __m256& d02, __m256& d03, __m256& d04, __m256& d05, __m256& d06, __m256& d07, __m256& d08, __m256& d09) {
    __m256  tmp;
    __m256 topBit = _mm256_set1_epi64x(1LLU << 63);

    tmp = d01;
    
    d01 = _mm256_min_ps(d09, d01);
    
    d09 = _mm256_max_ps(d09, tmp);

    bitonic_sort_float_08v_merge_ascending(d01, d02, d03, d04, d05, d06, d07, d08);
    bitonic_sort_float_01v_merge_ascending(d09);
}

static inline void bitonic_sort_float_09v_merge_descending(__m256& d01, __m256& d02, __m256& d03, __m256& d04, __m256& d05, __m256& d06, __m256& d07, __m256& d08, __m256& d09) {
    __m256  tmp;
    __m256 topBit = _mm256_set1_epi64x(1LLU << 63);

    tmp = d01;
    
    d01 = _mm256_min_ps(d09, d01);
    
    d09 = _mm256_max_ps(d09, tmp);

    bitonic_sort_float_08v_merge_descending(d01, d02, d03, d04, d05, d06, d07, d08);
    bitonic_sort_float_01v_merge_descending(d09);
}

static inline void bitonic_sort_float_10v_ascending(__m256& d01, __m256& d02, __m256& d03, __m256& d04, __m256& d05, __m256& d06, __m256& d07, __m256& d08, __m256& d09, __m256& d10) {
    __m256  tmp;
    __m256 topBit = _mm256_set1_epi64x(1LLU << 63);

    bitonic_sort_float_08v_ascending(d01, d02, d03, d04, d05, d06, d07, d08);
    bitonic_sort_float_02v_descending(d09, d10);

    tmp = d09;
    
    d09 = _mm256_max_ps(d08, d09);
    d08 = _mm256_min_ps(d08, tmp);

    tmp = d10;
    
    d10 = _mm256_max_ps(d07, d10);
    d07 = _mm256_min_ps(d07, tmp);

    bitonic_sort_float_08v_merge_ascending(d01, d02, d03, d04, d05, d06, d07, d08);
    bitonic_sort_float_02v_merge_ascending(d09, d10);
}

static inline void bitonic_sort_float_10v_descending(__m256& d01, __m256& d02, __m256& d03, __m256& d04, __m256& d05, __m256& d06, __m256& d07, __m256& d08, __m256& d09, __m256& d10) {
    __m256  tmp;
    __m256 topBit = _mm256_set1_epi64x(1LLU << 63);

    bitonic_sort_float_08v_descending(d01, d02, d03, d04, d05, d06, d07, d08);
    bitonic_sort_float_02v_ascending(d09, d10);

    tmp = d09;
    
    d09 = _mm256_max_ps(d08, d09);
    d08 = _mm256_min_ps(d08, tmp);

    tmp = d10;
    
    d10 = _mm256_max_ps(d07, d10);
    d07 = _mm256_min_ps(d07, tmp);

    bitonic_sort_float_08v_merge_descending(d01, d02, d03, d04, d05, d06, d07, d08);
    bitonic_sort_float_02v_merge_descending(d09, d10);
}

static inline void bitonic_sort_float_10v_merge_ascending(__m256& d01, __m256& d02, __m256& d03, __m256& d04, __m256& d05, __m256& d06, __m256& d07, __m256& d08, __m256& d09, __m256& d10) {
    __m256  tmp;
    __m256 topBit = _mm256_set1_epi64x(1LLU << 63);

    tmp = d01;
    
    d01 = _mm256_min_ps(d09, d01);
    
    d09 = _mm256_max_ps(d09, tmp);

    tmp = d02;
    
    d02 = _mm256_min_ps(d10, d02);
    
    d10 = _mm256_max_ps(d10, tmp);

    bitonic_sort_float_08v_merge_ascending(d01, d02, d03, d04, d05, d06, d07, d08);
    bitonic_sort_float_02v_merge_ascending(d09, d10);
}

static inline void bitonic_sort_float_10v_merge_descending(__m256& d01, __m256& d02, __m256& d03, __m256& d04, __m256& d05, __m256& d06, __m256& d07, __m256& d08, __m256& d09, __m256& d10) {
    __m256  tmp;
    __m256 topBit = _mm256_set1_epi64x(1LLU << 63);

    tmp = d01;
    
    d01 = _mm256_min_ps(d09, d01);
    
    d09 = _mm256_max_ps(d09, tmp);

    tmp = d02;
    
    d02 = _mm256_min_ps(d10, d02);
    
    d10 = _mm256_max_ps(d10, tmp);

    bitonic_sort_float_08v_merge_descending(d01, d02, d03, d04, d05, d06, d07, d08);
    bitonic_sort_float_02v_merge_descending(d09, d10);
}

static inline void bitonic_sort_float_11v_ascending(__m256& d01, __m256& d02, __m256& d03, __m256& d04, __m256& d05, __m256& d06, __m256& d07, __m256& d08, __m256& d09, __m256& d10, __m256& d11) {
    __m256  tmp;
    __m256 topBit = _mm256_set1_epi64x(1LLU << 63);

    bitonic_sort_float_08v_ascending(d01, d02, d03, d04, d05, d06, d07, d08);
    bitonic_sort_float_03v_descending(d09, d10, d11);

    tmp = d09;
    
    d09 = _mm256_max_ps(d08, d09);
    d08 = _mm256_min_ps(d08, tmp);

    tmp = d10;
    
    d10 = _mm256_max_ps(d07, d10);
    d07 = _mm256_min_ps(d07, tmp);

    tmp = d11;
    
    d11 = _mm256_max_ps(d06, d11);
    d06 = _mm256_min_ps(d06, tmp);

    bitonic_sort_float_08v_merge_ascending(d01, d02, d03, d04, d05, d06, d07, d08);
    bitonic_sort_float_03v_merge_ascending(d09, d10, d11);
}

static inline void bitonic_sort_float_11v_descending(__m256& d01, __m256& d02, __m256& d03, __m256& d04, __m256& d05, __m256& d06, __m256& d07, __m256& d08, __m256& d09, __m256& d10, __m256& d11) {
    __m256  tmp;
    __m256 topBit = _mm256_set1_epi64x(1LLU << 63);

    bitonic_sort_float_08v_descending(d01, d02, d03, d04, d05, d06, d07, d08);
    bitonic_sort_float_03v_ascending(d09, d10, d11);

    tmp = d09;
    
    d09 = _mm256_max_ps(d08, d09);
    d08 = _mm256_min_ps(d08, tmp);

    tmp = d10;
    
    d10 = _mm256_max_ps(d07, d10);
    d07 = _mm256_min_ps(d07, tmp);

    tmp = d11;
    
    d11 = _mm256_max_ps(d06, d11);
    d06 = _mm256_min_ps(d06, tmp);

    bitonic_sort_float_08v_merge_descending(d01, d02, d03, d04, d05, d06, d07, d08);
    bitonic_sort_float_03v_merge_descending(d09, d10, d11);
}

static inline void bitonic_sort_float_11v_merge_ascending(__m256& d01, __m256& d02, __m256& d03, __m256& d04, __m256& d05, __m256& d06, __m256& d07, __m256& d08, __m256& d09, __m256& d10, __m256& d11) {
    __m256  tmp;
    __m256 topBit = _mm256_set1_epi64x(1LLU << 63);

    tmp = d01;
    
    d01 = _mm256_min_ps(d09, d01);
    
    d09 = _mm256_max_ps(d09, tmp);

    tmp = d02;
    
    d02 = _mm256_min_ps(d10, d02);
    
    d10 = _mm256_max_ps(d10, tmp);

    tmp = d03;
    
    d03 = _mm256_min_ps(d11, d03);
    
    d11 = _mm256_max_ps(d11, tmp);

    bitonic_sort_float_08v_merge_ascending(d01, d02, d03, d04, d05, d06, d07, d08);
    bitonic_sort_float_03v_merge_ascending(d09, d10, d11);
}

static inline void bitonic_sort_float_11v_merge_descending(__m256& d01, __m256& d02, __m256& d03, __m256& d04, __m256& d05, __m256& d06, __m256& d07, __m256& d08, __m256& d09, __m256& d10, __m256& d11) {
    __m256  tmp;
    __m256 topBit = _mm256_set1_epi64x(1LLU << 63);

    tmp = d01;
    
    d01 = _mm256_min_ps(d09, d01);
    
    d09 = _mm256_max_ps(d09, tmp);

    tmp = d02;
    
    d02 = _mm256_min_ps(d10, d02);
    
    d10 = _mm256_max_ps(d10, tmp);

    tmp = d03;
    
    d03 = _mm256_min_ps(d11, d03);
    
    d11 = _mm256_max_ps(d11, tmp);

    bitonic_sort_float_08v_merge_descending(d01, d02, d03, d04, d05, d06, d07, d08);
    bitonic_sort_float_03v_merge_descending(d09, d10, d11);
}

static inline void bitonic_sort_float_12v_ascending(__m256& d01, __m256& d02, __m256& d03, __m256& d04, __m256& d05, __m256& d06, __m256& d07, __m256& d08, __m256& d09, __m256& d10, __m256& d11, __m256& d12) {
    __m256  tmp;
    __m256 topBit = _mm256_set1_epi64x(1LLU << 63);

    bitonic_sort_float_08v_ascending(d01, d02, d03, d04, d05, d06, d07, d08);
    bitonic_sort_float_04v_descending(d09, d10, d11, d12);

    tmp = d09;
    
    d09 = _mm256_max_ps(d08, d09);
    d08 = _mm256_min_ps(d08, tmp);

    tmp = d10;
    
    d10 = _mm256_max_ps(d07, d10);
    d07 = _mm256_min_ps(d07, tmp);

    tmp = d11;
    
    d11 = _mm256_max_ps(d06, d11);
    d06 = _mm256_min_ps(d06, tmp);

    tmp = d12;
    
    d12 = _mm256_max_ps(d05, d12);
    d05 = _mm256_min_ps(d05, tmp);

    bitonic_sort_float_08v_merge_ascending(d01, d02, d03, d04, d05, d06, d07, d08);
    bitonic_sort_float_04v_merge_ascending(d09, d10, d11, d12);
}

static inline void bitonic_sort_float_12v_descending(__m256& d01, __m256& d02, __m256& d03, __m256& d04, __m256& d05, __m256& d06, __m256& d07, __m256& d08, __m256& d09, __m256& d10, __m256& d11, __m256& d12) {
    __m256  tmp;
    __m256 topBit = _mm256_set1_epi64x(1LLU << 63);

    bitonic_sort_float_08v_descending(d01, d02, d03, d04, d05, d06, d07, d08);
    bitonic_sort_float_04v_ascending(d09, d10, d11, d12);

    tmp = d09;
    
    d09 = _mm256_max_ps(d08, d09);
    d08 = _mm256_min_ps(d08, tmp);

    tmp = d10;
    
    d10 = _mm256_max_ps(d07, d10);
    d07 = _mm256_min_ps(d07, tmp);

    tmp = d11;
    
    d11 = _mm256_max_ps(d06, d11);
    d06 = _mm256_min_ps(d06, tmp);

    tmp = d12;
    
    d12 = _mm256_max_ps(d05, d12);
    d05 = _mm256_min_ps(d05, tmp);

    bitonic_sort_float_08v_merge_descending(d01, d02, d03, d04, d05, d06, d07, d08);
    bitonic_sort_float_04v_merge_descending(d09, d10, d11, d12);
}

static inline void bitonic_sort_float_12v_merge_ascending(__m256& d01, __m256& d02, __m256& d03, __m256& d04, __m256& d05, __m256& d06, __m256& d07, __m256& d08, __m256& d09, __m256& d10, __m256& d11, __m256& d12) {
    __m256  tmp;
    __m256 topBit = _mm256_set1_epi64x(1LLU << 63);

    tmp = d01;
    
    d01 = _mm256_min_ps(d09, d01);
    
    d09 = _mm256_max_ps(d09, tmp);

    tmp = d02;
    
    d02 = _mm256_min_ps(d10, d02);
    
    d10 = _mm256_max_ps(d10, tmp);

    tmp = d03;
    
    d03 = _mm256_min_ps(d11, d03);
    
    d11 = _mm256_max_ps(d11, tmp);

    tmp = d04;
    
    d04 = _mm256_min_ps(d12, d04);
    
    d12 = _mm256_max_ps(d12, tmp);

    bitonic_sort_float_08v_merge_ascending(d01, d02, d03, d04, d05, d06, d07, d08);
    bitonic_sort_float_04v_merge_ascending(d09, d10, d11, d12);
}

static inline void bitonic_sort_float_12v_merge_descending(__m256& d01, __m256& d02, __m256& d03, __m256& d04, __m256& d05, __m256& d06, __m256& d07, __m256& d08, __m256& d09, __m256& d10, __m256& d11, __m256& d12) {
    __m256  tmp;
    __m256 topBit = _mm256_set1_epi64x(1LLU << 63);

    tmp = d01;
    
    d01 = _mm256_min_ps(d09, d01);
    
    d09 = _mm256_max_ps(d09, tmp);

    tmp = d02;
    
    d02 = _mm256_min_ps(d10, d02);
    
    d10 = _mm256_max_ps(d10, tmp);

    tmp = d03;
    
    d03 = _mm256_min_ps(d11, d03);
    
    d11 = _mm256_max_ps(d11, tmp);

    tmp = d04;
    
    d04 = _mm256_min_ps(d12, d04);
    
    d12 = _mm256_max_ps(d12, tmp);

    bitonic_sort_float_08v_merge_descending(d01, d02, d03, d04, d05, d06, d07, d08);
    bitonic_sort_float_04v_merge_descending(d09, d10, d11, d12);
}

static inline void bitonic_sort_float_13v_ascending(__m256& d01, __m256& d02, __m256& d03, __m256& d04, __m256& d05, __m256& d06, __m256& d07, __m256& d08, __m256& d09, __m256& d10, __m256& d11, __m256& d12, __m256& d13) {
    __m256  tmp;
    __m256 topBit = _mm256_set1_epi64x(1LLU << 63);

    bitonic_sort_float_08v_ascending(d01, d02, d03, d04, d05, d06, d07, d08);
    bitonic_sort_float_05v_descending(d09, d10, d11, d12, d13);

    tmp = d09;
    
    d09 = _mm256_max_ps(d08, d09);
    d08 = _mm256_min_ps(d08, tmp);

    tmp = d10;
    
    d10 = _mm256_max_ps(d07, d10);
    d07 = _mm256_min_ps(d07, tmp);

    tmp = d11;
    
    d11 = _mm256_max_ps(d06, d11);
    d06 = _mm256_min_ps(d06, tmp);

    tmp = d12;
    
    d12 = _mm256_max_ps(d05, d12);
    d05 = _mm256_min_ps(d05, tmp);

    tmp = d13;
    
    d13 = _mm256_max_ps(d04, d13);
    d04 = _mm256_min_ps(d04, tmp);

    bitonic_sort_float_08v_merge_ascending(d01, d02, d03, d04, d05, d06, d07, d08);
    bitonic_sort_float_05v_merge_ascending(d09, d10, d11, d12, d13);
}

static inline void bitonic_sort_float_13v_descending(__m256& d01, __m256& d02, __m256& d03, __m256& d04, __m256& d05, __m256& d06, __m256& d07, __m256& d08, __m256& d09, __m256& d10, __m256& d11, __m256& d12, __m256& d13) {
    __m256  tmp;
    __m256 topBit = _mm256_set1_epi64x(1LLU << 63);

    bitonic_sort_float_08v_descending(d01, d02, d03, d04, d05, d06, d07, d08);
    bitonic_sort_float_05v_ascending(d09, d10, d11, d12, d13);

    tmp = d09;
    
    d09 = _mm256_max_ps(d08, d09);
    d08 = _mm256_min_ps(d08, tmp);

    tmp = d10;
    
    d10 = _mm256_max_ps(d07, d10);
    d07 = _mm256_min_ps(d07, tmp);

    tmp = d11;
    
    d11 = _mm256_max_ps(d06, d11);
    d06 = _mm256_min_ps(d06, tmp);

    tmp = d12;
    
    d12 = _mm256_max_ps(d05, d12);
    d05 = _mm256_min_ps(d05, tmp);

    tmp = d13;
    
    d13 = _mm256_max_ps(d04, d13);
    d04 = _mm256_min_ps(d04, tmp);

    bitonic_sort_float_08v_merge_descending(d01, d02, d03, d04, d05, d06, d07, d08);
    bitonic_sort_float_05v_merge_descending(d09, d10, d11, d12, d13);
}

static inline void bitonic_sort_float_13v_merge_ascending(__m256& d01, __m256& d02, __m256& d03, __m256& d04, __m256& d05, __m256& d06, __m256& d07, __m256& d08, __m256& d09, __m256& d10, __m256& d11, __m256& d12, __m256& d13) {
    __m256  tmp;
    __m256 topBit = _mm256_set1_epi64x(1LLU << 63);

    tmp = d01;
    
    d01 = _mm256_min_ps(d09, d01);
    
    d09 = _mm256_max_ps(d09, tmp);

    tmp = d02;
    
    d02 = _mm256_min_ps(d10, d02);
    
    d10 = _mm256_max_ps(d10, tmp);

    tmp = d03;
    
    d03 = _mm256_min_ps(d11, d03);
    
    d11 = _mm256_max_ps(d11, tmp);

    tmp = d04;
    
    d04 = _mm256_min_ps(d12, d04);
    
    d12 = _mm256_max_ps(d12, tmp);

    tmp = d05;
    
    d05 = _mm256_min_ps(d13, d05);
    
    d13 = _mm256_max_ps(d13, tmp);

    bitonic_sort_float_08v_merge_ascending(d01, d02, d03, d04, d05, d06, d07, d08);
    bitonic_sort_float_05v_merge_ascending(d09, d10, d11, d12, d13);
}

static inline void bitonic_sort_float_13v_merge_descending(__m256& d01, __m256& d02, __m256& d03, __m256& d04, __m256& d05, __m256& d06, __m256& d07, __m256& d08, __m256& d09, __m256& d10, __m256& d11, __m256& d12, __m256& d13) {
    __m256  tmp;
    __m256 topBit = _mm256_set1_epi64x(1LLU << 63);

    tmp = d01;
    
    d01 = _mm256_min_ps(d09, d01);
    
    d09 = _mm256_max_ps(d09, tmp);

    tmp = d02;
    
    d02 = _mm256_min_ps(d10, d02);
    
    d10 = _mm256_max_ps(d10, tmp);

    tmp = d03;
    
    d03 = _mm256_min_ps(d11, d03);
    
    d11 = _mm256_max_ps(d11, tmp);

    tmp = d04;
    
    d04 = _mm256_min_ps(d12, d04);
    
    d12 = _mm256_max_ps(d12, tmp);

    tmp = d05;
    
    d05 = _mm256_min_ps(d13, d05);
    
    d13 = _mm256_max_ps(d13, tmp);

    bitonic_sort_float_08v_merge_descending(d01, d02, d03, d04, d05, d06, d07, d08);
    bitonic_sort_float_05v_merge_descending(d09, d10, d11, d12, d13);
}

static inline void bitonic_sort_float_14v_ascending(__m256& d01, __m256& d02, __m256& d03, __m256& d04, __m256& d05, __m256& d06, __m256& d07, __m256& d08, __m256& d09, __m256& d10, __m256& d11, __m256& d12, __m256& d13, __m256& d14) {
    __m256  tmp;
    __m256 topBit = _mm256_set1_epi64x(1LLU << 63);

    bitonic_sort_float_08v_ascending(d01, d02, d03, d04, d05, d06, d07, d08);
    bitonic_sort_float_06v_descending(d09, d10, d11, d12, d13, d14);

    tmp = d09;
    
    d09 = _mm256_max_ps(d08, d09);
    d08 = _mm256_min_ps(d08, tmp);

    tmp = d10;
    
    d10 = _mm256_max_ps(d07, d10);
    d07 = _mm256_min_ps(d07, tmp);

    tmp = d11;
    
    d11 = _mm256_max_ps(d06, d11);
    d06 = _mm256_min_ps(d06, tmp);

    tmp = d12;
    
    d12 = _mm256_max_ps(d05, d12);
    d05 = _mm256_min_ps(d05, tmp);

    tmp = d13;
    
    d13 = _mm256_max_ps(d04, d13);
    d04 = _mm256_min_ps(d04, tmp);

    tmp = d14;
    
    d14 = _mm256_max_ps(d03, d14);
    d03 = _mm256_min_ps(d03, tmp);

    bitonic_sort_float_08v_merge_ascending(d01, d02, d03, d04, d05, d06, d07, d08);
    bitonic_sort_float_06v_merge_ascending(d09, d10, d11, d12, d13, d14);
}

static inline void bitonic_sort_float_14v_descending(__m256& d01, __m256& d02, __m256& d03, __m256& d04, __m256& d05, __m256& d06, __m256& d07, __m256& d08, __m256& d09, __m256& d10, __m256& d11, __m256& d12, __m256& d13, __m256& d14) {
    __m256  tmp;
    __m256 topBit = _mm256_set1_epi64x(1LLU << 63);

    bitonic_sort_float_08v_descending(d01, d02, d03, d04, d05, d06, d07, d08);
    bitonic_sort_float_06v_ascending(d09, d10, d11, d12, d13, d14);

    tmp = d09;
    
    d09 = _mm256_max_ps(d08, d09);
    d08 = _mm256_min_ps(d08, tmp);

    tmp = d10;
    
    d10 = _mm256_max_ps(d07, d10);
    d07 = _mm256_min_ps(d07, tmp);

    tmp = d11;
    
    d11 = _mm256_max_ps(d06, d11);
    d06 = _mm256_min_ps(d06, tmp);

    tmp = d12;
    
    d12 = _mm256_max_ps(d05, d12);
    d05 = _mm256_min_ps(d05, tmp);

    tmp = d13;
    
    d13 = _mm256_max_ps(d04, d13);
    d04 = _mm256_min_ps(d04, tmp);

    tmp = d14;
    
    d14 = _mm256_max_ps(d03, d14);
    d03 = _mm256_min_ps(d03, tmp);

    bitonic_sort_float_08v_merge_descending(d01, d02, d03, d04, d05, d06, d07, d08);
    bitonic_sort_float_06v_merge_descending(d09, d10, d11, d12, d13, d14);
}

static inline void bitonic_sort_float_14v_merge_ascending(__m256& d01, __m256& d02, __m256& d03, __m256& d04, __m256& d05, __m256& d06, __m256& d07, __m256& d08, __m256& d09, __m256& d10, __m256& d11, __m256& d12, __m256& d13, __m256& d14) {
    __m256  tmp;
    __m256 topBit = _mm256_set1_epi64x(1LLU << 63);

    tmp = d01;
    
    d01 = _mm256_min_ps(d09, d01);
    
    d09 = _mm256_max_ps(d09, tmp);

    tmp = d02;
    
    d02 = _mm256_min_ps(d10, d02);
    
    d10 = _mm256_max_ps(d10, tmp);

    tmp = d03;
    
    d03 = _mm256_min_ps(d11, d03);
    
    d11 = _mm256_max_ps(d11, tmp);

    tmp = d04;
    
    d04 = _mm256_min_ps(d12, d04);
    
    d12 = _mm256_max_ps(d12, tmp);

    tmp = d05;
    
    d05 = _mm256_min_ps(d13, d05);
    
    d13 = _mm256_max_ps(d13, tmp);

    tmp = d06;
    
    d06 = _mm256_min_ps(d14, d06);
    
    d14 = _mm256_max_ps(d14, tmp);

    bitonic_sort_float_08v_merge_ascending(d01, d02, d03, d04, d05, d06, d07, d08);
    bitonic_sort_float_06v_merge_ascending(d09, d10, d11, d12, d13, d14);
}

static inline void bitonic_sort_float_14v_merge_descending(__m256& d01, __m256& d02, __m256& d03, __m256& d04, __m256& d05, __m256& d06, __m256& d07, __m256& d08, __m256& d09, __m256& d10, __m256& d11, __m256& d12, __m256& d13, __m256& d14) {
    __m256  tmp;
    __m256 topBit = _mm256_set1_epi64x(1LLU << 63);

    tmp = d01;
    
    d01 = _mm256_min_ps(d09, d01);
    
    d09 = _mm256_max_ps(d09, tmp);

    tmp = d02;
    
    d02 = _mm256_min_ps(d10, d02);
    
    d10 = _mm256_max_ps(d10, tmp);

    tmp = d03;
    
    d03 = _mm256_min_ps(d11, d03);
    
    d11 = _mm256_max_ps(d11, tmp);

    tmp = d04;
    
    d04 = _mm256_min_ps(d12, d04);
    
    d12 = _mm256_max_ps(d12, tmp);

    tmp = d05;
    
    d05 = _mm256_min_ps(d13, d05);
    
    d13 = _mm256_max_ps(d13, tmp);

    tmp = d06;
    
    d06 = _mm256_min_ps(d14, d06);
    
    d14 = _mm256_max_ps(d14, tmp);

    bitonic_sort_float_08v_merge_descending(d01, d02, d03, d04, d05, d06, d07, d08);
    bitonic_sort_float_06v_merge_descending(d09, d10, d11, d12, d13, d14);
}

static inline void bitonic_sort_float_15v_ascending(__m256& d01, __m256& d02, __m256& d03, __m256& d04, __m256& d05, __m256& d06, __m256& d07, __m256& d08, __m256& d09, __m256& d10, __m256& d11, __m256& d12, __m256& d13, __m256& d14, __m256& d15) {
    __m256  tmp;
    __m256 topBit = _mm256_set1_epi64x(1LLU << 63);

    bitonic_sort_float_08v_ascending(d01, d02, d03, d04, d05, d06, d07, d08);
    bitonic_sort_float_07v_descending(d09, d10, d11, d12, d13, d14, d15);

    tmp = d09;
    
    d09 = _mm256_max_ps(d08, d09);
    d08 = _mm256_min_ps(d08, tmp);

    tmp = d10;
    
    d10 = _mm256_max_ps(d07, d10);
    d07 = _mm256_min_ps(d07, tmp);

    tmp = d11;
    
    d11 = _mm256_max_ps(d06, d11);
    d06 = _mm256_min_ps(d06, tmp);

    tmp = d12;
    
    d12 = _mm256_max_ps(d05, d12);
    d05 = _mm256_min_ps(d05, tmp);

    tmp = d13;
    
    d13 = _mm256_max_ps(d04, d13);
    d04 = _mm256_min_ps(d04, tmp);

    tmp = d14;
    
    d14 = _mm256_max_ps(d03, d14);
    d03 = _mm256_min_ps(d03, tmp);

    tmp = d15;
    
    d15 = _mm256_max_ps(d02, d15);
    d02 = _mm256_min_ps(d02, tmp);

    bitonic_sort_float_08v_merge_ascending(d01, d02, d03, d04, d05, d06, d07, d08);
    bitonic_sort_float_07v_merge_ascending(d09, d10, d11, d12, d13, d14, d15);
}

static inline void bitonic_sort_float_15v_descending(__m256& d01, __m256& d02, __m256& d03, __m256& d04, __m256& d05, __m256& d06, __m256& d07, __m256& d08, __m256& d09, __m256& d10, __m256& d11, __m256& d12, __m256& d13, __m256& d14, __m256& d15) {
    __m256  tmp;
    __m256 topBit = _mm256_set1_epi64x(1LLU << 63);

    bitonic_sort_float_08v_descending(d01, d02, d03, d04, d05, d06, d07, d08);
    bitonic_sort_float_07v_ascending(d09, d10, d11, d12, d13, d14, d15);

    tmp = d09;
    
    d09 = _mm256_max_ps(d08, d09);
    d08 = _mm256_min_ps(d08, tmp);

    tmp = d10;
    
    d10 = _mm256_max_ps(d07, d10);
    d07 = _mm256_min_ps(d07, tmp);

    tmp = d11;
    
    d11 = _mm256_max_ps(d06, d11);
    d06 = _mm256_min_ps(d06, tmp);

    tmp = d12;
    
    d12 = _mm256_max_ps(d05, d12);
    d05 = _mm256_min_ps(d05, tmp);

    tmp = d13;
    
    d13 = _mm256_max_ps(d04, d13);
    d04 = _mm256_min_ps(d04, tmp);

    tmp = d14;
    
    d14 = _mm256_max_ps(d03, d14);
    d03 = _mm256_min_ps(d03, tmp);

    tmp = d15;
    
    d15 = _mm256_max_ps(d02, d15);
    d02 = _mm256_min_ps(d02, tmp);

    bitonic_sort_float_08v_merge_descending(d01, d02, d03, d04, d05, d06, d07, d08);
    bitonic_sort_float_07v_merge_descending(d09, d10, d11, d12, d13, d14, d15);
}

static inline void bitonic_sort_float_15v_merge_ascending(__m256& d01, __m256& d02, __m256& d03, __m256& d04, __m256& d05, __m256& d06, __m256& d07, __m256& d08, __m256& d09, __m256& d10, __m256& d11, __m256& d12, __m256& d13, __m256& d14, __m256& d15) {
    __m256  tmp;
    __m256 topBit = _mm256_set1_epi64x(1LLU << 63);

    tmp = d01;
    
    d01 = _mm256_min_ps(d09, d01);
    
    d09 = _mm256_max_ps(d09, tmp);

    tmp = d02;
    
    d02 = _mm256_min_ps(d10, d02);
    
    d10 = _mm256_max_ps(d10, tmp);

    tmp = d03;
    
    d03 = _mm256_min_ps(d11, d03);
    
    d11 = _mm256_max_ps(d11, tmp);

    tmp = d04;
    
    d04 = _mm256_min_ps(d12, d04);
    
    d12 = _mm256_max_ps(d12, tmp);

    tmp = d05;
    
    d05 = _mm256_min_ps(d13, d05);
    
    d13 = _mm256_max_ps(d13, tmp);

    tmp = d06;
    
    d06 = _mm256_min_ps(d14, d06);
    
    d14 = _mm256_max_ps(d14, tmp);

    tmp = d07;
    
    d07 = _mm256_min_ps(d15, d07);
    
    d15 = _mm256_max_ps(d15, tmp);

    bitonic_sort_float_08v_merge_ascending(d01, d02, d03, d04, d05, d06, d07, d08);
    bitonic_sort_float_07v_merge_ascending(d09, d10, d11, d12, d13, d14, d15);
}

static inline void bitonic_sort_float_15v_merge_descending(__m256& d01, __m256& d02, __m256& d03, __m256& d04, __m256& d05, __m256& d06, __m256& d07, __m256& d08, __m256& d09, __m256& d10, __m256& d11, __m256& d12, __m256& d13, __m256& d14, __m256& d15) {
    __m256  tmp;
    __m256 topBit = _mm256_set1_epi64x(1LLU << 63);

    tmp = d01;
    
    d01 = _mm256_min_ps(d09, d01);
    
    d09 = _mm256_max_ps(d09, tmp);

    tmp = d02;
    
    d02 = _mm256_min_ps(d10, d02);
    
    d10 = _mm256_max_ps(d10, tmp);

    tmp = d03;
    
    d03 = _mm256_min_ps(d11, d03);
    
    d11 = _mm256_max_ps(d11, tmp);

    tmp = d04;
    
    d04 = _mm256_min_ps(d12, d04);
    
    d12 = _mm256_max_ps(d12, tmp);

    tmp = d05;
    
    d05 = _mm256_min_ps(d13, d05);
    
    d13 = _mm256_max_ps(d13, tmp);

    tmp = d06;
    
    d06 = _mm256_min_ps(d14, d06);
    
    d14 = _mm256_max_ps(d14, tmp);

    tmp = d07;
    
    d07 = _mm256_min_ps(d15, d07);
    
    d15 = _mm256_max_ps(d15, tmp);

    bitonic_sort_float_08v_merge_descending(d01, d02, d03, d04, d05, d06, d07, d08);
    bitonic_sort_float_07v_merge_descending(d09, d10, d11, d12, d13, d14, d15);
}

static inline void bitonic_sort_float_16v_ascending(__m256& d01, __m256& d02, __m256& d03, __m256& d04, __m256& d05, __m256& d06, __m256& d07, __m256& d08, __m256& d09, __m256& d10, __m256& d11, __m256& d12, __m256& d13, __m256& d14, __m256& d15, __m256& d16) {
    __m256  tmp;
    __m256 topBit = _mm256_set1_epi64x(1LLU << 63);

    bitonic_sort_float_08v_ascending(d01, d02, d03, d04, d05, d06, d07, d08);
    bitonic_sort_float_08v_descending(d09, d10, d11, d12, d13, d14, d15, d16);

    tmp = d09;
    
    d09 = _mm256_max_ps(d08, d09);
    d08 = _mm256_min_ps(d08, tmp);

    tmp = d10;
    
    d10 = _mm256_max_ps(d07, d10);
    d07 = _mm256_min_ps(d07, tmp);

    tmp = d11;
    
    d11 = _mm256_max_ps(d06, d11);
    d06 = _mm256_min_ps(d06, tmp);

    tmp = d12;
    
    d12 = _mm256_max_ps(d05, d12);
    d05 = _mm256_min_ps(d05, tmp);

    tmp = d13;
    
    d13 = _mm256_max_ps(d04, d13);
    d04 = _mm256_min_ps(d04, tmp);

    tmp = d14;
    
    d14 = _mm256_max_ps(d03, d14);
    d03 = _mm256_min_ps(d03, tmp);

    tmp = d15;
    
    d15 = _mm256_max_ps(d02, d15);
    d02 = _mm256_min_ps(d02, tmp);

    tmp = d16;
    
    d16 = _mm256_max_ps(d01, d16);
    d01 = _mm256_min_ps(d01, tmp);

    bitonic_sort_float_08v_merge_ascending(d01, d02, d03, d04, d05, d06, d07, d08);
    bitonic_sort_float_08v_merge_ascending(d09, d10, d11, d12, d13, d14, d15, d16);
}

static inline void bitonic_sort_float_16v_descending(__m256& d01, __m256& d02, __m256& d03, __m256& d04, __m256& d05, __m256& d06, __m256& d07, __m256& d08, __m256& d09, __m256& d10, __m256& d11, __m256& d12, __m256& d13, __m256& d14, __m256& d15, __m256& d16) {
    __m256  tmp;
    __m256 topBit = _mm256_set1_epi64x(1LLU << 63);

    bitonic_sort_float_08v_descending(d01, d02, d03, d04, d05, d06, d07, d08);
    bitonic_sort_float_08v_ascending(d09, d10, d11, d12, d13, d14, d15, d16);

    tmp = d09;
    
    d09 = _mm256_max_ps(d08, d09);
    d08 = _mm256_min_ps(d08, tmp);

    tmp = d10;
    
    d10 = _mm256_max_ps(d07, d10);
    d07 = _mm256_min_ps(d07, tmp);

    tmp = d11;
    
    d11 = _mm256_max_ps(d06, d11);
    d06 = _mm256_min_ps(d06, tmp);

    tmp = d12;
    
    d12 = _mm256_max_ps(d05, d12);
    d05 = _mm256_min_ps(d05, tmp);

    tmp = d13;
    
    d13 = _mm256_max_ps(d04, d13);
    d04 = _mm256_min_ps(d04, tmp);

    tmp = d14;
    
    d14 = _mm256_max_ps(d03, d14);
    d03 = _mm256_min_ps(d03, tmp);

    tmp = d15;
    
    d15 = _mm256_max_ps(d02, d15);
    d02 = _mm256_min_ps(d02, tmp);

    tmp = d16;
    
    d16 = _mm256_max_ps(d01, d16);
    d01 = _mm256_min_ps(d01, tmp);

    bitonic_sort_float_08v_merge_descending(d01, d02, d03, d04, d05, d06, d07, d08);
    bitonic_sort_float_08v_merge_descending(d09, d10, d11, d12, d13, d14, d15, d16);
}

static inline void bitonic_sort_float_16v_merge_ascending(__m256& d01, __m256& d02, __m256& d03, __m256& d04, __m256& d05, __m256& d06, __m256& d07, __m256& d08, __m256& d09, __m256& d10, __m256& d11, __m256& d12, __m256& d13, __m256& d14, __m256& d15, __m256& d16) {
    __m256  tmp;
    __m256 topBit = _mm256_set1_epi64x(1LLU << 63);

    tmp = d01;
    
    d01 = _mm256_min_ps(d09, d01);
    
    d09 = _mm256_max_ps(d09, tmp);

    tmp = d02;
    
    d02 = _mm256_min_ps(d10, d02);
    
    d10 = _mm256_max_ps(d10, tmp);

    tmp = d03;
    
    d03 = _mm256_min_ps(d11, d03);
    
    d11 = _mm256_max_ps(d11, tmp);

    tmp = d04;
    
    d04 = _mm256_min_ps(d12, d04);
    
    d12 = _mm256_max_ps(d12, tmp);

    tmp = d05;
    
    d05 = _mm256_min_ps(d13, d05);
    
    d13 = _mm256_max_ps(d13, tmp);

    tmp = d06;
    
    d06 = _mm256_min_ps(d14, d06);
    
    d14 = _mm256_max_ps(d14, tmp);

    tmp = d07;
    
    d07 = _mm256_min_ps(d15, d07);
    
    d15 = _mm256_max_ps(d15, tmp);

    tmp = d08;
    
    d08 = _mm256_min_ps(d16, d08);
    
    d16 = _mm256_max_ps(d16, tmp);

    bitonic_sort_float_08v_merge_ascending(d01, d02, d03, d04, d05, d06, d07, d08);
    bitonic_sort_float_08v_merge_ascending(d09, d10, d11, d12, d13, d14, d15, d16);
}

static inline void bitonic_sort_float_16v_merge_descending(__m256& d01, __m256& d02, __m256& d03, __m256& d04, __m256& d05, __m256& d06, __m256& d07, __m256& d08, __m256& d09, __m256& d10, __m256& d11, __m256& d12, __m256& d13, __m256& d14, __m256& d15, __m256& d16) {
    __m256  tmp;
    __m256 topBit = _mm256_set1_epi64x(1LLU << 63);

    tmp = d01;
    
    d01 = _mm256_min_ps(d09, d01);
    
    d09 = _mm256_max_ps(d09, tmp);

    tmp = d02;
    
    d02 = _mm256_min_ps(d10, d02);
    
    d10 = _mm256_max_ps(d10, tmp);

    tmp = d03;
    
    d03 = _mm256_min_ps(d11, d03);
    
    d11 = _mm256_max_ps(d11, tmp);

    tmp = d04;
    
    d04 = _mm256_min_ps(d12, d04);
    
    d12 = _mm256_max_ps(d12, tmp);

    tmp = d05;
    
    d05 = _mm256_min_ps(d13, d05);
    
    d13 = _mm256_max_ps(d13, tmp);

    tmp = d06;
    
    d06 = _mm256_min_ps(d14, d06);
    
    d14 = _mm256_max_ps(d14, tmp);

    tmp = d07;
    
    d07 = _mm256_min_ps(d15, d07);
    
    d15 = _mm256_max_ps(d15, tmp);

    tmp = d08;
    
    d08 = _mm256_min_ps(d16, d08);
    
    d16 = _mm256_max_ps(d16, tmp);

    bitonic_sort_float_08v_merge_descending(d01, d02, d03, d04, d05, d06, d07, d08);
    bitonic_sort_float_08v_merge_descending(d09, d10, d11, d12, d13, d14, d15, d16);
}

static inline void bitonic_sort_float_17v_ascending(__m256& d01, __m256& d02, __m256& d03, __m256& d04, __m256& d05, __m256& d06, __m256& d07, __m256& d08, __m256& d09, __m256& d10, __m256& d11, __m256& d12, __m256& d13, __m256& d14, __m256& d15, __m256& d16, __m256& d17) {
    __m256  tmp;
    __m256 topBit = _mm256_set1_epi64x(1LLU << 63);

    bitonic_sort_float_16v_ascending(d01, d02, d03, d04, d05, d06, d07, d08, d09, d10, d11, d12, d13, d14, d15, d16);
    bitonic_sort_float_01v_descending(d17);

    tmp = d17;
    
    d17 = _mm256_max_ps(d16, d17);
    d16 = _mm256_min_ps(d16, tmp);

    bitonic_sort_float_16v_merge_ascending(d01, d02, d03, d04, d05, d06, d07, d08, d09, d10, d11, d12, d13, d14, d15, d16);
    bitonic_sort_float_01v_merge_ascending(d17);
}

static inline void bitonic_sort_float_17v_descending(__m256& d01, __m256& d02, __m256& d03, __m256& d04, __m256& d05, __m256& d06, __m256& d07, __m256& d08, __m256& d09, __m256& d10, __m256& d11, __m256& d12, __m256& d13, __m256& d14, __m256& d15, __m256& d16, __m256& d17) {
    __m256  tmp;
    __m256 topBit = _mm256_set1_epi64x(1LLU << 63);

    bitonic_sort_float_16v_descending(d01, d02, d03, d04, d05, d06, d07, d08, d09, d10, d11, d12, d13, d14, d15, d16);
    bitonic_sort_float_01v_ascending(d17);

    tmp = d17;
    
    d17 = _mm256_max_ps(d16, d17);
    d16 = _mm256_min_ps(d16, tmp);

    bitonic_sort_float_16v_merge_descending(d01, d02, d03, d04, d05, d06, d07, d08, d09, d10, d11, d12, d13, d14, d15, d16);
    bitonic_sort_float_01v_merge_descending(d17);
}

static inline void bitonic_sort_float_18v_ascending(__m256& d01, __m256& d02, __m256& d03, __m256& d04, __m256& d05, __m256& d06, __m256& d07, __m256& d08, __m256& d09, __m256& d10, __m256& d11, __m256& d12, __m256& d13, __m256& d14, __m256& d15, __m256& d16, __m256& d17, __m256& d18) {
    __m256  tmp;
    __m256 topBit = _mm256_set1_epi64x(1LLU << 63);

    bitonic_sort_float_16v_ascending(d01, d02, d03, d04, d05, d06, d07, d08, d09, d10, d11, d12, d13, d14, d15, d16);
    bitonic_sort_float_02v_descending(d17, d18);

    tmp = d17;
    
    d17 = _mm256_max_ps(d16, d17);
    d16 = _mm256_min_ps(d16, tmp);

    tmp = d18;
    
    d18 = _mm256_max_ps(d15, d18);
    d15 = _mm256_min_ps(d15, tmp);

    bitonic_sort_float_16v_merge_ascending(d01, d02, d03, d04, d05, d06, d07, d08, d09, d10, d11, d12, d13, d14, d15, d16);
    bitonic_sort_float_02v_merge_ascending(d17, d18);
}

static inline void bitonic_sort_float_18v_descending(__m256& d01, __m256& d02, __m256& d03, __m256& d04, __m256& d05, __m256& d06, __m256& d07, __m256& d08, __m256& d09, __m256& d10, __m256& d11, __m256& d12, __m256& d13, __m256& d14, __m256& d15, __m256& d16, __m256& d17, __m256& d18) {
    __m256  tmp;
    __m256 topBit = _mm256_set1_epi64x(1LLU << 63);

    bitonic_sort_float_16v_descending(d01, d02, d03, d04, d05, d06, d07, d08, d09, d10, d11, d12, d13, d14, d15, d16);
    bitonic_sort_float_02v_ascending(d17, d18);

    tmp = d17;
    
    d17 = _mm256_max_ps(d16, d17);
    d16 = _mm256_min_ps(d16, tmp);

    tmp = d18;
    
    d18 = _mm256_max_ps(d15, d18);
    d15 = _mm256_min_ps(d15, tmp);

    bitonic_sort_float_16v_merge_descending(d01, d02, d03, d04, d05, d06, d07, d08, d09, d10, d11, d12, d13, d14, d15, d16);
    bitonic_sort_float_02v_merge_descending(d17, d18);
}

static inline void bitonic_sort_float_19v_ascending(__m256& d01, __m256& d02, __m256& d03, __m256& d04, __m256& d05, __m256& d06, __m256& d07, __m256& d08, __m256& d09, __m256& d10, __m256& d11, __m256& d12, __m256& d13, __m256& d14, __m256& d15, __m256& d16, __m256& d17, __m256& d18, __m256& d19) {
    __m256  tmp;
    __m256 topBit = _mm256_set1_epi64x(1LLU << 63);

    bitonic_sort_float_16v_ascending(d01, d02, d03, d04, d05, d06, d07, d08, d09, d10, d11, d12, d13, d14, d15, d16);
    bitonic_sort_float_03v_descending(d17, d18, d19);

    tmp = d17;
    
    d17 = _mm256_max_ps(d16, d17);
    d16 = _mm256_min_ps(d16, tmp);

    tmp = d18;
    
    d18 = _mm256_max_ps(d15, d18);
    d15 = _mm256_min_ps(d15, tmp);

    tmp = d19;
    
    d19 = _mm256_max_ps(d14, d19);
    d14 = _mm256_min_ps(d14, tmp);

    bitonic_sort_float_16v_merge_ascending(d01, d02, d03, d04, d05, d06, d07, d08, d09, d10, d11, d12, d13, d14, d15, d16);
    bitonic_sort_float_03v_merge_ascending(d17, d18, d19);
}

static inline void bitonic_sort_float_19v_descending(__m256& d01, __m256& d02, __m256& d03, __m256& d04, __m256& d05, __m256& d06, __m256& d07, __m256& d08, __m256& d09, __m256& d10, __m256& d11, __m256& d12, __m256& d13, __m256& d14, __m256& d15, __m256& d16, __m256& d17, __m256& d18, __m256& d19) {
    __m256  tmp;
    __m256 topBit = _mm256_set1_epi64x(1LLU << 63);

    bitonic_sort_float_16v_descending(d01, d02, d03, d04, d05, d06, d07, d08, d09, d10, d11, d12, d13, d14, d15, d16);
    bitonic_sort_float_03v_ascending(d17, d18, d19);

    tmp = d17;
    
    d17 = _mm256_max_ps(d16, d17);
    d16 = _mm256_min_ps(d16, tmp);

    tmp = d18;
    
    d18 = _mm256_max_ps(d15, d18);
    d15 = _mm256_min_ps(d15, tmp);

    tmp = d19;
    
    d19 = _mm256_max_ps(d14, d19);
    d14 = _mm256_min_ps(d14, tmp);

    bitonic_sort_float_16v_merge_descending(d01, d02, d03, d04, d05, d06, d07, d08, d09, d10, d11, d12, d13, d14, d15, d16);
    bitonic_sort_float_03v_merge_descending(d17, d18, d19);
}

static inline void bitonic_sort_float_20v_ascending(__m256& d01, __m256& d02, __m256& d03, __m256& d04, __m256& d05, __m256& d06, __m256& d07, __m256& d08, __m256& d09, __m256& d10, __m256& d11, __m256& d12, __m256& d13, __m256& d14, __m256& d15, __m256& d16, __m256& d17, __m256& d18, __m256& d19, __m256& d20) {
    __m256  tmp;
    __m256 topBit = _mm256_set1_epi64x(1LLU << 63);

    bitonic_sort_float_16v_ascending(d01, d02, d03, d04, d05, d06, d07, d08, d09, d10, d11, d12, d13, d14, d15, d16);
    bitonic_sort_float_04v_descending(d17, d18, d19, d20);

    tmp = d17;
    
    d17 = _mm256_max_ps(d16, d17);
    d16 = _mm256_min_ps(d16, tmp);

    tmp = d18;
    
    d18 = _mm256_max_ps(d15, d18);
    d15 = _mm256_min_ps(d15, tmp);

    tmp = d19;
    
    d19 = _mm256_max_ps(d14, d19);
    d14 = _mm256_min_ps(d14, tmp);

    tmp = d20;
    
    d20 = _mm256_max_ps(d13, d20);
    d13 = _mm256_min_ps(d13, tmp);

    bitonic_sort_float_16v_merge_ascending(d01, d02, d03, d04, d05, d06, d07, d08, d09, d10, d11, d12, d13, d14, d15, d16);
    bitonic_sort_float_04v_merge_ascending(d17, d18, d19, d20);
}

static inline void bitonic_sort_float_20v_descending(__m256& d01, __m256& d02, __m256& d03, __m256& d04, __m256& d05, __m256& d06, __m256& d07, __m256& d08, __m256& d09, __m256& d10, __m256& d11, __m256& d12, __m256& d13, __m256& d14, __m256& d15, __m256& d16, __m256& d17, __m256& d18, __m256& d19, __m256& d20) {
    __m256  tmp;
    __m256 topBit = _mm256_set1_epi64x(1LLU << 63);

    bitonic_sort_float_16v_descending(d01, d02, d03, d04, d05, d06, d07, d08, d09, d10, d11, d12, d13, d14, d15, d16);
    bitonic_sort_float_04v_ascending(d17, d18, d19, d20);

    tmp = d17;
    
    d17 = _mm256_max_ps(d16, d17);
    d16 = _mm256_min_ps(d16, tmp);

    tmp = d18;
    
    d18 = _mm256_max_ps(d15, d18);
    d15 = _mm256_min_ps(d15, tmp);

    tmp = d19;
    
    d19 = _mm256_max_ps(d14, d19);
    d14 = _mm256_min_ps(d14, tmp);

    tmp = d20;
    
    d20 = _mm256_max_ps(d13, d20);
    d13 = _mm256_min_ps(d13, tmp);

    bitonic_sort_float_16v_merge_descending(d01, d02, d03, d04, d05, d06, d07, d08, d09, d10, d11, d12, d13, d14, d15, d16);
    bitonic_sort_float_04v_merge_descending(d17, d18, d19, d20);
}

static inline void bitonic_sort_float_21v_ascending(__m256& d01, __m256& d02, __m256& d03, __m256& d04, __m256& d05, __m256& d06, __m256& d07, __m256& d08, __m256& d09, __m256& d10, __m256& d11, __m256& d12, __m256& d13, __m256& d14, __m256& d15, __m256& d16, __m256& d17, __m256& d18, __m256& d19, __m256& d20, __m256& d21) {
    __m256  tmp;
    __m256 topBit = _mm256_set1_epi64x(1LLU << 63);

    bitonic_sort_float_16v_ascending(d01, d02, d03, d04, d05, d06, d07, d08, d09, d10, d11, d12, d13, d14, d15, d16);
    bitonic_sort_float_05v_descending(d17, d18, d19, d20, d21);

    tmp = d17;
    
    d17 = _mm256_max_ps(d16, d17);
    d16 = _mm256_min_ps(d16, tmp);

    tmp = d18;
    
    d18 = _mm256_max_ps(d15, d18);
    d15 = _mm256_min_ps(d15, tmp);

    tmp = d19;
    
    d19 = _mm256_max_ps(d14, d19);
    d14 = _mm256_min_ps(d14, tmp);

    tmp = d20;
    
    d20 = _mm256_max_ps(d13, d20);
    d13 = _mm256_min_ps(d13, tmp);

    tmp = d21;
    
    d21 = _mm256_max_ps(d12, d21);
    d12 = _mm256_min_ps(d12, tmp);

    bitonic_sort_float_16v_merge_ascending(d01, d02, d03, d04, d05, d06, d07, d08, d09, d10, d11, d12, d13, d14, d15, d16);
    bitonic_sort_float_05v_merge_ascending(d17, d18, d19, d20, d21);
}

static inline void bitonic_sort_float_21v_descending(__m256& d01, __m256& d02, __m256& d03, __m256& d04, __m256& d05, __m256& d06, __m256& d07, __m256& d08, __m256& d09, __m256& d10, __m256& d11, __m256& d12, __m256& d13, __m256& d14, __m256& d15, __m256& d16, __m256& d17, __m256& d18, __m256& d19, __m256& d20, __m256& d21) {
    __m256  tmp;
    __m256 topBit = _mm256_set1_epi64x(1LLU << 63);

    bitonic_sort_float_16v_descending(d01, d02, d03, d04, d05, d06, d07, d08, d09, d10, d11, d12, d13, d14, d15, d16);
    bitonic_sort_float_05v_ascending(d17, d18, d19, d20, d21);

    tmp = d17;
    
    d17 = _mm256_max_ps(d16, d17);
    d16 = _mm256_min_ps(d16, tmp);

    tmp = d18;
    
    d18 = _mm256_max_ps(d15, d18);
    d15 = _mm256_min_ps(d15, tmp);

    tmp = d19;
    
    d19 = _mm256_max_ps(d14, d19);
    d14 = _mm256_min_ps(d14, tmp);

    tmp = d20;
    
    d20 = _mm256_max_ps(d13, d20);
    d13 = _mm256_min_ps(d13, tmp);

    tmp = d21;
    
    d21 = _mm256_max_ps(d12, d21);
    d12 = _mm256_min_ps(d12, tmp);

    bitonic_sort_float_16v_merge_descending(d01, d02, d03, d04, d05, d06, d07, d08, d09, d10, d11, d12, d13, d14, d15, d16);
    bitonic_sort_float_05v_merge_descending(d17, d18, d19, d20, d21);
}

static inline void bitonic_sort_float_22v_ascending(__m256& d01, __m256& d02, __m256& d03, __m256& d04, __m256& d05, __m256& d06, __m256& d07, __m256& d08, __m256& d09, __m256& d10, __m256& d11, __m256& d12, __m256& d13, __m256& d14, __m256& d15, __m256& d16, __m256& d17, __m256& d18, __m256& d19, __m256& d20, __m256& d21, __m256& d22) {
    __m256  tmp;
    __m256 topBit = _mm256_set1_epi64x(1LLU << 63);

    bitonic_sort_float_16v_ascending(d01, d02, d03, d04, d05, d06, d07, d08, d09, d10, d11, d12, d13, d14, d15, d16);
    bitonic_sort_float_06v_descending(d17, d18, d19, d20, d21, d22);

    tmp = d17;
    
    d17 = _mm256_max_ps(d16, d17);
    d16 = _mm256_min_ps(d16, tmp);

    tmp = d18;
    
    d18 = _mm256_max_ps(d15, d18);
    d15 = _mm256_min_ps(d15, tmp);

    tmp = d19;
    
    d19 = _mm256_max_ps(d14, d19);
    d14 = _mm256_min_ps(d14, tmp);

    tmp = d20;
    
    d20 = _mm256_max_ps(d13, d20);
    d13 = _mm256_min_ps(d13, tmp);

    tmp = d21;
    
    d21 = _mm256_max_ps(d12, d21);
    d12 = _mm256_min_ps(d12, tmp);

    tmp = d22;
    
    d22 = _mm256_max_ps(d11, d22);
    d11 = _mm256_min_ps(d11, tmp);

    bitonic_sort_float_16v_merge_ascending(d01, d02, d03, d04, d05, d06, d07, d08, d09, d10, d11, d12, d13, d14, d15, d16);
    bitonic_sort_float_06v_merge_ascending(d17, d18, d19, d20, d21, d22);
}

static inline void bitonic_sort_float_22v_descending(__m256& d01, __m256& d02, __m256& d03, __m256& d04, __m256& d05, __m256& d06, __m256& d07, __m256& d08, __m256& d09, __m256& d10, __m256& d11, __m256& d12, __m256& d13, __m256& d14, __m256& d15, __m256& d16, __m256& d17, __m256& d18, __m256& d19, __m256& d20, __m256& d21, __m256& d22) {
    __m256  tmp;
    __m256 topBit = _mm256_set1_epi64x(1LLU << 63);

    bitonic_sort_float_16v_descending(d01, d02, d03, d04, d05, d06, d07, d08, d09, d10, d11, d12, d13, d14, d15, d16);
    bitonic_sort_float_06v_ascending(d17, d18, d19, d20, d21, d22);

    tmp = d17;
    
    d17 = _mm256_max_ps(d16, d17);
    d16 = _mm256_min_ps(d16, tmp);

    tmp = d18;
    
    d18 = _mm256_max_ps(d15, d18);
    d15 = _mm256_min_ps(d15, tmp);

    tmp = d19;
    
    d19 = _mm256_max_ps(d14, d19);
    d14 = _mm256_min_ps(d14, tmp);

    tmp = d20;
    
    d20 = _mm256_max_ps(d13, d20);
    d13 = _mm256_min_ps(d13, tmp);

    tmp = d21;
    
    d21 = _mm256_max_ps(d12, d21);
    d12 = _mm256_min_ps(d12, tmp);

    tmp = d22;
    
    d22 = _mm256_max_ps(d11, d22);
    d11 = _mm256_min_ps(d11, tmp);

    bitonic_sort_float_16v_merge_descending(d01, d02, d03, d04, d05, d06, d07, d08, d09, d10, d11, d12, d13, d14, d15, d16);
    bitonic_sort_float_06v_merge_descending(d17, d18, d19, d20, d21, d22);
}

static inline void bitonic_sort_float_23v_ascending(__m256& d01, __m256& d02, __m256& d03, __m256& d04, __m256& d05, __m256& d06, __m256& d07, __m256& d08, __m256& d09, __m256& d10, __m256& d11, __m256& d12, __m256& d13, __m256& d14, __m256& d15, __m256& d16, __m256& d17, __m256& d18, __m256& d19, __m256& d20, __m256& d21, __m256& d22, __m256& d23) {
    __m256  tmp;
    __m256 topBit = _mm256_set1_epi64x(1LLU << 63);

    bitonic_sort_float_16v_ascending(d01, d02, d03, d04, d05, d06, d07, d08, d09, d10, d11, d12, d13, d14, d15, d16);
    bitonic_sort_float_07v_descending(d17, d18, d19, d20, d21, d22, d23);

    tmp = d17;
    
    d17 = _mm256_max_ps(d16, d17);
    d16 = _mm256_min_ps(d16, tmp);

    tmp = d18;
    
    d18 = _mm256_max_ps(d15, d18);
    d15 = _mm256_min_ps(d15, tmp);

    tmp = d19;
    
    d19 = _mm256_max_ps(d14, d19);
    d14 = _mm256_min_ps(d14, tmp);

    tmp = d20;
    
    d20 = _mm256_max_ps(d13, d20);
    d13 = _mm256_min_ps(d13, tmp);

    tmp = d21;
    
    d21 = _mm256_max_ps(d12, d21);
    d12 = _mm256_min_ps(d12, tmp);

    tmp = d22;
    
    d22 = _mm256_max_ps(d11, d22);
    d11 = _mm256_min_ps(d11, tmp);

    tmp = d23;
    
    d23 = _mm256_max_ps(d10, d23);
    d10 = _mm256_min_ps(d10, tmp);

    bitonic_sort_float_16v_merge_ascending(d01, d02, d03, d04, d05, d06, d07, d08, d09, d10, d11, d12, d13, d14, d15, d16);
    bitonic_sort_float_07v_merge_ascending(d17, d18, d19, d20, d21, d22, d23);
}

static inline void bitonic_sort_float_23v_descending(__m256& d01, __m256& d02, __m256& d03, __m256& d04, __m256& d05, __m256& d06, __m256& d07, __m256& d08, __m256& d09, __m256& d10, __m256& d11, __m256& d12, __m256& d13, __m256& d14, __m256& d15, __m256& d16, __m256& d17, __m256& d18, __m256& d19, __m256& d20, __m256& d21, __m256& d22, __m256& d23) {
    __m256  tmp;
    __m256 topBit = _mm256_set1_epi64x(1LLU << 63);

    bitonic_sort_float_16v_descending(d01, d02, d03, d04, d05, d06, d07, d08, d09, d10, d11, d12, d13, d14, d15, d16);
    bitonic_sort_float_07v_ascending(d17, d18, d19, d20, d21, d22, d23);

    tmp = d17;
    
    d17 = _mm256_max_ps(d16, d17);
    d16 = _mm256_min_ps(d16, tmp);

    tmp = d18;
    
    d18 = _mm256_max_ps(d15, d18);
    d15 = _mm256_min_ps(d15, tmp);

    tmp = d19;
    
    d19 = _mm256_max_ps(d14, d19);
    d14 = _mm256_min_ps(d14, tmp);

    tmp = d20;
    
    d20 = _mm256_max_ps(d13, d20);
    d13 = _mm256_min_ps(d13, tmp);

    tmp = d21;
    
    d21 = _mm256_max_ps(d12, d21);
    d12 = _mm256_min_ps(d12, tmp);

    tmp = d22;
    
    d22 = _mm256_max_ps(d11, d22);
    d11 = _mm256_min_ps(d11, tmp);

    tmp = d23;
    
    d23 = _mm256_max_ps(d10, d23);
    d10 = _mm256_min_ps(d10, tmp);

    bitonic_sort_float_16v_merge_descending(d01, d02, d03, d04, d05, d06, d07, d08, d09, d10, d11, d12, d13, d14, d15, d16);
    bitonic_sort_float_07v_merge_descending(d17, d18, d19, d20, d21, d22, d23);
}

static inline void bitonic_sort_float_24v_ascending(__m256& d01, __m256& d02, __m256& d03, __m256& d04, __m256& d05, __m256& d06, __m256& d07, __m256& d08, __m256& d09, __m256& d10, __m256& d11, __m256& d12, __m256& d13, __m256& d14, __m256& d15, __m256& d16, __m256& d17, __m256& d18, __m256& d19, __m256& d20, __m256& d21, __m256& d22, __m256& d23, __m256& d24) {
    __m256  tmp;
    __m256 topBit = _mm256_set1_epi64x(1LLU << 63);

    bitonic_sort_float_16v_ascending(d01, d02, d03, d04, d05, d06, d07, d08, d09, d10, d11, d12, d13, d14, d15, d16);
    bitonic_sort_float_08v_descending(d17, d18, d19, d20, d21, d22, d23, d24);

    tmp = d17;
    
    d17 = _mm256_max_ps(d16, d17);
    d16 = _mm256_min_ps(d16, tmp);

    tmp = d18;
    
    d18 = _mm256_max_ps(d15, d18);
    d15 = _mm256_min_ps(d15, tmp);

    tmp = d19;
    
    d19 = _mm256_max_ps(d14, d19);
    d14 = _mm256_min_ps(d14, tmp);

    tmp = d20;
    
    d20 = _mm256_max_ps(d13, d20);
    d13 = _mm256_min_ps(d13, tmp);

    tmp = d21;
    
    d21 = _mm256_max_ps(d12, d21);
    d12 = _mm256_min_ps(d12, tmp);

    tmp = d22;
    
    d22 = _mm256_max_ps(d11, d22);
    d11 = _mm256_min_ps(d11, tmp);

    tmp = d23;
    
    d23 = _mm256_max_ps(d10, d23);
    d10 = _mm256_min_ps(d10, tmp);

    tmp = d24;
    
    d24 = _mm256_max_ps(d09, d24);
    d09 = _mm256_min_ps(d09, tmp);

    bitonic_sort_float_16v_merge_ascending(d01, d02, d03, d04, d05, d06, d07, d08, d09, d10, d11, d12, d13, d14, d15, d16);
    bitonic_sort_float_08v_merge_ascending(d17, d18, d19, d20, d21, d22, d23, d24);
}

static inline void bitonic_sort_float_24v_descending(__m256& d01, __m256& d02, __m256& d03, __m256& d04, __m256& d05, __m256& d06, __m256& d07, __m256& d08, __m256& d09, __m256& d10, __m256& d11, __m256& d12, __m256& d13, __m256& d14, __m256& d15, __m256& d16, __m256& d17, __m256& d18, __m256& d19, __m256& d20, __m256& d21, __m256& d22, __m256& d23, __m256& d24) {
    __m256  tmp;
    __m256 topBit = _mm256_set1_epi64x(1LLU << 63);

    bitonic_sort_float_16v_descending(d01, d02, d03, d04, d05, d06, d07, d08, d09, d10, d11, d12, d13, d14, d15, d16);
    bitonic_sort_float_08v_ascending(d17, d18, d19, d20, d21, d22, d23, d24);

    tmp = d17;
    
    d17 = _mm256_max_ps(d16, d17);
    d16 = _mm256_min_ps(d16, tmp);

    tmp = d18;
    
    d18 = _mm256_max_ps(d15, d18);
    d15 = _mm256_min_ps(d15, tmp);

    tmp = d19;
    
    d19 = _mm256_max_ps(d14, d19);
    d14 = _mm256_min_ps(d14, tmp);

    tmp = d20;
    
    d20 = _mm256_max_ps(d13, d20);
    d13 = _mm256_min_ps(d13, tmp);

    tmp = d21;
    
    d21 = _mm256_max_ps(d12, d21);
    d12 = _mm256_min_ps(d12, tmp);

    tmp = d22;
    
    d22 = _mm256_max_ps(d11, d22);
    d11 = _mm256_min_ps(d11, tmp);

    tmp = d23;
    
    d23 = _mm256_max_ps(d10, d23);
    d10 = _mm256_min_ps(d10, tmp);

    tmp = d24;
    
    d24 = _mm256_max_ps(d09, d24);
    d09 = _mm256_min_ps(d09, tmp);

    bitonic_sort_float_16v_merge_descending(d01, d02, d03, d04, d05, d06, d07, d08, d09, d10, d11, d12, d13, d14, d15, d16);
    bitonic_sort_float_08v_merge_descending(d17, d18, d19, d20, d21, d22, d23, d24);
}

static inline void bitonic_sort_float_25v_ascending(__m256& d01, __m256& d02, __m256& d03, __m256& d04, __m256& d05, __m256& d06, __m256& d07, __m256& d08, __m256& d09, __m256& d10, __m256& d11, __m256& d12, __m256& d13, __m256& d14, __m256& d15, __m256& d16, __m256& d17, __m256& d18, __m256& d19, __m256& d20, __m256& d21, __m256& d22, __m256& d23, __m256& d24, __m256& d25) {
    __m256  tmp;
    __m256 topBit = _mm256_set1_epi64x(1LLU << 63);

    bitonic_sort_float_16v_ascending(d01, d02, d03, d04, d05, d06, d07, d08, d09, d10, d11, d12, d13, d14, d15, d16);
    bitonic_sort_float_09v_descending(d17, d18, d19, d20, d21, d22, d23, d24, d25);

    tmp = d17;
    
    d17 = _mm256_max_ps(d16, d17);
    d16 = _mm256_min_ps(d16, tmp);

    tmp = d18;
    
    d18 = _mm256_max_ps(d15, d18);
    d15 = _mm256_min_ps(d15, tmp);

    tmp = d19;
    
    d19 = _mm256_max_ps(d14, d19);
    d14 = _mm256_min_ps(d14, tmp);

    tmp = d20;
    
    d20 = _mm256_max_ps(d13, d20);
    d13 = _mm256_min_ps(d13, tmp);

    tmp = d21;
    
    d21 = _mm256_max_ps(d12, d21);
    d12 = _mm256_min_ps(d12, tmp);

    tmp = d22;
    
    d22 = _mm256_max_ps(d11, d22);
    d11 = _mm256_min_ps(d11, tmp);

    tmp = d23;
    
    d23 = _mm256_max_ps(d10, d23);
    d10 = _mm256_min_ps(d10, tmp);

    tmp = d24;
    
    d24 = _mm256_max_ps(d09, d24);
    d09 = _mm256_min_ps(d09, tmp);

    tmp = d25;
    
    d25 = _mm256_max_ps(d08, d25);
    d08 = _mm256_min_ps(d08, tmp);

    bitonic_sort_float_16v_merge_ascending(d01, d02, d03, d04, d05, d06, d07, d08, d09, d10, d11, d12, d13, d14, d15, d16);
    bitonic_sort_float_09v_merge_ascending(d17, d18, d19, d20, d21, d22, d23, d24, d25);
}

static inline void bitonic_sort_float_25v_descending(__m256& d01, __m256& d02, __m256& d03, __m256& d04, __m256& d05, __m256& d06, __m256& d07, __m256& d08, __m256& d09, __m256& d10, __m256& d11, __m256& d12, __m256& d13, __m256& d14, __m256& d15, __m256& d16, __m256& d17, __m256& d18, __m256& d19, __m256& d20, __m256& d21, __m256& d22, __m256& d23, __m256& d24, __m256& d25) {
    __m256  tmp;
    __m256 topBit = _mm256_set1_epi64x(1LLU << 63);

    bitonic_sort_float_16v_descending(d01, d02, d03, d04, d05, d06, d07, d08, d09, d10, d11, d12, d13, d14, d15, d16);
    bitonic_sort_float_09v_ascending(d17, d18, d19, d20, d21, d22, d23, d24, d25);

    tmp = d17;
    
    d17 = _mm256_max_ps(d16, d17);
    d16 = _mm256_min_ps(d16, tmp);

    tmp = d18;
    
    d18 = _mm256_max_ps(d15, d18);
    d15 = _mm256_min_ps(d15, tmp);

    tmp = d19;
    
    d19 = _mm256_max_ps(d14, d19);
    d14 = _mm256_min_ps(d14, tmp);

    tmp = d20;
    
    d20 = _mm256_max_ps(d13, d20);
    d13 = _mm256_min_ps(d13, tmp);

    tmp = d21;
    
    d21 = _mm256_max_ps(d12, d21);
    d12 = _mm256_min_ps(d12, tmp);

    tmp = d22;
    
    d22 = _mm256_max_ps(d11, d22);
    d11 = _mm256_min_ps(d11, tmp);

    tmp = d23;
    
    d23 = _mm256_max_ps(d10, d23);
    d10 = _mm256_min_ps(d10, tmp);

    tmp = d24;
    
    d24 = _mm256_max_ps(d09, d24);
    d09 = _mm256_min_ps(d09, tmp);

    tmp = d25;
    
    d25 = _mm256_max_ps(d08, d25);
    d08 = _mm256_min_ps(d08, tmp);

    bitonic_sort_float_16v_merge_descending(d01, d02, d03, d04, d05, d06, d07, d08, d09, d10, d11, d12, d13, d14, d15, d16);
    bitonic_sort_float_09v_merge_descending(d17, d18, d19, d20, d21, d22, d23, d24, d25);
}

static inline void bitonic_sort_float_26v_ascending(__m256& d01, __m256& d02, __m256& d03, __m256& d04, __m256& d05, __m256& d06, __m256& d07, __m256& d08, __m256& d09, __m256& d10, __m256& d11, __m256& d12, __m256& d13, __m256& d14, __m256& d15, __m256& d16, __m256& d17, __m256& d18, __m256& d19, __m256& d20, __m256& d21, __m256& d22, __m256& d23, __m256& d24, __m256& d25, __m256& d26) {
    __m256  tmp;
    __m256 topBit = _mm256_set1_epi64x(1LLU << 63);

    bitonic_sort_float_16v_ascending(d01, d02, d03, d04, d05, d06, d07, d08, d09, d10, d11, d12, d13, d14, d15, d16);
    bitonic_sort_float_10v_descending(d17, d18, d19, d20, d21, d22, d23, d24, d25, d26);

    tmp = d17;
    
    d17 = _mm256_max_ps(d16, d17);
    d16 = _mm256_min_ps(d16, tmp);

    tmp = d18;
    
    d18 = _mm256_max_ps(d15, d18);
    d15 = _mm256_min_ps(d15, tmp);

    tmp = d19;
    
    d19 = _mm256_max_ps(d14, d19);
    d14 = _mm256_min_ps(d14, tmp);

    tmp = d20;
    
    d20 = _mm256_max_ps(d13, d20);
    d13 = _mm256_min_ps(d13, tmp);

    tmp = d21;
    
    d21 = _mm256_max_ps(d12, d21);
    d12 = _mm256_min_ps(d12, tmp);

    tmp = d22;
    
    d22 = _mm256_max_ps(d11, d22);
    d11 = _mm256_min_ps(d11, tmp);

    tmp = d23;
    
    d23 = _mm256_max_ps(d10, d23);
    d10 = _mm256_min_ps(d10, tmp);

    tmp = d24;
    
    d24 = _mm256_max_ps(d09, d24);
    d09 = _mm256_min_ps(d09, tmp);

    tmp = d25;
    
    d25 = _mm256_max_ps(d08, d25);
    d08 = _mm256_min_ps(d08, tmp);

    tmp = d26;
    
    d26 = _mm256_max_ps(d07, d26);
    d07 = _mm256_min_ps(d07, tmp);

    bitonic_sort_float_16v_merge_ascending(d01, d02, d03, d04, d05, d06, d07, d08, d09, d10, d11, d12, d13, d14, d15, d16);
    bitonic_sort_float_10v_merge_ascending(d17, d18, d19, d20, d21, d22, d23, d24, d25, d26);
}

static inline void bitonic_sort_float_26v_descending(__m256& d01, __m256& d02, __m256& d03, __m256& d04, __m256& d05, __m256& d06, __m256& d07, __m256& d08, __m256& d09, __m256& d10, __m256& d11, __m256& d12, __m256& d13, __m256& d14, __m256& d15, __m256& d16, __m256& d17, __m256& d18, __m256& d19, __m256& d20, __m256& d21, __m256& d22, __m256& d23, __m256& d24, __m256& d25, __m256& d26) {
    __m256  tmp;
    __m256 topBit = _mm256_set1_epi64x(1LLU << 63);

    bitonic_sort_float_16v_descending(d01, d02, d03, d04, d05, d06, d07, d08, d09, d10, d11, d12, d13, d14, d15, d16);
    bitonic_sort_float_10v_ascending(d17, d18, d19, d20, d21, d22, d23, d24, d25, d26);

    tmp = d17;
    
    d17 = _mm256_max_ps(d16, d17);
    d16 = _mm256_min_ps(d16, tmp);

    tmp = d18;
    
    d18 = _mm256_max_ps(d15, d18);
    d15 = _mm256_min_ps(d15, tmp);

    tmp = d19;
    
    d19 = _mm256_max_ps(d14, d19);
    d14 = _mm256_min_ps(d14, tmp);

    tmp = d20;
    
    d20 = _mm256_max_ps(d13, d20);
    d13 = _mm256_min_ps(d13, tmp);

    tmp = d21;
    
    d21 = _mm256_max_ps(d12, d21);
    d12 = _mm256_min_ps(d12, tmp);

    tmp = d22;
    
    d22 = _mm256_max_ps(d11, d22);
    d11 = _mm256_min_ps(d11, tmp);

    tmp = d23;
    
    d23 = _mm256_max_ps(d10, d23);
    d10 = _mm256_min_ps(d10, tmp);

    tmp = d24;
    
    d24 = _mm256_max_ps(d09, d24);
    d09 = _mm256_min_ps(d09, tmp);

    tmp = d25;
    
    d25 = _mm256_max_ps(d08, d25);
    d08 = _mm256_min_ps(d08, tmp);

    tmp = d26;
    
    d26 = _mm256_max_ps(d07, d26);
    d07 = _mm256_min_ps(d07, tmp);

    bitonic_sort_float_16v_merge_descending(d01, d02, d03, d04, d05, d06, d07, d08, d09, d10, d11, d12, d13, d14, d15, d16);
    bitonic_sort_float_10v_merge_descending(d17, d18, d19, d20, d21, d22, d23, d24, d25, d26);
}

static inline void bitonic_sort_float_27v_ascending(__m256& d01, __m256& d02, __m256& d03, __m256& d04, __m256& d05, __m256& d06, __m256& d07, __m256& d08, __m256& d09, __m256& d10, __m256& d11, __m256& d12, __m256& d13, __m256& d14, __m256& d15, __m256& d16, __m256& d17, __m256& d18, __m256& d19, __m256& d20, __m256& d21, __m256& d22, __m256& d23, __m256& d24, __m256& d25, __m256& d26, __m256& d27) {
    __m256  tmp;
    __m256 topBit = _mm256_set1_epi64x(1LLU << 63);

    bitonic_sort_float_16v_ascending(d01, d02, d03, d04, d05, d06, d07, d08, d09, d10, d11, d12, d13, d14, d15, d16);
    bitonic_sort_float_11v_descending(d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27);

    tmp = d17;
    
    d17 = _mm256_max_ps(d16, d17);
    d16 = _mm256_min_ps(d16, tmp);

    tmp = d18;
    
    d18 = _mm256_max_ps(d15, d18);
    d15 = _mm256_min_ps(d15, tmp);

    tmp = d19;
    
    d19 = _mm256_max_ps(d14, d19);
    d14 = _mm256_min_ps(d14, tmp);

    tmp = d20;
    
    d20 = _mm256_max_ps(d13, d20);
    d13 = _mm256_min_ps(d13, tmp);

    tmp = d21;
    
    d21 = _mm256_max_ps(d12, d21);
    d12 = _mm256_min_ps(d12, tmp);

    tmp = d22;
    
    d22 = _mm256_max_ps(d11, d22);
    d11 = _mm256_min_ps(d11, tmp);

    tmp = d23;
    
    d23 = _mm256_max_ps(d10, d23);
    d10 = _mm256_min_ps(d10, tmp);

    tmp = d24;
    
    d24 = _mm256_max_ps(d09, d24);
    d09 = _mm256_min_ps(d09, tmp);

    tmp = d25;
    
    d25 = _mm256_max_ps(d08, d25);
    d08 = _mm256_min_ps(d08, tmp);

    tmp = d26;
    
    d26 = _mm256_max_ps(d07, d26);
    d07 = _mm256_min_ps(d07, tmp);

    tmp = d27;
    
    d27 = _mm256_max_ps(d06, d27);
    d06 = _mm256_min_ps(d06, tmp);

    bitonic_sort_float_16v_merge_ascending(d01, d02, d03, d04, d05, d06, d07, d08, d09, d10, d11, d12, d13, d14, d15, d16);
    bitonic_sort_float_11v_merge_ascending(d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27);
}

static inline void bitonic_sort_float_27v_descending(__m256& d01, __m256& d02, __m256& d03, __m256& d04, __m256& d05, __m256& d06, __m256& d07, __m256& d08, __m256& d09, __m256& d10, __m256& d11, __m256& d12, __m256& d13, __m256& d14, __m256& d15, __m256& d16, __m256& d17, __m256& d18, __m256& d19, __m256& d20, __m256& d21, __m256& d22, __m256& d23, __m256& d24, __m256& d25, __m256& d26, __m256& d27) {
    __m256  tmp;
    __m256 topBit = _mm256_set1_epi64x(1LLU << 63);

    bitonic_sort_float_16v_descending(d01, d02, d03, d04, d05, d06, d07, d08, d09, d10, d11, d12, d13, d14, d15, d16);
    bitonic_sort_float_11v_ascending(d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27);

    tmp = d17;
    
    d17 = _mm256_max_ps(d16, d17);
    d16 = _mm256_min_ps(d16, tmp);

    tmp = d18;
    
    d18 = _mm256_max_ps(d15, d18);
    d15 = _mm256_min_ps(d15, tmp);

    tmp = d19;
    
    d19 = _mm256_max_ps(d14, d19);
    d14 = _mm256_min_ps(d14, tmp);

    tmp = d20;
    
    d20 = _mm256_max_ps(d13, d20);
    d13 = _mm256_min_ps(d13, tmp);

    tmp = d21;
    
    d21 = _mm256_max_ps(d12, d21);
    d12 = _mm256_min_ps(d12, tmp);

    tmp = d22;
    
    d22 = _mm256_max_ps(d11, d22);
    d11 = _mm256_min_ps(d11, tmp);

    tmp = d23;
    
    d23 = _mm256_max_ps(d10, d23);
    d10 = _mm256_min_ps(d10, tmp);

    tmp = d24;
    
    d24 = _mm256_max_ps(d09, d24);
    d09 = _mm256_min_ps(d09, tmp);

    tmp = d25;
    
    d25 = _mm256_max_ps(d08, d25);
    d08 = _mm256_min_ps(d08, tmp);

    tmp = d26;
    
    d26 = _mm256_max_ps(d07, d26);
    d07 = _mm256_min_ps(d07, tmp);

    tmp = d27;
    
    d27 = _mm256_max_ps(d06, d27);
    d06 = _mm256_min_ps(d06, tmp);

    bitonic_sort_float_16v_merge_descending(d01, d02, d03, d04, d05, d06, d07, d08, d09, d10, d11, d12, d13, d14, d15, d16);
    bitonic_sort_float_11v_merge_descending(d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27);
}

static inline void bitonic_sort_float_28v_ascending(__m256& d01, __m256& d02, __m256& d03, __m256& d04, __m256& d05, __m256& d06, __m256& d07, __m256& d08, __m256& d09, __m256& d10, __m256& d11, __m256& d12, __m256& d13, __m256& d14, __m256& d15, __m256& d16, __m256& d17, __m256& d18, __m256& d19, __m256& d20, __m256& d21, __m256& d22, __m256& d23, __m256& d24, __m256& d25, __m256& d26, __m256& d27, __m256& d28) {
    __m256  tmp;
    __m256 topBit = _mm256_set1_epi64x(1LLU << 63);

    bitonic_sort_float_16v_ascending(d01, d02, d03, d04, d05, d06, d07, d08, d09, d10, d11, d12, d13, d14, d15, d16);
    bitonic_sort_float_12v_descending(d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28);

    tmp = d17;
    
    d17 = _mm256_max_ps(d16, d17);
    d16 = _mm256_min_ps(d16, tmp);

    tmp = d18;
    
    d18 = _mm256_max_ps(d15, d18);
    d15 = _mm256_min_ps(d15, tmp);

    tmp = d19;
    
    d19 = _mm256_max_ps(d14, d19);
    d14 = _mm256_min_ps(d14, tmp);

    tmp = d20;
    
    d20 = _mm256_max_ps(d13, d20);
    d13 = _mm256_min_ps(d13, tmp);

    tmp = d21;
    
    d21 = _mm256_max_ps(d12, d21);
    d12 = _mm256_min_ps(d12, tmp);

    tmp = d22;
    
    d22 = _mm256_max_ps(d11, d22);
    d11 = _mm256_min_ps(d11, tmp);

    tmp = d23;
    
    d23 = _mm256_max_ps(d10, d23);
    d10 = _mm256_min_ps(d10, tmp);

    tmp = d24;
    
    d24 = _mm256_max_ps(d09, d24);
    d09 = _mm256_min_ps(d09, tmp);

    tmp = d25;
    
    d25 = _mm256_max_ps(d08, d25);
    d08 = _mm256_min_ps(d08, tmp);

    tmp = d26;
    
    d26 = _mm256_max_ps(d07, d26);
    d07 = _mm256_min_ps(d07, tmp);

    tmp = d27;
    
    d27 = _mm256_max_ps(d06, d27);
    d06 = _mm256_min_ps(d06, tmp);

    tmp = d28;
    
    d28 = _mm256_max_ps(d05, d28);
    d05 = _mm256_min_ps(d05, tmp);

    bitonic_sort_float_16v_merge_ascending(d01, d02, d03, d04, d05, d06, d07, d08, d09, d10, d11, d12, d13, d14, d15, d16);
    bitonic_sort_float_12v_merge_ascending(d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28);
}

static inline void bitonic_sort_float_28v_descending(__m256& d01, __m256& d02, __m256& d03, __m256& d04, __m256& d05, __m256& d06, __m256& d07, __m256& d08, __m256& d09, __m256& d10, __m256& d11, __m256& d12, __m256& d13, __m256& d14, __m256& d15, __m256& d16, __m256& d17, __m256& d18, __m256& d19, __m256& d20, __m256& d21, __m256& d22, __m256& d23, __m256& d24, __m256& d25, __m256& d26, __m256& d27, __m256& d28) {
    __m256  tmp;
    __m256 topBit = _mm256_set1_epi64x(1LLU << 63);

    bitonic_sort_float_16v_descending(d01, d02, d03, d04, d05, d06, d07, d08, d09, d10, d11, d12, d13, d14, d15, d16);
    bitonic_sort_float_12v_ascending(d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28);

    tmp = d17;
    
    d17 = _mm256_max_ps(d16, d17);
    d16 = _mm256_min_ps(d16, tmp);

    tmp = d18;
    
    d18 = _mm256_max_ps(d15, d18);
    d15 = _mm256_min_ps(d15, tmp);

    tmp = d19;
    
    d19 = _mm256_max_ps(d14, d19);
    d14 = _mm256_min_ps(d14, tmp);

    tmp = d20;
    
    d20 = _mm256_max_ps(d13, d20);
    d13 = _mm256_min_ps(d13, tmp);

    tmp = d21;
    
    d21 = _mm256_max_ps(d12, d21);
    d12 = _mm256_min_ps(d12, tmp);

    tmp = d22;
    
    d22 = _mm256_max_ps(d11, d22);
    d11 = _mm256_min_ps(d11, tmp);

    tmp = d23;
    
    d23 = _mm256_max_ps(d10, d23);
    d10 = _mm256_min_ps(d10, tmp);

    tmp = d24;
    
    d24 = _mm256_max_ps(d09, d24);
    d09 = _mm256_min_ps(d09, tmp);

    tmp = d25;
    
    d25 = _mm256_max_ps(d08, d25);
    d08 = _mm256_min_ps(d08, tmp);

    tmp = d26;
    
    d26 = _mm256_max_ps(d07, d26);
    d07 = _mm256_min_ps(d07, tmp);

    tmp = d27;
    
    d27 = _mm256_max_ps(d06, d27);
    d06 = _mm256_min_ps(d06, tmp);

    tmp = d28;
    
    d28 = _mm256_max_ps(d05, d28);
    d05 = _mm256_min_ps(d05, tmp);

    bitonic_sort_float_16v_merge_descending(d01, d02, d03, d04, d05, d06, d07, d08, d09, d10, d11, d12, d13, d14, d15, d16);
    bitonic_sort_float_12v_merge_descending(d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28);
}

static inline void bitonic_sort_float_29v_ascending(__m256& d01, __m256& d02, __m256& d03, __m256& d04, __m256& d05, __m256& d06, __m256& d07, __m256& d08, __m256& d09, __m256& d10, __m256& d11, __m256& d12, __m256& d13, __m256& d14, __m256& d15, __m256& d16, __m256& d17, __m256& d18, __m256& d19, __m256& d20, __m256& d21, __m256& d22, __m256& d23, __m256& d24, __m256& d25, __m256& d26, __m256& d27, __m256& d28, __m256& d29) {
    __m256  tmp;
    __m256 topBit = _mm256_set1_epi64x(1LLU << 63);

    bitonic_sort_float_16v_ascending(d01, d02, d03, d04, d05, d06, d07, d08, d09, d10, d11, d12, d13, d14, d15, d16);
    bitonic_sort_float_13v_descending(d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29);

    tmp = d17;
    
    d17 = _mm256_max_ps(d16, d17);
    d16 = _mm256_min_ps(d16, tmp);

    tmp = d18;
    
    d18 = _mm256_max_ps(d15, d18);
    d15 = _mm256_min_ps(d15, tmp);

    tmp = d19;
    
    d19 = _mm256_max_ps(d14, d19);
    d14 = _mm256_min_ps(d14, tmp);

    tmp = d20;
    
    d20 = _mm256_max_ps(d13, d20);
    d13 = _mm256_min_ps(d13, tmp);

    tmp = d21;
    
    d21 = _mm256_max_ps(d12, d21);
    d12 = _mm256_min_ps(d12, tmp);

    tmp = d22;
    
    d22 = _mm256_max_ps(d11, d22);
    d11 = _mm256_min_ps(d11, tmp);

    tmp = d23;
    
    d23 = _mm256_max_ps(d10, d23);
    d10 = _mm256_min_ps(d10, tmp);

    tmp = d24;
    
    d24 = _mm256_max_ps(d09, d24);
    d09 = _mm256_min_ps(d09, tmp);

    tmp = d25;
    
    d25 = _mm256_max_ps(d08, d25);
    d08 = _mm256_min_ps(d08, tmp);

    tmp = d26;
    
    d26 = _mm256_max_ps(d07, d26);
    d07 = _mm256_min_ps(d07, tmp);

    tmp = d27;
    
    d27 = _mm256_max_ps(d06, d27);
    d06 = _mm256_min_ps(d06, tmp);

    tmp = d28;
    
    d28 = _mm256_max_ps(d05, d28);
    d05 = _mm256_min_ps(d05, tmp);

    tmp = d29;
    
    d29 = _mm256_max_ps(d04, d29);
    d04 = _mm256_min_ps(d04, tmp);

    bitonic_sort_float_16v_merge_ascending(d01, d02, d03, d04, d05, d06, d07, d08, d09, d10, d11, d12, d13, d14, d15, d16);
    bitonic_sort_float_13v_merge_ascending(d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29);
}

static inline void bitonic_sort_float_29v_descending(__m256& d01, __m256& d02, __m256& d03, __m256& d04, __m256& d05, __m256& d06, __m256& d07, __m256& d08, __m256& d09, __m256& d10, __m256& d11, __m256& d12, __m256& d13, __m256& d14, __m256& d15, __m256& d16, __m256& d17, __m256& d18, __m256& d19, __m256& d20, __m256& d21, __m256& d22, __m256& d23, __m256& d24, __m256& d25, __m256& d26, __m256& d27, __m256& d28, __m256& d29) {
    __m256  tmp;
    __m256 topBit = _mm256_set1_epi64x(1LLU << 63);

    bitonic_sort_float_16v_descending(d01, d02, d03, d04, d05, d06, d07, d08, d09, d10, d11, d12, d13, d14, d15, d16);
    bitonic_sort_float_13v_ascending(d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29);

    tmp = d17;
    
    d17 = _mm256_max_ps(d16, d17);
    d16 = _mm256_min_ps(d16, tmp);

    tmp = d18;
    
    d18 = _mm256_max_ps(d15, d18);
    d15 = _mm256_min_ps(d15, tmp);

    tmp = d19;
    
    d19 = _mm256_max_ps(d14, d19);
    d14 = _mm256_min_ps(d14, tmp);

    tmp = d20;
    
    d20 = _mm256_max_ps(d13, d20);
    d13 = _mm256_min_ps(d13, tmp);

    tmp = d21;
    
    d21 = _mm256_max_ps(d12, d21);
    d12 = _mm256_min_ps(d12, tmp);

    tmp = d22;
    
    d22 = _mm256_max_ps(d11, d22);
    d11 = _mm256_min_ps(d11, tmp);

    tmp = d23;
    
    d23 = _mm256_max_ps(d10, d23);
    d10 = _mm256_min_ps(d10, tmp);

    tmp = d24;
    
    d24 = _mm256_max_ps(d09, d24);
    d09 = _mm256_min_ps(d09, tmp);

    tmp = d25;
    
    d25 = _mm256_max_ps(d08, d25);
    d08 = _mm256_min_ps(d08, tmp);

    tmp = d26;
    
    d26 = _mm256_max_ps(d07, d26);
    d07 = _mm256_min_ps(d07, tmp);

    tmp = d27;
    
    d27 = _mm256_max_ps(d06, d27);
    d06 = _mm256_min_ps(d06, tmp);

    tmp = d28;
    
    d28 = _mm256_max_ps(d05, d28);
    d05 = _mm256_min_ps(d05, tmp);

    tmp = d29;
    
    d29 = _mm256_max_ps(d04, d29);
    d04 = _mm256_min_ps(d04, tmp);

    bitonic_sort_float_16v_merge_descending(d01, d02, d03, d04, d05, d06, d07, d08, d09, d10, d11, d12, d13, d14, d15, d16);
    bitonic_sort_float_13v_merge_descending(d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29);
}

static inline void bitonic_sort_float_30v_ascending(__m256& d01, __m256& d02, __m256& d03, __m256& d04, __m256& d05, __m256& d06, __m256& d07, __m256& d08, __m256& d09, __m256& d10, __m256& d11, __m256& d12, __m256& d13, __m256& d14, __m256& d15, __m256& d16, __m256& d17, __m256& d18, __m256& d19, __m256& d20, __m256& d21, __m256& d22, __m256& d23, __m256& d24, __m256& d25, __m256& d26, __m256& d27, __m256& d28, __m256& d29, __m256& d30) {
    __m256  tmp;
    __m256 topBit = _mm256_set1_epi64x(1LLU << 63);

    bitonic_sort_float_16v_ascending(d01, d02, d03, d04, d05, d06, d07, d08, d09, d10, d11, d12, d13, d14, d15, d16);
    bitonic_sort_float_14v_descending(d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30);

    tmp = d17;
    
    d17 = _mm256_max_ps(d16, d17);
    d16 = _mm256_min_ps(d16, tmp);

    tmp = d18;
    
    d18 = _mm256_max_ps(d15, d18);
    d15 = _mm256_min_ps(d15, tmp);

    tmp = d19;
    
    d19 = _mm256_max_ps(d14, d19);
    d14 = _mm256_min_ps(d14, tmp);

    tmp = d20;
    
    d20 = _mm256_max_ps(d13, d20);
    d13 = _mm256_min_ps(d13, tmp);

    tmp = d21;
    
    d21 = _mm256_max_ps(d12, d21);
    d12 = _mm256_min_ps(d12, tmp);

    tmp = d22;
    
    d22 = _mm256_max_ps(d11, d22);
    d11 = _mm256_min_ps(d11, tmp);

    tmp = d23;
    
    d23 = _mm256_max_ps(d10, d23);
    d10 = _mm256_min_ps(d10, tmp);

    tmp = d24;
    
    d24 = _mm256_max_ps(d09, d24);
    d09 = _mm256_min_ps(d09, tmp);

    tmp = d25;
    
    d25 = _mm256_max_ps(d08, d25);
    d08 = _mm256_min_ps(d08, tmp);

    tmp = d26;
    
    d26 = _mm256_max_ps(d07, d26);
    d07 = _mm256_min_ps(d07, tmp);

    tmp = d27;
    
    d27 = _mm256_max_ps(d06, d27);
    d06 = _mm256_min_ps(d06, tmp);

    tmp = d28;
    
    d28 = _mm256_max_ps(d05, d28);
    d05 = _mm256_min_ps(d05, tmp);

    tmp = d29;
    
    d29 = _mm256_max_ps(d04, d29);
    d04 = _mm256_min_ps(d04, tmp);

    tmp = d30;
    
    d30 = _mm256_max_ps(d03, d30);
    d03 = _mm256_min_ps(d03, tmp);

    bitonic_sort_float_16v_merge_ascending(d01, d02, d03, d04, d05, d06, d07, d08, d09, d10, d11, d12, d13, d14, d15, d16);
    bitonic_sort_float_14v_merge_ascending(d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30);
}

static inline void bitonic_sort_float_30v_descending(__m256& d01, __m256& d02, __m256& d03, __m256& d04, __m256& d05, __m256& d06, __m256& d07, __m256& d08, __m256& d09, __m256& d10, __m256& d11, __m256& d12, __m256& d13, __m256& d14, __m256& d15, __m256& d16, __m256& d17, __m256& d18, __m256& d19, __m256& d20, __m256& d21, __m256& d22, __m256& d23, __m256& d24, __m256& d25, __m256& d26, __m256& d27, __m256& d28, __m256& d29, __m256& d30) {
    __m256  tmp;
    __m256 topBit = _mm256_set1_epi64x(1LLU << 63);

    bitonic_sort_float_16v_descending(d01, d02, d03, d04, d05, d06, d07, d08, d09, d10, d11, d12, d13, d14, d15, d16);
    bitonic_sort_float_14v_ascending(d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30);

    tmp = d17;
    
    d17 = _mm256_max_ps(d16, d17);
    d16 = _mm256_min_ps(d16, tmp);

    tmp = d18;
    
    d18 = _mm256_max_ps(d15, d18);
    d15 = _mm256_min_ps(d15, tmp);

    tmp = d19;
    
    d19 = _mm256_max_ps(d14, d19);
    d14 = _mm256_min_ps(d14, tmp);

    tmp = d20;
    
    d20 = _mm256_max_ps(d13, d20);
    d13 = _mm256_min_ps(d13, tmp);

    tmp = d21;
    
    d21 = _mm256_max_ps(d12, d21);
    d12 = _mm256_min_ps(d12, tmp);

    tmp = d22;
    
    d22 = _mm256_max_ps(d11, d22);
    d11 = _mm256_min_ps(d11, tmp);

    tmp = d23;
    
    d23 = _mm256_max_ps(d10, d23);
    d10 = _mm256_min_ps(d10, tmp);

    tmp = d24;
    
    d24 = _mm256_max_ps(d09, d24);
    d09 = _mm256_min_ps(d09, tmp);

    tmp = d25;
    
    d25 = _mm256_max_ps(d08, d25);
    d08 = _mm256_min_ps(d08, tmp);

    tmp = d26;
    
    d26 = _mm256_max_ps(d07, d26);
    d07 = _mm256_min_ps(d07, tmp);

    tmp = d27;
    
    d27 = _mm256_max_ps(d06, d27);
    d06 = _mm256_min_ps(d06, tmp);

    tmp = d28;
    
    d28 = _mm256_max_ps(d05, d28);
    d05 = _mm256_min_ps(d05, tmp);

    tmp = d29;
    
    d29 = _mm256_max_ps(d04, d29);
    d04 = _mm256_min_ps(d04, tmp);

    tmp = d30;
    
    d30 = _mm256_max_ps(d03, d30);
    d03 = _mm256_min_ps(d03, tmp);

    bitonic_sort_float_16v_merge_descending(d01, d02, d03, d04, d05, d06, d07, d08, d09, d10, d11, d12, d13, d14, d15, d16);
    bitonic_sort_float_14v_merge_descending(d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30);
}

static inline void bitonic_sort_float_31v_ascending(__m256& d01, __m256& d02, __m256& d03, __m256& d04, __m256& d05, __m256& d06, __m256& d07, __m256& d08, __m256& d09, __m256& d10, __m256& d11, __m256& d12, __m256& d13, __m256& d14, __m256& d15, __m256& d16, __m256& d17, __m256& d18, __m256& d19, __m256& d20, __m256& d21, __m256& d22, __m256& d23, __m256& d24, __m256& d25, __m256& d26, __m256& d27, __m256& d28, __m256& d29, __m256& d30, __m256& d31) {
    __m256  tmp;
    __m256 topBit = _mm256_set1_epi64x(1LLU << 63);

    bitonic_sort_float_16v_ascending(d01, d02, d03, d04, d05, d06, d07, d08, d09, d10, d11, d12, d13, d14, d15, d16);
    bitonic_sort_float_15v_descending(d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31);

    tmp = d17;
    
    d17 = _mm256_max_ps(d16, d17);
    d16 = _mm256_min_ps(d16, tmp);

    tmp = d18;
    
    d18 = _mm256_max_ps(d15, d18);
    d15 = _mm256_min_ps(d15, tmp);

    tmp = d19;
    
    d19 = _mm256_max_ps(d14, d19);
    d14 = _mm256_min_ps(d14, tmp);

    tmp = d20;
    
    d20 = _mm256_max_ps(d13, d20);
    d13 = _mm256_min_ps(d13, tmp);

    tmp = d21;
    
    d21 = _mm256_max_ps(d12, d21);
    d12 = _mm256_min_ps(d12, tmp);

    tmp = d22;
    
    d22 = _mm256_max_ps(d11, d22);
    d11 = _mm256_min_ps(d11, tmp);

    tmp = d23;
    
    d23 = _mm256_max_ps(d10, d23);
    d10 = _mm256_min_ps(d10, tmp);

    tmp = d24;
    
    d24 = _mm256_max_ps(d09, d24);
    d09 = _mm256_min_ps(d09, tmp);

    tmp = d25;
    
    d25 = _mm256_max_ps(d08, d25);
    d08 = _mm256_min_ps(d08, tmp);

    tmp = d26;
    
    d26 = _mm256_max_ps(d07, d26);
    d07 = _mm256_min_ps(d07, tmp);

    tmp = d27;
    
    d27 = _mm256_max_ps(d06, d27);
    d06 = _mm256_min_ps(d06, tmp);

    tmp = d28;
    
    d28 = _mm256_max_ps(d05, d28);
    d05 = _mm256_min_ps(d05, tmp);

    tmp = d29;
    
    d29 = _mm256_max_ps(d04, d29);
    d04 = _mm256_min_ps(d04, tmp);

    tmp = d30;
    
    d30 = _mm256_max_ps(d03, d30);
    d03 = _mm256_min_ps(d03, tmp);

    tmp = d31;
    
    d31 = _mm256_max_ps(d02, d31);
    d02 = _mm256_min_ps(d02, tmp);

    bitonic_sort_float_16v_merge_ascending(d01, d02, d03, d04, d05, d06, d07, d08, d09, d10, d11, d12, d13, d14, d15, d16);
    bitonic_sort_float_15v_merge_ascending(d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31);
}

static inline void bitonic_sort_float_31v_descending(__m256& d01, __m256& d02, __m256& d03, __m256& d04, __m256& d05, __m256& d06, __m256& d07, __m256& d08, __m256& d09, __m256& d10, __m256& d11, __m256& d12, __m256& d13, __m256& d14, __m256& d15, __m256& d16, __m256& d17, __m256& d18, __m256& d19, __m256& d20, __m256& d21, __m256& d22, __m256& d23, __m256& d24, __m256& d25, __m256& d26, __m256& d27, __m256& d28, __m256& d29, __m256& d30, __m256& d31) {
    __m256  tmp;
    __m256 topBit = _mm256_set1_epi64x(1LLU << 63);

    bitonic_sort_float_16v_descending(d01, d02, d03, d04, d05, d06, d07, d08, d09, d10, d11, d12, d13, d14, d15, d16);
    bitonic_sort_float_15v_ascending(d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31);

    tmp = d17;
    
    d17 = _mm256_max_ps(d16, d17);
    d16 = _mm256_min_ps(d16, tmp);

    tmp = d18;
    
    d18 = _mm256_max_ps(d15, d18);
    d15 = _mm256_min_ps(d15, tmp);

    tmp = d19;
    
    d19 = _mm256_max_ps(d14, d19);
    d14 = _mm256_min_ps(d14, tmp);

    tmp = d20;
    
    d20 = _mm256_max_ps(d13, d20);
    d13 = _mm256_min_ps(d13, tmp);

    tmp = d21;
    
    d21 = _mm256_max_ps(d12, d21);
    d12 = _mm256_min_ps(d12, tmp);

    tmp = d22;
    
    d22 = _mm256_max_ps(d11, d22);
    d11 = _mm256_min_ps(d11, tmp);

    tmp = d23;
    
    d23 = _mm256_max_ps(d10, d23);
    d10 = _mm256_min_ps(d10, tmp);

    tmp = d24;
    
    d24 = _mm256_max_ps(d09, d24);
    d09 = _mm256_min_ps(d09, tmp);

    tmp = d25;
    
    d25 = _mm256_max_ps(d08, d25);
    d08 = _mm256_min_ps(d08, tmp);

    tmp = d26;
    
    d26 = _mm256_max_ps(d07, d26);
    d07 = _mm256_min_ps(d07, tmp);

    tmp = d27;
    
    d27 = _mm256_max_ps(d06, d27);
    d06 = _mm256_min_ps(d06, tmp);

    tmp = d28;
    
    d28 = _mm256_max_ps(d05, d28);
    d05 = _mm256_min_ps(d05, tmp);

    tmp = d29;
    
    d29 = _mm256_max_ps(d04, d29);
    d04 = _mm256_min_ps(d04, tmp);

    tmp = d30;
    
    d30 = _mm256_max_ps(d03, d30);
    d03 = _mm256_min_ps(d03, tmp);

    tmp = d31;
    
    d31 = _mm256_max_ps(d02, d31);
    d02 = _mm256_min_ps(d02, tmp);

    bitonic_sort_float_16v_merge_descending(d01, d02, d03, d04, d05, d06, d07, d08, d09, d10, d11, d12, d13, d14, d15, d16);
    bitonic_sort_float_15v_merge_descending(d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31);
}

static inline void bitonic_sort_float_32v_ascending(__m256& d01, __m256& d02, __m256& d03, __m256& d04, __m256& d05, __m256& d06, __m256& d07, __m256& d08, __m256& d09, __m256& d10, __m256& d11, __m256& d12, __m256& d13, __m256& d14, __m256& d15, __m256& d16, __m256& d17, __m256& d18, __m256& d19, __m256& d20, __m256& d21, __m256& d22, __m256& d23, __m256& d24, __m256& d25, __m256& d26, __m256& d27, __m256& d28, __m256& d29, __m256& d30, __m256& d31, __m256& d32) {
    __m256  tmp;
    __m256 topBit = _mm256_set1_epi64x(1LLU << 63);

    bitonic_sort_float_16v_ascending(d01, d02, d03, d04, d05, d06, d07, d08, d09, d10, d11, d12, d13, d14, d15, d16);
    bitonic_sort_float_16v_descending(d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32);

    tmp = d17;
    
    d17 = _mm256_max_ps(d16, d17);
    d16 = _mm256_min_ps(d16, tmp);

    tmp = d18;
    
    d18 = _mm256_max_ps(d15, d18);
    d15 = _mm256_min_ps(d15, tmp);

    tmp = d19;
    
    d19 = _mm256_max_ps(d14, d19);
    d14 = _mm256_min_ps(d14, tmp);

    tmp = d20;
    
    d20 = _mm256_max_ps(d13, d20);
    d13 = _mm256_min_ps(d13, tmp);

    tmp = d21;
    
    d21 = _mm256_max_ps(d12, d21);
    d12 = _mm256_min_ps(d12, tmp);

    tmp = d22;
    
    d22 = _mm256_max_ps(d11, d22);
    d11 = _mm256_min_ps(d11, tmp);

    tmp = d23;
    
    d23 = _mm256_max_ps(d10, d23);
    d10 = _mm256_min_ps(d10, tmp);

    tmp = d24;
    
    d24 = _mm256_max_ps(d09, d24);
    d09 = _mm256_min_ps(d09, tmp);

    tmp = d25;
    
    d25 = _mm256_max_ps(d08, d25);
    d08 = _mm256_min_ps(d08, tmp);

    tmp = d26;
    
    d26 = _mm256_max_ps(d07, d26);
    d07 = _mm256_min_ps(d07, tmp);

    tmp = d27;
    
    d27 = _mm256_max_ps(d06, d27);
    d06 = _mm256_min_ps(d06, tmp);

    tmp = d28;
    
    d28 = _mm256_max_ps(d05, d28);
    d05 = _mm256_min_ps(d05, tmp);

    tmp = d29;
    
    d29 = _mm256_max_ps(d04, d29);
    d04 = _mm256_min_ps(d04, tmp);

    tmp = d30;
    
    d30 = _mm256_max_ps(d03, d30);
    d03 = _mm256_min_ps(d03, tmp);

    tmp = d31;
    
    d31 = _mm256_max_ps(d02, d31);
    d02 = _mm256_min_ps(d02, tmp);

    tmp = d32;
    
    d32 = _mm256_max_ps(d01, d32);
    d01 = _mm256_min_ps(d01, tmp);

    bitonic_sort_float_16v_merge_ascending(d01, d02, d03, d04, d05, d06, d07, d08, d09, d10, d11, d12, d13, d14, d15, d16);
    bitonic_sort_float_16v_merge_ascending(d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32);
}

static inline void bitonic_sort_float_32v_descending(__m256& d01, __m256& d02, __m256& d03, __m256& d04, __m256& d05, __m256& d06, __m256& d07, __m256& d08, __m256& d09, __m256& d10, __m256& d11, __m256& d12, __m256& d13, __m256& d14, __m256& d15, __m256& d16, __m256& d17, __m256& d18, __m256& d19, __m256& d20, __m256& d21, __m256& d22, __m256& d23, __m256& d24, __m256& d25, __m256& d26, __m256& d27, __m256& d28, __m256& d29, __m256& d30, __m256& d31, __m256& d32) {
    __m256  tmp;
    __m256 topBit = _mm256_set1_epi64x(1LLU << 63);

    bitonic_sort_float_16v_descending(d01, d02, d03, d04, d05, d06, d07, d08, d09, d10, d11, d12, d13, d14, d15, d16);
    bitonic_sort_float_16v_ascending(d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32);

    tmp = d17;
    
    d17 = _mm256_max_ps(d16, d17);
    d16 = _mm256_min_ps(d16, tmp);

    tmp = d18;
    
    d18 = _mm256_max_ps(d15, d18);
    d15 = _mm256_min_ps(d15, tmp);

    tmp = d19;
    
    d19 = _mm256_max_ps(d14, d19);
    d14 = _mm256_min_ps(d14, tmp);

    tmp = d20;
    
    d20 = _mm256_max_ps(d13, d20);
    d13 = _mm256_min_ps(d13, tmp);

    tmp = d21;
    
    d21 = _mm256_max_ps(d12, d21);
    d12 = _mm256_min_ps(d12, tmp);

    tmp = d22;
    
    d22 = _mm256_max_ps(d11, d22);
    d11 = _mm256_min_ps(d11, tmp);

    tmp = d23;
    
    d23 = _mm256_max_ps(d10, d23);
    d10 = _mm256_min_ps(d10, tmp);

    tmp = d24;
    
    d24 = _mm256_max_ps(d09, d24);
    d09 = _mm256_min_ps(d09, tmp);

    tmp = d25;
    
    d25 = _mm256_max_ps(d08, d25);
    d08 = _mm256_min_ps(d08, tmp);

    tmp = d26;
    
    d26 = _mm256_max_ps(d07, d26);
    d07 = _mm256_min_ps(d07, tmp);

    tmp = d27;
    
    d27 = _mm256_max_ps(d06, d27);
    d06 = _mm256_min_ps(d06, tmp);

    tmp = d28;
    
    d28 = _mm256_max_ps(d05, d28);
    d05 = _mm256_min_ps(d05, tmp);

    tmp = d29;
    
    d29 = _mm256_max_ps(d04, d29);
    d04 = _mm256_min_ps(d04, tmp);

    tmp = d30;
    
    d30 = _mm256_max_ps(d03, d30);
    d03 = _mm256_min_ps(d03, tmp);

    tmp = d31;
    
    d31 = _mm256_max_ps(d02, d31);
    d02 = _mm256_min_ps(d02, tmp);

    tmp = d32;
    
    d32 = _mm256_max_ps(d01, d32);
    d01 = _mm256_min_ps(d01, tmp);

    bitonic_sort_float_16v_merge_descending(d01, d02, d03, d04, d05, d06, d07, d08, d09, d10, d11, d12, d13, d14, d15, d16);
    bitonic_sort_float_16v_merge_descending(d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32);
}

static __attribute__((noinline)) void bitonic_sort_float_01v(float *ptr) {
    __m256 d01 = _mm256_loadu_ps((float const *) ptr + 0);
    bitonic_sort_float_01v_ascending(d01);
    _mm256_storeu_ps((float *) ptr + 0, d01);
}

static __attribute__((noinline)) void bitonic_sort_float_02v(float *ptr) {
    __m256 d01 = _mm256_loadu_ps((float const *) ptr + 0);
    __m256 d02 = _mm256_loadu_ps((float const *) ptr + 1);
    bitonic_sort_float_02v_ascending(d01, d02);
    _mm256_storeu_ps((float *) ptr + 0, d01);
    _mm256_storeu_ps((float *) ptr + 1, d02);
}

static __attribute__((noinline)) void bitonic_sort_float_03v(float *ptr) {
    __m256 d01 = _mm256_loadu_ps((float const *) ptr + 0);
    __m256 d02 = _mm256_loadu_ps((float const *) ptr + 1);
    __m256 d03 = _mm256_loadu_ps((float const *) ptr + 2);
    bitonic_sort_float_03v_ascending(d01, d02, d03);
    _mm256_storeu_ps((float *) ptr + 0, d01);
    _mm256_storeu_ps((float *) ptr + 1, d02);
    _mm256_storeu_ps((float *) ptr + 2, d03);
}

static __attribute__((noinline)) void bitonic_sort_float_04v(float *ptr) {
    __m256 d01 = _mm256_loadu_ps((float const *) ptr + 0);
    __m256 d02 = _mm256_loadu_ps((float const *) ptr + 1);
    __m256 d03 = _mm256_loadu_ps((float const *) ptr + 2);
    __m256 d04 = _mm256_loadu_ps((float const *) ptr + 3);
    bitonic_sort_float_04v_ascending(d01, d02, d03, d04);
    _mm256_storeu_ps((float *) ptr + 0, d01);
    _mm256_storeu_ps((float *) ptr + 1, d02);
    _mm256_storeu_ps((float *) ptr + 2, d03);
    _mm256_storeu_ps((float *) ptr + 3, d04);
}

static __attribute__((noinline)) void bitonic_sort_float_05v(float *ptr) {
    __m256 d01 = _mm256_loadu_ps((float const *) ptr + 0);
    __m256 d02 = _mm256_loadu_ps((float const *) ptr + 1);
    __m256 d03 = _mm256_loadu_ps((float const *) ptr + 2);
    __m256 d04 = _mm256_loadu_ps((float const *) ptr + 3);
    __m256 d05 = _mm256_loadu_ps((float const *) ptr + 4);
    bitonic_sort_float_05v_ascending(d01, d02, d03, d04, d05);
    _mm256_storeu_ps((float *) ptr + 0, d01);
    _mm256_storeu_ps((float *) ptr + 1, d02);
    _mm256_storeu_ps((float *) ptr + 2, d03);
    _mm256_storeu_ps((float *) ptr + 3, d04);
    _mm256_storeu_ps((float *) ptr + 4, d05);
}

static __attribute__((noinline)) void bitonic_sort_float_06v(float *ptr) {
    __m256 d01 = _mm256_loadu_ps((float const *) ptr + 0);
    __m256 d02 = _mm256_loadu_ps((float const *) ptr + 1);
    __m256 d03 = _mm256_loadu_ps((float const *) ptr + 2);
    __m256 d04 = _mm256_loadu_ps((float const *) ptr + 3);
    __m256 d05 = _mm256_loadu_ps((float const *) ptr + 4);
    __m256 d06 = _mm256_loadu_ps((float const *) ptr + 5);
    bitonic_sort_float_06v_ascending(d01, d02, d03, d04, d05, d06);
    _mm256_storeu_ps((float *) ptr + 0, d01);
    _mm256_storeu_ps((float *) ptr + 1, d02);
    _mm256_storeu_ps((float *) ptr + 2, d03);
    _mm256_storeu_ps((float *) ptr + 3, d04);
    _mm256_storeu_ps((float *) ptr + 4, d05);
    _mm256_storeu_ps((float *) ptr + 5, d06);
}

static __attribute__((noinline)) void bitonic_sort_float_07v(float *ptr) {
    __m256 d01 = _mm256_loadu_ps((float const *) ptr + 0);
    __m256 d02 = _mm256_loadu_ps((float const *) ptr + 1);
    __m256 d03 = _mm256_loadu_ps((float const *) ptr + 2);
    __m256 d04 = _mm256_loadu_ps((float const *) ptr + 3);
    __m256 d05 = _mm256_loadu_ps((float const *) ptr + 4);
    __m256 d06 = _mm256_loadu_ps((float const *) ptr + 5);
    __m256 d07 = _mm256_loadu_ps((float const *) ptr + 6);
    bitonic_sort_float_07v_ascending(d01, d02, d03, d04, d05, d06, d07);
    _mm256_storeu_ps((float *) ptr + 0, d01);
    _mm256_storeu_ps((float *) ptr + 1, d02);
    _mm256_storeu_ps((float *) ptr + 2, d03);
    _mm256_storeu_ps((float *) ptr + 3, d04);
    _mm256_storeu_ps((float *) ptr + 4, d05);
    _mm256_storeu_ps((float *) ptr + 5, d06);
    _mm256_storeu_ps((float *) ptr + 6, d07);
}

static __attribute__((noinline)) void bitonic_sort_float_08v(float *ptr) {
    __m256 d01 = _mm256_loadu_ps((float const *) ptr + 0);
    __m256 d02 = _mm256_loadu_ps((float const *) ptr + 1);
    __m256 d03 = _mm256_loadu_ps((float const *) ptr + 2);
    __m256 d04 = _mm256_loadu_ps((float const *) ptr + 3);
    __m256 d05 = _mm256_loadu_ps((float const *) ptr + 4);
    __m256 d06 = _mm256_loadu_ps((float const *) ptr + 5);
    __m256 d07 = _mm256_loadu_ps((float const *) ptr + 6);
    __m256 d08 = _mm256_loadu_ps((float const *) ptr + 7);
    bitonic_sort_float_08v_ascending(d01, d02, d03, d04, d05, d06, d07, d08);
    _mm256_storeu_ps((float *) ptr + 0, d01);
    _mm256_storeu_ps((float *) ptr + 1, d02);
    _mm256_storeu_ps((float *) ptr + 2, d03);
    _mm256_storeu_ps((float *) ptr + 3, d04);
    _mm256_storeu_ps((float *) ptr + 4, d05);
    _mm256_storeu_ps((float *) ptr + 5, d06);
    _mm256_storeu_ps((float *) ptr + 6, d07);
    _mm256_storeu_ps((float *) ptr + 7, d08);
}

static __attribute__((noinline)) void bitonic_sort_float_09v(float *ptr) {
    __m256 d01 = _mm256_loadu_ps((float const *) ptr + 0);
    __m256 d02 = _mm256_loadu_ps((float const *) ptr + 1);
    __m256 d03 = _mm256_loadu_ps((float const *) ptr + 2);
    __m256 d04 = _mm256_loadu_ps((float const *) ptr + 3);
    __m256 d05 = _mm256_loadu_ps((float const *) ptr + 4);
    __m256 d06 = _mm256_loadu_ps((float const *) ptr + 5);
    __m256 d07 = _mm256_loadu_ps((float const *) ptr + 6);
    __m256 d08 = _mm256_loadu_ps((float const *) ptr + 7);
    __m256 d09 = _mm256_loadu_ps((float const *) ptr + 8);
    bitonic_sort_float_09v_ascending(d01, d02, d03, d04, d05, d06, d07, d08, d09);
    _mm256_storeu_ps((float *) ptr + 0, d01);
    _mm256_storeu_ps((float *) ptr + 1, d02);
    _mm256_storeu_ps((float *) ptr + 2, d03);
    _mm256_storeu_ps((float *) ptr + 3, d04);
    _mm256_storeu_ps((float *) ptr + 4, d05);
    _mm256_storeu_ps((float *) ptr + 5, d06);
    _mm256_storeu_ps((float *) ptr + 6, d07);
    _mm256_storeu_ps((float *) ptr + 7, d08);
    _mm256_storeu_ps((float *) ptr + 8, d09);
}

static __attribute__((noinline)) void bitonic_sort_float_10v(float *ptr) {
    __m256 d01 = _mm256_loadu_ps((float const *) ptr + 0);
    __m256 d02 = _mm256_loadu_ps((float const *) ptr + 1);
    __m256 d03 = _mm256_loadu_ps((float const *) ptr + 2);
    __m256 d04 = _mm256_loadu_ps((float const *) ptr + 3);
    __m256 d05 = _mm256_loadu_ps((float const *) ptr + 4);
    __m256 d06 = _mm256_loadu_ps((float const *) ptr + 5);
    __m256 d07 = _mm256_loadu_ps((float const *) ptr + 6);
    __m256 d08 = _mm256_loadu_ps((float const *) ptr + 7);
    __m256 d09 = _mm256_loadu_ps((float const *) ptr + 8);
    __m256 d10 = _mm256_loadu_ps((float const *) ptr + 9);
    bitonic_sort_float_10v_ascending(d01, d02, d03, d04, d05, d06, d07, d08, d09, d10);
    _mm256_storeu_ps((float *) ptr + 0, d01);
    _mm256_storeu_ps((float *) ptr + 1, d02);
    _mm256_storeu_ps((float *) ptr + 2, d03);
    _mm256_storeu_ps((float *) ptr + 3, d04);
    _mm256_storeu_ps((float *) ptr + 4, d05);
    _mm256_storeu_ps((float *) ptr + 5, d06);
    _mm256_storeu_ps((float *) ptr + 6, d07);
    _mm256_storeu_ps((float *) ptr + 7, d08);
    _mm256_storeu_ps((float *) ptr + 8, d09);
    _mm256_storeu_ps((float *) ptr + 9, d10);
}

static __attribute__((noinline)) void bitonic_sort_float_11v(float *ptr) {
    __m256 d01 = _mm256_loadu_ps((float const *) ptr + 0);
    __m256 d02 = _mm256_loadu_ps((float const *) ptr + 1);
    __m256 d03 = _mm256_loadu_ps((float const *) ptr + 2);
    __m256 d04 = _mm256_loadu_ps((float const *) ptr + 3);
    __m256 d05 = _mm256_loadu_ps((float const *) ptr + 4);
    __m256 d06 = _mm256_loadu_ps((float const *) ptr + 5);
    __m256 d07 = _mm256_loadu_ps((float const *) ptr + 6);
    __m256 d08 = _mm256_loadu_ps((float const *) ptr + 7);
    __m256 d09 = _mm256_loadu_ps((float const *) ptr + 8);
    __m256 d10 = _mm256_loadu_ps((float const *) ptr + 9);
    __m256 d11 = _mm256_loadu_ps((float const *) ptr + 10);
    bitonic_sort_float_11v_ascending(d01, d02, d03, d04, d05, d06, d07, d08, d09, d10, d11);
    _mm256_storeu_ps((float *) ptr + 0, d01);
    _mm256_storeu_ps((float *) ptr + 1, d02);
    _mm256_storeu_ps((float *) ptr + 2, d03);
    _mm256_storeu_ps((float *) ptr + 3, d04);
    _mm256_storeu_ps((float *) ptr + 4, d05);
    _mm256_storeu_ps((float *) ptr + 5, d06);
    _mm256_storeu_ps((float *) ptr + 6, d07);
    _mm256_storeu_ps((float *) ptr + 7, d08);
    _mm256_storeu_ps((float *) ptr + 8, d09);
    _mm256_storeu_ps((float *) ptr + 9, d10);
    _mm256_storeu_ps((float *) ptr + 10, d11);
}

static __attribute__((noinline)) void bitonic_sort_float_12v(float *ptr) {
    __m256 d01 = _mm256_loadu_ps((float const *) ptr + 0);
    __m256 d02 = _mm256_loadu_ps((float const *) ptr + 1);
    __m256 d03 = _mm256_loadu_ps((float const *) ptr + 2);
    __m256 d04 = _mm256_loadu_ps((float const *) ptr + 3);
    __m256 d05 = _mm256_loadu_ps((float const *) ptr + 4);
    __m256 d06 = _mm256_loadu_ps((float const *) ptr + 5);
    __m256 d07 = _mm256_loadu_ps((float const *) ptr + 6);
    __m256 d08 = _mm256_loadu_ps((float const *) ptr + 7);
    __m256 d09 = _mm256_loadu_ps((float const *) ptr + 8);
    __m256 d10 = _mm256_loadu_ps((float const *) ptr + 9);
    __m256 d11 = _mm256_loadu_ps((float const *) ptr + 10);
    __m256 d12 = _mm256_loadu_ps((float const *) ptr + 11);
    bitonic_sort_float_12v_ascending(d01, d02, d03, d04, d05, d06, d07, d08, d09, d10, d11, d12);
    _mm256_storeu_ps((float *) ptr + 0, d01);
    _mm256_storeu_ps((float *) ptr + 1, d02);
    _mm256_storeu_ps((float *) ptr + 2, d03);
    _mm256_storeu_ps((float *) ptr + 3, d04);
    _mm256_storeu_ps((float *) ptr + 4, d05);
    _mm256_storeu_ps((float *) ptr + 5, d06);
    _mm256_storeu_ps((float *) ptr + 6, d07);
    _mm256_storeu_ps((float *) ptr + 7, d08);
    _mm256_storeu_ps((float *) ptr + 8, d09);
    _mm256_storeu_ps((float *) ptr + 9, d10);
    _mm256_storeu_ps((float *) ptr + 10, d11);
    _mm256_storeu_ps((float *) ptr + 11, d12);
}

static __attribute__((noinline)) void bitonic_sort_float_13v(float *ptr) {
    __m256 d01 = _mm256_loadu_ps((float const *) ptr + 0);
    __m256 d02 = _mm256_loadu_ps((float const *) ptr + 1);
    __m256 d03 = _mm256_loadu_ps((float const *) ptr + 2);
    __m256 d04 = _mm256_loadu_ps((float const *) ptr + 3);
    __m256 d05 = _mm256_loadu_ps((float const *) ptr + 4);
    __m256 d06 = _mm256_loadu_ps((float const *) ptr + 5);
    __m256 d07 = _mm256_loadu_ps((float const *) ptr + 6);
    __m256 d08 = _mm256_loadu_ps((float const *) ptr + 7);
    __m256 d09 = _mm256_loadu_ps((float const *) ptr + 8);
    __m256 d10 = _mm256_loadu_ps((float const *) ptr + 9);
    __m256 d11 = _mm256_loadu_ps((float const *) ptr + 10);
    __m256 d12 = _mm256_loadu_ps((float const *) ptr + 11);
    __m256 d13 = _mm256_loadu_ps((float const *) ptr + 12);
    bitonic_sort_float_13v_ascending(d01, d02, d03, d04, d05, d06, d07, d08, d09, d10, d11, d12, d13);
    _mm256_storeu_ps((float *) ptr + 0, d01);
    _mm256_storeu_ps((float *) ptr + 1, d02);
    _mm256_storeu_ps((float *) ptr + 2, d03);
    _mm256_storeu_ps((float *) ptr + 3, d04);
    _mm256_storeu_ps((float *) ptr + 4, d05);
    _mm256_storeu_ps((float *) ptr + 5, d06);
    _mm256_storeu_ps((float *) ptr + 6, d07);
    _mm256_storeu_ps((float *) ptr + 7, d08);
    _mm256_storeu_ps((float *) ptr + 8, d09);
    _mm256_storeu_ps((float *) ptr + 9, d10);
    _mm256_storeu_ps((float *) ptr + 10, d11);
    _mm256_storeu_ps((float *) ptr + 11, d12);
    _mm256_storeu_ps((float *) ptr + 12, d13);
}

static __attribute__((noinline)) void bitonic_sort_float_14v(float *ptr) {
    __m256 d01 = _mm256_loadu_ps((float const *) ptr + 0);
    __m256 d02 = _mm256_loadu_ps((float const *) ptr + 1);
    __m256 d03 = _mm256_loadu_ps((float const *) ptr + 2);
    __m256 d04 = _mm256_loadu_ps((float const *) ptr + 3);
    __m256 d05 = _mm256_loadu_ps((float const *) ptr + 4);
    __m256 d06 = _mm256_loadu_ps((float const *) ptr + 5);
    __m256 d07 = _mm256_loadu_ps((float const *) ptr + 6);
    __m256 d08 = _mm256_loadu_ps((float const *) ptr + 7);
    __m256 d09 = _mm256_loadu_ps((float const *) ptr + 8);
    __m256 d10 = _mm256_loadu_ps((float const *) ptr + 9);
    __m256 d11 = _mm256_loadu_ps((float const *) ptr + 10);
    __m256 d12 = _mm256_loadu_ps((float const *) ptr + 11);
    __m256 d13 = _mm256_loadu_ps((float const *) ptr + 12);
    __m256 d14 = _mm256_loadu_ps((float const *) ptr + 13);
    bitonic_sort_float_14v_ascending(d01, d02, d03, d04, d05, d06, d07, d08, d09, d10, d11, d12, d13, d14);
    _mm256_storeu_ps((float *) ptr + 0, d01);
    _mm256_storeu_ps((float *) ptr + 1, d02);
    _mm256_storeu_ps((float *) ptr + 2, d03);
    _mm256_storeu_ps((float *) ptr + 3, d04);
    _mm256_storeu_ps((float *) ptr + 4, d05);
    _mm256_storeu_ps((float *) ptr + 5, d06);
    _mm256_storeu_ps((float *) ptr + 6, d07);
    _mm256_storeu_ps((float *) ptr + 7, d08);
    _mm256_storeu_ps((float *) ptr + 8, d09);
    _mm256_storeu_ps((float *) ptr + 9, d10);
    _mm256_storeu_ps((float *) ptr + 10, d11);
    _mm256_storeu_ps((float *) ptr + 11, d12);
    _mm256_storeu_ps((float *) ptr + 12, d13);
    _mm256_storeu_ps((float *) ptr + 13, d14);
}

static __attribute__((noinline)) void bitonic_sort_float_15v(float *ptr) {
    __m256 d01 = _mm256_loadu_ps((float const *) ptr + 0);
    __m256 d02 = _mm256_loadu_ps((float const *) ptr + 1);
    __m256 d03 = _mm256_loadu_ps((float const *) ptr + 2);
    __m256 d04 = _mm256_loadu_ps((float const *) ptr + 3);
    __m256 d05 = _mm256_loadu_ps((float const *) ptr + 4);
    __m256 d06 = _mm256_loadu_ps((float const *) ptr + 5);
    __m256 d07 = _mm256_loadu_ps((float const *) ptr + 6);
    __m256 d08 = _mm256_loadu_ps((float const *) ptr + 7);
    __m256 d09 = _mm256_loadu_ps((float const *) ptr + 8);
    __m256 d10 = _mm256_loadu_ps((float const *) ptr + 9);
    __m256 d11 = _mm256_loadu_ps((float const *) ptr + 10);
    __m256 d12 = _mm256_loadu_ps((float const *) ptr + 11);
    __m256 d13 = _mm256_loadu_ps((float const *) ptr + 12);
    __m256 d14 = _mm256_loadu_ps((float const *) ptr + 13);
    __m256 d15 = _mm256_loadu_ps((float const *) ptr + 14);
    bitonic_sort_float_15v_ascending(d01, d02, d03, d04, d05, d06, d07, d08, d09, d10, d11, d12, d13, d14, d15);
    _mm256_storeu_ps((float *) ptr + 0, d01);
    _mm256_storeu_ps((float *) ptr + 1, d02);
    _mm256_storeu_ps((float *) ptr + 2, d03);
    _mm256_storeu_ps((float *) ptr + 3, d04);
    _mm256_storeu_ps((float *) ptr + 4, d05);
    _mm256_storeu_ps((float *) ptr + 5, d06);
    _mm256_storeu_ps((float *) ptr + 6, d07);
    _mm256_storeu_ps((float *) ptr + 7, d08);
    _mm256_storeu_ps((float *) ptr + 8, d09);
    _mm256_storeu_ps((float *) ptr + 9, d10);
    _mm256_storeu_ps((float *) ptr + 10, d11);
    _mm256_storeu_ps((float *) ptr + 11, d12);
    _mm256_storeu_ps((float *) ptr + 12, d13);
    _mm256_storeu_ps((float *) ptr + 13, d14);
    _mm256_storeu_ps((float *) ptr + 14, d15);
}

static __attribute__((noinline)) void bitonic_sort_float_16v(float *ptr) {
    __m256 d01 = _mm256_loadu_ps((float const *) ptr + 0);
    __m256 d02 = _mm256_loadu_ps((float const *) ptr + 1);
    __m256 d03 = _mm256_loadu_ps((float const *) ptr + 2);
    __m256 d04 = _mm256_loadu_ps((float const *) ptr + 3);
    __m256 d05 = _mm256_loadu_ps((float const *) ptr + 4);
    __m256 d06 = _mm256_loadu_ps((float const *) ptr + 5);
    __m256 d07 = _mm256_loadu_ps((float const *) ptr + 6);
    __m256 d08 = _mm256_loadu_ps((float const *) ptr + 7);
    __m256 d09 = _mm256_loadu_ps((float const *) ptr + 8);
    __m256 d10 = _mm256_loadu_ps((float const *) ptr + 9);
    __m256 d11 = _mm256_loadu_ps((float const *) ptr + 10);
    __m256 d12 = _mm256_loadu_ps((float const *) ptr + 11);
    __m256 d13 = _mm256_loadu_ps((float const *) ptr + 12);
    __m256 d14 = _mm256_loadu_ps((float const *) ptr + 13);
    __m256 d15 = _mm256_loadu_ps((float const *) ptr + 14);
    __m256 d16 = _mm256_loadu_ps((float const *) ptr + 15);
    bitonic_sort_float_16v_ascending(d01, d02, d03, d04, d05, d06, d07, d08, d09, d10, d11, d12, d13, d14, d15, d16);
    _mm256_storeu_ps((float *) ptr + 0, d01);
    _mm256_storeu_ps((float *) ptr + 1, d02);
    _mm256_storeu_ps((float *) ptr + 2, d03);
    _mm256_storeu_ps((float *) ptr + 3, d04);
    _mm256_storeu_ps((float *) ptr + 4, d05);
    _mm256_storeu_ps((float *) ptr + 5, d06);
    _mm256_storeu_ps((float *) ptr + 6, d07);
    _mm256_storeu_ps((float *) ptr + 7, d08);
    _mm256_storeu_ps((float *) ptr + 8, d09);
    _mm256_storeu_ps((float *) ptr + 9, d10);
    _mm256_storeu_ps((float *) ptr + 10, d11);
    _mm256_storeu_ps((float *) ptr + 11, d12);
    _mm256_storeu_ps((float *) ptr + 12, d13);
    _mm256_storeu_ps((float *) ptr + 13, d14);
    _mm256_storeu_ps((float *) ptr + 14, d15);
    _mm256_storeu_ps((float *) ptr + 15, d16);
}

static __attribute__((noinline)) void bitonic_sort_float_17v(float *ptr) {
    __m256 d01 = _mm256_loadu_ps((float const *) ptr + 0);
    __m256 d02 = _mm256_loadu_ps((float const *) ptr + 1);
    __m256 d03 = _mm256_loadu_ps((float const *) ptr + 2);
    __m256 d04 = _mm256_loadu_ps((float const *) ptr + 3);
    __m256 d05 = _mm256_loadu_ps((float const *) ptr + 4);
    __m256 d06 = _mm256_loadu_ps((float const *) ptr + 5);
    __m256 d07 = _mm256_loadu_ps((float const *) ptr + 6);
    __m256 d08 = _mm256_loadu_ps((float const *) ptr + 7);
    __m256 d09 = _mm256_loadu_ps((float const *) ptr + 8);
    __m256 d10 = _mm256_loadu_ps((float const *) ptr + 9);
    __m256 d11 = _mm256_loadu_ps((float const *) ptr + 10);
    __m256 d12 = _mm256_loadu_ps((float const *) ptr + 11);
    __m256 d13 = _mm256_loadu_ps((float const *) ptr + 12);
    __m256 d14 = _mm256_loadu_ps((float const *) ptr + 13);
    __m256 d15 = _mm256_loadu_ps((float const *) ptr + 14);
    __m256 d16 = _mm256_loadu_ps((float const *) ptr + 15);
    __m256 d17 = _mm256_loadu_ps((float const *) ptr + 16);
    bitonic_sort_float_17v_ascending(d01, d02, d03, d04, d05, d06, d07, d08, d09, d10, d11, d12, d13, d14, d15, d16, d17);
    _mm256_storeu_ps((float *) ptr + 0, d01);
    _mm256_storeu_ps((float *) ptr + 1, d02);
    _mm256_storeu_ps((float *) ptr + 2, d03);
    _mm256_storeu_ps((float *) ptr + 3, d04);
    _mm256_storeu_ps((float *) ptr + 4, d05);
    _mm256_storeu_ps((float *) ptr + 5, d06);
    _mm256_storeu_ps((float *) ptr + 6, d07);
    _mm256_storeu_ps((float *) ptr + 7, d08);
    _mm256_storeu_ps((float *) ptr + 8, d09);
    _mm256_storeu_ps((float *) ptr + 9, d10);
    _mm256_storeu_ps((float *) ptr + 10, d11);
    _mm256_storeu_ps((float *) ptr + 11, d12);
    _mm256_storeu_ps((float *) ptr + 12, d13);
    _mm256_storeu_ps((float *) ptr + 13, d14);
    _mm256_storeu_ps((float *) ptr + 14, d15);
    _mm256_storeu_ps((float *) ptr + 15, d16);
    _mm256_storeu_ps((float *) ptr + 16, d17);
}

static __attribute__((noinline)) void bitonic_sort_float_18v(float *ptr) {
    __m256 d01 = _mm256_loadu_ps((float const *) ptr + 0);
    __m256 d02 = _mm256_loadu_ps((float const *) ptr + 1);
    __m256 d03 = _mm256_loadu_ps((float const *) ptr + 2);
    __m256 d04 = _mm256_loadu_ps((float const *) ptr + 3);
    __m256 d05 = _mm256_loadu_ps((float const *) ptr + 4);
    __m256 d06 = _mm256_loadu_ps((float const *) ptr + 5);
    __m256 d07 = _mm256_loadu_ps((float const *) ptr + 6);
    __m256 d08 = _mm256_loadu_ps((float const *) ptr + 7);
    __m256 d09 = _mm256_loadu_ps((float const *) ptr + 8);
    __m256 d10 = _mm256_loadu_ps((float const *) ptr + 9);
    __m256 d11 = _mm256_loadu_ps((float const *) ptr + 10);
    __m256 d12 = _mm256_loadu_ps((float const *) ptr + 11);
    __m256 d13 = _mm256_loadu_ps((float const *) ptr + 12);
    __m256 d14 = _mm256_loadu_ps((float const *) ptr + 13);
    __m256 d15 = _mm256_loadu_ps((float const *) ptr + 14);
    __m256 d16 = _mm256_loadu_ps((float const *) ptr + 15);
    __m256 d17 = _mm256_loadu_ps((float const *) ptr + 16);
    __m256 d18 = _mm256_loadu_ps((float const *) ptr + 17);
    bitonic_sort_float_18v_ascending(d01, d02, d03, d04, d05, d06, d07, d08, d09, d10, d11, d12, d13, d14, d15, d16, d17, d18);
    _mm256_storeu_ps((float *) ptr + 0, d01);
    _mm256_storeu_ps((float *) ptr + 1, d02);
    _mm256_storeu_ps((float *) ptr + 2, d03);
    _mm256_storeu_ps((float *) ptr + 3, d04);
    _mm256_storeu_ps((float *) ptr + 4, d05);
    _mm256_storeu_ps((float *) ptr + 5, d06);
    _mm256_storeu_ps((float *) ptr + 6, d07);
    _mm256_storeu_ps((float *) ptr + 7, d08);
    _mm256_storeu_ps((float *) ptr + 8, d09);
    _mm256_storeu_ps((float *) ptr + 9, d10);
    _mm256_storeu_ps((float *) ptr + 10, d11);
    _mm256_storeu_ps((float *) ptr + 11, d12);
    _mm256_storeu_ps((float *) ptr + 12, d13);
    _mm256_storeu_ps((float *) ptr + 13, d14);
    _mm256_storeu_ps((float *) ptr + 14, d15);
    _mm256_storeu_ps((float *) ptr + 15, d16);
    _mm256_storeu_ps((float *) ptr + 16, d17);
    _mm256_storeu_ps((float *) ptr + 17, d18);
}

static __attribute__((noinline)) void bitonic_sort_float_19v(float *ptr) {
    __m256 d01 = _mm256_loadu_ps((float const *) ptr + 0);
    __m256 d02 = _mm256_loadu_ps((float const *) ptr + 1);
    __m256 d03 = _mm256_loadu_ps((float const *) ptr + 2);
    __m256 d04 = _mm256_loadu_ps((float const *) ptr + 3);
    __m256 d05 = _mm256_loadu_ps((float const *) ptr + 4);
    __m256 d06 = _mm256_loadu_ps((float const *) ptr + 5);
    __m256 d07 = _mm256_loadu_ps((float const *) ptr + 6);
    __m256 d08 = _mm256_loadu_ps((float const *) ptr + 7);
    __m256 d09 = _mm256_loadu_ps((float const *) ptr + 8);
    __m256 d10 = _mm256_loadu_ps((float const *) ptr + 9);
    __m256 d11 = _mm256_loadu_ps((float const *) ptr + 10);
    __m256 d12 = _mm256_loadu_ps((float const *) ptr + 11);
    __m256 d13 = _mm256_loadu_ps((float const *) ptr + 12);
    __m256 d14 = _mm256_loadu_ps((float const *) ptr + 13);
    __m256 d15 = _mm256_loadu_ps((float const *) ptr + 14);
    __m256 d16 = _mm256_loadu_ps((float const *) ptr + 15);
    __m256 d17 = _mm256_loadu_ps((float const *) ptr + 16);
    __m256 d18 = _mm256_loadu_ps((float const *) ptr + 17);
    __m256 d19 = _mm256_loadu_ps((float const *) ptr + 18);
    bitonic_sort_float_19v_ascending(d01, d02, d03, d04, d05, d06, d07, d08, d09, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19);
    _mm256_storeu_ps((float *) ptr + 0, d01);
    _mm256_storeu_ps((float *) ptr + 1, d02);
    _mm256_storeu_ps((float *) ptr + 2, d03);
    _mm256_storeu_ps((float *) ptr + 3, d04);
    _mm256_storeu_ps((float *) ptr + 4, d05);
    _mm256_storeu_ps((float *) ptr + 5, d06);
    _mm256_storeu_ps((float *) ptr + 6, d07);
    _mm256_storeu_ps((float *) ptr + 7, d08);
    _mm256_storeu_ps((float *) ptr + 8, d09);
    _mm256_storeu_ps((float *) ptr + 9, d10);
    _mm256_storeu_ps((float *) ptr + 10, d11);
    _mm256_storeu_ps((float *) ptr + 11, d12);
    _mm256_storeu_ps((float *) ptr + 12, d13);
    _mm256_storeu_ps((float *) ptr + 13, d14);
    _mm256_storeu_ps((float *) ptr + 14, d15);
    _mm256_storeu_ps((float *) ptr + 15, d16);
    _mm256_storeu_ps((float *) ptr + 16, d17);
    _mm256_storeu_ps((float *) ptr + 17, d18);
    _mm256_storeu_ps((float *) ptr + 18, d19);
}

static __attribute__((noinline)) void bitonic_sort_float_20v(float *ptr) {
    __m256 d01 = _mm256_loadu_ps((float const *) ptr + 0);
    __m256 d02 = _mm256_loadu_ps((float const *) ptr + 1);
    __m256 d03 = _mm256_loadu_ps((float const *) ptr + 2);
    __m256 d04 = _mm256_loadu_ps((float const *) ptr + 3);
    __m256 d05 = _mm256_loadu_ps((float const *) ptr + 4);
    __m256 d06 = _mm256_loadu_ps((float const *) ptr + 5);
    __m256 d07 = _mm256_loadu_ps((float const *) ptr + 6);
    __m256 d08 = _mm256_loadu_ps((float const *) ptr + 7);
    __m256 d09 = _mm256_loadu_ps((float const *) ptr + 8);
    __m256 d10 = _mm256_loadu_ps((float const *) ptr + 9);
    __m256 d11 = _mm256_loadu_ps((float const *) ptr + 10);
    __m256 d12 = _mm256_loadu_ps((float const *) ptr + 11);
    __m256 d13 = _mm256_loadu_ps((float const *) ptr + 12);
    __m256 d14 = _mm256_loadu_ps((float const *) ptr + 13);
    __m256 d15 = _mm256_loadu_ps((float const *) ptr + 14);
    __m256 d16 = _mm256_loadu_ps((float const *) ptr + 15);
    __m256 d17 = _mm256_loadu_ps((float const *) ptr + 16);
    __m256 d18 = _mm256_loadu_ps((float const *) ptr + 17);
    __m256 d19 = _mm256_loadu_ps((float const *) ptr + 18);
    __m256 d20 = _mm256_loadu_ps((float const *) ptr + 19);
    bitonic_sort_float_20v_ascending(d01, d02, d03, d04, d05, d06, d07, d08, d09, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20);
    _mm256_storeu_ps((float *) ptr + 0, d01);
    _mm256_storeu_ps((float *) ptr + 1, d02);
    _mm256_storeu_ps((float *) ptr + 2, d03);
    _mm256_storeu_ps((float *) ptr + 3, d04);
    _mm256_storeu_ps((float *) ptr + 4, d05);
    _mm256_storeu_ps((float *) ptr + 5, d06);
    _mm256_storeu_ps((float *) ptr + 6, d07);
    _mm256_storeu_ps((float *) ptr + 7, d08);
    _mm256_storeu_ps((float *) ptr + 8, d09);
    _mm256_storeu_ps((float *) ptr + 9, d10);
    _mm256_storeu_ps((float *) ptr + 10, d11);
    _mm256_storeu_ps((float *) ptr + 11, d12);
    _mm256_storeu_ps((float *) ptr + 12, d13);
    _mm256_storeu_ps((float *) ptr + 13, d14);
    _mm256_storeu_ps((float *) ptr + 14, d15);
    _mm256_storeu_ps((float *) ptr + 15, d16);
    _mm256_storeu_ps((float *) ptr + 16, d17);
    _mm256_storeu_ps((float *) ptr + 17, d18);
    _mm256_storeu_ps((float *) ptr + 18, d19);
    _mm256_storeu_ps((float *) ptr + 19, d20);
}

static __attribute__((noinline)) void bitonic_sort_float_21v(float *ptr) {
    __m256 d01 = _mm256_loadu_ps((float const *) ptr + 0);
    __m256 d02 = _mm256_loadu_ps((float const *) ptr + 1);
    __m256 d03 = _mm256_loadu_ps((float const *) ptr + 2);
    __m256 d04 = _mm256_loadu_ps((float const *) ptr + 3);
    __m256 d05 = _mm256_loadu_ps((float const *) ptr + 4);
    __m256 d06 = _mm256_loadu_ps((float const *) ptr + 5);
    __m256 d07 = _mm256_loadu_ps((float const *) ptr + 6);
    __m256 d08 = _mm256_loadu_ps((float const *) ptr + 7);
    __m256 d09 = _mm256_loadu_ps((float const *) ptr + 8);
    __m256 d10 = _mm256_loadu_ps((float const *) ptr + 9);
    __m256 d11 = _mm256_loadu_ps((float const *) ptr + 10);
    __m256 d12 = _mm256_loadu_ps((float const *) ptr + 11);
    __m256 d13 = _mm256_loadu_ps((float const *) ptr + 12);
    __m256 d14 = _mm256_loadu_ps((float const *) ptr + 13);
    __m256 d15 = _mm256_loadu_ps((float const *) ptr + 14);
    __m256 d16 = _mm256_loadu_ps((float const *) ptr + 15);
    __m256 d17 = _mm256_loadu_ps((float const *) ptr + 16);
    __m256 d18 = _mm256_loadu_ps((float const *) ptr + 17);
    __m256 d19 = _mm256_loadu_ps((float const *) ptr + 18);
    __m256 d20 = _mm256_loadu_ps((float const *) ptr + 19);
    __m256 d21 = _mm256_loadu_ps((float const *) ptr + 20);
    bitonic_sort_float_21v_ascending(d01, d02, d03, d04, d05, d06, d07, d08, d09, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21);
    _mm256_storeu_ps((float *) ptr + 0, d01);
    _mm256_storeu_ps((float *) ptr + 1, d02);
    _mm256_storeu_ps((float *) ptr + 2, d03);
    _mm256_storeu_ps((float *) ptr + 3, d04);
    _mm256_storeu_ps((float *) ptr + 4, d05);
    _mm256_storeu_ps((float *) ptr + 5, d06);
    _mm256_storeu_ps((float *) ptr + 6, d07);
    _mm256_storeu_ps((float *) ptr + 7, d08);
    _mm256_storeu_ps((float *) ptr + 8, d09);
    _mm256_storeu_ps((float *) ptr + 9, d10);
    _mm256_storeu_ps((float *) ptr + 10, d11);
    _mm256_storeu_ps((float *) ptr + 11, d12);
    _mm256_storeu_ps((float *) ptr + 12, d13);
    _mm256_storeu_ps((float *) ptr + 13, d14);
    _mm256_storeu_ps((float *) ptr + 14, d15);
    _mm256_storeu_ps((float *) ptr + 15, d16);
    _mm256_storeu_ps((float *) ptr + 16, d17);
    _mm256_storeu_ps((float *) ptr + 17, d18);
    _mm256_storeu_ps((float *) ptr + 18, d19);
    _mm256_storeu_ps((float *) ptr + 19, d20);
    _mm256_storeu_ps((float *) ptr + 20, d21);
}

static __attribute__((noinline)) void bitonic_sort_float_22v(float *ptr) {
    __m256 d01 = _mm256_loadu_ps((float const *) ptr + 0);
    __m256 d02 = _mm256_loadu_ps((float const *) ptr + 1);
    __m256 d03 = _mm256_loadu_ps((float const *) ptr + 2);
    __m256 d04 = _mm256_loadu_ps((float const *) ptr + 3);
    __m256 d05 = _mm256_loadu_ps((float const *) ptr + 4);
    __m256 d06 = _mm256_loadu_ps((float const *) ptr + 5);
    __m256 d07 = _mm256_loadu_ps((float const *) ptr + 6);
    __m256 d08 = _mm256_loadu_ps((float const *) ptr + 7);
    __m256 d09 = _mm256_loadu_ps((float const *) ptr + 8);
    __m256 d10 = _mm256_loadu_ps((float const *) ptr + 9);
    __m256 d11 = _mm256_loadu_ps((float const *) ptr + 10);
    __m256 d12 = _mm256_loadu_ps((float const *) ptr + 11);
    __m256 d13 = _mm256_loadu_ps((float const *) ptr + 12);
    __m256 d14 = _mm256_loadu_ps((float const *) ptr + 13);
    __m256 d15 = _mm256_loadu_ps((float const *) ptr + 14);
    __m256 d16 = _mm256_loadu_ps((float const *) ptr + 15);
    __m256 d17 = _mm256_loadu_ps((float const *) ptr + 16);
    __m256 d18 = _mm256_loadu_ps((float const *) ptr + 17);
    __m256 d19 = _mm256_loadu_ps((float const *) ptr + 18);
    __m256 d20 = _mm256_loadu_ps((float const *) ptr + 19);
    __m256 d21 = _mm256_loadu_ps((float const *) ptr + 20);
    __m256 d22 = _mm256_loadu_ps((float const *) ptr + 21);
    bitonic_sort_float_22v_ascending(d01, d02, d03, d04, d05, d06, d07, d08, d09, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22);
    _mm256_storeu_ps((float *) ptr + 0, d01);
    _mm256_storeu_ps((float *) ptr + 1, d02);
    _mm256_storeu_ps((float *) ptr + 2, d03);
    _mm256_storeu_ps((float *) ptr + 3, d04);
    _mm256_storeu_ps((float *) ptr + 4, d05);
    _mm256_storeu_ps((float *) ptr + 5, d06);
    _mm256_storeu_ps((float *) ptr + 6, d07);
    _mm256_storeu_ps((float *) ptr + 7, d08);
    _mm256_storeu_ps((float *) ptr + 8, d09);
    _mm256_storeu_ps((float *) ptr + 9, d10);
    _mm256_storeu_ps((float *) ptr + 10, d11);
    _mm256_storeu_ps((float *) ptr + 11, d12);
    _mm256_storeu_ps((float *) ptr + 12, d13);
    _mm256_storeu_ps((float *) ptr + 13, d14);
    _mm256_storeu_ps((float *) ptr + 14, d15);
    _mm256_storeu_ps((float *) ptr + 15, d16);
    _mm256_storeu_ps((float *) ptr + 16, d17);
    _mm256_storeu_ps((float *) ptr + 17, d18);
    _mm256_storeu_ps((float *) ptr + 18, d19);
    _mm256_storeu_ps((float *) ptr + 19, d20);
    _mm256_storeu_ps((float *) ptr + 20, d21);
    _mm256_storeu_ps((float *) ptr + 21, d22);
}

static __attribute__((noinline)) void bitonic_sort_float_23v(float *ptr) {
    __m256 d01 = _mm256_loadu_ps((float const *) ptr + 0);
    __m256 d02 = _mm256_loadu_ps((float const *) ptr + 1);
    __m256 d03 = _mm256_loadu_ps((float const *) ptr + 2);
    __m256 d04 = _mm256_loadu_ps((float const *) ptr + 3);
    __m256 d05 = _mm256_loadu_ps((float const *) ptr + 4);
    __m256 d06 = _mm256_loadu_ps((float const *) ptr + 5);
    __m256 d07 = _mm256_loadu_ps((float const *) ptr + 6);
    __m256 d08 = _mm256_loadu_ps((float const *) ptr + 7);
    __m256 d09 = _mm256_loadu_ps((float const *) ptr + 8);
    __m256 d10 = _mm256_loadu_ps((float const *) ptr + 9);
    __m256 d11 = _mm256_loadu_ps((float const *) ptr + 10);
    __m256 d12 = _mm256_loadu_ps((float const *) ptr + 11);
    __m256 d13 = _mm256_loadu_ps((float const *) ptr + 12);
    __m256 d14 = _mm256_loadu_ps((float const *) ptr + 13);
    __m256 d15 = _mm256_loadu_ps((float const *) ptr + 14);
    __m256 d16 = _mm256_loadu_ps((float const *) ptr + 15);
    __m256 d17 = _mm256_loadu_ps((float const *) ptr + 16);
    __m256 d18 = _mm256_loadu_ps((float const *) ptr + 17);
    __m256 d19 = _mm256_loadu_ps((float const *) ptr + 18);
    __m256 d20 = _mm256_loadu_ps((float const *) ptr + 19);
    __m256 d21 = _mm256_loadu_ps((float const *) ptr + 20);
    __m256 d22 = _mm256_loadu_ps((float const *) ptr + 21);
    __m256 d23 = _mm256_loadu_ps((float const *) ptr + 22);
    bitonic_sort_float_23v_ascending(d01, d02, d03, d04, d05, d06, d07, d08, d09, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23);
    _mm256_storeu_ps((float *) ptr + 0, d01);
    _mm256_storeu_ps((float *) ptr + 1, d02);
    _mm256_storeu_ps((float *) ptr + 2, d03);
    _mm256_storeu_ps((float *) ptr + 3, d04);
    _mm256_storeu_ps((float *) ptr + 4, d05);
    _mm256_storeu_ps((float *) ptr + 5, d06);
    _mm256_storeu_ps((float *) ptr + 6, d07);
    _mm256_storeu_ps((float *) ptr + 7, d08);
    _mm256_storeu_ps((float *) ptr + 8, d09);
    _mm256_storeu_ps((float *) ptr + 9, d10);
    _mm256_storeu_ps((float *) ptr + 10, d11);
    _mm256_storeu_ps((float *) ptr + 11, d12);
    _mm256_storeu_ps((float *) ptr + 12, d13);
    _mm256_storeu_ps((float *) ptr + 13, d14);
    _mm256_storeu_ps((float *) ptr + 14, d15);
    _mm256_storeu_ps((float *) ptr + 15, d16);
    _mm256_storeu_ps((float *) ptr + 16, d17);
    _mm256_storeu_ps((float *) ptr + 17, d18);
    _mm256_storeu_ps((float *) ptr + 18, d19);
    _mm256_storeu_ps((float *) ptr + 19, d20);
    _mm256_storeu_ps((float *) ptr + 20, d21);
    _mm256_storeu_ps((float *) ptr + 21, d22);
    _mm256_storeu_ps((float *) ptr + 22, d23);
}

static __attribute__((noinline)) void bitonic_sort_float_24v(float *ptr) {
    __m256 d01 = _mm256_loadu_ps((float const *) ptr + 0);
    __m256 d02 = _mm256_loadu_ps((float const *) ptr + 1);
    __m256 d03 = _mm256_loadu_ps((float const *) ptr + 2);
    __m256 d04 = _mm256_loadu_ps((float const *) ptr + 3);
    __m256 d05 = _mm256_loadu_ps((float const *) ptr + 4);
    __m256 d06 = _mm256_loadu_ps((float const *) ptr + 5);
    __m256 d07 = _mm256_loadu_ps((float const *) ptr + 6);
    __m256 d08 = _mm256_loadu_ps((float const *) ptr + 7);
    __m256 d09 = _mm256_loadu_ps((float const *) ptr + 8);
    __m256 d10 = _mm256_loadu_ps((float const *) ptr + 9);
    __m256 d11 = _mm256_loadu_ps((float const *) ptr + 10);
    __m256 d12 = _mm256_loadu_ps((float const *) ptr + 11);
    __m256 d13 = _mm256_loadu_ps((float const *) ptr + 12);
    __m256 d14 = _mm256_loadu_ps((float const *) ptr + 13);
    __m256 d15 = _mm256_loadu_ps((float const *) ptr + 14);
    __m256 d16 = _mm256_loadu_ps((float const *) ptr + 15);
    __m256 d17 = _mm256_loadu_ps((float const *) ptr + 16);
    __m256 d18 = _mm256_loadu_ps((float const *) ptr + 17);
    __m256 d19 = _mm256_loadu_ps((float const *) ptr + 18);
    __m256 d20 = _mm256_loadu_ps((float const *) ptr + 19);
    __m256 d21 = _mm256_loadu_ps((float const *) ptr + 20);
    __m256 d22 = _mm256_loadu_ps((float const *) ptr + 21);
    __m256 d23 = _mm256_loadu_ps((float const *) ptr + 22);
    __m256 d24 = _mm256_loadu_ps((float const *) ptr + 23);
    bitonic_sort_float_24v_ascending(d01, d02, d03, d04, d05, d06, d07, d08, d09, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24);
    _mm256_storeu_ps((float *) ptr + 0, d01);
    _mm256_storeu_ps((float *) ptr + 1, d02);
    _mm256_storeu_ps((float *) ptr + 2, d03);
    _mm256_storeu_ps((float *) ptr + 3, d04);
    _mm256_storeu_ps((float *) ptr + 4, d05);
    _mm256_storeu_ps((float *) ptr + 5, d06);
    _mm256_storeu_ps((float *) ptr + 6, d07);
    _mm256_storeu_ps((float *) ptr + 7, d08);
    _mm256_storeu_ps((float *) ptr + 8, d09);
    _mm256_storeu_ps((float *) ptr + 9, d10);
    _mm256_storeu_ps((float *) ptr + 10, d11);
    _mm256_storeu_ps((float *) ptr + 11, d12);
    _mm256_storeu_ps((float *) ptr + 12, d13);
    _mm256_storeu_ps((float *) ptr + 13, d14);
    _mm256_storeu_ps((float *) ptr + 14, d15);
    _mm256_storeu_ps((float *) ptr + 15, d16);
    _mm256_storeu_ps((float *) ptr + 16, d17);
    _mm256_storeu_ps((float *) ptr + 17, d18);
    _mm256_storeu_ps((float *) ptr + 18, d19);
    _mm256_storeu_ps((float *) ptr + 19, d20);
    _mm256_storeu_ps((float *) ptr + 20, d21);
    _mm256_storeu_ps((float *) ptr + 21, d22);
    _mm256_storeu_ps((float *) ptr + 22, d23);
    _mm256_storeu_ps((float *) ptr + 23, d24);
}

static __attribute__((noinline)) void bitonic_sort_float_25v(float *ptr) {
    __m256 d01 = _mm256_loadu_ps((float const *) ptr + 0);
    __m256 d02 = _mm256_loadu_ps((float const *) ptr + 1);
    __m256 d03 = _mm256_loadu_ps((float const *) ptr + 2);
    __m256 d04 = _mm256_loadu_ps((float const *) ptr + 3);
    __m256 d05 = _mm256_loadu_ps((float const *) ptr + 4);
    __m256 d06 = _mm256_loadu_ps((float const *) ptr + 5);
    __m256 d07 = _mm256_loadu_ps((float const *) ptr + 6);
    __m256 d08 = _mm256_loadu_ps((float const *) ptr + 7);
    __m256 d09 = _mm256_loadu_ps((float const *) ptr + 8);
    __m256 d10 = _mm256_loadu_ps((float const *) ptr + 9);
    __m256 d11 = _mm256_loadu_ps((float const *) ptr + 10);
    __m256 d12 = _mm256_loadu_ps((float const *) ptr + 11);
    __m256 d13 = _mm256_loadu_ps((float const *) ptr + 12);
    __m256 d14 = _mm256_loadu_ps((float const *) ptr + 13);
    __m256 d15 = _mm256_loadu_ps((float const *) ptr + 14);
    __m256 d16 = _mm256_loadu_ps((float const *) ptr + 15);
    __m256 d17 = _mm256_loadu_ps((float const *) ptr + 16);
    __m256 d18 = _mm256_loadu_ps((float const *) ptr + 17);
    __m256 d19 = _mm256_loadu_ps((float const *) ptr + 18);
    __m256 d20 = _mm256_loadu_ps((float const *) ptr + 19);
    __m256 d21 = _mm256_loadu_ps((float const *) ptr + 20);
    __m256 d22 = _mm256_loadu_ps((float const *) ptr + 21);
    __m256 d23 = _mm256_loadu_ps((float const *) ptr + 22);
    __m256 d24 = _mm256_loadu_ps((float const *) ptr + 23);
    __m256 d25 = _mm256_loadu_ps((float const *) ptr + 24);
    bitonic_sort_float_25v_ascending(d01, d02, d03, d04, d05, d06, d07, d08, d09, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25);
    _mm256_storeu_ps((float *) ptr + 0, d01);
    _mm256_storeu_ps((float *) ptr + 1, d02);
    _mm256_storeu_ps((float *) ptr + 2, d03);
    _mm256_storeu_ps((float *) ptr + 3, d04);
    _mm256_storeu_ps((float *) ptr + 4, d05);
    _mm256_storeu_ps((float *) ptr + 5, d06);
    _mm256_storeu_ps((float *) ptr + 6, d07);
    _mm256_storeu_ps((float *) ptr + 7, d08);
    _mm256_storeu_ps((float *) ptr + 8, d09);
    _mm256_storeu_ps((float *) ptr + 9, d10);
    _mm256_storeu_ps((float *) ptr + 10, d11);
    _mm256_storeu_ps((float *) ptr + 11, d12);
    _mm256_storeu_ps((float *) ptr + 12, d13);
    _mm256_storeu_ps((float *) ptr + 13, d14);
    _mm256_storeu_ps((float *) ptr + 14, d15);
    _mm256_storeu_ps((float *) ptr + 15, d16);
    _mm256_storeu_ps((float *) ptr + 16, d17);
    _mm256_storeu_ps((float *) ptr + 17, d18);
    _mm256_storeu_ps((float *) ptr + 18, d19);
    _mm256_storeu_ps((float *) ptr + 19, d20);
    _mm256_storeu_ps((float *) ptr + 20, d21);
    _mm256_storeu_ps((float *) ptr + 21, d22);
    _mm256_storeu_ps((float *) ptr + 22, d23);
    _mm256_storeu_ps((float *) ptr + 23, d24);
    _mm256_storeu_ps((float *) ptr + 24, d25);
}

static __attribute__((noinline)) void bitonic_sort_float_26v(float *ptr) {
    __m256 d01 = _mm256_loadu_ps((float const *) ptr + 0);
    __m256 d02 = _mm256_loadu_ps((float const *) ptr + 1);
    __m256 d03 = _mm256_loadu_ps((float const *) ptr + 2);
    __m256 d04 = _mm256_loadu_ps((float const *) ptr + 3);
    __m256 d05 = _mm256_loadu_ps((float const *) ptr + 4);
    __m256 d06 = _mm256_loadu_ps((float const *) ptr + 5);
    __m256 d07 = _mm256_loadu_ps((float const *) ptr + 6);
    __m256 d08 = _mm256_loadu_ps((float const *) ptr + 7);
    __m256 d09 = _mm256_loadu_ps((float const *) ptr + 8);
    __m256 d10 = _mm256_loadu_ps((float const *) ptr + 9);
    __m256 d11 = _mm256_loadu_ps((float const *) ptr + 10);
    __m256 d12 = _mm256_loadu_ps((float const *) ptr + 11);
    __m256 d13 = _mm256_loadu_ps((float const *) ptr + 12);
    __m256 d14 = _mm256_loadu_ps((float const *) ptr + 13);
    __m256 d15 = _mm256_loadu_ps((float const *) ptr + 14);
    __m256 d16 = _mm256_loadu_ps((float const *) ptr + 15);
    __m256 d17 = _mm256_loadu_ps((float const *) ptr + 16);
    __m256 d18 = _mm256_loadu_ps((float const *) ptr + 17);
    __m256 d19 = _mm256_loadu_ps((float const *) ptr + 18);
    __m256 d20 = _mm256_loadu_ps((float const *) ptr + 19);
    __m256 d21 = _mm256_loadu_ps((float const *) ptr + 20);
    __m256 d22 = _mm256_loadu_ps((float const *) ptr + 21);
    __m256 d23 = _mm256_loadu_ps((float const *) ptr + 22);
    __m256 d24 = _mm256_loadu_ps((float const *) ptr + 23);
    __m256 d25 = _mm256_loadu_ps((float const *) ptr + 24);
    __m256 d26 = _mm256_loadu_ps((float const *) ptr + 25);
    bitonic_sort_float_26v_ascending(d01, d02, d03, d04, d05, d06, d07, d08, d09, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26);
    _mm256_storeu_ps((float *) ptr + 0, d01);
    _mm256_storeu_ps((float *) ptr + 1, d02);
    _mm256_storeu_ps((float *) ptr + 2, d03);
    _mm256_storeu_ps((float *) ptr + 3, d04);
    _mm256_storeu_ps((float *) ptr + 4, d05);
    _mm256_storeu_ps((float *) ptr + 5, d06);
    _mm256_storeu_ps((float *) ptr + 6, d07);
    _mm256_storeu_ps((float *) ptr + 7, d08);
    _mm256_storeu_ps((float *) ptr + 8, d09);
    _mm256_storeu_ps((float *) ptr + 9, d10);
    _mm256_storeu_ps((float *) ptr + 10, d11);
    _mm256_storeu_ps((float *) ptr + 11, d12);
    _mm256_storeu_ps((float *) ptr + 12, d13);
    _mm256_storeu_ps((float *) ptr + 13, d14);
    _mm256_storeu_ps((float *) ptr + 14, d15);
    _mm256_storeu_ps((float *) ptr + 15, d16);
    _mm256_storeu_ps((float *) ptr + 16, d17);
    _mm256_storeu_ps((float *) ptr + 17, d18);
    _mm256_storeu_ps((float *) ptr + 18, d19);
    _mm256_storeu_ps((float *) ptr + 19, d20);
    _mm256_storeu_ps((float *) ptr + 20, d21);
    _mm256_storeu_ps((float *) ptr + 21, d22);
    _mm256_storeu_ps((float *) ptr + 22, d23);
    _mm256_storeu_ps((float *) ptr + 23, d24);
    _mm256_storeu_ps((float *) ptr + 24, d25);
    _mm256_storeu_ps((float *) ptr + 25, d26);
}

static __attribute__((noinline)) void bitonic_sort_float_27v(float *ptr) {
    __m256 d01 = _mm256_loadu_ps((float const *) ptr + 0);
    __m256 d02 = _mm256_loadu_ps((float const *) ptr + 1);
    __m256 d03 = _mm256_loadu_ps((float const *) ptr + 2);
    __m256 d04 = _mm256_loadu_ps((float const *) ptr + 3);
    __m256 d05 = _mm256_loadu_ps((float const *) ptr + 4);
    __m256 d06 = _mm256_loadu_ps((float const *) ptr + 5);
    __m256 d07 = _mm256_loadu_ps((float const *) ptr + 6);
    __m256 d08 = _mm256_loadu_ps((float const *) ptr + 7);
    __m256 d09 = _mm256_loadu_ps((float const *) ptr + 8);
    __m256 d10 = _mm256_loadu_ps((float const *) ptr + 9);
    __m256 d11 = _mm256_loadu_ps((float const *) ptr + 10);
    __m256 d12 = _mm256_loadu_ps((float const *) ptr + 11);
    __m256 d13 = _mm256_loadu_ps((float const *) ptr + 12);
    __m256 d14 = _mm256_loadu_ps((float const *) ptr + 13);
    __m256 d15 = _mm256_loadu_ps((float const *) ptr + 14);
    __m256 d16 = _mm256_loadu_ps((float const *) ptr + 15);
    __m256 d17 = _mm256_loadu_ps((float const *) ptr + 16);
    __m256 d18 = _mm256_loadu_ps((float const *) ptr + 17);
    __m256 d19 = _mm256_loadu_ps((float const *) ptr + 18);
    __m256 d20 = _mm256_loadu_ps((float const *) ptr + 19);
    __m256 d21 = _mm256_loadu_ps((float const *) ptr + 20);
    __m256 d22 = _mm256_loadu_ps((float const *) ptr + 21);
    __m256 d23 = _mm256_loadu_ps((float const *) ptr + 22);
    __m256 d24 = _mm256_loadu_ps((float const *) ptr + 23);
    __m256 d25 = _mm256_loadu_ps((float const *) ptr + 24);
    __m256 d26 = _mm256_loadu_ps((float const *) ptr + 25);
    __m256 d27 = _mm256_loadu_ps((float const *) ptr + 26);
    bitonic_sort_float_27v_ascending(d01, d02, d03, d04, d05, d06, d07, d08, d09, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27);
    _mm256_storeu_ps((float *) ptr + 0, d01);
    _mm256_storeu_ps((float *) ptr + 1, d02);
    _mm256_storeu_ps((float *) ptr + 2, d03);
    _mm256_storeu_ps((float *) ptr + 3, d04);
    _mm256_storeu_ps((float *) ptr + 4, d05);
    _mm256_storeu_ps((float *) ptr + 5, d06);
    _mm256_storeu_ps((float *) ptr + 6, d07);
    _mm256_storeu_ps((float *) ptr + 7, d08);
    _mm256_storeu_ps((float *) ptr + 8, d09);
    _mm256_storeu_ps((float *) ptr + 9, d10);
    _mm256_storeu_ps((float *) ptr + 10, d11);
    _mm256_storeu_ps((float *) ptr + 11, d12);
    _mm256_storeu_ps((float *) ptr + 12, d13);
    _mm256_storeu_ps((float *) ptr + 13, d14);
    _mm256_storeu_ps((float *) ptr + 14, d15);
    _mm256_storeu_ps((float *) ptr + 15, d16);
    _mm256_storeu_ps((float *) ptr + 16, d17);
    _mm256_storeu_ps((float *) ptr + 17, d18);
    _mm256_storeu_ps((float *) ptr + 18, d19);
    _mm256_storeu_ps((float *) ptr + 19, d20);
    _mm256_storeu_ps((float *) ptr + 20, d21);
    _mm256_storeu_ps((float *) ptr + 21, d22);
    _mm256_storeu_ps((float *) ptr + 22, d23);
    _mm256_storeu_ps((float *) ptr + 23, d24);
    _mm256_storeu_ps((float *) ptr + 24, d25);
    _mm256_storeu_ps((float *) ptr + 25, d26);
    _mm256_storeu_ps((float *) ptr + 26, d27);
}

static __attribute__((noinline)) void bitonic_sort_float_28v(float *ptr) {
    __m256 d01 = _mm256_loadu_ps((float const *) ptr + 0);
    __m256 d02 = _mm256_loadu_ps((float const *) ptr + 1);
    __m256 d03 = _mm256_loadu_ps((float const *) ptr + 2);
    __m256 d04 = _mm256_loadu_ps((float const *) ptr + 3);
    __m256 d05 = _mm256_loadu_ps((float const *) ptr + 4);
    __m256 d06 = _mm256_loadu_ps((float const *) ptr + 5);
    __m256 d07 = _mm256_loadu_ps((float const *) ptr + 6);
    __m256 d08 = _mm256_loadu_ps((float const *) ptr + 7);
    __m256 d09 = _mm256_loadu_ps((float const *) ptr + 8);
    __m256 d10 = _mm256_loadu_ps((float const *) ptr + 9);
    __m256 d11 = _mm256_loadu_ps((float const *) ptr + 10);
    __m256 d12 = _mm256_loadu_ps((float const *) ptr + 11);
    __m256 d13 = _mm256_loadu_ps((float const *) ptr + 12);
    __m256 d14 = _mm256_loadu_ps((float const *) ptr + 13);
    __m256 d15 = _mm256_loadu_ps((float const *) ptr + 14);
    __m256 d16 = _mm256_loadu_ps((float const *) ptr + 15);
    __m256 d17 = _mm256_loadu_ps((float const *) ptr + 16);
    __m256 d18 = _mm256_loadu_ps((float const *) ptr + 17);
    __m256 d19 = _mm256_loadu_ps((float const *) ptr + 18);
    __m256 d20 = _mm256_loadu_ps((float const *) ptr + 19);
    __m256 d21 = _mm256_loadu_ps((float const *) ptr + 20);
    __m256 d22 = _mm256_loadu_ps((float const *) ptr + 21);
    __m256 d23 = _mm256_loadu_ps((float const *) ptr + 22);
    __m256 d24 = _mm256_loadu_ps((float const *) ptr + 23);
    __m256 d25 = _mm256_loadu_ps((float const *) ptr + 24);
    __m256 d26 = _mm256_loadu_ps((float const *) ptr + 25);
    __m256 d27 = _mm256_loadu_ps((float const *) ptr + 26);
    __m256 d28 = _mm256_loadu_ps((float const *) ptr + 27);
    bitonic_sort_float_28v_ascending(d01, d02, d03, d04, d05, d06, d07, d08, d09, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28);
    _mm256_storeu_ps((float *) ptr + 0, d01);
    _mm256_storeu_ps((float *) ptr + 1, d02);
    _mm256_storeu_ps((float *) ptr + 2, d03);
    _mm256_storeu_ps((float *) ptr + 3, d04);
    _mm256_storeu_ps((float *) ptr + 4, d05);
    _mm256_storeu_ps((float *) ptr + 5, d06);
    _mm256_storeu_ps((float *) ptr + 6, d07);
    _mm256_storeu_ps((float *) ptr + 7, d08);
    _mm256_storeu_ps((float *) ptr + 8, d09);
    _mm256_storeu_ps((float *) ptr + 9, d10);
    _mm256_storeu_ps((float *) ptr + 10, d11);
    _mm256_storeu_ps((float *) ptr + 11, d12);
    _mm256_storeu_ps((float *) ptr + 12, d13);
    _mm256_storeu_ps((float *) ptr + 13, d14);
    _mm256_storeu_ps((float *) ptr + 14, d15);
    _mm256_storeu_ps((float *) ptr + 15, d16);
    _mm256_storeu_ps((float *) ptr + 16, d17);
    _mm256_storeu_ps((float *) ptr + 17, d18);
    _mm256_storeu_ps((float *) ptr + 18, d19);
    _mm256_storeu_ps((float *) ptr + 19, d20);
    _mm256_storeu_ps((float *) ptr + 20, d21);
    _mm256_storeu_ps((float *) ptr + 21, d22);
    _mm256_storeu_ps((float *) ptr + 22, d23);
    _mm256_storeu_ps((float *) ptr + 23, d24);
    _mm256_storeu_ps((float *) ptr + 24, d25);
    _mm256_storeu_ps((float *) ptr + 25, d26);
    _mm256_storeu_ps((float *) ptr + 26, d27);
    _mm256_storeu_ps((float *) ptr + 27, d28);
}

static __attribute__((noinline)) void bitonic_sort_float_29v(float *ptr) {
    __m256 d01 = _mm256_loadu_ps((float const *) ptr + 0);
    __m256 d02 = _mm256_loadu_ps((float const *) ptr + 1);
    __m256 d03 = _mm256_loadu_ps((float const *) ptr + 2);
    __m256 d04 = _mm256_loadu_ps((float const *) ptr + 3);
    __m256 d05 = _mm256_loadu_ps((float const *) ptr + 4);
    __m256 d06 = _mm256_loadu_ps((float const *) ptr + 5);
    __m256 d07 = _mm256_loadu_ps((float const *) ptr + 6);
    __m256 d08 = _mm256_loadu_ps((float const *) ptr + 7);
    __m256 d09 = _mm256_loadu_ps((float const *) ptr + 8);
    __m256 d10 = _mm256_loadu_ps((float const *) ptr + 9);
    __m256 d11 = _mm256_loadu_ps((float const *) ptr + 10);
    __m256 d12 = _mm256_loadu_ps((float const *) ptr + 11);
    __m256 d13 = _mm256_loadu_ps((float const *) ptr + 12);
    __m256 d14 = _mm256_loadu_ps((float const *) ptr + 13);
    __m256 d15 = _mm256_loadu_ps((float const *) ptr + 14);
    __m256 d16 = _mm256_loadu_ps((float const *) ptr + 15);
    __m256 d17 = _mm256_loadu_ps((float const *) ptr + 16);
    __m256 d18 = _mm256_loadu_ps((float const *) ptr + 17);
    __m256 d19 = _mm256_loadu_ps((float const *) ptr + 18);
    __m256 d20 = _mm256_loadu_ps((float const *) ptr + 19);
    __m256 d21 = _mm256_loadu_ps((float const *) ptr + 20);
    __m256 d22 = _mm256_loadu_ps((float const *) ptr + 21);
    __m256 d23 = _mm256_loadu_ps((float const *) ptr + 22);
    __m256 d24 = _mm256_loadu_ps((float const *) ptr + 23);
    __m256 d25 = _mm256_loadu_ps((float const *) ptr + 24);
    __m256 d26 = _mm256_loadu_ps((float const *) ptr + 25);
    __m256 d27 = _mm256_loadu_ps((float const *) ptr + 26);
    __m256 d28 = _mm256_loadu_ps((float const *) ptr + 27);
    __m256 d29 = _mm256_loadu_ps((float const *) ptr + 28);
    bitonic_sort_float_29v_ascending(d01, d02, d03, d04, d05, d06, d07, d08, d09, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29);
    _mm256_storeu_ps((float *) ptr + 0, d01);
    _mm256_storeu_ps((float *) ptr + 1, d02);
    _mm256_storeu_ps((float *) ptr + 2, d03);
    _mm256_storeu_ps((float *) ptr + 3, d04);
    _mm256_storeu_ps((float *) ptr + 4, d05);
    _mm256_storeu_ps((float *) ptr + 5, d06);
    _mm256_storeu_ps((float *) ptr + 6, d07);
    _mm256_storeu_ps((float *) ptr + 7, d08);
    _mm256_storeu_ps((float *) ptr + 8, d09);
    _mm256_storeu_ps((float *) ptr + 9, d10);
    _mm256_storeu_ps((float *) ptr + 10, d11);
    _mm256_storeu_ps((float *) ptr + 11, d12);
    _mm256_storeu_ps((float *) ptr + 12, d13);
    _mm256_storeu_ps((float *) ptr + 13, d14);
    _mm256_storeu_ps((float *) ptr + 14, d15);
    _mm256_storeu_ps((float *) ptr + 15, d16);
    _mm256_storeu_ps((float *) ptr + 16, d17);
    _mm256_storeu_ps((float *) ptr + 17, d18);
    _mm256_storeu_ps((float *) ptr + 18, d19);
    _mm256_storeu_ps((float *) ptr + 19, d20);
    _mm256_storeu_ps((float *) ptr + 20, d21);
    _mm256_storeu_ps((float *) ptr + 21, d22);
    _mm256_storeu_ps((float *) ptr + 22, d23);
    _mm256_storeu_ps((float *) ptr + 23, d24);
    _mm256_storeu_ps((float *) ptr + 24, d25);
    _mm256_storeu_ps((float *) ptr + 25, d26);
    _mm256_storeu_ps((float *) ptr + 26, d27);
    _mm256_storeu_ps((float *) ptr + 27, d28);
    _mm256_storeu_ps((float *) ptr + 28, d29);
}

static __attribute__((noinline)) void bitonic_sort_float_30v(float *ptr) {
    __m256 d01 = _mm256_loadu_ps((float const *) ptr + 0);
    __m256 d02 = _mm256_loadu_ps((float const *) ptr + 1);
    __m256 d03 = _mm256_loadu_ps((float const *) ptr + 2);
    __m256 d04 = _mm256_loadu_ps((float const *) ptr + 3);
    __m256 d05 = _mm256_loadu_ps((float const *) ptr + 4);
    __m256 d06 = _mm256_loadu_ps((float const *) ptr + 5);
    __m256 d07 = _mm256_loadu_ps((float const *) ptr + 6);
    __m256 d08 = _mm256_loadu_ps((float const *) ptr + 7);
    __m256 d09 = _mm256_loadu_ps((float const *) ptr + 8);
    __m256 d10 = _mm256_loadu_ps((float const *) ptr + 9);
    __m256 d11 = _mm256_loadu_ps((float const *) ptr + 10);
    __m256 d12 = _mm256_loadu_ps((float const *) ptr + 11);
    __m256 d13 = _mm256_loadu_ps((float const *) ptr + 12);
    __m256 d14 = _mm256_loadu_ps((float const *) ptr + 13);
    __m256 d15 = _mm256_loadu_ps((float const *) ptr + 14);
    __m256 d16 = _mm256_loadu_ps((float const *) ptr + 15);
    __m256 d17 = _mm256_loadu_ps((float const *) ptr + 16);
    __m256 d18 = _mm256_loadu_ps((float const *) ptr + 17);
    __m256 d19 = _mm256_loadu_ps((float const *) ptr + 18);
    __m256 d20 = _mm256_loadu_ps((float const *) ptr + 19);
    __m256 d21 = _mm256_loadu_ps((float const *) ptr + 20);
    __m256 d22 = _mm256_loadu_ps((float const *) ptr + 21);
    __m256 d23 = _mm256_loadu_ps((float const *) ptr + 22);
    __m256 d24 = _mm256_loadu_ps((float const *) ptr + 23);
    __m256 d25 = _mm256_loadu_ps((float const *) ptr + 24);
    __m256 d26 = _mm256_loadu_ps((float const *) ptr + 25);
    __m256 d27 = _mm256_loadu_ps((float const *) ptr + 26);
    __m256 d28 = _mm256_loadu_ps((float const *) ptr + 27);
    __m256 d29 = _mm256_loadu_ps((float const *) ptr + 28);
    __m256 d30 = _mm256_loadu_ps((float const *) ptr + 29);
    bitonic_sort_float_30v_ascending(d01, d02, d03, d04, d05, d06, d07, d08, d09, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30);
    _mm256_storeu_ps((float *) ptr + 0, d01);
    _mm256_storeu_ps((float *) ptr + 1, d02);
    _mm256_storeu_ps((float *) ptr + 2, d03);
    _mm256_storeu_ps((float *) ptr + 3, d04);
    _mm256_storeu_ps((float *) ptr + 4, d05);
    _mm256_storeu_ps((float *) ptr + 5, d06);
    _mm256_storeu_ps((float *) ptr + 6, d07);
    _mm256_storeu_ps((float *) ptr + 7, d08);
    _mm256_storeu_ps((float *) ptr + 8, d09);
    _mm256_storeu_ps((float *) ptr + 9, d10);
    _mm256_storeu_ps((float *) ptr + 10, d11);
    _mm256_storeu_ps((float *) ptr + 11, d12);
    _mm256_storeu_ps((float *) ptr + 12, d13);
    _mm256_storeu_ps((float *) ptr + 13, d14);
    _mm256_storeu_ps((float *) ptr + 14, d15);
    _mm256_storeu_ps((float *) ptr + 15, d16);
    _mm256_storeu_ps((float *) ptr + 16, d17);
    _mm256_storeu_ps((float *) ptr + 17, d18);
    _mm256_storeu_ps((float *) ptr + 18, d19);
    _mm256_storeu_ps((float *) ptr + 19, d20);
    _mm256_storeu_ps((float *) ptr + 20, d21);
    _mm256_storeu_ps((float *) ptr + 21, d22);
    _mm256_storeu_ps((float *) ptr + 22, d23);
    _mm256_storeu_ps((float *) ptr + 23, d24);
    _mm256_storeu_ps((float *) ptr + 24, d25);
    _mm256_storeu_ps((float *) ptr + 25, d26);
    _mm256_storeu_ps((float *) ptr + 26, d27);
    _mm256_storeu_ps((float *) ptr + 27, d28);
    _mm256_storeu_ps((float *) ptr + 28, d29);
    _mm256_storeu_ps((float *) ptr + 29, d30);
}

static __attribute__((noinline)) void bitonic_sort_float_31v(float *ptr) {
    __m256 d01 = _mm256_loadu_ps((float const *) ptr + 0);
    __m256 d02 = _mm256_loadu_ps((float const *) ptr + 1);
    __m256 d03 = _mm256_loadu_ps((float const *) ptr + 2);
    __m256 d04 = _mm256_loadu_ps((float const *) ptr + 3);
    __m256 d05 = _mm256_loadu_ps((float const *) ptr + 4);
    __m256 d06 = _mm256_loadu_ps((float const *) ptr + 5);
    __m256 d07 = _mm256_loadu_ps((float const *) ptr + 6);
    __m256 d08 = _mm256_loadu_ps((float const *) ptr + 7);
    __m256 d09 = _mm256_loadu_ps((float const *) ptr + 8);
    __m256 d10 = _mm256_loadu_ps((float const *) ptr + 9);
    __m256 d11 = _mm256_loadu_ps((float const *) ptr + 10);
    __m256 d12 = _mm256_loadu_ps((float const *) ptr + 11);
    __m256 d13 = _mm256_loadu_ps((float const *) ptr + 12);
    __m256 d14 = _mm256_loadu_ps((float const *) ptr + 13);
    __m256 d15 = _mm256_loadu_ps((float const *) ptr + 14);
    __m256 d16 = _mm256_loadu_ps((float const *) ptr + 15);
    __m256 d17 = _mm256_loadu_ps((float const *) ptr + 16);
    __m256 d18 = _mm256_loadu_ps((float const *) ptr + 17);
    __m256 d19 = _mm256_loadu_ps((float const *) ptr + 18);
    __m256 d20 = _mm256_loadu_ps((float const *) ptr + 19);
    __m256 d21 = _mm256_loadu_ps((float const *) ptr + 20);
    __m256 d22 = _mm256_loadu_ps((float const *) ptr + 21);
    __m256 d23 = _mm256_loadu_ps((float const *) ptr + 22);
    __m256 d24 = _mm256_loadu_ps((float const *) ptr + 23);
    __m256 d25 = _mm256_loadu_ps((float const *) ptr + 24);
    __m256 d26 = _mm256_loadu_ps((float const *) ptr + 25);
    __m256 d27 = _mm256_loadu_ps((float const *) ptr + 26);
    __m256 d28 = _mm256_loadu_ps((float const *) ptr + 27);
    __m256 d29 = _mm256_loadu_ps((float const *) ptr + 28);
    __m256 d30 = _mm256_loadu_ps((float const *) ptr + 29);
    __m256 d31 = _mm256_loadu_ps((float const *) ptr + 30);
    bitonic_sort_float_31v_ascending(d01, d02, d03, d04, d05, d06, d07, d08, d09, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31);
    _mm256_storeu_ps((float *) ptr + 0, d01);
    _mm256_storeu_ps((float *) ptr + 1, d02);
    _mm256_storeu_ps((float *) ptr + 2, d03);
    _mm256_storeu_ps((float *) ptr + 3, d04);
    _mm256_storeu_ps((float *) ptr + 4, d05);
    _mm256_storeu_ps((float *) ptr + 5, d06);
    _mm256_storeu_ps((float *) ptr + 6, d07);
    _mm256_storeu_ps((float *) ptr + 7, d08);
    _mm256_storeu_ps((float *) ptr + 8, d09);
    _mm256_storeu_ps((float *) ptr + 9, d10);
    _mm256_storeu_ps((float *) ptr + 10, d11);
    _mm256_storeu_ps((float *) ptr + 11, d12);
    _mm256_storeu_ps((float *) ptr + 12, d13);
    _mm256_storeu_ps((float *) ptr + 13, d14);
    _mm256_storeu_ps((float *) ptr + 14, d15);
    _mm256_storeu_ps((float *) ptr + 15, d16);
    _mm256_storeu_ps((float *) ptr + 16, d17);
    _mm256_storeu_ps((float *) ptr + 17, d18);
    _mm256_storeu_ps((float *) ptr + 18, d19);
    _mm256_storeu_ps((float *) ptr + 19, d20);
    _mm256_storeu_ps((float *) ptr + 20, d21);
    _mm256_storeu_ps((float *) ptr + 21, d22);
    _mm256_storeu_ps((float *) ptr + 22, d23);
    _mm256_storeu_ps((float *) ptr + 23, d24);
    _mm256_storeu_ps((float *) ptr + 24, d25);
    _mm256_storeu_ps((float *) ptr + 25, d26);
    _mm256_storeu_ps((float *) ptr + 26, d27);
    _mm256_storeu_ps((float *) ptr + 27, d28);
    _mm256_storeu_ps((float *) ptr + 28, d29);
    _mm256_storeu_ps((float *) ptr + 29, d30);
    _mm256_storeu_ps((float *) ptr + 30, d31);
}

static __attribute__((noinline)) void bitonic_sort_float_32v(float *ptr) {
    __m256 d01 = _mm256_loadu_ps((float const *) ptr + 0);
    __m256 d02 = _mm256_loadu_ps((float const *) ptr + 1);
    __m256 d03 = _mm256_loadu_ps((float const *) ptr + 2);
    __m256 d04 = _mm256_loadu_ps((float const *) ptr + 3);
    __m256 d05 = _mm256_loadu_ps((float const *) ptr + 4);
    __m256 d06 = _mm256_loadu_ps((float const *) ptr + 5);
    __m256 d07 = _mm256_loadu_ps((float const *) ptr + 6);
    __m256 d08 = _mm256_loadu_ps((float const *) ptr + 7);
    __m256 d09 = _mm256_loadu_ps((float const *) ptr + 8);
    __m256 d10 = _mm256_loadu_ps((float const *) ptr + 9);
    __m256 d11 = _mm256_loadu_ps((float const *) ptr + 10);
    __m256 d12 = _mm256_loadu_ps((float const *) ptr + 11);
    __m256 d13 = _mm256_loadu_ps((float const *) ptr + 12);
    __m256 d14 = _mm256_loadu_ps((float const *) ptr + 13);
    __m256 d15 = _mm256_loadu_ps((float const *) ptr + 14);
    __m256 d16 = _mm256_loadu_ps((float const *) ptr + 15);
    __m256 d17 = _mm256_loadu_ps((float const *) ptr + 16);
    __m256 d18 = _mm256_loadu_ps((float const *) ptr + 17);
    __m256 d19 = _mm256_loadu_ps((float const *) ptr + 18);
    __m256 d20 = _mm256_loadu_ps((float const *) ptr + 19);
    __m256 d21 = _mm256_loadu_ps((float const *) ptr + 20);
    __m256 d22 = _mm256_loadu_ps((float const *) ptr + 21);
    __m256 d23 = _mm256_loadu_ps((float const *) ptr + 22);
    __m256 d24 = _mm256_loadu_ps((float const *) ptr + 23);
    __m256 d25 = _mm256_loadu_ps((float const *) ptr + 24);
    __m256 d26 = _mm256_loadu_ps((float const *) ptr + 25);
    __m256 d27 = _mm256_loadu_ps((float const *) ptr + 26);
    __m256 d28 = _mm256_loadu_ps((float const *) ptr + 27);
    __m256 d29 = _mm256_loadu_ps((float const *) ptr + 28);
    __m256 d30 = _mm256_loadu_ps((float const *) ptr + 29);
    __m256 d31 = _mm256_loadu_ps((float const *) ptr + 30);
    __m256 d32 = _mm256_loadu_ps((float const *) ptr + 31);
    bitonic_sort_float_32v_ascending(d01, d02, d03, d04, d05, d06, d07, d08, d09, d10, d11, d12, d13, d14, d15, d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31, d32);
    _mm256_storeu_ps((float *) ptr + 0, d01);
    _mm256_storeu_ps((float *) ptr + 1, d02);
    _mm256_storeu_ps((float *) ptr + 2, d03);
    _mm256_storeu_ps((float *) ptr + 3, d04);
    _mm256_storeu_ps((float *) ptr + 4, d05);
    _mm256_storeu_ps((float *) ptr + 5, d06);
    _mm256_storeu_ps((float *) ptr + 6, d07);
    _mm256_storeu_ps((float *) ptr + 7, d08);
    _mm256_storeu_ps((float *) ptr + 8, d09);
    _mm256_storeu_ps((float *) ptr + 9, d10);
    _mm256_storeu_ps((float *) ptr + 10, d11);
    _mm256_storeu_ps((float *) ptr + 11, d12);
    _mm256_storeu_ps((float *) ptr + 12, d13);
    _mm256_storeu_ps((float *) ptr + 13, d14);
    _mm256_storeu_ps((float *) ptr + 14, d15);
    _mm256_storeu_ps((float *) ptr + 15, d16);
    _mm256_storeu_ps((float *) ptr + 16, d17);
    _mm256_storeu_ps((float *) ptr + 17, d18);
    _mm256_storeu_ps((float *) ptr + 18, d19);
    _mm256_storeu_ps((float *) ptr + 19, d20);
    _mm256_storeu_ps((float *) ptr + 20, d21);
    _mm256_storeu_ps((float *) ptr + 21, d22);
    _mm256_storeu_ps((float *) ptr + 22, d23);
    _mm256_storeu_ps((float *) ptr + 23, d24);
    _mm256_storeu_ps((float *) ptr + 24, d25);
    _mm256_storeu_ps((float *) ptr + 25, d26);
    _mm256_storeu_ps((float *) ptr + 26, d27);
    _mm256_storeu_ps((float *) ptr + 27, d28);
    _mm256_storeu_ps((float *) ptr + 28, d29);
    _mm256_storeu_ps((float *) ptr + 29, d30);
    _mm256_storeu_ps((float *) ptr + 30, d31);
    _mm256_storeu_ps((float *) ptr + 31, d32);
}

static void bitonic_sort_float(float *ptr, int length) {
    const int N = 8;

    switch(length / N) {
        case 1: bitonic_sort_float_01v(ptr); break;
        case 2: bitonic_sort_float_02v(ptr); break;
        case 3: bitonic_sort_float_03v(ptr); break;
        case 4: bitonic_sort_float_04v(ptr); break;
        case 5: bitonic_sort_float_05v(ptr); break;
        case 6: bitonic_sort_float_06v(ptr); break;
        case 7: bitonic_sort_float_07v(ptr); break;
        case 8: bitonic_sort_float_08v(ptr); break;
        case 9: bitonic_sort_float_09v(ptr); break;
        case 10: bitonic_sort_float_10v(ptr); break;
        case 11: bitonic_sort_float_11v(ptr); break;
        case 12: bitonic_sort_float_12v(ptr); break;
        case 13: bitonic_sort_float_13v(ptr); break;
        case 14: bitonic_sort_float_14v(ptr); break;
        case 15: bitonic_sort_float_15v(ptr); break;
        case 16: bitonic_sort_float_16v(ptr); break;
        case 17: bitonic_sort_float_17v(ptr); break;
        case 18: bitonic_sort_float_18v(ptr); break;
        case 19: bitonic_sort_float_19v(ptr); break;
        case 20: bitonic_sort_float_20v(ptr); break;
        case 21: bitonic_sort_float_21v(ptr); break;
        case 22: bitonic_sort_float_22v(ptr); break;
        case 23: bitonic_sort_float_23v(ptr); break;
        case 24: bitonic_sort_float_24v(ptr); break;
        case 25: bitonic_sort_float_25v(ptr); break;
        case 26: bitonic_sort_float_26v(ptr); break;
        case 27: bitonic_sort_float_27v(ptr); break;
        case 28: bitonic_sort_float_28v(ptr); break;
        case 29: bitonic_sort_float_29v(ptr); break;
        case 30: bitonic_sort_float_30v(ptr); break;
        case 31: bitonic_sort_float_31v(ptr); break;
        case 32: bitonic_sort_float_32v(ptr); break;
    }
}
}
}
