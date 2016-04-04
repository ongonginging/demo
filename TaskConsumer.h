
#ifndef __WORKER_H__
#define __WORKER_H__

#include "ITask.h"
#include "ThreadPool.h"
#include "TaskQueue.h"

class TaskConsumer{

public:
	TaskConsumer();
	virtual ~TaskConsumer();

	bool Init(long size);
	bool Start();
	bool Shutdown();
	bool GetTask(ITask *&task);
	bool SetTask(ITask *task);

private:
	class RoutineArg{
	};

	static void *_Routine(void *);
	RoutineArg _RoutineArg;

	long size;
	ThreadPool _ThreadPool;

	TaskQueue _TaskQueue;
};

#endif //__WORKER_H__

