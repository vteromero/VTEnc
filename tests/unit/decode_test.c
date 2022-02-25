/**
  Copyright (c) 2019 Vicente Romero Calero. All rights reserved.
  Licensed under the MIT License.
  See LICENSE file in the project root for full license information.
 */
#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "unit_tests.h"
#include "../../vtenc.h"

struct EncodingParams {
  int allow_repeated_values;
  int skip_full_subtrees;
  size_t min_cluster_length;
};

struct DecodeTestCaseInput {
  struct EncodingParams params;
  const uint8_t *bytes;
  size_t bytes_len;
  size_t values_len;
};

struct DecodeTestCaseOutput {
  void *values;
  int result_code;
};

struct DecodeTestCase {
  struct DecodeTestCaseInput input;
  struct DecodeTestCaseOutput expected_output;
};

static struct DecodeTestCase test_cases8[] = {
  {
    .input = {
      .params = {
        .allow_repeated_values = 1,
        .skip_full_subtrees = 0,
        .min_cluster_length = 1
      },
      .bytes = (uint8_t []){0x0e},
      .bytes_len = 1,
      .values_len = 4,
    },
    .expected_output = {
      .values = (uint8_t []){},
      .result_code = VTENC_ERR_WRONG_FORMAT
    }
  },
  {
    .input = {
      .params = {
        .allow_repeated_values = 1,
        .skip_full_subtrees = 0,
        .min_cluster_length = 1
      },
      .bytes = (uint8_t []){},
      .bytes_len = 0,
      .values_len = 0xffffffffffffffffULL,
    },
    .expected_output = {
      .values = (uint8_t []){},
      .result_code = VTENC_ERR_OUTPUT_TOO_BIG
    }
  },
  {
    .input = {
      .params = {
        .allow_repeated_values = 1,
        .skip_full_subtrees = 0,
        .min_cluster_length = 1
      },
      .bytes = (uint8_t []){},
      .bytes_len = 0,
      .values_len = 0
    },
    .expected_output = {
      .values = (uint8_t []){},
      .result_code = VTENC_OK
    }
  },
  {
    .input = {
      .params = {
        .allow_repeated_values = 1,
        .skip_full_subtrees = 0,
        .min_cluster_length = 1
      },
      .bytes = (uint8_t []){0x26},
      .bytes_len = 1,
      .values_len = 1,
    },
    .expected_output = {
      .values = (uint8_t []){38},
      .result_code = VTENC_OK
    }
  },
  {
    .input = {
      .params = {
        .allow_repeated_values = 1,
        .skip_full_subtrees = 0,
        .min_cluster_length = 1
      },
      .bytes = (uint8_t []){
        0x58, 0xab, 0x84, 0x62, 0xaf, 0xd4, 0x91, 0xac, 0xc9
      },
      .bytes_len = 9,
      .values_len = 11,
    },
    .expected_output = {
      .values = (uint8_t []){5, 22, 23, 44, 62, 69, 109, 113, 178, 194, 206},
      .result_code = VTENC_OK
    }
  },
  {
    .input = {
      .params = {
        .allow_repeated_values = 1,
        .skip_full_subtrees = 0,
        .min_cluster_length = 1
      },
      .bytes = (uint8_t []){0x37, 0xe0, 0x01, 0x01, 0x00, 0x51, 0x05},
      .bytes_len = 7,
      .values_len = 9,
    },
    .expected_output = {
      .values = (uint8_t []){57, 57, 57, 111, 111, 111, 111, 208, 208},
      .result_code = VTENC_OK
    }
  },
  {
    .input = {
      .params = {
        .allow_repeated_values = 0,
        .skip_full_subtrees = 1,
        .min_cluster_length = 1
      },
      .bytes = (uint8_t []){0xff},
      .bytes_len = 1,
      .values_len = 4,
    },
    .expected_output = {
      .values = (uint8_t []){},
      .result_code = VTENC_ERR_WRONG_FORMAT
    }
  },
  {
    .input = {
      .params = {
        .allow_repeated_values = 0,
        .skip_full_subtrees = 1,
        .min_cluster_length = 1
      },
      .bytes = (uint8_t []){},
      .bytes_len = 0,
      .values_len = 257,
    },
    .expected_output = {
      .values = (uint8_t []){},
      .result_code = VTENC_ERR_OUTPUT_TOO_BIG
    }
  },
  {
    .input = {
      .params = {
        .allow_repeated_values = 0,
        .skip_full_subtrees = 1,
        .min_cluster_length = 1
      },
      .bytes = (uint8_t []){},
      .bytes_len = 0,
      .values_len = 0,
    },
    .expected_output = {
      .values = (uint8_t []){},
      .result_code = VTENC_OK
    }
  },
  {
    .input = {
      .params = {
        .allow_repeated_values = 0,
        .skip_full_subtrees = 1,
        .min_cluster_length = 1
      },
      .bytes = (uint8_t []){},
      .bytes_len = 0,
      .values_len = 256,
    },
    .expected_output = {
      .values = (uint8_t []){
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
        20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37,
        38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55,
        56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73,
        74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91,
        92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107,
        108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121,
        122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135,
        136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 147, 148, 149,
        150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160, 161, 162, 163,
        164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 176, 177,
        178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191,
        192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205,
        206, 207, 208, 209, 210, 211, 212, 213, 214, 215, 216, 217, 218, 219,
        220, 221, 222, 223, 224, 225, 226, 227, 228, 229, 230, 231, 232, 233,
        234, 235, 236, 237, 238, 239, 240, 241, 242, 243, 244, 245, 246, 247,
        248, 249, 250, 251, 252, 253, 254, 255
      },
      .result_code = VTENC_OK
    }
  },
  {
    .input = {
      .params = {
        .allow_repeated_values = 0,
        .skip_full_subtrees = 1,
        .min_cluster_length = 1
      },
      .bytes = (uint8_t []){0x21},
      .bytes_len = 1,
      .values_len = 1,
    },
    .expected_output = {
      .values = (uint8_t []){33},
      .result_code = VTENC_OK
    }
  },
  {
    .input = {
      .params = {
        .allow_repeated_values = 0,
        .skip_full_subtrees = 1,
        .min_cluster_length = 1
      },
      .bytes = (uint8_t []){0x88, 0x88, 0x48, 0x90, 0x04},
      .bytes_len = 5,
      .values_len = 12,
    },
    .expected_output = {
      .values = (uint8_t []){0, 1, 2, 3, 4, 5, 6, 7, 160, 161, 162, 163},
      .result_code = VTENC_OK
    }
  },
  {
    .input = {
      .params = {
        .allow_repeated_values = 0,
        .skip_full_subtrees = 1,
        .min_cluster_length = 1
      },
      .bytes = (uint8_t []){0x4c, 0x73, 0x4d, 0x54, 0x45, 0x01},
      .bytes_len = 6,
      .values_len = 6,
    },
    .expected_output = {
      .values = (uint8_t []){13, 77, 88, 93, 149, 212},
      .result_code = VTENC_OK
    }
  },
  {
    .input = {
      .params = {
        .allow_repeated_values = 1,
        .skip_full_subtrees = 0,
        .min_cluster_length = 2
      },
      .bytes = (uint8_t []){0x6e, 0x29, 0x0d, 0x03, 0x1d},
      .bytes_len = 5,
      .values_len = 6,
    },
    .expected_output = {
      .values = (uint8_t []){2, 3, 8, 11, 16, 122},
      .result_code = VTENC_OK
    }
  },
  {
    .input = {
      .params = {
        .allow_repeated_values = 1,
        .skip_full_subtrees = 0,
        .min_cluster_length = 3
      },
      .bytes = (uint8_t []){0x6e, 0x29, 0x0d, 0x03, 0x1d},
      .bytes_len = 5,
      .values_len = 6,
    },
    .expected_output = {
      .values = (uint8_t []){2, 3, 8, 11, 16, 122},
      .result_code = VTENC_OK
    }
  },
  {
    .input = {
      .params = {
        .allow_repeated_values = 1,
        .skip_full_subtrees = 0,
        .min_cluster_length = 4
      },
      .bytes = (uint8_t []){0x6e, 0x29, 0x83, 0x0b, 0x3a},
      .bytes_len = 5,
      .values_len = 6,
    },
    .expected_output = {
      .values = (uint8_t []){2, 3, 8, 11, 16, 122},
      .result_code = VTENC_OK
    }
  },
  {
    .input = {
      .params = {
        .allow_repeated_values = 1,
        .skip_full_subtrees = 0,
        .min_cluster_length = 8
      },
      .bytes = (uint8_t []){0x02, 0x03, 0x08, 0x0b, 0x10, 0x7a},
      .bytes_len = 6,
      .values_len = 6,
    },
    .expected_output = {
      .values = (uint8_t []){2, 3, 8, 11, 16, 122},
      .result_code = VTENC_OK
    }
  },
  {
    .input = {
      .params = {
        .allow_repeated_values = 0,
        .skip_full_subtrees = 1,
        .min_cluster_length = 8
      },
      .bytes = (uint8_t []){0x99, 0x99, 0x28},
      .bytes_len = 3,
      .values_len = 9,
    },
    .expected_output = {
      .values = (uint8_t []){0, 1, 2, 3, 4, 5, 6, 7, 10},
      .result_code = VTENC_OK
    }
  }
};

