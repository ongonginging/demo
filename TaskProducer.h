
#ifndef __TASK_PRODUCER_H__
#define __TASK_PRODUCER_H__

#include "ITask.h"
#include "ITaskQueue.h"

class TaskProducer{

public:
	TaskProducer(ITaskQueue *pTaskQueue);
	virtual ~TaskProducer();

	bool Send(ITask *task);
private:
	ITaskQueue *pTaskQueue;
};

#endif //__TASK_PRODUCER_H__
