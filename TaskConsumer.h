
#ifndef __WORKER_H__
#define __WORKER_H__

#include "ThreadPool.h"

class TaskConsumer{

public:
	TaskConsumer();
	virtual ~TaskConsumer();

	bool Init(long size);
	bool Start();
	bool Shutdown();

private:
	class RoutineArg{
	};

	static void *_Routine(void *);
	RoutineArg _RoutineArg;

	long size;
	struct ThreadPool _ThreadPool;
};

#endif //__WORKER_H__

