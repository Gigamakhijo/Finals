#include "rle.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int main() {

  int *enc = malloc(sizeof(int) * 1000);
  int src[] = {0, 0, 0, 0, 0, 0, 1, 0, 4, 6, 0, 2, 4, 0, 0, 0, 1, 0};
  int res[] = {0, 6, 1, 0, 1, 4, 6, 0, 1, 2, 4, 0, 2, 1, 0, 1};

  int len = rle_encode(enc, src, 18);

  printf("src:\n");
  for (int i = 0; i < 18; i++)
    printf("%d ", src[i]);
  putchar('\n');

  assert(len == 16);

  printf("Encoding rle on zeros:\n");
  for (int i = 0; i < len; i++)
    printf("%d ", enc[i]);
  putchar('\n');

  for (int i = 0; i < len; i++)
    assert(enc[len] == res[len]);

  printf("Decoding rle on zeros:\n");
  int *dec = malloc(sizeof(int) * 1000);
  len = rle_decode(dec, enc, len);

  for (int i = 0; i < len; i++)
    printf("%d ", dec[i]);
  putchar('\n');

  assert(len == 18);

  for (int i = 0; i < len; i++)
    assert(dec[i] == src[i]);
  free(enc);
  free(dec);
}
