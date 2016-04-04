
#include <iostream>

#include "ITaskQueue.h"
#include "TaskProducer.h"

using namespace std;

TaskProducer::TaskProducer(ITaskQueue *pTaskQueue){
	cout<<"Construct TaskProducer."<<endl;
	this->pTaskQueue = pTaskQueue;
}

TaskProducer::~TaskProducer(){
	cout<<"Destruct TaskProducer."<<endl;
}

bool TaskProducer::Send(ITask *task){
	bool rv = this->pTaskQueue->Push(task);
	return rv;
}

