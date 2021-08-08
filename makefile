CC=g++ -std=c++0x
CFLAGS=-Wall -pedantic -Werror -g  -o
MAIN=main.cpp
TESTER=test.o

test: $(MAIN)
	$(CC) $(CFLAGS) $(TESTER) $(MAIN)
all: 

# g++ -Wall -pedantic -g  -Werror test.c