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
        case ROTL24(0x000000ul, 8): return p4->pteh;
        case ROTL24(0x000004ul, 8): return p4->ptel;
        case ROTL24(0x000008ul, 8): return p4->ttb;
        case ROTL24(0x00000cul, 8): return p4->tea;
        case ROTL24(0x000010ul, 8): return p4->mmucr;
        case ROTL24(0x00001cul, 8): return p4->ccr;
        case ROTL24(0x000020ul, 8): return p4->tra;
        case ROTL24(0x000024ul, 8): return p4->expevt;
        case ROTL24(0x000028ul, 8): return p4->intevt;
        case ROTL24(0x000034ul, 8): return p4->ptea;
        case ROTL24(0x000038ul, 8): return p4->qacr0;
        case ROTL24(0x00003cul, 8): return p4->qacr1;
        case ROTL24(0x200000ul, 8): return p4->bara;
        case ROTL24(0x20000cul, 8): return p4->barb;
        case ROTL24(0x200018ul, 8): return p4->bdrb;
        case ROTL24(0x20001cul, 8): return p4->bdmrb;
        case ROTL24(0x800000ul, 8): return p4->bcr1;
        case ROTL24(0x800008ul, 8): return p4->wcr1;
        case ROTL24(0x80000cul, 8): return p4->wcr2;
        case ROTL24(0x800010ul, 8): return p4->wcr3;
        case ROTL24(0x800014ul, 8): return p4->mcr;
        case ROTL24(0x80002cul, 8): return p4->pctra;
        case ROTL24(0x800040ul, 8): return p4->pctrb;
        case ROTL24(0xa00000ul, 8): return p4->sar0;
        case ROTL24(0xa00004ul, 8): return p4->dar0;
        case ROTL24(0xa00008ul, 8): return p4->dmatcr0;
        case ROTL24(0xa0000cul, 8): return p4->chcr0;
        case ROTL24(0xa00010ul, 8): return p4->sar1;
        case ROTL24(0xa00014ul, 8): return p4->dar1;
        case ROTL24(0xa00018ul, 8): return p4->dmatcr1;
        case ROTL24(0xa0001cul, 8): return p4->chcr1;
        case ROTL24(0xa00020ul, 8): return p4->sar2;
        case ROTL24(0xa00024ul, 8): return p4->dar2;
        case ROTL24(0xa00028ul, 8): return p4->dmatcr2;
        case ROTL24(0xa0002cul, 8): return p4->chcr2;
        case ROTL24(0xa00030ul, 8): return p4->sar3;
        case ROTL24(0xa00034ul, 8): return p4->dar3;
        case ROTL24(0xa00038ul, 8): return p4->dmatcr3;
        case ROTL24(0xa0003cul, 8): return p4->chcr3;
        case ROTL24(0xa00040ul, 8): return p4->dmaor;
        case ROTL24(0xd80008ul, 8): return p4->tcor0;
        case ROTL24(0xd8000cul, 8): return p4->tcnt0;
        case ROTL24(0xd80014ul, 8): return p4->tcor1;
        case ROTL24(0xd80018ul, 8): return p4->tcnt1;
        case ROTL24(0xd80020ul, 8): return p4->tcor2;
        case ROTL24(0xd80024ul, 8): return p4->tcnt2;
        case ROTL24(0xd8002cul, 8): return p4->tcpr2;
        case ROTL24(0xf00008ul, 8): return p4->sddr;
    }

    printf("unhandled 32-bit P4 register read %08x\n", addr);

    return 0;
}

uint32_t p4_read16(void* udata, uint32_t addr) {
    p4_state* p4 = udata;

    switch (ROTL24(addr, 8)) {
        case ROTL24(0x200008ul, 8): return p4->bbra;
        case ROTL24(0x200014ul, 8): return p4->bbrb;
        case ROTL24(0x200020ul, 8): return p4->brcr;
        case ROTL24(0x800004ul, 8): return p4->bcr2;
        case ROTL24(0x800018ul, 8): return p4->pcr;
        case ROTL24(0x80001cul, 8): return p4->rtcsr;
        case ROTL24(0x800020ul, 8): return p4->rtcnt;
        case ROTL24(0x800024ul, 8): return p4->rtcor;
        case ROTL24(0x800028ul, 8): return p4->rfcr;
        case ROTL24(0x800030ul, 8): return p4->pdtra;
        case ROTL24(0x800044ul, 8): return p4->pdtrb;
        case ROTL24(0x800048ul, 8): return p4->gpioic;
        case ROTL24(0xc00000ul, 8): return p4->frqcr;
        case ROTL24(0xc8001cul, 8): return p4->ryrcnt;
        case ROTL24(0xd00000ul, 8): return p4->icr;
        case ROTL24(0xd00004ul, 8): return p4->ipra;
        case ROTL24(0xd00008ul, 8): return p4->iprb;
        case ROTL24(0xd0000cul, 8): return p4->iprc;
        case ROTL24(0xd80010ul, 8): return p4->tcr0;
        case ROTL24(0xd8001cul, 8): return p4->tcr1;
        case ROTL24(0xd80028ul, 8): return p4->tcr2;
        case ROTL24(0xe80000ul, 8): return p4->scsmr2;
        case ROTL24(0xe80008ul, 8): return p4->scscr2;
        case ROTL24(0xe80010ul, 8): return p4->scfsr2;
        case ROTL24(0xe80018ul, 8): return p4->scfcr2;
        case ROTL24(0xe8001cul, 8): return p4->scfdr2;
        case ROTL24(0xe80020ul, 8): return p4->scsptr2;
        case ROTL24(0xe80024ul, 8): return p4->sclsr2;
        case ROTL24(0xf00000ul, 8): return p4->sdir;
    }

    printf("unhandled 16-bit P4 register read %08x\n", addr);

    return 0;
}

