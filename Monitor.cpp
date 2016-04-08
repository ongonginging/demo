
#include <unistd.h>
#include <iostream>

#include "Monitor.h"

using namespace std;

Monitor::Monitor(){
#if DEBUG
	cout<<"Construct Monitor."<<endl;
#endif
}

Monitor::~Monitor(){
#if DEBUG
	cout<<"Destruct Monitor."<<endl;
#endif
}

void Monitor::Run(){
#if DEBUG
	cout<<"Running Monitor"<<std::endl;
#endif
	while(true){
		sleep(1);
#if DEBUG
		cout<<"In loop of Monitor."<<endl;
#endif
	}
}
