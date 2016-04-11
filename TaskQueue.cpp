
#include <deque>
#include <iostream>
#include <semaphore.h>
#include <pthread.h>

#include "ITask.h"
#include "TaskQueue.h"

using namespace std;

TaskQueue::TaskQueue(){
	int pshared = 0; /* saphore is used within this process only. */
	int value = 0;
	this->M = PTHREAD_MUTEX_INITIALIZER;
	int ret = pthread_mutex_init(&this->M, &this->MAttr);
	switch(ret){
		case 0:
		{
#if DEBUG
			cout<<"Initialized mutex lock of TaskQueue success."<<endl;
#endif
		}
		break;
		case EINVAL:
		{
			cout<<"Error: value exceeds SEM_VALUE_MAX."<<endl;
		}
		break;
		case EBUSY:
		{
			cout<<"Error:."<<endl;
		}
		break;
		case EFAULT:
		{
			cout<<"Error:."<<endl;
		}
		break;
		default:
		{
			cout<<"Error: Unknown error happend when initializing semaphore."<<endl;
		}
		break;
	
	}
	ret = sem_init(&this->S, pshared, value);
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
	int ret = sem_destroy(&this->S);
	switch(ret){
		case 0:
		{
#if DEBUG
			cout<<"Destoried semaphore of TaskQueue success."<<endl;
#endif
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
	//pthread_mutex_lock(&this->M);/* 单点写入可以不加锁 */
	this->Q.push_back(task);
	//pthread_mutex_unlock(&this->M);
	int ret = sem_post(&this->S);
	switch(ret){
		case 0:
		{
#if DEBUG
			cout<<"Post semaphore success."<<endl;
#endif
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
	int ret = sem_wait(&this->S);
	if (this->Q.empty()){
		cout<<"Error: It should not happen."<<endl;
		rv = false;
		return rv;
	}
	pthread_mutex_lock(&this->M);
	task = this->Q.front();
	this->Q.pop_front();
	pthread_mutex_unlock(&this->M);
	return rv;
}

