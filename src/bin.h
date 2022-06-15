#ifndef BIN_H
#define BIN_H

#include "bit.h"
#include "utils.h"

void bin_encode(char *input, char *output);
void bin_decode(char *input, char *output);

void read_user(BITFILE *bf, User *user);
void read_item(BITFILE *bf, User *user);
void read_friend(BITFILE *bf, User *user);
void read_description(BITFILE *bf, User *user);

void write_user(User *user, BITFILE *bf);
void write_item(User *user, BITFILE *bf);
void write_friend(User *user, BITFILE *bf);
void write_description(User *user, BITFILE *bf);

#endif
