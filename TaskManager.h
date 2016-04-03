
#ifndef __TASK_MANAGER_H__
#define __TASK_MANAGER_H__

#include <semaphore.h>
#include <deque>

#include "ITask.h"

class TaskManager{

public:
	TaskManager();
	virtual ~TaskManager();

	bool PushTask(ITask &task);
	bool PopTask(ITask &task);

private:
	sem_t Sem;
	
	deque<ITask> QTask;
};

#endif //__TASK_MANAGER_H__

