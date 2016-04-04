
#include <unistd.h>
#include <iostream>

#include "TaskConsumer.h"
#include "ITask.h"

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

bool TaskConsumer::GetTask(ITask *&task){
	bool rv = this->_TaskQueue.Pop(task);
	return rv;
}

void *TaskConsumer::_Routine(void *arg){

	void *rv = NULL;

	TaskConsumer *consumer = static_cast<TaskConsumer *>(arg);
	
	while(true){
		cout<<"("<<pthread_self()<<")wait semaphore..."<<endl;
		ITask* task = NULL;
		bool ret = consumer->GetTask(task);
		if (ret){
			if (task != NULL){
				task->Run();
			}else{
				cout<<"Task is NULL."<<endl;
			}
		}else{
			cout<<"Failed to get task."<<endl;
		}
	}

	return rv;
}

