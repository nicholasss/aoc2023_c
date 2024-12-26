#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

// constants and structs
const char *test_path = "/Users/nicholas/Developer/aoc2023_c/source/02/test.txt";
const char *main_path = "/Users/nicholas/Developer/aoc2023_c/source/02/main.txt";

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
	// printf("'%s'", str);

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
	obj->num = atoi(number);

	int color_starts_at = num_digits + 1;
	char *color = malloc(10 * sizeof(char));
	strncpy(color, str + color_starts_at, (sizeof(str) - color_starts_at) + 1);
	obj->color = color;
	// printf(" should be %d %s\n", obj->num, obj->color);
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

		int objs_list_size = 32;
		color_num **objs = malloc(sizeof(color_num) * objs_list_size);

		int line_length = (int)strlen(line); // reconverted from unsigned long to int
		int obj_starts_at = 0;
		int obj_ends_at = 0;

		// read characters until there is a comma or semicolon
		for (int i = 0; i < line_length; i++) {
			// finds the first color-num after 'game x:'
			if (line[i] == ':') {
				// printf("%c ---\n", line[i]);
				obj_starts_at = i + 1;
			}

			// finds the end of the character and uses it
			if (line[i] == comma || line[i] == semicolon) {
				obj_ends_at = i;

				char *score_str = malloc(sizeof(char) * 16);
				int str_len = obj_ends_at - obj_starts_at - 1;
				strncpy(score_str, line + obj_starts_at + 1, str_len);

				// printf("'%s'\n", score_str);

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
		int invalid_game = false;
		for (int i = 0; i < objs_list_size; i++) {
			// invalid obj pointer
			if (objs[i] == NULL) {
				continue;
			}

			char *color = objs[i]->color; // this line causes segfault -- why?
			int num = objs[i]->num;

			// printf("game #%d -- %s : %d",game_num, color, num);

			if (strcmp(color, "red") == 0) {
				if (num > num_red) {
					invalid_game = true;
					// printf(" <-- invalid");
					// printf("too many of red- %d\n", num);
				}
			} else if (strcmp(color, "blue") == 0) {
				if (num > num_blue) {
					invalid_game = true;
					// printf(" <-- invalid");
					// printf("too many of blue- %d\n", num);
				}
			} else if (strcmp(color, "green") == 0) {
				if (num > num_green) {
					invalid_game = true;
					// printf(" <-- invalid");
					// printf("too many of green- %d\n", num);
				}
			}
			// printf("\n");
		}

		if (invalid_game == true) {
			invalid_game = false; // reset invalid game
			// printf("game %d is not going to be added\n\n", game_num);
			continue; // go to the next line in the test
		} else {
			// printf("%d + %d", game_num, sum);
			sum += game_num;
			// printf(" = %d\n", sum);
		}

		// freeing resources
		// this should free all of the objs within this list
		free_obj_list(objs, objs_list_size);
	}

	fclose(file);
	return sum;
}
