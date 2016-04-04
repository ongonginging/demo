
#include <unistd.h>
#include <iostream>

#include "WorkerManager.h"

WorkerManager::WorkerManager(){
}

WorkerManager::~WorkerManager(){
}

bool WorkerManager::Init(long size){

	bool rv = this->_ThreadPool.Init(size);

	return rv;
}

bool WorkerManager::Start(){

	bool rv = this->_ThreadPool.Start(&this->_Routine, static_cast<void *>(this));

	return rv;
}

bool WorkerManager::Shutdown(){

	bool rv = this->_ThreadPool.Shutdown();

	return rv;
}

void *WorkerManager::_Routine(void *arg){

	void *rv = NULL;

	WorkerManager *worker = static_cast<WorkerManager *>(arg);
	
	while(true){
		sleep(1);
		cout<<"Hello, World!("<<pthread_self()<<")"<<endl;
	}

	return rv;
}

