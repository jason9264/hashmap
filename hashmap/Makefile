# Compiler and compiler flags
CC = gcc
CFLAGS = -Wall -std=c99 -g

# Target executable name
TARGET = driver

# Source files
SRCS = driver.o input.o

# Object files derived from source files
OBJS = $(SRCS:.c=.o)

# Default target
all: $(TARGET)

# Rule to compile source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to link object files and create the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

# Clean rule to remove object files and the executable
clean:
	rm -f $(OBJS) $(TARGET)

