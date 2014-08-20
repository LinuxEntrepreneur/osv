/*
 * Copyright (C) 2014 Cloudius Systems, Ltd.
 *
 * This work is open source software, licensed under the terms of the
 * BSD license as described in the LICENSE file in the top-level directory.
 */

#ifndef SSE_HH_
#define SSE_HH_

#include <x86intrin.h>

template <unsigned N>
struct sse_register_file;

template <>
struct sse_register_file<0> {
    void load_aligned(const __m128i* p) {}
    void store_aligned(__m128i* p) {}
    void load_unaligned(const __m128i* p) {}
    void store_unaligned(__m128i* p) {}
};

template <unsigned N>
struct sse_register_file : sse_register_file<N-1> {
    __m128i reg;
    void load_aligned(const __m128i* p) {
        sse_register_file<N-1>::load_aligned(p);
        reg = _mm_load_si128(&p[N-1]);
    }
    void store_aligned(__m128i* p) {
        sse_register_file<N-1>::store_aligned(p);
        _mm_store_si128(&p[N-1], reg);
    }
    void load_unaligned(const __m128i* p) {
        sse_register_file<N-1>::load_unaligned(p);
        reg = _mm_loadu_si128(&p[N-1]);
    }
    void store_unaligned(__m128i* p) {
        sse_register_file<N-1>::store_unaligned(p);
        _mm_storeu_si128(&p[N-1], reg);
    }
};


#endif /* SSE_HH_ */