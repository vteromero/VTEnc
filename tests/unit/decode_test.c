/**
  Copyright (c) 2019 Vicente Romero Calero. All rights reserved.
  Licensed under the MIT License.
  See LICENSE file in the project root for full license information.
 */
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "unit_tests.h"
#include "../../vtenc.h"

int test_vtenc_decoder_init(void)
{
  VtencDecoder dec;

  vtenc_decoder_init(&dec);

  EXPECT_TRUE(dec.allow_repeated_values == 1);
  EXPECT_TRUE(dec.skip_full_subtrees == 1);
  EXPECT_TRUE(dec.last_error_code == VtencErrorNoError);

  return 1;
}

struct DecodeTestCaseInput {
  VtencDecoder decoder;
  const uint8_t *bytes;
  size_t bytes_len;
  size_t values_len;
};

struct DecodeTestCaseOutput {
  void *values;
  VtencErrorCode last_error_code;
};

struct DecodeTestCase {
  struct DecodeTestCaseInput input;
  struct DecodeTestCaseOutput expected_output;
};

static struct DecodeTestCase test_cases8[] = {
  {
    .input = {
      .decoder = {
        .allow_repeated_values = 1,
        .skip_full_subtrees = 0
      },
      .bytes = (uint8_t []){0x0e},
      .bytes_len = 1,
      .values_len = 4,
    },
    .expected_output = {
      .values = (uint8_t []){},
      .last_error_code = VtencErrorWrongFormat
    }
  },
  {
    .input = {
      .decoder = {
        .allow_repeated_values = 1,
        .skip_full_subtrees = 0
      },
      .bytes = (uint8_t []){},
      .bytes_len = 0,
      .values_len = 0xffffffffffffffffULL,
    },
    .expected_output = {
      .values = (uint8_t []){},
      .last_error_code = VtencErrorOutputTooBig
    }
  },
  // {
  //   .input = {
  //     .decoder = {
  //       .allow_repeated_values = 1,
  //       .skip_full_subtrees = 0
  //     },
  //     .bytes = (uint8_t []){},
  //     .bytes_len = 0,
  //     .values_len = 0
  //   },
  //   .expected_output = {
  //     .values = (uint8_t []){},
  //     .last_error_code = VtencErrorNoError
  //   }
  // },
  {
    .input = {
      .decoder = {
        .allow_repeated_values = 1,
        .skip_full_subtrees = 0
      },
      .bytes = (uint8_t []){0x26},
      .bytes_len = 1,
      .values_len = 1,
    },
    .expected_output = {
      .values = (uint8_t []){38},
      .last_error_code = VtencErrorNoError
    }
  },
  {
    .input = {
      .decoder = {
        .allow_repeated_values = 1,
        .skip_full_subtrees = 0
      },
      .bytes = (uint8_t []){
        0x98, 0x66, 0xc9, 0x55, 0xd1, 0x65, 0x39, 0x27, 0x54
      },
      .bytes_len = 9,
      .values_len = 11,
    },
    .expected_output = {
      .values = (uint8_t []){5, 22, 23, 44, 62, 69, 109, 113, 178, 194, 206},
      .last_error_code = VtencErrorNoError
    }
  },
  {
    .input = {
      .decoder = {
        .allow_repeated_values = 1,
        .skip_full_subtrees = 0
      },
      .bytes = (uint8_t []){0x87, 0xa8, 0x0e, 0x04, 0x00, 0xe0, 0x01},
      .bytes_len = 7,
      .values_len = 9,
    },
    .expected_output = {
      .values = (uint8_t []){57, 57, 57, 111, 111, 111, 111, 208, 208},
      .last_error_code = VtencErrorNoError
    }
  },
  {
    .input = {
      .decoder = {
        .allow_repeated_values = 0,
        .skip_full_subtrees = 1
      },
      .bytes = (uint8_t []){0xff},
      .bytes_len = 1,
      .values_len = 4,
    },
    .expected_output = {
      .values = (uint8_t []){},
      .last_error_code = VtencErrorWrongFormat
    }
  },
  {
    .input = {
      .decoder = {
        .allow_repeated_values = 0,
        .skip_full_subtrees = 1
      },
      .bytes = (uint8_t []){},
      .bytes_len = 0,
      .values_len = 257,
    },
    .expected_output = {
      .values = (uint8_t []){},
      .last_error_code = VtencErrorOutputTooBig
    }
  },
  // {
  //   .input = {
  //     .decoder = {
  //       .allow_repeated_values = 0,
  //       .skip_full_subtrees = 1
  //     },
  //     .bytes = (uint8_t []){},
  //     .bytes_len = 0,
  //     .values_len = 0,
  //   },
  //   .expected_output = {
  //     .values = (uint8_t []){},
  //     .last_error_code = VtencErrorNoError
  //   }
  // },
  // {
  //   .input = {
  //     .decoder = {
  //       .allow_repeated_values = 0,
  //       .skip_full_subtrees = 1
  //     },
  //     .bytes = (uint8_t []){},
  //     .bytes_len = 0,
  //     .values_len = 256,
  //   },
  //   .expected_output = {
  //     .values = (uint8_t []){
  //       0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
  //       20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37,
  //       38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55,
  //       56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73,
  //       74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91,
  //       92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107,
  //       108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121,
  //       122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135,
  //       136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 147, 148, 149,
  //       150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160, 161, 162, 163,
  //       164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 176, 177,
  //       178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191,
  //       192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205,
  //       206, 207, 208, 209, 210, 211, 212, 213, 214, 215, 216, 217, 218, 219,
  //       220, 221, 222, 223, 224, 225, 226, 227, 228, 229, 230, 231, 232, 233,
  //       234, 235, 236, 237, 238, 239, 240, 241, 242, 243, 244, 245, 246, 247,
  //       248, 249, 250, 251, 252, 253, 254, 255
  //     },
  //     .last_error_code = VtencErrorNoError
  //   }
  // },
  {
    .input = {
      .decoder = {
        .allow_repeated_values = 0,
        .skip_full_subtrees = 1
      },
      .bytes = (uint8_t []){0x21},
      .bytes_len = 1,
      .values_len = 1,
    },
    .expected_output = {
      .values = (uint8_t []){33},
      .last_error_code = VtencErrorNoError
    }
  },
  {
    .input = {
      .decoder = {
        .allow_repeated_values = 0,
        .skip_full_subtrees = 1
      },
      .bytes = (uint8_t []){0x48, 0x90, 0x44, 0x44, 0x04},
      .bytes_len = 5,
      .values_len = 12,
    },
    .expected_output = {
      .values = (uint8_t []){0, 1, 2, 3, 4, 5, 6, 7, 160, 161, 162, 163},
      .last_error_code = VtencErrorNoError
    }
  },
  {
    .input = {
      .decoder = {
        .allow_repeated_values = 0,
        .skip_full_subtrees = 1
      },
      .bytes = (uint8_t []){0x8c, 0xaa, 0x72, 0x14, 0xdd, 0x00},
      .bytes_len = 6,
      .values_len = 6,
    },
    .expected_output = {
      .values = (uint8_t []){13, 77, 88, 93, 149, 212},
      .last_error_code = VtencErrorNoError
    }
  }
};

