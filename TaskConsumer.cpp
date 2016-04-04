
#include <unistd.h>
#include <iostream>

#include "TaskConsumer.h"

TaskConsumer::TaskConsumer(){
}

TaskConsumer::~TaskConsumer(){
}

bool TaskConsumer::Init(long size){

	bool rv = this->_ThreadPool.Init(size);

	return rv;
}

bool TaskConsumer::Start(){

	bool rv = this->_ThreadPool.Start(&this->_Routine, static_cast<void *>(this));

	return rv;
}

bool TaskConsumer::Shutdown(){

	bool rv = this->_ThreadPool.Shutdown();

	return rv;
}

void *TaskConsumer::_Routine(void *arg){

	void *rv = NULL;

	TaskConsumer *worker = static_cast<TaskConsumer *>(arg);
	
	while(true){
		sleep(1);
		cout<<"Hello, World!("<<pthread_self()<<")"<<endl;
	}

	return rv;
}

