
#ifndef __WORKER_H__
#define __WORKER_H__

#include "ThreadPool.h"

class WorkerManager{

public:
	WorkerManager();
	virtual ~WorkerManager();

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

