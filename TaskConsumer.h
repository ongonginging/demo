
#ifndef __TASK_CONSUMER_H__
#define __TASK_CONSUMER_H__

#include "ITask.h"
#include "ThreadPool.h"
#include "ITaskQueue.h"

class TaskConsumer{

public:
	TaskConsumer(ITaskQueue *pTaskQueue);
	virtual ~TaskConsumer();

	bool Init(long size);
	bool Start();
	bool Shutdown();
	bool Recv(ITask *&task);

private:
	class RoutineArg{
	};

	static void *_Routine(void *);
	RoutineArg _RoutineArg;

	long size;
	ThreadPool _ThreadPool;

	ITaskQueue *pTaskQueue;
};

#endif //__TASK_CONSUMER_H__

