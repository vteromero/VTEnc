/**
  Copyright (c) 2019 Vicente Romero Calero. All rights reserved.
  Licensed under the MIT License.
  See LICENSE file in the project root for full license information.
 */
#ifndef VTENC_COMPILER_H_
#define VTENC_COMPILER_H_

#define GCC_VERSION (__GNUC__ * 10000		\
		     + __GNUC_MINOR__ * 100	\
		     + __GNUC_PATCHLEVEL__)

#if GCC_VERSION >= 40300
#define __HAVE_BUILTIN_BSWAP32__
#define __HAVE_BUILTIN_BSWAP64__
#endif

#if GCC_VERSION >= 40800
#define __HAVE_BUILTIN_BSWAP16__
#endif

#if GCC_VERSION >= 40000
#define __HAVE_BUILTIN_CLZ__
#define __HAVE_BUILTIN_CLZLL__
#endif

#define likely(x)  __builtin_expect(!!(x), 1)
#define unlikely(x)  __builtin_expect(!!(x), 0)

#endif /* VTENC_COMPILER_H_ */
