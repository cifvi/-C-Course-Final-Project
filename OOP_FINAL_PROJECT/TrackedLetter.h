#ifndef _TRACKED_LETTER_H_
#define _TRACKED_LETTER_H_
#include "Letter.h"
#include <List>
class TrackedLetter :public Letter
{
	bool arrived;
	list<string> status;
	int trackingNum;
	static int ctr;

public:
	TrackedLetter();
	TrackedLetter(char* name, int words, long senderId, long recipientId, string data);
	TrackedLetter(char* name, int words, long senderId, long recipientId, string data,int trackNum,bool status,string stracking);
	~TrackedLetter();//grandfather has dynamic field
	void setArrived(char a)throw(const char*);//throw if char isn't 0/1
	void setArrived(bool b) { arrived = b; }
	bool isArrived() { return arrived; }
	void changeStatus(string nextst) throw(const char*);//update status list
	int getTrackingNum() { return trackingNum; }
	bool operator==(Document& other)const;
	friend ostream& operator<<(ostream& out, const TrackedLetter& p);//used for file printing
	virtual void show() const;//print to cmd
	virtual bool father(bool a = 0); // check if object is father or son 
};
#endif
