
#include <unistd.h>
#include <iostream>

#include "Worker.h"

using namespace std;

int main(int argc, char **argv){

	bool ret = true;

	long size = sysconf(_SC_NPROCESSORS_ONLN);
	cout<<"number of WorkerManagers: "<<size<<endl;

	Worker WorkerManager;

	ret = WorkerManager.Init(size);
	if (!ret){
		return -1;
	}

	ret = WorkerManager.Start();
	if (!ret){
		WorkerManager.Shutdown();
		return -1;
	}

	int n = 3;
	while(n-->0){
		sleep(2);
	}

	WorkerManager.Shutdown();

	return 0;
}

