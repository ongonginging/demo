
#include <iostream>
#include <pthread.h>

#include "Hello.h"

using namespace std;

Hello::Hello(){
	cout<<"Construct Hello."<<endl;
}

Hello::~Hello(){
	cout<<"Destruct Hello."<<endl;
}

void Hello::Run(){
	cout<<"Hello, Thread("<<pthread_self()<<")"<<endl;
}

