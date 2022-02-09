/**
  Copyright (c) 2022 Vicente Romero Calero. All rights reserved.
  Licensed under the MIT License.
  See LICENSE file in the project root for full license information.
 */
#include "internals.h"

int vtenc_init(vtenc *handler)
{
  handler->params.allow_repeated_values = 1;
  handler->params.skip_full_subtrees    = 1;
  handler->params.min_cluster_length    = 1;
  handler->out_size                     = 0;

  return VTENC_OK;
}

