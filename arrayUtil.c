#include "arrayUtil.h"
#include <stdio.h>
#include <stdlib.h>

int areEqual(ArrayUtil util1,ArrayUtil util2){
	int i;
	char *a = util1.base;
	char *b = util2.base; 
	if(util1.length != util2.length)
			return 0;
	for(i=0;i<util1.length*util1.typeSize;i++)
		if(a[i] != b[i])
			return 0;
	return 1;
};


ArrayUtil create(int typeSize,int length){
	ArrayUtil array = {calloc(length,typeSize),typeSize,length};
 	return array;
};

ArrayUtil resize(ArrayUtil array,int length){
	int i,j=array.length*array.typeSize;
	int newIndexs = (length-array.length)*array.typeSize;
	array.base = realloc(array.base,length*array.typeSize);
	for(i=0;i<newIndexs;i++){
		((char*)array.base)[i+j]=0;
	}
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

// void* findFirst(ArrayUtil array, MatchFunc* match, void* hint){
// 	int i;
// 	char* src = (char*)array.base;
// 	int mLength = array.length*array.typeSize;
// 	for(i=0;i<mLength;i++){
// 		if(match(hint,&src[i]))
// 			return &src[i];
// 	};
// 	return NULL;
// };