static struct DecodeTestCase test_cases16[] = {
  {
    .input = {
      .params = {
        .allow_repeated_values = 1,
        .skip_full_subtrees = 0,
        .min_cluster_length = 1
      },
      .bytes = (uint8_t []){0x0e},
      .bytes_len = 1,
      .values_len = 4
    },
    .expected_output = {
      .values = (uint16_t []){},
      .result_code = VTENC_ERR_WRONG_FORMAT
    }
  },
  {
    .input = {
      .params = {
        .allow_repeated_values = 1,
        .skip_full_subtrees = 0,
        .min_cluster_length = 1
      },
      .bytes = (uint8_t []){},
      .bytes_len = 0,
      .values_len = 0xffffffffffffffffULL
    },
    .expected_output = {
      .values = (uint16_t []){},
      .result_code = VTENC_ERR_OUTPUT_TOO_BIG
    }
  },
  {
    .input = {
      .params = {
        .allow_repeated_values = 1,
        .skip_full_subtrees = 0,
        .min_cluster_length = 1
      },
      .bytes = (uint8_t []){},
      .bytes_len = 0,
      .values_len = 0
    },
    .expected_output = {
      .values = (uint16_t []){},
      .result_code = VTENC_OK
    }
  },
  {
    .input = {
      .params = {
        .allow_repeated_values = 1,
        .skip_full_subtrees = 0,
        .min_cluster_length = 1
      },
      .bytes = (uint8_t []){0x26, 0x36},
      .bytes_len = 2,
      .values_len = 1
    },
    .expected_output = {
      .values = (uint16_t []){13862},
      .result_code = VTENC_OK
    }
  },
  {
    .input = {
      .params = {
        .allow_repeated_values = 1,
        .skip_full_subtrees = 0,
        .min_cluster_length = 1
      },
      .bytes = (uint8_t []){
        0xdd, 0xb6, 0xc4, 0x59, 0x98, 0x3e, 0x19, 0x70, 0x52, 0x74, 0xab, 0x8c,
        0x0e
      },
      .bytes_len = 13,
      .values_len = 7
    },
    .expected_output = {
      .values = (uint16_t []){1099, 2227, 8102, 27654, 29001, 35511, 50083},
      .result_code = VTENC_OK
    }
  },
  {
    .input = {
      .params = {
        .allow_repeated_values = 1,
        .skip_full_subtrees = 0,
        .min_cluster_length = 1
      },
      .bytes = (uint8_t []){
        0x88, 0xf3, 0x33, 0xf3, 0x4c, 0x5b, 0x14, 0x05, 0xda, 0x02
      },
      .bytes_len = 10,
      .values_len = 8
    },
    .expected_output = {
      .values = (uint16_t []){677, 677, 677, 8881, 8881, 8881, 8881, 8881},
      .result_code = VTENC_OK
    }
  },
  {
    .input = {
      .params = {
        .allow_repeated_values = 0,
        .skip_full_subtrees = 1,
        .min_cluster_length = 1
      },
      .bytes = (uint8_t []){0xff},
      .bytes_len = 1,
      .values_len = 4
    },
    .expected_output = {
      .values = (uint16_t []){},
      .result_code = VTENC_ERR_WRONG_FORMAT
    }
  },
  {
    .input = {
      .params = {
        .allow_repeated_values = 0,
        .skip_full_subtrees = 1,
        .min_cluster_length = 1
      },
      .bytes = (uint8_t []){},
      .bytes_len = 0,
      .values_len = 65537
    },
    .expected_output = {
      .values = (uint16_t []){},
      .result_code = VTENC_ERR_OUTPUT_TOO_BIG
    }
  },
  {
    .input = {
      .params = {
        .allow_repeated_values = 0,
        .skip_full_subtrees = 1,
        .min_cluster_length = 1
      },
      .bytes = (uint8_t []){},
      .bytes_len = 0,
      .values_len = 0
    },
    .expected_output = {
      .values = (uint16_t []){},
      .result_code = VTENC_OK
    }
  },
  {
    .input = {
      .params = {
        .allow_repeated_values = 0,
        .skip_full_subtrees = 1,
        .min_cluster_length = 1
      },
      .bytes = (uint8_t []){0x33, 0x5a},
      .bytes_len = 2,
      .values_len = 1
    },
    .expected_output = {
      .values = (uint16_t []){23091},
      .result_code = VTENC_OK
    }
  },
  {
    .input = {
      .params = {
        .allow_repeated_values = 0,
        .skip_full_subtrees = 1,
        .min_cluster_length = 1
      },
      .bytes = (uint8_t []){
        0xc6, 0xd9, 0x9d, 0x7f, 0xfa, 0x00, 0x42, 0x02, 0x72, 0x0a, 0xf2, 0x0b,
        0x07, 0x74, 0x45
      },
      .bytes_len = 15,
      .values_len = 8
    },
    .expected_output = {
      .values = (uint16_t []){1655, 3391, 4111, 8770, 29006, 32712, 32993, 58042},
      .result_code = VTENC_OK
    }
  },
  {
    .input = {
      .params = {
        .allow_repeated_values = 0,
        .skip_full_subtrees = 1,
        .min_cluster_length = 1
      },
      .bytes = (uint8_t []){
        0x8c, 0x00, 0x08, 0x80, 0x80, 0x00, 0x48, 0x02, 0x20, 0x09, 0x92
      },
      .bytes_len = 11,
      .values_len = 12
    },
    .expected_output = {
      .values = (uint16_t []){
        14000, 14001, 14002, 14003, 14004, 14005, 14006, 14007,
        20000, 20001, 20002, 20003
      },
      .result_code = VTENC_OK
    }
  },
  {
    .input = {
      .params = {
        .allow_repeated_values = 1,
        .skip_full_subtrees = 0,
        .min_cluster_length = 2
      },
      .bytes = (uint8_t []){
        0xa4, 0x3e, 0x04, 0x96, 0x28, 0x2f, 0xa0, 0x06, 0x16, 0x00
      },
      .bytes_len = 10,
      .values_len = 5
    },
    .expected_output = {
      .values = (uint16_t []){543, 600, 9701, 9888, 32944},
      .result_code = VTENC_OK
    }
  },
  {
    .input = {
      .params = {
        .allow_repeated_values = 1,
        .skip_full_subtrees = 0,
        .min_cluster_length = 4
      },
      .bytes = (uint8_t []){
        0xfc, 0x10, 0x60, 0x09, 0xca, 0x4b, 0xa0, 0x26, 0x58, 0x00
      },
      .bytes_len = 10,
      .values_len = 5
    },
    .expected_output = {
      .values = (uint16_t []){543, 600, 9701, 9888, 32944},
      .result_code = VTENC_OK
    }
  },
  {
    .input = {
      .params = {
        .allow_repeated_values = 1,
        .skip_full_subtrees = 0,
        .min_cluster_length = 8
      },
      .bytes = (uint8_t []){
        0x1f, 0x02, 0x58, 0x02, 0xe5, 0x25, 0xa0, 0x26, 0xb0, 0x80
      },
      .bytes_len = 10,
      .values_len = 5
    },
    .expected_output = {
      .values = (uint16_t []){543, 600, 9701, 9888, 32944},
      .result_code = VTENC_OK
    }
  },
  {
    .input = {
      .params = {
        .allow_repeated_values = 0,
        .skip_full_subtrees = 1,
        .min_cluster_length = 8
      },
      .bytes = (uint8_t []){0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x28},
      .bytes_len = 7,
      .values_len = 9,
    },
    .expected_output = {
      .values = (uint16_t []){0, 1, 2, 3, 4, 5, 6, 7, 10},
      .result_code = VTENC_OK
    }
  }
};

