#include <iostream>
using namespace std;
//#include "BaseTypes.h"

struct rect interpreter::readRect(int* body, int nBits)
{	
	//This should include the first byte. So body* should match the first 5 bits with length
	//char firstChar = *body;
	int firstCharToInt = *body;
	
	bool xMinBits[nBits];
	bool xMaxBits[nBits];
	bool yMinBits[nBits];
	bool yMaxBits[nBits];
	
	int xMin;
	int yMin;
	int xMax;
	int yMax;
	
	if(firstCharToInt/8 != nBits)
		cout<<"Error: expected body: "<<body<<" to be equal to the nBits parameter passed: "<<nBits;
	//First thing's first, break this into bits. There should be ((nBits * 4) + 5 )/8 + 1 bytes in the char* body.
	//Four elements of nbits size: 
	int bitSize = nBits*4;
	vector<bool> bits = toBits(body , (ceil((nBits*4.0+5.0)/8.0)));
	//Get rid of the first 5 bits after this.
	
	//From the first 5 bits onwards, parse into nBit samples.
	for(int i = 5; i < nBits+5; i++)
		xMinBits[i-5] = bits.at(i);
	for(int i = 5 + nBits;i < (2*nBits)+5; i++)
		xMaxBits[i-nBits-5] = bits[i];
	for(int i = 5 + (2 * nBits); i < (3 * nBits) + 5; i++)
		yMinBits[i-(2*nBits)-5] = bits[i];
	for(int i = 5 + (3 * nBits); i < 5 + (4 * nBits); i++)
		yMaxBits[i-(3*nBits)-5] = bits[i];
	
	xMin = fromBits(&xMinBits[0], nBits);
	xMax = fromBits(&xMaxBits[0], nBits);
	yMin = fromBits(&yMinBits[0], nBits);
	yMax = fromBits(&yMaxBits[0], nBits);
	
	struct rect returnRect;
	returnRect.xmin=xMin;
	returnRect.xmax=xMax;
	returnRect.ymin=yMin;
	returnRect.ymax=yMax;

	return returnRect;
}

vector<bool> interpreter::toBits(int* body, int nBytes)
{
	int data;
	vector<bool> output;
	for (int i=0;i<nBytes;i++)
	{
		data = *body;
		for(int j = 7; j >= 0; j--)
		{
			if(data >= pow(2,j))
				output.push_back(true);
			else
				output.push_back(false);
			data=data%(int)pow(2,j);
		}
		body++;
	}
	return output;
}

int interpreter::fromBits(bool* body, int nBits)
{
	int value = 0; //start with 0 bits
	for(int i=0;i<nBits;i++)
	{
		value*=2;
		if( *body)
			value++;
		body++;
	}
	return value;
}

struct argb interpreter::readArgb(int* body)
{
	int Alph = *body;
	cout<<Alph;
	body++;
	int Red = *body;
	body++;
	int Green = *body;
	body++;
	int Blue = *body;
	struct argb value;
	value.a=Alph;
	value.r=Red;
	value.g=Green;
	value.b=Blue;
	return value;
}

struct rgb interpreter::readRgb(int* body)
{
	int Red = *body;
	body++;
	int Green = *body;
	body++;
	int Blue = *body;
	struct rgb value;
	value.r=Red;
	value.g=Green;
	value.b=Blue;
	return value;
}

double interpreter::fFromBits(bool* body, int nBits)
{
	return fromBits(body, nBits)/65536.0; //Turn to float
}

struct matrix interpreter::readMat(int* body, int nBytes)
{
	vector<bool> bitBodyVect = toBits(body,nBytes);
	bool bitBody[bitBodyVect.size()];
	for(int i = 0; i < bitBodyVect.size(); i++)
		bitBody[i] = bitBodyVect.at(i);
	bool hasScale = bitBody[0];
	int index = 1;
	struct partMatrix scale;
	struct partMatrix skew;
	if(hasScale)
	{
		//Create a partMatrix struct that can be attatched
		int num = fromBits(&bitBody[index], 5);
		index+=5;
		double xScale = signedDoubleFromBits(&bitBody[index], num);
		index+=num;
		double yScale = signedDoubleFromBits(&bitBody[index], num);
		index+=num;
		scale.xVar = xScale;
		scale.yVar = yScale;
		scale.tag = 's';
	}
	
