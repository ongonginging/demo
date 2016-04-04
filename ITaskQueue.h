
#ifndef __ITASKQUEUE_H__
#define __ITASKQUEUE_H__

#include "ITask.h"

class ITaskQueue{
public:
	ITaskQueue(){};
	virtual ~ITaskQueue(){};
	virtual bool Push(ITask *task) = 0;
	virtual bool Pop(ITask *&task) = 0;
};

#endif //__ITASKQUEUE_H__
