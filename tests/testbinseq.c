/**
  Copyright (c) 2020 Vicente Romero Calero. All rights reserved.
  Licensed under the MIT License.
  See LICENSE file in the project root for full license information.
 */
#include <stdio.h>
#include <stdlib.h>

#include "../mem.h"
#include "../vtenc.h"

struct SequenceAttr
{
  unsigned int width;
  size_t size;
  int islist;
};

static void usage(const char *program)
{
  fprintf(stderr,
"Tests encoding and decoding on the sequence stored in the provided binary file.\n"
"\n"
"Usage: %s <file>\n"
"\n",
  program);
}

static int read_u8(FILE *f, uint8_t *value)
{
  size_t n_read = fread(value, 1, 1, f);

  if (n_read < 1) {
    return 0;
  } else {
    return 1;
  }
}

static int read_u16(FILE *f, uint16_t *value)
{
  char buf[2];
  size_t n_read = fread(buf, sizeof(char), sizeof(buf), f);

  if (n_read < sizeof(buf)) {
    return 0;
  } else {
    *value = mem_read_le_u16(buf);
    return 1;
  }
}

static int read_u32(FILE *f, uint32_t *value)
{
  char buf[4];
  size_t n_read = fread(buf, sizeof(char), sizeof(buf), f);

  if (n_read < sizeof(buf)) {
    return 0;
  } else {
    *value = mem_read_le_u32(buf);
    return 1;
  }
}

static int read_u64(FILE *f, uint64_t *value)
{
  char buf[8];
  size_t n_read = fread(buf, sizeof(char), sizeof(buf), f);

  if (n_read < sizeof(buf)) {
    return 0;
  } else {
    *value = mem_read_le_u64(buf);
    return 1;
  }
}

static int read_header(FILE *f, struct SequenceAttr *attr)
{
  uint8_t x;
  uint32_t seqsize;

  if (!read_u8(f, &x)) {
    perror("fread() failed");
    return 0;
  }

  if (!read_u32(f, &seqsize)) {
    perror("fread() failed");
    return 0;
  }

  attr->islist = (int)(x >> 7);
  attr->width = (unsigned int)(x & 0x7f);
  attr->size = (size_t)seqsize;

  return 1;
}

// static void print_sequence_attr(const struct SequenceAttr *attr)
// {
//   printf("Sequence attributes:\n");
//   printf("  islist: %d\n", attr->islist);
//   printf("  width: %u\n", attr->width);
//   printf("  size: %lu\n", attr->size);
// }

static int is_valid_sequence_attr(const struct SequenceAttr *attr)
{
  return attr->width == 8 || attr->width == 16 || attr->width == 32 || attr->width == 64;
}

static int read_arr8(FILE *f, uint8_t *arr, size_t arr_len)
{
  size_t i;

  for (i = 0; i < arr_len; ++i) {
    if (!read_u8(f, arr + i)) {
      perror("fread() failed");
      return 0;
    }
  }

  return 1;
}

static int read_arr16(FILE *f, uint16_t *arr, size_t arr_len)
{
  size_t i;

  for (i = 0; i < arr_len; ++i) {
    if (!read_u16(f, arr + i)) {
      perror("fread() failed");
      return 0;
    }
  }

  return 1;
}

static int read_arr32(FILE *f, uint32_t *arr, size_t arr_len)
{
  size_t i;

  for (i = 0; i < arr_len; ++i) {
    if (!read_u32(f, arr + i)) {
      perror("fread() failed");
      return 0;
    }
  }

  return 1;
}

static int read_arr64(FILE *f, uint64_t *arr, size_t arr_len)
{
  size_t i;

  for (i = 0; i < arr_len; ++i) {
    if (!read_u64(f, arr + i)) {
      perror("fread() failed");
      return 0;
    }
  }

  return 1;
}

// static void print_arr8(uint8_t *arr, size_t arr_len)
// {
//   size_t i;
//   printf("[%lu]:", arr_len);
//   for (i = 0; i < arr_len; ++i) printf(" %u", arr[i]);
//   printf("\n");
// }

// static void print_arr16(uint16_t *arr, size_t arr_len)
// {
//   size_t i;
//   printf("[%lu]:", arr_len);
//   for (i = 0; i < arr_len; ++i) printf(" %u", arr[i]);
//   printf("\n");
// }

