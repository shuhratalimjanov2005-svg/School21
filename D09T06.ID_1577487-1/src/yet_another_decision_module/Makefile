CC=gcc
CFLAGS=-Wall -Wextra -Werror
LIB_DIR=../data_libs
BUILD_DIR=../../build

all: decision

decision:
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) yet_another_decision_module_entry.c decision.c $(LIB_DIR)/data_io.c $(LIB_DIR)/data_stat.c -o $(BUILD_DIR)/Quest_2 -lm

clean:
	rm -rf $(BUILD_DIR)/Quest_2

rebuild: clean all
