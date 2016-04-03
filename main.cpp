
#include<map>
#include<vector>
#include<iostream>

#include<pthread.h>
#include<unistd.h>

using namespace std;

void *arg = NULL;

void *start_routine(void *arg){
	while(true){
		cout<<"Hello, World("<<pthread_self()<<")!"<<endl;
		sleep(1);
	}
	pthread_exit(0);
}

bool init_thread(pthread_attr_t &attr){
	bool rv = true;
	pthread_attr_init(&attr);
	return rv;
}

bool start_thread(pthread_t& tid, pthread_attr_t& pthread_attr, void *(*start_routine)(void *), void *arg){

	bool rv = true;
	void *status = NULL;

	int ret = pthread_create(&tid, &pthread_attr, start_routine, arg);
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

bool stop_thread(pthread_t &tid, pthread_attr_t &attr){
	pthread_cancel(tid);
	pthread_attr_destroy(&attr);
}

struct thread_pool{
	thread_pool(long size){
		this->size = size;
		for(int i=0; i<size; i++){
			pthread_attr_t attr;
			this->v_attr.push_back(attr);
			this->v_tid.push_back(-1);
		}
	};
	~thread_pool(){
	};
	long size;
	std::vector<pthread_attr_t> v_attr;
	std::vector<pthread_t> v_tid;
};

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
		rv = start_thread(tid, attr, start_routine, arg);
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

int main(int argc, char **argv){

#if 0
	pthread_t tid;
	pthread_attr_t attr;

	init_thread(attr);
	start_thread(tid, attr, start_routine, arg);
	
	int n = 3;
	while(n-->0){
		sleep(2);
	}
	if(tid != 0){
		stop_thread(tid, attr);
	}
#else

	bool ret = true;

	long size = sysconf(_SC_NPROCESSORS_ONLN);
	struct thread_pool p(size);
	std::cout<<"online thread supported: "<<p.size<<std::endl;

	ret = init_thread_pool(p);
	if (!ret){
		return -1;
	}

	ret = start_thread_pool(p);
	if (!ret){
		stop_thread_pool(p);
		return -1;
	}

	int n = 3;
	while(n-->0){
		sleep(2);
	}
	stop_thread_pool(p);
#endif
	return 0;
}

