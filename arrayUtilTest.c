#define String char*
#include "expr_assert.h"
#include "arrayUtil.h"
#include<stdlib.h>

void test_ArrayUtil_a_and_ArrayUtil_b_are_will_be_equal(){
	int a [] = {1,2};
	int b [] = {1,2};
	ArrayUtil array1 = {a, sizeof(int), 2};
	ArrayUtil array2 = {b, sizeof(int), 2};
	
	assertEqual(areEqual(array1,array2),1);
};

void test_ArrayUtil_a_and_ArrayUtil_b_are_not_equal(){
	float a [] = {1.5,2.3,3.4};
	float b [] = {1.3,2.4};
	ArrayUtil array1 = {a, sizeof(float), 3};
	ArrayUtil array2 = {b, sizeof(float), 2};

	assertEqual(areEqual(array1,array2),0);
};


void test_ArrayUtil_a_and_ArrayUtil_b_are_will_be_equal_by_each_element(){
	char a [] = {'a','b'};
	char b [] = {'a','b'};

	ArrayUtil array1 = {a, sizeof(char), 2};
	ArrayUtil array2 = {b, sizeof(char), 2};

	assertEqual(areEqual(array1,array2),1);
};

void test_ArrayUtil_a_and_ArrayUtil_b_are_will_be_equal_by_each_element_typeof_string(){
	String a [] = {"hello"};
	String b [] = {"hello"};
	ArrayUtil array1 = {a, sizeof(String), 1};
	ArrayUtil array2 = {b, sizeof(String), 1};

	assertEqual(areEqual(array1,array2),1);
};

void test_ArrayUtil_a_and_ArrayUtil_b_are_will_not_be_equal_String(){
	String a [] = {"hallo"};
	String b [] = {"hello"};
	ArrayUtil array1 = {a, sizeof(String), 1};
	ArrayUtil array2 = {b, sizeof(String), 1};

	assertEqual(areEqual(array1,array2),0);
};

void test_ArrayUtil_a_and_ArrayUtil_b_are_will_be_equal_by_each_element_typeof_double(){
	double a [] = {2.34};
	double b [] = {2.34};
	ArrayUtil array1 = {a, sizeof(double), 1};
	ArrayUtil array2 = {b, sizeof(double), 1};

	assertEqual(areEqual(array1,array2),1);
};

void test_It_return_the_array_have_length_2(){
	ArrayUtil array = create(sizeof(int),2);
	assertEqual(array.length, 2);
};

void test_It_return_the_array_with_2_element_0_0(){
	ArrayUtil array = create(sizeof(int),2);
	assertEqual(((char*)array.base)[0],0);
	assertEqual(((char*)array.base)[1],0);
};

void test_ArrayUtil_returns_the_array_length_3(){
	ArrayUtil array = create(sizeof(int),5);
	ArrayUtil resultArray = resize(array,2);
	assertEqual(resultArray.length, 2);
};

void test_ArrayUtil_returns_the_array_which_last_value_will_be_2(){
	ArrayUtil array = create(sizeof(float),5);
	ArrayUtil resultArray;
	((char*)array.base)[1] = 2;
	resultArray = resize(array,2);
	assertEqual(((char*)resultArray.base)[1], 2);
};

void test_ArrayUtil_add_0_in_characterArray(){
	ArrayUtil array = create(sizeof(char),1);
	ArrayUtil resultArray;
	resultArray = resize(array,2);
	((char*)array.base)[1] = 'a';
	assertEqual(((char*)resultArray.base)[1], 97);
};

void test_ArrayUtil_add_2_more_length_in_string(){
	ArrayUtil array = create(sizeof(String),1);
	ArrayUtil resultArray;
	((String*)array.base)[0] = "hello";
	resultArray = resize(array,3);

	assertEqual(resultArray.length, 3);
	assertEqual(((char*)resultArray.base)[2],64);

};



void test_it_return_indexof_3(){
	int array[]= {2,6,7,8,6,5,4},index,element=8;
	ArrayUtil src = {array,sizeof(int), 7};
	index = findIndex(src,&element);

	assertEqual(index,3);
};

void test_it_return_indexof_minus_1(){
	float array[]= {4.0,6.9,7.2,8.7,6.6,5,4},index;
	float element = 2.3;
	ArrayUtil src = {array,sizeof(float), 7};
	index = findIndex(src,&element);

	assertEqual(index,-1);
};

void test_it_return_indexof_5(){
	float array[]= {4.0,6.9,7.2,8.7,6.6,5,4},index;
	float element = 6.6;
	ArrayUtil src = {array,sizeof(float), 7};	
	index = findIndex(src,&element);

	assertEqual(index,4);
};

void test_it_return_indexof_2(){
	char array[]= {'a','b','c','d'};
	char element ='c';
	int index;
	ArrayUtil src = {array,sizeof(char), 4};
	index = findIndex(src,&element);

	assertEqual(index,2);
};

void test_dispose_free_the_allocated_memory(){
	ArrayUtil array;
	array = create(sizeof(int),5);
	assertEqual(((int*)array.base)[0],0);
	assertEqual(((int*)array.base)[1],0);
	dispose(array);
	//after dispose there will we no index 
	// assertEqual(((int*)array.base)[1],0);
};


int isEqual(void* hint, void* item){
	int value = 8;
	if(*(int*)item==8)
		return 1;
	return 0;
}

void test_findFirst_will_return_8(){
	int a[]={8,3,5,7,8,9},hint=3;
	ArrayUtil array = {a, sizeof(int), 6};
	int* result = findFirst(array,isEqual,&hint);

	assertEqual((int)*result,8);
};

void test_findFirst_will_return_NULL(){
	int a[]={1,3,5,7,5,9},hint=3,*result;
	ArrayUtil array = {a, sizeof(int), 6};
	array.typeSize = sizeof(int);
	result = findFirst(array,isEqual,&hint);\

	assertEqual((int)(result),(int)NULL);
};

void test_findLast_will_return_last_8(){
	int a[]={8,3,5,7,8,9},hint=3;
	ArrayUtil array = {a, sizeof(int), 6};
	int* result = findLast(array,isEqual,&hint);

	assertEqual((int)*result,8);
};


void test_findLast_will_return_NULL(){
	int a[]={1,3,5,7,5,9},hint=3,*result;
	ArrayUtil array = {a, sizeof(int), 6};
	array.typeSize = sizeof(int);
	result = findFirst(array,isEqual,&hint);

	assertEqual((int)(result),(int)NULL);
};