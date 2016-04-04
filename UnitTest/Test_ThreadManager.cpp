
#include <unistd.h>
#include <iostream>

#include "ThreadManager.h"

using namespace std;

int main(int argc, char **argv){

	bool ret = true;

	long size = sysconf(_SC_NPROCESSORS_ONLN);
	cout<<"number of ThreadManagers: "<<size<<endl;

	ThreadManager ThreadManager;

	ret = ThreadManager.Init(size);
	if (!ret){
		return -1;
	}

	ret = ThreadManager.Start();
	if (!ret){
		ThreadManager.Shutdown();
		return -1;
	}

	int n = 3;
	while(n-->0){
		sleep(2);
	}
	ThreadManager.Shutdown();

	return 0;
}

