#include "core.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>


void Read_User(BITFILE* bf, User* user){
	char id_buffer;
	char name_buffer;
	int GENDER_buffer;

	for(int i = 0; id_buffer != ','; i++){
		bread(CHAR, bf, &id_buffer, 7, 1);
		if(id_buffer == ',')
			break;
		user->id[i] = id_buffer;
	}
	
	for(int i = 0; name_buffer != ','; i++){
		bread(CHAR, bf, &name_buffer, 7, 1);
		if(name_buffer == ',')
			break;
		user->name[i] = name_buffer; 
	}

	bread(INT, bf, &GENDER_buffer, 1, 1);
	if(GENDER_buffer == 0)
		strcpy(user->gender, "MALE");
	else
		strcpy(user->gender, "FEMALE");

  bread(INT, bf, &user->age, 7, 1);
	bread(INT, bf, &user->hp, 8, 1);
	bread(INT, bf, &user->mp, 8, 1);
	bread(INT, bf, &user->coin, 16, 1);
	
	return;
}

void Read_Item(BITFILE* bf, User* user){
	int ITEM_count;
	int ITEM_buffer;

	Item* item = NULL;
	bread(INT, bf, &ITEM_count, 3, 1);
	
	for(int i = 0; i < ITEM_count; i++){
		item = new_item();
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

		bread(INT, bf ,&item->count, 8, 1);
    enqueue(user->items, item);
	}
	free_item(item);
	return;
}

void Read_Friend(BITFILE* bf, User* user){
	Friend* friend = NULL;
	int FRIEND_count;
	char FRIEND_id_buffer;
	char FRIEND_name_buffer;
	int FRIEND_gender_buffer;

  bread(INT, bf, &FRIEND_count, 7, 1); //친구 수

	
	for(int i = 0; i < FRIEND_count; i++){
		friend = new_friend();

		for(int k = 0; FRIEND_id_buffer != ','; k++){
			bread(CHAR, bf, &FRIEND_id_buffer, 7, 1);
			friend->id[k] = FRIEND_id_buffer;
		}

		for(int j = 0; FRIEND_name_buffer != ','; j++){
			bread(CHAR, bf, &FRIEND_name_buffer, 7, 1);
			friend->name[j] = FRIEND_name_buffer;
	}

		bread(INT, bf, &FRIEND_gender_buffer, 1, 1);
		if(FRIEND_gender_buffer == 0)
			strcpy(friend->gender, "MALE");
		else
			strcpy(friend->gender, "FEMALE");
	
		bread(INT, bf, &friend->age, 7, 1);
		enqueue(user->friends, friend);		

	  free_friend(friend);
	}
	return;
}

void Read_Description(BITFILE* bf, User* user){
	char Description_buffer;

	for(int i = 0; Description_buffer != '\0'; i++){
		bread(CHAR, bf, &Description_buffer, 7, 1);
		user->description[i] = Description_buffer;
	}

	return;

}
int main() {

	printf("line 113\n");
	BITFILE *bf = bopen("data.encoded", "rb");

  // read_bits();
  // remove_ecc();
  // decompress();
  // decode();
	User user;
  Item *item = NULL;
  Friend *friend = NULL;

  user.items = new_queue();
	user.friends = new_queue();	

	Read_User(bf, &user);
	Read_Item(bf, &user);
	printf("line 132\n");
	Read_Friend(bf, &user);
	printf("line 133\n");
	Read_Description(bf, &user);
	printf("line 135\n");

  // read description
  printf("%s\n", user.id);
  printf("%s\n", user.name);
  printf("%s\n", user.gender);
  printf("%d\n", user.age);
  printf("%d\n", user.hp);
  printf("%d\n", user.mp);
  printf("%d\n", user.coin);

	int ITEM_count = q_len(user.items);

  for (int k = 0; k < ITEM_count; k++) {
    item = dequeue(user.items);
    printf("%s : ", item->name);
    printf("%d\n", item->count);
  }

	int FRIEND_count = q_len(user.friends);
  printf("\n%d\n", FRIEND_count);

  for (int k = 0; k < FRIEND_count; k++) {
    friend  = dequeue(user.friends);
    printf("%s / ", friend->id);
    printf("%s / ", friend->name);
    printf("%s / ", friend->gender);
    printf("%d / ", friend->age);
    printf("\n\n");
  }

  printf("%s\n", user.description);

  // write_text();

  free_item(item);
  free_friend(friend);
  free_queue(user.items);
  free_queue(user.friends);

  bclose(bf);
}
