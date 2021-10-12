INCLUDE_DIRS := ./include
INCLUDES := $(foreach dir, $(INCLUDE_DIRS), -I$(dir))
USR_DEFS ?= 
USR_DEFS += #-DGENERATE_VECTOR_FUNCTIONS_INLINE
CFLAGS := -std=c17 -Wpedantic -Wall -Wextra -fno-common -Wconversion -flto -O3 $(USR_DEFS)
CPPFLAGS := -std=c++2a -Wpedantic -Wall -Wextra -fno-common -Wconversion -flto -O3 $(USR_DEFS)
 
CC := gcc
CXX := g++
OBJ_DIR := objs
TARGETS := benchmark test benchmark_cpp


VPATH = tests:src/vectors:src/short_string

src_to_objs = $(foreach file, $(notdir $(1:.c=.o)), $(2)/$(file))

TEST_SRCS := src/vectors/vector.c src/vectors/vector_autogen.c src/short_string/short_string.c
TEST_OBJS := $(call src_to_objs, $(TEST_SRCS), $(OBJ_DIR))

BENCHMARK_SRCS := src/vectors/vector.c src/vectors/vector_autogen.c
BENCHMARK_OBJS := $(call src_to_objs, $(BENCHMARK_SRCS), $(OBJ_DIR))

SIEVE_SRCS := src/vectors/vector.c src/vectors/vector_autogen.c
SIEVE_OBJS := $(call src_to_objs, $(SIEVE_SRCS), $(OBJ_DIR))


.PHONY: clean generate_vectors test

all: $(TARGETS)

benchmark: tests/benchmark.c $(BENCHMARK_OBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(INCLUDES)

test: tests/test.c $(TEST_OBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(INCLUDES)

benchmark_cpp:
	$(CXX) tests/benchmark.cpp -o benchmark_cpp $(CPPFLAGS)

sieve: tests/sieve.c $(SIEVE_OBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(INCLUDES)

$(OBJ_DIR)/%.o: %.c %.h | $(OBJ_DIR)
	$(CC) -c $< -o $@ $(CFLAGS) $(INCLUDES)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) -c $< -o $@ $(CFLAGS) $(INCLUDES)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

./src/vectors/vector_autogen.c: ./script/mapping.txt
	make generate_vectors

./include/vector_autogen.h: ./script/mapping.txt
	make generate_vectors

generate_vectors: ./script/mapping.txt
	python3 ./script/generate_vectors.py \
		./script/mapping.txt \
		./include/vector_autogen.h \
		./src/vectors/vector_autogen.c > /dev/null

run_test: #CFLAGS = -g -O0
run_test: test 
	./test && valgrind ./test && scan-build make test

clean:
	rm -rf $(OBJ_DIR)/* test benchmark benchmark_cpp
