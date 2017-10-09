RM = rm -rf

CC=g++

INC_DIR=./include
SRC_DIR=./src
OBJ_DIR=./build
BIN_DIR=./bin
DOC_DIR=./doc

CFLAGS = -Wall -pedantic -ansi -std=c++11 -I. -I$(INC_DIR)

.PHONY: all clean distclean doxy

all: sort_algorithms

debug: CFLAGS += -g -O0
debug: sort_algorithms

init:
	@mkdir -p $(BIN_DIR)/
	@mkdir -p $(OBJ_DIR)/
	@mkdir -p $(INC_DIR)/
	@mkdir -p $(SRC_DIR)/
	@mkdir -p $(DOC_DIR)/

sort_algorithms: $(OBJ_DIR)/sort_algorithms.o $(OBJ_DIR)/main.o
	@echo "============="
	@echo "Connecting the target $@"
	@echo "============="
	$(CC) $(CFLAGS) -o $(BIN_DIR)/$@ $^
	@echo "+++ [Executable sort_algorithms created in $(BIN_DIR)] +++"
	@echo "============="

$(OBJ_DIR)/sort_algorithms.o: $(SRC_DIR)/sort_algorithms.cpp $(INC_DIR)/sort_algorithms.h
	$(CC) -c $(CFLAGS) -o $@ $<

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.cpp
	$(CC) -c $(CFLAGS) -o $@ $<

doxy:
	$(RM) $(DOC_DIR)/*
	doxygen Doxyfile

clean:
	$(RM) $(BIN_DIR)/*
	$(RM) $(OBJ_DIR)/*
	$(RM) $(DOC_DIR)/*