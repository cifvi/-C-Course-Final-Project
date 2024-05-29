#include "Person.h"

Person::Person(): FirstName("Empty"),LastName("Empty"),BirthDay(Date()),idNum(0)
{
}

Person::Person(string FirstName, string LastName, long idNum, Date BirthDay) :FirstName(FirstName), LastName(LastName), idNum(idNum) ,BirthDay(BirthDay)
{
}

Person::Person(const Person& other)
{
	*this = other;
}

void Person::refreshFine()
{
	vector<Document*>::iterator itr = docArray.begin();
	int size = docArray.size();
	for (int i = 0; i < size; i++)
	{
		Fine* ptr = dynamic_cast<Fine*>(*itr);
		if (ptr)
		{
			if (ptr->getPrice() == 0);
			{
			delete* itr;
			docArray.erase(itr);
			docArray.shrink_to_fit();
			size = docArray.size();
			i = 0;
			itr = docArray.begin();
			}
		}
	}
}

bool Person::operator==(const Person& other) const
{
	return (FirstName==other.FirstName && LastName==other.LastName &&idNum==other.idNum &&docArray==other.docArray && BirthDay==other.BirthDay);
}

bool Person::operator+=(Document* doc) //check legal doc for our system
{ 
	Fine* ptrF = dynamic_cast<Fine*>(doc);
	if (ptrF)
	{ 
		docArray.push_back(ptrF);
		return true;
	}

	Letter* ptrL = dynamic_cast<Letter*>(doc);
	 if(ptrL)
	 {	
			docArray.push_back(ptrL);
			return true;
	 }
	 TrackedLetter* ptrTL = dynamic_cast<TrackedLetter*>(doc);
	 if (ptrTL)
	 {
		 docArray.push_back(ptrTL);
		 return true;
	 }
		return false;
}

Person::~Person() // will be eliminated in DeleteData function
{
}

const Person& Person::operator=(const Person& other)
{
	this->clearDoc();
	this->docArray = other.docArray;
	this->FirstName = other.FirstName;
	this->LastName = other.LastName;
	this->idNum = other.idNum;
	this->BirthDay = other.BirthDay;
	
	return *this;
}

void Person::clearDoc()
{
	vector<Document*>::iterator itrBeg = docArray.begin();
	vector<Document*>::iterator itrEnd = docArray.end();
	for (; itrBeg != itrEnd; itrBeg++)
	{
		delete* itrBeg;
		*itrBeg = NULL;
	}
	this->docArray.resize(0);
	this->docArray.shrink_to_fit();
}

void Person::show() const
{
	cout << "Id number: " << idNum << ", First name: " << FirstName << ", Last name: " << LastName << ", Amout of docs:  " << docArray.size() << ", Birth date: " << BirthDay;
}


ostream& operator<<(ostream& out, const Person& p)
{
	out  << p.idNum << " " << p.FirstName << " " << p.LastName<<" " << p.docArray.size()<< " "<<p.BirthDay;
	return out;
}