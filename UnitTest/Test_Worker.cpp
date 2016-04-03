
#include <unistd.h>
#include <iostream>

#include "Worker.h"

using namespace std;

int main(int argc, char **argv){

	bool ret = true;

	long size = sysconf(_SC_NPROCESSORS_ONLN);
	cout<<"number of workers: "<<size<<endl;

	Worker worker;

	ret = worker.Init(size);
	if (!ret){
		return -1;
	}

	ret = worker.Start();
	if (!ret){
		worker.Shutdown();
		return -1;
	}

	int n = 3;
	while(n-->0){
		sleep(2);
	}
	worker.Shutdown();

	return 0;
}

