
#include "Worker.h"

Worker::Worker(){
}

Worker::~Worker(){
}

bool Worker::Init(long size){

	bool rv = this->_ThreadPool.Init(size, &this->_Routine, static_cast<void *>(this));

	return rv;
}

bool Worker::Start(){

	bool rv = this->_ThreadPool.Start();

	return rv;
}

bool Worker::Shutdown(){

	bool rv = this->_ThreadPool.Shutdown();

	return rv;
}

void *Worker::_Routine(void *arg){

	void *rv = NULL;

	Worker *worker = static_cast<Worker *>(arg);

	return rv;
}
