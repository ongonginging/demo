
TARGET:=program
CXX:=g++
CXXFLAGS:= -std=gnu++0x -g -O0 -I.
LDFLAGS:= -lpthread 

HEADERS:= Monitor.h TaskQueue.h ThreadPool.h TaskConsumer.h TaskProducer.h Hello.h

.PHONY:clean

TARGET:Main.o Hello.o Monitor.o ThreadPool.o TaskConsumer.o TaskProducer.o TaskQueue.o TaskQueueWithRWLock.o $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) Main.o Hello.o Monitor.o ThreadPool.o TaskProducer.o TaskConsumer.o TaskQueue.o TaskQueueWithRWLock.o $(LDFLAGS)

Main.o:Main.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c Main.cpp

ThreadPool.o:ThreadPool.cpp ThreadPool.h
	$(CXX) $(CXXFLAGS) -c ThreadPool.cpp 

TaskConsumer.o:TaskConsumer.cpp TaskConsumer.h 
	$(CXX) $(CXXFLAGS) -c TaskConsumer.cpp 

TaskProducer.o:TaskProducer.cpp TaskProducer.h 
	$(CXX) $(CXXFLAGS) -c TaskProducer.cpp 

TaskQueue.o:TaskQueue.cpp TaskQueue.h
	$(CXX) $(CXXFLAGS) -c TaskQueue.cpp

TaskQueueWithRWLock.o:TaskQueueWithRWLock.cpp TaskQueueWithRWLock.h
	$(CXX) $(CXXFLAGS) -c TaskQueueWithRWLock.cpp

Monitor.o:Monitor.cpp Monitor.h
	$(CXX) $(CXXFLAGS) -c Monitor.cpp

Hello.o:Hello.cpp Hello.h
	$(CXX) $(CXXFLAGS) -c Hello.cpp

clean:
	rm -rf $(TARGET) *.o

