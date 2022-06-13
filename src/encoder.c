#include "core.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
  convert_protocol(argv[1], "encoder.protocol");
  convert_correction("encoder.protocol", "encoder.correction");
  convert_fivot("encoder.correction", "encoder.fivot");

  remove("encoder.protocol");
  remove("encoder.correction");
  rename("encoder.fivot", "encoded_data");
}
