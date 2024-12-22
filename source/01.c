#include <stdio.h>

int main() {

	const char *test_file = "./01/test.txt";
	const char *main_file = "./01/main.txt";

	int test_num = read_txt(test_file);
	int main_num = read_txt(main_file);

	printf("Test calculation is %d", test_num);
	printf("Main calculation is %d", main_num);
}

int read_txt(char *file_path) {
	

}
