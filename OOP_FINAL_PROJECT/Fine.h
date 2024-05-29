#ifndef __FINE_H
#define __FINE_H
#include "Document.h"
#include "Date.h"
#include "PoliceStation.h"

class Fine : public Document, public PoliceStation
{
	long recipientId;
	string data;
	double price;
	Date PayDue;


public:
	Fine();
	Fine(char* name, int words, long recipientId, string data, double price,Date date,char* stname,string phoneNumber);
	Fine(const Fine& other);
	long getRecipient() const { return recipientId; }
	virtual ~Fine();//father has dynamic field
	void setName(const char* name);
	void setPrice(double nprice) {this->price = nprice;}
	double getPrice() { return price; }
	const Fine& operator=(const Fine& other);
	virtual void show() const;//print to cmd
	virtual int wordsCounter();
	bool operator==(Document& other)const;
	bool operator+=(string str);
	void operator++();// increase the price by one 
	friend ostream& operator<<(ostream& out, const Fine& p);//used for file printing

};
#endif