// static void print_arr32(uint32_t *arr, size_t arr_len)
// {
//   size_t i;
//   printf("[%lu]:", arr_len);
//   for (i = 0; i < arr_len; ++i) printf(" %u", arr[i]);
//   printf("\n");
// }

// static void print_arr64(uint64_t *arr, size_t arr_len)
// {
//   size_t i;
//   printf("[%lu]:", arr_len);
//   for (i = 0; i < arr_len; ++i) printf(" %lu", arr[i]);
//   printf("\n");
// }

static int test_encdec_list8(uint8_t *list, size_t list_len)
{
  size_t enc_out_cap, enc_out_len, dec_out_len;
  uint8_t *enc_out=NULL, *dec_out=NULL;
  VtencErrorCode enc_ret_code, dec_ret_code;
  int ret_code = 1;

  enc_out_cap = vtenc_list_max_encoded_size_u8(list_len);
  enc_out = (uint8_t *) malloc(enc_out_cap * sizeof(uint8_t));
  if (enc_out == NULL) {
    fprintf(stderr, "allocation error\n");
    ret_code = 0;
    goto free_and_exit;
  }

  enc_ret_code = vtenc_list_encode_u8(list, list_len, enc_out, enc_out_cap, &enc_out_len);
  if (enc_ret_code != VtencErrorNoError) {
    fprintf(stderr, "encode error code: %d\n", enc_ret_code);
    ret_code = 0;
    goto free_and_exit;
  }

  dec_out_len = vtenc_list_decoded_size_u8(enc_out, enc_out_len);
  dec_out = (uint8_t *) malloc(dec_out_len * sizeof(uint8_t));
  if (dec_out == NULL) {
    fprintf(stderr, "allocation error\n");
    ret_code = 0;
    goto free_and_exit;
  }

  dec_ret_code = vtenc_list_decode_u8(enc_out, enc_out_len, dec_out, dec_out_len);
  if (dec_ret_code != VtencErrorNoError) {
    fprintf(stderr, "decode error code: %d\n", dec_ret_code);
    ret_code = 0;
    goto free_and_exit;
  }

  if ((dec_out_len != list_len) || (memcmp(list, dec_out, list_len) != 0)) {
    fprintf(stderr, "decoded output different from original input\n");
    ret_code = 0;
    goto free_and_exit;
  }

free_and_exit:
  if (enc_out != NULL) free(enc_out);
  if (dec_out != NULL) free(dec_out);

  return ret_code;
}

static int test_encdec_list16(uint16_t *list, size_t list_len)
{
  size_t enc_out_cap, enc_out_len, dec_out_len;
  uint8_t *enc_out = NULL;
  uint16_t *dec_out = NULL;
  VtencErrorCode enc_ret_code, dec_ret_code;
  int ret_code = 1;

  enc_out_cap = vtenc_list_max_encoded_size_u16(list_len);
  enc_out = (uint8_t *) malloc(enc_out_cap * sizeof(uint8_t));
  if (enc_out == NULL) {
    fprintf(stderr, "allocation error\n");
    ret_code = 0;
    goto free_and_exit;
  }

  enc_ret_code = vtenc_list_encode_u16(list, list_len, enc_out, enc_out_cap, &enc_out_len);
  if (enc_ret_code != VtencErrorNoError) {
    fprintf(stderr, "encode error code: %d\n", enc_ret_code);
    ret_code = 0;
    goto free_and_exit;
  }

  dec_out_len = vtenc_list_decoded_size_u16(enc_out, enc_out_len);
  dec_out = (uint16_t *) malloc(dec_out_len * sizeof(uint16_t));
  if (dec_out == NULL) {
    fprintf(stderr, "allocation error\n");
    ret_code = 0;
    goto free_and_exit;
  }

  dec_ret_code = vtenc_list_decode_u16(enc_out, enc_out_len, dec_out, dec_out_len);
  if (dec_ret_code != VtencErrorNoError) {
    fprintf(stderr, "decode error code: %d\n", dec_ret_code);
    ret_code = 0;
    goto free_and_exit;
  }

  if ((dec_out_len != list_len) || (memcmp(list, dec_out, list_len * sizeof(uint16_t)) != 0)) {
    fprintf(stderr, "decoded output different from original input\n");
    ret_code = 0;
    goto free_and_exit;
  }

free_and_exit:
  if (enc_out != NULL) free(enc_out);
  if (dec_out != NULL) free(dec_out);

  return ret_code;
}

