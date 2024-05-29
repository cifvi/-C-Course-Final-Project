#define _CRT_SECURE_NO_WARNINGS
#ifndef _POLICE_H_
#define _POLICE_H_
#include <iostream>
#include <string>
using namespace std;
#define MAX_SIZE 256


class PoliceStation
{
	char* name;
	string phoneNumber;

public:
	PoliceStation();
	PoliceStation(char* name, string phoneNumber);
	PoliceStation(const PoliceStation& ps);
	virtual ~PoliceStation();
	void setPhoneNum(string phone) { phoneNumber = phone; }
	string getPhoneNum() { return phoneNumber; }
	const PoliceStation& operator=(const PoliceStation& other);
	void setName(const char* name);
	friend ostream& operator<<(ostream& out, const PoliceStation& p);
	friend istream& operator>>(istream& in, PoliceStation& p);
	bool operator== (const PoliceStation& other) const;
	virtual void show() const;


};
#endif

