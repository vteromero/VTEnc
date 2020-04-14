/**
  Copyright (c) 2020 Vicente Romero Calero. All rights reserved.
  Licensed under the MIT License.
  See LICENSE file in the project root for full license information.
 */
#include <stdio.h>
#include <stdlib.h>

#include "encdec.h"
#include "../mem.h"

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

static int test_encode_and_decode(struct EncDec *encdec, const void *seq, size_t seqsize)
{
  if (!encdec_encode(encdec, seq, seqsize)) {
    fprintf(stderr, "encdec_encode failed\n");
    encdec_free(encdec);
    return 0;
  }

  if (!encdec_decode(encdec)) {
    fprintf(stderr, "encdec_decode failed\n");
    encdec_free(encdec);
    return 0;
  }

  if (!encdec_check_equality(encdec)) {
    fprintf(stderr, "encdec_check_equality failed\n");
    encdec_free(encdec);
    return 0;
  }

  encdec_free(encdec);

  return 1;
}

static int test_seq8(FILE *f, int islist, size_t seqsize)
{
  struct EncDec encdec;
  uint8_t *seq = (uint8_t *) malloc(seqsize * sizeof(uint8_t));

  if (!read_arr8(f, seq, seqsize)) {
    fprintf(stderr, "Reading sequence failed\n");
    free(seq);
    return 0;
  }

  encdec_init8(&encdec);
  encdec.has_repeated_values = islist;

  if (!test_encode_and_decode(&encdec, seq, seqsize)) {
    fprintf(stderr, "Encoding/decoding test failed\n");
    free(seq);
    return 0;
  }

  free(seq);

  return 1;
}

static int test_seq16(FILE *f, int islist, size_t seqsize)
{
  struct EncDec encdec;
  uint16_t *seq = (uint16_t *) malloc(seqsize * sizeof(uint16_t));

  if (!read_arr16(f, seq, seqsize)) {
    fprintf(stderr, "Reading sequence failed\n");
    free(seq);
    return 0;
  }

  encdec_init16(&encdec);
  encdec.has_repeated_values = islist;

  if (!test_encode_and_decode(&encdec, seq, seqsize)) {
    fprintf(stderr, "Encoding/decoding test failed\n");
    free(seq);
    return 0;
  }

  free(seq);

  return 1;
}

static int test_seq32(FILE *f, int islist, size_t seqsize)
{
  struct EncDec encdec;
  uint32_t *seq = (uint32_t *) malloc(seqsize * sizeof(uint32_t));

  if (!read_arr32(f, seq, seqsize)) {
    fprintf(stderr, "Reading sequence failed\n");
    free(seq);
    return 0;
  }

  encdec_init32(&encdec);
  encdec.has_repeated_values = islist;

  if (!test_encode_and_decode(&encdec, seq, seqsize)) {
    fprintf(stderr, "Encoding/decoding test failed\n");
    free(seq);
    return 0;
  }

  free(seq);

  return 1;
}

static int test_seq64(FILE *f, int islist, size_t seqsize)
{
  struct EncDec encdec;
  uint64_t *seq = (uint64_t *) malloc(seqsize * sizeof(uint64_t));

  if (!read_arr64(f, seq, seqsize)) {
    fprintf(stderr, "Reading sequence failed\n");
    free(seq);
    return 0;
  }

  encdec_init64(&encdec);
  encdec.has_repeated_values = islist;

  if (!test_encode_and_decode(&encdec, seq, seqsize)) {
    fprintf(stderr, "Encoding/decoding test failed\n");
    free(seq);
    return 0;
  }

  free(seq);

  return 1;
}

static int test_sequence(FILE *f, const struct SequenceAttr *attr)
{
  switch (attr->width) {
    case 8: return test_seq8(f, attr->islist, attr->size);
    case 16: return test_seq16(f, attr->islist, attr->size);
    case 32: return test_seq32(f, attr->islist, attr->size);
    case 64: return test_seq64(f, attr->islist, attr->size);
    default: return 0;
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
