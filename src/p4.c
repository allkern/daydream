#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "p4.h"

#define ROTL24(v, r) ((((v) << r) | ((v) >> (24 - r))) & 0xffffff)

p4_state* p4_create() {
    return malloc(sizeof(p4_state));
}

void p4_init(p4_state* p4) {
    memset(p4, 0, sizeof(p4_state));
}

uint32_t p4_read32(void* udata, uint32_t addr) {
    p4_state* p4 = udata;

    switch (ROTL24(addr, 8)) {
        case ROTL24(0x000000, 8): return p4->pteh;
        case ROTL24(0x000004, 8): return p4->ptel;
        case ROTL24(0x000008, 8): return p4->ttb;
        case ROTL24(0x00000c, 8): return p4->tea;
        case ROTL24(0x000010, 8): return p4->mmucr;
        case ROTL24(0x00001c, 8): return p4->ccr;
        case ROTL24(0x000020, 8): return p4->tra;
        case ROTL24(0x000024, 8): return p4->expevt;
        case ROTL24(0x000028, 8): return p4->intevt;
        case ROTL24(0x000034, 8): return p4->ptea;
        case ROTL24(0x000038, 8): return p4->qacr0;
        case ROTL24(0x00003c, 8): return p4->qacr1;
        case ROTL24(0x200000, 8): return p4->bara;
        case ROTL24(0x20000c, 8): return p4->barb;
        case ROTL24(0x200018, 8): return p4->bdrb;
        case ROTL24(0x20001c, 8): return p4->bdmrb;
        case ROTL24(0x800000, 8): return p4->bcr1;
        case ROTL24(0x800008, 8): return p4->wcr1;
        case ROTL24(0x80000c, 8): return p4->wcr2;
        case ROTL24(0x800010, 8): return p4->wcr3;
        case ROTL24(0x800014, 8): return p4->mcr;
        case ROTL24(0x80002c, 8): return p4->pctra;
        case ROTL24(0x800040, 8): return p4->pctrb;
        case ROTL24(0xa00000, 8): return p4->sar0;
        case ROTL24(0xa00004, 8): return p4->dar0;
        case ROTL24(0xa00008, 8): return p4->dmatcr0;
        case ROTL24(0xa0000c, 8): return p4->chcr0;
        case ROTL24(0xa00010, 8): return p4->sar1;
        case ROTL24(0xa00014, 8): return p4->dar1;
        case ROTL24(0xa00018, 8): return p4->dmatcr1;
        case ROTL24(0xa0001c, 8): return p4->chcr1;
        case ROTL24(0xa00020, 8): return p4->sar2;
        case ROTL24(0xa00024, 8): return p4->dar2;
        case ROTL24(0xa00028, 8): return p4->dmatcr2;
        case ROTL24(0xa0002c, 8): return p4->chcr2;
        case ROTL24(0xa00030, 8): return p4->sar3;
        case ROTL24(0xa00034, 8): return p4->dar3;
        case ROTL24(0xa00038, 8): return p4->dmatcr3;
        case ROTL24(0xa0003c, 8): return p4->chcr3;
        case ROTL24(0xa00040, 8): return p4->dmaor;
        case ROTL24(0xd80008, 8): return p4->tcor0;
        case ROTL24(0xd8000c, 8): return p4->tcnt0;
        case ROTL24(0xd80014, 8): return p4->tcor1;
        case ROTL24(0xd80018, 8): return p4->tcnt1;
        case ROTL24(0xd80020, 8): return p4->tcor2;
        case ROTL24(0xd80024, 8): return p4->tcnt2;
        case ROTL24(0xd8002c, 8): return p4->tcpr2;
        case ROTL24(0xf00008, 8): return p4->sddr;
    }

    printf("unhandled 32-bit P4 register read %08x\n", addr);

    return 0;
}