static int test_encdec_list32(uint32_t *list, size_t list_len)
{
  size_t enc_out_cap, enc_out_len, dec_out_len;
  uint8_t *enc_out = NULL;
  uint32_t *dec_out = NULL;
  VtencErrorCode enc_ret_code, dec_ret_code;
  int ret_code = 1;

  enc_out_cap = vtenc_list_max_encoded_size_u32(list_len);
  enc_out = (uint8_t *) malloc(enc_out_cap * sizeof(uint8_t));
  if (enc_out == NULL) {
    fprintf(stderr, "allocation error\n");
    ret_code = 0;
    goto free_and_exit;
  }

  enc_ret_code = vtenc_list_encode_u32(list, list_len, enc_out, enc_out_cap, &enc_out_len);
  if (enc_ret_code != VtencErrorNoError) {
    fprintf(stderr, "encode error code: %d\n", enc_ret_code);
    ret_code = 0;
    goto free_and_exit;
  }

  dec_out_len = vtenc_list_decoded_size_u32(enc_out, enc_out_len);
  dec_out = (uint32_t *) malloc(dec_out_len * sizeof(uint32_t));
  if (dec_out == NULL) {
    fprintf(stderr, "allocation error\n");
    ret_code = 0;
    goto free_and_exit;
  }

  dec_ret_code = vtenc_list_decode_u32(enc_out, enc_out_len, dec_out, dec_out_len);
  if (dec_ret_code != VtencErrorNoError) {
    fprintf(stderr, "decode error code: %d\n", dec_ret_code);
    ret_code = 0;
    goto free_and_exit;
  }

  if ((dec_out_len != list_len) || (memcmp(list, dec_out, list_len * sizeof(uint32_t)) != 0)) {
    fprintf(stderr, "decoded output different from original input\n");
    ret_code = 0;
    goto free_and_exit;
  }

free_and_exit:
  if (enc_out != NULL) free(enc_out);
  if (dec_out != NULL) free(dec_out);

  return ret_code;
}

static int test_encdec_list64(uint64_t *list, size_t list_len)
{
  size_t enc_out_cap, enc_out_len, dec_out_len;
  uint8_t *enc_out = NULL;
  uint64_t *dec_out = NULL;
  VtencErrorCode enc_ret_code, dec_ret_code;
  int ret_code = 1;

  enc_out_cap = vtenc_list_max_encoded_size_u64(list_len);
  enc_out = (uint8_t *) malloc(enc_out_cap * sizeof(uint8_t));
  if (enc_out == NULL) {
    fprintf(stderr, "allocation error\n");
    ret_code = 0;
    goto free_and_exit;
  }

  enc_ret_code = vtenc_list_encode_u64(list, list_len, enc_out, enc_out_cap, &enc_out_len);
  if (enc_ret_code != VtencErrorNoError) {
    fprintf(stderr, "encode error code: %d\n", enc_ret_code);
    ret_code = 0;
    goto free_and_exit;
  }

  dec_out_len = vtenc_list_decoded_size_u64(enc_out, enc_out_len);
  dec_out = (uint64_t *) malloc(dec_out_len * sizeof(uint64_t));
  if (dec_out == NULL) {
    fprintf(stderr, "allocation error\n");
    ret_code = 0;
    goto free_and_exit;
  }

  dec_ret_code = vtenc_list_decode_u64(enc_out, enc_out_len, dec_out, dec_out_len);
  if (dec_ret_code != VtencErrorNoError) {
    fprintf(stderr, "decode error code: %d\n", dec_ret_code);
    ret_code = 0;
    goto free_and_exit;
  }

  if ((dec_out_len != list_len) || (memcmp(list, dec_out, list_len * sizeof(uint64_t)) != 0)) {
    fprintf(stderr, "decoded output different from original input\n");
    ret_code = 0;
    goto free_and_exit;
  }

free_and_exit:
  if (enc_out != NULL) free(enc_out);
  if (dec_out != NULL) free(dec_out);

  return ret_code;
}

