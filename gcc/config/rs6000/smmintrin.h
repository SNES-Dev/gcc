/* Copyright (C) 2018-2021 Free Software Foundation, Inc.

   This file is part of GCC.

   GCC is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3, or (at your option)
   any later version.

   GCC is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   Under Section 7 of GPL version 3, you are granted additional
   permissions described in the GCC Runtime Library Exception, version
   3.1, as published by the Free Software Foundation.

   You should have received a copy of the GNU General Public License and
   a copy of the GCC Runtime Library Exception along with this program;
   see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
   <http://www.gnu.org/licenses/>.  */

/* Implemented from the specification included in the Intel C++ Compiler
   User Guide and Reference, version 9.0.

   NOTE: This is NOT a complete implementation of the SSE4 intrinsics!  */

#ifndef NO_WARN_X86_INTRINSICS
/* This header is distributed to simplify porting x86_64 code that
   makes explicit use of Intel intrinsics to powerpc64le.
   It is the user's responsibility to determine if the results are
   acceptable and make additional changes as necessary.
   Note that much code that uses Intel intrinsics can be rewritten in
   standard C or GNU C extensions, which are more portable and better
   optimized across multiple targets.  */
#endif

#ifndef SMMINTRIN_H_
#define SMMINTRIN_H_

#include <altivec.h>
#include <tmmintrin.h>

extern __inline __m128i __attribute__((__gnu_inline__, __always_inline__, __artificial__))
_mm_insert_epi8 (__m128i const __A, int const __D, int const __N)
{
  __v16qi result = (__v16qi)__A;

  result [__N & 0xf] = __D;

  return (__m128i) result;
}

extern __inline __m128i __attribute__((__gnu_inline__, __always_inline__, __artificial__))
_mm_insert_epi32 (__m128i const __A, int const __D, int const __N)
{
  __v4si result = (__v4si)__A;

  result [__N & 3] = __D;

  return (__m128i) result;
}

extern __inline __m128i __attribute__((__gnu_inline__, __always_inline__, __artificial__))
_mm_insert_epi64 (__m128i const __A, long long const __D, int const __N)
{
  __v2di result = (__v2di)__A;

  result [__N & 1] = __D;

  return (__m128i) result;
}

extern __inline int __attribute__((__gnu_inline__, __always_inline__, __artificial__))
_mm_extract_epi8 (__m128i __X, const int __N)
{
  return (unsigned char) ((__v16qi)__X)[__N & 15];
}

extern __inline int __attribute__((__gnu_inline__, __always_inline__, __artificial__))
_mm_extract_epi32 (__m128i __X, const int __N)
{
  return ((__v4si)__X)[__N & 3];
}

extern __inline int __attribute__((__gnu_inline__, __always_inline__, __artificial__))
_mm_extract_epi64 (__m128i __X, const int __N)
{
  return ((__v2di)__X)[__N & 1];
}

extern __inline int __attribute__((__gnu_inline__, __always_inline__, __artificial__))
_mm_extract_ps (__m128 __X, const int __N)
{
  return ((__v4si)__X)[__N & 3];
}

extern __inline __m128i __attribute__((__gnu_inline__, __always_inline__, __artificial__))
_mm_blend_epi16 (__m128i __A, __m128i __B, const int __imm8)
{
  __v16qi __charmask = vec_splats ((signed char) __imm8);
  __charmask = vec_gb (__charmask);
  __v8hu __shortmask = (__v8hu) vec_unpackh (__charmask);
  #ifdef __BIG_ENDIAN__
  __shortmask = vec_reve (__shortmask);
  #endif
  return (__m128i) vec_sel ((__v8hu) __A, (__v8hu) __B, __shortmask);
}

extern __inline __m128i __attribute__((__gnu_inline__, __always_inline__, __artificial__))
_mm_blendv_epi8 (__m128i __A, __m128i __B, __m128i __mask)
{
  const __v16qu __seven = vec_splats ((unsigned char) 0x07);
  __v16qu __lmask = vec_sra ((__v16qu) __mask, __seven);
  return (__m128i) vec_sel ((__v16qu) __A, (__v16qu) __B, __lmask);
}

