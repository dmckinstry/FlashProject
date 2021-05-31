/*
Header for the basic structs of SWF, and the functions that can add them
*/

struct rect{
	int xmin;
	int xmax;
	int ymin;
	int ymax;
};

struct argb{ //same as rgba
	int a;
	int r;
	int g;
	int b;
};

struct rgb{
	int r;
	int g;
	int b;
};

struct matrix{ //any and all values may be null, though that would be kinda terrible.
	int scaleX;
	int scaleY;
	double RotateSkew0; //Each signed fixed point bits object is 16 bits below the decimal
	double RotateSkew1;
	int translateX;
	int translateY;
};

struct partMatrix { //Refers to skew, translate, or scale.
	double xVar;
	double yVar;
	char tag; //s'k'ew, s'c'ale, 't'ranslate
};

struct cxform {
	bool has_add_terms;
	bool has_mult_terms;
	int red_add;
	int green_add;
	int blue_add;
	int red_mult;
	int blue_mult;
	int green_mult;
};

struct cxform_alpha {
	bool has_add_terms;
	bool has_mult_terms;
	int red_add;
	int green_add;
	int blue_add;
	int alpha_add;
	int red_mult;
	int blue_mult;
	int green_mult;
	int alpha_mult;
};

class interpreter{
	public:
		static struct rect readRect(int*, int); //the body and the length of the body. For each function.
		static struct argb readArgb(int*); //Always 4 bytes, size not needed.
		static struct rgb readRgb(int*); //Always 3 bytes, size not needed.
		static struct matrix readMat(int*, int);
		static struct cxform readCXF(int*, int);
		static struct cxform_alpha readCXFA(int*, int);
		static vector<bool> toBits(int*, int);
		static int fromBits(bool*, int);
		static vector<int> littleEndian(int*, int);
		static double fFromBits(bool*, int);
		static double signedDoubleFromBits(bool*,  int);
		static int signedIntFromBits(bool*, int);
		static vector<bool> cutBits(vector<bool>, int);
};
