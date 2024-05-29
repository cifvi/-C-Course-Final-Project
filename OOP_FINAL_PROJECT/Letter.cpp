#include "Letter.h"

Letter::Letter() : senderId(0), recipientId(0), data("Empty")
{
}

Letter::Letter(char* name, int words, long senderId, long recipientId, string data)
	: Document(name, words), senderId(senderId), recipientId(recipientId), data(data)
{
}


Letter::Letter(const Letter& other) : Document(other)
{
	*this = other;
}

Letter::~Letter()
{
}

const Letter& Letter::operator=(const Letter& other)
{
	if (this != &other)
	{
		senderId=other.senderId;
		recipientId = other.recipientId;
		data = other.data;
	}
	return *this;
}

void Letter::show() const
{
	Document::PrintField();
	cout << ", SenderId: " << senderId << ", RecipientId: " << recipientId << ", Data: " << data; 
}

int Letter::wordsCounter()
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
		return ctr;
}

bool Letter::operator==(Document& other) const
{
	const Letter* l = dynamic_cast<const Letter*>(&other);
	if (l)
	{
		if (senderId == l->senderId &&
			recipientId == l->recipientId &&
			data == l->data)
			return Document::operator==((Document&)other);
	}
	return false;

}

bool Letter::father(bool a)
{
	return a;
}

bool Letter::operator+=(string str)
{
	if(!str.empty())
	{
	data += str; 
	this->setWords(wordsCounter());
	return true;
	}
	return false;
}

bool Letter::operator>(Letter& other)
{
	if (this->getWords() > other.getWords())
		return true;

	return false;
}

ostream& operator<<(ostream& out, const Letter& p)
{
	out  << p.recipientId << " ";
	out << (Document&)p;
	out << " " << p.data << ", " << p.senderId;
	return out;
}
