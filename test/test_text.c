#include <stdio.h>

#include "core.h"

#include <assert.h>
#include <string.h>

int main(int argc, char *argv[]) {
  FILE *fp = fopen(argv[1], "r");
  if (!fp) {
    perror("File opening failed");
    return -1;
  }

  User user;
  if (read_text(&user, fp) == -1) {
    fclose(fp);
    exit(1);
  } else
    fclose(fp);

  assert(strcmp(user.id, "KMU_CS23") == 0);
  assert(strcmp(user.name, "HONG CHAN PARK") == 0);
  assert(strcmp(user.gender, "FEMALE") == 0);
  assert(user.age == 33);
  assert(user.hp == 200);
  assert(user.mp == 5);
  assert(user.coin == 43210);

  Item *item;
  while (q_len(user.items) > 0) {
    item = dequeue(user.items);
    printf("%s%d\n", item->name, item->count);
    free_item(item);
  }
  putchar('\n');

  Friend *friend;
  for (int i = 1; q_len(user.friends) > 0; i++) {
    friend = dequeue(user.friends);
    printf("FRIEND%d ID: %s NAME: %s GENDER: %s AGE: %d\n", i, friend->id,
           friend->name, friend->gender, friend->age);
    free_friend(friend);
  }
  putchar('\n');

  printf("%s\n", user.description);

  free_queue(user.items);
  free_queue(user.friends);
}
