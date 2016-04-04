
#include <unistd.h>
#include <iostream>

#include "TaskSched.h"

using namespace std;

int main(int argc, char **argv){

	bool ret = true;

	long size = sysconf(_SC_NPROCESSORS_ONLN);
	cout<<"number of TaskScheds: "<<size<<endl;

	TaskSched TaskSched;

	ret = TaskSched.Init(size);
	if (!ret){
		return -1;
	}

	ret = TaskSched.Start();
	if (!ret){
		TaskSched.Shutdown();
		return -1;
	}

	int n = 3;
	while(n-->0){
		sleep(2);
	}
	TaskSched.Shutdown();

	return 0;
}

