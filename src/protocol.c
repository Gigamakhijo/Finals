#include "protocol.h"
#include "bit.h"
#include "text.h"
#include "utils.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>

void read_user(BITFILE *bf, User *user) {
  int id_index = 0;
  int name_index = 0;
  int gender;
  while (1) {
    char id_buffer;
    bread(CHAR, bf, &id_buffer, 7, 1);
    if (id_buffer == ',')
      break;
    user->id[id_index++] = id_buffer;
  }
  user->id[id_index] = '\0';

  while (1) {
    char name_buffer;

    bread(CHAR, bf, &name_buffer, 7, 1);
    if (name_buffer == ',')
      break;
    user->name[name_index++] = name_buffer;
  }
  user->name[name_index] = '\0';

  bread(INT, bf, &gender, 1, 1);
  if (gender == 0)
    strcpy(user->gender, "MALE");
  else
    strcpy(user->gender, "FEMALE");
  bread(INT, bf, &user->age, 7, 1);
  bread(INT, bf, &user->hp, 8, 1);
  bread(INT, bf, &user->mp, 8, 1);
  bread(INT, bf, &user->coin, 16, 1);

  return;
}

void read_item(BITFILE *bf, User *user) {
  int ITEM_count;
  bread(INT, bf, &ITEM_count, 3, 1);

  for (int i = 0; i < ITEM_count; i++) {
    int ITEM_buffer;
    Item *item = new_item();
    bread(INT, bf, &ITEM_buffer, 3, 1);

    if (ITEM_buffer == 0)
      strcpy(item->name, "BOMB");
    else if (ITEM_buffer == 1)
      strcpy(item->name, "POTION");
    else if (ITEM_buffer == 2)
      strcpy(item->name, "CURE");
    else if (ITEM_buffer == 3)
      strcpy(item->name, "BOOK");
    else if (ITEM_buffer == 4)
      strcpy(item->name, "SHIELD");
    else
      strcpy(item->name, "CANNON");

    bread(INT, bf, &item->count, 8, 1);
    enqueue(user->items, item);
  }
  return;
}

void read_friend(BITFILE *bf, User *user) {
  int count;
  bread(INT, bf, &count, 7, 1); //친구 수
  for (int i = 0; i < count; i++) {

    Friend *friend = new_friend();
    int gender;
    int age;
    int id_index = 0;
    int name_index = 0;
    while (1) {
      char buffer;
      bread(CHAR, bf, &buffer, 7, 1);
      if (buffer == ',') {
        break;
      }
      friend->id[id_index++] = buffer;
    }
    friend->id[id_index] = '\0';
    while (1) {
      char buffer;
      bread(CHAR, bf, &buffer, 7, 1);
      if (buffer == ',')
        break;
      friend->name[name_index++] = buffer;
    }
    friend->name[name_index] = '\0';
    bread(INT, bf, &gender, 1, 1);
    if (gender == 0) {
      strcpy(friend->gender, "MALE");
    } else {
      strcpy(friend->gender, "FEMALE");
    }
    bread(INT, bf, &age, 7, 1);
    friend->age = age;

    enqueue(user->friends, friend);
  }
  return;
}

void read_description(BITFILE *bf, User *user) {
  int index = 0;
  while (1) {
    char buffer;
    bread(CHAR, bf, &buffer, 7, 1);
    if (feof(bf->fp) == 1)
      break;
    if (buffer == '\0')
      break;
    user->description[index++] = buffer;
  }
  user->description[index] = '\0';
  return;
}

void write_user(User *user, BITFILE *bf) {
  int gender;
  char next = ',';

  const char str_male[] = "MALE";
  const char str_female[] = "FEMALE";
  if (strcmp(user->gender, str_male) == 0)
    gender = 0;
  else if (strcmp(user->gender, str_female) == 0)
    gender = 1;

  bwrite(CHAR, bf, user->id, 7, strlen(user->id));
  bwrite(CHAR, bf, &next, 7, 1);
  bwrite(CHAR, bf, user->name, 7, strlen(user->name));
  bwrite(CHAR, bf, &next, 7, 1);
  bwrite(INT, bf, &gender, 1, 1);
  bwrite(INT, bf, &user->age, 7, 1);
  bwrite(INT, bf, &user->hp, 8, 1);
  bwrite(INT, bf, &user->mp, 8, 1);
  bwrite(INT, bf, &user->coin, 16, 1);
}

void write_item(User *user, BITFILE *bf) {
  char *bomb = "BOMB: ";
  char *potion = "POTION: ";
  char *cure = "CURE: ";
  char *book = "BOOK: ";
  char *shield = "SHIELD: ";
  char *cannon = "CANNON: ";

  int item_len = q_len(user->items);
  bwrite(INT, bf, &item_len, 3, 1);

  for (int i = 0; i < item_len; i++) {
    Item *item = dequeue(user->items);
    int item_id;
    if (strcmp(item->name, bomb) == 0)
      item_id = 0;
    else if (strcmp(item->name, potion) == 0)
      item_id = 1;
    else if (strcmp(item->name, cure) == 0)
      item_id = 2;
    else if (strcmp(item->name, book) == 0)
      item_id = 3;
    else if (strcmp(item->name, shield) == 0)
      item_id = 4;
    else if (strcmp(item->name, cannon) == 0)
      item_id = 5;

    bwrite(INT, bf, &item_id, 3, 1);
    bwrite(INT, bf, &item->count, 8, 1);
  }
}

void write_friend(User *user, BITFILE *bf) {
  int gender;
  int friend_len = q_len(user->friends);
  char next = ',';
  const char str_male[] = "MALE";
  const char str_female[] = "FEMALE";

  bwrite(INT, bf, &friend_len, 7, 1);

  for (int i = 0; i < friend_len; i++) {
    Friend *friend = dequeue(user->friends);

    bwrite(CHAR, bf, friend->id, 7, strlen(friend->id));
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
}

void write_description(User *user, BITFILE *bf) {
  char end = '\0';
  bwrite(CHAR, bf, user->description, 7, strlen(user->description));
  bwrite(CHAR, bf, &end, 7, 1);
}

void convert_protocol(char *input, char *output) {
  FILE *fp = fopen(input, "r");
  if (!fp) {
    perror("File opening failed");
    return;
  }

  User user;
  if (read_text(&user, fp) == -1) {
    fclose(fp);
    exit(1);
  } else
    fclose(fp);

  BITFILE *wbf = bopen(output, "wb");
  write_user(&user, wbf);
  write_item(&user, wbf);
  write_friend(&user, wbf);
  write_description(&user, wbf);

  bflush(wbf);
  bclose(wbf);
  free_queue(user.items);
  free_queue(user.friends);
}

void revert_protocol(char *input, char *output) {
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
