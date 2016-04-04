
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
	cout<<"Monitor"<<std::endl;
}