static struct DecodeTestCase test_cases32[] = {
  {
    .input = {
      .params = {
        .allow_repeated_values = 1,
        .skip_full_subtrees = 0,
        .min_cluster_length = 1
      },
      .bytes = (uint8_t []){0x0e},
      .bytes_len = 1,
      .values_len = 4
    },
    .expected_output = {
      .values = (uint32_t []){},
      .result_code = VTENC_ERR_WRONG_FORMAT
    }
  },
  {
    .input = {
      .params = {
        .allow_repeated_values = 1,
        .skip_full_subtrees = 0,
        .min_cluster_length = 1
      },
      .bytes = (uint8_t []){},
      .bytes_len = 0,
      .values_len = 0xffffffffffffffffULL
    },
    .expected_output = {
      .values = (uint32_t []){},
      .result_code = VTENC_ERR_OUTPUT_TOO_BIG
    }
  },
  {
    .input = {
      .params = {
        .allow_repeated_values = 1,
        .skip_full_subtrees = 0,
        .min_cluster_length = 1
      },
      .bytes = (uint8_t []){},
      .bytes_len = 0,
      .values_len = 0
    },
    .expected_output = {
      .values = (uint32_t []){},
      .result_code = VTENC_OK
    }
  },
  {
    .input = {
      .params = {
        .allow_repeated_values = 1,
        .skip_full_subtrees = 0,
        .min_cluster_length = 1
      },
      .bytes = (uint8_t []){0x59, 0x48, 0x4e, 0x2b},
      .bytes_len = 4,
      .values_len = 1
    },
    .expected_output = {
      .values = (uint32_t []){726550617},
      .result_code = VTENC_OK
    }
  },
  {
    .input = {
      .params = {
        .allow_repeated_values = 1,
        .skip_full_subtrees = 0,
        .min_cluster_length = 1
      },
      .bytes = (uint8_t []){
        0x25, 0xb7, 0x1a, 0x39, 0x05, 0xa0, 0x46, 0xf7, 0x88, 0x21, 0x1d, 0x54,
        0x43, 0xd0, 0x09, 0x08, 0xca, 0x27, 0x5a
      },
      .bytes_len = 19,
      .values_len = 5
    },
    .expected_output = {
      .values = (uint32_t []){
        5348, 13089333, 88199704, 271008013, 1451881090
      },
      .result_code = VTENC_OK
    }
  },
  {
    .input = {
      .params = {
        .allow_repeated_values = 1,
        .skip_full_subtrees = 0,
        .min_cluster_length = 1
      },
      .bytes = (uint8_t []){
        0xb6, 0x49, 0x90, 0x20, 0x48, 0x90, 0x24, 0x48, 0x02, 0x20, 0x8, 0x10,
        0x8a, 0xa0, 0x82, 0x8a, 0xa8, 0x0a, 0x82
      },
      .bytes_len = 19,
      .values_len = 6
    },
    .expected_output = {
      .values = (uint32_t []){
        77865901, 77865901, 77865901, 77865901, 314976310, 314976310
      },
      .result_code = VTENC_OK
    }
  },
  {
    .input = {
      .params = {
        .allow_repeated_values = 0,
        .skip_full_subtrees = 1,
        .min_cluster_length = 1
      },
      .bytes = (uint8_t []){0xff},
      .bytes_len = 1,
      .values_len = 4
    },
    .expected_output = {
      .values = (uint32_t []){},
      .result_code = VTENC_ERR_WRONG_FORMAT
    }
  },
  {
    .input = {
      .params = {
        .allow_repeated_values = 0,
        .skip_full_subtrees = 1,
        .min_cluster_length = 1
      },
      .bytes = (uint8_t []){},
      .bytes_len = 0,
      .values_len = 0x200000000
    },
    .expected_output = {
      .values = (uint32_t []){},
      .result_code = VTENC_ERR_OUTPUT_TOO_BIG
    }
  },
  {
    .input = {
      .params = {
        .allow_repeated_values = 0,
        .skip_full_subtrees = 1,
        .min_cluster_length = 1
      },
      .bytes = (uint8_t []){},
      .bytes_len = 0,
      .values_len = 0
    },
    .expected_output = {
      .values = (uint32_t []){},
      .result_code = VTENC_OK
    }
  },
  {
    .input = {
      .params = {
        .allow_repeated_values = 0,
        .skip_full_subtrees = 1,
        .min_cluster_length = 1
      },
      .bytes = (uint8_t []){0x42, 0xba, 0xe3, 0x77},
      .bytes_len = 4,
      .values_len = 1
    },
    .expected_output = {
      .values = (uint32_t []){0x77e3ba42},
      .result_code = VTENC_OK
    }
  },
  {
    .input = {
      .params = {
        .allow_repeated_values = 0,
        .skip_full_subtrees = 1,
        .min_cluster_length = 1
      },
      .bytes = (uint8_t []){
        0x9c, 0x11, 0xc8, 0x62, 0x02, 0xed, 0xea, 0x8b, 0xc0, 0x3b, 0x3b, 0xde,
        0xc7, 0x55, 0xe6, 0x7b, 0x37, 0xc1, 0x80, 0x04
      },
      .bytes_len = 20,
      .values_len = 5
    },
    .expected_output = {
      .values = (uint32_t []){
        0x98b204, 0x122fabb4, 0x378ecef0, 0x77ccab8f, 0xa40609bb
      },
      .result_code = VTENC_OK
    }
  },
  {
    .input = {
      .params = {
        .allow_repeated_values = 0,
        .skip_full_subtrees = 1,
        .min_cluster_length = 1
      },
      .bytes = (uint8_t []){
        0xee, 0xee, 0xee, 0xee, 0x46, 0x92, 0x24, 0x41, 0x90, 0x20, 0x48, 0x92,
        0x54, 0x04, 0x04, 0x04, 0x55, 0x15, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x10, 0x11, 0x11
      },
      .bytes_len = 28,
      .values_len = 14
    },
    .expected_output = {
      .values = (uint32_t []){
        0xa500, 0xa501, 0xa502, 0xa503,
        0x4bbb00, 0x4bbb01,
        0xffff00, 0xffff01, 0xffff02, 0xffff03, 0xffff04, 0xffff05, 0xffff06, 0xffff07
      },
      .result_code = VTENC_OK
    }
  },
  {
    .input = {
      .params = {
        .allow_repeated_values = 1,
        .skip_full_subtrees = 0,
        .min_cluster_length = 2
      },
      .bytes = (uint8_t []){
        0x20, 0x09, 0x52, 0x05, 0xab, 0xf1, 0x09, 0xab, 0xf1, 0xd0, 0x3b, 0x63,
        0xdf, 0x3b, 0x63, 0xfe, 0x6f, 0x11, 0x08
      },
      .bytes_len = 19,
      .values_len = 5
    },
    .expected_output = {
      .values = (uint32_t []){
        0x88f1ab05, 0x88f1ab09, 0x89633bd0, 0x89633bdf, 0xc8116ffe
      },
      .result_code = VTENC_OK
    }
  },
  {
    .input = {
      .params = {
        .allow_repeated_values = 1,
        .skip_full_subtrees = 0,
        .min_cluster_length = 4
      },
      .bytes = (uint8_t []){
        0x60, 0xc1, 0x6a, 0x3c, 0x92, 0xb0, 0x1a, 0x8f, 0x40, 0xef, 0x8c, 0x25,
        0xdf, 0x3b, 0x63, 0x89, 0xff, 0x5b, 0x04, 0x02
      },
      .bytes_len = 20,
      .values_len = 5
    },
    .expected_output = {
      .values = (uint32_t []){
        0x88f1ab05, 0x88f1ab09, 0x89633bd0, 0x89633bdf, 0xc8116ffe
      },
      .result_code = VTENC_OK
    }
  },
  {
    .input = {
      .params = {
        .allow_repeated_values = 1,
        .skip_full_subtrees = 0,
        .min_cluster_length = 8
      },
      .bytes = (uint8_t []){
        0x05, 0xab, 0xf1, 0x88, 0x09, 0xab, 0xf1, 0x88, 0xd0, 0x3b, 0x63, 0x89,
        0xdf, 0x3b, 0x63, 0x89, 0xfe, 0x6f, 0x11, 0xc8
      },
      .bytes_len = 20,
      .values_len = 5
    },
    .expected_output = {
      .values = (uint32_t []){
        0x88f1ab05, 0x88f1ab09, 0x89633bd0, 0x89633bdf, 0xc8116ffe
      },
      .result_code = VTENC_OK
    }
  },
  {
    .input = {
      .params = {
        .allow_repeated_values = 0,
        .skip_full_subtrees = 1,
        .min_cluster_length = 8
      },
      .bytes = (uint8_t []){
        0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99,
        0x99, 0x99, 0x28
      },
      .bytes_len = 15,
      .values_len = 9,
    },
    .expected_output = {
      .values = (uint32_t []){0, 1, 2, 3, 4, 5, 6, 7, 10},
      .result_code = VTENC_OK
    }
  }
};

