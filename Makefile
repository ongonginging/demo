
TARGET:=program
CXX:=g++
CXXFLAGS:= --std=c++11 -g -O0 -I.
LDFLAGS:= -lpthread 

.PHONY:clean

TARGET:main.o thread_pool.o
	$(CXX) $(CXXFLAGS) -o $(TARGET) main.o thread_pool.o $(LDFLAGS)

main.o:main.cpp thread_pool.h
	$(CXX) $(CXXFLAGS) -c main.cpp

thread_pool.o:thread_pool.cpp thread_pool.h
	$(CXX) $(CXXFLAGS) -c thread_pool.cpp 

clean:
	rm -rf $(TARGET) *.o
