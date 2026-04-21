CC=gcc
CFLAGS=-Wall -Wextra -Werror
BUILD_DIR=../../build

all: data_module

data_module:
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) data_module_entry.c ../data_libs/data_io.c ../data_libs/data_stat.c -o $(BUILD_DIR)/Quest_1

clean:
	rm -rf $(BUILD_DIR)/Quest_1
 data_module:
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) data_module_entry.c data_process.c ../data_libs/data_io.c ../data_libs/data_stat.c -o $(BUILD_DIR)/Quest_1
rebuild: clean all
