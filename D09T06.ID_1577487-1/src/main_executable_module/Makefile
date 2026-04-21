CC = gcc
CFLAGS = -Wall -Wextra -Werror

AR = $(shell which ar || which llvm-ar)
BUILD_DIR = ../../build
DATA_LIBS_DIR = ../data_libs
DATA_MOD_DIR = ../data_module
DECISION_DIR = ../yet_another_decision_module

SRCS = main_executable_module.c \
       $(DATA_LIBS_DIR)/data_io.c \
       $(DATA_LIBS_DIR)/data_stat.c \
       $(DATA_MOD_DIR)/data_process.c \
       $(DECISION_DIR)/decision.c

all: quest3


quest3: $(BUILD_DIR)/Quest_3

$(BUILD_DIR)/Quest_3:
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(SRCS) -o $(BUILD_DIR)/Quest_3 -lm


data_stat.a:
	$(CC) $(CFLAGS) -c $(DATA_LIBS_DIR)/data_stat.c -o data_stat.o
	$(AR) rcs data_stat.a data_stat.o
	rm data_stat.o

build_with_static: data_stat.a
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) main_executable_module.c \
	$(DATA_MOD_DIR)/data_process.c \
	$(DECISION_DIR)/decision.c \
	$(DATA_LIBS_DIR)/data_io.c \
	data_stat.a -o $(BUILD_DIR)/Quest_4 -lm


data_process.so:
	$(CC) $(CFLAGS) -fPIC -c $(DATA_MOD_DIR)/data_process.c -o data_process.o
	$(CC) -shared -o data_process.so data_process.o $(DATA_LIBS_DIR)/data_stat.c
	rm data_process.o

build_with_dynamic: data_process.so
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -DDYNAMIC main_executable_module.c \
	$(DATA_LIBS_DIR)/data_io.c \
	$(DATA_LIBS_DIR)/data_stat.c \
	$(DECISION_DIR)/decision.c \
	-L. ./data_process.so -o $(BUILD_DIR)/Quest_5 -lm


clean:
	rm -rf $(BUILD_DIR)/* *.a *.o *.so

rebuild: clean all

.PHONY: all clean rebuild build_with_static build_with_dynamic

