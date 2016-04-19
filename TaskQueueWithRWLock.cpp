
#include <deque>
#include <iostream>
#include <semaphore.h>
#include <pthread.h>

#include "ITask.h"
#include "TaskQueueWithRWLock.h"

using namespace std;

TaskQueueWithRWLock::TaskQueueWithRWLock(){
	int pshared = 0; /* saphore is used within this process only. */
	int value = 0;
	int ret = pthread_rwlockattr_init(&this->RWLAttr);
	switch(ret){
		case 0:
		{
#if DEBUG
			cout<<"Initialized mutex lock of TaskQueue success."<<endl;
#endif
		}
		break;
		case ENOMEM:
		{
			cout<<"Error: do not have enough memory."<<endl;
		}
		break;
		default:
		{
			cout<<"Error: Unknown error happend when initializing semaphore."<<endl;
		}
		break;
	
	}
	ret = pthread_rwlock_init(&this->RWLock, &this->RWLAttr);
	switch(ret){
		case 0:
		{
#if DEBUG
			cout<<"Initialized semaphore of TaskQueue success."<<endl;
#endif
		}
		break;
		case EINVAL:
		{
			cout<<"Error: value exceeds SEM_VALUE_MAX."<<endl;
		}
		break;
		default:
		{
			cout<<"Error: Unknown error happend when initializing semaphore."<<endl;
		}
		break;
	}
}

TaskQueueWithRWLock::~TaskQueueWithRWLock(){
	pthread_rwlock_destroy(&this->RWLock);
	pthread_rwlockattr_destroy(&this->RWLAttr);
}

bool TaskQueueWithRWLock::Push(ITask *task){
	bool rv = true;
	pthread_rwlock_wrlock(&this->RWLock);
	this->Q.push_back(task);
	pthread_rwlock_unlock(&this->RWLock);
	return rv;
}

bool TaskQueueWithRWLock::Pop(ITask *&task){
	bool rv = true;
	pthread_rwlock_rdlock(&this->RWLock);
	if (this->Q.empty()){
		cout<<"Warning: thundering??"<<endl;
		rv = false;
		return rv;
	}
	task = this->Q.front();
	this->Q.pop_front();
	pthread_rwlock_unlock(&this->RWLock);
	return rv;
}