static struct DecodeTestCase test_cases64[] = {
  {
    .input = {
      .params = {
        .allow_repeated_values = 1,
        .skip_full_subtrees = 0,
        .min_cluster_length = 1
      },
      .bytes = (uint8_t []){0x0e},
      .bytes_len = 1,
      .values_len = 4
    },
    .expected_output = {
      .values = (uint64_t []){},
      .result_code = VTENC_ERR_WRONG_FORMAT
    }
  },
  {
    .input = {
      .params = {
        .allow_repeated_values = 1,
        .skip_full_subtrees = 0,
        .min_cluster_length = 1
      },
      .bytes = (uint8_t []){},
      .bytes_len = 0,
      .values_len = 0xffffffffffffffffULL
    },
    .expected_output = {
      .values = (uint64_t []){},
      .result_code = VTENC_ERR_OUTPUT_TOO_BIG
    }
  },
  {
    .input = {
      .params = {
        .allow_repeated_values = 1,
        .skip_full_subtrees = 0,
        .min_cluster_length = 1
      },
      .bytes = (uint8_t []){},
      .bytes_len = 0,
      .values_len = 0
    },
    .expected_output = {
      .values = (uint64_t []){},
      .result_code = VTENC_OK
    }
  },
  {
    .input = {
      .params = {
        .allow_repeated_values = 1,
        .skip_full_subtrees = 0,
        .min_cluster_length = 1
      },
      .bytes = (uint8_t []){
        0x61, 0x22, 0xc4, 0xfe, 0x90, 0x81, 0x77, 0xab
      },
      .bytes_len = 8,
      .values_len = 1
    },
    .expected_output = {
      .values = (uint64_t []){0xab778190fec42261ULL},
      .result_code = VTENC_OK
    }
  },
  {
    .input = {
      .params = {
        .allow_repeated_values = 1,
        .skip_full_subtrees = 0,
        .min_cluster_length = 1
      },
      .bytes = (uint8_t []){
        0x24, 0x49, 0x92, 0x24, 0x49, 0x92, 0xe4, 0xfe, 0xff, 0xff, 0x57, 0x55,
        0xcd, 0x54, 0x02, 0x00, 0xdf, 0xad, 0xd8, 0xa5, 0x0d, 0xfd, 0xab, 0x6a,
        0x8e, 0x3b, 0x96, 0x04
      },
      .bytes_len = 28,
      .values_len = 4
    },
    .expected_output = {
      .values = (uint64_t []){
        0x12a6ULL, 0x8addf0ULL, 0xffa1b4bbULL, 0x21258ee39aaaULL
      },
      .result_code = VTENC_OK
    }
  },
  {
    .input = {
      .params = {
        .allow_repeated_values = 1,
        .skip_full_subtrees = 0,
        .min_cluster_length = 1
      },
      .bytes = (uint8_t []){
        0x6d, 0xdb, 0xb6, 0x6d, 0xdb, 0xb6, 0x6d, 0xf7, 0xff, 0xff, 0x3f, 0x33,
        0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0xa3, 0xa2, 0xa2, 0xa2, 0xa2, 0xa2,
        0xa2, 0xa2, 0xa2, 0xa2, 0xa2, 0x02
      },
      .bytes_len = 30,
      .values_len = 5
    },
    .expected_output = {
      .values = (uint64_t []){
        0x55555555ULL, 0x55555555ULL, 0x55555555ULL,
        0x111111111111ULL, 0x111111111111ULL
      },
      .result_code = VTENC_OK
    }
  },
  {
    .input = {
      .params = {
        .allow_repeated_values = 0,
        .skip_full_subtrees = 1,
        .min_cluster_length = 1
      },
      .bytes = (uint8_t []){0xfe},
      .bytes_len = 1,
      .values_len = 4
    },
    .expected_output = {
      .values = (uint64_t []){},
      .result_code = VTENC_ERR_WRONG_FORMAT
    }
  },
  {
    .input = {
      .params = {
        .allow_repeated_values = 0,
        .skip_full_subtrees = 1,
        .min_cluster_length = 1
      },
      .bytes = (uint8_t []){},
      .bytes_len = 0,
      .values_len = 0xffffffffffffffffULL
    },
    .expected_output = {
      .values = (uint64_t []){},
      .result_code = VTENC_ERR_OUTPUT_TOO_BIG
    }
  },
  {
    .input = {
      .params = {
        .allow_repeated_values = 0,
        .skip_full_subtrees = 1,
        .min_cluster_length = 1
      },
      .bytes = (uint8_t []){},
      .bytes_len = 0,
      .values_len = 0
    },
    .expected_output = {
      .values = (uint64_t []){},
      .result_code = VTENC_OK
    }
  },
  {
    .input = {
      .params = {
        .allow_repeated_values = 0,
        .skip_full_subtrees = 1,
        .min_cluster_length = 1
      },
      .bytes = (uint8_t []){
        0x88, 0x77, 0x66, 0x55, 0x44, 0x33, 0x22, 0x11
      },
      .bytes_len = 8,
      .values_len = 1
    },
    .expected_output = {
      .values = (uint64_t []){0x1122334455667788ULL},
      .result_code = VTENC_OK
    }
  },
  {
    .input = {
      .params = {
        .allow_repeated_values = 0,
        .skip_full_subtrees = 1,
        .min_cluster_length = 1
      },
      .bytes = (uint8_t []){
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x6d, 0xdb, 0xb6, 0xdc, 0xaa, 0x46,
        0x34, 0x23, 0x12, 0xe9, 0x66, 0xde, 0x55, 0x41, 0x40, 0x40, 0x40, 0x40,
        0x55, 0x55, 0x55, 0x55, 0x05, 0x0f, 0x0f, 0x0f, 0x0f, 0x8f, 0xa8, 0xca,
        0xec, 0x0e, 0x31, 0x73, 0xff, 0x77, 0xff, 0x77, 0xff, 0x01
      },
      .bytes_len = 46,
      .values_len = 7
    },
    .expected_output = {
      .values = (uint64_t []){
        0x11223344ULL, 0xaabbccddULL, 0x1010101010ULL, 0x5555555555ULL, 0xf0f0f0f0f0ULL,
        0x998877665544ULL, 0xffeeffeeffeeULL
      },
      .result_code = VTENC_OK
    }
  },
  {
    .input = {
      .params = {
        .allow_repeated_values = 0,
        .skip_full_subtrees = 1,
        .min_cluster_length = 1
      },
      .bytes = (uint8_t []){
        0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88,
        0x88, 0x66, 0xdb, 0x26, 0x41, 0x92, 0x24, 0x49, 0x92, 0x24, 0x49, 0x92,
        0x24, 0x49, 0x52, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55,
        0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x01
      },
      .bytes_len = 44,
      .values_len = 8
    },
    .expected_output = {
      .values = (uint64_t []){
        0x20000000ULL, 0x20000001ULL, 0x20000002ULL, 0x20000003ULL,
        0x80000000ULL, 0x80000001ULL,
        0x2000000000ULL, 0x2000000001ULL
      },
      .result_code = VTENC_OK
    }
  },
  {
    .input = {
      .params = {
        .allow_repeated_values = 1,
        .skip_full_subtrees = 0,
        .min_cluster_length = 2
      },
      .bytes = (uint8_t []){
        0xb6, 0x6d, 0xdb, 0xb6, 0x6d, 0xdb, 0x26, 0x40, 0x92, 0x24, 0x49, 0x92,
        0x24, 0x49, 0x92, 0x24, 0x49, 0x52, 0x01, 0x00, 0x0f, 0x00, 0x01, 0x00,
        0x0f, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x03, 0x00, 0x00, 0x00,
        0x00, 0x08
      },
      .bytes_len = 38,
      .values_len = 6
    },
    .expected_output = {
      .values = (uint64_t []){
        0x300000000001ULL, 0x30000000000fULL,
        0x300000010001ULL, 0x30000001000fULL,
        0x600000000001ULL, 0x60000000000fULL
      },
      .result_code = VTENC_OK
    }
  },
  {
    .input = {
      .params = {
        .allow_repeated_values = 1,
        .skip_full_subtrees = 0,
        .min_cluster_length = 4
      },
      .bytes = (uint8_t []){
        0xb6, 0x6d, 0xdb, 0xb6, 0x6d, 0xdb, 0x66, 0x00, 0x00, 0x00, 0x00, 0x00,
        0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x04, 0x00, 0x00, 0xc0,
        0x0f, 0x00, 0x01, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x02
      },
      .bytes_len = 42,
      .values_len = 6
    },
    .expected_output = {
      .values = (uint64_t []){
        0x300000000001ULL, 0x30000000000fULL,
        0x300000010001ULL, 0x30000001000fULL,
        0x600000000001ULL, 0x60000000000fULL
      },
      .result_code = VTENC_OK
    }
  },
  {
    .input = {
      .params = {
        .allow_repeated_values = 1,
        .skip_full_subtrees = 0,
        .min_cluster_length = 8
      },
      .bytes = (uint8_t []){
        0x01, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00,
        0x00, 0x30, 0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x30, 0x00, 0x00,
        0x0f, 0x00, 0x01, 0x00, 0x00, 0x30, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
        0x00, 0x60, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00
      },
      .bytes_len = 48,
      .values_len = 6
    },
    .expected_output = {
      .values = (uint64_t []){
        0x300000000001ULL, 0x30000000000fULL,
        0x300000010001ULL, 0x30000001000fULL,
        0x600000000001ULL, 0x60000000000fULL
      },
      .result_code = VTENC_OK
    }
  },
  {
    .input = {
      .params = {
        .allow_repeated_values = 0,
        .skip_full_subtrees = 1,
        .min_cluster_length = 8
      },
      .bytes = (uint8_t []){
        0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99,
        0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99,
        0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x28
      },
      .bytes_len = 31,
      .values_len = 9,
    },
    .expected_output = {
      .values = (uint64_t []){
        0ULL, 1ULL, 2ULL, 3ULL, 4ULL, 5ULL, 6ULL, 7ULL, 10ULL
      },
      .result_code = VTENC_OK
    }
  }
};

