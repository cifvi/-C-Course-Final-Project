#define _CRT_SECURE_NO_WARNINGS
#ifndef _DATE_H_
#define _DATE_H_
#define CURRENT_YEAR 2022
#include <iostream>
#include <string>
using namespace std;
class Date
{
protected:
	int day;
	char* month;
	int year;
public:
	Date(int day, const char* month, int year = CURRENT_YEAR);
	Date();
	Date(const Date& other);
	~Date();
	const Date& operator=(const Date& other);
	void setDate(int day, const char* month, int year);
	void setDay(int day, int max_day) throw(const char*);//throw exeption
	void setMonth(const char* month) throw(const char*);//throw exeption
	void setYear(int year) throw(const char*);//throw exeption
	friend ostream& operator<<(ostream& out, const Date& p);
	friend istream& operator>>(istream& in, Date& p);
	int getDay() const { return day; }
	char* getMonth() const { return month; }
	int getYear() const { return year; }
	bool operator>(const Date& other) const;
	bool operator== (const Date& other) const;
};
#endif