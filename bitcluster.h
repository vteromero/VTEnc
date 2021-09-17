/**
  Copyright (c) 2019-2020 Vicente Romero Calero. All rights reserved.
  Licensed under the MIT License.
  See LICENSE file in the project root for full license information.
 */
#ifndef VTENC_BITCLUSTER_H_
#define VTENC_BITCLUSTER_H_

#include <stddef.h>

struct BitCluster {
  size_t from;
  size_t length;
  unsigned int bit_pos;
};

#endif /* VTENC_BITCLUSTER_H_ */
