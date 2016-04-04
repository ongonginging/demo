
#include <unistd.h>
#include <iostream>

#include "Monitor.h"

using namespace std;

Monitor::Monitor(){
	cout<<"Construct Monitor."<<endl;
}

Monitor::~Monitor(){
	cout<<"Destruct Monitor."<<endl;
}

void Monitor::Run(){
	cout<<"Running Monitor"<<std::endl;
	while(true){
		sleep(1);
		cout<<"In loop of Monitor."<<endl;
	}
}
