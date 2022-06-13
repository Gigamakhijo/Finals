#include "core.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
  convert_protocol(argv[1], "encoder.protocol");
  // compress
  convert_correction("encoder.protocol", "encoder.correction");
  convert_pivot("encoder.correction", "encoder.pivot");

  remove("encoder.protocol");
  remove("encoder.correction");
  rename("encoder.pivot", "encoded_data");
}
