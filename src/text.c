#include "text.h"
#include "queue.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRSIZE 200
#define MAXUSER 200
#define MAXDESCRIPTION 1000

#define TEST_ZERO(cond)                                                        \
  if ((cond) == 0)                                                             \
    return -1;
#define TEST_NULL(cond)                                                        \
  if ((cond) == NULL)                                                          \
    return -1;

char *item_keys[ITEMCOUNT] = {
    "BOMB: ", "POTION: ", "CURE: ", "BOOK: ", "SHIELD: ", "CANNON: "};

static char *sget_field(char *name, char *str) {
  // strip newline
  int n = strlen(name);
  str[strlen(str) - 1] = '\0';

  if (strncmp(str, name, n) != 0)
    return NULL;

  char tmp[STRSIZE];
  strcpy(tmp, str);
  strcpy(str, tmp + n);

  return str;
}

static char *get_field(char *name, char *str, FILE *fp) {
  if (fgets(str, STRSIZE, fp) == NULL)
    return NULL;
  return sget_field(name, str);
}

int read_text(User *user, FILE *fp) {
  char str[STRSIZE];

  TEST_NULL(fgets(str, STRSIZE, fp));
  TEST_ZERO(!strcmp(str, "*USER STATUS*\n"));

  TEST_NULL(get_field("ID: ", user->id, fp));

  TEST_NULL(get_field("NAME: ", user->name, fp));

  TEST_NULL(get_field("GENDER: ", user->gender, fp));

  TEST_NULL(get_field("AGE: ", str, fp));
  user->age = atoi(str);

  TEST_NULL(get_field("HP: ", str, fp));
  user->hp = atoi(str);

  TEST_NULL(get_field("MP: ", str, fp));
  user->mp = atoi(str);

  TEST_NULL(get_field("COIN: ", str, fp));
  user->coin = atoi(str);

  if (fgetc(fp) != '\n')
    return -1;

  TEST_NULL(fgets(str, STRSIZE, fp));
  TEST_ZERO(!strcmp(str, "*ITEMS*\n"));

  user->items = new_queue();

  Item *item;
  char *key;
  int count = 0;
  while (fgets(str, STRSIZE, fp) != NULL && *str != '\n' && count < ITEMCOUNT) {
    for (int i = 0; i < ITEMCOUNT; i++) {
      key = item_keys[i];
      if (strncmp(str, key, strlen(key)) == 0)
        break;
    }
    item = new_item();
    strcpy(item->name, key);

    TEST_NULL(sget_field(key, str));
    item->count = atoi(str);

    enqueue(user->items, item);
    count++;
  }

  TEST_NULL(fgets(str, STRSIZE, fp));
  TEST_ZERO(!strcmp(str, "*FRIENDS LIST*\n"));

  user->friends = new_queue();

  count = 0;
  char field[STRSIZE];
  int len = 0;

  Friend *friend;
  do {
    sprintf(field, "FRIEND%d ", count++ + 1);
    len = strlen(field);

    TEST_NULL(fgets(str, STRSIZE, fp));
    if (strcmp(str, "*DESCRIPTION*\n") == 0)
      break;

    friend = new_friend();

    strcat(field, "ID: ");
    TEST_NULL(sget_field(field, str));
    strcpy(friend->id, str);
    field[len] = '\0';

    strcat(field, "NAME: ");
    TEST_NULL(get_field(field, str, fp));
    strcpy(friend->name, str);
    field[len] = '\0';

    strcat(field, "GENDER: ");
    TEST_NULL(get_field(field, str, fp));
    strcpy(friend->gender, str);
    field[len] = '\0';

    strcat(field, "AGE: ");
    TEST_NULL(get_field(field, str, fp));
    friend->age = atoi(str);
    field[len] = '\0';

    enqueue(user->friends, friend);
  } while (fgets(str, STRSIZE, fp) != NULL && *str == '\n');

  fread(user->description, sizeof(char), MAXDESCRIPTION, fp);

  return 0;
}

void write_text(User *user, char * output){
  FILE *fp;
  fp = fopen(output, "w");
  if(fp==NULL) exit(1);
  fputs("*USER STATUS*\n", fp);
  fprintf(fp, "ID: %s\n",user->id);
  fprintf(fp, "NAME: %s\n",user->name);
  fprintf(fp, "GENDER: %s\n",user->gender);
  fprintf(fp, "AGE: %d\n",user->age);
  fprintf(fp, "HP: %d\n",user->hp);
  fprintf(fp, "MP: %d\n",user->mp);
  fprintf(fp, "COIN: %d\n",user->coin);
  fputc('\n', fp);

  fputs("*ITEMS*\n", fp);

  int item_count = q_len(user->items);
  for (int k = 0; k < item_count; k++) {
      Item * item = dequeue(user->items);
      fprintf(fp, "%s: %d\n", item->name, item->count);
  }
  fputc('\n', fp);

  fputs("*FRIENDS LIST*\n", fp);

  int friend_count = q_len(user->friends);
  for (int k = 0; k < friend_count; k++) {
      Friend * friend  = dequeue(user->friends);
      fprintf(fp, "FRIEND%d ID: %s\n", k+1, friend->id);
      fprintf(fp, "FRIEND%d NAME: %s\n", k+1, friend->name);
      fprintf(fp, "FRIEND%d GENDER: %s\n", k+1, friend->gender);
      fprintf(fp, "FRIEND%d AGE: %d\n", k+1, friend->age);
      fputc('\n', fp);
  }

  fputs("*DESCRIPTION*\n", fp);
  fprintf(fp, "%s", user->description);

  fclose(fp);

}
