#include "core.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
  assert(argc > 2);

  char input[100];
  char output[100];
  sprintf(output, "%s.pivot", argv[2]);
  pivot_decode(argv[1], output);

  sprintf(input, "%s.pivot", argv[2]);
  sprintf(output, "%s.ecc", argv[2]);
  ecc_decode(input, output);

  sprintf(input, "%s.ecc", argv[2]);
  BITFILE *rbf = bopen(input, "rb");
  User user;
  user.items = new_queue();
  user.friends = new_queue();

  read_user(rbf, &user);
  read_item(rbf, &user);
  read_friend(rbf, &user);

  int len = 64;
  int *arr = malloc(sizeof(int) * len);

  int index = 0;
  while (1) {
    int buffer;
    bread(INT, rbf, &buffer, 7, 1);
    if (feof(rbf->fp) == 1)
      break;
    arr[index++] = buffer;
    if (index >= len) {
      len += 64;
      arr = realloc(arr, sizeof(int) * len);
    }
  }

  bclose(rbf);

  printf("raw val: ");
  for (int i = 0; i < index; i++)
    printf("%d ", arr[i]);
  putchar('\n');

  int *dec = malloc(sizeof(int) * 10000);
  len = rle_decode(dec, arr, index);

  printf("rle decode: ");
  for (int i = 0; i < len; i++)
    printf("%d ", dec[i]);
  putchar('\n');

  char list[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ$\n";

  char *str = mtf_decode(dec, len, list);
  free(dec);

  printf("mtf decode: %s\n", str);

  char *bwt = bwt_decode(str);
  free(str);

  printf("bwt decode: %s\n", bwt);

  // remove $
  bwt[strlen(bwt) - 1] = '\0';
  strcpy(user.description, bwt);
  free(bwt);

  write_text(&user, argv[2]);

  free_queue(user.items);
  free_queue(user.friends);
}
