#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

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
bool add_to_struct_list(color_num** list, int arr_length, color_num *item);
void free_obj(color_num *obj);
color_num *text_to_obj(char *str);
int read_txt(const char *file_path);

// main
int main() {
	int test = read_txt(test_path);
	int main = read_txt(main_path);

	// NOTE: testing
	int arr_length = 5;
	color_num **struct_arr = malloc(sizeof(struct_arr) * 5);
	color_num cn = { .num = 10, .color = "green", };
	color_num *p_cn = &cn;
	bool status = add_to_struct_list(struct_arr, arr_length, p_cn);

	printf("Test calculation is %d\n", test);
	printf("Main calculation is %d\n", main);
}

bool add_to_struct_list(color_num** list, int arr_length, color_num *p_item) {
	bool success = false;

	for (int i = 0; i < arr_length; i++) {

		if (list[i] != NULL) {
			continue;
		} else {
			list[i] = p_item;
			success = true;
			printf("added item to list at index %d\n", i);
			break;
		}

		if (i == arr_length - 1) {
			printf("Unable to add to array, array too small.\n");
			return false;
		}
	}
	return success;
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
	char line[256];
	while (fgets(line, sizeof(line), file)) {
		color_num **objs = malloc(sizeof(color_num) * 8);

		int line_length = strlen(line);
		char comma = ',';
		char semicolon = ';';

		// read characters until there is a comma or semicolon
		int obj_starts_at = 0;
		int obj_ends_at = 0;
		for (int i = 0; i < line_length; i++) {
			if (line[i] == comma || line[i] == semicolon) {
				
				obj_ends_at = i;

				char *score_str = malloc(sizeof(char) * 10);
				int str_len = obj_ends_at - obj_starts_at;
				strncpy(score_str, line + obj_starts_at, str_len);
				color_num* new_obj = text_to_obj(score_str);
				free(score_str);


				obj_starts_at = obj_ends_at + 1;
			}
		}

	}

	fclose(file);

	// NOTE: the following is a test object
	// color_num *test = text_to_obj("13 green");
	// return test->num;
}
