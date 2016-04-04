
TARGET:=program
CXX:=g++
CXXFLAGS:= --std=c++11 -g -O0 -I.
LDFLAGS:= -lpthread 

HEADERS:= ThreadPool.h TaskSched.h

.PHONY:clean

TARGET:Main.o Master.o ThreadPool.o TaskSched.o TaskQueue.o $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) Main.o ThreadPool.o TaskSched.o TaskQueue.o $(LDFLAGS)

Main.o:Main.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c Main.cpp

ThreadPool.o:ThreadPool.cpp ThreadPool.h
	$(CXX) $(CXXFLAGS) -c ThreadPool.cpp 

TaskSched.o:TaskSched.cpp TaskSched.h ThreadPool.h
	$(CXX) $(CXXFLAGS) -c TaskSched.cpp 

TaskQueue.o:TaskQueue.cpp TaskQueue.h
	$(CXX) $(CXXFLAGS) -c TaskQueue.cpp

Master.o:Master.cpp Master.h
	$(CXX) $(CXXFLAGS) -c Master.cpp

clean:
	rm -rf $(TARGET) *.o

