
TARGET:=program
CXX:=g++
CXXFLAGS:= --std=c++11 -g -O0 -I.
LDFLAGS:= -lpthread 

.PHONY:clean

TARGET:Main.o ThreadPool.o Worker.o
	$(CXX) $(CXXFLAGS) -o $(TARGET) Main.o ThreadPool.o Worker.o $(LDFLAGS)

Main.o:Main.cpp ThreadPool.h
	$(CXX) $(CXXFLAGS) -c Main.cpp

ThreadPool.o:ThreadPool.cpp ThreadPool.h
	$(CXX) $(CXXFLAGS) -c ThreadPool.cpp 

Worker.o:Worker.cpp Worker.h
	$(CXX) $(CXXFLAGS) -c Worker.cpp 

clean:
	rm -rf $(TARGET) *.o
