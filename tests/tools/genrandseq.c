/**
  Copyright (c) 2020 Vicente Romero Calero. All rights reserved.
  Licensed under the MIT License.
  See LICENSE file in the project root for full license information.
 */
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../../mem.h"
#include "tinymt32.h"
#include "tinymt64.h"

struct Options {
  int show_help;
  int width;
  size_t seqsize;
  char seqtype;
  const char *filename;
};

static void init_options(struct Options *opt)
{
  opt->show_help = 0;
  opt->width = 0;
  opt->seqsize = 0;
  opt->seqtype = 'x';
  opt->filename = NULL;
}

static void parse_options(int argc, char **argv, struct Options *opt) {
  for (int i = 1; i < argc; ++i) {
    if (strcmp(argv[i], "-h") == 0) {
      opt->show_help = 1;
    } else if ((strcmp(argv[i], "-n") == 0) && (i + 1 < argc)) {
      opt->seqsize = (size_t)(atoll(argv[++i]));
    } else if ((strcmp(argv[i], "-t") == 0) && (i + 1 < argc)) {
      opt->seqtype = (char)(argv[++i][0]);
    } else if ((strcmp(argv[i], "-w") == 0) && (i + 1 < argc)) {
      opt->width = atoi(argv[++i]);
    } else if(argv[i][0] == '-') {
      fprintf(stderr, "Unrecognized option: '%s'\n", argv[i]);
    } else {
      opt->filename = argv[i];
    }
  }
}

static int validate_options(const struct Options *opt)
{
  switch (opt->width) {
    case 8:
    case 16:
    case 32:
    case 64:
      break;
    default:
      fprintf(stderr, "Invalid -w option: %d\n", opt->width);
      return 0;
  }

  switch (opt->seqtype) {
    case 'l':
    case 's':
      break;
    default:
      fprintf(stderr, "Invalid -t option: %c\n", opt->seqtype);
      return 0;
  }

  if (opt->seqsize == 0) {
    fprintf(stderr, "Sequence size must be greater than 0\n");
    return 0;
  }

  if (opt->filename == NULL) {
    fprintf(stderr, "Output file not specified\n");
    return 0;
  }

  return 1;
}

static void usage(const char *program)
{
  fprintf(stderr,
"Generates a random sequence and saves it into <file>.\n"
"\n"
"Usage: %s OPTIONS <file>\n"
"\n"
"OPTIONS:\n"
"\n"
"  -h              Output this help and exit\n"
"  -n <size>       Specify size of sequence\n"
"  -t <seqtype>    Specify type of sequence: \"l\"ist or \"s\"et\n"
"  -w <width>      Specify size of sequence's data type: 8, 16, 32 or 64\n"
"\n",
  program);
}

static void random_arr8(uint8_t *arr, size_t arr_len)
{
  srand(time(NULL));

  for (int i = 0; i < arr_len; ++i) {
    arr[i] = (uint8_t)(rand() & 0xff);
  }
}

static void random_arr16(uint16_t *arr, size_t arr_len)
{
  srand(time(NULL));

  for (int i = 0; i < arr_len; ++i) {
    arr[i] = (uint16_t)(rand() & 0xffff);
  }
}

static void random_arr32(uint32_t *arr, size_t arr_len)
{
  tinymt32_t tinymt;

  tinymt32_init(&tinymt, (uint32_t)time(NULL));

  for (int i = 0; i < arr_len; ++i) {
    arr[i] = tinymt32_generate_uint32(&tinymt);
  }
}

static void random_arr64(uint64_t *arr, size_t arr_len)
{
  tinymt64_t tinymt;

  tinymt64_init(&tinymt, (uint64_t)time(NULL));

  for (int i = 0; i < arr_len; ++i) {
    arr[i] = tinymt64_generate_uint64(&tinymt);
  }
}

static int cmp8(const void *pa, const void *pb)
{
  uint8_t a = *(const uint8_t *)pa;
  uint8_t b = *(const uint8_t *)pb;
  return (a < b) ? -1 : (a > b);
}