uint32_t p4_read16(void* udata, uint32_t addr) {
    p4_state* p4 = udata;

    switch (ROTL24(addr, 8)) {
        case ROTL24(0x200008, 8): return p4->bbra;
        case ROTL24(0x200014, 8): return p4->bbrb;
        case ROTL24(0x200020, 8): return p4->brcr;
        case ROTL24(0x800004, 8): return p4->bcr2;
        case ROTL24(0x800018, 8): return p4->pcr;
        case ROTL24(0x80001c, 8): return p4->rtcsr;
        case ROTL24(0x800020, 8): return p4->rtcnt;
        case ROTL24(0x800024, 8): return p4->rtcor;
        case ROTL24(0x800028, 8): return p4->rfcr;
        case ROTL24(0x800030, 8): return p4->pdtra;
        case ROTL24(0x800044, 8): return p4->pdtrb;
        case ROTL24(0x800048, 8): return p4->gpioic;
        case ROTL24(0xc00000, 8): return p4->frqcr;
        case ROTL24(0xc8001c, 8): return p4->ryrcnt;
        case ROTL24(0xd00000, 8): return p4->icr;
        case ROTL24(0xd00004, 8): return p4->ipra;
        case ROTL24(0xd00008, 8): return p4->iprb;
        case ROTL24(0xd0000c, 8): return p4->iprc;
        case ROTL24(0xd80010, 8): return p4->tcr0;
        case ROTL24(0xd8001c, 8): return p4->tcr1;
        case ROTL24(0xd80028, 8): return p4->tcr2;
        case ROTL24(0xe80000, 8): return p4->scsmr2;
        case ROTL24(0xe80008, 8): return p4->scscr2;
        case ROTL24(0xe80010, 8): return p4->scfsr2;
        case ROTL24(0xe80018, 8): return p4->scfcr2;
        case ROTL24(0xe8001c, 8): return p4->scfdr2;
        case ROTL24(0xe80020, 8): return p4->scsptr2;
        case ROTL24(0xe80024, 8): return p4->sclsr2;
        case ROTL24(0xf00000, 8): return p4->sdir;
    }

    printf("unhandled 16-bit P4 register read %08x\n", addr);

    return 0;
}

uint32_t p4_read8(void* udata, uint32_t addr) {
    p4_state* p4 = udata;

    switch (ROTL24(addr, 8)) {
        case ROTL24(0x000014, 8): return p4->basra;
        case ROTL24(0x000018, 8): return p4->basrb;
        case ROTL24(0x200004, 8): return p4->bamra;
        case ROTL24(0x200010, 8): return p4->bamrb;
        case ROTL24(0xc00004, 8): return p4->stbcr;
        case ROTL24(0xc00008, 8): return p4->wtcnt;
        case ROTL24(0xc0000c, 8): return p4->wtcsr;
        case ROTL24(0xc00010, 8): return p4->stbcr2;
        case ROTL24(0xc80000, 8): return p4->r64cnt;
        case ROTL24(0xc80004, 8): return p4->rseccnt;
        case ROTL24(0xc80008, 8): return p4->rmincnt;
        case ROTL24(0xc8000c, 8): return p4->rhrcnt;
        case ROTL24(0xc80010, 8): return p4->rwkcnt;
        case ROTL24(0xc80014, 8): return p4->rdaycnt;
        case ROTL24(0xc80018, 8): return p4->rmoncnt;
        case ROTL24(0xc80020, 8): return p4->rsecar;
        case ROTL24(0xc80024, 8): return p4->rminar;
        case ROTL24(0xc80028, 8): return p4->rhrar;
        case ROTL24(0xc8002c, 8): return p4->rwkar;
        case ROTL24(0xc80030, 8): return p4->rdayar;
        case ROTL24(0xc80034, 8): return p4->rmonar;
        case ROTL24(0xc80038, 8): return p4->rcr1;
        case ROTL24(0xc8003c, 8): return p4->rcr2;
        case ROTL24(0xd80000, 8): return p4->tocr;
        case ROTL24(0xd80004, 8): return p4->tstr;
        case ROTL24(0xe00000, 8): return p4->scsmr1;
        case ROTL24(0xe00004, 8): return p4->scbrr1;
        case ROTL24(0xe00008, 8): return p4->scscr1;
        case ROTL24(0xe0000c, 8): return p4->sctdr1;
        case ROTL24(0xe00010, 8): return p4->scssr1;
        case ROTL24(0xe00014, 8): return p4->scrdr1;
        case ROTL24(0xe00018, 8): return p4->scscmr1;
        case ROTL24(0xe0001c, 8): return p4->scsptr1;
        case ROTL24(0xe80004, 8): return p4->scbrr2;
        case ROTL24(0xe8000c, 8): return p4->scftdr2;
        case ROTL24(0xe80014, 8): return p4->scfrdr2;
    }

    printf("unhandled 8-bit P4 register read %08x\n", addr);

    return 0;
}

