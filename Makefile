# Define the compiler and flags
CC = g++
CFLAGS = -Wall -g

# Define the source files
SRCS = $(wildcard */src/*.cc)

# Define the object files
OBJS = $(SRCS:.cc=.o)

# Define the target executable
TARGET = program

all: build

build: $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

clean:
	rm -f $(TARGET) $(OBJS)