static int cmp16(const void *pa, const void *pb)
{
  uint16_t a = *(const uint16_t *)pa;
  uint16_t b = *(const uint16_t *)pb;
  return (a < b) ? -1 : (a > b);
}

static int cmp32(const void *pa, const void *pb)
{
  uint32_t a = *(const uint32_t *)pa;
  uint32_t b = *(const uint32_t *)pb;
  return (a < b) ? -1 : (a > b);
}

static int cmp64(const void *pa, const void *pb)
{
  uint64_t a = *(const uint64_t *)pa;
  uint64_t b = *(const uint64_t *)pb;
  return (a < b) ? -1 : (a > b);
}

static void sort_arr8(uint8_t *arr, size_t arr_len)
{
  qsort(arr, arr_len, sizeof(uint8_t), cmp8);
}

static void sort_arr16(uint16_t *arr, size_t arr_len)
{
  qsort(arr, arr_len, sizeof(uint16_t), cmp16);
}

static void sort_arr32(uint32_t *arr, size_t arr_len)
{
  qsort(arr, arr_len, sizeof(uint32_t), cmp32);
}

static void sort_arr64(uint64_t *arr, size_t arr_len)
{
  qsort(arr, arr_len, sizeof(uint64_t), cmp64);
}

static size_t make_set8(uint8_t *arr, size_t arr_len)
{
  size_t new_len = 0;
  size_t i;

  for (i = 0; i < arr_len; ++i) {
    if (arr[i] > arr[new_len]) {
      arr[++new_len] = arr[i];
    }
  }

  return new_len + 1;
}

static size_t make_set16(uint16_t *arr, size_t arr_len)
{
  size_t new_len = 0;
  size_t i;

  for (i = 0; i < arr_len; ++i) {
    if (arr[i] > arr[new_len]) {
      arr[++new_len] = arr[i];
    }
  }

  return new_len + 1;
}

static size_t make_set32(uint32_t *arr, size_t arr_len)
{
  size_t new_len = 0;
  size_t i;

  for (i = 0; i < arr_len; ++i) {
    if (arr[i] > arr[new_len]) {
      arr[++new_len] = arr[i];
    }
  }

  return new_len + 1;
}

static size_t make_set64(uint64_t *arr, size_t arr_len)
{
  size_t new_len = 0;
  size_t i;

  for (i = 0; i < arr_len; ++i) {
    if (arr[i] > arr[new_len]) {
      arr[++new_len] = arr[i];
    }
  }

  return new_len + 1;
}

// static void print_arr8(uint8_t *arr, size_t arr_len)
// {
//   size_t i;
//   printf("[%lu]:", arr_len);
//   for (i = 0; i < arr_len; ++i) printf(" %u", arr[i]);
//   printf("\n");
// }
//
// static void print_arr16(uint16_t *arr, size_t arr_len)
// {
//   size_t i;
//   printf("[%lu]:", arr_len);
//   for (i = 0; i < arr_len; ++i) printf(" %u", arr[i]);
//   printf("\n");
// }
//
// static void print_arr32(uint32_t *arr, size_t arr_len)
// {
//   size_t i;
//   printf("[%lu]:", arr_len);
//   for (i = 0; i < arr_len; ++i) printf(" %u", arr[i]);
//   printf("\n");
// }
//
// static void print_arr64(uint64_t *arr, size_t arr_len)
// {
//   size_t i;
//   printf("[%lu]:", arr_len);
//   for (i = 0; i < arr_len; ++i) printf(" %lu", arr[i]);
//   printf("\n");
// }

static int write_u8(FILE *f, uint8_t value)
{
  size_t n_written = fwrite(&value, 1, sizeof(value), f);

  if (n_written < sizeof(value)) {
    return 0;
  } else {
    return 1;
  }
}

static int write_u16(FILE *f, uint16_t value)
{
  char buf[2];
  size_t n_written;

  mem_write_le_u16(buf, value);
  n_written = fwrite(buf, 1, sizeof(buf), f);

  if (n_written < sizeof(buf)) {
    return 0;
  } else {
    return 1;
  }
}

