# Define the compiler and flags
CC = g++
DEPS = -I/usr/include/openssl -L/usr/lib/x86_64-linux-gnu
LIBS = -lssl -lcrypto
CFLAGS = -Wall -g $(DEPS)

# Define the source files
SRCS = $(wildcard */src/*.cc)

# Define the object files
OBJS = $(SRCS:.cc=.o)

# Define the target executable
TARGET = program

all: build

build: $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

clean:
	rm -f $(TARGET) $(OBJS)
