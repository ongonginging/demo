
#include <unistd.h>
#include <pthread.h>
#include <iostream>

#include "Hello.h"

using namespace std;

Hello::Hello(int i){
	this->i = i;
#if DEBUG
	cout<<"Construct Hello "<<this->i<<"."<<endl;
#endif
}

Hello::~Hello(){
#if DEBUG
	cout<<"Destruct Hello "<<this->i<<"."<<endl;
#endif
}

void Hello::Run(){
#if DEBUG
	cout<<"Hello, Thread("<<pthread_self()<<")."<<endl;
#endif
	usleep(1);
}