__inline __m128
__attribute__ ((__gnu_inline__, __always_inline__, __artificial__))
_mm_blend_ps (__m128 __A, __m128 __B, const int __imm8)
{
  __v16qu __pcv[] =
    {
      {  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15 },
      { 16, 17, 18, 19,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15 },
      {  0,  1,  2,  3, 20, 21, 22, 23,  8,  9, 10, 11, 12, 13, 14, 15 },
      { 16, 17, 18, 19, 20, 21, 22, 23,  8,  9, 10, 11, 12, 13, 14, 15 },
      {  0,  1,  2,  3,  4,  5,  6,  7, 24, 25, 26, 27, 12, 13, 14, 15 },
      { 16, 17, 18, 19,  4,  5,  6,  7, 24, 25, 26, 27, 12, 13, 14, 15 },
      {  0,  1,  2,  3, 20, 21, 22, 23, 24, 25, 26, 27, 12, 13, 14, 15 },
      { 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 12, 13, 14, 15 },
      {  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 28, 29, 30, 31 },
      { 16, 17, 18, 19,  4,  5,  6,  7,  8,  9, 10, 11, 28, 29, 30, 31 },
      {  0,  1,  2,  3, 20, 21, 22, 23,  8,  9, 10, 11, 28, 29, 30, 31 },
      { 16, 17, 18, 19, 20, 21, 22, 23,  8,  9, 10, 11, 28, 29, 30, 31 },
      {  0,  1,  2,  3,  4,  5,  6,  7, 24, 25, 26, 27, 28, 29, 30, 31 },
      { 16, 17, 18, 19,  4,  5,  6,  7, 24, 25, 26, 27, 28, 29, 30, 31 },
      {  0,  1,  2,  3, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31 },
      { 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31 },
    };
  __v16qu __r = vec_perm ((__v16qu) __A, (__v16qu)__B, __pcv[__imm8]);
  return (__m128) __r;
}

__inline __m128
__attribute__ ((__gnu_inline__, __always_inline__, __artificial__))
_mm_blendv_ps (__m128 __A, __m128 __B, __m128 __mask)
{
  const __v4si __zero = {0};
  const __vector __bool int __boolmask = vec_cmplt ((__v4si) __mask, __zero);
  return (__m128) vec_sel ((__v4su) __A, (__v4su) __B, (__v4su) __boolmask);
}

__inline __m128d
__attribute__ ((__gnu_inline__, __always_inline__, __artificial__))
_mm_blend_pd (__m128d __A, __m128d __B, const int __imm8)
{
  __v16qu __pcv[] =
    {
      {  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15 },
      { 16, 17, 18, 19, 20, 21, 22, 23,  8,  9, 10, 11, 12, 13, 14, 15 },
      {  0,  1,  2,  3,  4,  5,  6,  7, 24, 25, 26, 27, 28, 29, 30, 31 },
      { 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31 }
    };
  __v16qu __r = vec_perm ((__v16qu) __A, (__v16qu)__B, __pcv[__imm8]);
  return (__m128d) __r;
}

__inline __m128d
__attribute__ ((__gnu_inline__, __always_inline__, __artificial__))
_mm_blendv_pd (__m128d __A, __m128d __B, __m128d __mask)
{
  const __v2di __zero = {0};
  const __vector __bool long long __boolmask = vec_cmplt ((__v2di) __mask, __zero);
  return (__m128d) vec_sel ((__v2du) __A, (__v2du) __B, (__v2du) __boolmask);
}

__inline int
__attribute__ ((__gnu_inline__, __always_inline__, __artificial__))
_mm_testz_si128 (__m128i __A, __m128i __B)
{
  /* Note: This implementation does NOT set "zero" or "carry" flags.  */
  const __v16qu __zero = {0};
  return vec_all_eq (vec_and ((__v16qu) __A, (__v16qu) __B), __zero);
}

