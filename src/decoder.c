#include "core.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
	revert_fivot(argv[1], "decoder.fivot");
  	revert_correction("decoder.fivot", "decoder.correction");
  	revert_protocol("decoder.correction", "decode.txt");

	remove("decoder.fivot");
	remove("decoder.correction");
}
