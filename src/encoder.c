#include "core.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
  assert(argc > 2);

  char input[100];
  char output[100];
  sprintf(input, "%s.protocol", argv[2]);

  FILE *fp = fopen(argv[1], "r");
  if (!fp) {
    perror("File opening failed");
    exit(1);
  }

  User user;
  if (read_text(&user, fp) == -1) {
    fclose(fp);
    exit(1);
  } else
    fclose(fp);

  strcat(user.description, "$");

  char *bwt = bwt_encode(user.description);
  printf("bwt encode: %s\n", bwt);

  char *list = (char *)malloc(sizeof(char) * 100);
  strcpy(list, "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ$\n");
  int *arr = mtf_encode(bwt, list);

  printf("mtf encode: ");
  for (int i = 0; i < strlen(bwt); i++)
    printf("%d ", arr[i]);
  putchar('\n');

  int *enc = malloc(sizeof(int) * strlen(bwt));
  int len = rle_encode(enc, arr, strlen(bwt));

  printf("rle encode: ");
  for (int i = 0; i < len; i++)
    printf("%d ", enc[i]);
  putchar('\n');

  BITFILE *wbf = bopen(input, "wb");
  write_user(&user, wbf);
  write_item(&user, wbf);
  write_friend(&user, wbf);

  bwrite(INT, wbf, enc, 7, len);
  free(enc);

  bflush(wbf);
  bclose(wbf);

  free_queue(user.items);
  free_queue(user.friends);

  sprintf(input, "%s.protocol", argv[2]);
  sprintf(output, "%s.ecc", argv[2]);
  ecc_encode(input, output);

  sprintf(input, "%s.ecc", argv[2]);
  sprintf(output, "%s", argv[2]);
  pivot_encode(input, output);
}
