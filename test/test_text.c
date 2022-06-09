#include <stdio.h>

#include "queue.h"
#include "text.h"
#include "utils.h"

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

  printf("id: %s\n", user.id);
  printf("name: %s\n", user.name);
  printf("gender: %s\n", user.gender);
  printf("age: %d\n", user.age);
  printf("hp: %d\n", user.hp);
  printf("mp: %d\n", user.mp);
  printf("coin: %d\n", user.coin);

  printf("id: %d\n", user.coin);
  putchar('\n');

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
