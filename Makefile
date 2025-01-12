# Compiler and flags
CC = gcc
CFLAGS = -I/home/moss/vcpkg/installed/x64-linux/include -Wall -O2
LDFLAGS = -L/home/moss/vcpkg/installed/x64-linux/lib -lraylib -lglfw3 -lm -lpthread -ldl

# Source and output
SRC = main.c
OUT = build/program

# Default target
all: $(OUT)

# Build the executable
$(OUT): $(SRC)
	$(CC) -o $(OUT) $(SRC) $(CFLAGS) $(LDFLAGS)

# Clean the build
clean:
	rm -f $(OUT)

