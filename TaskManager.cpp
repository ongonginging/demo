
#include <iostream>
#include <semaphore.h>

#include "ITask.h"
#include "TaskManager.h"

using namespace std;

TaskManager::TaskManager(){
	int pshared = 0; /* Semaphore is used within this process only. */
	int count = 0;
	int ret = sem_init(&this->Sem, pshared, count);
	switch(ret){
		case 0:
		{
			cout<<"Initialized semaphore of TaskManager success."<<endl;
		}
		break;
		case EINVAL:
		{
			cout<<"value exceeds SEM_VALUE_MAX."<<endl;
		}
		break;
		case ENOSYS:
		{
			cout<<"pshared is nonzero, but the system does not support process-shared semaphores (see sem_overview(7))."<<endl;
		}
		break;
		default:
		{
			cout<<"Unknown error happend when initializing semaphore."<<endl;
		}
		break;
	}
}

TaskManager::~TaskManager(){
	int ret = sem_destroy(&this->Sem);
	switch(ret){
		case 0:
		{
			cout<<"Destoried semaphore of TaskManager success."<<endl;
		}
		break;
		case EINVAL:
		{
			cout<<"sem is not a valid semaphore. "<<endl;
		}
		break;
		default:
		{
			cout<<"Unknown error happend when destroying semaphore."<<endl;
		}
		break;
	}
}

bool TaskManager::PushTask(ITask &task){
	bool rv = true;
	this->QTask.push_back(task);
	int ret = sem_post(&this->Sem);
	switch(ret){
		case 0:
		{
			cout<<"Post semaphore of TaskManager success."<<endl;
		}
		break;
		case EINVAL:
		{
			cout<<"sem is not a valid semaphore."<<endl;
		}
		break;
		case EOVERFLOW:
		{
			cout<<"The maximum allowable value for a semaphore would be exceeded."<<endl;
		}
		break;
		default:
		{
			cout<<"Unknown error happend when posting semaphore."<<endl;
		}
		break;
	}
	return rv;
}

bool TaskManager::PopTask(ITask &task){
	bool rv = true;
	int ret = sem_wait(&this->Sem);
	if (this->QTask.empty()){
		rv = false;
		return rv;
	}
	task = this->QTask.front();
	this->QTask.pop_front();
	return rv;
}

