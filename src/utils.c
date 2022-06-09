#include "utils.h"

#include <string.h>

Item *new_item(void) {
  Item *item = (Item *)malloc(sizeof(Item));
  item->count = 0;
  return item;
}

void free_item(Item *item) { free(item); }

Friend *new_friend(void) { return (Friend *)malloc(sizeof(Friend)); }

void free_friend(Friend *friend) { free(friend); }
