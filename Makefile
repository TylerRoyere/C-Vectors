INCLUDE_DIRS := ./include
INCLUDES := $(foreach dir, $(INCLUDE_DIRS), -I$(dir))
USR_DEFS ?= 
USR_DEFS += #-DGENERATE_VECTOR_FUNCTIONS_INLINE
CFLAGS := -Wpedantic -Wall -Wextra -fno-common -Wconversion -flto -O3 $(USR_DEFS)
CC := gcc
OBJ_DIR := objs


VPATH = tests:src/vectors:src/short_string

src_to_objs = $(foreach file, $(notdir $(1:.c=.o)), $(2)/$(file))

TEST_SRCS := src/vectors/vector.c src/vectors/vector_autogen.c src/short_string/short_string.c
TEST_OBJS := $(call src_to_objs, $(TEST_SRCS), $(OBJ_DIR))

BENCHMARK_SRCS := src/vectors/vector.c src/vectors/vector_autogen.c
BENCHMARK_OBJS := $(call src_to_objs, $(BENCHMARK_SRCS), $(OBJ_DIR))

.PHONY: clean generate_vectors

benchmark: $(BENCHMARK_OBJS)
	$(CC) tests/benchmark.c -o $@ $^ $(CFLAGS) $(INCLUDES)

test: $(TEST_OBJS)
	$(CC) tests/test.c -o $@ $^ $(CFLAGS) $(INCLUDES)

benchmark_cpp:
	g++ tests/benchmark.cpp -o benchmark_cpp $(CFLAGS)

$(OBJ_DIR)/%.o: %.c %.h | $(OBJ_DIR)
	$(CC) -c $< -o $@ $(CFLAGS) $(INCLUDES)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) -c $< -o $@ $(CFLAGS) $(INCLUDES)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

./src/vectors/vector_autogen.c: generate_vectors
./include/vector_autogen.h: generate_vectors

generate_vectors: ./script/mapping.txt
	python3 ./script/generate_vectors.py \
		./script/mapping.txt \
		./include/vector_autogen.h \
		./src/vectors/vector_autogen.c > /dev/null

clean:
	rm $(OBJ_DIR)/* test benchmark benchmark_cpp
