CC = g++
CFLAG = -I.
PROG_NAME = autocorrect

SRC_DIR = ./src
BIN_DIR  = ./bin
SRC_LIST = $(wildcard $(SRC_DIR)/*.cpp)
INC_LIST = $(wildcard $(SRC_DIR)/*.h)

all: $(PROG_NAME)

$(PROG_NAME): $(SRC_LIST) $(INC_LIST)
	$(CC)	$(SRC_DIR)/autocorrect.cpp	-o $(BIN_DIR)/$(PROG_NAME) $(CFLAG)

clean:
	rm -f $(BIN_DIR)/$(PROG_NAME)
