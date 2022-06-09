#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>

#define MAXID 255
#define MAXNAME 255
#define MAXGENDER 8  // MALE: 5, FEMALE: 7
#define ITEMCOUNT 6

typedef struct {
  char id[MAXID];
  char name[MAXNAME];
  char gender[MAXGENDER];
  uint8_t age;
} User;

typedef struct {
  uint8_t hp;
  uint8_t mp;
  uint16_t coin;
} Status;

typedef struct {
  User user;
  Status status;
} UserStatus;

typedef struct {
  char *name;
  uint8_t count;
} Item;

typedef struct {
  Item *item_list;
  int count;
} Items;

typedef struct {
  User *friends_list;
  int count;
} FriendsList;

typedef struct {
  UserStatus user_status;
  Items items;
  FriendsList friends_list;
  char *description;
} Data;

#endif
