
#include <iostream>

#include "ITaskQueue.h"
#include "TaskProducer.h"

using namespace std;

TaskProducer::TaskProducer(ITaskQueue *pTaskQueue){
#if DEBUG
	cout<<"Construct TaskProducer."<<endl;
#endif
	this->pTaskQueue = pTaskQueue;
}

TaskProducer::~TaskProducer(){
#if DEBUG
	cout<<"Destruct TaskProducer."<<endl;
#endif
}

bool TaskProducer::Send(ITask *task){
	bool rv = this->pTaskQueue->Push(task);
	return rv;
}

