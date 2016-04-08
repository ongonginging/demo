
#ifndef __ITASK_H__
#define __ITASK_H__

class ITask{
public:
	ITask(){};
	virtual ~ITask(){};
	virtual void Run(void) = 0;
};

#endif //__ITASK_H__

