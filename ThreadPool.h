
#ifndef __THREAD_POOL_H__
#define __THREAD_POOL_H__

#include <vector>

using namespace std;

class ThreadPool{

public:

	ThreadPool(long size, void *(* start_routine)(void *), void *arg);
	~ThreadPool();
	bool Init();
	bool Spawn();
	bool Shutdown();

private:

	long size;
	vector<pthread_attr_t> v_attr;
	vector<pthread_t> v_tid;

	void * (*start_routine)(void *);
	void * arg;
};

#endif //__THREAD_POOL_H__

