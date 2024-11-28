CXX = g++
TARGET = adif
OBJS = main.o adif.o

$(TARGET): $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS)

main.o: main.cpp
	$(CXX) -c main.cpp

adif.o: adif.cpp
	$(CXX) -c adif.cpp

clean:
	del -f $(OBJS) adif.exe total.adi