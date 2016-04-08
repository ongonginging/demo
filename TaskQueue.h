
#ifndef __TASK_QUEUE_H__
#define __TASK_QUEUE_H__

#include <deque>
#include <semaphore.h>
#include <pthread.h>

#include "ITask.h"
#include "ITaskQueue.h"

using namespace std;

class TaskQueue:public ITaskQueue{

public:
	TaskQueue();
	virtual ~TaskQueue();

	virtual bool Push(ITask *task);
	virtual bool Pop(ITask *&task);

private:
	sem_t S; 
	pthread_mutex_t M;
	pthread_mutexattr_t MAttr;
	deque<ITask*> Q;
};

#endif //__TASK_QUEUE_H__

