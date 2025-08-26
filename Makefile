CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2 -Iinclude
LIBS = -lSDL2

SRC_DIR = src
OBJ_DIR = obj

# SRC = main.c player.c map.c renderer.c
SRC = $(wildcard $(SRC_DIR)/*.c)
# OBJ = $(SRC:.c=.o)

OBJ = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))

TARGET = platformer

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)