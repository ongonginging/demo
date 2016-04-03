
TARGET:=program
CXX:=g++
CXXFLAGS:= --std=c++11 -g -O0 -I.
LDFLAGS:= -lpthread 

.PHONY:clean

TARGET:main.o ThreadPool.o Worker.o
	$(CXX) $(CXXFLAGS) -o $(TARGET) main.o ThreadPool.o $(LDFLAGS)

main.o:main.cpp ThreadPool.h
	$(CXX) $(CXXFLAGS) -c main.cpp

ThreadPool.o:ThreadPool.cpp ThreadPool.h
	$(CXX) $(CXXFLAGS) -c ThreadPool.cpp 

Worker.o:Worker.cpp Worker.h
	$(CXX) $(CXXFLAGS) -c Worker.cpp 

clean:
	rm -rf $(TARGET) *.o