void p4_write32(void* udata, uint32_t addr, uint32_t data) {
    p4_state* p4 = udata;

    switch (ROTL24(addr, 8)) {
        case ROTL24(0x000000, 8): p4->pteh = data; return;
        case ROTL24(0x000004, 8): p4->ptel = data; return;
        case ROTL24(0x000008, 8): p4->ttb = data; return;
        case ROTL24(0x00000c, 8): p4->tea = data; return;
        case ROTL24(0x000010, 8): p4->mmucr = data; return;
        case ROTL24(0x00001c, 8): p4->ccr = data; return;
        case ROTL24(0x000020, 8): p4->tra = data; return;
        case ROTL24(0x000024, 8): p4->expevt = data; return;
        case ROTL24(0x000028, 8): p4->intevt = data; return;
        case ROTL24(0x000034, 8): p4->ptea = data; return;
        case ROTL24(0x000038, 8): p4->qacr0 = data; return;
        case ROTL24(0x00003c, 8): p4->qacr1 = data; return;
        case ROTL24(0x200000, 8): p4->bara = data; return;
        case ROTL24(0x20000c, 8): p4->barb = data; return;
        case ROTL24(0x200018, 8): p4->bdrb = data; return;
        case ROTL24(0x20001c, 8): p4->bdmrb = data; return;
        case ROTL24(0x800000, 8): p4->bcr1 = data; return;
        case ROTL24(0x800008, 8): p4->wcr1 = data; return;
        case ROTL24(0x80000c, 8): p4->wcr2 = data; return;
        case ROTL24(0x800010, 8): p4->wcr3 = data; return;
        case ROTL24(0x800014, 8): p4->mcr = data; return;
        case ROTL24(0x80002c, 8): p4->pctra = data; return;
        case ROTL24(0x800040, 8): p4->pctrb = data; return;
        case ROTL24(0xa00000, 8): p4->sar0 = data; return;
        case ROTL24(0xa00004, 8): p4->dar0 = data; return;
        case ROTL24(0xa00008, 8): p4->dmatcr0 = data; return;
        case ROTL24(0xa0000c, 8): p4->chcr0 = data; return;
        case ROTL24(0xa00010, 8): p4->sar1 = data; return;
        case ROTL24(0xa00014, 8): p4->dar1 = data; return;
        case ROTL24(0xa00018, 8): p4->dmatcr1 = data; return;
        case ROTL24(0xa0001c, 8): p4->chcr1 = data; return;
        case ROTL24(0xa00020, 8): p4->sar2 = data; return;
        case ROTL24(0xa00024, 8): p4->dar2 = data; return;
        case ROTL24(0xa00028, 8): p4->dmatcr2 = data; return;
        case ROTL24(0xa0002c, 8): p4->chcr2 = data; return;
        case ROTL24(0xa00030, 8): p4->sar3 = data; return;
        case ROTL24(0xa00034, 8): p4->dar3 = data; return;
        case ROTL24(0xa00038, 8): p4->dmatcr3 = data; return;
        case ROTL24(0xa0003c, 8): p4->chcr3 = data; return;
        case ROTL24(0xa00040, 8): p4->dmaor = data; return;
        case ROTL24(0xd80008, 8): p4->tcor0 = data; return;
        case ROTL24(0xd8000c, 8): p4->tcnt0 = data; return;
        case ROTL24(0xd80014, 8): p4->tcor1 = data; return;
        case ROTL24(0xd80018, 8): p4->tcnt1 = data; return;
        case ROTL24(0xd80020, 8): p4->tcor2 = data; return;
        case ROTL24(0xd80024, 8): p4->tcnt2 = data; return;
        case ROTL24(0xd8002c, 8): p4->tcpr2 = data; return;
        case ROTL24(0xf00008, 8): p4->sddr = data; return;
    }

    printf("unhandled 32-bit P4 register write %08x (%08x)\n", addr, data);
}

