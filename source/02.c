#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// constants and structs
const char *test_path = "./source/02/test.txt";
const char *main_path = "./source/02/main.txt";

const int num_red = 12;
const int num_green = 13;
const int num_blue = 14;

typedef struct {
	int num;
	char *color;
} color_num;

// function signatures
void free_obj(color_num *obj);
color_num *text_to_obj(char *str);
int read_txt(const char *file_path);

// main
int main() {
	int test = read_txt(test_path);
	int main = read_txt(main_path);

	printf("Test calculation is %d\n", test);
	printf("Main calculation is %d\n", main);
}

// function definitions
void free_obj(color_num *obj) {
	free(obj->color);
	free(obj);
}

color_num *text_to_obj(char *str) {
	color_num *obj = malloc(sizeof(color_num));
	char number[3];

	// i.e. 3 green, number then color
	int num_digits = 0;
	char second_digit = str[1];
	if (isdigit(second_digit)) {
		num_digits = 2;
		strncpy(number, str, num_digits); // two digits
	} else {
		num_digits = 1;
		strncpy(number, str, num_digits); // one digit
	}

	int color_starts_at = num_digits + 1;
	char *color = malloc(10 * sizeof(char));
	strncpy(color, str + color_starts_at, (sizeof(str) - color_starts_at) + 1);
	obj->color = color;
	// printf("color is %s\n", color);
	return obj;
}

int read_txt(const char *file_path) {
	
	FILE *file = fopen(file_path, "r");
	if (file == NULL) {
		printf("Unable to open file: %s\n", file_path);
		return -1;
	}

	int games_sum = 0;

	// NOTE: the following is a test object
	color_num *test = text_to_obj("13 green");
	return test->num;
}
