#include "ecc.h"
#include "bit.h"

#include <stdlib.h>

int checkPowerOfTwo(int num) { return !(num & (num - 1)); }

int getBit(int data, int shift) { return (data >> shift) & 1; }

int power(int shift) { return 1 << shift; }

int encodeParity(int n, int p, int data) {
  int result = 0;
  int dataIndex = 0;
  //패리티 형식으로 바꿔주는 부분
  for (int i = 1; i < n + p + 1; i++) {
    if (checkPowerOfTwo(i))
      result |= 0;
    else
      result |= getBit(data, n - dataIndex++ - 1); //첫번째 부터
    if (i != (n + p))
      result = result << 1;
  }

  //각 패리티 범위만큼 계산해서 p를 넣어주는 함수
  for (int i = 0; i < p; i++) {
    int isCheck = 1;
    int turnCount = 0;
    int count = 0;

    for (int j = 0; j < n + p + 1; j++) { // 0 ~ n + p
      if (turnCount == 0) {
        turnCount = power(i);
        isCheck = !isCheck;
      }
      // printf(" %d", isCheck);
      if (isCheck == 1) {
        if ((result >> (n + p - j) & 1) == 1) {
          count++;
        }
      }
      turnCount--;
    }
    int parity = count % 2;
    // printf(" i = %d, parity = %d\n", i, parity);
    result |= parity << ((n + p) - (power(i)));
  }

  //패리티 코드가 적용된 해밍코드 출력
  return result;
}

int checkParity(int n, int p, int data) {
  int result = 0;

  for (int i = 0; i < p; i++) {
    int isCheck = 1;
    int turnCount = 0;
    int masked = power(i);
    int even = 0;
    for (int j = 0; j < n + p + 1; j++) {
      if (turnCount == 0) {
        turnCount = power(i);
        isCheck = !isCheck;
      }
      if (isCheck == 1) {
        if ((data >> (n + p - j) & 1) == 1) {
          even ^= j;
        }
      }
      turnCount--;
    }
    result |= (even & masked);
  }
  return result;
}

int decodeParity(int n, int p, int data, int checked) {
  int hamming_code = data;
  int result = 0;
  if (checked != 0) {
    int mask = 1 << (n + p - checked);
    hamming_code = data ^ mask;
  }
  for (int i = 1; i < n + p + 1; i++) {
    if (checkPowerOfTwo(i))
      continue;
    result = result << 1;
    result |= getBit(hamming_code, n + p - i); //첫번째 부터
  }

  return result;
}

void ecc_encode(char *input, char *output) {
  BITFILE *rbp, *wbp;
  rbp = bopen(input, "rb");
  wbp = bopen(output, "wb");

  char buffer;
  int parity;

  while (1) {
    bread(CHAR, rbp, &buffer, 4, 1);
    if (feof(rbp->fp))
      break; //파일 끝
    parity = encodeParity(4, 3, buffer);
    bwrite(CHAR, wbp, &parity, 8, 1);
  }
  bflush(wbp);
  bclose(wbp);
  bclose(rbp);
}

void ecc_decode(char *input, char *output) {
  BITFILE *rbp, *wbp;
  rbp = bopen(input, "rb");
  wbp = bopen(output, "wb");
  if (rbp == NULL) {
    fprintf(stderr, "파일열기 실패");
    exit(1);
  }
  wbp = bopen(output, "wb");
  if (wbp == NULL) {
    fprintf(stderr, "파일열기 실패");
    exit(1);
  }
  char buffer;
  while (1) {
    bread(CHAR, rbp, &buffer, 8, 1);
    if (feof(rbp->fp))
      break; //파일 끝
    int check = checkParity(4, 3, buffer);
    int n = decodeParity(4, 3, buffer, check);
    bwrite(INT, wbp, &n, 4, 1);
  }

  bflush(wbp);
  bclose(wbp);
  bclose(rbp);
}
