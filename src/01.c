// #include <ctype.h>
#include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

#include "01.h"

// === definitions

// path constants
const char *test_path = "./src/01/test.txt";
const char *main_path = "./src/01/main.txt";

//
// === main ===
int main() {
  int test_num = calc_number(test_path);
  int main_num = calc_number(main_path);

  printf("Test calculation is %d\n", test_num);
  printf("Main calculation is %d\n", main_num);
}

int calc_number(const char *file_path) {
  FILE *file = fopen(file_path, "r");

  if (file == NULL) {
    printf("Unable to open file: %s\n", file_path);
    return -1;
  }

  char line[256]; // buffer for each line of the
  int sum = 0;

  while (fgets(line, sizeof(line), file)) {
    // look at each line
  }
  return 0;
}
