#include <stdio.h>
#include <string.h>

#include <iostream>

#ifdef ENABLE_MY_MATH
    #include "my_math.h"
#endif

#ifdef ENABLE_MY_FLASH
    #include "my_flash.h"
#endif

#include "test_add.h"
#include "01_SimpleFactory.h"

using namespace std;

int main(int argc, char *argv[])
{
    UseSimpleFactoryModel();
    printf("C++ Standard is %ld\n", __cplusplus);
    const double input_para1 = stod("1.2");
    const double input_para2 = stod("3.0");
    cout << "test_add_int(6, -2) returned " << test_add_int(6, -2) << endl;
#ifdef ENABLE_MY_MATH
    printf("test_add_double(%lf, %lf) returned %lf\n", input_para1, input_para2, test_add_double(input_para1, input_para2));
    printf("power(2, 10) is %d\n", power(2, 10));
#endif

#ifdef ENABLE_MY_FLASH
    const char my_str[] = "Hello CMake !";
    char buffer[128];
    flash_copy(buffer, my_str, strlen(my_str)+1);
    printf("content in buffer is %s\n", buffer);
#endif
    return 0;
}