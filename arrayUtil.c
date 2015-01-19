#include "arrayUtil.h"
#include <stdio.h>

int areEqual(arrayUtil array1,arrayUtil array2){
	int i;
	int *a = array1.base;
	int *b = array2.base; 
	if(array1.length != array2.length)
			return 0;
	for(i=0;i<array1.length;i++){
		if(a[i] != b[i])
			return 0;
	}
	return 1;
};