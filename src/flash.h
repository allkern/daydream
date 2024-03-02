#ifndef FLASH_H
#define FLASH_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdlib.h>

typedef struct {
    uint8_t* buf;
} flash_state;

flash_state* flash_create();
void flash_init(flash_state* flash, const char* path);
uint32_t flash_read32(void* udata, uint32_t addr);
uint32_t flash_read16(void* udata, uint32_t addr);
uint32_t flash_read8(void* udata, uint32_t addr);
void flash_write32(void* udata, uint32_t addr, uint32_t data);
void flash_write16(void* udata, uint32_t addr, uint32_t data);
void flash_write8(void* udata, uint32_t addr, uint32_t data);
void flash_destroy(flash_state* flash);

#ifdef __cplusplus
}
#endif

#endif