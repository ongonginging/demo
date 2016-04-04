
#include <unistd.h>
#include <iostream>

#include "ThreadManager.h"

ThreadManager::ThreadManager(){
}

ThreadManager::~ThreadManager(){
}

bool ThreadManager::Init(long size){

	bool rv = this->_ThreadPool.Init(size);

	return rv;
}

bool ThreadManager::Start(){

	bool rv = this->_ThreadPool.Start(&this->_Routine, static_cast<void *>(this));

	return rv;
}

bool ThreadManager::Shutdown(){

	bool rv = this->_ThreadPool.Shutdown();

	return rv;
}

void *ThreadManager::_Routine(void *arg){

	void *rv = NULL;

	ThreadManager *worker = static_cast<ThreadManager *>(arg);
	
	while(true){
		sleep(1);
		cout<<"Hello, World!("<<pthread_self()<<")"<<endl;
	}

	return rv;
}

