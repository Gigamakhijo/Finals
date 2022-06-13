#include "lzss.h"

#include <stdio.h>
#include <stdlib.h>

#define BUFSIZE 100000

void lzss_encode(char *buf, size_t size) {
  char *search_buffer = malloc(size);
  for (int i = 0; i < size; i++) {
    printf("%d\n", buf[i]);
    search_buffer[i] = buf[i];
  }
}

void compress(const char *src, const char *dst) {
  FILE *fp = fopen(src, "rb");
  char buf[BUFSIZE];
  size_t size = fread(buf, 1, BUFSIZE, fp);
  fclose(fp);

  lzss_encode(buf, size);

  fp = fopen(dst, "wb");
  fwrite(buf, 1, size, fp);
  fclose(fp);
}

void decompress(const char *src, const char *dst) {
  FILE *fp = fopen(src, "rb");
  char buf[BUFSIZE];
  size_t size = fread(buf, 1, BUFSIZE, fp);
  fclose(fp);

  fp = fopen(dst, "wb");
  fwrite(buf, 1, size, fp);
  fclose(fp);
}
