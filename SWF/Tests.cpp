
void testToBits()
{
	
	int testArr[2] = {(int)'1',(int)'2'}; //x31, x32
	cout<<"Testing toBits function on input x31, x32, should return 0011 0001 0011 0010\n";
	vector<bool> testBits = interpreter::toBits(&testArr[0],2);
		for(int i=0; i<testBits.size(); i++)
	{
		if(i%4==0)
			cout<<" ";
		cout<<testBits.at(i);
	}
	cout<<'\n';
}

void testRect()
{
	int rectchar[4] = {40, 32, 8, 0};
	cout<<"Testing rect reader with 0010 1-000 00-10 000-0 0000-1000 0-000 0000, as characters.\n";
	cout<<"This should be: size 5(unread), xmin 0, xmax 16, ymin 0, ymax 16, with 7 trailing zeroes for byte alignment.\n";
	struct rect testRect = interpreter::readRect(&rectchar[0], 5);
	cout<<"xmin "<<testRect.xmin<<", xMax "<<testRect.xmax<<", yMin "<<testRect.ymin<<", yMax "<<testRect.ymax;
}

void testArgb()
{
	int testArgbChar[4] = {255,  255, 0, 0}; 
	cout<<"\nTesting argb function on full red, full alpha color scheme.\n";
	struct argb testArgb = interpreter::readArgb(&testArgbChar[0]);
	cout<<"A "<<testArgb.a<<", R "<<testArgb.r<<", G "<<testArgb.g<<", B "<<testArgb.b<<'\n';
}

void testRgb()
{
	int testRgbInts[3] = {255, 0, 0};
	cout<<"\nTesting rgb function on full red color scheme.\n";
	struct rgb rugby = interpreter::readRgb(&testRgbInts[0]);
	cout<<"R "<<rugby.r<<", G "<<rugby.g<<", B "<<rugby.b<<'\n';
}

void testFFromBits()
{
	bool bits[18]={1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	//try 1.5
	cout<<"\nTrying 11 1000 0000 0000 0000 on the fFromBits(), should return 3.5";
	cout<<'\n'<<interpreter::fFromBits(&bits[0],18);
}

void testMat()
{
	//Create a read matrix thing: Has a scale of 5.0 X and Y, no skew, and a TX and TY of 5;
	// Scale of 5.0; 0101 0000 0000 0000 0000, 20 bits: 10100
	//TX and TY 101: length 3 00011
	// 1 101,00 01,01 00,00 00,00 00,00 00,00 01,01 00,00 00,00 00,00 00,00 0 0,0011, 101 1,01
	// 1101 0001 0100 0000 0000 0000 0001 0100 0000 0000 0000 0000 0011 1011 0100
	//bool bits[58] = {1, 1,0,1,0,0, 0,1,0,1, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,1,0,1, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0, 0,0,0,1,1, 1,0,1, 1,0,1};
	int bytes[8] = {209, 64, 0, 20, 0, 0, 59, 64};
	struct matrix testMatrix = interpreter::readMat(&bytes[0], 8);
	cout<<"\nCreating a matrix with 5.0 X and Y scale, TX and TY of -1:";
	cout<<"\nscaleX: "<<testMatrix.scaleX<<" scaleY: "<<testMatrix.scaleY<<" TX: "<<testMatrix.translateX<<" TY: "<<testMatrix.translateY;
}

void testSignedIntFromBits()
{
	bool bits[3] = {1,0,1};
	cout<<"\nTesting signedIntFromBits on 101 = -1: "<<interpreter::signedIntFromBits(bits, 3);
}

void testCXF()
{
	//Testing one with add and multiply, with 100 each.
	//100 : 110100, 6 bits = 0110; so: 1|1|0110|110100|110100|110100|110100|110100
	//						1101 1011 0100 1101 0011 0100 1101 0011 0100 1101 0000 2 trailing
	//						219			115		52			211		77			0
	bool bitVal[48];
	int hund = 100;
	bitVal[0] = 1;
	bitVal[1] = 1;
	bitVal[2] = 0;
	bitVal[3] = 1;
	bitVal[4] = 1;
	bitVal[5] = 1; //FIRST SIX FUCKING BITS ARE T, T, 7.
	vector<bool> sevVect = interpreter::toBits(&hund, 7); //Seven bit hundred
	sevVect = interpreter::cutBits(sevVect,1);
	for (int i = 0; i < 6; i++) //print 6 hundreds to bitVal. Index = 6 + (7*i) + j
		for(int j = 0; j < 7; j++) //Finds the bit at j for the seven bit 100;
			bitVal[6 + (7*i) + j] = sevVect.at(j);
	//THE REMAINING 42 BITS ARE 100 REPEATING
	int bytes[6] = {interpreter::fromBits(&bitVal[0],8),interpreter::fromBits(&bitVal[8],8),interpreter::fromBits(&bitVal[16],8),
			interpreter::fromBits(&bitVal[24],8),interpreter::fromBits(&bitVal[32],8),interpreter::fromBits(&bitVal[40],8)}; 
	struct cxform test = interpreter::readCXF(&bytes[0],11);
	cout <<"\nTesting CXForm with 100 RBG add and multiply terms, should return 100 6 times:\n";
	cout <<test.red_add<<' '<<test.green_add<<' '<<test.blue_add<<' '<<test.red_mult<<' '<<test.green_mult<<' '<<test.blue_mult;
	
}

void testCXFA()
{
	int bytes[8] = {223, 38, 76, 153, 50, 100, 201, 144};

	struct cxform_alpha test= interpreter::readCXFA(&bytes[0], 8);
	cout <<"\nTesting CXForm_alpha with 100 RBGA add and multiply terms, should return 100 8 times:\n";
	cout <<test.red_add<<' '<<test.green_add<<' '<<test.blue_add<<' '<<test.alpha_add<<' '<<test.red_mult<<' '<<test.green_mult<<' '<<test.blue_mult<<' '<<test.alpha_mult;
	
}
