#include <stdio.h>
#include <string.h>
#include <strings.h>

#include "01.h"

// === definitions

// path constants
const char *test_path = "./src/01/test.txt";
const char *main_path = "./src/01/main.txt";

//
// === main ===
int main() {
  int test_num = calc_number(test_path);
  // int main_num = calc_number(main_path);

  printf("Test calculation is %d\n", test_num);
  // printf("Main calculation is %d\n", main_num);
}

// calculates the final number
int calc_number(const char *file_path) {
  FILE *file = fopen(file_path, "r");

  if (file == NULL) {
    printf("Unable to open file: %s\n", file_path);
    return -1;
  }

  char line[256]; // buffer for each line of the
  int sum = 0;

  // get the first digit and second digit of the line
  // -- and smush them together
  // -- e.g. '7' & '4' --> '74'
  while (fgets(line, sizeof(line), file)) {
    // read through the characters
    size_t chars_on_line = strlen(line);
    printf("Line: %s\n", line);

    for (int i = 0; i <= chars_on_line; i++) {
      printf(" - Character: %c\n", line[i]);
    }
  }
  return 0;
}
