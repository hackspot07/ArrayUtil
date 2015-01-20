#include "arrayUtil.h"
#include <stdio.h>
#include <stdlib.h>

int areEqual(ArrayUtil array1,ArrayUtil array2){
	int i;
	int *a = (int*)array1.base;
	int *b = (int*)array2.base; 
	if(array1.length != array2.length)
			return 0;
	for(i=0;i<array1.length;i++){
		if(a[i] != b[i])
			return 0;
	}
	return 1;
};


ArrayUtil create(int typeSize,int length){
	ArrayUtil array;
	void *base = calloc(length,typeSize);
	array.base = base;
	array.typeSize = typeSize;
	array.length = length;
 	return array;
};

ArrayUtil resize(ArrayUtil array,int length){
	int i,*srcArray = (int*)array.base;
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