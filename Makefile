INCLUDE_DIRS := ./include
INCLUDES := $(foreach dir, $(INCLUDE_DIRS), -I$(dir))
CFLAGS := -Wpedantic -Wall -Wextra -fno-common -Wconversion -flto -O3
CC := gcc
OBJ_DIR := objs

VPATH = tests:src/vectors:src/short_string

src_to_objs = $(foreach file, $(notdir $(1:.c=.o)), $(2)/$(file))

TEST_SRCS := src/vectors/vector.c src/short_string/short_string.c
TEST_OBJS := $(call src_to_objs, $(TEST_SRCS), $(OBJ_DIR))

BENCHMARK_SRCS := src/vectors/vector.c
BENCHMARK_OBJS := $(call src_to_objs, $(BENCHMARK_SRCS), $(OBJ_DIR))

.PHONY: clean

benchmark: $(BENCHMARK_OBJS)
	$(CC) tests/benchmark.c -o $@ $^ $(CFLAGS) $(INCLUDES)

test: $(TEST_OBJS)
	$(CC) tests/test.c -o $@ $^ $(CFLAGS) $(INCLUDES)

$(OBJ_DIR)/%.o: %.c %.h
	$(CC) -c $< -o $@ $(CFLAGS) $(INCLUDES)

$(OBJ_DIR)/%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS) $(INCLUDES)

generate_vectors: 
	python3 ./script/generate_vectors.py ./script/mapping.txt ./include/vector_autogen.h

clean:
	rm $(OBJ_DIR)/* test benchmark