int vtenc_decode8_test_case(struct DecodeTestCase *test_case)
{
  struct DecodeTestCaseInput *input = &(test_case->input);
  struct DecodeTestCaseOutput *expected_output = &(test_case->expected_output);
  uint8_t out[input->values_len & 0xffff]; // mask length to avoid large allocations on the stack
  int rc;
  vtenc *decoder = vtenc_create();
  assert(decoder != NULL);

  vtenc_config(decoder, VTENC_CONFIG_ALLOW_REPEATED_VALUES, input->params.allow_repeated_values);
  vtenc_config(decoder, VTENC_CONFIG_SKIP_FULL_SUBTREES, input->params.skip_full_subtrees);
  vtenc_config(decoder, VTENC_CONFIG_MIN_CLUSTER_LENGTH, input->params.min_cluster_length);

  rc = vtenc_decode8(
    decoder,
    input->bytes,
    input->bytes_len,
    out,
    input->values_len
  );

  EXPECT_TRUE(rc == expected_output->result_code);
  if (rc == VTENC_OK) {
    EXPECT_TRUE(memcmp(out, expected_output->values, sizeof(out)) == 0);
  }

  vtenc_destroy(decoder);

  return 1;
}

int vtenc_decode16_test_case(struct DecodeTestCase *test_case)
{
  struct DecodeTestCaseInput *input = &(test_case->input);
  struct DecodeTestCaseOutput *expected_output = &(test_case->expected_output);
  uint16_t out[input->values_len & 0xffff]; // mask length to avoid large allocations on the stack
  int rc;
  vtenc *decoder = vtenc_create();
  assert(decoder != NULL);

  vtenc_config(decoder, VTENC_CONFIG_ALLOW_REPEATED_VALUES, input->params.allow_repeated_values);
  vtenc_config(decoder, VTENC_CONFIG_SKIP_FULL_SUBTREES, input->params.skip_full_subtrees);
  vtenc_config(decoder, VTENC_CONFIG_MIN_CLUSTER_LENGTH, input->params.min_cluster_length);

  rc = vtenc_decode16(
    decoder,
    input->bytes,
    input->bytes_len,
    out,
    input->values_len
  );

  EXPECT_TRUE(rc == expected_output->result_code);
  if (rc == VTENC_OK) {
    EXPECT_TRUE(memcmp(out, expected_output->values, sizeof(out)) == 0);
  }

  vtenc_destroy(decoder);

  return 1;
}

