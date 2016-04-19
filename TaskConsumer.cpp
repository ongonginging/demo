
#include <unistd.h>
#include <iostream>

#include "ITask.h"
#include "ITaskQueue.h"
#include "TaskConsumer.h"

TaskConsumer::TaskConsumer(ITaskQueue *pTaskQueue){
	this->pTaskQueue = pTaskQueue;
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

bool TaskConsumer::Recv(ITask *&task){
	bool rv = this->pTaskQueue->Pop(task);
	return rv;
}

void *TaskConsumer::_Routine(void *arg){

	void *rv = NULL;
	TaskConsumer *consumer = static_cast<TaskConsumer *>(arg);
	
	ITask* task = NULL;
	while(true){
		bool ret = consumer->Recv(task);
		if (ret){
			if (task != NULL){
				task->Run();
				delete task;
				task = NULL;
			}else{
				cout<<"Task is NULL."<<endl;
			}
		}else{
			cout<<"Failed to get task."<<endl;
		}
	}
	return rv;
}

