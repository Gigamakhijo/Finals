#include "mtf.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Driver program to test functions above
int main() {
  char *input_text = "PANAMA";

  // Maintains an ordered list of legal symbols
  char *list = (char *)malloc(sizeof(char) * 27);
  strcpy(list, "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ$\n");

  printf("Input text: %s", input_text);
  printf("\nMove to Front Transform: ");

  // Computes Move to Front transform of given text
  int *arr = mtf_encode(input_text, list);
  for (int i = 0; i < strlen(input_text); i++)
    printf("%d ", arr[i]);
  putchar('\n');

  strcpy(list, "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ$\n");
  char *str = mtf_decode(arr, strlen(input_text), list);
  printf("%s\n", str);

  return 0;
}