__inline int
__attribute__ ((__gnu_inline__, __always_inline__, __artificial__))
_mm_testc_si128 (__m128i __A, __m128i __B)
{
  /* Note: This implementation does NOT set "zero" or "carry" flags.  */
  const __v16qu __zero = {0};
  const __v16qu __notA = vec_nor ((__v16qu) __A, (__v16qu) __A);
  return vec_all_eq (vec_and ((__v16qu) __notA, (__v16qu) __B), __zero);
}

__inline int
__attribute__ ((__gnu_inline__, __always_inline__, __artificial__))
_mm_testnzc_si128 (__m128i __A, __m128i __B)
{
  /* Note: This implementation does NOT set "zero" or "carry" flags.  */
  return _mm_testz_si128 (__A, __B) == 0 && _mm_testc_si128 (__A, __B) == 0;
}

__inline int
__attribute__ ((__gnu_inline__, __always_inline__, __artificial__))
_mm_test_all_zeros (__m128i __A, __m128i __mask)
{
  const __v16qu __zero = {0};
  return vec_all_eq (vec_and ((__v16qu) __A, (__v16qu) __mask), __zero);
}

__inline int
__attribute__ ((__gnu_inline__, __always_inline__, __artificial__))
_mm_test_all_ones (__m128i __A)
{
  const __v16qu __ones = vec_splats ((unsigned char) 0xff);
  return vec_all_eq ((__v16qu) __A, __ones);
}

__inline int
__attribute__ ((__gnu_inline__, __always_inline__, __artificial__))
_mm_test_mix_ones_zeros (__m128i __A, __m128i __mask)
{
  const __v16qu __zero = {0};
  const __v16qu __Amasked = vec_and ((__v16qu) __A, (__v16qu) __mask);
  const int any_ones = vec_any_ne (__Amasked, __zero);
  const __v16qu __notA = vec_nor ((__v16qu) __A, (__v16qu) __A);
  const __v16qu __notAmasked = vec_and ((__v16qu) __notA, (__v16qu) __mask);
  const int any_zeros = vec_any_ne (__notAmasked, __zero);
  return any_ones * any_zeros;
}

__inline __m128d
__attribute__ ((__gnu_inline__, __always_inline__, __artificial__))
_mm_ceil_pd (__m128d __A)
{
  return (__m128d) vec_ceil ((__v2df) __A);
}

__inline __m128d
__attribute__ ((__gnu_inline__, __always_inline__, __artificial__))
_mm_ceil_sd (__m128d __A, __m128d __B)
{
  __v2df __r = vec_ceil ((__v2df) __B);
  __r[1] = ((__v2df) __A)[1];
  return (__m128d) __r;
}

__inline __m128d
__attribute__ ((__gnu_inline__, __always_inline__, __artificial__))
_mm_floor_pd (__m128d __A)
{
  return (__m128d) vec_floor ((__v2df) __A);
}

__inline __m128d
__attribute__ ((__gnu_inline__, __always_inline__, __artificial__))
_mm_floor_sd (__m128d __A, __m128d __B)
{
  __v2df __r = vec_floor ((__v2df) __B);
  __r[1] = ((__v2df) __A)[1];
  return (__m128d) __r;
}

__inline __m128
__attribute__ ((__gnu_inline__, __always_inline__, __artificial__))
_mm_ceil_ps (__m128 __A)
{
  return (__m128) vec_ceil ((__v4sf) __A);
}

__inline __m128
__attribute__ ((__gnu_inline__, __always_inline__, __artificial__))
_mm_ceil_ss (__m128 __A, __m128 __B)
{
  __v4sf __r = (__v4sf) __A;
  __r[0] = __builtin_ceil (((__v4sf) __B)[0]);
  return __r;
}

__inline __m128
__attribute__ ((__gnu_inline__, __always_inline__, __artificial__))
_mm_floor_ps (__m128 __A)
{
  return (__m128) vec_floor ((__v4sf) __A);
}

__inline __m128
__attribute__ ((__gnu_inline__, __always_inline__, __artificial__))
_mm_floor_ss (__m128 __A, __m128 __B)
{
  __v4sf __r = (__v4sf) __A;
  __r[0] = __builtin_floor (((__v4sf) __B)[0]);
  return __r;
}

#endif
