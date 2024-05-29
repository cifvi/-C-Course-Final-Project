#ifndef __DOCUMENT_H
#define __DOCUMENT_H
#include <iostream>
using namespace std;
#define MAX_SIZE 256

class Document //abstract
{
	char* name;
	long id;
	int words;
	static long ctrid;
public:
	Document();
	Document(char* name, int words);
	Document(char* name);
	Document(const Document& other);
	virtual ~Document();
	const Document& operator=(const Document& other);
	friend ostream& operator<<(ostream& out, const Document& d);//used for file printing
	virtual void show() const = 0;//print to cmd
	virtual bool operator==(Document& other)const;
	Document& operator+(const Document& o);//increase words by o's words
	char* getName() const { return name; }
	long getID() const { return id; }
	int getWords() const { return words; }
	void setName(const char* name);
	void setWords(int words);
	bool Long(); //length over 1000 words
	virtual int wordsCounter()=0;
	void PrintField() const {cout << "Doc id: " << this->getID() << ", Name: " << this->getName() << ", Amount of words: " << this->getWords(); }
	//help to print show
};
#endif