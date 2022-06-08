#include "text.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRSIZE 200
#define MAXUSER 200

#define test_zero(cond) \
  if ((cond) == 0) return -1;
#define test_null(cond) \
  if ((cond) == NULL) return -1;
#define test_neg(cond) \
  if ((cond) == -1) return -1;

char *item_keys[ITEMCOUNT] = {
    "BOMB: ", "POTION: ", "CURE: ", "BOOK: ", "SHIELD: ", "CANNON: "};

static char *StringGetField(char *name, char *str) {
  // strip newline
  int n = strlen(name);
  str[strlen(str) - 1] = '\0';

  if (strncmp(str, name, n) != 0) return NULL;

  char tmp[STRSIZE];
  strcpy(tmp, str);
  strcpy(str, tmp + n);

  return str;
}

static char *GetField(char *name, char *str, FILE *fp) {
  if (fgets(str, STRSIZE, fp) == NULL) return NULL;
  return StringGetField(name, str);
}

int ReadText(Data *data, FILE *fp) {
  char str[STRSIZE];

  User user = data->user_status.user;
  Status status = data->user_status.status;

  test_null(fgets(str, STRSIZE, fp));
  test_zero(!strcmp(str, "*USER STATUS*\n"));

  test_null(GetField("ID: ", str, fp));
  strcpy(user.id, str);

  test_null(GetField("NAME: ", str, fp));
  strcpy(user.name, str);

  test_null(GetField("GENDER: ", str, fp));
  strcpy(user.gender, str);

  test_null(GetField("AGE: ", str, fp));
  user.age = atoi(str);

  test_null(GetField("HP: ", str, fp));
  status.hp = atoi(str);

  test_null(GetField("MP: ", str, fp));
  status.mp = atoi(str);

  test_null(GetField("COIN: ", str, fp));
  status.coin = atoi(str);

  printf("%s\n%s\n%s\n%d %d %d %d\n", user.id, user.name, user.gender, user.age,
         status.hp, status.mp, status.coin);

  data->user_status.user = user;
  data->user_status.status = status;

  if (fgetc(fp) != '\n') return -1;

  Item *items = (Item *)malloc(sizeof(Item) * ITEMCOUNT);
  test_null(fgets(str, STRSIZE, fp));
  test_zero(!strcmp(str, "*ITEMS*\n"));

  int count = 0;
  while (fgets(str, STRSIZE, fp) != NULL && *str != '\n' && count < ITEMCOUNT) {
    char *key;
    for (int i = 0; i < ITEMCOUNT; i++) {
      key = item_keys[i];
      if (strncmp(str, key, strlen(key)) == 0) break;
    }

    test_null(StringGetField(key, str));

    items[count].name = key;
    items[count].count = atoi(str);
    count++;
  }

  data->items.count = count;
  data->items.item_list = items;

  putchar('\n');
  for (int i = 0; i < count; i++)
    printf("%s%d\n", items[i].name, items[i].count);

  User *users = (User *)malloc(sizeof(User) * MAXUSER);

  int i = 0;
  char field[STRSIZE];
  int len = 0;

  test_null(fgets(str, STRSIZE, fp));
  test_zero(!strcmp(str, "*FRIENDS LIST*\n"));

  do {
    sprintf(field, "FRIEND%d ", i + 1);
    len = strlen(field);

    test_null(fgets(str, STRSIZE, fp));
    if (strcmp(str, "*DESCRIPTION*\n") == 0) break;

    strcat(field, "ID: ");
    test_null(StringGetField(field, str));
    strcpy(users[i].id, str);
    field[len] = '\0';

    strcat(field, "NAME: ");
    test_null(GetField(field, str, fp));
    strcpy(users[i].name, str);
    field[len] = '\0';

    strcat(field, "GENDER: ");
    test_null(GetField(field, str, fp));
    strcpy(users[i].gender, str);
    field[len] = '\0';

    strcat(field, "AGE: ");
    test_null(GetField(field, str, fp));
    users[i].age = atoi(str);
    field[len] = '\0';

    i++;
  } while (fgets(str, STRSIZE, fp) != NULL && *str == '\n');

  data->friends_list.friends_list = users;
  data->friends_list.count = i;

  putchar('\n');
  for (int i = 0; i < data->friends_list.count; i++)
    printf("FRIEND%d ID: %s NAME: %s GENDER: %s AGE: %d\n", i + 1, users[i].id,
           users[i].name, users[i].gender, users[i].age);

  return 0;
}
