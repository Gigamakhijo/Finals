#ifndef MTF_H
#define MTF_H

int *mtf_encode(char *src, char *list);
char *mtf_decode(int *src, int text_len, char *list);

#endif
