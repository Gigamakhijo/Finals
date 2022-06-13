#include "core.h"

#include <assert.h>
#include <stdio.h>

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

  BITFILE *wbf = bopen(input, "wb");
  write_user(&user, wbf);
  write_item(&user, wbf);
  write_friend(&user, wbf);
  write_description(&user, wbf);

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
