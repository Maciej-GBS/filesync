DEPS = -I${PROJECT_ROOT} -I/usr/include/openssl
LDFLAGS = -L${PROJECT_ROOT} -L/usr/lib/x86_64-linux-gnu
LIBS = -lssl -lcrypto
CFLAGS = -Wall -g $(DEPS)

SRCS = $(shell find . -name *.cc)
OBJS = $(SRCS:.cc=.o)

TARGET = program

.PHONY: all
all: build

%.o: %.cc
	$(CXX) $(CFLAGS) -c -o $@ $<

build: $(OBJS)
	$(CXX) $(CFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS) $(LIBS)

clean:
	rm -f $(TARGET) $(OBJS)

