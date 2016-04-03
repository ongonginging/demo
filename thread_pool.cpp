
#include <vector>
#include <iostream>

#include <pthread.h>

#include "thread_pool.h"

using namespace std;

static bool init_thread(pthread_attr_t &attr){
	bool rv = true;
	pthread_attr_init(&attr);
	return rv;
}

static bool start_thread(pthread_t& tid, pthread_attr_t& attr, void *(*start_routine)(void *), void *arg){

	bool rv = true;
	void *status = NULL;

	int ret = pthread_create(&tid, &attr, start_routine, arg);
	switch(ret){
		case 0:
		{
			cout<<"Creating thread success, thread id: "<<tid<<"!"<<endl;
		}
		break;
		case EAGAIN:
		{
			cout<<"Insufficient  resources  to  create another thread, or a system-imposed limit on the number of threads was encountered."<<endl;
		}
		break;
		case EINVAL:
		{
			cout<<"Invalid settings in attr."<<endl;
		}
		break;
		case EPERM:
		{
			cout<<"No permission to set the scheduling policy and parameters specified in attr."<<endl;
		}
		break;
		default:
		{
			cout<<"Unknown error happended when creating thread."<<endl;
		}
		break;
	}

	if(0 != ret){
		rv = false;
		goto ext;
	}

#if 1
	/* detach不会阻塞启动线程，线程退出以后自动释放所有资源 */
	ret = pthread_detach(tid);
	switch(ret){
		case 0:
		{
			cout<<"thread id: "<<tid<<" detached success!"<<endl;
		}
		break;
		case EINVAL:
		{
			cout<<"thread is not a joinable thread."<<endl;
		}
		break;
		case ESRCH:
		{
			cout<<"No thread with the ID thread could be found."<<endl;
		}
		break;
		default:
		{
			cout<<"Unknown error happended when join thread"<<tid<<"."<<endl;
		}
		break;
	}
#else
	/* join到启动线程会导致启动线程阻塞 */
	ret = pthread_join(tid, &status);
	switch(ret){
		case 0:
		{
			cout<<"thread id: "<<tid<<" join success!"<<endl;
		}
		break;
		case EDEADLK:
		{
			cout<<"A deadlock was detected (e.g., two threads tried to join with each other); or thread specifies the calling thread."<<endl;
		}
		break;
		case EINVAL:
		{
			cout<<"thread is not a joinable thread."<<endl;
			cout<<"or"<<endl;
			cout<<"Another thread is already waiting to join with this thread."<<endl;
		}
		break;
		case ESRCH:
		{
			cout<<"No thread with the ID thread could be found."<<endl;
		}
		break;
		default:
		{
			cout<<"Unknown error happended when join thread"<<tid<<"."<<endl;
		}
		break;
	}
#endif
	if(0 != ret){
		rv = false;
		goto ext;
	}
ext:
	return rv;
}

static bool stop_thread(pthread_t &tid, pthread_attr_t &attr){
	pthread_cancel(tid);
	pthread_attr_destroy(&attr);
}

bool init_thread_pool(struct thread_pool &p){

	bool rv = true;

	for (int i=0; i<p.size; i++){
		pthread_attr_init(&p.v_attr[i]);
	}

	return rv;
}

bool start_thread_pool(struct thread_pool &p){
	
	bool rv = true;
	
	for(int i=0; i<p.size; i++){
		pthread_attr_t &attr = p.v_attr[i];
		pthread_t &tid = p.v_tid[i];
		rv = start_thread(tid, attr, p.start_routine, p.arg);
		if (!rv) {
			break;
		}
	}

	return rv;
}

bool stop_thread_pool(struct thread_pool &p){

	bool rv = true;

	for (int i=0; i<p.size; i++){
		pthread_attr_t &attr = p.v_attr[i];
		pthread_t &tid = p.v_tid[i];
		if (tid > 0){
			stop_thread(tid, attr);
		}
	}

	return rv;
}

