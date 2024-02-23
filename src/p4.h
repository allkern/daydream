#ifndef P4_H
#define P4_H

#include <stdint.h>
#include <stdlib.h>

typedef struct {
    uint32_t pteh;    // 0x1f000000
    uint32_t ptel;    // 0x1f000004
    uint32_t ttb;     // 0x1f000008
    uint32_t tea;     // 0x1f00000c
    uint32_t mmucr;   // 0x1f000010
    uint8_t  basra;   // 0x1f000014
    uint8_t  basrb;   // 0x1f000018
    uint32_t ccr;     // 0x1f00001c
    uint32_t tra;     // 0x1f000020
    uint32_t expevt;  // 0x1f000024
    uint32_t intevt;  // 0x1f000028
    uint32_t ptea;    // 0x1f000034
    uint32_t qacr0;   // 0x1f000038
    uint32_t qacr1;   // 0x1f00003c
    uint32_t bara;    // 0x1f200000
    uint8_t  bamra;   // 0x1f200004
    uint16_t bbra;    // 0x1f200008
    uint32_t barb;    // 0x1f20000c
    uint8_t  bamrb;   // 0x1f200010
    uint16_t bbrb;    // 0x1f200014
    uint32_t bdrb;    // 0x1f200018
    uint32_t bdmrb;   // 0x1f20001c
    uint16_t brcr;    // 0x1f200020
    uint32_t bcr1;    // 0x1f800000
    uint16_t bcr2;    // 0x1f800004
    uint32_t wcr1;    // 0x1f800008
    uint32_t wcr2;    // 0x1f80000c
    uint32_t wcr3;    // 0x1f800010
    uint32_t mcr;     // 0x1f800014
    uint16_t pcr;     // 0x1f800018
    uint16_t rtcsr;   // 0x1f80001c
    uint16_t rtcnt;   // 0x1f800020
    uint16_t rtcor;   // 0x1f800024
    uint16_t rfcr;    // 0x1f800028
    uint32_t pctra;   // 0x1f80002c
    uint16_t pdtra;   // 0x1f800030
    uint32_t pctrb;   // 0x1f800040
    uint16_t pdtrb;   // 0x1f800044
    uint16_t gpioic;  // 0x1f800048
    uint32_t sar0;    // 0x1fa00000
    uint32_t dar0;    // 0x1fa00004
    uint32_t dmatcr0; // 0x1fa00008
    uint32_t chcr0;   // 0x1fa0000c
    uint32_t sar1;    // 0x1fa00010
    uint32_t dar1;    // 0x1fa00014
    uint32_t dmatcr1; // 0x1fa00018
    uint32_t chcr1;   // 0x1fa0001c
    uint32_t sar2;    // 0x1fa00020
    uint32_t dar2;    // 0x1fa00024
    uint32_t dmatcr2; // 0x1fa00028
    uint32_t chcr2;   // 0x1fa0002c
    uint32_t sar3;    // 0x1fa00030
    uint32_t dar3;    // 0x1fa00034
    uint32_t dmatcr3; // 0x1fa00038
    uint32_t chcr3;   // 0x1fa0003c
    uint32_t dmaor;   // 0x1fa00040
    uint16_t frqcr;   // 0x1fc00000
    uint8_t  stbcr;   // 0x1fc00004
    uint8_t  wtcnt;   // 0x1fc00008
    uint8_t  wtcsr;   // 0x1fc0000c
    uint8_t  stbcr2;  // 0x1fc00010
    uint8_t  r64cnt;  // 0x1fc80000
    uint8_t  rseccnt; // 0x1fc80004
    uint8_t  rmincnt; // 0x1fc80008
    uint8_t  rhrcnt;  // 0x1fc8000c
    uint8_t  rwkcnt;  // 0x1fc80010
    uint8_t  rdaycnt; // 0x1fc80014
    uint8_t  rmoncnt; // 0x1fc80018
    uint16_t ryrcnt;  // 0x1fc8001c
    uint8_t  rsecar;  // 0x1fc80020
    uint8_t  rminar;  // 0x1fc80024
    uint8_t  rhrar;   // 0x1fc80028
    uint8_t  rwkar;   // 0x1fc8002c
    uint8_t  rdayar;  // 0x1fc80030
    uint8_t  rmonar;  // 0x1fc80034
    uint8_t  rcr1;    // 0x1fc80038
    uint8_t  rcr2;    // 0x1fc8003c
    uint16_t icr;     // 0x1fd00000
    uint16_t ipra;    // 0x1fd00004
    uint16_t iprb;    // 0x1fd00008
    uint16_t iprc;    // 0x1fd0000c
    uint8_t  tocr;    // 0x1fd80000
    uint8_t  tstr;    // 0x1fd80004
    uint32_t tcor0;   // 0x1fd80008
    uint32_t tcnt0;   // 0x1fd8000c
    uint16_t tcr0;    // 0x1fd80010
    uint32_t tcor1;   // 0x1fd80014
    uint32_t tcnt1;   // 0x1fd80018
    uint16_t tcr1;    // 0x1fd8001c
    uint32_t tcor2;   // 0x1fd80020
    uint32_t tcnt2;   // 0x1fd80024
    uint16_t tcr2;    // 0x1fd80028
    uint32_t tcpr2;   // 0x1fd8002c
    uint8_t  scsmr1;  // 0x1fe00000
    uint8_t  scbrr1;  // 0x1fe00004
    uint8_t  scscr1;  // 0x1fe00008
    uint8_t  sctdr1;  // 0x1fe0000c
    uint8_t  scssr1;  // 0x1fe00010
    uint8_t  scrdr1;  // 0x1fe00014
    uint8_t  scscmr1; // 0x1fe00018
    uint8_t  scsptr1; // 0x1fe0001c
    uint16_t scsmr2;  // 0x1fe80000
    uint8_t  scbrr2;  // 0x1fe80004
    uint16_t scscr2;  // 0x1fe80008
    uint8_t  scftdr2; // 0x1fe8000c
    uint16_t scfsr2;  // 0x1fe80010
    uint8_t  scfrdr2; // 0x1fe80014
    uint16_t scfcr2;  // 0x1fe80018
    uint16_t scfdr2;  // 0x1fe8001c
    uint16_t scsptr2; // 0x1fe80020
    uint16_t sclsr2;  // 0x1fe80024
    uint16_t sdir;    // 0x1ff00000
    uint32_t sddr;    // 0x1ff00008
    // uint8_t  sdmr2;   // 0x1f90xxxx
    // uint8_t  sdmr3;   // 0x1f94xxxx
} p4_state;

p4_state* p4_create();
void p4_init(p4_state* p4);
uint32_t p4_read32(void* udata, uint32_t addr);
uint32_t p4_read16(void* udata, uint32_t addr);
uint32_t p4_read8(void* udata, uint32_t addr);
void p4_write32(void* udata, uint32_t addr, uint32_t data);
void p4_write16(void* udata, uint32_t addr, uint32_t data);
void p4_write8(void* udata, uint32_t addr, uint32_t data);
void p4_destroy(p4_state* p4);

#endif