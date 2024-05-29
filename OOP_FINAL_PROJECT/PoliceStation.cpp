#include "PoliceStation.h"

PoliceStation::PoliceStation(): phoneNumber("100")
{
	this->setName("Israel Police");
}

PoliceStation::PoliceStation(char* name, string phoneNumber) : phoneNumber(phoneNumber)
{
	this->setName(name);

}

PoliceStation::PoliceStation(const PoliceStation& ps)
{
	*this = ps;
}

PoliceStation::~PoliceStation()
{
	delete name;
	name = NULL;
}

const PoliceStation& PoliceStation::operator=(const PoliceStation& other)
{
	if (this != &other)
	{
		this->phoneNumber = other.phoneNumber;
		setName(other.name);
	}
	return *this;
}

void PoliceStation::setName(const char* name)
{
	if (name)
	{
		this->name = new char[strlen(name) + 1];
		strcpy(this->name, name);
	}
	else this->name = NULL;
}

bool PoliceStation::operator==(const PoliceStation& other) const
{
	
	return (!strcmp(name, other.name) && phoneNumber == other.phoneNumber);
}

void PoliceStation::show() const
{
	cout << ", Police station: " << name << ", Phone mumber: " << phoneNumber;
}

ostream& operator<<(ostream& out, const PoliceStation& p)
{
	out << " " << p.name << " " << p.phoneNumber;
	return out;
}

istream& operator>>(istream& in, PoliceStation& p)
{
	cout << "Please insert police station name: " << endl;
	char stname[MAX_SIZE];
	fseek(stdin, 0, SEEK_SET);
	cin.getline(stname,MAX_SIZE);
	p.setName(stname);
	cout << "Please insert police station phone number: " << endl;
	string phone;
	fseek(stdin, 0, SEEK_SET);
	cin >> phone;
	return in;
}
