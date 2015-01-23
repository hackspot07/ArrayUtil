typedef char*  String;
#define SIZEOF_INT sizeof(int)
#define INT_SIZE sizeof(int)
#define CHAR_SIZE sizeof(char)
#define FLOAT_SIZE sizeof(float)
#define DOUBLE_SIZE sizeof(double)
#include "expr_assert.h"
#include "arrayUtil.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isCapital(void *hint, void *item) {
    return((*(char *)item >=65) && (*(char *)item <= 91));
}

int isGreaterThan5(void *hint, void *item) {
    return(*(float *)item > 5);
}

int isEven(void* a,void* b){
	return (*((int*)b)%2==0) ? 1 : 0;
}

int isDivisible(void* a,void *b){
	return (*((int*)b)%*((int*)a) == 0) ? 1 : 0;
}
int isUpperCase(void* a,void *b){
	return (*((char*)b) >= 'A' && *((char*)b) <= 'Z') ? 1 : 0;
}
void intAddOperation(void* hint, void* item) {
	*((int *)item) = *((int *)hint) + *((int *)item);	
}
void intConvertFunc(void* hint, void* sourceItem, void* destinationItem){
	*((int *)destinationItem) = *((int *)hint) + *((int *)sourceItem);
}

void charConvertFunc(void* hint, void* sourceItem, void* destinationItem){
	*((char*)destinationItem) = *((char*)sourceItem) - 32;
}



