
#include <unistd.h>
#include <iostream>

#include "ThreadPool.h"

using namespace std;

void *arg = NULL;

void *start_routine(void *arg){
	while(true){
		cout<<"Hello, World("<<pthread_self()<<")!"<<endl;
		sleep(1);
	}
	pthread_exit(0);
}

int main(int argc, char **argv){

	bool ret = true;

	long size = sysconf(_SC_NPROCESSORS_ONLN);
	cout<<"number of workers: "<<size<<endl;

	ThreadPool p;

	ret = p.Init(size, start_routine, arg);
	if (!ret){
		return -1;
	}

	ret = p.Start();
	if (!ret){
		p.Shutdown();
		return -1;
	}

	int n = 3;
	while(n-->0){
		sleep(2);
	}
	p.Shutdown();

	return 0;
}

