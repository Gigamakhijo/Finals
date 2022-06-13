#include "pivot.h"
#include "bit.h"
#include <stdint.h>
#include <stdlib.h>
#include <sys/stat.h>

int filesize(const char *filename) {
  struct stat file_info;
  if (0 > stat(filename, &file_info)) {
    return -1; // file이 없거나 에러
  }
  return file_info.st_size;
}

int **new_bitmap(int chunk_size) {
  int **bitmap = malloc(sizeof(int *) * 8);
  //초기화 과정a
  for (int i = 0; i < 8; i++) {
    bitmap[i] = malloc(sizeof(int) * chunk_size);
  }
  return bitmap;
}

int **new_pivot_bitmap(int chunk_size) {
  int **bitmap = malloc(sizeof(int *) * chunk_size);
  //초기화 과정
  for (int i = 0; i < chunk_size; i++) {
    bitmap[i] = malloc(sizeof(int) * 8);
  }
  return bitmap;
}

void set_bitmap(int **bitmap, int chunk_size, BITFILE *bf) {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < chunk_size; j++) {
      bread(INT, bf, &bitmap[i][j], 1, 1);
    }
  }
}

void set_pivot_bitmap(int **bitmap, int chunk_size, BITFILE *bf) {
  for (int i = 0; i < chunk_size; i++) {
    for (int j = 0; j < 8; j++) {
      bread(INT, bf, &bitmap[i][j], 1, 1);
    }
  }
}

void print_bitmap(int **bitmap, int chunk_size) {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < chunk_size; j++) {
      printf("%d ", bitmap[i][j]);
    }
    printf("\n");
  }
}

void print_pivot_bitmap(int **bitmap, int chunk_size) {
  for (int i = 0; i < chunk_size; i++) {
    for (int j = 0; j < 8; j++) {
      printf("%d ", bitmap[i][j]);
    }
    printf("\n");
  }
}

void free_bitmap(int **bitmap) {
  for (int i = 0; i < 8; i++) {
    free(bitmap[i]);
  }
  free(bitmap);
}

void free_pivot_bitmap(int **bitmap, int chunk_size) {
  for (int i = 0; i < chunk_size; i++) {
    free(bitmap[i]);
  }
  free(bitmap);
}

void convert_pivot(char *input, char *output) {
  int chunk = filesize(input);
  int **bitmap = new_bitmap(chunk);
  BITFILE *rbf, *wbf;
  rbf = bopen(input, "rb");
  wbf = bopen(output, "wb");
  set_bitmap(bitmap, chunk, rbf);
  for (int i = 0; i < chunk; i++) {
    for (int j = 0; j < 8; j++) {
      bwrite(INT, wbf, &bitmap[j][i], 1, 1);
    }
  }
  free_bitmap(bitmap);
  bflush(wbf);
  bclose(wbf);
  bclose(rbf);
}

void revert_pivot(char *input, char *output) {
  int chunk = filesize(input);
  int **bitmap = new_pivot_bitmap(chunk);

  BITFILE *rbf, *wbf;
  rbf = bopen(input, "rb");
  wbf = bopen(output, "wb");
  set_pivot_bitmap(bitmap, chunk, rbf);
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < chunk; j++) {
      bwrite(INT, wbf, &bitmap[j][i], 1, 1);
    }
  }

  free_pivot_bitmap(bitmap, chunk);
  bflush(wbf);
  bclose(wbf);
  bclose(rbf);
}
