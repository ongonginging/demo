
#include <deque>
#include <iostream>
#include <semaphore.h>

#include "ITask.h"
#include "TaskQueue.h"

using namespace std;

TaskQueue::TaskQueue(){
	int pshared = 0; /* Semaphore is used within this process only. */
	int count = 0;
	int ret = sem_init(&this->Sem, pshared, count);
	switch(ret){
		case 0:
		{
			cout<<"Initialized semaphore of TaskQueue success."<<endl;
		}
		break;
		case EINVAL:
		{
			cout<<"Error: value exceeds SEM_VALUE_MAX."<<endl;
		}
		break;
		case ENOSYS:
		{
			cout<<"Error: pshared is nonzero, but the system does not support process-shared semaphores (see sem_overview(7))."<<endl;
		}
		break;
		default:
		{
			cout<<"Error: Unknown error happend when initializing semaphore."<<endl;
		}
		break;
	}
}

TaskQueue::~TaskQueue(){
	int ret = sem_destroy(&this->Sem);
	switch(ret){
		case 0:
		{
			cout<<"Destoried semaphore of TaskQueue success."<<endl;
		}
		break;
		case EINVAL:
		{
			cout<<"Error: sem is not a valid semaphore. "<<endl;
		}
		break;
		default:
		{
			cout<<"Error: Unknown error happend when destroying semaphore."<<endl;
		}
		break;
	}
}

bool TaskQueue::Push(ITask *task){
	bool rv = true;
	this->_Queue.push_back(task);
	int ret = sem_post(&this->Sem);
	switch(ret){
		case 0:
		{
			cout<<"Post semaphore of TaskQueue success."<<endl;
		}
		break;
		case EINVAL:
		{
			cout<<"Error: sem is not a valid semaphore."<<endl;
		}
		break;
		case EOVERFLOW:
		{
			cout<<"Error: The maximum allowable value for a semaphore would be exceeded."<<endl;
		}
		break;
		default:
		{
			cout<<"Error: Unknown error happend when posting semaphore."<<endl;
		}
		break;
	}
	return rv;
}

bool TaskQueue::Pop(ITask *&task){
	bool rv = true;
	int ret = sem_wait(&this->Sem);
	if (this->_Queue.empty()){
		cout<<"Error: It should not happen."<<endl;
		rv = false;
		return rv;
	}
	task = this->_Queue.front();
	this->_Queue.pop_front();
	return rv;
}

