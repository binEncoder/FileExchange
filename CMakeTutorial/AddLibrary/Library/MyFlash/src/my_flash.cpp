#ifdef ENABLE_MY_FLASH

#include <string.h>
#include "my_flash.h"


void flash_copy(void *dest, const void *src, uint32_t len)
{
#if 1
    memcpy(dest, src, len);
#else
    char *ptr_dest = (char *)dest;
    const char *ptr_src = (const char *)src;
    for(uint32_t idx = 0; idx < len; idx++){
        *ptr_dest = *ptr_src;
        ptr_dest++;
        ptr_src++;
    }
#endif
}

#endif /* ENABLE_MY_FLASH */