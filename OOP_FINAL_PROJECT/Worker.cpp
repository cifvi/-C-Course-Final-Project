#include "Worker.h"

int Worker::counter = 0;

Worker::Worker() :salary(0)
{
}

Worker::Worker(string FirstName, string LastName, long idNum, Date BirthDay,float salary)
	:Person(FirstName, LastName,idNum ,BirthDay), salary(salary), empId(++counter)
{
}

Worker::Worker(const Worker& other)
{
	*this = other;
}

void Worker::show() const
{
	Person::show();
	cout << ", Salary: " << salary;


}

ostream& operator<<(ostream& out, const Worker& w)
{
	out << (Person)w <<" "<< w.salary;
	return out;
}
