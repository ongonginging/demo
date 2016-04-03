
#include <vector>
#include <iostream>

#include <pthread.h>

#include "ThreadPool.h"

using namespace std;


#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#define handle_error_en(en, msg) \
        do { errno = en; perror(msg); exit(EXIT_FAILURE); } while (0)

static void
display_pthread_attr(pthread_attr_t *attr, char *prefix)
{
    int s, i;
    size_t v;
    void *stkaddr;
    struct sched_param sp;

    s = pthread_attr_getdetachstate(attr, &i);
    if (s != 0)
        handle_error_en(s, "pthread_attr_getdetachstate");
    printf("%sDetach state        = %s\n", prefix,
            (i == PTHREAD_CREATE_DETACHED) ? "PTHREAD_CREATE_DETACHED" :
            (i == PTHREAD_CREATE_JOINABLE) ? "PTHREAD_CREATE_JOINABLE" :
            "???");

    s = pthread_attr_getscope(attr, &i);
    if (s != 0)
        handle_error_en(s, "pthread_attr_getscope");
    printf("%sScope               = %s\n", prefix,
            (i == PTHREAD_SCOPE_SYSTEM)  ? "PTHREAD_SCOPE_SYSTEM" :
            (i == PTHREAD_SCOPE_PROCESS) ? "PTHREAD_SCOPE_PROCESS" :
            "???");

    s = pthread_attr_getinheritsched(attr, &i);
    if (s != 0)
        handle_error_en(s, "pthread_attr_getinheritsched");
    printf("%sInherit scheduler   = %s\n", prefix,
            (i == PTHREAD_INHERIT_SCHED)  ? "PTHREAD_INHERIT_SCHED" :
            (i == PTHREAD_EXPLICIT_SCHED) ? "PTHREAD_EXPLICIT_SCHED" :
            "???");

    s = pthread_attr_getschedpolicy(attr, &i);
    if (s != 0)
        handle_error_en(s, "pthread_attr_getschedpolicy");
    printf("%sScheduling policy   = %s\n", prefix,
            (i == SCHED_OTHER) ? "SCHED_OTHER" :
            (i == SCHED_FIFO)  ? "SCHED_FIFO" :
            (i == SCHED_RR)    ? "SCHED_RR" :
            "???");

    s = pthread_attr_getschedparam(attr, &sp);
    if (s != 0)
        handle_error_en(s, "pthread_attr_getschedparam");
    printf("%sScheduling priority = %d\n", prefix, sp.sched_priority);

    s = pthread_attr_getguardsize(attr, &v);
    if (s != 0)
        handle_error_en(s, "pthread_attr_getguardsize");
    printf("%sGuard size          = %lu bytes\n", prefix, v);

    s = pthread_attr_getstack(attr, &stkaddr, &v);
    if (s != 0)
        handle_error_en(s, "pthread_attr_getstack");
    printf("%sStack address       = %p\n", prefix, stkaddr);
    printf("%sStack size          = 0x%lx bytes\n", prefix, v);
}

static bool 
init_thread(pthread_attr_t &attr){
	bool rv = true;
	pthread_attr_init(&attr);
	return rv;
}

static bool 
spawn_thread(pthread_t& tid, pthread_attr_t& attr, void *(*start_routine)(void *), void *arg){

	bool rv = true;
	void *status = NULL;


#if 1
	/* 设置线程属性 */
	int stack_size = 2097152;//2M
	void *sp;
	int s;

	s = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
        if (s != 0)
        	handle_error_en(s, "pthread_attr_setdetachstate");

        s = pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);
        if (s != 0)
        	handle_error_en(s, "pthread_attr_setinheritsched");

        s = posix_memalign(&sp, sysconf(_SC_PAGESIZE), stack_size);
        if (s != 0)
        	handle_error_en(s, "posix_memalign");

        printf("posix_memalign() allocated at %p\n", sp);

        s = pthread_attr_setstack(&attr, sp, stack_size);
        if (s != 0)
        	handle_error_en(s, "pthread_attr_setstack");
#endif


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

#if 0
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
#endif
#if 0
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

static bool 
free_thread(pthread_t &tid, pthread_attr_t &attr){
	pthread_cancel(tid);
	pthread_attr_destroy(&attr);
}

ThreadPool::ThreadPool(){
	std::cout<<"Contruct ThreadPool."<<std::endl;
};

ThreadPool::~ThreadPool(){
	std::cout<<"Destruct ThreadPool."<<std::endl;
};

bool 
ThreadPool::Init(long size, void *(* start_routine)(void *), void *arg){

	bool rv = true;

	this->size = size;
	for(int i=0; i<size; i++){
		pthread_attr_t attr;
		this->v_attr.push_back(attr);
		this->v_tid.push_back(-1);
	}
	this->start_routine = start_routine;
	this->arg = arg;

	for (int i=0; i<this->size; i++){
		pthread_attr_init(&this->v_attr[i]);
	}

	return rv;
}

bool 
ThreadPool::Start(){
	
	bool rv = true;
	
	for(int i=0; i<this->size; i++){
		pthread_attr_t &attr = this->v_attr[i];
		pthread_t &tid = this->v_tid[i];
		rv = spawn_thread(tid, attr, this->start_routine, this->arg);
		if (!rv) {
			break;
		}
		display_pthread_attr(&attr, (char *)"\t");
	}

	return rv;
}

bool 
ThreadPool::Shutdown(){

	bool rv = true;

	for (int i=0; i<this->size; i++){
		pthread_attr_t &attr = this->v_attr[i];
		pthread_t &tid = this->v_tid[i];
		if (tid > 0){
			free_thread(tid, attr);
		}
	}

	return rv;
}