uint32_t p4_read8(void* udata, uint32_t addr) {
    p4_state* p4 = udata;

    switch (ROTL24(addr, 8)) {
        case ROTL24(0x000014ul, 8): return p4->basra;
        case ROTL24(0x000018ul, 8): return p4->basrb;
        case ROTL24(0x200004ul, 8): return p4->bamra;
        case ROTL24(0x200010ul, 8): return p4->bamrb;
        case ROTL24(0xc00004ul, 8): return p4->stbcr;
        case ROTL24(0xc00008ul, 8): return p4->wtcnt;
        case ROTL24(0xc0000cul, 8): return p4->wtcsr;
        case ROTL24(0xc00010ul, 8): return p4->stbcr2;
        case ROTL24(0xc80000ul, 8): return p4->r64cnt;
        case ROTL24(0xc80004ul, 8): return p4->rseccnt;
        case ROTL24(0xc80008ul, 8): return p4->rmincnt;
        case ROTL24(0xc8000cul, 8): return p4->rhrcnt;
        case ROTL24(0xc80010ul, 8): return p4->rwkcnt;
        case ROTL24(0xc80014ul, 8): return p4->rdaycnt;
        case ROTL24(0xc80018ul, 8): return p4->rmoncnt;
        case ROTL24(0xc80020ul, 8): return p4->rsecar;
        case ROTL24(0xc80024ul, 8): return p4->rminar;
        case ROTL24(0xc80028ul, 8): return p4->rhrar;
        case ROTL24(0xc8002cul, 8): return p4->rwkar;
        case ROTL24(0xc80030ul, 8): return p4->rdayar;
        case ROTL24(0xc80034ul, 8): return p4->rmonar;
        case ROTL24(0xc80038ul, 8): return p4->rcr1;
        case ROTL24(0xc8003cul, 8): return p4->rcr2;
        case ROTL24(0xd80000ul, 8): return p4->tocr;
        case ROTL24(0xd80004ul, 8): return p4->tstr;
        case ROTL24(0xe00000ul, 8): return p4->scsmr1;
        case ROTL24(0xe00004ul, 8): return p4->scbrr1;
        case ROTL24(0xe00008ul, 8): return p4->scscr1;
        case ROTL24(0xe0000cul, 8): return p4->sctdr1;
        case ROTL24(0xe00010ul, 8): return p4->scssr1;
        case ROTL24(0xe00014ul, 8): return p4->scrdr1;
        case ROTL24(0xe00018ul, 8): return p4->scscmr1;
        case ROTL24(0xe0001cul, 8): return p4->scsptr1;
        case ROTL24(0xe80004ul, 8): return p4->scbrr2;
        case ROTL24(0xe8000cul, 8): return p4->scftdr2;
        case ROTL24(0xe80014ul, 8): return p4->scfrdr2;
    }

    printf("unhandled 8-bit P4 register read %08x\n", addr);

    return 0;
}

