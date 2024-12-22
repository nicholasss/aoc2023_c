#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// function signatures
int read_txt(const char *file_path);

// main function
int main() {

	const char *test_file = "./01/test.txt";
	const char *main_file = "./01/main.txt";

	int test_num = read_txt(test_file);
	int main_num = read_txt(main_file);

	printf("Test calculation is %d\n", test_num);
	printf("Main calculation is %d\n", main_num);
}

// function definitions
int read_txt(const char *file_path) {
	
	FILE *file = fopen(file_path, "r");

	if (file == NULL) {
		printf("Unable to open file: %s\n", file_path);
		return -1;
	}

	char line[256]; // buffer for each line of the 
	int sum = 0;

	while(fgets(line, sizeof(line), file)) {
		char first = '\0';
		char second = '\0';
		int line_len = (int)strlen(line);

		// get first number
		for (int i = 0; i < line_len; i++) {
			char nchar = line[i];

			if (isdigit(nchar)) {
				first = nchar;
				break;
			}
		}

		// get second number
		char last_char = line[0];
		for (int i = 0; i < line_len; i++) {
			char curr_char = line[i];

			if (isdigit(curr_char)) {
				last_char = curr_char;
			}
		}
		second = last_char;

		// combine them together #1,#2
		char cnumber[10] = "00";
		cnumber[0] = first;
		cnumber[1] = second;
		int number = atoi(cnumber);

		if (number == 0) {
			printf("Unable to convert %s to integer\n", cnumber);
			return -1;
		}

		// add to sum var
		sum += number;
	}

	fclose(file);

	printf("%d is the sum of the digits.\n", sum);
	return sum;
}
