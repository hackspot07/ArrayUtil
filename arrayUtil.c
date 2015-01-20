#include "arrayUtil.h"
#include <stdio.h>
#include <stdlib.h>

int areEqual(ArrayUtil array1,ArrayUtil array2){
	int i;
	char *a = array1.base;
	char *b = array2.base; 
	if(array1.length != array2.length)
			return 0;
	for(i=0;i<array1.length*array1.typeSize;i++){
		if(a[i] != b[i])
			return 0;
	}
	return 1;
};


ArrayUtil create(int typeSize,int length){
	ArrayUtil array;
	char *base = calloc(length,typeSize);
	array.base = base;
	array.typeSize = typeSize;
	array.length = length;
 	return array;
};

ArrayUtil resize(ArrayUtil array,int length){
	int i,*srcArray = array.base;
	int typeSize = sizeof(srcArray[0]);
	int *resultBase =calloc(length,typeSize);
	for(i=0;i<length;i++){
		if(i<array.length)
			resultBase[i] = srcArray[i];
	};
	array.base = resultBase;
	array.length = length;
	return array;
};

int findIndex(ArrayUtil array, void* element){
	int index,count=0;
	char *src = (char*)array.base;
	char *ele = (char*)element;
	int mLength = array.length*array.typeSize;
	for(index=0;index<mLength;index++){
		if(src[index]==ele[count])
			count++;
		if(count==array.typeSize)
	 		return index/array.typeSize;
	};
	return -1;
};


void dispose(ArrayUtil array){
	free(array.base);
	array.length=0;
	array.typeSize=0;
};

void* findFirst(ArrayUtil array, MatchFunc* match, void* hint){
	int i;
	char* src = (char*)array.base;
	int mLength = array.length*array.typeSize;
	for(i=0;i<mLength;i++){
		if(match(hint,&src[i]))
			return &src[i];
	};
	return NULL;
};
