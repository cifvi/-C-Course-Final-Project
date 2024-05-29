#include "TrackedLetter.h"
int TrackedLetter::ctr = 55560;


TrackedLetter::TrackedLetter():arrived(false),trackingNum(-1)
{
}

TrackedLetter::TrackedLetter(char* name, int words, long senderId, long recipientId, string data)
	:Letter(name, words,senderId,recipientId, data), arrived(false),trackingNum(ctr++)
{
	changeStatus("Packaging");
}

TrackedLetter::TrackedLetter(char* name, int words, long senderId, long recipientId, string data,int trackNum, bool status,string stracking) 
	:Letter(name, words, senderId, recipientId, data), trackingNum(trackNum)
{
	setArrived(status);
	if (trackNum!=-1)
	changeStatus(stracking);
	else
	changeStatus("Packaging");
}

TrackedLetter::~TrackedLetter()
{
}

void TrackedLetter::setArrived(char a) throw(const char*)
{
	if (a != '0' && a != '1')
		throw ("Insert only\t 1 / 0\n");
	if (a == '0')
		arrived = false;
	else arrived = true;
}

void TrackedLetter::changeStatus(string nextst) throw(const char*)
{
	int size = nextst.size();
	for (int i = 0; i < size; i++)
	{
		if (!((nextst[i] >= 'a' && nextst[i] <= 'z') || (nextst[i] >= 'A' && nextst[i] <= 'Z')))
			if(!(nextst[i]==' '))
			throw ("Status can only contain letters!Please try again:\n");
	}
	status.push_back(nextst);
}

bool TrackedLetter::operator==(Document& other) const
{
	const TrackedLetter* tl = dynamic_cast<const TrackedLetter*>(&other);
	if (tl)
	{
		if (trackingNum == tl->trackingNum)// only if tracking number the same its matter...
			return Letter::operator==((Document&)other);
	}
	return false;
}

void TrackedLetter::show() const
{
	Letter::show();
	cout << ", Is deliverd?: ";
	if (arrived) cout << "true"<<endl;
	else cout << "false"<<endl;
	cout << "Tracking number: " << trackingNum << ", Last location: "; 
	if (!status.empty())
		cout << status.back();
	else cout<<"No tracking info";
}

bool TrackedLetter::father(bool a)
{
	return false;
}

ostream& operator<<(ostream& out, const TrackedLetter& p)
{
	out << (Letter&)p;
	out << " ";
	if (p.arrived) out << "1" ;
	else out << "0" ;
	out << " " << p.trackingNum  << " ";
	if (!p.status.empty())
		out << p.status.back();
	else out << " No tracking info";
	out << ".";
	return out;
}
