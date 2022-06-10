#include "core.h"

#include <stdio.h>
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

  Item *item;
  Friend *friend;

  BITFILE *bf = bopen("data.encoded", "wb");

  char next = ',';
  int g_buffer;
  int item_len;
  int friend_len;
  int i_buffer;

  const char str_male[] = "MALE";
  const char str_female[] = "FEMALE";
  if (strcmp(user.gender, str_male) == 0)
    g_buffer = 0;
  else if (strcmp(user.gender, str_female) == 0)
    g_buffer = 1;

  bwrite(CHAR, bf, user.id, 7, strlen(user.id));
  bwrite(CHAR, bf, &next, 7, 1);
  bwrite(CHAR, bf, user.name, 7, strlen(user.name));
  bwrite(CHAR, bf, &next, 7, 1);
  bwrite(INT, bf, &g_buffer, 1, 1);
  bwrite(INT, bf, &user.age, 7, 1);
  bwrite(INT, bf, &user.hp, 8, 1);
  bwrite(INT, bf, &user.mp, 8, 1);
  bwrite(INT, bf, &user.coin, 16, 1);

  char *bomb = "BOMB: ";
  char *potion = "POTION: ";
  char *cure = "CURE: ";
  char *book = "BOOK: ";
  char *shield = "SHIELD: ";
  char *cannon = "CANNON: ";

  item_len = q_len(user.items);
  bwrite(INT, bf, &item_len, 3, 1);

  for (int i = 0; i < item_len; i++) {
    item = dequeue(user.items);
    printf("%s\n", item->name);
    if (strcmp(item->name, bomb) == 0)
      i_buffer = 0;
    else if (strcmp(item->name, potion) == 0)
      i_buffer = 1;
    else if (strcmp(item->name, cure) == 0)
      i_buffer = 2;
    else if (strcmp(item->name, book) == 0)
      i_buffer = 3;
    else if (strcmp(item->name, shield) == 0)
      i_buffer = 4;
    else if (strcmp(item->name, cannon) == 0)
      i_buffer = 5;

    bwrite(INT, bf, &i_buffer, 3, 1);
    bwrite(INT, bf, &item->count, 8, 1);
  }

  int gender;
  friend_len = q_len(user.friends);
  bwrite(INT, bf, &friend_len, 7, 1);
  for (int i = 0; i < friend_len; i++) {
    friend = dequeue(user.friends);

    bwrite(CHAR, bf, friend->id, 7, strlen(friend->id));
    printf("%d : %s\n", i, friend->id);
    bwrite(CHAR, bf, &next, 7, 1);
    bwrite(CHAR, bf, friend->name, 7, strlen(friend->name));
    bwrite(CHAR, bf, &next, 7, 1);
    if (strcmp(friend->gender, str_male) == 0) {
      gender = 0;
    } else if (strcmp(friend->gender, str_female) == 0) {
      gender = 1;
    }
    bwrite(INT, bf, &gender, 1, 1);
    bwrite(INT, bf, &friend->age, 7, 1);
  }

  bwrite(CHAR, bf, user.description, 7, strlen(user.description));

  free_queue(user.items);
  free_queue(user.friends);
}
