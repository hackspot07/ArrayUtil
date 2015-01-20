#include "expr_assert.h"
#include "arrayUtil.h"
#include<stdlib.h>

void test_ArrayUtil_a_and_ArrayUtil_b_are_not_equal(){
	float a [] = {1.5,2,3,4,5};
	float b [] = {1,2,4,3,5};

	ArrayUtil array1;
	ArrayUtil array2;

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

	ArrayUtil array1;
	ArrayUtil array2;

	array1.base = a;
	array1.typeSize = sizeof(int);
	array1.length = 5;

	array2.base = b;
	array2.typeSize = sizeof(int);
	array2.length = 5;

	assertEqual(areEqual(array1,array2),1);
};

void test_ArrayUtil_return_the_array_that_contains_all_element_0(){
	ArrayUtil array = create(sizeof(int),5);
	int *a  = (int*)array.base;
	assertEqual(a[0],0);
	assertEqual(a[4],0);
	assertEqual(array.length, 5);
	assertEqual(array.typeSize, 4);
};

void test_ArrayUtil_returns_the_array_length_3(){
	int array [] = {1,2,3,4,5};
	int *resultArray;
	ArrayUtil resizeArray,src;
	src.base = array;
	src.length = 5;
	resizeArray = resize(src ,15);
	resultArray = resizeArray.base;
	assertEqual(resultArray[2],3);
	assertEqual(resultArray[4],5);
	assertEqual(resizeArray.length,15);
	assertEqual(resultArray[14],0);

};


void test_it_return_indexof_3(){
	int array[]= {2,6,7,8,6,5,4},index,element=8;
	ArrayUtil src;
	src.base = array;
	src.length = 7;
	src.typeSize = sizeof(int);
	index = findIndex(src,&element);
	assertEqual(index,3);
};

void test_it_return_indexof_minus_1(){
	float array[]= {4.0,6.9,7.2,8.7,6.6,5,4},index;
	float element = 2.3;
	ArrayUtil src;
	src.base = array;
	src.length = 7;
	src.typeSize = sizeof(float);
	index = findIndex(src,&element);
	assertEqual(index,-1);
};

void test_it_return_indexof_5(){
	float array[]= {4.0,6.9,7.2,8.7,6.6,5,4},index;
	float element = 6.6;
	ArrayUtil src;
	src.base = array;
	src.length = 7;
	src.typeSize = sizeof(float);
	index = findIndex(src,&element);
	assertEqual(index,4);
};

void test_it_return_indexof_2(){
	char array[]= {'a','b','c','d'};
	char element ='c';
	int index;
	ArrayUtil src;
	src.base = array;
	src.length = 4;
	src.typeSize = sizeof(char);
	index = findIndex(src,&element);
	assertEqual(index,2);
};

void test_dispose_free_the_allocated_memory(){
	ArrayUtil array;
	array = create(sizeof(int),5);
	assertEqual(((int*)array.base)[0],0);
	assertEqual(((int*)array.base)[1],0);
	dispose(array);
	//after dispose there wiill we no index 
	// assertEqual(((int*)array.base)[1],0);
};