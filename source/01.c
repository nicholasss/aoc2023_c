#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

typedef struct {
	char number;
	int start_pos;
} num_obj;

// function signatures
void free_obj(num_obj *obj);
num_obj *make_obj(int start_pos, char number);
num_obj **read_line(char *line);
int read_txt(const char *file_path);
num_obj *string_to_num(int start_pos, char *str);

// enum nums{one, two ,three, four, five, six, seven, eight, nine};

// main function
int main() {

	const char *test_file = "./source/01/test.txt";
	const char *main_file = "./source/01/main.txt";

	int test_num = read_txt(test_file);
	int main_num = read_txt(main_file);

	printf("Test calculation is %d\n", test_num);
	printf("Main calculation is %d\n", main_num);
}

void free_obj(num_obj *obj) {
	free(obj);
}

num_obj *make_obj(int start_pos, char number) {
	num_obj *new_obj = malloc(sizeof(num_obj));
	if (new_obj == NULL) {
		printf("Unable to allocate memory for new object\n");
		return NULL;
	}

	new_obj->start_pos = start_pos;
	new_obj->number = number;
	return new_obj;
};

// function definitions
num_obj *string_to_num(int start_pos, char *str) {
	if (strcmp(str, "one") == 0) {
		return make_obj(start_pos, '1');
	} else if (strcmp(str, "two") == 0) {
		return make_obj(start_pos, '2');
	} else if (strcmp(str, "three") == 0) {
		return make_obj(start_pos, '3');
	} else if (strcmp(str, "four") == 0) {
		return make_obj(start_pos,'4');
	} else if (strcmp(str, "five") == 0) {
		return make_obj(start_pos, '5');
	} else if (strcmp(str, "six") == 0) {
		return make_obj(start_pos, '6');
	} else if (strcmp(str, "seven") == 0) {
		return make_obj(start_pos, '7');
	} else if (strcmp(str, "eight") == 0) {
		return make_obj(start_pos, '8');
	} else if (strcmp(str, "nine") == 0) {
		return make_obj(start_pos, '9');
	} else {
		printf("Unable to identify the following number: %s\n", str); 
		return NULL;
	}
}

num_obj **read_line(char *line) {
	// returns two num_objs
	num_obj *first_digit;
	num_obj *first_spelled;
	num_obj *second_digit;
	num_obj *second_spelled;
	int line_len = (int)strlen(line);

	// first letter
	// find both first letter and first number then return both
	for (int i = 0; i < line_len; i++) {
		if (isalpha(line[i])) {
			char *buffer = malloc(sizeof(char) * 10);

			for (int j = i; j < line_len; j++) {
				strncpy(buffer, line + i, i - j);
				if (isdigit(line[j])) {
					break;
				}

				first_spelled = string_to_num(i, buffer);

				if (first_spelled != NULL) {
				
				}
			}
		}
	}

}

int read_txt(const char *file_path) {
	char *numbers[] = {
		"zero",
		"one",
		"two",
		"three",
		"four",
		"five",
		"six",
		"seven",
		"eight",
		"nine"
	};

	FILE *file = fopen(file_path, "r");

	if (file == NULL) {
		printf("Unable to open file: %s\n", file_path);
		return -1;
	}

	char line[256]; // buffer for each line of the 
	int sum = 0;

	// TODO: add spelled out digits
	while(fgets(line, sizeof(line), file)) {
		num_obj *first; 
		num_obj *second;

		int line_len = (int)strlen(line);

		// get first digit number
		for (int i = 0; i < line_len; i++) {
			char nchar = line[i];
			if (isdigit(nchar)) {
				first = nchar;
				break;
			}
		}

		// check 5 letters for spelled number
		char letters[6];
		for (int i = 0; i < 5; i++) {
			letters[i] = line[i];
			// first = string_to_num(letters);
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

		// check for the last letters

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
