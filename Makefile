# Define variables for compiler, flags, and sources
CC = gcc
CFLAGS = -Wall -Wextra
LIBS = -lcurl -lcjson
TARGET = github-activity
SOURCES = main.c cli.c
OBJ = $(SOURCES:.c=.o)

# Default target
all: $(TARGET)

# Rule to build the target
$(TARGET): $(OBJ)
	$(CC) -o $@ $(OBJ) $(LIBS)

# Rule to compile source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule to remove compiled files
clean:
	rm -f $(OBJ)

# Phony targets
.PHONY: all clean
