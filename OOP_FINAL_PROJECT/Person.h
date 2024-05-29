#ifndef _PERSON_H_
#define _PERSON_H_
#include <string>
#include <vector>
#include "Date.h"
#include "Fine.h"
#include "TrackedLetter.h"


class Person //:public Date
{
	protected:
	string FirstName;
	string LastName;
	Date BirthDay;
	long idNum; 
	vector<Document*> docArray;

public:
	Person();
	Person(string FirstName, string LastName, long idNum,Date BirthDay);
	Person(const Person& other);
	void refreshFine();//exclude "zero" price fines
	friend ostream& operator<<(ostream& out, const Person& p);
	bool operator== (const Person& other) const;
	bool operator+= (Document* doc);//add docs to person array
	~Person();
	const Person& operator=(const Person& other);
	long getId() { return idNum; }
	vector<Document*> getDocs() { return docArray; }
	void clearDoc();//delete all docs array
	template<class Type>
	int countDocsByType(Type& c);//return counter by docs type helper for manager
	void show() const;

};
#endif

template<class Type>
inline int Person::countDocsByType(Type& c)
{
	int size=docArray.size();
	int ctr=0;
	Type* ptr;
	string non_name;
	for (int i = 0; i < size; i++)
	{
		ptr = dynamic_cast<Type*>(docArray[i]);
			if (ptr)
			ctr++;
	}
	return ctr;
}
