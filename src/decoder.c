#include "core.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
	revert_fivot(argv[1], "decoder.fivot");
  	revert_correction("decoder.fivot", "decoder.correction");
	//compress
  	revert_protocol("decoder.correction", "decode.protocol");

	remove("decoder.fivot");
	remove("decoder.correction");
	rename("decode.protocol", "decode.txt");
}