void test_create_returns_same_array_if_array_lengths_are_same_and_values_are_same() {
	ArrayUtil a,b;
	int expected = 1,actual;
	a = create(sizeof(int),2);
	b = create(sizeof(int),2);
	assert(areEqual(a,b) == 1);
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

void test_findLast_returns_null_if_there_is_no_match_in_integer_array(){
	ArrayUtil a = {(int[]){1,3,5,7,9},sizeof(int),5};
	int x = 2;
	assertEqual((int)findLast(a,isEven,&x),(int)NULL);
};

void test_filter_gives_D_E_for_a_b_c_D_E() {
	ArrayUtil a = {(char []){'a','b','c','D','E'},sizeof(char),5};
	char *result,hint = 'a',*lIst;
	void* list;
	int count;
	count =  filter(a,isUpperCase,&hint,&list,2);
	lIst = (char*)list;
	assert(count==2);
	assertEqual(lIst[0],'D');
	assertEqual(lIst[1],'E');
	free(list); 
};

void test_findLast_returns_the_last_element_if_there_is_match_in_character_array(){
	ArrayUtil a = {(char[]){'a','b','C','D','e'},sizeof(char),5};
	int x = 'D';
	assertEqual(*((char*)findLast(a,isUpperCase,&x)),'D');
};

void test_findLast_returns_the_last_element_if_there_is_match_in_integer_array(){
	ArrayUtil a = {(int[]){1,3,5,8,10},sizeof(int),5};
	int x = 2;
	assertEqual(*((int*)findLast(a,isEven,&x)),10);
};

void test_map_gives_2_3_4_5_6_for_1_2_3_4_5_for_integer_array(){
	ArrayUtil src = {(int[]){1,2,3,4,5},sizeof(int),5},dest = create(sizeof(int),5);
	ArrayUtil tmp = {(int[]){2,3,4,5,6},sizeof(int),5};
	int hint = 1;
	map(src,dest,intConvertFunc,&hint);
	assert(areEqual(dest,tmp)==1);
};


void test_map_gives_A_B_C_D_E_for_a_b_c_d_e_for_character_array(){
	ArrayUtil src = {(char[]){'a','b','c','d','e'},sizeof(char),5},dest = create(sizeof(char),5);
	ArrayUtil tmp = {(char[]){'A','B','C','D','E'},sizeof(char),5};
	char hint = 32;
	map(src,dest,charConvertFunc,&hint);
	assertEqual(areEqual(dest,tmp),1);
	dispose(dest);
}

// void test_resize_add_0_to_the_new_places_created_in_integer_array(){
// 	int array[] = {1,2,3}, arr[] = {1,2,3,0,0};
// 	ArrayUtil array2, util1 = {array, SIZEOF_INT, 3};
// 	ArrayUtil expected = {arr, SIZEOF_INT ,5};
// 	array2 =  resize(util1,5);
// 	assert(areEqual(array2 , expected));
// };

void test_create_allocates_space_for_INT_array_and_assigns_zero_to_all_bytes(){
	ArrayUtil util = create(sizeof(int),4);
	int intArray[] = {0,0,0,0};
	ArrayUtil expectedUtil;
	expectedUtil.base = intArray;
	expectedUtil.typeSize = sizeof(int);
	expectedUtil.length = 4;

	assertEqual(areEqual(expectedUtil,util),1);
};
void test_when_an_array_is_resized_into_smaller_size_the_array_is_trimmed(){
	ArrayUtil util = create( sizeof(char) , 3);
	ArrayUtil resizedUtil = resize(util, 2);
	char array[]={0,0,0};
	ArrayUtil expected = { (void *)array, sizeof(char), 2};

	assert(areEqual(expected, resizedUtil));
};

void test_findIndex_returns_1_if_the_search_char_is_found_on_1st_location (){
	int x = 'a';
	char array[] = "car";
	ArrayUtil util = create(CHAR_SIZE,3);
	util.base = (void*)array;
	assertEqual(findIndex(util,&x),1);
}

void* sum (void* hint, void* pv, void* cv){
	int* _pv = (int*)pv;
	int* _cv = (int*)cv;
	int* result = (int*)malloc(INT_SIZE); 
	*result = *_pv + *_cv;
	return result;
}
void test_that_function_creates_new_array_or_not(){
	ArrayUtil array = create(sizeof(int),3);
	int *createArray  = (int*)array.base;
	assertEqual(createArray[0], 0);
	assertEqual(createArray[2], 0);
	assertEqual(array.length, 3);
	assertEqual(array.typeSize, 4);
};


void test_findFirst_returns_the_address_of_the_first_element_in_the_array_that_is_capital(){
    char array1[] = {'k','M','k'};
    ArrayUtil util1 = {array1,sizeof(char),3};
    assertEqual(*(char *)(findFirst(util1,&isCapital,0)), 'M');
}

void test_findFirst_returns_the_address_of_the_first_element_in_the_array_that_is_even(){
    int array1[] = {1,2,3,4,5};
    ArrayUtil util1 = {array1,sizeof(int),5};
    assertEqual(*(int *)(findFirst(util1,&isEven, 0)), 2);
}

void test_findFirst_returns_the_adsdress_of_first_element_in_the_array_greater_than_5() {
    float array1[] = {1.1,6.6,5.5,8.8,2.2};
    ArrayUtil util1 ={array1, sizeof(float),5};
    assertEqual(*(float *)(findFirst(util1,&isGreaterThan5,0)), (float)6.6);
}

void test_findIndex_returns_index_of_the_String_element_where_it_presents(){
    String array1[] = {"Mahesh","Kumar","Kolla"};
    String element = "Kumar";
    ArrayUtil util1 = {array1,sizeof(String),3};
    assertEqual(findIndex(util1,&element), 1);
}

void test_findIndex_returns_index_of_the_char_element_where_it_presents(){
    char array1[] = {'m','a','h','e','s','h'};
    char element = 's';
    ArrayUtil util1 = {array1,sizeof(char),6};
    assertEqual(findIndex(util1,&element), 4);
}

void test_findIndex_returns_index_of_the_float_element_where_it_presents(){
    float array1[] = {1.1,2.2,3.3,4.4};
    float element = 4.4;
    ArrayUtil util1 = {array1,sizeof(float),4};
    assertEqual(findIndex(util1,&element), 3);
}

void test_findIndex_returns_index_of_the_integer_element_where_it_presents(){
    int array1[] = {1,2,3,4,5};
    int element = 2;
    ArrayUtil util1 = {array1,sizeof(int),5};
    assertEqual(findIndex(util1,&element), 1);
}

// void test_resize_returns_new_Array_util_with_String_array_of_new_length_by_putting_0s_in_new_created_spaces(){
//     String array1[] = {"Mahesh","Kumar"}, array2[] = {"Mahesh","Kumar",0,0,0};
//     ArrayUtil util1 = {array1,sizeof(char *),2};
//     ArrayUtil util2 = {array2,sizeof(char *),5};
//     assertEqual(areEqual(resize(util1, 5), util2), 1);    
// }
// void test_resize_returns_new_Array_util_with_String_array_of_new_length_by_removing_extra_values(){
//     String array1[] = {"Mahesh","Kumar","Kolla"}, array2[] = {"Mahesh","Kumar"};
//     ArrayUtil util1 = {array1,sizeof(char *),3};
//     ArrayUtil util2 = {array2,sizeof(char *),2};
//     assertEqual(areEqual(resize(util1, 2), util2), 1);    
// }

void test_ArrayUtil_a_and_ArrayUtil_b_are_will_be_equal_by_each_element_typeof_double(){
	double a [] = {2.34};
	double b [] = {2.34};
	ArrayUtil array1 = {a, sizeof(double), 1};
	ArrayUtil array2 = {b, sizeof(double), 1};

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

int compare(void *hint,void* item){
	if(*(char*)item=='a')
		return 1;
	return 0;
};

int isEqual(void* hint, void* item){
	if(*(int*)item==8 ||*(float*)item == 9.0 || *(double*)item==8.9)
		return 1;
	return 0;
}

int stringCompare(void *hint, void* item){
	String str ="hello";
	String getItem = *(String*)item;
	if(getItem==str)
		return 1;
	return 0;
}


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

//Parmatma done


//beginning pooja g


void test_areEqual_returns_1_if_two_int_array_are_equal(){
	int array1[] = {1,2,3};
	int array2[] = {1,2,3};
	ArrayUtil a1 = create(4,3);
	ArrayUtil a2 = create(4,3);
	a1.base = array1;
	a2.base = array2;
	assertEqual(areEqual(a1,a2),1);
}

void test_areEqual_returns_0_if_two_int_array_are_not_equal(){
	int array1[] = {1,2,4};
	int array2[] = {1,2,3};
	ArrayUtil a1 = create(4,3);
	ArrayUtil a2 = create(4,3);
	a1.base = array1;
	a2.base = array2;
	assertEqual(areEqual(a1,a2),0);
}

void test_areEqual_returns_1_if_two_char_array_are_equal(){
	char array1[] = {'a','b','c'};
	char array2[] = {'a','b','c'};
	ArrayUtil a1 = create(1,3);
	ArrayUtil a2 = create(1,3);
	a1.base = array1;
	a2.base = array2;
	assertEqual(areEqual(a1,a2),1);
}



