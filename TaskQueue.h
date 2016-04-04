
#ifndef __TASK_MANAGER_H__
#define __TASK_MANAGER_H__

#include <deque>
#include <semaphore.h>

#include "ITask.h"

using namespace std;

class TaskQueue{

public:
	TaskQueue();
	virtual ~TaskQueue();

	bool Push(ITask *task);
	bool Pop(ITask *&task);

private:
	sem_t Sem;
	
	deque<ITask*> _Queue;
};

#endif //__TASK_MANAGER_H__