static int write_u32(FILE *f, uint32_t value)
{
  char buf[4];
  size_t n_written;

  mem_write_le_u32(buf, value);
  n_written = fwrite(buf, 1, sizeof(buf), f);

  if (n_written < sizeof(buf)) {
    return 0;
  } else {
    return 1;
  }
}

static int write_u64(FILE *f, uint64_t value)
{
  char buf[8];
  size_t n_written;

  mem_write_le_u64(buf, value);
  n_written = fwrite(buf, 1, sizeof(buf), f);

  if (n_written < sizeof(buf)) {
    return 0;
  } else {
    return 1;
  }
}

static int write_header(FILE *f, int islist, int width,  size_t seqsize)
{
  uint8_t x = (uint8_t)(islist << 7) | (uint8_t)(width);

  return write_u8(f, x) && write_u32(f, (uint32_t)seqsize);
}

static int save_arr8(const char *filename, const uint8_t *arr, size_t arr_len,
  int islist)
{
  size_t i;
  FILE *f = fopen(filename, "wb");

  if (f == NULL) {
    perror("fopen() failed");
    return 0;
  }

  if (!write_header(f, islist, 8, arr_len)) {
    perror("fwrite() failed");
    fclose(f);
    return 0;
  }

  for (i = 0; i < arr_len; ++i) {
    if (!write_u8(f, arr[i])) {
      perror("fwrite() failed");
      fclose(f);
      return 0;
    }
  }

  fclose(f);

  return 1;
}

static int save_arr16(const char *filename, const uint16_t *arr, size_t arr_len,
  int islist)
{
  size_t i;
  FILE *f = fopen(filename, "wb");

  if (f == NULL) {
    perror("fopen() failed");
    return 0;
  }

  if (!write_header(f, islist, 16, arr_len)) {
    perror("fwrite() failed");
    fclose(f);
    return 0;
  }

  for (i = 0; i < arr_len; ++i) {
    if (!write_u16(f, arr[i])) {
      perror("fwrite() failed");
      fclose(f);
      return 0;
    }
  }

  fclose(f);

  return 1;
}

static int save_arr32(const char *filename, const uint32_t *arr, size_t arr_len,
  int islist)
{
  size_t i;
  FILE *f = fopen(filename, "wb");

  if (f == NULL) {
    perror("fopen() failed");
    return 0;
  }

  if (!write_header(f, islist, 32, arr_len)) {
    perror("fwrite() failed");
    fclose(f);
    return 0;
  }

  for (i = 0; i < arr_len; ++i) {
    if (!write_u32(f, arr[i])) {
      perror("fwrite() failed");
      fclose(f);
      return 0;
    }
  }

  fclose(f);

  return 1;
}

static int save_arr64(const char *filename, const uint64_t *arr, size_t arr_len,
  int islist)
{
  size_t i;
  FILE *f = fopen(filename, "wb");

  if (f == NULL) {
    perror("fopen() failed");
    return 0;
  }

  if (!write_header(f, islist, 64, arr_len)) {
    perror("fwrite() failed");
    fclose(f);
    return 0;
  }

  for (i = 0; i < arr_len; ++i) {
    if (!write_u64(f, arr[i])) {
      perror("fwrite() failed");
      fclose(f);
      return 0;
    }
  }

  fclose(f);

  return 1;
}

static int generate_list8(const char *filename, size_t seqsize)
{
  uint8_t *list = (uint8_t *) malloc(seqsize * sizeof(uint8_t));

  if (list == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    return 0;
  }

  random_arr8(list, seqsize);
  sort_arr8(list, seqsize);

  if (!save_arr8(filename, list, seqsize, 1)) {
    free(list);
    return 0;
  }

  free(list);

  return 1;
}

static int generate_list16(const char *filename, size_t seqsize)
{
  uint16_t *list = (uint16_t *) malloc(seqsize * sizeof(uint16_t));

  if (list == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    return 0;
  }

  random_arr16(list, seqsize);
  sort_arr16(list, seqsize);

  if (!save_arr16(filename, list, seqsize, 1)) {
    free(list);
    return 0;
  }

  free(list);

  return 1;
}