static struct DecodeTestCase test_cases16[] = {
  {
    .input = {
      .decoder = {
        .allow_repeated_values = 1,
        .skip_full_subtrees = 0
      },
      .bytes = (uint8_t []){0x0e},
      .bytes_len = 1,
      .values_len = 4
    },
    .expected_output = {
      .values = (uint16_t []){},
      .last_error_code = VtencErrorWrongFormat
    }
  },
  {
    .input = {
      .decoder = {
        .allow_repeated_values = 1,
        .skip_full_subtrees = 0
      },
      .bytes = (uint8_t []){},
      .bytes_len = 0,
      .values_len = 0xffffffffffffffffULL
    },
    .expected_output = {
      .values = (uint16_t []){},
      .last_error_code = VtencErrorOutputTooBig
    }
  },
  // {
  //   .input = {
  //     .decoder = {
  //       .allow_repeated_values = 1,
  //       .skip_full_subtrees = 0
  //     },
  //     .bytes = (uint8_t []){},
  //     .bytes_len = 0,
  //     .values_len = 0
  //   },
  //   .expected_output = {
  //     .values = (uint16_t []){},
  //     .last_error_code = VtencErrorNoError
  //   }
  // },
  {
    .input = {
      .decoder = {
        .allow_repeated_values = 1,
        .skip_full_subtrees = 0
      },
      .bytes = (uint8_t []){0x26, 0x36},
      .bytes_len = 2,
      .values_len = 1
    },
    .expected_output = {
      .values = (uint16_t []){13862},
      .last_error_code = VtencErrorNoError
    }
  },
  {
    .input = {
      .decoder = {
        .allow_repeated_values = 1,
        .skip_full_subtrees = 0
      },
      .bytes = (uint8_t []){
        0x6d, 0x74, 0xb8, 0x55, 0x46, 0x49, 0x61, 0xc0, 0x6b, 0xfa, 0xcd, 0x62,
        0x89
      },
      .bytes_len = 13,
      .values_len = 7
    },
    .expected_output = {
      .values = (uint16_t []){1099, 2227, 8102, 27654, 29001, 35511, 50083},
      .last_error_code = VtencErrorNoError
    }
  },
  {
    .input = {
      .decoder = {
        .allow_repeated_values = 1,
        .skip_full_subtrees = 0
      },
      .bytes = (uint8_t []){
        0x88, 0xd3, 0x16, 0x45, 0x81, 0xb6, 0xf8, 0x99, 0x79, 0x06
      },
      .bytes_len = 10,
      .values_len = 8
    },
    .expected_output = {
      .values = (uint16_t []){677, 677, 677, 8881, 8881, 8881, 8881, 8881},
      .last_error_code = VtencErrorNoError
    }
  },
  {
    .input = {
      .decoder = {
        .allow_repeated_values = 0,
        .skip_full_subtrees = 1
      },
      .bytes = (uint8_t []){0xff},
      .bytes_len = 1,
      .values_len = 4
    },
    .expected_output = {
      .values = (uint16_t []){},
      .last_error_code = VtencErrorWrongFormat
    }
  },
  {
    .input = {
      .decoder = {
        .allow_repeated_values = 0,
        .skip_full_subtrees = 1
      },
      .bytes = (uint8_t []){},
      .bytes_len = 0,
      .values_len = 65537
    },
    .expected_output = {
      .values = (uint16_t []){},
      .last_error_code = VtencErrorOutputTooBig
    }
  },
  // {
  //   .input = {
  //     .decoder = {
  //       .allow_repeated_values = 0,
  //       .skip_full_subtrees = 1
  //     },
  //     .bytes = (uint8_t []){},
  //     .bytes_len = 0,
  //     .values_len = 0
  //   },
  //   .expected_output = {
  //     .values = (uint16_t []){},
  //     .last_error_code = VtencErrorNoError
  //   }
  // },
  {
    .input = {
      .decoder = {
        .allow_repeated_values = 0,
        .skip_full_subtrees = 1
      },
      .bytes = (uint8_t []){0x33, 0x5a},
      .bytes_len = 2,
      .values_len = 1
    },
    .expected_output = {
      .values = (uint16_t []){23091},
      .last_error_code = VtencErrorNoError
    }
  },
  {
    .input = {
      .decoder = {
        .allow_repeated_values = 0,
        .skip_full_subtrees = 1
      },
      .bytes = (uint8_t []){
        0x96, 0xae, 0x18, 0x0e, 0x10, 0x42, 0xbe, 0x53, 0x26, 0x24, 0x7c, 0x80,
        0x7e, 0x7a, 0x67
      },
      .bytes_len = 15,
      .values_len = 8
    },
    .expected_output = {
      .values = (uint16_t []){1655, 3391, 4111, 8770, 29006, 32712, 32993, 58042},
      .last_error_code = VtencErrorNoError
    }
  },
  {
    .input = {
      .decoder = {
        .allow_repeated_values = 0,
        .skip_full_subtrees = 1
      },
      .bytes = (uint8_t []){
        0x8c, 0x24, 0x00, 0x92, 0x20, 0x09, 0x80, 0x00, 0x08, 0x08, 0x80
      },
      .bytes_len = 11,
      .values_len = 12
    },
    .expected_output = {
      .values = (uint16_t []){
        14000, 14001, 14002, 14003, 14004, 14005, 14006, 14007,
        20000, 20001, 20002, 20003
      },
      .last_error_code = VtencErrorNoError
    }
  }
};