int vtenc_decode32_test_case(struct DecodeTestCase *test_case)
{
  struct DecodeTestCaseInput *input = &(test_case->input);
  struct DecodeTestCaseOutput *expected_output = &(test_case->expected_output);
  uint32_t out[input->values_len & 0xffff]; // mask length to avoid large allocations on the stack
  int rc;
  vtenc *decoder = vtenc_create();
  assert(decoder != NULL);

  vtenc_config(decoder, VTENC_CONFIG_ALLOW_REPEATED_VALUES, input->params.allow_repeated_values);
  vtenc_config(decoder, VTENC_CONFIG_SKIP_FULL_SUBTREES, input->params.skip_full_subtrees);
  vtenc_config(decoder, VTENC_CONFIG_MIN_CLUSTER_LENGTH, input->params.min_cluster_length);

  rc = vtenc_decode32(
    decoder,
    input->bytes,
    input->bytes_len,
    out,
    input->values_len
  );

  EXPECT_TRUE(rc == expected_output->result_code);
  if (rc == VTENC_OK) {
    EXPECT_TRUE(memcmp(out, expected_output->values, sizeof(out)) == 0);
  }

  vtenc_destroy(decoder);

  return 1;
}

int vtenc_decode64_test_case(struct DecodeTestCase *test_case)
{
  struct DecodeTestCaseInput *input = &(test_case->input);
  struct DecodeTestCaseOutput *expected_output = &(test_case->expected_output);
  uint64_t out[input->values_len & 0xffff]; // mask length to avoid large allocations on the stack
  int rc;
  vtenc *decoder = vtenc_create();
  assert(decoder != NULL);

  vtenc_config(decoder, VTENC_CONFIG_ALLOW_REPEATED_VALUES, input->params.allow_repeated_values);
  vtenc_config(decoder, VTENC_CONFIG_SKIP_FULL_SUBTREES, input->params.skip_full_subtrees);
  vtenc_config(decoder, VTENC_CONFIG_MIN_CLUSTER_LENGTH, input->params.min_cluster_length);

  rc = vtenc_decode64(
    decoder,
    input->bytes,
    input->bytes_len,
    out,
    input->values_len
  );

  EXPECT_TRUE(rc == expected_output->result_code);
  if (rc == VTENC_OK) {
    EXPECT_TRUE(memcmp(out, expected_output->values, sizeof(out)) == 0);
  }

  vtenc_destroy(decoder);

  return 1;
}

