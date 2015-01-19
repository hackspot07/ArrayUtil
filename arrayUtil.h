typedef struct arrayUtil{
	void  *base;
	int typeSize;
	int length;
}ArrayUtil;

int areEqual(ArrayUtil array1,ArrayUtil Array2); 
ArrayUtil create(int typeSize, int length);
ArrayUtil resize(ArrayUtil array, int length); 