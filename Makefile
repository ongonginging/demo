
TARGET:=program
CXX:=g++
CXXFLAGS:= --std=c++11 -g -O0 -I.
LDFLAGS:= -lpthread 

HEADERS:= ThreadPool.h ThreadManager.h

.PHONY:clean

TARGET:Main.o ThreadPool.o ThreadManager.o TaskQueue.o $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) Main.o ThreadPool.o ThreadManager.o TaskQueue.o $(LDFLAGS)

Main.o:Main.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c Main.cpp

ThreadPool.o:ThreadPool.cpp ThreadPool.h
	$(CXX) $(CXXFLAGS) -c ThreadPool.cpp 

ThreadManager.o:ThreadManager.cpp ThreadManager.h ThreadPool.h
	$(CXX) $(CXXFLAGS) -c ThreadManager.cpp 

TaskQueue.o:TaskQueue.cpp TaskQueue.h
	$(CXX) $(CXXFLAGS) -c TaskQueue.cpp

clean:
	rm -rf $(TARGET) *.o

