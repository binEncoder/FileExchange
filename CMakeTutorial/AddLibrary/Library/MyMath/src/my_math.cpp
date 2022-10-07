#ifdef ENABLE_MY_MATH

#include "my_math.h"

int power(int x, int y)
{
    int ret = 1;
    for(int idx = 0; idx < y; idx++){
        ret *= x;
    }
    return ret;
}

#endif /* ENABLE_MY_MATH */