static int test_encdec_set8(uint8_t *set, size_t set_len)
{
  size_t enc_out_cap, enc_out_len, dec_out_len;
  uint8_t *enc_out=NULL, *dec_out=NULL;
  VtencErrorCode enc_ret_code, dec_ret_code;
  int ret_code = 1;

  enc_out_cap = vtenc_set_max_encoded_size_u8(set_len);
  enc_out = (uint8_t *) malloc(enc_out_cap * sizeof(uint8_t));
  if (enc_out == NULL) {
    fprintf(stderr, "allocation error\n");
    ret_code = 0;
    goto free_and_exit;
  }

  enc_ret_code = vtenc_set_encode_u8(set, set_len, enc_out, enc_out_cap, &enc_out_len);
  if (enc_ret_code != VtencErrorNoError) {
    fprintf(stderr, "encode error code: %d\n", enc_ret_code);
    ret_code = 0;
    goto free_and_exit;
  }

  dec_out_len = vtenc_set_decoded_size_u8(enc_out, enc_out_len);
  dec_out = (uint8_t *) malloc(dec_out_len * sizeof(uint8_t));
  if (dec_out == NULL) {
    fprintf(stderr, "allocation error\n");
    ret_code = 0;
    goto free_and_exit;
  }

  dec_ret_code = vtenc_set_decode_u8(enc_out, enc_out_len, dec_out, dec_out_len);
  if (dec_ret_code != VtencErrorNoError) {
    fprintf(stderr, "decode error code: %d\n", dec_ret_code);
    ret_code = 0;
    goto free_and_exit;
  }

  if ((dec_out_len != set_len) || (memcmp(set, dec_out, set_len) != 0)) {
    fprintf(stderr, "decoded output different from original input\n");
    ret_code = 0;
    goto free_and_exit;
  }

free_and_exit:
  if (enc_out != NULL) free(enc_out);
  if (dec_out != NULL) free(dec_out);

  return ret_code;
}

static int test_encdec_set16(uint16_t *set, size_t set_len)
{
  size_t enc_out_cap, enc_out_len, dec_out_len;
  uint8_t *enc_out = NULL;
  uint16_t *dec_out = NULL;
  VtencErrorCode enc_ret_code, dec_ret_code;
  int ret_code = 1;

  enc_out_cap = vtenc_set_max_encoded_size_u16(set_len);
  enc_out = (uint8_t *) malloc(enc_out_cap * sizeof(uint8_t));
  if (enc_out == NULL) {
    fprintf(stderr, "allocation error\n");
    ret_code = 0;
    goto free_and_exit;
  }

  enc_ret_code = vtenc_set_encode_u16(set, set_len, enc_out, enc_out_cap, &enc_out_len);
  if (enc_ret_code != VtencErrorNoError) {
    fprintf(stderr, "encode error code: %d\n", enc_ret_code);
    ret_code = 0;
    goto free_and_exit;
  }

  dec_out_len = vtenc_set_decoded_size_u16(enc_out, enc_out_len);
  dec_out = (uint16_t *) malloc(dec_out_len * sizeof(uint16_t));
  if (dec_out == NULL) {
    fprintf(stderr, "allocation error\n");
    ret_code = 0;
    goto free_and_exit;
  }

  dec_ret_code = vtenc_set_decode_u16(enc_out, enc_out_len, dec_out, dec_out_len);
  if (dec_ret_code != VtencErrorNoError) {
    fprintf(stderr, "decode error code: %d\n", dec_ret_code);
    ret_code = 0;
    goto free_and_exit;
  }

  if ((dec_out_len != set_len) || (memcmp(set, dec_out, set_len * sizeof(uint16_t)) != 0)) {
    fprintf(stderr, "decoded output different from original input\n");
    ret_code = 0;
    goto free_and_exit;
  }

free_and_exit:
  if (enc_out != NULL) free(enc_out);
  if (dec_out != NULL) free(dec_out);

  return ret_code;
}

