CC = g++
SRC = src
INCLUDE = -I$(SRC)
CFLAGS = -Wall -std=c++11

OBJS = main.o $(SRC)/String.o

all: test

test: $(OBJS)
	$(CC) $(OBJS) -o test $(CFLAGS)

main.o: main.cpp
	$(CC) -c main.cpp -o main.o $(INCLUDE) $(CFLAGS)

$(SRC)/String.o: $(SRC)/String.cpp
	$(CC) -c $(SRC)/String.cpp -o $(SRC)/String.o $(INCLUDE) $(CFLAGS)

clean:
	rm -f $(OBJS) test

run:
	./test output.txt
