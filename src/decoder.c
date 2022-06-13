#include "core.h"

#include <assert.h>
#include <stdio.h>

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
  read_description(rbf, &user);

  bclose(rbf);

  write_text(&user, output);

  free_queue(user.items);
  free_queue(user.friends);
}
