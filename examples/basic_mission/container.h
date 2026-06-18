/*
 * SPDX-FileCopyrightText: 2014 Freie Universität Berlin
 * SPDX-FileCopyrightText: 2017 HAW-Hamburg
 * SPDX-License-Identifier: LGPL-2.1-only
 */
 
#pragma once
 
#include <stddef.h>
#include <stdint.h>
 
#ifdef __cplusplus
extern "C" {
#endif
 
/* uncrustify gets mightily confused by these macros... */
/* begin{code-style-ignore} */
#if __STDC_VERSION__ >= 201112L
#   define container_of(PTR, TYPE, MEMBER) \
        (_Generic((PTR), \
            const __typeof__ (((TYPE *) 0)->MEMBER) *: \
                ((TYPE *) ((uintptr_t) (PTR) - offsetof(TYPE, MEMBER))), \
            __typeof__ (((TYPE *) 0)->MEMBER) *: \
                ((TYPE *) ((uintptr_t) (PTR) - offsetof(TYPE, MEMBER))) \
        ))
#elif defined __GNUC__
#   define container_of(PTR, TYPE, MEMBER) \
        (__extension__ ({ \
            __extension__ const __typeof__ (((TYPE *) 0)->MEMBER) *__m____ = (PTR); \
            ((TYPE *) ((uintptr_t) __m____ - offsetof(TYPE, MEMBER))); \
        }))
#else
#   define container_of(PTR, TYPE, MEMBER) \
        ((TYPE *) ((char *) (PTR) - offsetof(TYPE, MEMBER)))
#endif
#define index_of(ARRAY, ELEMENT) (((uintptr_t)(ELEMENT) - (uintptr_t)(ARRAY)) / sizeof((ARRAY)[0]))
#ifndef ARRAY_SIZE
#define ARRAY_SIZE(a) (sizeof((a)) / sizeof((a)[0]))
#endif
 
#ifdef __cplusplus
}
#endif
