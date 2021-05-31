//BytIt.cpp

//BytIt::getNext() = 0;


//Inherited BytIt functions:
int strBytIt::getNext()
{
	int val = interpreter::fromBits(&body[index],8);
	index += 8;
	return val;
}
strBytIt::strBytIt(bool body[1000]):BytIt()
{
	for (int i = 0; i < 1000; i++)
	{
		this->body[i] = *(body + i);
	}
	this->index = 0;
}
