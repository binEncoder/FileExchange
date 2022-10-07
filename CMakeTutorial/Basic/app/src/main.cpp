#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <iostream>

#include "test_add.h"
#include "01_SimpleFactory.h"

using namespace std;

typedef uint16_t array_item_t;

typedef struct{
    array_item_t *elements;
    uint16_t ele_number;
    uint16_t ele_capacity;
} max_array_t;

max_array_t* max_array_init(uint16_t capacity)
{
    max_array_t *max_array = (max_array_t *)malloc(sizeof(max_array_t) + sizeof(array_item_t)*capacity);
    max_array->elements = (array_item_t *)((char *)max_array + sizeof(max_array_t));
    max_array->ele_capacity = capacity;
    max_array->ele_number = 0;
    memset(max_array->elements, 0x00, sizeof(array_item_t)*max_array->ele_capacity);
    //printf("max array is initialized.\n");
    return max_array;
}


void max_array_destroy(max_array_t **array)
{
    free(*array);
    *array = NULL;
}


void max_array_insert(max_array_t *array, array_item_t element)
{
    int idx = 0, item_idx;
    for(idx = 0; idx < array->ele_number; idx++){
        if(array->elements[idx] < element){
            break;
        }
    }
    if(idx == array->ele_capacity){
        return;
    }
    //printf("max_array_insert idx is %d, number is %d\n", idx, array->ele_number);

    item_idx = array->ele_number;
    while(item_idx > idx ){
        //assert(item_idx < array->ele_capacity);
        array->elements[item_idx] = array->elements[item_idx-1];
        --item_idx;
        //printf("max_array_insert item_idx: %d\n", item_idx);
    }
    array->elements[idx] = element;
    if(array->ele_number < array->ele_capacity){
        ++array->ele_number;
    }
}


void max_array_print(max_array_t *array)
{
    printf("array number: %d, capacity: %d\n", array->ele_number, array->ele_capacity);
    for(uint16_t idx = 0; idx < array->ele_number; idx++){
        printf("%d ", array->elements[idx]);
    }
    printf("\n\n");
}



int main(int argc, char *argv[])
{
    UseSimpleFactoryModel();
    printf("C++ Standard is %ld\n", __cplusplus);
    const double input_para1 = stod("1.2");
    const double input_para2 = stod("3.0");
    cout << "test_add_int(6, -2) returned " << test_add_int(6, -2) << endl;
    printf("test_add_double(%lf, %lf) returned %lf\n", input_para1, input_para2, test_add_double(input_para1, input_para2));

    uint16_t items[] = { 1009, 22, 3, 46, 5, 6, 7, 8, 59, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 };
    max_array_t* array = max_array_init(30);
    for(int idx = 0; idx < sizeof(items)/sizeof(uint16_t); idx++){
        max_array_insert(array, items[idx]);
    }
    max_array_print(array);
    max_array_destroy(&array);
    return 0;
}