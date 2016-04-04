
#ifndef __TASK_H__
#define __TASK_H__

class ITask{
public:
	ITask(){};
	virtual ~ITask(){};
	virtual void Run(void) = 0;
};

#endif //__TASK_H__
