#include "core.h"

#include <stdio.h>

int main(int argc, char *argv[]) {
  convert_protocol(argv[1], "encoder.protocol");
  // compress
  compress("encoder.protocol", "encoder.compressed");

  convert_correction("encoder.compressed", "encoder.correction");
  convert_pivot("encoder.correction", "encoder.pivot");

  remove("encoder.protocol");
  remove("encoder.correction");
  rename("encoder.pivot", "encoded_data");
}
