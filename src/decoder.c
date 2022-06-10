#include "core.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

int main() {
  // read_bits();
  // remove_ecc();
  // decompress();
  // decode();
  Item *item = NULL;
  Friend *friend = NULL;
  User user;

  BITFILE *bf = NULL;
  bf = bopen("data.encoded", "rb");

  char c;

  int GENDER_count = 0;

  int ITEM_count;
  int ITEM_name;

  int FRIEND_count;

  int i = 0;
  while (1) {
    bread(CHAR, bf, &c, 7, 1); // Status의 ID 읽어오기
    if (c == ',') //, 나올 때까지 읽고 나오면 id 인식 종료
      break;
    else {
      user.id[i] = c;
      i++;
    }
  }

  i = 0;

  while (1) {
    bread(CHAR, bf, &c, 7, 1); // Status의 ID 읽어오기
    if (c == ',') //, 나올 때까지 읽고 나오면 id 인식 종료
      break;
    else {
      user.name[i] = c;
      i++;
    }
  }

  bread(CHAR, bf, &GENDER_count, 1, 1);
  if (GENDER_count == 0)
    strcpy(user.gender, "MALE");
  else
    strcpy(user.gender, "FEMALE");

  bread(INT, bf, &user.age, 7, 1);
  printf("%d\n", user.age);
  bread(INT, bf, &user.hp, 8, 1);
  printf("%d\n", user.hp);
  bread(INT, bf, &user.mp, 8, 1);
  printf("%d\n", user.mp);
  bread(INT, bf, &user.coin, 16, 1);
  printf("%d\n", user.coin);

  bread(INT, bf, &ITEM_count, 3, 1); // ITEM 종류 개수
  printf("%d\n", ITEM_count);

  user.items = new_queue();

  for (int k = 0; k < ITEM_count; k++) {
    item = new_item();
    bread(INT, bf, &ITEM_name, 3, 1);
    printf("%d\n", ITEM_count);
    if (ITEM_name == 0)
      strcpy(item->name, "BOMB");
    else if (ITEM_name == 1)
      strcpy(item->name, "POTION");
    else if (ITEM_name == 2)
      strcpy(item->name, "CURE");
    else if (ITEM_name == 3)
      strcpy(item->name, "BOOK");
    else if (ITEM_name == 4)
      strcpy(item->name, "SHILED");
    else
      strcpy(item->name, "CANNON");
    printf("%s\n", item->name);
    bread(INT, bf, &item->count, 8, 1);
    printf("%d\n", ITEM_count);
    enqueue(user.items, item);
  }

  bread(INT, bf, &FRIEND_count, 7, 1); //친구 수
  printf("%d\n", FRIEND_count);

  i = 0;
  user.friends = new_queue();
  printf("friend count : %d\n", FRIEND_count);
  for (int k = 0; FRIEND_count; k++) {

    friend = new_friend();
    i = 0;
    while (1) {
      bread(CHAR, bf, &c, 7, 1);
      if (c == ',') {
        friend->id[i] = '\0';
        break;
      } else {
        friend->id[i++] = c;
      }
    }
    printf("id : %s\n", friend->id);
    i = 0;

    while (1) {
      bread(CHAR, bf, &c, 7, 1);
      if (c == ',')
        break;
      else {
        friend->name[i] = c;
        i++;
      }
    }
    printf("%s\n", friend->name);
    bread(CHAR, bf, &GENDER_count, 1, 1);
    printf("%c\n", c);
    printf("gender cound %d\n", GENDER_count);
    if (GENDER_count == 0)
      strcpy(friend->gender, "MALE");
    else
      strcpy(friend->gender, "FEMALE");
    bread(INT, bf, &friend->age, 7, 1);
    printf("%s\n", friend->gender);
    printf("%d\n", friend->age);

    enqueue(user.friends, friend);
  }

  // read description
  i = 0;
  while (1) {
    bread(CHAR, bf, &c, 7, 1);
    printf("%c", c);
    if (c == '\0')
      break;
    else {
      user.description[i] = c;
      i++;
    }
  }

  printf("%s\n", user.id);
  printf("%s\n", user.name);
  printf("%s\n", user.gender);
  printf("%d\n", user.age);
  printf("%d\n", user.hp);
  printf("%d\n", user.mp);
  printf("%d\n", user.coin);
  printf("%d\n\n", ITEM_count);

  for (int k = 0; k < ITEM_count; k++) {
    Item *item = dequeue(user.items);
    printf("%s : ", item->name);
    printf("%d\n", item->count);
  }

  printf("\n%d\n", FRIEND_count);

  for (int k = 0; k < FRIEND_count; k++) {
    Friend *friend = dequeue(user.friends);
    printf("%s / ", friend->id);
    printf("%s / ", friend->name);
    printf("%s / ", friend->gender);
    printf("%d / ", friend->age);
    printf("\n\n");
  }

  printf("%s\n", user.description);

  // write_text();

  free_queue(user.items);
  free_queue(user.friends);
  free_item(item);
  free_friend(friend);

  bclose(bf);
}
