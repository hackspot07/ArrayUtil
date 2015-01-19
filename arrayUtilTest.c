#include "expr_assert.h"
#include "arrayUtil.h"
#include<stdlib.h>

void test_ArrayUtil_a_and_ArrayUtil_b_are_not_equal(){
	float a [] = {1.5,2,3,4,5};
	float b [] = {1,2,4,3,5};

	arrayUtil array1;
	arrayUtil array2;

	array1.base = a;
	array1.typeSize = sizeof(int);
	array1.length = 5;

	array2.base = b;
	array2.typeSize = sizeof(int);
	array2.length = 5;

	assertEqual(areEqual(array1,array2),0);
};

void test_ArrayUtil_a_and_ArrayUtil_b_are_will_be_equal(){
	int a [] = {1,2,3,4,5};
	int b [] = {1,2,3,4,5};

	arrayUtil array1;
	arrayUtil array2;

	array1.base = a;
	array1.typeSize = sizeof(int);
	array1.length = 5;

	array2.base = b;
	array2.typeSize = sizeof(int);
	array2.length = 5;

	assertEqual(areEqual(array1,array2),1);
};
