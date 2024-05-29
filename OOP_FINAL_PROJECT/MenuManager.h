#ifndef _MENUMANAGER_H_
#define _MENUMANAGER_H_
#include "date.h"
#include "TrackedLetter.h"
#include "Worker.h"
#include <fstream>
#include <typeinfo>


class MenuManager
{
	vector<Person> CustomerArray;
	vector<Worker> WorkersArray;

	template<class Container>
	void addGeneral(Container&c,char type);//template function to add person for array
	void createPerson(long id, Person& p, Worker& w,char tav); // helper for addGeneral
	void AddFine();//to customer
	void TrackUpdate();//considering the exsit status worker can update tracking location throw exception
	void DeleteCostumer();// worker can delet customer from service
	template<class Container>
	void PrintData(Container& c,ostream& out);//helper for <<
	template<class Container>
	void PrintData(Container& c);//print data to cmd
public:

	MenuManager();
	MenuManager(const char* FileName);
	MenuManager(vector<Person> C, vector<Worker> W);
	MenuManager(vector<Worker> W);

	bool ReadFromFile(const char* str); //build the program from file
	bool WriteToFile(const char* str); // export data to file
	void startProgram(); //menu system
	void CustomerMenu(); //helper for startProgram
	void WorkerMenu();//helper for startProgram
	void SendLetter(long sId,int op); // customer can send letter to another
	void createLetter(long rId,long sId,int op,int idx);//helper
	friend ostream& operator<<(ostream& out,  MenuManager& p);
	template <class Container>
	int isExist(Container& c, long id); //check if id exist in array, support template
	void PayFine(int ctr); // customer can pay for a fine
	int Ask4Choice(int tmp1, int tmp2); // helper for user desicion
	template<class Container>
	void PrintPeople(Container& c, ofstream& os); //worker can print customer data, support template
	template<class Container>
	void PrintDocs(Container& c, ofstream& os, const int& docsSize); // helper for file export
	int Jump2Class(ifstream& MyReadFile,char* tmp); // helper for file export
	char* string2char(string str); // convert string to char*
	template<class Type>
	void DocsCounter(Type& t1, int& integer); // count how many docs in array by type
	void DeleteData(); // delete all data 
};

#endif

template<class Container>
inline void MenuManager::addGeneral(Container& c,char type)
{
	long tmpId;
	Person p;
	Worker w;
		cout << "Please insert id number:" << endl;
		cin >> tmpId;
	if (isExist(c, tmpId)==-1)
	{
		switch (type)
		{
		case'w': ////create
			createPerson(tmpId,p, w,type);
			WorkersArray.push_back(w);
			if (isExist(CustomerArray, tmpId) == -1)
			CustomerArray.push_back(p);
			break;

		case'c': ////create
			createPerson(tmpId,p,w,type);
			CustomerArray.push_back(p);
			break;
		}		
	}
	else cout << "Person already exist!" << endl<< "=============================\n";
}

template<class Container>
inline void MenuManager::PrintData(Container& c, ostream& out)
{
	typename Container::iterator itrBeg = c.begin();
	typename Container::iterator itrEnd = c.end();
	if (itrBeg == itrEnd)
		out << "no persons found in data" << endl;
	for (; itrBeg != itrEnd; itrBeg++)
	{
		out << *itrBeg << endl;
	}
	out << endl;
}
template<class Container>
inline void MenuManager::PrintData(Container& c)
{
	int size;
	string name = typeid(*c.begin()).name();
	if (name == "class Person")
	{
		size=CustomerArray.size();
		for (int i = 0; i < size; i++)
		{
			CustomerArray[i].show();
			cout << endl;
		}
		return;
	}
	size = WorkersArray.size();
	for (int i = 0; i < size; i++)
	{
		WorkersArray[i].show();
		cout << endl;
	}
		
	cout << endl;
}

template<class Container>
inline int MenuManager::isExist(Container& c, long id)
{
	typename Container::iterator itr = c.begin();
	typename Container::iterator itrEnd = c.end();
	for (int i=0; itr != itrEnd; i++, itr++)
	{
		if (itr->getId() == id)
			return i;
	}
	return -1;
}

template<class Container>
inline void MenuManager::PrintPeople(Container& c, ofstream& os)
{
	int size = c.size();
	typename Container::iterator itr = c.begin();
	string name = typeid(*c.begin()).name();
	os << typeid(*c.begin()).name()<<"- <"<<size<<"> in system"<<endl;
	os << "Id, First Name, Last Name, Document amount, Birth date" ;
	if (name == "class Worker")
		 os << ", Salary:" << endl;
	else os << ":" << endl;

	for (int i = 0; i < size; itr++, i++)
	{
		os << *itr << endl;
	}
	os << endl;
}
template<class Container>
inline void MenuManager::PrintDocs(Container& c, ofstream& os,const int& docsSize)
{
	vector<Document*> dtmp;
	int docSize;
	vector<Person>::iterator itr=CustomerArray.begin();
	int size = CustomerArray.size();
	Container* ptr;
	string name = typeid(c).name();

	os << name<<"- <" << docsSize << "> in system\nRecipientId, Id number, Name, Words count, Data";
	if (name == "class Letter")
		os << ", SenderId";
		if (name == "class TrackedLetter")
		os << ", SenderId, Is deliverd?, Tracking number,Last location";
		if (name == "class Fine")
		os << ", Price, Payment day, Police station name, Phone number";
	os << ":" << endl;
	for (int i = 0; i < size; itr++, i++)
	{
		dtmp = CustomerArray[i].getDocs();
		docSize = dtmp.size();
		
		for (int k = 0; k < docSize; k++)
		{
			ptr = dynamic_cast<Container*>(dtmp[k]);
			if (ptr)
				os << *ptr << endl;
		}
	}
	os << endl;
}

template<class Type>
inline void MenuManager::DocsCounter(Type& t1, int& integer)
{
	int size = CustomerArray.size();
	for (int k = 0; k < size; k++)
	{
		integer += CustomerArray[k].countDocsByType(t1);
	}
}
	


