#define _CRT_SECURE_NO_WARNINGS
#include "Document.h"
long Document::ctrid = 10016;

Document::Document():words(0), id(ctrid++)
{
	this->setName("NoName");
}

Document::Document(char* name, int words)  :id(ctrid++)
{
	if (name != NULL && words>=0)
	{
		setName(name);
		this->words = words;
	}
	else 
	{
		this->setName("NoName");
		this->words = 0;
	}
}

Document::Document(char* name) :Document(name,0)
{
}

Document::Document(const Document& other)
{
	this->id = other.id;
	this->words = other.words;
	*this = other;
}

Document::~Document()
{
	if (name)
	{ 
	delete name;
	name = NULL;
	}
}

const Document& Document::operator=(const Document& other)
{
	if (this != &other)
	{
		setName(other.name);
	}
	return *this;
}

bool Document::operator==(Document& other) const
{
	return (other.words == words && !strcmp(other.name, this->name));
}

Document& Document::operator+(const Document& o)
{
	words += o.words;
	return *this;
}

void Document::setName(const char* name)
{
	if (name)
	{
		this->name = new char[strlen(name) + 1];
		strcpy(this->name, name);
	}
	else this->name = NULL;
}

void Document::setWords(int words)
{
	this->words = words;
}

bool Document::Long()
{
	return ((words>100)? true:false);
}

ostream& operator<<(ostream& out, const Document& d)
{
	out << d.id <<" "<< d.name <<" "<<d.words;
	return out;
}

