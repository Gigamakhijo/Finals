#include "bwt.h"

#include <stdio.h>
#include <stdlib.h>

int main() {
  char *bwt = bwt_encode("asdfasfasdfadfwjkegasfkj$");
  printf("bwt encoded string: %s\n", bwt);

  char *str = bwt_decode(bwt);
  printf("decoded string: %s\n", str);

  free(bwt);
  free(str);
}
