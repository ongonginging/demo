
TARGET:=program
CXX:=g++
CXXFLAGS:= --std=c++11 -g -O2
LDFLAGS:= -lpthread 

.PHONY:clean

TARGET:main.o
	$(CXX) $(CXXFLAGS) -o $(TARGET) main.o $(LDFLAGS)

main.o:main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

clean:
	rm -rf $(TARGET) *.o

