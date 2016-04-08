
#include <sys/time.h>
#include <unistd.h>
#include <iostream>

#include "TaskQueue.h"
#include "TaskProducer.h"
#include "TaskConsumer.h"
#include "Monitor.h"
#include "Hello.h"

using namespace std;

#define TIMES 10000000

int main(int argc, char **argv){

	bool ret = true;

	TaskQueue *q = new TaskQueue();

	TaskConsumer consumer((ITaskQueue *)q);
	TaskProducer producer((ITaskQueue *)q);

	long size = sysconf(_SC_NPROCESSORS_ONLN);
	cout<<"number of consumers: "<<size<<endl;

	ret = consumer.Init(size);
	if (!ret){
		return -1;
	}

	ret = consumer.Start();
	if (!ret){
		consumer.Shutdown();
		return -1;
	}

	cout<<"enter testing ..."<<endl;

	struct timeval t1;
	gettimeofday(&t1, NULL);

	for(int i=0; i<TIMES; i++){
		producer.Send(new Hello(i));
	}

	struct timeval t2;
	gettimeofday(&t2, NULL);

	cout<<"coast: "<<TIMES<<" messages handled in "<<(t2.tv_sec*1000000+t2.tv_usec)-(t1.tv_sec*1000000+t1.tv_usec)<<" Microseconds(微秒)."<<endl;

	cout<<"leave testing ..."<<endl;

	Monitor monitor;
	monitor.Run();

	consumer.Shutdown();

	delete q;

	return 0;
}

