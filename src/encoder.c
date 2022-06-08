#include <stdio.h>

#include "text.h"

int main(int argc, char *argv[]) {
  Data data;

  FILE *fp = fopen(argv[1], "r");
  if (!fp) {
    perror("File opening failed");
    return -1;
  }

  printf("%d\n", ReadText(&data, fp));

  fclose(fp);
  // encode();
  // compress();
  // add_ecc();
  // write_bits();
}
