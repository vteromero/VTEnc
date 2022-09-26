#include <stddef.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../vtenc.h"

static void print_arr(uint32_t *arr, size_t arr_len)
{
  size_t i;
  printf("[%lu]:", arr_len);
  for (i = 0; i < arr_len; ++i) printf(" %u", arr[i]);
  printf("\n");
}

static int cmp32(const void *pa, const void *pb)
{
  uint32_t a = *(const uint32_t *)pa;
  uint32_t b = *(const uint32_t *)pb;
  return (a < b) ? -1 : (a > b);
}

static void usage(const char *program)
{
  fprintf(stderr,
"Tests encoding methods for random sets of sizes from 1 through 2^BITWIDTH.\n"
"Encoding methods are: lower bits literals (lit), Bit Cluster Tree encoding\n"
"(tree) and lower bits as bitmaps (bmp).\n"
"\n"
"Usage: %s BITWIDTH\n"
"\n",
  program);
}

// https://benpfaff.org/writings/clc/shuffle.html
static void shuffle(uint32_t *arr, size_t arr_len)
{
  size_t i;

  if (arr_len <= 1) {
    return;
  }

  for (i = 0; i < arr_len - 1; i++) {
    size_t j = i + rand() / (RAND_MAX / (arr_len - i) + 1);
    uint32_t t = arr[j];
    arr[j] = arr[i];
    arr[i] = t;
  }
}

static void generate_shuffled_arr(uint32_t *out, size_t out_len) {
  size_t i;

  srand(time(NULL));

  for (i = 0; i < out_len; i++) {
    out[i] = (uint32_t)i;
  }

  shuffle(out, out_len);
}

static size_t encode(
  const uint32_t *in, size_t in_len,
  uint8_t *out, size_t out_cap,
  unsigned int bit_width)
{
  int rc;
  size_t res = 0;
  vtenc *encoder = vtenc_create();

  if (encoder == NULL) {
    fprintf(stderr, "failed to create the encoder\n");
    return res;
  }

  vtenc_config(encoder, VTENC_CONFIG_ALLOW_REPEATED_VALUES, 0);
  vtenc_config(encoder, VTENC_CONFIG_SKIP_FULL_SUBTREES, 1);
  vtenc_config(encoder, VTENC_CONFIG_MIN_CLUSTER_LENGTH, 0);
  vtenc_config(encoder, VTENC_CONFIG_BIT_WIDTH, bit_width);

  rc = vtenc_encode32(encoder, in, in_len, out, out_cap);

  if (rc != VTENC_OK) {
    fprintf(stderr, "encode failed with code: %d\n", rc);
    goto destroy_and_return;
  }

  res = vtenc_encoded_size(encoder);

destroy_and_return:
  vtenc_destroy(encoder);

  return res;
}

static void test_arr(
  const uint32_t *arr, size_t arr_len,
  uint8_t *buf, size_t buf_cap,
  unsigned int bit_width)
{
  size_t lit = arr_len * bit_width;
  size_t tree = encode(arr, arr_len, buf, buf_cap, bit_width) * 8;
  size_t bmp = 1u << bit_width;

  printf("len: %lu, lit: %lu, tree: %lu, bmp: %lu\n",
    arr_len, lit, tree, bmp);
}

static void test_enc_methods(unsigned int bit_width)
{
  size_t max_len = 1u << bit_width;
  size_t arr_len;
  size_t buf_cap = vtenc_max_encoded_size32(max_len);
  uint32_t *shuffled_arr = (uint32_t *) malloc(max_len * sizeof(uint32_t));
  uint32_t *arr = (uint32_t *) malloc(max_len * sizeof(uint32_t));
  uint8_t *buf = (uint8_t *) malloc(buf_cap * sizeof(uint8_t));

  if (shuffled_arr == NULL || arr == NULL || buf == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    goto cleanup_and_exit;
  }

  generate_shuffled_arr(shuffled_arr, max_len);
  //print_arr(shuffled_arr, max_len);

  for (arr_len = 1; arr_len <= max_len; arr_len++) {
    memcpy(arr, shuffled_arr, arr_len * sizeof(uint32_t));
    qsort(arr, arr_len, sizeof(uint32_t), cmp32);
    //print_arr(arr, arr_len);

    test_arr(arr, arr_len, buf, buf_cap, bit_width);
  }

cleanup_and_exit:
  if (shuffled_arr != NULL) free(shuffled_arr);
  if (arr != NULL) free(arr);
  if (buf != NULL) free(buf);
}

int main(int argc, char **argv)
{
  int bit_width;

  if (argc == 1) {
    usage(argv[0]);
    return 1;
  }

  bit_width = atoi(argv[1]);

  if (bit_width < 1 || bit_width > 16) {
    fprintf(stderr, "BITWIDTH must be a positive integer in the range [1, 16]\n\n");
    usage(argv[0]);
    return 1;
  }

  test_enc_methods(bit_width);

  return 0;
}
