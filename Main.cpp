
#include <unistd.h>
#include <iostream>

#include "TaskQueue.h"
#include "TaskProducer.h"
#include "TaskConsumer.h"
#include "Monitor.h"
#include "Hello.h"

using namespace std;

int main(int argc, char **argv){

	bool ret = true;

	TaskQueue* q = new TaskQueue();

	TaskConsumer consumer((ITaskQueue *)q);
	TaskProducer producer((ITaskQueue *)q);

	long size = sysconf(_SC_NPROCESSORS_ONLN);
	cout<<"number of TaskConsumers: "<<size<<endl;

	ret = consumer.Init(size);
	if (!ret){
		return -1;
	}

	ret = consumer.Start();
	if (!ret){
		consumer.Shutdown();
		return -1;
	}

	for(int i=0; i<20; i++){
		producer.Send(new Hello(i));
	}

	Monitor monitor;
	monitor.Run();

	consumer.Shutdown();

	delete q;

	return 0;
}

