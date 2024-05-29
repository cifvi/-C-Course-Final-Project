#ifndef __LETTER_H
#define __LETTER_H
#include "Document.h"


class Letter : public Document
{
	long senderId;
	long recipientId;
	string data;

public:
	Letter();
	Letter(char* name, int words, long senderId, long recipientId, string data);
	Letter(const Letter& other);
	~Letter();//father has dynamic field
	long getSender() const { return senderId; }
	long getRecipient() const { return recipientId; }	
	const Letter& operator=(const Letter& other);
	virtual void show() const;//print to cmd
	virtual int wordsCounter();
	virtual bool operator==(Document& other)const;
	virtual bool father(bool a = 1);// check if object is father or son 
	bool operator+=(string str);//add data and update word field
	bool operator>(Letter& other);//compare between letters lenght
	friend ostream& operator<<(ostream& out, const Letter& p);//used for file printing
};
#endif