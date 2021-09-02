CFLAGS := -Wall -Wextra -std=c99 -pedantic -Og -g3

all: xrle
xrle: xrle.o main.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) $(LDLIBS)
