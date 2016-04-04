
#ifndef __HELLO_H__
#define __HELLO_H__

#include "ITask.h"

class Hello: public ITask{
public:
	Hello(int i);
	virtual ~Hello();
	virtual void Run();
private:
	int i;
};

#endif //__HELLO_H__

