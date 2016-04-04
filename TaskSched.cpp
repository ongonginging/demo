
#include <unistd.h>
#include <iostream>

#include "TaskSched.h"

TaskSched::TaskSched(){
}

TaskSched::~TaskSched(){
}

bool TaskSched::Init(long size){

	bool rv = this->_ThreadPool.Init(size);

	return rv;
}

bool TaskSched::Start(){

	bool rv = this->_ThreadPool.Start(&this->_Routine, static_cast<void *>(this));

	return rv;
}

bool TaskSched::Shutdown(){

	bool rv = this->_ThreadPool.Shutdown();

	return rv;
}

void *TaskSched::_Routine(void *arg){

	void *rv = NULL;

	TaskSched *worker = static_cast<TaskSched *>(arg);
	
	while(true){
		sleep(1);
		cout<<"Hello, World!("<<pthread_self()<<")"<<endl;
	}

	return rv;
}

