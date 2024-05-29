#ifndef _WORKER_H_
#define _WORKER_H_
#include "Person.h"
class Worker : public Person
{
	int empId;
	static int counter;
	float salary;

public:
	Worker();
	Worker(string FirstName, string LastName, long idNum, Date BirthDay,float salary);
	Worker(const Worker& other);
	friend ostream& operator<<(ostream& out, const Worker& w);
	void show() const;


};
#endif