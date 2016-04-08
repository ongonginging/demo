
#include <unistd.h>
#include <pthread.h>
#include <iostream>

#include "Hello.h"

using namespace std;

Hello::Hello(int i){
	this->i = i;
	//cout<<"Construct Hello "<<this->i<<"."<<endl;
}

Hello::~Hello(){
	//cout<<"Destruct Hello "<<this->i<<"."<<endl;
}

void Hello::Run(){
	//cout<<"Hello, Thread("<<pthread_self()<<")."<<endl;
	usleep(1);
}

