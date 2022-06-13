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

  int arr[10000];

  int index = 0;
  while (1) {
    int buffer;
    bread(INT, rbf, &buffer, 7, 1);
    if (feof(rbf->fp) == 1)
      break;
    arr[index++] = buffer;
  }

  bclose(rbf);

  char list[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ$\n";

  char *str = mtf_decode(arr, index, list);
  char *bwt = bwt_decode(str);
  free(str);

  // remove $
  bwt[strlen(bwt) - 1] = '\0';
  int i;
  for (i = 0; i < index; i++)
    user.description[i] = bwt[i];
  user.description[i] = '\0';
  free(bwt);

  write_text(&user, argv[2]);

  free_queue(user.items);
  free_queue(user.friends);
}
