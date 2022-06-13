#include "core.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
  revert_pivot(argv[1], "decoder.pivot");
  revert_correction("decoder.pivot", "decoder.correction");
  // compress
  revert_protocol("decoder.correction", "decode.protocol");

  remove("decoder.pivot");
  remove("decoder.correction");
  rename("decode.protocol", "decode.txt");
}
