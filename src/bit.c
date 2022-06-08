#include "bit.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

BITFILE *initBF(FILE *fp) {
  BITFILE *bf = (BITFILE *)malloc(sizeof(BITFILE));
  bf->offset = 0;
  bf->buffer = 0x00;
  bf->fp = fp;
  return bf;
}

void clearBF(BITFILE *bf) {
  bf->offset = 0;
  bf->buffer = 0x00;
}

int getMaskedBit(int shift) { return (int)((1 << shift) - 1); }

// BitBuffer 내용 다 출력
void bflush(BITFILE *bf) { fwrite(&bf->buffer, 1, 1, bf->fp); }
// BitBuffer 초기화
BITFILE *bopen(char *filename, char *mode) {
  FILE *fp = fopen(filename, mode);
  if (fp == NULL) exit(1);
  // init BITFILE buffer
  BITFILE *bf = initBF(fp);
  return bf;
}

void bclose(BITFILE *bf) {
  fclose(bf->fp);
  free(bf);
}

//비트 버퍼가 FULL 유무
int isFullBF(BITFILE *bf) { return bf->offset == 8; }

int readFirstBit(BITFILE *bf) {
  int result = (bf->buffer & 128) >> 7;
  bf->buffer = bf->buffer << 1;
  bf->offset--;
  return result;
}

// BitBuffer에 1bit 추가
void addBF(BITFILE *bf, int bit) { bf->buffer |= (bit << (7 - bf->offset++)); }

// BitBuffer에 새로운 1바이트 세팅
void fillBF(BITFILE *bf) {
  fread(&bf->buffer, 1, 1, bf->fp);
  bf->offset = 8;
}

void checkBF(BITFILE *bf) {
  if (!isFullBF(bf)) return;
  bflush(bf);
  clearBF(bf);
}

// INT
// data를 정해진 Bit로 쪼개서 저장
void bwriteInt(BITFILE *bf, int *data, int bitSize, int length) {
  for (int i = 0; i < length; i++) {
    int masked = data[i] & getMaskedBit(bitSize);
    for (int j = 0; j < bitSize; j++) {
      int bit = masked >> (bitSize - j - 1) & 1;
      addBF(bf, bit);
      checkBF(bf);
    }
  }
}

void breadInt(BITFILE *bf, int *data, int bitSize, int length) {
  for (int i = 0; i < length; i++) {
    *(data + i) = 0;
    for (int j = 0; j < bitSize; j++) {
      if (bf->offset == 0) {  //비어있을시
        fillBF(bf);
      }

      *(data + i) = *(data + i) << 1;
      *(data + i) |= readFirstBit(bf);
    }
  }
}

void bwriteChar(BITFILE *bf, char *str, int bitSize, int length) {
  for (int i = 0; i < length; i++) {
    for (int j = 0; j < bitSize; j++) {
      int bit = str[i] >> (bitSize - j - 1) & 1;
      addBF(bf, bit);
      checkBF(bf);
    }
  }
  // flushBF(bf);
}

void breadChar(BITFILE *bf, char *data, int bitSize, int length) {
  for (int i = 0; i < length; i++) {
    *(data + i) = 0;
    for (int j = 0; j < bitSize; j++) {
      if (bf->offset == 0) {  //비어있을시
        fillBF(bf);
      }
      *(data + i) = *(data + i) << 1;
      *(data + i) |= readFirstBit(bf);
    }
  }
}

void bread(TYPE type, BITFILE *bf, void *data, int bitSize, int length) {
  switch (type) {
    case INT:
      breadInt(bf, data, bitSize, length);
      break;
    case CHAR:
      breadChar(bf, data, bitSize, length);
      break;
  }
}

void bwrite(TYPE type, BITFILE *bf, void *data, int bitSize, int length) {
  switch (type) {
    case INT:
      bwriteInt(bf, data, bitSize, length);
      break;
    case CHAR:
      bwriteChar(bf, data, bitSize, length);
      break;
  }
}