	bool hasRotate = bitBody[index];
	index++;
	if(hasRotate)
	{
		int num = fromBits(&bitBody[index], 5);
		index += 5;
		double xRot = signedDoubleFromBits(&bitBody[index], num);
		index += num;
		double yRot = signedDoubleFromBits(&bitBody[index], num);
		index += num;
		scale.xVar = xRot; //xRot is actually 0skew.
		scale.yVar = yRot;
		scale.tag = 'k';
	}
	
	//No if statement for translate
	int numT = 	fromBits(&bitBody[index], 5);
	index += 5;
	int TX = signedIntFromBits(&bitBody[index], numT);
	index += numT;
	int TY = signedIntFromBits(&bitBody[index], numT);
	
	
	struct matrix value;
	value.scaleX = scale.xVar;
	value.scaleY = scale.yVar;
	value.RotateSkew0 = skew.xVar;
	value.RotateSkew1 = skew.yVar;
	value.translateX = TX;
	value.translateY = TY;
	return value;
}

double interpreter::signedDoubleFromBits(bool* body,  int nBits)
{
	int intFromBits = fromBits(body, nBits);
	if(intFromBits > pow(2, nBits-1)) //This is the highest bit!
		intFromBits = -1 * (intFromBits % (int)pow(2, nBits - 1));
	return intFromBits / 65536.0;
}

int interpreter::signedIntFromBits(bool* body, int nBits)
{
	int unsignedInt = fromBits(body, nBits);
	if(unsignedInt > pow(2, nBits-1))
		return (unsignedInt % (int) pow(2, nBits - 1))*-1;
	else
		return unsignedInt;	
}

struct cxform interpreter::readCXF(int* body, int nBytes)
{
	vector<bool> bitBodVect = toBits(body, nBytes);
	bool bitBody[bitBodVect.size()];
	struct cxform value;
	for (int i = 0; i < bitBodVect.size(); i++)
		bitBody[i] = bitBodVect.at(i);

//	int thirteen = 13;
//	vector<bool> tB = toBits(&thirteen, 1);
	bool hasAdd = bitBody[0];
	bool hasMult = bitBody[1];
	int nBits = fromBits(&bitBody[2], 4);
	int index = 6;
	if(hasMult)
	{
		value.red_mult = fromBits(&bitBody[index],nBits);
		index += nBits;
		value.green_mult = fromBits(&bitBody[index],nBits);
		index += nBits;
		value.blue_mult = fromBits(&bitBody[index],nBits);
		index += nBits;
	}
	if(hasAdd)
	{
		value.red_add = fromBits(&bitBody[index],nBits);
		index += nBits;
		value.green_add = fromBits(&bitBody[index],nBits);
		index += nBits;
		value.blue_add = fromBits(&bitBody[index],nBits);
		index += nBits;
	}
	value.has_add_terms = hasAdd;
	value.has_mult_terms = hasMult;
	return value;
}

struct cxform_alpha interpreter::readCXFA(int* body, int nBytes)
{
	vector<bool> bitBodVect = toBits(body, nBytes);
	bool bitBody[bitBodVect.size()];
	struct cxform_alpha value;
	for (int i = 0; i < bitBodVect.size(); i++)
		bitBody[i] = bitBodVect.at(i);
	bool hasAdd = bitBody[0];
	bool hasMult = bitBody[1];
	int nBits = fromBits(&bitBody[2], 4);
	int index = 6;
	if(hasMult)
	{	value.red_mult = fromBits(&bitBody[index],nBits);
		index += nBits;
		value.green_mult = fromBits(&bitBody[index],nBits);
		index += nBits;
		value.blue_mult = fromBits(&bitBody[index],nBits);
		index += nBits;
		value.alpha_mult = fromBits(&bitBody[index],nBits);
		index += nBits;
	}
	if(hasAdd)
	{	value.red_add = fromBits(&bitBody[index],nBits);
		index += nBits;
		value.green_add = fromBits(&bitBody[index],nBits);
		index += nBits;
		value.blue_add = fromBits(&bitBody[index],nBits);
		index += nBits;
		value.alpha_add = fromBits(&bitBody[index],nBits);
		index += nBits;
	}
	value.has_add_terms = hasAdd;
	value.has_mult_terms = hasMult;
	return value;	
}

vector<bool> interpreter::cutBits(vector<bool> bits, int numCut)
{
	vector<bool> value;
	for(int i = numCut; i < bits.size(); i++)
		value.push_back(bits.at(i));
	return value;
}
