
TARGET:=program
CXX:=g++
CXXFLAGS:= --std=c++11 -g -O0 -I.
LDFLAGS:= -lpthread 

HEADERS:= Master.h TaskQueue.h ThreadPool.h TaskConsumer.h

.PHONY:clean

TARGET:Main.o Master.o ThreadPool.o TaskConsumer.o TaskQueue.o $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) Main.o ThreadPool.o TaskConsumer.o TaskQueue.o $(LDFLAGS)

Main.o:Main.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c Main.cpp

ThreadPool.o:ThreadPool.cpp ThreadPool.h
	$(CXX) $(CXXFLAGS) -c ThreadPool.cpp 

TaskConsumer.o:TaskConsumer.cpp TaskConsumer.h 
	$(CXX) $(CXXFLAGS) -c TaskConsumer.cpp 

TaskQueue.o:TaskQueue.cpp TaskQueue.h
	$(CXX) $(CXXFLAGS) -c TaskQueue.cpp

Master.o:Master.cpp Master.h
	$(CXX) $(CXXFLAGS) -c Master.cpp

clean:
	rm -rf $(TARGET) *.o

