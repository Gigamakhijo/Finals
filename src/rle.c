#include "rle.h"
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXRLEN 50

int rle_encode(int *dst, int *src, int len) {
  int rlen;

  int j = 0;
  for (int i = 0; i < len; i++) {
    dst[j++] = src[i];

    if (src[i] == 0) {
      rlen = 1;
      while (i + 1 < len && src[i] == src[i + 1]) {
        rlen++;
        i++;
      }
      dst[j++] = rlen;
    }
  }
  return j;
}

int rle_decode(int *dst, int *src, int len) {

  int j = 0;
  for (int i = 0; i < len; i++) {
    dst[j++] = src[i];
    if (src[i] == 0) {
      for (int k = 0; k < src[i + 1] - 1; k++)
        dst[j++] = 0;
      i++;
    }
  }
  return j;
}
