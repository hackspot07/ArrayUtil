typedef struct arrayUtil{
	void  *base;
	int typeSize;
	int length;
}ArrayUtil;

typedef int MatchFunc (void* hint, void* item);

int areEqual(ArrayUtil util1,ArrayUtil util2); 
ArrayUtil create(int typeSize, int length);
ArrayUtil resize(ArrayUtil util, int length); 
int findIndex(ArrayUtil util, void* element);
void dispose(ArrayUtil util);
void* findFirst(ArrayUtil util, MatchFunc* match, void* hint);