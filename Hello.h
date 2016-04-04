
#ifndef __HELLO_H__
#define __HELLO_H__

#include "ITask.h"

class Hello: public ITask{
public:
	Hello();
	virtual ~Hello();
	virtual void Run();
};

#endif //__HELLO_H__