void p4_write32(void* udata, uint32_t addr, uint32_t data) {
    p4_state* p4 = udata;

    switch (ROTL24(addr, 8)) {
        case ROTL24(0x000000ul, 8): p4->pteh = data; return;
        case ROTL24(0x000004ul, 8): p4->ptel = data; return;
        case ROTL24(0x000008ul, 8): p4->ttb = data; return;
        case ROTL24(0x00000cul, 8): p4->tea = data; return;
        case ROTL24(0x000010ul, 8): p4->mmucr = data; return;
        case ROTL24(0x00001cul, 8): p4->ccr = data; return;
        case ROTL24(0x000020ul, 8): p4->tra = data; return;
        case ROTL24(0x000024ul, 8): p4->expevt = data; return;
        case ROTL24(0x000028ul, 8): p4->intevt = data; return;
        case ROTL24(0x000034ul, 8): p4->ptea = data; return;
        case ROTL24(0x000038ul, 8): p4->qacr0 = data; return;
        case ROTL24(0x00003cul, 8): p4->qacr1 = data; return;
        case ROTL24(0x200000ul, 8): p4->bara = data; return;
        case ROTL24(0x20000cul, 8): p4->barb = data; return;
        case ROTL24(0x200018ul, 8): p4->bdrb = data; return;
        case ROTL24(0x20001cul, 8): p4->bdmrb = data; return;
        case ROTL24(0x800000ul, 8): p4->bcr1 = data; return;
        case ROTL24(0x800008ul, 8): p4->wcr1 = data; return;
        case ROTL24(0x80000cul, 8): p4->wcr2 = data; return;
        case ROTL24(0x800010ul, 8): p4->wcr3 = data; return;
        case ROTL24(0x800014ul, 8): p4->mcr = data; return;
        case ROTL24(0x80002cul, 8): p4->pctra = data; return;
        case ROTL24(0x800040ul, 8): p4->pctrb = data; return;
        case ROTL24(0xa00000ul, 8): p4->sar0 = data; return;
        case ROTL24(0xa00004ul, 8): p4->dar0 = data; return;
        case ROTL24(0xa00008ul, 8): p4->dmatcr0 = data; return;
        case ROTL24(0xa0000cul, 8): p4->chcr0 = data; return;
        case ROTL24(0xa00010ul, 8): p4->sar1 = data; return;
        case ROTL24(0xa00014ul, 8): p4->dar1 = data; return;
        case ROTL24(0xa00018ul, 8): p4->dmatcr1 = data; return;
        case ROTL24(0xa0001cul, 8): p4->chcr1 = data; return;
        case ROTL24(0xa00020ul, 8): p4->sar2 = data; return;
        case ROTL24(0xa00024ul, 8): p4->dar2 = data; return;
        case ROTL24(0xa00028ul, 8): p4->dmatcr2 = data; return;
        case ROTL24(0xa0002cul, 8): p4->chcr2 = data; return;
        case ROTL24(0xa00030ul, 8): p4->sar3 = data; return;
        case ROTL24(0xa00034ul, 8): p4->dar3 = data; return;
        case ROTL24(0xa00038ul, 8): p4->dmatcr3 = data; return;
        case ROTL24(0xa0003cul, 8): p4->chcr3 = data; return;
        case ROTL24(0xa00040ul, 8): p4->dmaor = data; return;
        case ROTL24(0xd80008ul, 8): p4->tcor0 = data; return;
        case ROTL24(0xd8000cul, 8): p4->tcnt0 = data; return;
        case ROTL24(0xd80014ul, 8): p4->tcor1 = data; return;
        case ROTL24(0xd80018ul, 8): p4->tcnt1 = data; return;
        case ROTL24(0xd80020ul, 8): p4->tcor2 = data; return;
        case ROTL24(0xd80024ul, 8): p4->tcnt2 = data; return;
        case ROTL24(0xd8002cul, 8): p4->tcpr2 = data; return;
        case ROTL24(0xf00008ul, 8): p4->sddr = data; return;
    }

    printf("unhandled 32-bit P4 register write %08x (%08x)\n", addr, data);
}