int test_vtenc_decode8(void)
{
  const size_t test_cases8_size = sizeof(test_cases8) / sizeof(test_cases8[0]);
  size_t i;
  char msg[30];

  for (i = 0; i < test_cases8_size; ++i) {
    sprintf(msg, "test case #%lu", i);
    EXPECT_TRUE_MSG(vtenc_decode8_test_case(&test_cases8[i]), msg);
  }

  return 1;
}

int test_vtenc_decode16(void)
{
  const size_t test_cases16_size = sizeof(test_cases16) / sizeof(test_cases16[0]);
  size_t i;
  char msg[30];

  for (i = 0; i < test_cases16_size; ++i) {
    sprintf(msg, "test case #%lu", i);
    EXPECT_TRUE_MSG(vtenc_decode16_test_case(&test_cases16[i]), msg);
  }

  return 1;
}

int test_vtenc_decode32(void)
{
  const size_t test_cases32_size = sizeof(test_cases32) / sizeof(test_cases32[0]);
  size_t i;
  char msg[30];

  for (i = 0; i < test_cases32_size; ++i) {
    sprintf(msg, "test case #%lu", i);
    EXPECT_TRUE_MSG(vtenc_decode32_test_case(&test_cases32[i]), msg);
  }

  return 1;
}

int test_vtenc_decode64(void)
{
  const size_t test_cases64_size = sizeof(test_cases64) / sizeof(test_cases64[0]);
  size_t i;
  char msg[30];

  for (i = 0; i < test_cases64_size; ++i) {
    sprintf(msg, "test case #%lu", i);
    EXPECT_TRUE_MSG(vtenc_decode64_test_case(&test_cases64[i]), msg);
  }

  return 1;
}
