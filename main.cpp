
#include <unistd.h>
#include <iostream>

#include "thread_pool.h"

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
	struct thread_pool p(size, start_routine, arg);
	cout<<"number of workers: "<<p.size<<endl;

	ret = init_thread_pool(p);
	if (!ret){
		return -1;
	}

	ret = start_thread_pool(p);
	if (!ret){
		stop_thread_pool(p);
		return -1;
	}

	int n = 3;
	while(n-->0){
		sleep(2);
	}
	stop_thread_pool(p);

	return 0;
}

