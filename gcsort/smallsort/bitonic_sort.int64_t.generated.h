
#ifndef BITONIC_SORT_INT64_T_H
#define BITONIC_SORT_INT64_T_H

#include <immintrin.h>
#include "bitonic_sort.h"

#ifdef _MSC_VER
    // MSVC
	#define INLINE __forceinline
	#define NOINLINE __declspec(noinline)
#else
    // GCC + Clang
	#define INLINE  __attribute__((always_inline))
	#define NOINLINE __attribute__((noinline))
#endif

#define i2d _mm256_castsi256_pd
#define d2i _mm256_castpd_si256

namespace gcsort {
namespace smallsort {
template<> struct bitonic<int64_t> {
public:

    static INLINE void sort_01v_ascending(__m256i& d01) {
        __m256i  min, max, s, cmp;

        s = d2i(_mm256_shuffle_pd(i2d(d01), i2d(d01), 0x5));
        cmp = _mm256_cmpgt_epi64(s, d01);
        min = d2i(_mm256_blendv_pd(i2d(s), i2d(d01), i2d(cmp)));
        max = d2i(_mm256_blendv_pd(i2d(d01), i2d(s), i2d(cmp)));
        d01 = d2i(_mm256_blend_pd(i2d(min), i2d(max), 0xA));

        s = d2i(_mm256_permute4x64_pd(i2d(d01), 0x1B));
        cmp = _mm256_cmpgt_epi64(s, d01);
        min = d2i(_mm256_blendv_pd(i2d(s), i2d(d01), i2d(cmp)));
        max = d2i(_mm256_blendv_pd(i2d(d01), i2d(s), i2d(cmp)));
        d01 = d2i(_mm256_blend_pd(i2d(min), i2d(max), 0xC));

        s = d2i(_mm256_shuffle_pd(i2d(d01), i2d(d01), 0x5));
        cmp = _mm256_cmpgt_epi64(s, d01);
        min = d2i(_mm256_blendv_pd(i2d(s), i2d(d01), i2d(cmp)));
        max = d2i(_mm256_blendv_pd(i2d(d01), i2d(s), i2d(cmp)));
        d01 = d2i(_mm256_blend_pd(i2d(min), i2d(max), 0xA));
}
    static INLINE void sort_01v_merge_ascending(__m256i& d01) {
        __m256i  min, max, s, cmp;

        s = d2i(_mm256_permute4x64_pd(i2d(d01), 0x4E));
        cmp = _mm256_cmpgt_epi64(s, d01);
        min = d2i(_mm256_blendv_pd(i2d(s), i2d(d01), i2d(cmp)));
        max = d2i(_mm256_blendv_pd(i2d(d01), i2d(s), i2d(cmp)));
        d01 = d2i(_mm256_blend_pd(i2d(min), i2d(max), 0xC));

        s = d2i(_mm256_shuffle_pd(i2d(d01), i2d(d01), 0x5));
        cmp = _mm256_cmpgt_epi64(s, d01);
        min = d2i(_mm256_blendv_pd(i2d(s), i2d(d01), i2d(cmp)));
        max = d2i(_mm256_blendv_pd(i2d(d01), i2d(s), i2d(cmp)));
        d01 = d2i(_mm256_blend_pd(i2d(min), i2d(max), 0xA));
}
    static INLINE void sort_01v_descending(__m256i& d01) {
        __m256i  min, max, s, cmp;

        s = d2i(_mm256_shuffle_pd(i2d(d01), i2d(d01), 0x5));
        cmp = _mm256_cmpgt_epi64(s, d01);
        min = d2i(_mm256_blendv_pd(i2d(s), i2d(d01), i2d(cmp)));
        max = d2i(_mm256_blendv_pd(i2d(d01), i2d(s), i2d(cmp)));
        d01 = d2i(_mm256_blend_pd(i2d(max), i2d(min), 0xA));

        s = d2i(_mm256_permute4x64_pd(i2d(d01), 0x1B));
        cmp = _mm256_cmpgt_epi64(s, d01);
        min = d2i(_mm256_blendv_pd(i2d(s), i2d(d01), i2d(cmp)));
        max = d2i(_mm256_blendv_pd(i2d(d01), i2d(s), i2d(cmp)));
        d01 = d2i(_mm256_blend_pd(i2d(max), i2d(min), 0xC));

        s = d2i(_mm256_shuffle_pd(i2d(d01), i2d(d01), 0x5));
        cmp = _mm256_cmpgt_epi64(s, d01);
        min = d2i(_mm256_blendv_pd(i2d(s), i2d(d01), i2d(cmp)));
        max = d2i(_mm256_blendv_pd(i2d(d01), i2d(s), i2d(cmp)));
        d01 = d2i(_mm256_blend_pd(i2d(max), i2d(min), 0xA));
}
    static INLINE void sort_01v_merge_descending(__m256i& d01) {
        __m256i  min, max, s, cmp;

        s = d2i(_mm256_permute4x64_pd(i2d(d01), 0x4E));
        cmp = _mm256_cmpgt_epi64(s, d01);
        min = d2i(_mm256_blendv_pd(i2d(s), i2d(d01), i2d(cmp)));
        max = d2i(_mm256_blendv_pd(i2d(d01), i2d(s), i2d(cmp)));
        d01 = d2i(_mm256_blend_pd(i2d(max), i2d(min), 0xC));

        s = d2i(_mm256_shuffle_pd(i2d(d01), i2d(d01), 0x5));
        cmp = _mm256_cmpgt_epi64(s, d01);
        min = d2i(_mm256_blendv_pd(i2d(s), i2d(d01), i2d(cmp)));
        max = d2i(_mm256_blendv_pd(i2d(d01), i2d(s), i2d(cmp)));
        d01 = d2i(_mm256_blend_pd(i2d(max), i2d(min), 0xA));
}
    static INLINE void sort_02v_ascending(__m256i& d01, __m256i& d02) {
    __m256i  tmp, cmp;

    sort_01v_ascending(d01);
    sort_01v_descending(d02);

    tmp = d02;
    cmp = _mm256_cmpgt_epi64(d01, d02);
    d02 = d2i(_mm256_blendv_pd(i2d(d02), i2d(d01), i2d(cmp)));
    d01 = d2i(_mm256_blendv_pd(i2d(d01), i2d(tmp), i2d(cmp)));

    sort_01v_merge_ascending(d01);
    sort_01v_merge_ascending(d02);
}
    static INLINE void sort_02v_descending(__m256i& d01, __m256i& d02) {
    __m256i  tmp, cmp;

    sort_01v_descending(d01);
    sort_01v_ascending(d02);

    tmp = d02;
    cmp = _mm256_cmpgt_epi64(d01, d02);
    d02 = d2i(_mm256_blendv_pd(i2d(d02), i2d(d01), i2d(cmp)));
    d01 = d2i(_mm256_blendv_pd(i2d(d01), i2d(tmp), i2d(cmp)));

    sort_01v_merge_descending(d01);
    sort_01v_merge_descending(d02);
}
    static INLINE void sort_02v_merge_ascending(__m256i& d01, __m256i& d02) {
    __m256i  tmp, cmp;

    tmp = d01;
    cmp = _mm256_cmpgt_epi64(d02, d01);
    d01 = d2i(_mm256_blendv_pd(i2d(d02), i2d(d01), i2d(cmp)));
    cmp = _mm256_cmpgt_epi64(d02, tmp);
    d02 = d2i(_mm256_blendv_pd(i2d(tmp), i2d(d02), i2d(cmp)));

    sort_01v_merge_ascending(d01);
    sort_01v_merge_ascending(d02);
}
    static INLINE void sort_02v_merge_descending(__m256i& d01, __m256i& d02) {
    __m256i  tmp, cmp;

    tmp = d01;
    cmp = _mm256_cmpgt_epi64(d02, d01);
    d01 = d2i(_mm256_blendv_pd(i2d(d02), i2d(d01), i2d(cmp)));
    cmp = _mm256_cmpgt_epi64(d02, tmp);
    d02 = d2i(_mm256_blendv_pd(i2d(tmp), i2d(d02), i2d(cmp)));

    sort_01v_merge_descending(d01);
    sort_01v_merge_descending(d02);
}
    static INLINE void sort_03v_ascending(__m256i& d01, __m256i& d02, __m256i& d03) {
    __m256i  tmp, cmp;

    sort_02v_ascending(d01, d02);
    sort_01v_descending(d03);

    tmp = d03;
    cmp = _mm256_cmpgt_epi64(d02, d03);
    d03 = d2i(_mm256_blendv_pd(i2d(d03), i2d(d02), i2d(cmp)));
    d02 = d2i(_mm256_blendv_pd(i2d(d02), i2d(tmp), i2d(cmp)));

    sort_02v_merge_ascending(d01, d02);
    sort_01v_merge_ascending(d03);
}
    static INLINE void sort_03v_descending(__m256i& d01, __m256i& d02, __m256i& d03) {
    __m256i  tmp, cmp;

    sort_02v_descending(d01, d02);
    sort_01v_ascending(d03);

    tmp = d03;
    cmp = _mm256_cmpgt_epi64(d02, d03);
    d03 = d2i(_mm256_blendv_pd(i2d(d03), i2d(d02), i2d(cmp)));
    d02 = d2i(_mm256_blendv_pd(i2d(d02), i2d(tmp), i2d(cmp)));

    sort_02v_merge_descending(d01, d02);
    sort_01v_merge_descending(d03);
}
    static INLINE void sort_03v_merge_ascending(__m256i& d01, __m256i& d02, __m256i& d03) {
    __m256i  tmp, cmp;

    tmp = d01;
    cmp = _mm256_cmpgt_epi64(d03, d01);
    d01 = d2i(_mm256_blendv_pd(i2d(d03), i2d(d01), i2d(cmp)));
    cmp = _mm256_cmpgt_epi64(d03, tmp);
    d03 = d2i(_mm256_blendv_pd(i2d(tmp), i2d(d03), i2d(cmp)));

    sort_02v_merge_ascending(d01, d02);
    sort_01v_merge_ascending(d03);
}
    static INLINE void sort_03v_merge_descending(__m256i& d01, __m256i& d02, __m256i& d03) {
    __m256i  tmp, cmp;

    tmp = d01;
    cmp = _mm256_cmpgt_epi64(d03, d01);
    d01 = d2i(_mm256_blendv_pd(i2d(d03), i2d(d01), i2d(cmp)));
    cmp = _mm256_cmpgt_epi64(d03, tmp);
    d03 = d2i(_mm256_blendv_pd(i2d(tmp), i2d(d03), i2d(cmp)));

    sort_02v_merge_descending(d01, d02);
    sort_01v_merge_descending(d03);
}
    static INLINE void sort_04v_ascending(__m256i& d01, __m256i& d02, __m256i& d03, __m256i& d04) {
    __m256i  tmp, cmp;

    sort_02v_ascending(d01, d02);
    sort_02v_descending(d03, d04);

    tmp = d03;
    cmp = _mm256_cmpgt_epi64(d02, d03);
    d03 = d2i(_mm256_blendv_pd(i2d(d03), i2d(d02), i2d(cmp)));
    d02 = d2i(_mm256_blendv_pd(i2d(d02), i2d(tmp), i2d(cmp)));

    tmp = d04;
    cmp = _mm256_cmpgt_epi64(d01, d04);
    d04 = d2i(_mm256_blendv_pd(i2d(d04), i2d(d01), i2d(cmp)));
    d01 = d2i(_mm256_blendv_pd(i2d(d01), i2d(tmp), i2d(cmp)));

    sort_02v_merge_ascending(d01, d02);
    sort_02v_merge_ascending(d03, d04);
}
    static INLINE void sort_04v_descending(__m256i& d01, __m256i& d02, __m256i& d03, __m256i& d04) {
    __m256i  tmp, cmp;

    sort_02v_descending(d01, d02);
    sort_02v_ascending(d03, d04);

    tmp = d03;
    cmp = _mm256_cmpgt_epi64(d02, d03);
    d03 = d2i(_mm256_blendv_pd(i2d(d03), i2d(d02), i2d(cmp)));
    d02 = d2i(_mm256_blendv_pd(i2d(d02), i2d(tmp), i2d(cmp)));

    tmp = d04;
    cmp = _mm256_cmpgt_epi64(d01, d04);
    d04 = d2i(_mm256_blendv_pd(i2d(d04), i2d(d01), i2d(cmp)));
    d01 = d2i(_mm256_blendv_pd(i2d(d01), i2d(tmp), i2d(cmp)));

    sort_02v_merge_descending(d01, d02);
    sort_02v_merge_descending(d03, d04);
}
    static INLINE void sort_04v_merge_ascending(__m256i& d01, __m256i& d02, __m256i& d03, __m256i& d04) {
    __m256i  tmp, cmp;

    tmp = d01;
    cmp = _mm256_cmpgt_epi64(d03, d01);
    d01 = d2i(_mm256_blendv_pd(i2d(d03), i2d(d01), i2d(cmp)));
    cmp = _mm256_cmpgt_epi64(d03, tmp);
    d03 = d2i(_mm256_blendv_pd(i2d(tmp), i2d(d03), i2d(cmp)));

    tmp = d02;
    cmp = _mm256_cmpgt_epi64(d04, d02);
    d02 = d2i(_mm256_blendv_pd(i2d(d04), i2d(d02), i2d(cmp)));
    cmp = _mm256_cmpgt_epi64(d04, tmp);
    d04 = d2i(_mm256_blendv_pd(i2d(tmp), i2d(d04), i2d(cmp)));

    sort_02v_merge_ascending(d01, d02);
    sort_02v_merge_ascending(d03, d04);
}
    static INLINE void sort_04v_merge_descending(__m256i& d01, __m256i& d02, __m256i& d03, __m256i& d04) {
    __m256i  tmp, cmp;

    tmp = d01;
    cmp = _mm256_cmpgt_epi64(d03, d01);
    d01 = d2i(_mm256_blendv_pd(i2d(d03), i2d(d01), i2d(cmp)));
    cmp = _mm256_cmpgt_epi64(d03, tmp);
    d03 = d2i(_mm256_blendv_pd(i2d(tmp), i2d(d03), i2d(cmp)));

    tmp = d02;
    cmp = _mm256_cmpgt_epi64(d04, d02);
    d02 = d2i(_mm256_blendv_pd(i2d(d04), i2d(d02), i2d(cmp)));
    cmp = _mm256_cmpgt_epi64(d04, tmp);
    d04 = d2i(_mm256_blendv_pd(i2d(tmp), i2d(d04), i2d(cmp)));

    sort_02v_merge_descending(d01, d02);
    sort_02v_merge_descending(d03, d04);
}
    static NOINLINE void sort_05v_ascending(__m256i& d01, __m256i& d02, __m256i& d03, __m256i& d04, __m256i& d05) {
    __m256i  tmp, cmp;

    sort_04v_ascending(d01, d02, d03, d04);
    sort_01v_descending(d05);

    tmp = d05;
    cmp = _mm256_cmpgt_epi64(d04, d05);
    d05 = d2i(_mm256_blendv_pd(i2d(d05), i2d(d04), i2d(cmp)));
    d04 = d2i(_mm256_blendv_pd(i2d(d04), i2d(tmp), i2d(cmp)));

    sort_04v_merge_ascending(d01, d02, d03, d04);
    sort_01v_merge_ascending(d05);
}
    static NOINLINE void sort_05v_descending(__m256i& d01, __m256i& d02, __m256i& d03, __m256i& d04, __m256i& d05) {
    __m256i  tmp, cmp;

    sort_04v_descending(d01, d02, d03, d04);
    sort_01v_ascending(d05);

    tmp = d05;
    cmp = _mm256_cmpgt_epi64(d04, d05);
    d05 = d2i(_mm256_blendv_pd(i2d(d05), i2d(d04), i2d(cmp)));
    d04 = d2i(_mm256_blendv_pd(i2d(d04), i2d(tmp), i2d(cmp)));

    sort_04v_merge_descending(d01, d02, d03, d04);
    sort_01v_merge_descending(d05);
}
    static NOINLINE void sort_05v_merge_ascending(__m256i& d01, __m256i& d02, __m256i& d03, __m256i& d04, __m256i& d05) {
    __m256i  tmp, cmp;

    tmp = d01;
    cmp = _mm256_cmpgt_epi64(d05, d01);
    d01 = d2i(_mm256_blendv_pd(i2d(d05), i2d(d01), i2d(cmp)));
    cmp = _mm256_cmpgt_epi64(d05, tmp);
    d05 = d2i(_mm256_blendv_pd(i2d(tmp), i2d(d05), i2d(cmp)));

    sort_04v_merge_ascending(d01, d02, d03, d04);
    sort_01v_merge_ascending(d05);
}
    static NOINLINE void sort_05v_merge_descending(__m256i& d01, __m256i& d02, __m256i& d03, __m256i& d04, __m256i& d05) {
    __m256i  tmp, cmp;

    tmp = d01;
    cmp = _mm256_cmpgt_epi64(d05, d01);
    d01 = d2i(_mm256_blendv_pd(i2d(d05), i2d(d01), i2d(cmp)));
    cmp = _mm256_cmpgt_epi64(d05, tmp);
    d05 = d2i(_mm256_blendv_pd(i2d(tmp), i2d(d05), i2d(cmp)));

    sort_04v_merge_descending(d01, d02, d03, d04);
    sort_01v_merge_descending(d05);
}
    static NOINLINE void sort_06v_ascending(__m256i& d01, __m256i& d02, __m256i& d03, __m256i& d04, __m256i& d05, __m256i& d06) {
    __m256i  tmp, cmp;

    sort_04v_ascending(d01, d02, d03, d04);
    sort_02v_descending(d05, d06);

    tmp = d05;
    cmp = _mm256_cmpgt_epi64(d04, d05);
    d05 = d2i(_mm256_blendv_pd(i2d(d05), i2d(d04), i2d(cmp)));
    d04 = d2i(_mm256_blendv_pd(i2d(d04), i2d(tmp), i2d(cmp)));

    tmp = d06;
    cmp = _mm256_cmpgt_epi64(d03, d06);
    d06 = d2i(_mm256_blendv_pd(i2d(d06), i2d(d03), i2d(cmp)));
    d03 = d2i(_mm256_blendv_pd(i2d(d03), i2d(tmp), i2d(cmp)));

    sort_04v_merge_ascending(d01, d02, d03, d04);
    sort_02v_merge_ascending(d05, d06);
}
    static NOINLINE void sort_06v_descending(__m256i& d01, __m256i& d02, __m256i& d03, __m256i& d04, __m256i& d05, __m256i& d06) {
    __m256i  tmp, cmp;

    sort_04v_descending(d01, d02, d03, d04);
    sort_02v_ascending(d05, d06);

    tmp = d05;
    cmp = _mm256_cmpgt_epi64(d04, d05);
    d05 = d2i(_mm256_blendv_pd(i2d(d05), i2d(d04), i2d(cmp)));
    d04 = d2i(_mm256_blendv_pd(i2d(d04), i2d(tmp), i2d(cmp)));

    tmp = d06;
    cmp = _mm256_cmpgt_epi64(d03, d06);
    d06 = d2i(_mm256_blendv_pd(i2d(d06), i2d(d03), i2d(cmp)));
    d03 = d2i(_mm256_blendv_pd(i2d(d03), i2d(tmp), i2d(cmp)));

    sort_04v_merge_descending(d01, d02, d03, d04);
    sort_02v_merge_descending(d05, d06);
}
    static NOINLINE void sort_06v_merge_ascending(__m256i& d01, __m256i& d02, __m256i& d03, __m256i& d04, __m256i& d05, __m256i& d06) {
    __m256i  tmp, cmp;

    tmp = d01;
    cmp = _mm256_cmpgt_epi64(d05, d01);
    d01 = d2i(_mm256_blendv_pd(i2d(d05), i2d(d01), i2d(cmp)));
    cmp = _mm256_cmpgt_epi64(d05, tmp);
    d05 = d2i(_mm256_blendv_pd(i2d(tmp), i2d(d05), i2d(cmp)));

    tmp = d02;
    cmp = _mm256_cmpgt_epi64(d06, d02);
    d02 = d2i(_mm256_blendv_pd(i2d(d06), i2d(d02), i2d(cmp)));
    cmp = _mm256_cmpgt_epi64(d06, tmp);
    d06 = d2i(_mm256_blendv_pd(i2d(tmp), i2d(d06), i2d(cmp)));

    sort_04v_merge_ascending(d01, d02, d03, d04);
    sort_02v_merge_ascending(d05, d06);
}
    static NOINLINE void sort_06v_merge_descending(__m256i& d01, __m256i& d02, __m256i& d03, __m256i& d04, __m256i& d05, __m256i& d06) {
    __m256i  tmp, cmp;

    tmp = d01;
    cmp = _mm256_cmpgt_epi64(d05, d01);
    d01 = d2i(_mm256_blendv_pd(i2d(d05), i2d(d01), i2d(cmp)));
    cmp = _mm256_cmpgt_epi64(d05, tmp);
    d05 = d2i(_mm256_blendv_pd(i2d(tmp), i2d(d05), i2d(cmp)));

    tmp = d02;
    cmp = _mm256_cmpgt_epi64(d06, d02);
    d02 = d2i(_mm256_blendv_pd(i2d(d06), i2d(d02), i2d(cmp)));
    cmp = _mm256_cmpgt_epi64(d06, tmp);
    d06 = d2i(_mm256_blendv_pd(i2d(tmp), i2d(d06), i2d(cmp)));

    sort_04v_merge_descending(d01, d02, d03, d04);
    sort_02v_merge_descending(d05, d06);
}
    static NOINLINE void sort_07v_ascending(__m256i& d01, __m256i& d02, __m256i& d03, __m256i& d04, __m256i& d05, __m256i& d06, __m256i& d07) {
    __m256i  tmp, cmp;

    sort_04v_ascending(d01, d02, d03, d04);
    sort_03v_descending(d05, d06, d07);

    tmp = d05;
    cmp = _mm256_cmpgt_epi64(d04, d05);
    d05 = d2i(_mm256_blendv_pd(i2d(d05), i2d(d04), i2d(cmp)));
    d04 = d2i(_mm256_blendv_pd(i2d(d04), i2d(tmp), i2d(cmp)));

    tmp = d06;
    cmp = _mm256_cmpgt_epi64(d03, d06);
    d06 = d2i(_mm256_blendv_pd(i2d(d06), i2d(d03), i2d(cmp)));
    d03 = d2i(_mm256_blendv_pd(i2d(d03), i2d(tmp), i2d(cmp)));

    tmp = d07;
    cmp = _mm256_cmpgt_epi64(d02, d07);
    d07 = d2i(_mm256_blendv_pd(i2d(d07), i2d(d02), i2d(cmp)));
    d02 = d2i(_mm256_blendv_pd(i2d(d02), i2d(tmp), i2d(cmp)));

    sort_04v_merge_ascending(d01, d02, d03, d04);
    sort_03v_merge_ascending(d05, d06, d07);
}
    static NOINLINE void sort_07v_descending(__m256i& d01, __m256i& d02, __m256i& d03, __m256i& d04, __m256i& d05, __m256i& d06, __m256i& d07) {
    __m256i  tmp, cmp;

    sort_04v_descending(d01, d02, d03, d04);
    sort_03v_ascending(d05, d06, d07);

    tmp = d05;
    cmp = _mm256_cmpgt_epi64(d04, d05);
    d05 = d2i(_mm256_blendv_pd(i2d(d05), i2d(d04), i2d(cmp)));
    d04 = d2i(_mm256_blendv_pd(i2d(d04), i2d(tmp), i2d(cmp)));

    tmp = d06;
    cmp = _mm256_cmpgt_epi64(d03, d06);
    d06 = d2i(_mm256_blendv_pd(i2d(d06), i2d(d03), i2d(cmp)));
    d03 = d2i(_mm256_blendv_pd(i2d(d03), i2d(tmp), i2d(cmp)));

    tmp = d07;
    cmp = _mm256_cmpgt_epi64(d02, d07);
    d07 = d2i(_mm256_blendv_pd(i2d(d07), i2d(d02), i2d(cmp)));
    d02 = d2i(_mm256_blendv_pd(i2d(d02), i2d(tmp), i2d(cmp)));

    sort_04v_merge_descending(d01, d02, d03, d04);
    sort_03v_merge_descending(d05, d06, d07);
}
    static NOINLINE void sort_07v_merge_ascending(__m256i& d01, __m256i& d02, __m256i& d03, __m256i& d04, __m256i& d05, __m256i& d06, __m256i& d07) {
    __m256i  tmp, cmp;

    tmp = d01;
    cmp = _mm256_cmpgt_epi64(d05, d01);
    d01 = d2i(_mm256_blendv_pd(i2d(d05), i2d(d01), i2d(cmp)));
    cmp = _mm256_cmpgt_epi64(d05, tmp);
    d05 = d2i(_mm256_blendv_pd(i2d(tmp), i2d(d05), i2d(cmp)));

    tmp = d02;
    cmp = _mm256_cmpgt_epi64(d06, d02);
    d02 = d2i(_mm256_blendv_pd(i2d(d06), i2d(d02), i2d(cmp)));
    cmp = _mm256_cmpgt_epi64(d06, tmp);
    d06 = d2i(_mm256_blendv_pd(i2d(tmp), i2d(d06), i2d(cmp)));

    tmp = d03;
    cmp = _mm256_cmpgt_epi64(d07, d03);
    d03 = d2i(_mm256_blendv_pd(i2d(d07), i2d(d03), i2d(cmp)));
    cmp = _mm256_cmpgt_epi64(d07, tmp);
    d07 = d2i(_mm256_blendv_pd(i2d(tmp), i2d(d07), i2d(cmp)));

    sort_04v_merge_ascending(d01, d02, d03, d04);
    sort_03v_merge_ascending(d05, d06, d07);
}
    static NOINLINE void sort_07v_merge_descending(__m256i& d01, __m256i& d02, __m256i& d03, __m256i& d04, __m256i& d05, __m256i& d06, __m256i& d07) {
    __m256i  tmp, cmp;

    tmp = d01;
    cmp = _mm256_cmpgt_epi64(d05, d01);
    d01 = d2i(_mm256_blendv_pd(i2d(d05), i2d(d01), i2d(cmp)));
    cmp = _mm256_cmpgt_epi64(d05, tmp);
    d05 = d2i(_mm256_blendv_pd(i2d(tmp), i2d(d05), i2d(cmp)));

    tmp = d02;
    cmp = _mm256_cmpgt_epi64(d06, d02);
    d02 = d2i(_mm256_blendv_pd(i2d(d06), i2d(d02), i2d(cmp)));
    cmp = _mm256_cmpgt_epi64(d06, tmp);
    d06 = d2i(_mm256_blendv_pd(i2d(tmp), i2d(d06), i2d(cmp)));

    tmp = d03;
    cmp = _mm256_cmpgt_epi64(d07, d03);
    d03 = d2i(_mm256_blendv_pd(i2d(d07), i2d(d03), i2d(cmp)));
    cmp = _mm256_cmpgt_epi64(d07, tmp);
    d07 = d2i(_mm256_blendv_pd(i2d(tmp), i2d(d07), i2d(cmp)));

    sort_04v_merge_descending(d01, d02, d03, d04);
    sort_03v_merge_descending(d05, d06, d07);
}
    static NOINLINE void sort_08v_ascending(__m256i& d01, __m256i& d02, __m256i& d03, __m256i& d04, __m256i& d05, __m256i& d06, __m256i& d07, __m256i& d08) {
    __m256i  tmp, cmp;

    sort_04v_ascending(d01, d02, d03, d04);
    sort_04v_descending(d05, d06, d07, d08);

    tmp = d05;
    cmp = _mm256_cmpgt_epi64(d04, d05);
    d05 = d2i(_mm256_blendv_pd(i2d(d05), i2d(d04), i2d(cmp)));
    d04 = d2i(_mm256_blendv_pd(i2d(d04), i2d(tmp), i2d(cmp)));

    tmp = d06;
    cmp = _mm256_cmpgt_epi64(d03, d06);
    d06 = d2i(_mm256_blendv_pd(i2d(d06), i2d(d03), i2d(cmp)));
    d03 = d2i(_mm256_blendv_pd(i2d(d03), i2d(tmp), i2d(cmp)));

    tmp = d07;
    cmp = _mm256_cmpgt_epi64(d02, d07);
    d07 = d2i(_mm256_blendv_pd(i2d(d07), i2d(d02), i2d(cmp)));
    d02 = d2i(_mm256_blendv_pd(i2d(d02), i2d(tmp), i2d(cmp)));

    tmp = d08;
    cmp = _mm256_cmpgt_epi64(d01, d08);
    d08 = d2i(_mm256_blendv_pd(i2d(d08), i2d(d01), i2d(cmp)));
    d01 = d2i(_mm256_blendv_pd(i2d(d01), i2d(tmp), i2d(cmp)));

    sort_04v_merge_ascending(d01, d02, d03, d04);
    sort_04v_merge_ascending(d05, d06, d07, d08);
}
    static NOINLINE void sort_08v_descending(__m256i& d01, __m256i& d02, __m256i& d03, __m256i& d04, __m256i& d05, __m256i& d06, __m256i& d07, __m256i& d08) {
    __m256i  tmp, cmp;

    sort_04v_descending(d01, d02, d03, d04);
    sort_04v_ascending(d05, d06, d07, d08);

    tmp = d05;
    cmp = _mm256_cmpgt_epi64(d04, d05);
    d05 = d2i(_mm256_blendv_pd(i2d(d05), i2d(d04), i2d(cmp)));
    d04 = d2i(_mm256_blendv_pd(i2d(d04), i2d(tmp), i2d(cmp)));

    tmp = d06;
    cmp = _mm256_cmpgt_epi64(d03, d06);
    d06 = d2i(_mm256_blendv_pd(i2d(d06), i2d(d03), i2d(cmp)));
    d03 = d2i(_mm256_blendv_pd(i2d(d03), i2d(tmp), i2d(cmp)));

    tmp = d07;
    cmp = _mm256_cmpgt_epi64(d02, d07);
    d07 = d2i(_mm256_blendv_pd(i2d(d07), i2d(d02), i2d(cmp)));
    d02 = d2i(_mm256_blendv_pd(i2d(d02), i2d(tmp), i2d(cmp)));

    tmp = d08;
    cmp = _mm256_cmpgt_epi64(d01, d08);
    d08 = d2i(_mm256_blendv_pd(i2d(d08), i2d(d01), i2d(cmp)));
    d01 = d2i(_mm256_blendv_pd(i2d(d01), i2d(tmp), i2d(cmp)));

    sort_04v_merge_descending(d01, d02, d03, d04);
    sort_04v_merge_descending(d05, d06, d07, d08);
}
    static NOINLINE void sort_08v_merge_ascending(__m256i& d01, __m256i& d02, __m256i& d03, __m256i& d04, __m256i& d05, __m256i& d06, __m256i& d07, __m256i& d08) {
    __m256i  tmp, cmp;

    tmp = d01;
    cmp = _mm256_cmpgt_epi64(d05, d01);
    d01 = d2i(_mm256_blendv_pd(i2d(d05), i2d(d01), i2d(cmp)));
    cmp = _mm256_cmpgt_epi64(d05, tmp);
    d05 = d2i(_mm256_blendv_pd(i2d(tmp), i2d(d05), i2d(cmp)));

    tmp = d02;
    cmp = _mm256_cmpgt_epi64(d06, d02);
    d02 = d2i(_mm256_blendv_pd(i2d(d06), i2d(d02), i2d(cmp)));
    cmp = _mm256_cmpgt_epi64(d06, tmp);
    d06 = d2i(_mm256_blendv_pd(i2d(tmp), i2d(d06), i2d(cmp)));

    tmp = d03;
    cmp = _mm256_cmpgt_epi64(d07, d03);
    d03 = d2i(_mm256_blendv_pd(i2d(d07), i2d(d03), i2d(cmp)));
    cmp = _mm256_cmpgt_epi64(d07, tmp);
    d07 = d2i(_mm256_blendv_pd(i2d(tmp), i2d(d07), i2d(cmp)));

    tmp = d04;
    cmp = _mm256_cmpgt_epi64(d08, d04);
    d04 = d2i(_mm256_blendv_pd(i2d(d08), i2d(d04), i2d(cmp)));
    cmp = _mm256_cmpgt_epi64(d08, tmp);
    d08 = d2i(_mm256_blendv_pd(i2d(tmp), i2d(d08), i2d(cmp)));

    sort_04v_merge_ascending(d01, d02, d03, d04);
    sort_04v_merge_ascending(d05, d06, d07, d08);
}
    static NOINLINE void sort_08v_merge_descending(__m256i& d01, __m256i& d02, __m256i& d03, __m256i& d04, __m256i& d05, __m256i& d06, __m256i& d07, __m256i& d08) {
    __m256i  tmp, cmp;

    tmp = d01;
    cmp = _mm256_cmpgt_epi64(d05, d01);
    d01 = d2i(_mm256_blendv_pd(i2d(d05), i2d(d01), i2d(cmp)));
    cmp = _mm256_cmpgt_epi64(d05, tmp);
    d05 = d2i(_mm256_blendv_pd(i2d(tmp), i2d(d05), i2d(cmp)));

    tmp = d02;
    cmp = _mm256_cmpgt_epi64(d06, d02);
    d02 = d2i(_mm256_blendv_pd(i2d(d06), i2d(d02), i2d(cmp)));
    cmp = _mm256_cmpgt_epi64(d06, tmp);
    d06 = d2i(_mm256_blendv_pd(i2d(tmp), i2d(d06), i2d(cmp)));

    tmp = d03;
    cmp = _mm256_cmpgt_epi64(d07, d03);
    d03 = d2i(_mm256_blendv_pd(i2d(d07), i2d(d03), i2d(cmp)));
    cmp = _mm256_cmpgt_epi64(d07, tmp);
    d07 = d2i(_mm256_blendv_pd(i2d(tmp), i2d(d07), i2d(cmp)));

    tmp = d04;
    cmp = _mm256_cmpgt_epi64(d08, d04);
    d04 = d2i(_mm256_blendv_pd(i2d(d08), i2d(d04), i2d(cmp)));
    cmp = _mm256_cmpgt_epi64(d08, tmp);
    d08 = d2i(_mm256_blendv_pd(i2d(tmp), i2d(d08), i2d(cmp)));

    sort_04v_merge_descending(d01, d02, d03, d04);
    sort_04v_merge_descending(d05, d06, d07, d08);
}
    static NOINLINE void sort_09v_ascending(__m256i& d01, __m256i& d02, __m256i& d03, __m256i& d04, __m256i& d05, __m256i& d06, __m256i& d07, __m256i& d08, __m256i& d09) {
    __m256i  tmp, cmp;

    sort_08v_ascending(d01, d02, d03, d04, d05, d06, d07, d08);
    sort_01v_descending(d09);

    tmp = d09;
    cmp = _mm256_cmpgt_epi64(d08, d09);
    d09 = d2i(_mm256_blendv_pd(i2d(d09), i2d(d08), i2d(cmp)));
    d08 = d2i(_mm256_blendv_pd(i2d(d08), i2d(tmp), i2d(cmp)));

    sort_08v_merge_ascending(d01, d02, d03, d04, d05, d06, d07, d08);
    sort_01v_merge_ascending(d09);
}
    static NOINLINE void sort_09v_descending(__m256i& d01, __m256i& d02, __m256i& d03, __m256i& d04, __m256i& d05, __m256i& d06, __m256i& d07, __m256i& d08, __m256i& d09) {
    __m256i  tmp, cmp;

    sort_08v_descending(d01, d02, d03, d04, d05, d06, d07, d08);
    sort_01v_ascending(d09);

    tmp = d09;
    cmp = _mm256_cmpgt_epi64(d08, d09);
    d09 = d2i(_mm256_blendv_pd(i2d(d09), i2d(d08), i2d(cmp)));
    d08 = d2i(_mm256_blendv_pd(i2d(d08), i2d(tmp), i2d(cmp)));

    sort_08v_merge_descending(d01, d02, d03, d04, d05, d06, d07, d08);
    sort_01v_merge_descending(d09);
}
    static NOINLINE void sort_10v_ascending(__m256i& d01, __m256i& d02, __m256i& d03, __m256i& d04, __m256i& d05, __m256i& d06, __m256i& d07, __m256i& d08, __m256i& d09, __m256i& d10) {
    __m256i  tmp, cmp;

    sort_08v_ascending(d01, d02, d03, d04, d05, d06, d07, d08);
    sort_02v_descending(d09, d10);

    tmp = d09;
    cmp = _mm256_cmpgt_epi64(d08, d09);
    d09 = d2i(_mm256_blendv_pd(i2d(d09), i2d(d08), i2d(cmp)));
    d08 = d2i(_mm256_blendv_pd(i2d(d08), i2d(tmp), i2d(cmp)));

    tmp = d10;
    cmp = _mm256_cmpgt_epi64(d07, d10);
    d10 = d2i(_mm256_blendv_pd(i2d(d10), i2d(d07), i2d(cmp)));
    d07 = d2i(_mm256_blendv_pd(i2d(d07), i2d(tmp), i2d(cmp)));

    sort_08v_merge_ascending(d01, d02, d03, d04, d05, d06, d07, d08);
    sort_02v_merge_ascending(d09, d10);
}
    static NOINLINE void sort_10v_descending(__m256i& d01, __m256i& d02, __m256i& d03, __m256i& d04, __m256i& d05, __m256i& d06, __m256i& d07, __m256i& d08, __m256i& d09, __m256i& d10) {
    __m256i  tmp, cmp;

    sort_08v_descending(d01, d02, d03, d04, d05, d06, d07, d08);
    sort_02v_ascending(d09, d10);

    tmp = d09;
    cmp = _mm256_cmpgt_epi64(d08, d09);
    d09 = d2i(_mm256_blendv_pd(i2d(d09), i2d(d08), i2d(cmp)));
    d08 = d2i(_mm256_blendv_pd(i2d(d08), i2d(tmp), i2d(cmp)));

    tmp = d10;
    cmp = _mm256_cmpgt_epi64(d07, d10);
    d10 = d2i(_mm256_blendv_pd(i2d(d10), i2d(d07), i2d(cmp)));
    d07 = d2i(_mm256_blendv_pd(i2d(d07), i2d(tmp), i2d(cmp)));

    sort_08v_merge_descending(d01, d02, d03, d04, d05, d06, d07, d08);
    sort_02v_merge_descending(d09, d10);
}
    static NOINLINE void sort_11v_ascending(__m256i& d01, __m256i& d02, __m256i& d03, __m256i& d04, __m256i& d05, __m256i& d06, __m256i& d07, __m256i& d08, __m256i& d09, __m256i& d10, __m256i& d11) {
    __m256i  tmp, cmp;

    sort_08v_ascending(d01, d02, d03, d04, d05, d06, d07, d08);
    sort_03v_descending(d09, d10, d11);

    tmp = d09;
    cmp = _mm256_cmpgt_epi64(d08, d09);
    d09 = d2i(_mm256_blendv_pd(i2d(d09), i2d(d08), i2d(cmp)));
    d08 = d2i(_mm256_blendv_pd(i2d(d08), i2d(tmp), i2d(cmp)));

    tmp = d10;
    cmp = _mm256_cmpgt_epi64(d07, d10);
    d10 = d2i(_mm256_blendv_pd(i2d(d10), i2d(d07), i2d(cmp)));
    d07 = d2i(_mm256_blendv_pd(i2d(d07), i2d(tmp), i2d(cmp)));

    tmp = d11;
    cmp = _mm256_cmpgt_epi64(d06, d11);
    d11 = d2i(_mm256_blendv_pd(i2d(d11), i2d(d06), i2d(cmp)));
    d06 = d2i(_mm256_blendv_pd(i2d(d06), i2d(tmp), i2d(cmp)));

    sort_08v_merge_ascending(d01, d02, d03, d04, d05, d06, d07, d08);
    sort_03v_merge_ascending(d09, d10, d11);
}
    static NOINLINE void sort_11v_descending(__m256i& d01, __m256i& d02, __m256i& d03, __m256i& d04, __m256i& d05, __m256i& d06, __m256i& d07, __m256i& d08, __m256i& d09, __m256i& d10, __m256i& d11) {
    __m256i  tmp, cmp;

    sort_08v_descending(d01, d02, d03, d04, d05, d06, d07, d08);
    sort_03v_ascending(d09, d10, d11);

    tmp = d09;
    cmp = _mm256_cmpgt_epi64(d08, d09);
    d09 = d2i(_mm256_blendv_pd(i2d(d09), i2d(d08), i2d(cmp)));
    d08 = d2i(_mm256_blendv_pd(i2d(d08), i2d(tmp), i2d(cmp)));

    tmp = d10;
    cmp = _mm256_cmpgt_epi64(d07, d10);
    d10 = d2i(_mm256_blendv_pd(i2d(d10), i2d(d07), i2d(cmp)));
    d07 = d2i(_mm256_blendv_pd(i2d(d07), i2d(tmp), i2d(cmp)));

    tmp = d11;
    cmp = _mm256_cmpgt_epi64(d06, d11);
    d11 = d2i(_mm256_blendv_pd(i2d(d11), i2d(d06), i2d(cmp)));
    d06 = d2i(_mm256_blendv_pd(i2d(d06), i2d(tmp), i2d(cmp)));

    sort_08v_merge_descending(d01, d02, d03, d04, d05, d06, d07, d08);
    sort_03v_merge_descending(d09, d10, d11);
}
    static NOINLINE void sort_12v_ascending(__m256i& d01, __m256i& d02, __m256i& d03, __m256i& d04, __m256i& d05, __m256i& d06, __m256i& d07, __m256i& d08, __m256i& d09, __m256i& d10, __m256i& d11, __m256i& d12) {
    __m256i  tmp, cmp;

    sort_08v_ascending(d01, d02, d03, d04, d05, d06, d07, d08);
    sort_04v_descending(d09, d10, d11, d12);

    tmp = d09;
    cmp = _mm256_cmpgt_epi64(d08, d09);
    d09 = d2i(_mm256_blendv_pd(i2d(d09), i2d(d08), i2d(cmp)));
    d08 = d2i(_mm256_blendv_pd(i2d(d08), i2d(tmp), i2d(cmp)));

    tmp = d10;
    cmp = _mm256_cmpgt_epi64(d07, d10);
    d10 = d2i(_mm256_blendv_pd(i2d(d10), i2d(d07), i2d(cmp)));
    d07 = d2i(_mm256_blendv_pd(i2d(d07), i2d(tmp), i2d(cmp)));

    tmp = d11;
    cmp = _mm256_cmpgt_epi64(d06, d11);
    d11 = d2i(_mm256_blendv_pd(i2d(d11), i2d(d06), i2d(cmp)));
    d06 = d2i(_mm256_blendv_pd(i2d(d06), i2d(tmp), i2d(cmp)));

    tmp = d12;
    cmp = _mm256_cmpgt_epi64(d05, d12);
    d12 = d2i(_mm256_blendv_pd(i2d(d12), i2d(d05), i2d(cmp)));
    d05 = d2i(_mm256_blendv_pd(i2d(d05), i2d(tmp), i2d(cmp)));

    sort_08v_merge_ascending(d01, d02, d03, d04, d05, d06, d07, d08);
    sort_04v_merge_ascending(d09, d10, d11, d12);
}
    static NOINLINE void sort_12v_descending(__m256i& d01, __m256i& d02, __m256i& d03, __m256i& d04, __m256i& d05, __m256i& d06, __m256i& d07, __m256i& d08, __m256i& d09, __m256i& d10, __m256i& d11, __m256i& d12) {
    __m256i  tmp, cmp;

    sort_08v_descending(d01, d02, d03, d04, d05, d06, d07, d08);
    sort_04v_ascending(d09, d10, d11, d12);

    tmp = d09;
    cmp = _mm256_cmpgt_epi64(d08, d09);
    d09 = d2i(_mm256_blendv_pd(i2d(d09), i2d(d08), i2d(cmp)));
    d08 = d2i(_mm256_blendv_pd(i2d(d08), i2d(tmp), i2d(cmp)));

    tmp = d10;
    cmp = _mm256_cmpgt_epi64(d07, d10);
    d10 = d2i(_mm256_blendv_pd(i2d(d10), i2d(d07), i2d(cmp)));
    d07 = d2i(_mm256_blendv_pd(i2d(d07), i2d(tmp), i2d(cmp)));

    tmp = d11;
    cmp = _mm256_cmpgt_epi64(d06, d11);
    d11 = d2i(_mm256_blendv_pd(i2d(d11), i2d(d06), i2d(cmp)));
    d06 = d2i(_mm256_blendv_pd(i2d(d06), i2d(tmp), i2d(cmp)));

    tmp = d12;
    cmp = _mm256_cmpgt_epi64(d05, d12);
    d12 = d2i(_mm256_blendv_pd(i2d(d12), i2d(d05), i2d(cmp)));
    d05 = d2i(_mm256_blendv_pd(i2d(d05), i2d(tmp), i2d(cmp)));

    sort_08v_merge_descending(d01, d02, d03, d04, d05, d06, d07, d08);
    sort_04v_merge_descending(d09, d10, d11, d12);
}
    static NOINLINE void sort_13v_ascending(__m256i& d01, __m256i& d02, __m256i& d03, __m256i& d04, __m256i& d05, __m256i& d06, __m256i& d07, __m256i& d08, __m256i& d09, __m256i& d10, __m256i& d11, __m256i& d12, __m256i& d13) {
    __m256i  tmp, cmp;

    sort_08v_ascending(d01, d02, d03, d04, d05, d06, d07, d08);
    sort_05v_descending(d09, d10, d11, d12, d13);

    tmp = d09;
    cmp = _mm256_cmpgt_epi64(d08, d09);
    d09 = d2i(_mm256_blendv_pd(i2d(d09), i2d(d08), i2d(cmp)));
    d08 = d2i(_mm256_blendv_pd(i2d(d08), i2d(tmp), i2d(cmp)));

    tmp = d10;
    cmp = _mm256_cmpgt_epi64(d07, d10);
    d10 = d2i(_mm256_blendv_pd(i2d(d10), i2d(d07), i2d(cmp)));
    d07 = d2i(_mm256_blendv_pd(i2d(d07), i2d(tmp), i2d(cmp)));

    tmp = d11;
    cmp = _mm256_cmpgt_epi64(d06, d11);
    d11 = d2i(_mm256_blendv_pd(i2d(d11), i2d(d06), i2d(cmp)));
    d06 = d2i(_mm256_blendv_pd(i2d(d06), i2d(tmp), i2d(cmp)));

    tmp = d12;
    cmp = _mm256_cmpgt_epi64(d05, d12);
    d12 = d2i(_mm256_blendv_pd(i2d(d12), i2d(d05), i2d(cmp)));
    d05 = d2i(_mm256_blendv_pd(i2d(d05), i2d(tmp), i2d(cmp)));

    tmp = d13;
    cmp = _mm256_cmpgt_epi64(d04, d13);
    d13 = d2i(_mm256_blendv_pd(i2d(d13), i2d(d04), i2d(cmp)));
    d04 = d2i(_mm256_blendv_pd(i2d(d04), i2d(tmp), i2d(cmp)));

    sort_08v_merge_ascending(d01, d02, d03, d04, d05, d06, d07, d08);
    sort_05v_merge_ascending(d09, d10, d11, d12, d13);
}
    static NOINLINE void sort_13v_descending(__m256i& d01, __m256i& d02, __m256i& d03, __m256i& d04, __m256i& d05, __m256i& d06, __m256i& d07, __m256i& d08, __m256i& d09, __m256i& d10, __m256i& d11, __m256i& d12, __m256i& d13) {
    __m256i  tmp, cmp;

    sort_08v_descending(d01, d02, d03, d04, d05, d06, d07, d08);
    sort_05v_ascending(d09, d10, d11, d12, d13);

    tmp = d09;
    cmp = _mm256_cmpgt_epi64(d08, d09);
    d09 = d2i(_mm256_blendv_pd(i2d(d09), i2d(d08), i2d(cmp)));
    d08 = d2i(_mm256_blendv_pd(i2d(d08), i2d(tmp), i2d(cmp)));

    tmp = d10;
    cmp = _mm256_cmpgt_epi64(d07, d10);
    d10 = d2i(_mm256_blendv_pd(i2d(d10), i2d(d07), i2d(cmp)));
    d07 = d2i(_mm256_blendv_pd(i2d(d07), i2d(tmp), i2d(cmp)));

    tmp = d11;
    cmp = _mm256_cmpgt_epi64(d06, d11);
    d11 = d2i(_mm256_blendv_pd(i2d(d11), i2d(d06), i2d(cmp)));
    d06 = d2i(_mm256_blendv_pd(i2d(d06), i2d(tmp), i2d(cmp)));

    tmp = d12;
    cmp = _mm256_cmpgt_epi64(d05, d12);
    d12 = d2i(_mm256_blendv_pd(i2d(d12), i2d(d05), i2d(cmp)));
    d05 = d2i(_mm256_blendv_pd(i2d(d05), i2d(tmp), i2d(cmp)));

    tmp = d13;
    cmp = _mm256_cmpgt_epi64(d04, d13);
    d13 = d2i(_mm256_blendv_pd(i2d(d13), i2d(d04), i2d(cmp)));
    d04 = d2i(_mm256_blendv_pd(i2d(d04), i2d(tmp), i2d(cmp)));

    sort_08v_merge_descending(d01, d02, d03, d04, d05, d06, d07, d08);
    sort_05v_merge_descending(d09, d10, d11, d12, d13);
}
    static NOINLINE void sort_14v_ascending(__m256i& d01, __m256i& d02, __m256i& d03, __m256i& d04, __m256i& d05, __m256i& d06, __m256i& d07, __m256i& d08, __m256i& d09, __m256i& d10, __m256i& d11, __m256i& d12, __m256i& d13, __m256i& d14) {
    __m256i  tmp, cmp;

    sort_08v_ascending(d01, d02, d03, d04, d05, d06, d07, d08);
    sort_06v_descending(d09, d10, d11, d12, d13, d14);

    tmp = d09;
    cmp = _mm256_cmpgt_epi64(d08, d09);
    d09 = d2i(_mm256_blendv_pd(i2d(d09), i2d(d08), i2d(cmp)));
    d08 = d2i(_mm256_blendv_pd(i2d(d08), i2d(tmp), i2d(cmp)));

    tmp = d10;
    cmp = _mm256_cmpgt_epi64(d07, d10);
    d10 = d2i(_mm256_blendv_pd(i2d(d10), i2d(d07), i2d(cmp)));
    d07 = d2i(_mm256_blendv_pd(i2d(d07), i2d(tmp), i2d(cmp)));

    tmp = d11;
    cmp = _mm256_cmpgt_epi64(d06, d11);
    d11 = d2i(_mm256_blendv_pd(i2d(d11), i2d(d06), i2d(cmp)));
    d06 = d2i(_mm256_blendv_pd(i2d(d06), i2d(tmp), i2d(cmp)));

    tmp = d12;
    cmp = _mm256_cmpgt_epi64(d05, d12);
    d12 = d2i(_mm256_blendv_pd(i2d(d12), i2d(d05), i2d(cmp)));
    d05 = d2i(_mm256_blendv_pd(i2d(d05), i2d(tmp), i2d(cmp)));

    tmp = d13;
    cmp = _mm256_cmpgt_epi64(d04, d13);
    d13 = d2i(_mm256_blendv_pd(i2d(d13), i2d(d04), i2d(cmp)));
    d04 = d2i(_mm256_blendv_pd(i2d(d04), i2d(tmp), i2d(cmp)));

    tmp = d14;
    cmp = _mm256_cmpgt_epi64(d03, d14);
    d14 = d2i(_mm256_blendv_pd(i2d(d14), i2d(d03), i2d(cmp)));
    d03 = d2i(_mm256_blendv_pd(i2d(d03), i2d(tmp), i2d(cmp)));

    sort_08v_merge_ascending(d01, d02, d03, d04, d05, d06, d07, d08);
    sort_06v_merge_ascending(d09, d10, d11, d12, d13, d14);
}
    static NOINLINE void sort_14v_descending(__m256i& d01, __m256i& d02, __m256i& d03, __m256i& d04, __m256i& d05, __m256i& d06, __m256i& d07, __m256i& d08, __m256i& d09, __m256i& d10, __m256i& d11, __m256i& d12, __m256i& d13, __m256i& d14) {
    __m256i  tmp, cmp;

    sort_08v_descending(d01, d02, d03, d04, d05, d06, d07, d08);
    sort_06v_ascending(d09, d10, d11, d12, d13, d14);

    tmp = d09;
    cmp = _mm256_cmpgt_epi64(d08, d09);
    d09 = d2i(_mm256_blendv_pd(i2d(d09), i2d(d08), i2d(cmp)));
    d08 = d2i(_mm256_blendv_pd(i2d(d08), i2d(tmp), i2d(cmp)));

    tmp = d10;
    cmp = _mm256_cmpgt_epi64(d07, d10);
    d10 = d2i(_mm256_blendv_pd(i2d(d10), i2d(d07), i2d(cmp)));
    d07 = d2i(_mm256_blendv_pd(i2d(d07), i2d(tmp), i2d(cmp)));

    tmp = d11;
    cmp = _mm256_cmpgt_epi64(d06, d11);
    d11 = d2i(_mm256_blendv_pd(i2d(d11), i2d(d06), i2d(cmp)));
    d06 = d2i(_mm256_blendv_pd(i2d(d06), i2d(tmp), i2d(cmp)));

    tmp = d12;
    cmp = _mm256_cmpgt_epi64(d05, d12);
    d12 = d2i(_mm256_blendv_pd(i2d(d12), i2d(d05), i2d(cmp)));
    d05 = d2i(_mm256_blendv_pd(i2d(d05), i2d(tmp), i2d(cmp)));

    tmp = d13;
    cmp = _mm256_cmpgt_epi64(d04, d13);
    d13 = d2i(_mm256_blendv_pd(i2d(d13), i2d(d04), i2d(cmp)));
    d04 = d2i(_mm256_blendv_pd(i2d(d04), i2d(tmp), i2d(cmp)));

    tmp = d14;
    cmp = _mm256_cmpgt_epi64(d03, d14);
    d14 = d2i(_mm256_blendv_pd(i2d(d14), i2d(d03), i2d(cmp)));
    d03 = d2i(_mm256_blendv_pd(i2d(d03), i2d(tmp), i2d(cmp)));

    sort_08v_merge_descending(d01, d02, d03, d04, d05, d06, d07, d08);
    sort_06v_merge_descending(d09, d10, d11, d12, d13, d14);
}
    static NOINLINE void sort_15v_ascending(__m256i& d01, __m256i& d02, __m256i& d03, __m256i& d04, __m256i& d05, __m256i& d06, __m256i& d07, __m256i& d08, __m256i& d09, __m256i& d10, __m256i& d11, __m256i& d12, __m256i& d13, __m256i& d14, __m256i& d15) {
    __m256i  tmp, cmp;

    sort_08v_ascending(d01, d02, d03, d04, d05, d06, d07, d08);
    sort_07v_descending(d09, d10, d11, d12, d13, d14, d15);

    tmp = d09;
    cmp = _mm256_cmpgt_epi64(d08, d09);
    d09 = d2i(_mm256_blendv_pd(i2d(d09), i2d(d08), i2d(cmp)));
    d08 = d2i(_mm256_blendv_pd(i2d(d08), i2d(tmp), i2d(cmp)));

    tmp = d10;
    cmp = _mm256_cmpgt_epi64(d07, d10);
    d10 = d2i(_mm256_blendv_pd(i2d(d10), i2d(d07), i2d(cmp)));
    d07 = d2i(_mm256_blendv_pd(i2d(d07), i2d(tmp), i2d(cmp)));

    tmp = d11;
    cmp = _mm256_cmpgt_epi64(d06, d11);
    d11 = d2i(_mm256_blendv_pd(i2d(d11), i2d(d06), i2d(cmp)));
    d06 = d2i(_mm256_blendv_pd(i2d(d06), i2d(tmp), i2d(cmp)));

    tmp = d12;
    cmp = _mm256_cmpgt_epi64(d05, d12);
    d12 = d2i(_mm256_blendv_pd(i2d(d12), i2d(d05), i2d(cmp)));
    d05 = d2i(_mm256_blendv_pd(i2d(d05), i2d(tmp), i2d(cmp)));

    tmp = d13;
    cmp = _mm256_cmpgt_epi64(d04, d13);
    d13 = d2i(_mm256_blendv_pd(i2d(d13), i2d(d04), i2d(cmp)));
    d04 = d2i(_mm256_blendv_pd(i2d(d04), i2d(tmp), i2d(cmp)));

    tmp = d14;
    cmp = _mm256_cmpgt_epi64(d03, d14);
    d14 = d2i(_mm256_blendv_pd(i2d(d14), i2d(d03), i2d(cmp)));
    d03 = d2i(_mm256_blendv_pd(i2d(d03), i2d(tmp), i2d(cmp)));

    tmp = d15;
    cmp = _mm256_cmpgt_epi64(d02, d15);
    d15 = d2i(_mm256_blendv_pd(i2d(d15), i2d(d02), i2d(cmp)));
    d02 = d2i(_mm256_blendv_pd(i2d(d02), i2d(tmp), i2d(cmp)));

    sort_08v_merge_ascending(d01, d02, d03, d04, d05, d06, d07, d08);
    sort_07v_merge_ascending(d09, d10, d11, d12, d13, d14, d15);
}
    static NOINLINE void sort_15v_descending(__m256i& d01, __m256i& d02, __m256i& d03, __m256i& d04, __m256i& d05, __m256i& d06, __m256i& d07, __m256i& d08, __m256i& d09, __m256i& d10, __m256i& d11, __m256i& d12, __m256i& d13, __m256i& d14, __m256i& d15) {
    __m256i  tmp, cmp;

    sort_08v_descending(d01, d02, d03, d04, d05, d06, d07, d08);
    sort_07v_ascending(d09, d10, d11, d12, d13, d14, d15);

    tmp = d09;
    cmp = _mm256_cmpgt_epi64(d08, d09);
    d09 = d2i(_mm256_blendv_pd(i2d(d09), i2d(d08), i2d(cmp)));
    d08 = d2i(_mm256_blendv_pd(i2d(d08), i2d(tmp), i2d(cmp)));

    tmp = d10;
    cmp = _mm256_cmpgt_epi64(d07, d10);
    d10 = d2i(_mm256_blendv_pd(i2d(d10), i2d(d07), i2d(cmp)));
    d07 = d2i(_mm256_blendv_pd(i2d(d07), i2d(tmp), i2d(cmp)));

    tmp = d11;
    cmp = _mm256_cmpgt_epi64(d06, d11);
    d11 = d2i(_mm256_blendv_pd(i2d(d11), i2d(d06), i2d(cmp)));
    d06 = d2i(_mm256_blendv_pd(i2d(d06), i2d(tmp), i2d(cmp)));

    tmp = d12;
    cmp = _mm256_cmpgt_epi64(d05, d12);
    d12 = d2i(_mm256_blendv_pd(i2d(d12), i2d(d05), i2d(cmp)));
    d05 = d2i(_mm256_blendv_pd(i2d(d05), i2d(tmp), i2d(cmp)));

    tmp = d13;
    cmp = _mm256_cmpgt_epi64(d04, d13);
    d13 = d2i(_mm256_blendv_pd(i2d(d13), i2d(d04), i2d(cmp)));
    d04 = d2i(_mm256_blendv_pd(i2d(d04), i2d(tmp), i2d(cmp)));

    tmp = d14;
    cmp = _mm256_cmpgt_epi64(d03, d14);
    d14 = d2i(_mm256_blendv_pd(i2d(d14), i2d(d03), i2d(cmp)));
    d03 = d2i(_mm256_blendv_pd(i2d(d03), i2d(tmp), i2d(cmp)));

    tmp = d15;
    cmp = _mm256_cmpgt_epi64(d02, d15);
    d15 = d2i(_mm256_blendv_pd(i2d(d15), i2d(d02), i2d(cmp)));
    d02 = d2i(_mm256_blendv_pd(i2d(d02), i2d(tmp), i2d(cmp)));

    sort_08v_merge_descending(d01, d02, d03, d04, d05, d06, d07, d08);
    sort_07v_merge_descending(d09, d10, d11, d12, d13, d14, d15);
}
    static NOINLINE void sort_16v_ascending(__m256i& d01, __m256i& d02, __m256i& d03, __m256i& d04, __m256i& d05, __m256i& d06, __m256i& d07, __m256i& d08, __m256i& d09, __m256i& d10, __m256i& d11, __m256i& d12, __m256i& d13, __m256i& d14, __m256i& d15, __m256i& d16) {
    __m256i  tmp, cmp;

    sort_08v_ascending(d01, d02, d03, d04, d05, d06, d07, d08);
    sort_08v_descending(d09, d10, d11, d12, d13, d14, d15, d16);

    tmp = d09;
    cmp = _mm256_cmpgt_epi64(d08, d09);
    d09 = d2i(_mm256_blendv_pd(i2d(d09), i2d(d08), i2d(cmp)));
    d08 = d2i(_mm256_blendv_pd(i2d(d08), i2d(tmp), i2d(cmp)));

    tmp = d10;
    cmp = _mm256_cmpgt_epi64(d07, d10);
    d10 = d2i(_mm256_blendv_pd(i2d(d10), i2d(d07), i2d(cmp)));
    d07 = d2i(_mm256_blendv_pd(i2d(d07), i2d(tmp), i2d(cmp)));

    tmp = d11;
    cmp = _mm256_cmpgt_epi64(d06, d11);
    d11 = d2i(_mm256_blendv_pd(i2d(d11), i2d(d06), i2d(cmp)));
    d06 = d2i(_mm256_blendv_pd(i2d(d06), i2d(tmp), i2d(cmp)));

    tmp = d12;
    cmp = _mm256_cmpgt_epi64(d05, d12);
    d12 = d2i(_mm256_blendv_pd(i2d(d12), i2d(d05), i2d(cmp)));
    d05 = d2i(_mm256_blendv_pd(i2d(d05), i2d(tmp), i2d(cmp)));

    tmp = d13;
    cmp = _mm256_cmpgt_epi64(d04, d13);
    d13 = d2i(_mm256_blendv_pd(i2d(d13), i2d(d04), i2d(cmp)));
    d04 = d2i(_mm256_blendv_pd(i2d(d04), i2d(tmp), i2d(cmp)));

    tmp = d14;
    cmp = _mm256_cmpgt_epi64(d03, d14);
    d14 = d2i(_mm256_blendv_pd(i2d(d14), i2d(d03), i2d(cmp)));
    d03 = d2i(_mm256_blendv_pd(i2d(d03), i2d(tmp), i2d(cmp)));

    tmp = d15;
    cmp = _mm256_cmpgt_epi64(d02, d15);
    d15 = d2i(_mm256_blendv_pd(i2d(d15), i2d(d02), i2d(cmp)));
    d02 = d2i(_mm256_blendv_pd(i2d(d02), i2d(tmp), i2d(cmp)));

    tmp = d16;
    cmp = _mm256_cmpgt_epi64(d01, d16);
    d16 = d2i(_mm256_blendv_pd(i2d(d16), i2d(d01), i2d(cmp)));
    d01 = d2i(_mm256_blendv_pd(i2d(d01), i2d(tmp), i2d(cmp)));

    sort_08v_merge_ascending(d01, d02, d03, d04, d05, d06, d07, d08);
    sort_08v_merge_ascending(d09, d10, d11, d12, d13, d14, d15, d16);
}
    static NOINLINE void sort_16v_descending(__m256i& d01, __m256i& d02, __m256i& d03, __m256i& d04, __m256i& d05, __m256i& d06, __m256i& d07, __m256i& d08, __m256i& d09, __m256i& d10, __m256i& d11, __m256i& d12, __m256i& d13, __m256i& d14, __m256i& d15, __m256i& d16) {
    __m256i  tmp, cmp;

    sort_08v_descending(d01, d02, d03, d04, d05, d06, d07, d08);
    sort_08v_ascending(d09, d10, d11, d12, d13, d14, d15, d16);

    tmp = d09;
    cmp = _mm256_cmpgt_epi64(d08, d09);
    d09 = d2i(_mm256_blendv_pd(i2d(d09), i2d(d08), i2d(cmp)));
    d08 = d2i(_mm256_blendv_pd(i2d(d08), i2d(tmp), i2d(cmp)));

    tmp = d10;
    cmp = _mm256_cmpgt_epi64(d07, d10);
    d10 = d2i(_mm256_blendv_pd(i2d(d10), i2d(d07), i2d(cmp)));
    d07 = d2i(_mm256_blendv_pd(i2d(d07), i2d(tmp), i2d(cmp)));

    tmp = d11;
    cmp = _mm256_cmpgt_epi64(d06, d11);
    d11 = d2i(_mm256_blendv_pd(i2d(d11), i2d(d06), i2d(cmp)));
    d06 = d2i(_mm256_blendv_pd(i2d(d06), i2d(tmp), i2d(cmp)));

    tmp = d12;
    cmp = _mm256_cmpgt_epi64(d05, d12);
    d12 = d2i(_mm256_blendv_pd(i2d(d12), i2d(d05), i2d(cmp)));
    d05 = d2i(_mm256_blendv_pd(i2d(d05), i2d(tmp), i2d(cmp)));

    tmp = d13;
    cmp = _mm256_cmpgt_epi64(d04, d13);
    d13 = d2i(_mm256_blendv_pd(i2d(d13), i2d(d04), i2d(cmp)));
    d04 = d2i(_mm256_blendv_pd(i2d(d04), i2d(tmp), i2d(cmp)));

    tmp = d14;
    cmp = _mm256_cmpgt_epi64(d03, d14);
    d14 = d2i(_mm256_blendv_pd(i2d(d14), i2d(d03), i2d(cmp)));
    d03 = d2i(_mm256_blendv_pd(i2d(d03), i2d(tmp), i2d(cmp)));

    tmp = d15;
    cmp = _mm256_cmpgt_epi64(d02, d15);
    d15 = d2i(_mm256_blendv_pd(i2d(d15), i2d(d02), i2d(cmp)));
    d02 = d2i(_mm256_blendv_pd(i2d(d02), i2d(tmp), i2d(cmp)));

    tmp = d16;
    cmp = _mm256_cmpgt_epi64(d01, d16);
    d16 = d2i(_mm256_blendv_pd(i2d(d16), i2d(d01), i2d(cmp)));
    d01 = d2i(_mm256_blendv_pd(i2d(d01), i2d(tmp), i2d(cmp)));

    sort_08v_merge_descending(d01, d02, d03, d04, d05, d06, d07, d08);
    sort_08v_merge_descending(d09, d10, d11, d12, d13, d14, d15, d16);
}

static NOINLINE void sort_01v(int64_t *ptr) {
    __m256i d01 = _mm256_lddqu_si256((__m256i const *) ptr + 0);
    sort_01v_ascending(d01);
    _mm256_storeu_si256((__m256i *) ptr + 0, d01);
}

static NOINLINE void sort_02v(int64_t *ptr) {
    __m256i d01 = _mm256_lddqu_si256((__m256i const *) ptr + 0);
    __m256i d02 = _mm256_lddqu_si256((__m256i const *) ptr + 1);
    sort_02v_ascending(d01, d02);
    _mm256_storeu_si256((__m256i *) ptr + 0, d01);
    _mm256_storeu_si256((__m256i *) ptr + 1, d02);
}

static NOINLINE void sort_03v(int64_t *ptr) {
    __m256i d01 = _mm256_lddqu_si256((__m256i const *) ptr + 0);
    __m256i d02 = _mm256_lddqu_si256((__m256i const *) ptr + 1);
    __m256i d03 = _mm256_lddqu_si256((__m256i const *) ptr + 2);
    sort_03v_ascending(d01, d02, d03);
    _mm256_storeu_si256((__m256i *) ptr + 0, d01);
    _mm256_storeu_si256((__m256i *) ptr + 1, d02);
    _mm256_storeu_si256((__m256i *) ptr + 2, d03);
}

static NOINLINE void sort_04v(int64_t *ptr) {
    __m256i d01 = _mm256_lddqu_si256((__m256i const *) ptr + 0);
    __m256i d02 = _mm256_lddqu_si256((__m256i const *) ptr + 1);
    __m256i d03 = _mm256_lddqu_si256((__m256i const *) ptr + 2);
    __m256i d04 = _mm256_lddqu_si256((__m256i const *) ptr + 3);
    sort_04v_ascending(d01, d02, d03, d04);
    _mm256_storeu_si256((__m256i *) ptr + 0, d01);
    _mm256_storeu_si256((__m256i *) ptr + 1, d02);
    _mm256_storeu_si256((__m256i *) ptr + 2, d03);
    _mm256_storeu_si256((__m256i *) ptr + 3, d04);
}

static NOINLINE void sort_05v(int64_t *ptr) {
    __m256i d01 = _mm256_lddqu_si256((__m256i const *) ptr + 0);
    __m256i d02 = _mm256_lddqu_si256((__m256i const *) ptr + 1);
    __m256i d03 = _mm256_lddqu_si256((__m256i const *) ptr + 2);
    __m256i d04 = _mm256_lddqu_si256((__m256i const *) ptr + 3);
    __m256i d05 = _mm256_lddqu_si256((__m256i const *) ptr + 4);
    sort_05v_ascending(d01, d02, d03, d04, d05);
    _mm256_storeu_si256((__m256i *) ptr + 0, d01);
    _mm256_storeu_si256((__m256i *) ptr + 1, d02);
    _mm256_storeu_si256((__m256i *) ptr + 2, d03);
    _mm256_storeu_si256((__m256i *) ptr + 3, d04);
    _mm256_storeu_si256((__m256i *) ptr + 4, d05);
}

static NOINLINE void sort_06v(int64_t *ptr) {
    __m256i d01 = _mm256_lddqu_si256((__m256i const *) ptr + 0);
    __m256i d02 = _mm256_lddqu_si256((__m256i const *) ptr + 1);
    __m256i d03 = _mm256_lddqu_si256((__m256i const *) ptr + 2);
    __m256i d04 = _mm256_lddqu_si256((__m256i const *) ptr + 3);
    __m256i d05 = _mm256_lddqu_si256((__m256i const *) ptr + 4);
    __m256i d06 = _mm256_lddqu_si256((__m256i const *) ptr + 5);
    sort_06v_ascending(d01, d02, d03, d04, d05, d06);
    _mm256_storeu_si256((__m256i *) ptr + 0, d01);
    _mm256_storeu_si256((__m256i *) ptr + 1, d02);
    _mm256_storeu_si256((__m256i *) ptr + 2, d03);
    _mm256_storeu_si256((__m256i *) ptr + 3, d04);
    _mm256_storeu_si256((__m256i *) ptr + 4, d05);
    _mm256_storeu_si256((__m256i *) ptr + 5, d06);
}

static NOINLINE void sort_07v(int64_t *ptr) {
    __m256i d01 = _mm256_lddqu_si256((__m256i const *) ptr + 0);
    __m256i d02 = _mm256_lddqu_si256((__m256i const *) ptr + 1);
    __m256i d03 = _mm256_lddqu_si256((__m256i const *) ptr + 2);
    __m256i d04 = _mm256_lddqu_si256((__m256i const *) ptr + 3);
    __m256i d05 = _mm256_lddqu_si256((__m256i const *) ptr + 4);
    __m256i d06 = _mm256_lddqu_si256((__m256i const *) ptr + 5);
    __m256i d07 = _mm256_lddqu_si256((__m256i const *) ptr + 6);
    sort_07v_ascending(d01, d02, d03, d04, d05, d06, d07);
    _mm256_storeu_si256((__m256i *) ptr + 0, d01);
    _mm256_storeu_si256((__m256i *) ptr + 1, d02);
    _mm256_storeu_si256((__m256i *) ptr + 2, d03);
    _mm256_storeu_si256((__m256i *) ptr + 3, d04);
    _mm256_storeu_si256((__m256i *) ptr + 4, d05);
    _mm256_storeu_si256((__m256i *) ptr + 5, d06);
    _mm256_storeu_si256((__m256i *) ptr + 6, d07);
}

static NOINLINE void sort_08v(int64_t *ptr) {
    __m256i d01 = _mm256_lddqu_si256((__m256i const *) ptr + 0);
    __m256i d02 = _mm256_lddqu_si256((__m256i const *) ptr + 1);
    __m256i d03 = _mm256_lddqu_si256((__m256i const *) ptr + 2);
    __m256i d04 = _mm256_lddqu_si256((__m256i const *) ptr + 3);
    __m256i d05 = _mm256_lddqu_si256((__m256i const *) ptr + 4);
    __m256i d06 = _mm256_lddqu_si256((__m256i const *) ptr + 5);
    __m256i d07 = _mm256_lddqu_si256((__m256i const *) ptr + 6);
    __m256i d08 = _mm256_lddqu_si256((__m256i const *) ptr + 7);
    sort_08v_ascending(d01, d02, d03, d04, d05, d06, d07, d08);
    _mm256_storeu_si256((__m256i *) ptr + 0, d01);
    _mm256_storeu_si256((__m256i *) ptr + 1, d02);
    _mm256_storeu_si256((__m256i *) ptr + 2, d03);
    _mm256_storeu_si256((__m256i *) ptr + 3, d04);
    _mm256_storeu_si256((__m256i *) ptr + 4, d05);
    _mm256_storeu_si256((__m256i *) ptr + 5, d06);
    _mm256_storeu_si256((__m256i *) ptr + 6, d07);
    _mm256_storeu_si256((__m256i *) ptr + 7, d08);
}

static NOINLINE void sort_09v(int64_t *ptr) {
    __m256i d01 = _mm256_lddqu_si256((__m256i const *) ptr + 0);
    __m256i d02 = _mm256_lddqu_si256((__m256i const *) ptr + 1);
    __m256i d03 = _mm256_lddqu_si256((__m256i const *) ptr + 2);
    __m256i d04 = _mm256_lddqu_si256((__m256i const *) ptr + 3);
    __m256i d05 = _mm256_lddqu_si256((__m256i const *) ptr + 4);
    __m256i d06 = _mm256_lddqu_si256((__m256i const *) ptr + 5);
    __m256i d07 = _mm256_lddqu_si256((__m256i const *) ptr + 6);
    __m256i d08 = _mm256_lddqu_si256((__m256i const *) ptr + 7);
    __m256i d09 = _mm256_lddqu_si256((__m256i const *) ptr + 8);
    sort_09v_ascending(d01, d02, d03, d04, d05, d06, d07, d08, d09);
    _mm256_storeu_si256((__m256i *) ptr + 0, d01);
    _mm256_storeu_si256((__m256i *) ptr + 1, d02);
    _mm256_storeu_si256((__m256i *) ptr + 2, d03);
    _mm256_storeu_si256((__m256i *) ptr + 3, d04);
    _mm256_storeu_si256((__m256i *) ptr + 4, d05);
    _mm256_storeu_si256((__m256i *) ptr + 5, d06);
    _mm256_storeu_si256((__m256i *) ptr + 6, d07);
    _mm256_storeu_si256((__m256i *) ptr + 7, d08);
    _mm256_storeu_si256((__m256i *) ptr + 8, d09);
}

static NOINLINE void sort_10v(int64_t *ptr) {
    __m256i d01 = _mm256_lddqu_si256((__m256i const *) ptr + 0);
    __m256i d02 = _mm256_lddqu_si256((__m256i const *) ptr + 1);
    __m256i d03 = _mm256_lddqu_si256((__m256i const *) ptr + 2);
    __m256i d04 = _mm256_lddqu_si256((__m256i const *) ptr + 3);
    __m256i d05 = _mm256_lddqu_si256((__m256i const *) ptr + 4);
    __m256i d06 = _mm256_lddqu_si256((__m256i const *) ptr + 5);
    __m256i d07 = _mm256_lddqu_si256((__m256i const *) ptr + 6);
    __m256i d08 = _mm256_lddqu_si256((__m256i const *) ptr + 7);
    __m256i d09 = _mm256_lddqu_si256((__m256i const *) ptr + 8);
    __m256i d10 = _mm256_lddqu_si256((__m256i const *) ptr + 9);
    sort_10v_ascending(d01, d02, d03, d04, d05, d06, d07, d08, d09, d10);
    _mm256_storeu_si256((__m256i *) ptr + 0, d01);
    _mm256_storeu_si256((__m256i *) ptr + 1, d02);
    _mm256_storeu_si256((__m256i *) ptr + 2, d03);
    _mm256_storeu_si256((__m256i *) ptr + 3, d04);
    _mm256_storeu_si256((__m256i *) ptr + 4, d05);
    _mm256_storeu_si256((__m256i *) ptr + 5, d06);
    _mm256_storeu_si256((__m256i *) ptr + 6, d07);
    _mm256_storeu_si256((__m256i *) ptr + 7, d08);
    _mm256_storeu_si256((__m256i *) ptr + 8, d09);
    _mm256_storeu_si256((__m256i *) ptr + 9, d10);
}

static NOINLINE void sort_11v(int64_t *ptr) {
    __m256i d01 = _mm256_lddqu_si256((__m256i const *) ptr + 0);
    __m256i d02 = _mm256_lddqu_si256((__m256i const *) ptr + 1);
    __m256i d03 = _mm256_lddqu_si256((__m256i const *) ptr + 2);
    __m256i d04 = _mm256_lddqu_si256((__m256i const *) ptr + 3);
    __m256i d05 = _mm256_lddqu_si256((__m256i const *) ptr + 4);
    __m256i d06 = _mm256_lddqu_si256((__m256i const *) ptr + 5);
    __m256i d07 = _mm256_lddqu_si256((__m256i const *) ptr + 6);
    __m256i d08 = _mm256_lddqu_si256((__m256i const *) ptr + 7);
    __m256i d09 = _mm256_lddqu_si256((__m256i const *) ptr + 8);
    __m256i d10 = _mm256_lddqu_si256((__m256i const *) ptr + 9);
    __m256i d11 = _mm256_lddqu_si256((__m256i const *) ptr + 10);
    sort_11v_ascending(d01, d02, d03, d04, d05, d06, d07, d08, d09, d10, d11);
    _mm256_storeu_si256((__m256i *) ptr + 0, d01);
    _mm256_storeu_si256((__m256i *) ptr + 1, d02);
    _mm256_storeu_si256((__m256i *) ptr + 2, d03);
    _mm256_storeu_si256((__m256i *) ptr + 3, d04);
    _mm256_storeu_si256((__m256i *) ptr + 4, d05);
    _mm256_storeu_si256((__m256i *) ptr + 5, d06);
    _mm256_storeu_si256((__m256i *) ptr + 6, d07);
    _mm256_storeu_si256((__m256i *) ptr + 7, d08);
    _mm256_storeu_si256((__m256i *) ptr + 8, d09);
    _mm256_storeu_si256((__m256i *) ptr + 9, d10);
    _mm256_storeu_si256((__m256i *) ptr + 10, d11);
}

static NOINLINE void sort_12v(int64_t *ptr) {
    __m256i d01 = _mm256_lddqu_si256((__m256i const *) ptr + 0);
    __m256i d02 = _mm256_lddqu_si256((__m256i const *) ptr + 1);
    __m256i d03 = _mm256_lddqu_si256((__m256i const *) ptr + 2);
    __m256i d04 = _mm256_lddqu_si256((__m256i const *) ptr + 3);
    __m256i d05 = _mm256_lddqu_si256((__m256i const *) ptr + 4);
    __m256i d06 = _mm256_lddqu_si256((__m256i const *) ptr + 5);
    __m256i d07 = _mm256_lddqu_si256((__m256i const *) ptr + 6);
    __m256i d08 = _mm256_lddqu_si256((__m256i const *) ptr + 7);
    __m256i d09 = _mm256_lddqu_si256((__m256i const *) ptr + 8);
    __m256i d10 = _mm256_lddqu_si256((__m256i const *) ptr + 9);
    __m256i d11 = _mm256_lddqu_si256((__m256i const *) ptr + 10);
    __m256i d12 = _mm256_lddqu_si256((__m256i const *) ptr + 11);
    sort_12v_ascending(d01, d02, d03, d04, d05, d06, d07, d08, d09, d10, d11, d12);
    _mm256_storeu_si256((__m256i *) ptr + 0, d01);
    _mm256_storeu_si256((__m256i *) ptr + 1, d02);
    _mm256_storeu_si256((__m256i *) ptr + 2, d03);
    _mm256_storeu_si256((__m256i *) ptr + 3, d04);
    _mm256_storeu_si256((__m256i *) ptr + 4, d05);
    _mm256_storeu_si256((__m256i *) ptr + 5, d06);
    _mm256_storeu_si256((__m256i *) ptr + 6, d07);
    _mm256_storeu_si256((__m256i *) ptr + 7, d08);
    _mm256_storeu_si256((__m256i *) ptr + 8, d09);
    _mm256_storeu_si256((__m256i *) ptr + 9, d10);
    _mm256_storeu_si256((__m256i *) ptr + 10, d11);
    _mm256_storeu_si256((__m256i *) ptr + 11, d12);
}

static NOINLINE void sort_13v(int64_t *ptr) {
    __m256i d01 = _mm256_lddqu_si256((__m256i const *) ptr + 0);
    __m256i d02 = _mm256_lddqu_si256((__m256i const *) ptr + 1);
    __m256i d03 = _mm256_lddqu_si256((__m256i const *) ptr + 2);
    __m256i d04 = _mm256_lddqu_si256((__m256i const *) ptr + 3);
    __m256i d05 = _mm256_lddqu_si256((__m256i const *) ptr + 4);
    __m256i d06 = _mm256_lddqu_si256((__m256i const *) ptr + 5);
    __m256i d07 = _mm256_lddqu_si256((__m256i const *) ptr + 6);
    __m256i d08 = _mm256_lddqu_si256((__m256i const *) ptr + 7);
    __m256i d09 = _mm256_lddqu_si256((__m256i const *) ptr + 8);
    __m256i d10 = _mm256_lddqu_si256((__m256i const *) ptr + 9);
    __m256i d11 = _mm256_lddqu_si256((__m256i const *) ptr + 10);
    __m256i d12 = _mm256_lddqu_si256((__m256i const *) ptr + 11);
    __m256i d13 = _mm256_lddqu_si256((__m256i const *) ptr + 12);
    sort_13v_ascending(d01, d02, d03, d04, d05, d06, d07, d08, d09, d10, d11, d12, d13);
    _mm256_storeu_si256((__m256i *) ptr + 0, d01);
    _mm256_storeu_si256((__m256i *) ptr + 1, d02);
    _mm256_storeu_si256((__m256i *) ptr + 2, d03);
    _mm256_storeu_si256((__m256i *) ptr + 3, d04);
    _mm256_storeu_si256((__m256i *) ptr + 4, d05);
    _mm256_storeu_si256((__m256i *) ptr + 5, d06);
    _mm256_storeu_si256((__m256i *) ptr + 6, d07);
    _mm256_storeu_si256((__m256i *) ptr + 7, d08);
    _mm256_storeu_si256((__m256i *) ptr + 8, d09);
    _mm256_storeu_si256((__m256i *) ptr + 9, d10);
    _mm256_storeu_si256((__m256i *) ptr + 10, d11);
    _mm256_storeu_si256((__m256i *) ptr + 11, d12);
    _mm256_storeu_si256((__m256i *) ptr + 12, d13);
}

static NOINLINE void sort_14v(int64_t *ptr) {
    __m256i d01 = _mm256_lddqu_si256((__m256i const *) ptr + 0);
    __m256i d02 = _mm256_lddqu_si256((__m256i const *) ptr + 1);
    __m256i d03 = _mm256_lddqu_si256((__m256i const *) ptr + 2);
    __m256i d04 = _mm256_lddqu_si256((__m256i const *) ptr + 3);
    __m256i d05 = _mm256_lddqu_si256((__m256i const *) ptr + 4);
    __m256i d06 = _mm256_lddqu_si256((__m256i const *) ptr + 5);
    __m256i d07 = _mm256_lddqu_si256((__m256i const *) ptr + 6);
    __m256i d08 = _mm256_lddqu_si256((__m256i const *) ptr + 7);
    __m256i d09 = _mm256_lddqu_si256((__m256i const *) ptr + 8);
    __m256i d10 = _mm256_lddqu_si256((__m256i const *) ptr + 9);
    __m256i d11 = _mm256_lddqu_si256((__m256i const *) ptr + 10);
    __m256i d12 = _mm256_lddqu_si256((__m256i const *) ptr + 11);
    __m256i d13 = _mm256_lddqu_si256((__m256i const *) ptr + 12);
    __m256i d14 = _mm256_lddqu_si256((__m256i const *) ptr + 13);
    sort_14v_ascending(d01, d02, d03, d04, d05, d06, d07, d08, d09, d10, d11, d12, d13, d14);
    _mm256_storeu_si256((__m256i *) ptr + 0, d01);
    _mm256_storeu_si256((__m256i *) ptr + 1, d02);
    _mm256_storeu_si256((__m256i *) ptr + 2, d03);
    _mm256_storeu_si256((__m256i *) ptr + 3, d04);
    _mm256_storeu_si256((__m256i *) ptr + 4, d05);
    _mm256_storeu_si256((__m256i *) ptr + 5, d06);
    _mm256_storeu_si256((__m256i *) ptr + 6, d07);
    _mm256_storeu_si256((__m256i *) ptr + 7, d08);
    _mm256_storeu_si256((__m256i *) ptr + 8, d09);
    _mm256_storeu_si256((__m256i *) ptr + 9, d10);
    _mm256_storeu_si256((__m256i *) ptr + 10, d11);
    _mm256_storeu_si256((__m256i *) ptr + 11, d12);
    _mm256_storeu_si256((__m256i *) ptr + 12, d13);
    _mm256_storeu_si256((__m256i *) ptr + 13, d14);
}

static NOINLINE void sort_15v(int64_t *ptr) {
    __m256i d01 = _mm256_lddqu_si256((__m256i const *) ptr + 0);
    __m256i d02 = _mm256_lddqu_si256((__m256i const *) ptr + 1);
    __m256i d03 = _mm256_lddqu_si256((__m256i const *) ptr + 2);
    __m256i d04 = _mm256_lddqu_si256((__m256i const *) ptr + 3);
    __m256i d05 = _mm256_lddqu_si256((__m256i const *) ptr + 4);
    __m256i d06 = _mm256_lddqu_si256((__m256i const *) ptr + 5);
    __m256i d07 = _mm256_lddqu_si256((__m256i const *) ptr + 6);
    __m256i d08 = _mm256_lddqu_si256((__m256i const *) ptr + 7);
    __m256i d09 = _mm256_lddqu_si256((__m256i const *) ptr + 8);
    __m256i d10 = _mm256_lddqu_si256((__m256i const *) ptr + 9);
    __m256i d11 = _mm256_lddqu_si256((__m256i const *) ptr + 10);
    __m256i d12 = _mm256_lddqu_si256((__m256i const *) ptr + 11);
    __m256i d13 = _mm256_lddqu_si256((__m256i const *) ptr + 12);
    __m256i d14 = _mm256_lddqu_si256((__m256i const *) ptr + 13);
    __m256i d15 = _mm256_lddqu_si256((__m256i const *) ptr + 14);
    sort_15v_ascending(d01, d02, d03, d04, d05, d06, d07, d08, d09, d10, d11, d12, d13, d14, d15);
    _mm256_storeu_si256((__m256i *) ptr + 0, d01);
    _mm256_storeu_si256((__m256i *) ptr + 1, d02);
    _mm256_storeu_si256((__m256i *) ptr + 2, d03);
    _mm256_storeu_si256((__m256i *) ptr + 3, d04);
    _mm256_storeu_si256((__m256i *) ptr + 4, d05);
    _mm256_storeu_si256((__m256i *) ptr + 5, d06);
    _mm256_storeu_si256((__m256i *) ptr + 6, d07);
    _mm256_storeu_si256((__m256i *) ptr + 7, d08);
    _mm256_storeu_si256((__m256i *) ptr + 8, d09);
    _mm256_storeu_si256((__m256i *) ptr + 9, d10);
    _mm256_storeu_si256((__m256i *) ptr + 10, d11);
    _mm256_storeu_si256((__m256i *) ptr + 11, d12);
    _mm256_storeu_si256((__m256i *) ptr + 12, d13);
    _mm256_storeu_si256((__m256i *) ptr + 13, d14);
    _mm256_storeu_si256((__m256i *) ptr + 14, d15);
}

static NOINLINE void sort_16v(int64_t *ptr) {
    __m256i d01 = _mm256_lddqu_si256((__m256i const *) ptr + 0);
    __m256i d02 = _mm256_lddqu_si256((__m256i const *) ptr + 1);
    __m256i d03 = _mm256_lddqu_si256((__m256i const *) ptr + 2);
    __m256i d04 = _mm256_lddqu_si256((__m256i const *) ptr + 3);
    __m256i d05 = _mm256_lddqu_si256((__m256i const *) ptr + 4);
    __m256i d06 = _mm256_lddqu_si256((__m256i const *) ptr + 5);
    __m256i d07 = _mm256_lddqu_si256((__m256i const *) ptr + 6);
    __m256i d08 = _mm256_lddqu_si256((__m256i const *) ptr + 7);
    __m256i d09 = _mm256_lddqu_si256((__m256i const *) ptr + 8);
    __m256i d10 = _mm256_lddqu_si256((__m256i const *) ptr + 9);
    __m256i d11 = _mm256_lddqu_si256((__m256i const *) ptr + 10);
    __m256i d12 = _mm256_lddqu_si256((__m256i const *) ptr + 11);
    __m256i d13 = _mm256_lddqu_si256((__m256i const *) ptr + 12);
    __m256i d14 = _mm256_lddqu_si256((__m256i const *) ptr + 13);
    __m256i d15 = _mm256_lddqu_si256((__m256i const *) ptr + 14);
    __m256i d16 = _mm256_lddqu_si256((__m256i const *) ptr + 15);
    sort_16v_ascending(d01, d02, d03, d04, d05, d06, d07, d08, d09, d10, d11, d12, d13, d14, d15, d16);
    _mm256_storeu_si256((__m256i *) ptr + 0, d01);
    _mm256_storeu_si256((__m256i *) ptr + 1, d02);
    _mm256_storeu_si256((__m256i *) ptr + 2, d03);
    _mm256_storeu_si256((__m256i *) ptr + 3, d04);
    _mm256_storeu_si256((__m256i *) ptr + 4, d05);
    _mm256_storeu_si256((__m256i *) ptr + 5, d06);
    _mm256_storeu_si256((__m256i *) ptr + 6, d07);
    _mm256_storeu_si256((__m256i *) ptr + 7, d08);
    _mm256_storeu_si256((__m256i *) ptr + 8, d09);
    _mm256_storeu_si256((__m256i *) ptr + 9, d10);
    _mm256_storeu_si256((__m256i *) ptr + 10, d11);
    _mm256_storeu_si256((__m256i *) ptr + 11, d12);
    _mm256_storeu_si256((__m256i *) ptr + 12, d13);
    _mm256_storeu_si256((__m256i *) ptr + 13, d14);
    _mm256_storeu_si256((__m256i *) ptr + 14, d15);
    _mm256_storeu_si256((__m256i *) ptr + 15, d16);
}
    static void sort(int64_t *ptr, size_t length) {
    const int N = 4;

    switch(length / N) {
        case 1: sort_01v(ptr); break;
        case 2: sort_02v(ptr); break;
        case 3: sort_03v(ptr); break;
        case 4: sort_04v(ptr); break;
        case 5: sort_05v(ptr); break;
        case 6: sort_06v(ptr); break;
        case 7: sort_07v(ptr); break;
        case 8: sort_08v(ptr); break;
        case 9: sort_09v(ptr); break;
        case 10: sort_10v(ptr); break;
        case 11: sort_11v(ptr); break;
        case 12: sort_12v(ptr); break;
        case 13: sort_13v(ptr); break;
        case 14: sort_14v(ptr); break;
        case 15: sort_15v(ptr); break;
        case 16: sort_16v(ptr); break;
    }
}
};
}
}
#endif
