#include "Fine.h"

Fine::Fine() :recipientId(0),data("Empty"),price(0), PayDue(Date())
{

}

Fine::~Fine()
{
}

void Fine::setName(const char* name)
{
	Document::setName(name);
}

Fine::Fine(char* name, int words, long recipientId, string data,double price,Date date,char* stname,string phoneNumber)
	: Document(name, words), recipientId(recipientId), data(data),price(price), PayDue(date),PoliceStation(stname,phoneNumber)
	//using 2 fathers constructors
{
}

Fine::Fine(const Fine& other) : Document(other),PoliceStation(other)	//using 2 fathers constructors
{
	*this = other;
}

const Fine& Fine::operator=(const Fine& other)
{
	if (this != &other)
	{
		recipientId = other.recipientId;
		data = other.data;
		price = other.price;
	}
	return *this;
}

void Fine::show() const
{
	Document::PrintField();
	cout << ", data: " << data << ", Price:" << price;
	PoliceStation::show();
}

int Fine::wordsCounter()
{
	if (data.empty())
		return 0;
	int ctr = 0, strSize;
	strSize = data.size();
	for (int i = 0; i <= strSize; i++)
	{
		if (data[i] == ' ' || data[i] == '\0')
			ctr++;
	}
}

bool Fine::operator==(Document& other) const
{
	const Fine* f = dynamic_cast<const Fine*>(&other);
	if (f)
	{
		if (recipientId == f->recipientId &&
			data == f->data&& price==f->price&&
			PayDue==f->PayDue)
			return Document::operator==((Document&)other)
			&&PoliceStation::operator==((PoliceStation&)other);
	}
	return false;
}

bool Fine::operator+=(string str)
{
	if (!str.empty())
	{
		data += str;
		this->setWords(wordsCounter());
		return true;
	}
	return false;
}

void Fine::operator++()
{
	this->price++;
}

ostream& operator<<(ostream& out, const Fine& p)
{
	out << p.recipientId <<" " ;
	out << (Document&)p;
	out << " " << p.data <<", " << p.price<< " " << p.PayDue;
	out << (PoliceStation&)p;
	return out;
}
