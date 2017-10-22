RM = rm -rf

CC=g++

INC_DIR=./include
SRC_DIR=./src
OBJ_DIR=./build
BIN_DIR=./bin
DOC_DIR=./doc

CFLAGS = -pedantic -ansi -std=c++11 -I. -I$(INC_DIR)

.PHONY: all clean distclean doxy

all: vector

debug: CFLAGS += -g -O0
debug: vector

init:
	@mkdir -p $(BIN_DIR)/
	@mkdir -p $(OBJ_DIR)/
	@mkdir -p $(INC_DIR)/
	@mkdir -p $(SRC_DIR)/
	@mkdir -p $(DOC_DIR)/

vector: $(OBJ_DIR)/main.o
	@echo "============="
	@echo "Connecting the target $@"
	@echo "============="
	$(CC) $(CFLAGS) -o $(BIN_DIR)/$@ $^
	@echo "+++ [Executable vector created in $(BIN_DIR)] +++"
	@echo "============="

$(OBJ_DIR)/main.o: $(SRC_DIR)/vector.cpp
	$(CC) -c $(CFLAGS) -o $@ $<

doxy:
	$(RM) $(DOC_DIR)/*
	doxygen Doxyfile

clean:
	$(RM) $(BIN_DIR)/*
	$(RM) $(OBJ_DIR)/*
	$(RM) $(DOC_DIR)/*