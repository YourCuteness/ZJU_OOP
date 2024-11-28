CC = g++
CFLAG = -std=c++11
SRC = .
OD = ..
ADDOBJ = $(SRC)/pdadd.o			#	object file for pdadd
LISTOBJ = $(SRC)/pdlist.o		#	object file for pdlist
REMOVEOBJ = $(SRC)/pdremove.o	#	object file for pdremove
SHOWOBJ = $(SRC)/pdshow.o		#	object file for pdshow

all: $(OD)/pdadd $(OD)/pdlist $(OD)/pdremove $(OD)/pdshow

$(OD)/pdadd: $(ADDOBJ)
	$(CC) $(CFLAG) -o $(OD)/pdadd $(ADDOBJ)

$(OD)/pdlist: $(LISTOBJ)
	$(CC) $(CFLAG) -o $(OD)/pdlist $(LISTOBJ)

$(OD)/pdremove: $(REMOVEOBJ)
	$(CC) $(CFLAG) -o $(OD)/pdremove $(REMOVEOBJ)

$(OD)/pdshow: $(SHOWOBJ)
	$(CC) $(CFLAG) -o $(OD)/pdshow $(SHOWOBJ)	

.cpp.o:
	$(CC) $(CFLAG) -c $< -o $@

clean:
	rm -f $(ADDOBJ) $(LISTOBJ) $(REMOVEOBJ) $(SHOWOBJ) $(OD)/pdadd $(OD)/pdlist $(OD)/pdremove $(OD)/pdshow
