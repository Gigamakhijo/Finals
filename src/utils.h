#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>
#include <stdlib.h>

#include "queue.h"

#define MAXID 256
#define MAXNAME 256
#define MAXGENDER 8 // MALE: 5, FEMALE: 7
#define ITEMCOUNT 6
#define MAXDESCRIPTION 1001

typedef struct Item {
  char name[MAXNAME];
  uint8_t count;
} Item;

typedef struct Friend {
  char id[MAXID];
  char name[MAXNAME];
  char gender[MAXGENDER];
  uint8_t age;
} Friend;

typedef struct {
  char id[MAXID];
  char name[MAXNAME];
  char gender[MAXGENDER];
  uint8_t age;
  uint8_t hp;
  uint8_t mp;
  uint16_t coin;

  Queue *items;

  Queue *friends;

  char description[MAXDESCRIPTION];
} User;

Item *new_item(void);
void free_item(Item *item);

Friend *new_friend(void);
void free_friend(Friend *friend_);

#endif
