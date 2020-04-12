/**
  Copyright (c) 2019 Vicente Romero Calero. All rights reserved.
  Licensed under the MIT License.
  See LICENSE file in the project root for full license information.
 */
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "encdec.h"
#include "../vtenc.h"

struct array_t {
  uint32_t *values;
  size_t size;
  size_t capacity;
};

void array_init(struct array_t *arr, size_t capacity)
{
  arr->values = (uint32_t *) malloc(capacity * sizeof(uint32_t));
  if (arr->values == NULL) {
    fprintf(stderr, "array_init: allocation error\n");
    exit(EXIT_FAILURE);
  }

  arr->size = 0;
  arr->capacity = capacity;
}

void array_push(struct array_t *arr, uint32_t value)
{
  arr->values[arr->size++] = value;

  if (arr->size >= arr->capacity) {
    arr->capacity *= 2;
    arr->values = (uint32_t *) realloc(arr->values, arr->capacity * sizeof(uint32_t));
    if (arr->values == NULL) {
      fprintf(stderr, "array_push: re-allocation error\n");
      exit(EXIT_FAILURE);
    }
  }
}

void array_free(struct array_t *arr)
{
  free(arr->values);
  arr->size = 0;
  arr->capacity = 0;
}

void array_load_from_txt_file(const char *filename, struct array_t *arr)
{
  char buf[20], *end;
  uint32_t v;
  FILE *f = fopen(filename, "r");

  if (f == NULL) {
    fprintf(stderr, "array_load_from_txt_file: failed opening '%s' file\n", filename);
    exit(EXIT_FAILURE);
  }

  while (fgets(buf, sizeof(buf), f) != NULL) {
    v = strtoul(buf, &end, 10);
    array_push(arr, v);
  }

  fclose(f);
}

int has_ascending_order(uint32_t *values, size_t values_len)
{
  size_t i;

  for (i = 1; i < values_len; ++i) {
    if (values[i] < values[i - 1]) {
      return 0;
    }
  }

  return 1;
}

void usage(const char *program)
{
  fprintf(stderr,
  "Usage: %s <file>\n"
  "\n"
  "  <file> can be any text file containing a sorted list of 32-bit unsigned\n"
  "  integers, one per line.\n"
  "  This program was originally created to test a specific data set: 'ts.txt'.\n"
  "  You can download it from the following URL:\n"
  "  https://github.com/zentures/encoding/tree/master/benchmark/data\n",
  program);
}

int main(int argc, char **argv)
{
  struct array_t arr;
  VtencEncoder encoder;

  if (argc != 2) {
    usage(argv[0]);
    return EXIT_FAILURE;
  }

  array_init(&arr, 10000);

  array_load_from_txt_file(argv[1], &arr);

  if (!has_ascending_order(arr.values, arr.size)) {
    fprintf(stderr, "wrong list order\n");
    array_free(&arr);
    return EXIT_FAILURE;
  }

  vtenc_encoder_init(&encoder);

  if (!test_encode_and_decode32(&encoder, arr.values, arr.size, 1)) {
    fprintf(stderr, "test_encode_and_decode32 failed!\n");
    array_free(&arr);
    return EXIT_FAILURE;
  }

  array_free(&arr);

  return 0;
}
