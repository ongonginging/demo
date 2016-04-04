
#include <unistd.h>
#include <iostream>

#include "TaskConsumer.h"

using namespace std;

int main(int argc, char **argv){

	bool ret = true;

	long size = sysconf(_SC_NPROCESSORS_ONLN);
	cout<<"number of TaskConsumers: "<<size<<endl;

	TaskConsumer TaskConsumer;

	ret = TaskConsumer.Init(size);
	if (!ret){
		return -1;
	}

	ret = TaskConsumer.Start();
	if (!ret){
		TaskConsumer.Shutdown();
		return -1;
	}

	int n = 3;
	while(n-->0){
		sleep(2);
	}
	TaskConsumer.Shutdown();

	return 0;
}

