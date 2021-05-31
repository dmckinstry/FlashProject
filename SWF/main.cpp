#include <iostream>
#include <cmath>
#include <vector>
using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

/*
First and foremost, there is going to be something that reads the basic data types.

Then, there will be a different class for each individual tag. 
	XML, MP3, etc. are going to be their own bin dumps of data. The code that actually runs them is separate, if included at all.

At the highest sub-execution level, there will be a reader. 
	This reader will have either a file, a bytes, or a bytearray object, going off of python as an example.
	This reader will have a char dictating which type it is
	This reader will have a function that generates the next byte.

At execution level, there will be an object with the two higher-level classes 
*/

#include "BaseTypes.h"
#include "Tests.h"
#include "BytIt.h"
#include "TestBytIt.h"

#include "TestBytIt.cpp"
#include "BytIt.cpp"
#include "Tests.cpp"
#include "BaseTypes.cpp"

int main(int argc, char** argv) {
	
	//Tests of basic interpreter class:
	testToBits();
	testRect();
	testArgb();
	testRgb();

	testFFromBits();
	testSignedIntFromBits();
	testMat();
	testCXF();
	testCXFA();


	//Tests of BytIt and subclasses:
TestBytItGet();//PROBABLY NOT A DATA LEAK HERE? it will only be executed once though?

	return 0;
}
