# Define the compiler and flags
CC = g++
DEPS = -I${PROJECT_ROOT} -I/usr/include/openssl
LDFLAGS = -L${PROJECT_ROOT} -L/usr/lib/x86_64-linux-gnu
LIBS = -lssl -lcrypto
CFLAGS = -Wall -g $(DEPS)

# Define the source files
SRCS = $(wildcard */src/*.cc)

# Define the object files
OBJS = $(SRCS:.cc=.o)

# Define the target executable
TARGET = program

all: build

%.o: %.cc
	$(CC) $(CFLAGS) -c -o $@ $<

build: $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS) $(LIBS)

clean:
	rm -f $(TARGET) $(OBJS)
