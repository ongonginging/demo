
#ifndef __WORKER_H__
#define __WORKER_H__

#include "ThreadPool.h"

class Worker{

public:

	Worker();
	~Worker();

private:

	long size;
	struct ThreadPool _ThreadPool;
};

#endif //__WORKER_H__
