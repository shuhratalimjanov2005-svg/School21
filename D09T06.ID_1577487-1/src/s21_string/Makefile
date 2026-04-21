CC = gcc
CFLAGS = -Wall -Wextra -Werror
BUILD_DIR = ../../build

all: strlen_tests

strlen_tests:
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) s21_string.c s21_string_test.c -o $(BUILD_DIR)/Quest_6
strcmp_tests:
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) s21_string.c s21_string_test.c -o $(BUILD_DIR)/Quest_7 
strcpy:
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) s21_string.c s21_string_test.c -o $(BUILD_DIR)/Quest_8

strcat:
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) s21_string.c s21_string_test.c -o $(BUILD_DIR)/Quest_9
  
strchr:
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) s21_string.c s21_string_test.c -o $(BUILD_DIR)/Quest_10
strstr:
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) s21_string.c s21_string_test.c -o $(BUILD_DIR)/Quest_11
full_coverage_tests:
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) s21_string.c s21_string_test.c -o $(BUILD_DIR)/Quest_12
text_processor: text_processor.c
	mkdir -p ../../build
	$(CC) $(CFLAGS) text_processor.c -o ../../build/Quest_13

clean:
	rm -rf $(BUILD_DIR)/Quest_6

rebuild: clean all
