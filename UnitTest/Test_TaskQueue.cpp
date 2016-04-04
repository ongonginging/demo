
#include <unistd.h>
#include <iostream>

#include "TaskConsumer.h"
#include "Monitor.h"
#include "Hello.h"

using namespace std;

int main(int argc, char **argv){

	bool ret = true;

	long size = sysconf(_SC_NPROCESSORS_ONLN);
	cout<<"number of TaskConsumers: "<<size<<endl;

	TaskConsumer consumer;

	ret = consumer.Init(size);
	if (!ret){
		return -1;
	}

	ret = consumer.Start();
	if (!ret){
		consumer.Shutdown();
		return -1;
	}

	Monitor monitor;
	consumer.SetTask(new Hello);
	consumer.SetTask(new Hello);
	consumer.SetTask(new Hello);
	consumer.SetTask(new Hello);
	consumer.SetTask(new Hello);
	consumer.SetTask(new Hello);
	consumer.SetTask(new Hello);
	consumer.SetTask(new Hello);
	monitor.Run();

	consumer.Shutdown();

	return 0;
}

