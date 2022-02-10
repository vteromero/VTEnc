/**
  Copyright (c) 2019 Vicente Romero Calero. All rights reserved.
  Licensed under the MIT License.
  See LICENSE file in the project root for full license information.
 */
#ifndef VTENC_ERROR_H_
#define VTENC_ERROR_H_

#include "internals.h"

#define return_if_error(exp)  \
do {                          \
  const int code = (exp);     \
  if (code != VTENC_OK) {     \
    return code;              \
  }                           \
} while(0)

#endif /* VTENC_ERROR_H_ */