static int test_encdec_set32(uint32_t *set, size_t set_len)
{
  size_t enc_out_cap, enc_out_len, dec_out_len;
  uint8_t *enc_out = NULL;
  uint32_t *dec_out = NULL;
  VtencErrorCode enc_ret_code, dec_ret_code;
  int ret_code = 1;

  enc_out_cap = vtenc_set_max_encoded_size_u32(set_len);
  enc_out = (uint8_t *) malloc(enc_out_cap * sizeof(uint8_t));
  if (enc_out == NULL) {
    fprintf(stderr, "allocation error\n");
    ret_code = 0;
    goto free_and_exit;
  }

  enc_ret_code = vtenc_set_encode_u32(set, set_len, enc_out, enc_out_cap, &enc_out_len);
  if (enc_ret_code != VtencErrorNoError) {
    fprintf(stderr, "encode error code: %d\n", enc_ret_code);
    ret_code = 0;
    goto free_and_exit;
  }

  dec_out_len = vtenc_set_decoded_size_u32(enc_out, enc_out_len);
  dec_out = (uint32_t *) malloc(dec_out_len * sizeof(uint32_t));
  if (dec_out == NULL) {
    fprintf(stderr, "allocation error\n");
    ret_code = 0;
    goto free_and_exit;
  }

  dec_ret_code = vtenc_set_decode_u32(enc_out, enc_out_len, dec_out, dec_out_len);
  if (dec_ret_code != VtencErrorNoError) {
    fprintf(stderr, "decode error code: %d\n", dec_ret_code);
    ret_code = 0;
    goto free_and_exit;
  }

  if ((dec_out_len != set_len) || (memcmp(set, dec_out, set_len * sizeof(uint32_t)) != 0)) {
    fprintf(stderr, "decoded output different from original input\n");
    ret_code = 0;
    goto free_and_exit;
  }

free_and_exit:
  if (enc_out != NULL) free(enc_out);
  if (dec_out != NULL) free(dec_out);

  return ret_code;
}

static int test_encdec_set64(uint64_t *set, size_t set_len)
{
  size_t enc_out_cap, enc_out_len, dec_out_len;
  uint8_t *enc_out = NULL;
  uint64_t *dec_out = NULL;
  VtencErrorCode enc_ret_code, dec_ret_code;
  int ret_code = 1;

  enc_out_cap = vtenc_set_max_encoded_size_u64(set_len);
  enc_out = (uint8_t *) malloc(enc_out_cap * sizeof(uint8_t));
  if (enc_out == NULL) {
    fprintf(stderr, "allocation error\n");
    ret_code = 0;
    goto free_and_exit;
  }

  enc_ret_code = vtenc_set_encode_u64(set, set_len, enc_out, enc_out_cap, &enc_out_len);
  if (enc_ret_code != VtencErrorNoError) {
    fprintf(stderr, "encode error code: %d\n", enc_ret_code);
    ret_code = 0;
    goto free_and_exit;
  }

  dec_out_len = vtenc_set_decoded_size_u64(enc_out, enc_out_len);
  dec_out = (uint64_t *) malloc(dec_out_len * sizeof(uint64_t));
  if (dec_out == NULL) {
    fprintf(stderr, "allocation error\n");
    ret_code = 0;
    goto free_and_exit;
  }

  dec_ret_code = vtenc_set_decode_u64(enc_out, enc_out_len, dec_out, dec_out_len);
  if (dec_ret_code != VtencErrorNoError) {
    fprintf(stderr, "decode error code: %d\n", dec_ret_code);
    ret_code = 0;
    goto free_and_exit;
  }

  if ((dec_out_len != set_len) || (memcmp(set, dec_out, set_len * sizeof(uint64_t)) != 0)) {
    fprintf(stderr, "decoded output different from original input\n");
    ret_code = 0;
    goto free_and_exit;
  }

free_and_exit:
  if (enc_out != NULL) free(enc_out);
  if (dec_out != NULL) free(dec_out);

  return ret_code;
}

static int test_list8(FILE *f, size_t seqsize)
{
  uint8_t *list = (uint8_t *) malloc(seqsize * sizeof(uint8_t));

  if (!read_arr8(f, list, seqsize)) {
    fprintf(stderr, "Reading sequence failed\n");
    free(list);
    return 0;
  }

  if (!test_encdec_list8(list, seqsize)) {
    fprintf(stderr, "Encoding/decoding test failed\n");
    free(list);
    return 0;
  }

  free(list);

  return 1;
}

static int test_list16(FILE *f, size_t seqsize)
{
  uint16_t *list = (uint16_t *) malloc(seqsize * sizeof(uint16_t));

  if (!read_arr16(f, list, seqsize)) {
    fprintf(stderr, "Reading sequence failed\n");
    free(list);
    return 0;
  }

  if (!test_encdec_list16(list, seqsize)) {
    fprintf(stderr, "Encoding/decoding test failed\n");
    free(list);
    return 0;
  }

  free(list);

  return 1;
}

