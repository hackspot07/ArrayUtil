#define String char*
#define SIZEOF_CHAR sizeof(char)
#define SIZEOF_DOUBLE sizeof(double)
#include "expr_assert.h"
#include "arrayUtil.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ArrayUtil util, resultUtil, expectedUtil;
int sample[] = {1,2,3,4,5};

void increment(void* hint, void* sourceItem, void* destinationItem){

	*(int*)destinationItem = *(int*)hint + *(int*)sourceItem;
}

void charConvertFunc(void* hint, void* sourceItem, void* destinationItem){
	*((char*)destinationItem) = *((char*)sourceItem) - 32;
}

void test_ArrayUtil_a_and_ArrayUtil_b_are_will_be_equal(){
	int a [] = {1,02};
	int b [] = {1,02};
	ArrayUtil array1 = {a, sizeof(int), 2};
	ArrayUtil array2 = {b, sizeof(int), 2};
	
	assert(areEqual(array1,array2));
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

	assert(areEqual(array1,array2));
};

void test_ArrayUtil_a_and_ArrayUtil_b_are_will_be_equal_by_each_element_typeof_string(){
	String a [] = {"hello"};
	String b [] = {"hello"};
	ArrayUtil array1 = {a, sizeof(String), 1};
	ArrayUtil array2 = {b, sizeof(String), 1};

	assert(areEqual(array1,array2));
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

	assert(areEqual(array1,array2));
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

void test_resize_returns_INT_array_within_structure_with_new_allocated_space(){
	ArrayUtil resizedArray;
	util = (ArrayUtil){(int []){1,2,3,4},sizeof(int),4};
	resizedArray = resize(util,6);

	expectedUtil = (ArrayUtil){(int []){1,2,3,4,0,0},sizeof(int),6}; 

	assert(areEqual(expectedUtil, resizedArray));
	dispose(resizedArray);
};

void test_resize_add_0_to_the_new_places_created_in_char_array(){
	char *array= "abc";
	char arr[] = {'a','b','c',0,0};
	ArrayUtil array2, util1 = {array, SIZEOF_CHAR, 3};
	ArrayUtil expected = {arr, SIZEOF_CHAR ,5};
	array2 =  resize(util1,5);
	assert(areEqual(array2 , expected));
}

void test_resize_add_0_to_the_new_places_created_in_double_array(){
	double array[] = {1,2,3}, arr[] = {1,2,3,0,0};
	ArrayUtil array2, util1 = {array, SIZEOF_DOUBLE, 3};
	ArrayUtil expected = {arr, SIZEOF_DOUBLE ,5};
	array2 =  resize(util1,5);
	
	assert(areEqual(array2 , expected));
}

void test_ArrayUtil_returns_the_array_which_last_value_will_be_2(){
	ArrayUtil array = create(sizeof(float),5);
	ArrayUtil resultArray;
	((char*)array.base)[1] = 2;
	resultArray = resize(array,2);
	assertEqual(((char*)resultArray.base)[1], 2);
};

void test_ArrayUtil_add_0_in_characterArray(){
	ArrayUtil array = create(sizeof(char),2);
	ArrayUtil resultArray;
	((char*)array.base)[1] = 'a';
	resultArray = resize(array,2);
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
	if(*(int*)item==8 ||*(float*)item == 9.0 || *(double*)item==8.9)
		return 1;
	return 0;
}

void test_findFirst_will_return_8(){
	int a[]={8,3,5,7,8,9},hint=3;
	ArrayUtil array = {a, sizeof(int), 6};
	int* result = findFirst(array,isEqual,&hint);

	assertEqual((int)*result,8);
};

int stringCompare(void *hint, void* item){
	String str ="hello";
	String getItem = *(String*)item;
	if(getItem==str)
		return 1;
	return 0;
}

void test_findFirst_will_return_NULL(){
	int a[]={1,3,5,7,5,9},hint=3,*result;
	ArrayUtil array = {a, sizeof(int), 6};
	result = findFirst(array,isEqual,&hint);

	assertEqual((int)result,(int)NULL);
};

int compare(void *hint,void* item){
	if(*(char*)item=='a')
		return 1;
	return 0;
};

void test_findfirst_will_return_a(){
	char a[]={'b','a','b','b'},hint=3,*result;
	ArrayUtil array = {a, sizeof(char), 3};
	result = findFirst(array,compare,&hint);

	assertEqual((char)*result,'a');
};

void test_findfirst_will_return_hello(){
	ArrayUtil array = create(sizeof(String),2);
	String expected;
	int hint=3,*result;
	((char**)array.base)[0]="hello";
	((char**)array.base)[1]="gello";
	result = findFirst(array,stringCompare,&hint);
	expected = ((String)*result);

	assertEqual(strcmp(expected,"hello"),0);
};

void test_findLast_will_return_a(){
	char a[]={'a','b'},hint=3,*result;
	ArrayUtil array = {a, sizeof(char), 2};
	result = findFirst(array,compare,&hint);

	assertEqual((char)*result,'a');
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
	result = findFirst(array,isEqual,&hint);

	assertEqual((int)(result),(int)NULL);
};

void test_count_will_return_3(){
	int a[]={1,8,8,7,8,9},hint=3,result;
	ArrayUtil array = {a, sizeof(int), 6};
	result = count(array,isEqual,&hint);

	assertEqual(result,3);
};

void test_count_will_return_0(){
	int a[]={1,6,6,7,7,9},hint=3,result;
	ArrayUtil array = {a, sizeof(int), 6};
	result = count(array,isEqual,&hint);

	assertEqual(result,0);
};

void test_count_will_return_1(){
	char a[]={'a','b'},hint=3,result;
	ArrayUtil array = {a, sizeof(char), 2};
	result = count(array,compare,&hint);

	assertEqual(result,1);
};

void test_filter_will_return_the_length_of_array_3(){
	int a[]={1,8,8,7,8,9},hint=3,length;
	void* result = malloc(sizeof(int));
	ArrayUtil array = {a, sizeof(int), 6};
	length = filter(array,isEqual,&hint,result,5);

	assertEqual(length,3);
	free(result);
};


void test_filter_will_return_the_array_of_8_8_8(){
	int a[]={1,8,8,7,8,9},hint=3,length;
	void* result;
	ArrayUtil array = {a, sizeof(int), 6};
	length = filter(array,isEqual,&hint,&result,5);

	assertEqual(((int*)result)[0],8);
	assertEqual(length,3);
	free(result);
};


void test_filter_will_return_the_array_of_only_two_8(){
	int a[]={1,8,8,7,8,9},hint=3,length;
	void* result;
	ArrayUtil array = {a, sizeof(int), 6};
	length = filter(array,isEqual,&hint,&result,2);

	assertEqual(((int*)result)[1],8);
	assertEqual(length,2);
	free(result);
};

void test_filter_will_return_the_array_of_only_two_8_point_7_in_float(){
	float a[]={1.4,8.4,8.9,7,8,9.0},hint=3;
	int length;
	void* result;
	ArrayUtil array = {a, sizeof(float), 6};
	length = filter(array,isEqual,&hint,&result,2);

	assertEqual(((float*)result)[0],9.0);
	assertEqual(length,1);
	free(result);
};

void test_filter_will_return_the_array_a_a_a(){
	char a[]={'a','a','a','b','d'},hint=3;
	int length;
	void* result;
	ArrayUtil array = {a, sizeof(char), 5};
	length = filter(array,compare,&hint,&result,5);

	assertEqual(((char*)result)[1],'a');
	assertEqual(length,3);
	free(result);
};

void test_filter_will_return_the_array_of_only_one_element_8_point_9_in_double(){
	double a[]={8.4,8.4,8.9},hint=3.9;
	int length;
	void* result;
	ArrayUtil array = {a, sizeof(double), 3};
	length = filter(array,isEqual,&hint,&result,2);

	assertEqual(((double*)result)[0],8.9);
	assertEqual(length,1);
	free(result);
};

void test_filter_will_return_the_array_string_contain_hello(){
	int length,hint=9;
	void* result,*expected;
	ArrayUtil array = create(sizeof(String),2);
	((char**)array.base)[0]="hello";
	((char**)array.base)[1]="gello";
	length = filter(array,stringCompare,&hint,&result,2);
	expected = ((String*)result)[0];
	
	assertEqual(length,1);
	assertEqual(strcmp(expected,"hello"),0);
};




void multiplyBy2(void* hint, void* sourceItem, void* destinationItem){
	*(int*)destinationItem = *(int*)sourceItem*2;
};

void test_map_will_return_after_multiplyby_2_in_each_element(){
	int hint = 3;
	ArrayUtil source = create(sizeof(int),2);
	ArrayUtil expected = create(sizeof(int),2);
	ArrayUtil destination = create(sizeof(int), 2);
	((int*)source.base)[0] = -10200004;
	((int*)source.base)[1] = 11700;
	((int*)expected.base)[0] = -20400008;
	((int*)expected.base)[1] = 23400;
	map(source,destination,multiplyBy2,&hint);

	assert(areEqual(destination,expected));
	free(destination.base);
};

void test_map_will_return_array_of_elements_multiplyby_2(){
	int hint = 3;
	ArrayUtil source = create(sizeof(int),2);
	ArrayUtil expected = create(sizeof(int),2);
	ArrayUtil destination = create(sizeof(int), 2);
	((int*)source.base)[0] = 117;
	((int*)source.base)[1] = -117;
	((int*)expected.base)[0] = 234;
	((int*)expected.base)[1] = -234;
	map(source,destination,multiplyBy2,&hint);

	assert(areEqual(destination,expected));
	free(destination.base);
};


int isDivisible(void* a,void *b){
	return (*((int*)b)%*((int*)a) == 0) ? 1 : 0;
}


void test_filter_gives_2_4_for_1_2_3_4_5(){
	ArrayUtil util = create(sizeof(int),5);
	int *arr,i,result,hint = 2,*lIst;
	void* list;
	arr = (int*)util.base;
	for(i=0;i<5;i++){
		arr[i] = i+1;
	}
	result = filter(util, isDivisible,&hint,&list,2);
	lIst = (int*)list;
	assertEqual(result,2);
	assertEqual(lIst[0],2);
	assertEqual(lIst[1],4);
	free(list); 
}

void test_map_should_map_source_to_destination_using_the_provided_convert_function(){
	int hint = 1, result[] = {2,3,4,5,6};
	
	util = (ArrayUtil){sample, sizeof(int), 5};
	resultUtil = create(util.typeSize, util.length);
	expectedUtil = (ArrayUtil){result, sizeof(int), 5};

	map(util, resultUtil, increment, &hint);
	
	assert(areEqual(expectedUtil, resultUtil));
	dispose(resultUtil);
};

void test_map_gives_A_B_C_D_E_for_a_b_c_d_e_for_character_array(){
	ArrayUtil src = {(char[]){'a','b','c','d','e'},sizeof(char),5},dest = create(sizeof(char),5);
	ArrayUtil tmp = {(char[]){'A','B','C','D','E'},sizeof(char),5};
	char hint = 32;
	map(src,dest,charConvertFunc,&hint);
	assertEqual(areEqual(dest,tmp),1);
	dispose(dest);
}