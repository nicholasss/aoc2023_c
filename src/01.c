#include <stdbool.h>
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
  // int sum = 0;

  // reading through each of the lines
  // -- get the first digit and second digit of the line
  // -- and smush them together
  // -- e.g. '7' & '4' --> '74'
  while (fgets(line, sizeof(line), file)) {
    size_t chars_on_line = strlen(line) - 1;
    printf("Line: %s", line); // includes \n

    // for use after completed reading line
    bool found_first_number = false;
    int first_ascii = 0;

    // for tracking what the last number was
    int previous_ascii = 0;

    // reading through the characters on each line
    for (size_t i = 0; i < chars_on_line; i++) {
      // printf(" - Character: %c Number: %s\n", line[i],
      //        char_is_number(line[i]) ? "true" : "false");

      if (!char_is_number(line[i])) {
        continue;
      } else if (char_is_number(line[i]) && !found_first_number) {
        first_ascii = line[i];
        found_first_number = true;
      }

      previous_ascii = line[i];
    }
    // after reading line, set the last number on line
    int last_ascii = previous_ascii;

    printf(" - first number: %c, second number: %c\n", first_ascii, last_ascii);
  }

  return 0;
}

bool char_is_number(char ascii_char) {
  if (ascii_char >= 48 && ascii_char < 58) {
    return true;
  }
  return false;
}