void p4_write16(void* udata, uint32_t addr, uint32_t data) {
    p4_state* p4 = udata;

    switch (ROTL24(addr, 8)) {
        case ROTL24(0x200008ul, 8): p4->bbra = data; return;
        case ROTL24(0x200014ul, 8): p4->bbrb = data; return;
        case ROTL24(0x200020ul, 8): p4->brcr = data; return;
        case ROTL24(0x800004ul, 8): p4->bcr2 = data; return;
        case ROTL24(0x800018ul, 8): p4->pcr = data; return;
        case ROTL24(0x80001cul, 8): p4->rtcsr = data; return;
        case ROTL24(0x800020ul, 8): p4->rtcnt = data; return;
        case ROTL24(0x800024ul, 8): p4->rtcor = data; return;
        case ROTL24(0x800028ul, 8): p4->rfcr = data; return;
        case ROTL24(0x800030ul, 8): p4->pdtra = data; return;
        case ROTL24(0x800044ul, 8): p4->pdtrb = data; return;
        case ROTL24(0x800048ul, 8): p4->gpioic = data; return;
        case ROTL24(0xc00000ul, 8): p4->frqcr = data; return;
        case ROTL24(0xc8001cul, 8): p4->ryrcnt = data; return;
        case ROTL24(0xd00000ul, 8): p4->icr = data; return;
        case ROTL24(0xd00004ul, 8): p4->ipra = data; return;
        case ROTL24(0xd00008ul, 8): p4->iprb = data; return;
        case ROTL24(0xd0000cul, 8): p4->iprc = data; return;
        case ROTL24(0xd80010ul, 8): p4->tcr0 = data; return;
        case ROTL24(0xd8001cul, 8): p4->tcr1 = data; return;
        case ROTL24(0xd80028ul, 8): p4->tcr2 = data; return;
        case ROTL24(0xe80000ul, 8): p4->scsmr2 = data; return;
        case ROTL24(0xe80008ul, 8): p4->scscr2 = data; return;
        case ROTL24(0xe80010ul, 8): p4->scfsr2 = data; return;
        case ROTL24(0xe80018ul, 8): p4->scfcr2 = data; return;
        case ROTL24(0xe8001cul, 8): p4->scfdr2 = data; return;
        case ROTL24(0xe80020ul, 8): p4->scsptr2 = data; return;
        case ROTL24(0xe80024ul, 8): p4->sclsr2 = data; return;
        case ROTL24(0xf00000ul, 8): p4->sdir = data; return;
    }

    printf("unhandled 16-bit P4 register write %08x (%08x)\n", addr, data);
}

void p4_write8(void* udata, uint32_t addr, uint32_t data) {
    p4_state* p4 = udata;

    switch (ROTL24(addr, 8)) {
        case ROTL24(0x000014ul, 8): p4->basra = data; return;
        case ROTL24(0x000018ul, 8): p4->basrb = data; return;
        case ROTL24(0x200004ul, 8): p4->bamra = data; return;
        case ROTL24(0x200010ul, 8): p4->bamrb = data; return;
        case ROTL24(0xc00004ul, 8): p4->stbcr = data; return;
        case ROTL24(0xc00008ul, 8): p4->wtcnt = data; return;
        case ROTL24(0xc0000cul, 8): p4->wtcsr = data; return;
        case ROTL24(0xc00010ul, 8): p4->stbcr2 = data; return;
        case ROTL24(0xc80000ul, 8): p4->r64cnt = data; return;
        case ROTL24(0xc80004ul, 8): p4->rseccnt = data; return;
        case ROTL24(0xc80008ul, 8): p4->rmincnt = data; return;
        case ROTL24(0xc8000cul, 8): p4->rhrcnt = data; return;
        case ROTL24(0xc80010ul, 8): p4->rwkcnt = data; return;
        case ROTL24(0xc80014ul, 8): p4->rdaycnt = data; return;
        case ROTL24(0xc80018ul, 8): p4->rmoncnt = data; return;
        case ROTL24(0xc80020ul, 8): p4->rsecar = data; return;
        case ROTL24(0xc80024ul, 8): p4->rminar = data; return;
        case ROTL24(0xc80028ul, 8): p4->rhrar = data; return;
        case ROTL24(0xc8002cul, 8): p4->rwkar = data; return;
        case ROTL24(0xc80030ul, 8): p4->rdayar = data; return;
        case ROTL24(0xc80034ul, 8): p4->rmonar = data; return;
        case ROTL24(0xc80038ul, 8): p4->rcr1 = data; return;
        case ROTL24(0xc8003cul, 8): p4->rcr2 = data; return;
        case ROTL24(0xd80000ul, 8): p4->tocr = data; return;
        case ROTL24(0xd80004ul, 8): p4->tstr = data; return;
        case ROTL24(0xe00000ul, 8): p4->scsmr1 = data; return;
        case ROTL24(0xe00004ul, 8): p4->scbrr1 = data; return;
        case ROTL24(0xe00008ul, 8): p4->scscr1 = data; return;
        case ROTL24(0xe0000cul, 8): p4->sctdr1 = data; return;
        case ROTL24(0xe00010ul, 8): p4->scssr1 = data; return;
        case ROTL24(0xe00014ul, 8): p4->scrdr1 = data; return;
        case ROTL24(0xe00018ul, 8): p4->scscmr1 = data; return;
        case ROTL24(0xe0001cul, 8): p4->scsptr1 = data; return;
        case ROTL24(0xe80004ul, 8): p4->scbrr2 = data; return;
        case ROTL24(0xe8000cul, 8): p4->scftdr2 = data; return;
        case ROTL24(0xe80014ul, 8): p4->scfrdr2 = data; return;
    }

    printf("unhandled 8-bit P4 register write %08x (%08x)\n", addr, data);
}

void p4_destroy(p4_state* p4) {
    free(p4);
}