typedef struct arrayUtil{
	void  *base;
	int typeSize;
	int length;
}ArrayUtil;

typedef struct Student{
    int rollno;
    float age;
} student;

typedef int MatchFunc (void* hint, void* item);
typedef void ConvertFunc(void* hint, void* sourceItem, void* destinationItem);

int areEqual(ArrayUtil util1,ArrayUtil util2); 
ArrayUtil create(int typeSize, int length);
ArrayUtil resize(ArrayUtil util, int length); 
int findIndex(ArrayUtil util, void* element);
void dispose(ArrayUtil util);
void* findFirst(ArrayUtil util, MatchFunc* match, void* hint);
void* findLast(ArrayUtil util, MatchFunc* match, void* hint);
int count(ArrayUtil util, MatchFunc* match, void* hint);
int filter(ArrayUtil util, MatchFunc* match, void* hint, void** destination, int maxItems);
void map(ArrayUtil source, ArrayUtil destination, ConvertFunc* convert, void* hint);