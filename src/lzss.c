#include "lzss.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 100000

struct List {
  char *buf;
  size_t len;
  size_t size;
};

typedef struct List List;

List *list_new(size_t size) {
  List *list = malloc(sizeof(List));
  list->buf = malloc(size);
  list->len = 0;
  list->size = size;
  return list;
}

void list_free(List *list) {
  free(list->buf);
  free(list);
}

void list_append(List *list, char c) { list->buf[list->len++] = c; }

List *list_slice(List *list, size_t start, size_t end) {
  List *slice = list_new(list->size);
  for (size_t i = start; i < end; i++)
    slice->buf[i] = list->buf[i];

  return slice;
}

size_t elements_in_array(List *check, List *elements) {
  size_t offset = 0;
  for (size_t i = 0; i < elements->len; i++) {
    if (check->len <= offset)
      return i - check->len;

    if (check->buf[offset] == elements->buf[i])
      offset++;
    else
      offset = 0;
  }
  return -1;
}

size_t lzss_encode(char *buf, size_t size, size_t max_sliding_window_size) {
  List *buffer = list_new(10000);
  memcpy(buffer->buf, buf, size);

  List *search_buffer = list_new(10000);
  List *check_characters = list_new(10000);
  List *output = list_new(10000);

  for (int i = 0; i < size; i++) {
    list_append(check_characters, buffer->buf[i]);
    int index = elements_in_array(check_characters, search_buffer);

    if (index == -1 || i == (size - 1)) {
      if (check_characters->len > 1) {
        List *slice =
            list_slice(check_characters, 0, check_characters->len - 1);
        index = elements_in_array(slice, search_buffer);
        list_free(slice);

        int offset = i - index - check_characters->len + 1;
        size_t length = check_characters->len;

        char *token = malloc(1000);
        sprintf(token, "<%d,%zu>", offset, length);

        if (strlen(token) > length)
          for (size_t j = 0; j < check_characters->len; j++)
            list_append(output, check_characters->buf[j]);
        else
          for (size_t i = 0; i < strlen(token); i++)
            list_append(output, token[i]);

        free(token);
      } else
        list_append(output, check_characters->buf[0]);

      check_characters->len = 0;
    }

    list_append(search_buffer, buffer->buf[i]);

    if (search_buffer->len > max_sliding_window_size)
      for (int j = 1; j < search_buffer->len; j++) {
        search_buffer->buf[j - 1] = search_buffer->buf[j];
        search_buffer->len--;
      }
  }

  list_free(search_buffer);
  list_free(check_characters);
  buf = output->buf;
  size_t len = output->len;
  free(output);

  return len;
}

void compress(char *src, char *dst) {
  FILE *fp = fopen(src, "rb");
  char buf[BUFSIZE];
  size_t size = fread(buf, 1, BUFSIZE, fp);
  fclose(fp);

  size = lzss_encode(buf, size, 100);

  fp = fopen(dst, "wb");
  fwrite(buf, 1, size, fp);
  fclose(fp);
}

void decompress(char *src, char *dst) {
  FILE *fp = fopen(src, "rb");
  char buf[BUFSIZE];
  size_t size = fread(buf, 1, BUFSIZE, fp);
  fclose(fp);

  fp = fopen(dst, "wb");
  fwrite(buf, 1, size, fp);
  fclose(fp);
}
