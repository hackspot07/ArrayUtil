typedef struct arrayUtil{
	void  *base;
	int typeSize;
	int length;
}ArrayUtil;

typedef int MatchFunc (void* hint, void* item);

int areEqual(ArrayUtil array1,ArrayUtil Array2); 
ArrayUtil create(int typeSize, int length);
ArrayUtil resize(ArrayUtil array, int length); 
int findIndex(ArrayUtil array, void* element);
void dispose(ArrayUtil array);
void* findFirst(ArrayUtil util, MatchFunc* match, void* hint);