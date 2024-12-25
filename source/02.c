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

const char comma = ',';
const char semicolon = ';';

typedef struct {
	int num;
	char *color;
} color_num;

// function signatures
void free_obj_list(color_num** list, int list_length);
bool add_to_struct_list(color_num** list, int arr_length, color_num *item);
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
// free obj
void free_obj(color_num *obj) {
	free(obj->color);
	free(obj);
}

// free object list
void free_obj_list(color_num** list, int list_length) {
	for (int i = 0; i < list_length; i++) {
		if (list[i] != NULL) {
			free_obj(list[i]);
		}
	}
	free(list);
}

// adding to object list
bool add_to_struct_list(color_num** list, int list_length, color_num *p_item) {
	bool success = false;

	for (int i = 0; i < list_length; i++) {

		if (list[i] != NULL) {
			continue;
		} else {
			list[i] = p_item;
			success = true;
			// printf("added item to list at index %d\n", i);
			break;
		}

		if (i == list_length - 1) {
			printf("Unable to add to array, array too small.\n");
			return false;
		}
	}
	return success;
}

// create obj
color_num *text_to_obj(char *str) {
	// printf("string is: '%s'\n", str);

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
	return obj;
}

int read_txt(const char *file_path) {
	
	FILE *file = fopen(file_path, "r");
	if (file == NULL) {
		printf("Unable to open file: %s\n", file_path);
		return -1;
	}

	int sum = 0;
	int game_num = 0;
	char line[256];
	while (fgets(line, sizeof(line), file)) {
		game_num += 1;

		int objs_list_size = 10;
		color_num **objs = malloc(sizeof(color_num) * objs_list_size);

		int line_length = (int)strlen(line); // reconverted from unsigned long to int

		// read characters until there is a comma or semicolon
		int obj_starts_at = 7;
		int obj_ends_at = 0;
		for (int i = 0; i < line_length; i++) {
			if (line[i] == comma || line[i] == semicolon) {
				// ensure that 'Game: ' is not included
				// remove space before number
				
				obj_ends_at = i;

				char *score_str = malloc(sizeof(char) * 10);
				int str_len = obj_ends_at - obj_starts_at;
				strncpy(score_str, line + obj_starts_at + 1, str_len);

				// new_obj is created and can be added to the list
				color_num* new_obj = text_to_obj(score_str);
				free(score_str);

				bool status = add_to_struct_list(objs, objs_list_size, new_obj);
				if (status == false) {
					printf("failed to add to list\n");
					return -1;
				}
				obj_starts_at = obj_ends_at + 1;
			}
		}
		
		// obj list should then be added up to sum but only if its a valid game
		// if invalid game, break to skip to next line;
		for (int i = 0; i < objs_list_size; i++) {
			if (objs[i] == NULL) {
				continue;
			}
			char *color = objs[i]->color; // this line causes segfault -- why?
			int num = objs[i]->num;
			int invalid_game = 0;

			if (strcmp(color, "red") == 0) {
				if (num > num_red) {
					invalid_game = -1;
				}
			} else if (strcmp(color, "blue") == 0) {
				if (num > num_blue) {
					invalid_game = -1;
				}
			} else if (strcmp(color, "green") == 0) {
				if (num > num_green) {
					invalid_game = -1;
				}
			}

			if (invalid_game == -1) {
				break; // go to the next line in the test
			} else {
				sum += game_num;
			}
		}

		// freeing resources
		// this should free all of the objs within this list
		free_obj_list(objs, objs_list_size);
	}

	fclose(file);
	return sum; // just returning zero for fun
}