static int test_list32(FILE *f, size_t seqsize)
{
  uint32_t *list = (uint32_t *) malloc(seqsize * sizeof(uint32_t));

  if (!read_arr32(f, list, seqsize)) {
    fprintf(stderr, "Reading sequence failed\n");
    free(list);
    return 0;
  }

  if (!test_encdec_list32(list, seqsize)) {
    fprintf(stderr, "Encoding/decoding test failed\n");
    free(list);
    return 0;
  }

  free(list);

  return 1;
}

static int test_list64(FILE *f, size_t seqsize)
{
  uint64_t *list = (uint64_t *) malloc(seqsize * sizeof(uint64_t));

  if (!read_arr64(f, list, seqsize)) {
    fprintf(stderr, "Reading sequence failed\n");
    free(list);
    return 0;
  }

  if (!test_encdec_list64(list, seqsize)) {
    fprintf(stderr, "Encoding/decoding test failed\n");
    free(list);
    return 0;
  }

  free(list);

  return 1;
}

static int test_set8(FILE *f, size_t seqsize)
{
  uint8_t *set = (uint8_t *) malloc(seqsize * sizeof(uint8_t));

  if (!read_arr8(f, set, seqsize)) {
    fprintf(stderr, "Reading sequence failed\n");
    free(set);
    return 0;
  }

  if (!test_encdec_set8(set, seqsize)) {
    fprintf(stderr, "Encoding/decoding test failed\n");
    free(set);
    return 0;
  }

  free(set);

  return 1;
}

static int test_set16(FILE *f, size_t seqsize)
{
  uint16_t *set = (uint16_t *) malloc(seqsize * sizeof(uint16_t));

  if (!read_arr16(f, set, seqsize)) {
    fprintf(stderr, "Reading sequence failed\n");
    free(set);
    return 0;
  }

  if (!test_encdec_set16(set, seqsize)) {
    fprintf(stderr, "Encoding/decoding test failed\n");
    free(set);
    return 0;
  }

  free(set);

  return 1;
}

static int test_set32(FILE *f, size_t seqsize)
{
  uint32_t *set = (uint32_t *) malloc(seqsize * sizeof(uint32_t));

  if (!read_arr32(f, set, seqsize)) {
    fprintf(stderr, "Reading sequence failed\n");
    free(set);
    return 0;
  }

  if (!test_encdec_set32(set, seqsize)) {
    fprintf(stderr, "Encoding/decoding test failed\n");
    free(set);
    return 0;
  }

  free(set);

  return 1;
}

static int test_set64(FILE *f, size_t seqsize)
{
  uint64_t *set = (uint64_t *) malloc(seqsize * sizeof(uint64_t));

  if (!read_arr64(f, set, seqsize)) {
    fprintf(stderr, "Reading sequence failed\n");
    free(set);
    return 0;
  }

  if (!test_encdec_set64(set, seqsize)) {
    fprintf(stderr, "Encoding/decoding test failed\n");
    free(set);
    return 0;
  }

  free(set);

  return 1;
}

static int test_sequence(FILE *f, const struct SequenceAttr *attr)
{
  if (attr->islist) {
    switch (attr->width) {
      case 8: return test_list8(f, attr->size);
      case 16: return test_list16(f, attr->size);
      case 32: return test_list32(f, attr->size);
      case 64: return test_list64(f, attr->size);
      default: return 0;
    }
  } else {
    switch (attr->width) {
      case 8: return test_set8(f, attr->size);
      case 16: return test_set16(f, attr->size);
      case 32: return test_set32(f, attr->size);
      case 64: return test_set64(f, attr->size);
      default: return 0;
    }
  }

  return 0;
}

static int test_binary_file(const char *filename)
{
  struct SequenceAttr seq_attr;
  FILE *f = fopen(filename, "rb");

  if (f == NULL) {
    perror("fopen() failed");
    return 0;
  }

  if (!read_header(f, &seq_attr)) {
    fprintf(stderr, "read_header() failed\n");
    fclose(f);
    return 0;
  }

  if (!is_valid_sequence_attr(&seq_attr)) {
    fprintf(stderr, "Invalid binary format\n");
    fclose(f);
    return 0;
  }

  if (!test_sequence(f, &seq_attr)) {
    fprintf(stderr, "Tests failed\n");
    fclose(f);
    return 0;
  }

  fclose(f);

  return 1;
}

int main(int argc, char **argv)
{
 if (argc == 1) {
   usage(argv[0]);
   return 1;
 }

 if (!test_binary_file(argv[1])) {
   return 1;
 }

 return 0;
}
