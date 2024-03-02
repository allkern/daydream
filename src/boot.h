#ifndef BOOT_H
#define BOOT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdlib.h>

typedef struct {
    uint8_t* buf;
} boot_state;

boot_state* boot_create();
void boot_init(boot_state* boot, const char* path);
uint32_t boot_read32(void* udata, uint32_t addr);
uint32_t boot_read16(void* udata, uint32_t addr);
uint32_t boot_read8(void* udata, uint32_t addr);
void boot_write32(void* udata, uint32_t addr, uint32_t data);
void boot_write16(void* udata, uint32_t addr, uint32_t data);
void boot_write8(void* udata, uint32_t addr, uint32_t data);
void boot_destroy(boot_state* boot);

#ifdef __cplusplus
}
#endif

#endif