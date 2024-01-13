# Compiler and flags
CC = gcc
CFLAGS = -Wall -O2
LDFLAGS = -lm -lrt

# Executable name
TARGET = GA

# Source files
COMMON_SRC = functions.c OF.c
SRC = GA.c $(COMMON_SRC)

# Object files
OBJ = $(SRC:.c=.o)

# Header file
HEADER = functions.h

# Default target
all: $(TARGET)

# Linking rule
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ) $(LDFLAGS)

# Compilation rule
%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule
clean:
	rm -f $(TARGET) $(OBJ)
