#ifndef __MY_FLASH_H__
#define __MY_FLASH_H__

#ifdef ENABLE_MY_FLASH

    #ifdef __cplusplus
    extern "C" {
    #endif


    #include <stdint.h>

    void flash_copy(void *dest, const void *src, uint32_t len);


    #ifdef __cplusplus
    }
    #endif

#endif /* ENABLE_MY_FLASH */

#endif /* __MY_FLASH_H__ */