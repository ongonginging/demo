
#ifndef __WORKER_H__
#define __WORKER_H__

#include "ThreadPool.h"

struct worker{
	worker(long size=0){
		this->size = size;
	};
	~worker(){};

	long size;
	struct ThreadPool *pThreadPool;
};

#endif //__WORKER_H__
