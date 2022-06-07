#ifndef BIT_H
#define BIT_H

#include <stdio.h>
#include <stdint.h>

typedef struct BITFILE {
	int offset;
    uint8_t buffer;
	FILE * fp;
} BITFILE;

typedef enum TYPE {
  INT,
  CHAR,
} TYPE;

BITFILE * bopen(char * filename, char * mode);
void bclose(BITFILE *bf);
void bflush(BITFILE *bf);
void bread(TYPE type, BITFILE *bf, void * data, int bitSize, int length);
void bwrite(TYPE type, BITFILE *bf, void * data, int bitSize, int length);

#endif
