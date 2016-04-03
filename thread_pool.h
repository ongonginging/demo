
#ifndef __THREAD_POOL_H__
#define __THREAD_POOL_H__

#include <vector>

using namespace std;

struct thread_pool{
	thread_pool(long size, void *(* start_routine)(void *), void *arg){
		std::cout<<"Contruct thread_pool."<<std::endl;
		this->size = size;
		for(int i=0; i<size; i++){
			pthread_attr_t attr;
			this->v_attr.push_back(attr);
			this->v_tid.push_back(-1);
		}
		this->start_routine = start_routine;
		this->arg = arg;
	};
	~thread_pool(){
		std::cout<<"Destruct thread_pool."<<std::endl;
	};
	long size;
	vector<pthread_attr_t> v_attr;
	vector<pthread_t> v_tid;

	void * (*start_routine)(void *);
	void * arg;
};

bool init_thread_pool(struct thread_pool &p);
bool start_thread_pool(struct thread_pool &p);
bool stop_thread_pool(struct thread_pool &p);

#endif //__THREAD_POOL_H__