static int generate_list32(const char *filename, size_t seqsize)
{
  uint32_t *list = (uint32_t *) malloc(seqsize * sizeof(uint32_t));

  if (list == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    return 0;
  }

  random_arr32(list, seqsize);
  sort_arr32(list, seqsize);

  if (!save_arr32(filename, list, seqsize, 1)) {
    free(list);
    return 0;
  }

  free(list);

  return 1;
}

static int generate_list64(const char *filename, size_t seqsize)
{
  uint64_t *list = (uint64_t *) malloc(seqsize * sizeof(uint64_t));

  if (list == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    return 0;
  }

  random_arr64(list, seqsize);
  sort_arr64(list, seqsize);

  if (!save_arr64(filename, list, seqsize, 1)) {
    free(list);
    return 0;
  }

  free(list);

  return 1;
}

static int generate_set8(const char *filename, size_t seqsize)
{
  uint8_t *set = (uint8_t *) malloc(seqsize * sizeof(uint8_t));

  if (set == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    return 0;
  }

  random_arr8(set, seqsize);
  sort_arr8(set, seqsize);
  seqsize = make_set8(set, seqsize);

  if (!save_arr8(filename, set, seqsize, 0)) {
    free(set);
    return 0;
  }

  free(set);

  return 1;
}

static int generate_set16(const char *filename, size_t seqsize)
{
  uint16_t *set = (uint16_t *) malloc(seqsize * sizeof(uint16_t));

  if (set == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    return 0;
  }

  random_arr16(set, seqsize);
  sort_arr16(set, seqsize);
  seqsize = make_set16(set, seqsize);

  if (!save_arr16(filename, set, seqsize, 0)) {
    free(set);
    return 0;
  }

  free(set);

  return 1;
}

static int generate_set32(const char *filename, size_t seqsize)
{
  uint32_t *set = (uint32_t *) malloc(seqsize * sizeof(uint32_t));

  if (set == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    return 0;
  }

  random_arr32(set, seqsize);
  sort_arr32(set, seqsize);
  seqsize = make_set32(set, seqsize);

  if (!save_arr32(filename, set, seqsize, 0)) {
    free(set);
    return 0;
  }

  free(set);

  return 1;
}

static int generate_set64(const char *filename, size_t seqsize)
{
  uint64_t *set = (uint64_t *) malloc(seqsize * sizeof(uint64_t));

  if (set == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    return 0;
  }

  random_arr64(set, seqsize);
  sort_arr64(set, seqsize);
  seqsize = make_set64(set, seqsize);

  if (!save_arr64(filename, set, seqsize, 0)) {
    free(set);
    return 0;
  }

  free(set);

  return 1;
}

static int generate_random_sequence(const struct Options *opt)
{
  if (opt->seqtype == 'l') {
    switch (opt->width) {
      case 8: return generate_list8(opt->filename, opt->seqsize);
      case 16: return generate_list16(opt->filename, opt->seqsize);
      case 32: return generate_list32(opt->filename, opt->seqsize);
      case 64: return generate_list64(opt->filename, opt->seqsize);
      default: return 0;
    }
  } if (opt->seqtype == 's') {
    switch (opt->width) {
      case 8: return generate_set8(opt->filename, opt->seqsize);
      case 16: return generate_set16(opt->filename, opt->seqsize);
      case 32: return generate_set32(opt->filename, opt->seqsize);
      case 64: return generate_set64(opt->filename, opt->seqsize);
      default: return 0;
    }
  } else {
    return 0;
  }

  return 0;
}

int main(int argc, char **argv)
{
  struct Options opt;

  if (argc == 1) {
    usage(argv[0]);
    return 1;
  }

  init_options(&opt);
  parse_options(argc, argv, &opt);

  if (opt.show_help) {
    usage(argv[0]);
    return 0;
  }

  if (!validate_options(&opt)) {
    return 1;
  }

  if (!generate_random_sequence(&opt)) {
    return 1;
  }

  return 0;
}
