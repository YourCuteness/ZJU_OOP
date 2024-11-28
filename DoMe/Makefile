CC = g++
AR = ar
CFLAG = -std=c++11 -I.
SRC=.
OD = ..
OBJS = $(OD)/main.o $(SRC)/database.o $(SRC)/item.o $(SRC)/cd.o $(SRC)/dvd.o	# put your object files here

$(OD)/main: $(OBJS)
	$(CC) $(CFLAG) -o $@ $^

.cpp.o:
	$(CC) $(CFLAG) -c $< -o $@

clean:
	rm -f $(OBJS) $(OD)/main
