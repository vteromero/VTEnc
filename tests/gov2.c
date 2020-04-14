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

struct Stats {
  size_t n_sets;
  size_t total_input_size;
  size_t total_encoded_size;
};

void stats_init(struct Stats *stats)
{
  stats->n_sets = 0;
  stats->total_input_size = 0;
  stats->total_encoded_size = 0;
}

void stats_print(const struct Stats *stats)
{
  double ratio = stats->total_encoded_size / (double)(stats->total_input_size);

  printf("number of sets processed: %lu\n", stats->n_sets);
  printf("input size: %lu bytes\n", stats->total_input_size);
  printf("encoded size: %lu bytes\n", stats->total_encoded_size);
  printf("compression ratio: %f (%.4f%%)\n", ratio, ratio * 100.0);
}

int read_u32_from_file(FILE *fp, uint32_t *value)
{
  char bytes[4];
  size_t n_read = fread(bytes, sizeof(char), sizeof(bytes), fp);

  if (n_read < sizeof(bytes)) {
    return 0;
  } else {
    memcpy(value, bytes, sizeof(*value));
    return 1;
  }
}

int read_values_from_file(FILE *fp, uint32_t *values, uint32_t values_len)
{
  uint32_t i;

  for (i = 0; i < values_len; ++i) {
    if (!read_u32_from_file(fp, &(values[i]))) {
      return 0;
    }
  }

  return 1;
}

int has_strictly_ascending_order(const uint32_t *values, uint32_t values_len)
{
  uint32_t i;

  for (i = 1; i < values_len; ++i) {
    if (values[i] <= values[i - 1]) {
      return 0;
    }
  }

  return 1;
}

int encode_and_decode_set(const uint32_t *values, uint32_t values_len, struct Stats *stats)
{
  struct EncDec encdec;

  encdec_init32(&encdec);
  encdec.has_repeated_values = 0;

  if (!encdec_encode(&encdec, values, values_len)) {
    fprintf(stderr, "encdec_encode failed\n");
    encdec_free(&encdec);
    return 0;
  }

  if (!encdec_decode(&encdec)) {
    fprintf(stderr, "encdec_decode failed\n");
    encdec_free(&encdec);
    return 0;
  }

  if (!encdec_check_equality(&encdec)) {
    fprintf(stderr, "encdec_check_equality failed\n");
    encdec_free(&encdec);
    return 0;
  }

  stats->n_sets++;
  stats->total_input_size += values_len * sizeof(uint32_t);
  stats->total_encoded_size += encdec.ctx.enc_out_len;

  encdec_free(&encdec);

  return 1;
}

size_t do_test(const char *filename)
{
  uint32_t *values=NULL, values_len=0;
  size_t exit_code=0;
  struct Stats stats;
  FILE *fp = fopen(filename, "rb");

  stats_init(&stats);

  if (fp == NULL) {
    fprintf(stderr, "failed opening '%s' file\n", filename);
    return EXIT_FAILURE;
  }

  while ((exit_code == 0) && read_u32_from_file(fp, &values_len)) {
    values = (uint32_t *) malloc(values_len * sizeof(uint32_t));
    if (values == NULL) {
      fprintf(stderr, "allocation error\n");
      exit_code = EXIT_FAILURE;
      break;
    }

    if (!read_values_from_file(fp, values, values_len)) {
      fprintf(stderr, "failed reading values from file\n");
      exit_code = EXIT_FAILURE;
      goto cleanup_values;
    }

    if (!has_strictly_ascending_order(values, values_len)) {
      fprintf(stderr, "wrong set order\n");
      exit_code = EXIT_FAILURE;
      goto cleanup_values;
    }

    if (!encode_and_decode_set(values, values_len, &stats)) {
      exit_code = EXIT_FAILURE;
      goto cleanup_values;
    }

cleanup_values:
    free(values);
  }

  stats_print(&stats);

  fclose(fp);

  return exit_code;
}

void usage(const char *program)
{
  fprintf(stderr,
  "Usage: %s <file>\n"
  "\n"
  "  <file> is a binary file containing a list of sets. Each set starts with a\n"
  "  32-bit unsigned integer indicating its length followed by a sequence of\n"
  "  32-bit unsigned integers that make up the set. The values of each set\n"
  "  are sorted in ascending order.\n"
  "  This program was originally created to test a specific data set:\n"
  "  'gov2.sorted'. You can download it from the following URL:\n"
  "  https://lemire.me/data/integercompression2014.html\n",
  program);
}

int main(int argc, char **argv)
{
  if (argc != 2) {
    usage(argv[0]);
    return EXIT_FAILURE;
  }

  return do_test(argv[1]);
}
