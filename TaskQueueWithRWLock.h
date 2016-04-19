
#ifndef __TASK_QUEUE_WITH_RWLOCK_H__
#define __TASK_QUEUE_WITH_RWLOCK_H__

#include <deque>
#include <pthread.h>

#include "ITask.h"
#include "ITaskQueue.h"

using namespace std;

class TaskQueueWithRWLock:public ITaskQueue{

public:
	TaskQueueWithRWLock();
	virtual ~TaskQueueWithRWLock();

	virtual bool Push(ITask *task);
	virtual bool Pop(ITask *&task);

private:
	pthread_rwlockattr_t RWLAttr;
	pthread_rwlock_t RWLock;
	deque<ITask*> Q;
};

#endif //__TASK_QUEUE_WITH_RWLOCK_H__