void p4_write16(void* udata, uint32_t addr, uint32_t data) {
    p4_state* p4 = udata;

    switch (ROTL24(addr, 8)) {
        case ROTL24(0x200008, 8): p4->bbra = data; return;
        case ROTL24(0x200014, 8): p4->bbrb = data; return;
        case ROTL24(0x200020, 8): p4->brcr = data; return;
        case ROTL24(0x800004, 8): p4->bcr2 = data; return;
        case ROTL24(0x800018, 8): p4->pcr = data; return;
        case ROTL24(0x80001c, 8): p4->rtcsr = data; return;
        case ROTL24(0x800020, 8): p4->rtcnt = data; return;
        case ROTL24(0x800024, 8): p4->rtcor = data; return;
        case ROTL24(0x800028, 8): p4->rfcr = data; return;
        case ROTL24(0x800030, 8): p4->pdtra = data; return;
        case ROTL24(0x800044, 8): p4->pdtrb = data; return;
        case ROTL24(0x800048, 8): p4->gpioic = data; return;
        case ROTL24(0xc00000, 8): p4->frqcr = data; return;
        case ROTL24(0xc8001c, 8): p4->ryrcnt = data; return;
        case ROTL24(0xd00000, 8): p4->icr = data; return;
        case ROTL24(0xd00004, 8): p4->ipra = data; return;
        case ROTL24(0xd00008, 8): p4->iprb = data; return;
        case ROTL24(0xd0000c, 8): p4->iprc = data; return;
        case ROTL24(0xd80010, 8): p4->tcr0 = data; return;
        case ROTL24(0xd8001c, 8): p4->tcr1 = data; return;
        case ROTL24(0xd80028, 8): p4->tcr2 = data; return;
        case ROTL24(0xe80000, 8): p4->scsmr2 = data; return;
        case ROTL24(0xe80008, 8): p4->scscr2 = data; return;
        case ROTL24(0xe80010, 8): p4->scfsr2 = data; return;
        case ROTL24(0xe80018, 8): p4->scfcr2 = data; return;
        case ROTL24(0xe8001c, 8): p4->scfdr2 = data; return;
        case ROTL24(0xe80020, 8): p4->scsptr2 = data; return;
        case ROTL24(0xe80024, 8): p4->sclsr2 = data; return;
        case ROTL24(0xf00000, 8): p4->sdir = data; return;
    }

    printf("unhandled 16-bit P4 register write %08x (%08x)\n", addr, data);
}

void p4_write8(void* udata, uint32_t addr, uint32_t data) {
    p4_state* p4 = udata;

    switch (ROTL24(addr, 8)) {
        case ROTL24(0x000014, 8): p4->basra = data; return;
        case ROTL24(0x000018, 8): p4->basrb = data; return;
        case ROTL24(0x200004, 8): p4->bamra = data; return;
        case ROTL24(0x200010, 8): p4->bamrb = data; return;
        case ROTL24(0xc00004, 8): p4->stbcr = data; return;
        case ROTL24(0xc00008, 8): p4->wtcnt = data; return;
        case ROTL24(0xc0000c, 8): p4->wtcsr = data; return;
        case ROTL24(0xc00010, 8): p4->stbcr2 = data; return;
        case ROTL24(0xc80000, 8): p4->r64cnt = data; return;
        case ROTL24(0xc80004, 8): p4->rseccnt = data; return;
        case ROTL24(0xc80008, 8): p4->rmincnt = data; return;
        case ROTL24(0xc8000c, 8): p4->rhrcnt = data; return;
        case ROTL24(0xc80010, 8): p4->rwkcnt = data; return;
        case ROTL24(0xc80014, 8): p4->rdaycnt = data; return;
        case ROTL24(0xc80018, 8): p4->rmoncnt = data; return;
        case ROTL24(0xc80020, 8): p4->rsecar = data; return;
        case ROTL24(0xc80024, 8): p4->rminar = data; return;
        case ROTL24(0xc80028, 8): p4->rhrar = data; return;
        case ROTL24(0xc8002c, 8): p4->rwkar = data; return;
        case ROTL24(0xc80030, 8): p4->rdayar = data; return;
        case ROTL24(0xc80034, 8): p4->rmonar = data; return;
        case ROTL24(0xc80038, 8): p4->rcr1 = data; return;
        case ROTL24(0xc8003c, 8): p4->rcr2 = data; return;
        case ROTL24(0xd80000, 8): p4->tocr = data; return;
        case ROTL24(0xd80004, 8): p4->tstr = data; return;
        case ROTL24(0xe00000, 8): p4->scsmr1 = data; return;
        case ROTL24(0xe00004, 8): p4->scbrr1 = data; return;
        case ROTL24(0xe00008, 8): p4->scscr1 = data; return;
        case ROTL24(0xe0000c, 8): p4->sctdr1 = data; return;
        case ROTL24(0xe00010, 8): p4->scssr1 = data; return;
        case ROTL24(0xe00014, 8): p4->scrdr1 = data; return;
        case ROTL24(0xe00018, 8): p4->scscmr1 = data; return;
        case ROTL24(0xe0001c, 8): p4->scsptr1 = data; return;
        case ROTL24(0xe80004, 8): p4->scbrr2 = data; return;
        case ROTL24(0xe8000c, 8): p4->scftdr2 = data; return;
        case ROTL24(0xe80014, 8): p4->scfrdr2 = data; return;
    }

    printf("unhandled 8-bit P4 register write %08x (%08x)\n", addr, data);
}

void p4_destroy(p4_state* p4) {
    free(p4);
}