static struct DecodeTestCase test_cases32[] = {
  {
    .input = {
      .decoder = {
        .allow_repeated_values = 1,
        .skip_full_subtrees = 0
      },
      .bytes = (uint8_t []){0x0e},
      .bytes_len = 1,
      .values_len = 4
    },
    .expected_output = {
      .values = (uint32_t []){},
      .last_error_code = VtencErrorWrongFormat
    }
  },
  {
    .input = {
      .decoder = {
        .allow_repeated_values = 1,
        .skip_full_subtrees = 0
      },
      .bytes = (uint8_t []){},
      .bytes_len = 0,
      .values_len = 0xffffffffffffffffULL
    },
    .expected_output = {
      .values = (uint32_t []){},
      .last_error_code = VtencErrorOutputTooBig
    }
  },
  // {
  //   .input = {
  //     .decoder = {
  //       .allow_repeated_values = 1,
  //       .skip_full_subtrees = 0
  //     },
  //     .bytes = (uint8_t []){},
  //     .bytes_len = 0,
  //     .values_len = 0
  //   },
  //   .expected_output = {
  //     .values = (uint32_t []){},
  //     .last_error_code = VtencErrorNoError
  //   }
  // },
  {
    .input = {
      .decoder = {
        .allow_repeated_values = 1,
        .skip_full_subtrees = 0
      },
      .bytes = (uint8_t []){0x59, 0x48, 0x4e, 0x2b},
      .bytes_len = 4,
      .values_len = 1
    },
    .expected_output = {
      .values = (uint32_t []){726550617},
      .last_error_code = VtencErrorNoError
    }
  },
  {
    .input = {
      .decoder = {
        .allow_repeated_values = 1,
        .skip_full_subtrees = 0
      },
      .bytes = (uint8_t []){
        0xa5, 0xa0, 0x7c, 0xa2, 0xc5, 0x35, 0x04, 0x9d, 0xc0, 0x62, 0x48, 0x07,
        0xa5, 0xd5, 0xe8, 0x1e, 0xc9, 0x29, 0x00
      },
      .bytes_len = 19,
      .values_len = 5
    },
    .expected_output = {
      .values = (uint32_t []){
        5348, 13089333, 88199704, 271008013, 1451881090
      },
      .last_error_code = VtencErrorNoError
    }
  },
  {
    .input = {
      .decoder = {
        .allow_repeated_values = 1,
        .skip_full_subtrees = 0
      },
      .bytes = (uint8_t []){
        0xb6, 0xa9, 0x08, 0x2a, 0xa8, 0x88, 0xaa, 0x20, 0x48, 0x90, 0x20, 0x48,
        0x90, 0x24, 0x48, 0x02, 0x20, 0x08, 0x10
      },
      .bytes_len = 19,
      .values_len = 6
    },
    .expected_output = {
      .values = (uint32_t []){
        77865901, 77865901, 77865901, 77865901, 314976310, 314976310
      },
      .last_error_code = VtencErrorNoError
    }
  },
  {
    .input = {
      .decoder = {
        .allow_repeated_values = 0,
        .skip_full_subtrees = 1
      },
      .bytes = (uint8_t []){0xff},
      .bytes_len = 1,
      .values_len = 4
    },
    .expected_output = {
      .values = (uint32_t []){},
      .last_error_code = VtencErrorWrongFormat
    }
  },
  {
    .input = {
      .decoder = {
        .allow_repeated_values = 0,
        .skip_full_subtrees = 1
      },
      .bytes = (uint8_t []){},
      .bytes_len = 0,
      .values_len = 0x200000000
    },
    .expected_output = {
      .values = (uint32_t []){},
      .last_error_code = VtencErrorOutputTooBig
    }
  },
  // {
  //   .input = {
  //     .decoder = {
  //       .allow_repeated_values = 0,
  //       .skip_full_subtrees = 1
  //     },
  //     .bytes = (uint8_t []){},
  //     .bytes_len = 0,
  //     .values_len = 0
  //   },
  //   .expected_output = {
  //     .values = (uint32_t []){},
  //     .last_error_code = VtencErrorNoError
  //   }
  // },
  {
    .input = {
      .decoder = {
        .allow_repeated_values = 0,
        .skip_full_subtrees = 1
      },
      .bytes = (uint8_t []){0x42, 0xba, 0xe3, 0x77},
      .bytes_len = 4,
      .values_len = 1
    },
    .expected_output = {
      .values = (uint32_t []){0x77e3ba42},
      .last_error_code = VtencErrorNoError
    }
  },
  {
    .input = {
      .decoder = {
        .allow_repeated_values = 0,
        .skip_full_subtrees = 1
      },
      .bytes = (uint8_t []){
        0xdc, 0x4d, 0x30, 0x20, 0xed, 0x71, 0x95, 0xf9, 0x16, 0xde, 0xd9, 0xf1,
        0x46, 0xbb, 0xfa, 0x22, 0x04, 0xb2, 0x98, 0x00
      },
      .bytes_len = 20,
      .values_len = 5
    },
    .expected_output = {
      .values = (uint32_t []){
        0x98b204, 0x122fabb4, 0x378ecef0, 0x77ccab8f, 0xa40609bb
      },
      .last_error_code = VtencErrorNoError
    }
  },
  {
    .input = {
      .decoder = {
        .allow_repeated_values = 0,
        .skip_full_subtrees = 1
      },
      .bytes = (uint8_t []){
        0xee, 0xee, 0xee, 0xee, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x88, 0x88, 0x48, 0x45, 0x40, 0x40, 0x50, 0x55, 0x49, 0x92, 0x04, 0x41,
        0x82, 0x20, 0x49, 0x12
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
      .last_error_code = VtencErrorNoError
    }
  }
};

static struct DecodeTestCase test_cases64[] = {
  {
    .input = {
      .decoder = {
        .allow_repeated_values = 1,
        .skip_full_subtrees = 0
      },
      .bytes = (uint8_t []){0x0e},
      .bytes_len = 1,
      .values_len = 4
    },
    .expected_output = {
      .values = (uint64_t []){},
      .last_error_code = VtencErrorWrongFormat
    }
  },
  {
    .input = {
      .decoder = {
        .allow_repeated_values = 1,
        .skip_full_subtrees = 0
      },
      .bytes = (uint8_t []){},
      .bytes_len = 0,
      .values_len = 0xffffffffffffffffULL
    },
    .expected_output = {
      .values = (uint64_t []){},
      .last_error_code = VtencErrorOutputTooBig
    }
  },
  // {
  //   .input = {
  //     .decoder = {
  //       .allow_repeated_values = 1,
  //       .skip_full_subtrees = 0
  //     },
  //     .bytes = (uint8_t []){},
  //     .bytes_len = 0,
  //     .values_len = 0
  //   },
  //   .expected_output = {
  //     .values = (uint64_t []){},
  //     .last_error_code = VtencErrorNoError
  //   }
  // },
  {
    .input = {
      .decoder = {
        .allow_repeated_values = 1,
        .skip_full_subtrees = 0
      },
      .bytes = (uint8_t []){
        0x61, 0x22, 0xc4, 0xfe, 0x90, 0x81, 0x77, 0xab
      },
      .bytes_len = 8,
      .values_len = 1
    },
    .expected_output = {
      .values = (uint64_t []){0xab778190fec42261ULL},
      .last_error_code = VtencErrorNoError
    }
  },
  {
    .input = {
      .decoder = {
        .allow_repeated_values = 1,
        .skip_full_subtrees = 0
      },
      .bytes = (uint8_t []){
        0x24, 0x49, 0x92, 0x24, 0x49, 0x92, 0xe4, 0x54, 0x35, 0xc7, 0x1d, 0x4b,
        0xc2, 0xff, 0xff, 0xff, 0xee, 0xd2, 0x86, 0xfe, 0x55, 0xd5, 0xe0, 0xbb,
        0x15, 0xa6, 0x12, 0x00
      },
      .bytes_len = 28,
      .values_len = 4
    },
    .expected_output = {
      .values = (uint64_t []){
        0x12a6ULL, 0x8addf0ULL, 0xffa1b4bbULL, 0x21258ee39aaaULL
      },
      .last_error_code = VtencErrorNoError
    }
  },
  {
    .input = {
      .decoder = {
        .allow_repeated_values = 1,
        .skip_full_subtrees = 0
      },
      .bytes = (uint8_t []){
        0x6d, 0xdb, 0xb6, 0x6d, 0xdb, 0xb6, 0x6d, 0xa7, 0xa2, 0xa2, 0xa2, 0xa2,
        0xa2, 0xa2, 0xa2, 0xa2, 0xa2, 0xa2, 0xf2, 0xff, 0xff, 0x3f, 0x33, 0x33,
        0x33, 0x33, 0x33, 0x33, 0x33, 0x03
      },
      .bytes_len = 30,
      .values_len = 5
    },
    .expected_output = {
      .values = (uint64_t []){
        0x55555555ULL, 0x55555555ULL, 0x55555555ULL,
        0x111111111111ULL, 0x111111111111ULL
      },
      .last_error_code = VtencErrorNoError
    }
  },
  {
    .input = {
      .decoder = {
        .allow_repeated_values = 0,
        .skip_full_subtrees = 1
      },
      .bytes = (uint8_t []){0xfe},
      .bytes_len = 1,
      .values_len = 4
    },
    .expected_output = {
      .values = (uint64_t []){},
      .last_error_code = VtencErrorWrongFormat
    }
  },
  {
    .input = {
      .decoder = {
        .allow_repeated_values = 0,
        .skip_full_subtrees = 1
      },
      .bytes = (uint8_t []){},
      .bytes_len = 0,
      .values_len = 0xffffffffffffffffULL
    },
    .expected_output = {
      .values = (uint64_t []){},
      .last_error_code = VtencErrorOutputTooBig
    }
  },
  // {
  //   .input = {
  //     .decoder = {
  //       .allow_repeated_values = 0,
  //       .skip_full_subtrees = 1
  //     },
  //     .bytes = (uint8_t []){},
  //     .bytes_len = 0,
  //     .values_len = 0
  //   },
  //   .expected_output = {
  //     .values = (uint64_t []){},
  //     .last_error_code = VtencErrorNoError
  //   }
  // },
  {
    .input = {
      .decoder = {
        .allow_repeated_values = 0,
        .skip_full_subtrees = 1
      },
      .bytes = (uint8_t []){
        0x88, 0x77, 0x66, 0x55, 0x44, 0x33, 0x22, 0x11
      },
      .bytes_len = 8,
      .values_len = 1
    },
    .expected_output = {
      .values = (uint64_t []){0x1122334455667788ULL},
      .last_error_code = VtencErrorNoError
    }
  },
  {
    .input = {
      .decoder = {
        .allow_repeated_values = 0,
        .skip_full_subtrees = 1
      },
      .bytes = (uint8_t []){
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xcd, 0xfd, 0xdf, 0xfd, 0xdf, 0xfd,
        0x27, 0xaa, 0x32, 0xbb, 0x43, 0xcc, 0xda, 0xb6, 0x2d, 0xe1, 0xe1, 0xe1,
        0xe1, 0xe1, 0xab, 0xaa, 0xaa, 0xaa, 0xaa, 0x16, 0x02, 0x02, 0x02, 0x02,
        0x54, 0xeb, 0x66, 0xde, 0x55, 0x11, 0xcd, 0x88, 0x44, 0x00
      },
      .bytes_len = 46,
      .values_len = 7
    },
    .expected_output = {
      .values = (uint64_t []){
        0x11223344ULL, 0xaabbccddULL, 0x1010101010ULL, 0x5555555555ULL, 0xf0f0f0f0f0ULL,
        0x998877665544ULL, 0xffeeffeeffeeULL
      },
      .last_error_code = VtencErrorNoError
    }
  },
  {
    .input = {
      .decoder = {
        .allow_repeated_values = 0,
        .skip_full_subtrees = 1
      },
      .bytes = (uint8_t []){
        0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88,
        0x88, 0xa6, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0x6a, 0xdb,
        0xa6, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0x12, 0x24, 0x49, 0x92,
        0x24, 0x49, 0x92, 0x24, 0x49, 0x92, 0x24, 0x01
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
      .last_error_code = VtencErrorNoError
    }
  }
};

int vtenc_decode8_test_case(struct DecodeTestCase *test_case)
{
  struct DecodeTestCaseInput *input = &(test_case->input);
  struct DecodeTestCaseOutput *expected_output = &(test_case->expected_output);
  VtencDecoder *decoder = &(input->decoder);
  uint8_t out[input->values_len & 0xffff]; // mask length to avoid large allocations on the stack

  vtenc_decode8(
    decoder,
    input->bytes,
    input->bytes_len,
    out,
    input->values_len
  );

  EXPECT_TRUE(decoder->last_error_code == expected_output->last_error_code);
  if (decoder->last_error_code == VtencErrorNoError) {
    EXPECT_TRUE(memcmp(out, expected_output->values, sizeof(out)) == 0);
  }

  return 1;
}

int vtenc_decode16_test_case(struct DecodeTestCase *test_case)
{
  struct DecodeTestCaseInput *input = &(test_case->input);
  struct DecodeTestCaseOutput *expected_output = &(test_case->expected_output);
  VtencDecoder *decoder = &(input->decoder);
  uint16_t out[input->values_len & 0xffff]; // mask length to avoid large allocations on the stack

  vtenc_decode16(
    decoder,
    input->bytes,
    input->bytes_len,
    out,
    input->values_len
  );

  EXPECT_TRUE(decoder->last_error_code == expected_output->last_error_code);
  if (decoder->last_error_code == VtencErrorNoError) {
    EXPECT_TRUE(memcmp(out, expected_output->values, sizeof(out)) == 0);
  }

  return 1;
}

int vtenc_decode32_test_case(struct DecodeTestCase *test_case)
{
  struct DecodeTestCaseInput *input = &(test_case->input);
  struct DecodeTestCaseOutput *expected_output = &(test_case->expected_output);
  VtencDecoder *decoder = &(input->decoder);
  uint32_t out[input->values_len & 0xffff]; // mask length to avoid large allocations on the stack

  vtenc_decode32(
    decoder,
    input->bytes,
    input->bytes_len,
    out,
    input->values_len
  );

  EXPECT_TRUE(decoder->last_error_code == expected_output->last_error_code);
  if (decoder->last_error_code == VtencErrorNoError) {
    EXPECT_TRUE(memcmp(out, expected_output->values, sizeof(out)) == 0);
  }

  return 1;
}

int vtenc_decode64_test_case(struct DecodeTestCase *test_case)
{
  struct DecodeTestCaseInput *input = &(test_case->input);
  struct DecodeTestCaseOutput *expected_output = &(test_case->expected_output);
  VtencDecoder *decoder = &(input->decoder);
  uint64_t out[input->values_len & 0xffff]; // mask length to avoid large allocations on the stack

  vtenc_decode64(
    decoder,
    input->bytes,
    input->bytes_len,
    out,
    input->values_len
  );

  EXPECT_TRUE(decoder->last_error_code == expected_output->last_error_code);
  if (decoder->last_error_code == VtencErrorNoError) {
    EXPECT_TRUE(memcmp(out, expected_output->values, sizeof(out)) == 0);
  }

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
