#include "Date.h"

Date::Date(int day, const char* month, int year)
{
	setDate(day, month, year);
}

Date::Date() :Date(01, "01", 1990)
{
}

Date::~Date()
{
	delete month;
	month = NULL;
}

Date::Date(const Date& other) // copied date is legal
{
	*this = other;
}

const Date& Date::operator=(const Date& other)
{
	if (this != &other)
	{
		setMonth(other.getMonth());
		this->day = other.day;
		this->year = other.year;
	}
	return *this;

}

void Date::setDate(int day, const char* month, int year)
{
	setYear(year);
	setMonth(month);
	if(atoi(month)==2)
	setDay(day,29);
	else
	setDay(day, 30);


	
}

void Date::setDay(int day,int max_day) throw(const char*) //throw exeption
{
	if ((day >= 1) && (day <= max_day))
	{
		this->day=day;
	}
	else
	throw ("Error, you entered illegal day");
	
}

void Date::setMonth(const char* month) throw(const char*)//throw exeption
{
	int temp = atoi(month); 
	if (strlen(month) < 3 &&(temp >= 1) && (temp <= 12))
	{
		this->month = new char[strlen(month) + 1];
		//לבדוק הקצאה?
		strcpy(this->month, month);
	}
	else
	{
		this->month = NULL;
		throw ("Error, you entered illegal month");
	}
}

void Date::setYear(int year) throw(const char*) //throw exeption
{
	if (year >= 0)//positive num 
	this->year = year;

	else 
		throw ("Error, you entered illegal year");
}

bool Date::operator>(const Date& other) const
{
	if (this->year > other.year)
		return true;
	else if (this->year < other.year)
		return false;
	else//the year is equal!
	{
		int tmpmonth1=atoi(this->month), tmpmonth2=atoi(other.month);
		if (tmpmonth1 > tmpmonth2)
			return true;
		else if (tmpmonth1 < tmpmonth2)
			return false;
		else//the month is equal!
		{
			if (this->day > other.day)
				return true;
			return false;
		}
	}
}

bool Date::operator==(const Date& other) const
{
	return (this->day==other.day && this->year==other.year && atoi(this->month)==atoi(other.month));
}



ostream& operator<<(ostream& out, const Date& p)
{
	out <<"("<< p.day << " " << p.month << " " << p.year<<")";
return out;
}

istream& operator>>(istream& in, Date& p)
{
	bool flag = false;
	while (!flag)
	{
		cout << "please insert date (dd mm yyyy)" << endl;
		int day, year;
		char month[3];
		in >> day >> month >> year;
		try { p.setDate(day, month, year); }
		catch (const char* str) { cout << str << endl; continue; }
		flag = true;
	}
	return in;
}
