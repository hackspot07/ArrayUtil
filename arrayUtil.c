#include "arrayUtil.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int areEqual(ArrayUtil util1,ArrayUtil util2){
	int i;
	char *a = util1.base;
	char *b = util2.base; 
	if(util1.length != util2.length)
			return 0;
	for(i=0;i<util1.length*util1.typeSize;i++){ 
		if(a[i] != b[i])
			return 0;
	}
	return 1;
};


ArrayUtil create(int typeSize,int length){
	ArrayUtil array = {calloc(length,typeSize),typeSize,length};
 	return array;
};

ArrayUtil resize(ArrayUtil array,int length){
	int i,copyLength;
	void *newArray;
	copyLength = (length<=array.length?length:array.length)*array.typeSize;
	newArray = calloc(length,array.typeSize); 
	memcpy(newArray,array.base,copyLength);
	array.base = newArray;
	array.length = length;
	return array;
};

int findIndex(ArrayUtil array, void* element){
	int index,count=0;
	char *src = array.base;
	char *ele = element;
	int mLength = array.length*array.typeSize;
	for(index=0;index<mLength;index++){  
		if(src[index] != ele[count])
			count = 0;
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
	for(i=0;i<array.length*array.typeSize;){
		if(match(hint,&(array.base[i])))
			return &(array.base[i]);
		i = i + array.typeSize;
	};
	return NULL;
};

void* findLast(ArrayUtil array, MatchFunc* match, void* hint){
	int i;
	int position = (array.length-1)*array.typeSize;
	for(i=position;i>=0;){
		if(match(hint,&(array.base[i])))
			return &(array.base[i]);
		i = i - array.typeSize;
	};
	return NULL;
};

int count(ArrayUtil array, MatchFunc* match, void* hint){
	int i,j=0;
	for(i=0;i<array.length*array.typeSize;i++){
		if(match(hint,&(array.base[i]))){ 
			j++;
		}
	};
	return j;
};

int filter(ArrayUtil array, MatchFunc* match, void* hint, void** destination, int maxItems ){
	int i,length=0;
	*destination = malloc(array.typeSize);
	for(i=0;i<array.length*array.typeSize;){
		if(match(hint,&array.base[i])){
			memcpy(&((*destination)[length*array.typeSize]),&(array.base[i]),array.typeSize);
			length++;
			*destination = realloc(*destination,array.typeSize*length+1);
		}  
		i = i + array.typeSize;
		if(maxItems==length)
			return maxItems;
	};
	return length;
};

void map(ArrayUtil source, ArrayUtil destination, ConvertFunc* convert, void* hint){
	int i;
	for(i=0;i<source.length*source.typeSize;){
		 convert(hint,&(source.base[i]),&(destination.base[i]));
		 i = i + source.typeSize;
	}
};

void forEach(ArrayUtil util, OperationFunc* match, void* hint){
	int i;
	for(i=0;i<util.length*util.typeSize;){
		match(hint,&util.base[i]);
		i = i + util.typeSize;
	};
};

void* reduce(ArrayUtil util, ReducerFunc* reducer, void* hint, void* intialValue){
	int i;
	for(i=0;i<util.typeSize*util.length;){
		intialValue = reducer(hint,intialValue,&util.base[i]);
		i = i + util.typeSize;
	}
	return intialValue;
}
