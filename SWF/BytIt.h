//This is the .h for the byte iterator. This superclass includes the subclasses for fileBytIt and strBytIt
//The fileBytIt and strBytIt contain different constructors and different versions of the next()function

#include <fstream>
using namespace std;

#ifndef BYTIT_H
#define BYTIT_H

class BytIt
{	public:
		virtual int getNext() = 0;
		//BytIt();
};

class fileBytIt: public BytIt
{
	public:
		int getNext();
		fileBytIt(char[50]);
	private:
		fstream file;
};

class strBytIt: public BytIt
{
	public:
		 int getNext();
		 strBytIt(bool[1000]);
	private:
		 bool body[1000];
		 int index;
};

#endif
