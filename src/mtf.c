#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Returns index at which character of the input text
// exists in the list
int search(char input_char, char *list) {
  int i;
  for (i = 0; i < strlen(list); i++)
    if (list[i] == input_char) {
      break;
    }

  return i;
}

// Takes curr_index of input_char as argument
// to bring that character to the front of the list
void moveToFront(int curr_index, char *list) {
  char *record = (char *)malloc(sizeof(char) * 26);
  strcpy(record, list);

  // Characters pushed one position right
  // in the list up until curr_index
  strncpy(list + 1, record, curr_index);

  // Character at curr_index stored at 0th position
  list[0] = record[curr_index];
}

// Move to Front Encoding
int *mtf_encode(char *input_text, char *list) {
  int len_text = strlen(input_text);
  int i;
  int *output_arr = (int *)malloc(len_text * sizeof(int));

  for (i = 0; i < len_text; i++) {

    // Linear Searches the characters of input_text
    // in list
    output_arr[i] = search(input_text[i], list);

    // Moves the searched character to the front
    // of the list
    moveToFront(output_arr[i], list);
  }

  return output_arr;
}

char *mtf_decode(int *arr, int text_len, char *list) {
  char *str = malloc((text_len + 1) * sizeof(char));

  int i;
  for (i = 0; i < text_len; i++) {
    str[i] = list[arr[i]];
    moveToFront(arr[i], list);
  }

  str[i] = '\0';
  return str;
}
