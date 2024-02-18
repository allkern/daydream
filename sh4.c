#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "sh4.h"

sh4_state* sh4_create(void) {
    return malloc(sizeof(sh4_state));
}

void sh4_init(sh4_state* cpu, sh4_bus bus) {
    memset(cpu, 0, sizeof(sh4_state));

    cpu->sr.u32 = 0x700000f0;
    cpu->pc[0] = 0xa0000000;
    cpu->pc[1] = 0xa0000002;
    cpu->bus = bus;

    cpu->fpscr.u32 = 0x00040001;
}

#define ROTL16(v, r) ((((v) << r) | ((v) >> (16 - r))) & 0xffff)

void sh4_exec(sh4_state* cpu) {
    // To-do: Optimize by rotating and/or shifting masks
    //        so the compiler is more likely to generate
    //        jumptables instead of ifelse chains
    uint16_t opcode_f00f = cpu->opcode & 0xf00f;

    switch (ROTL16(opcode_f00f, 4)) {
        case ROTL16(0x6003, 4): sh4_op_mov(cpu); return;
        case ROTL16(0x6000, 4): sh4_op_movbl(cpu); return;
        case ROTL16(0x6001, 4): sh4_op_movwl(cpu); return;
        case ROTL16(0x6002, 4): sh4_op_movll(cpu); return;
        case ROTL16(0x2000, 4): sh4_op_movbs(cpu); return;
        case ROTL16(0x2001, 4): sh4_op_movws(cpu); return;
        case ROTL16(0x2002, 4): sh4_op_movls(cpu); return;
        case ROTL16(0x6004, 4): sh4_op_movbp(cpu); return;
        case ROTL16(0x6005, 4): sh4_op_movwp(cpu); return;
        case ROTL16(0x6006, 4): sh4_op_movlp(cpu); return;
        case ROTL16(0x2004, 4): sh4_op_movbm(cpu); return;
        case ROTL16(0x2005, 4): sh4_op_movwm(cpu); return;
        case ROTL16(0x2006, 4): sh4_op_movlm(cpu); return;
        case ROTL16(0x000c, 4): sh4_op_movbl0(cpu); return;
        case ROTL16(0x000d, 4): sh4_op_movwl0(cpu); return;
        case ROTL16(0x000e, 4): sh4_op_movll0(cpu); return;
        case ROTL16(0x0004, 4): sh4_op_movbs0(cpu); return;
        case ROTL16(0x0005, 4): sh4_op_movws0(cpu); return;
        case ROTL16(0x0006, 4): sh4_op_movls0(cpu); return;
        case ROTL16(0x6008, 4): sh4_op_swapb(cpu); return;
        case ROTL16(0x6009, 4): sh4_op_swapw(cpu); return;
        case ROTL16(0x200d, 4): sh4_op_xtrct(cpu); return;
        case ROTL16(0x300c, 4): sh4_op_add(cpu); return;
        case ROTL16(0x300e, 4): sh4_op_addc(cpu); return;
        case ROTL16(0x300f, 4): sh4_op_addv(cpu); return;
        case ROTL16(0x3000, 4): sh4_op_cmpeq(cpu); return;
        case ROTL16(0x3002, 4): sh4_op_cmphs(cpu); return;
        case ROTL16(0x3003, 4): sh4_op_cmpge(cpu); return;
        case ROTL16(0x3006, 4): sh4_op_cmphi(cpu); return;
        case ROTL16(0x3007, 4): sh4_op_cmpgt(cpu); return;
        case ROTL16(0x200c, 4): sh4_op_cmpstr(cpu); return;
        case ROTL16(0x2007, 4): sh4_op_div0s(cpu); return;
        case ROTL16(0x3004, 4): sh4_op_div1(cpu); return;
        case ROTL16(0x300d, 4): sh4_op_dmuls(cpu); return;
        case ROTL16(0x3005, 4): sh4_op_dmulu(cpu); return;
        case ROTL16(0x600e, 4): sh4_op_extsb(cpu); return;
        case ROTL16(0x600f, 4): sh4_op_extsw(cpu); return;
        case ROTL16(0x600c, 4): sh4_op_extub(cpu); return;
        case ROTL16(0x600d, 4): sh4_op_extuw(cpu); return;
        case ROTL16(0x000f, 4): sh4_op_macl(cpu); return;
        case ROTL16(0x400f, 4): sh4_op_macw(cpu); return;
        case ROTL16(0x0007, 4): sh4_op_mull(cpu); return;
        case ROTL16(0x200f, 4): sh4_op_muls(cpu); return;
        case ROTL16(0x200e, 4): sh4_op_mulu(cpu); return;
        case ROTL16(0x600b, 4): sh4_op_neg(cpu); return;
        case ROTL16(0x600a, 4): sh4_op_negc(cpu); return;
        case ROTL16(0x3008, 4): sh4_op_sub(cpu); return;
        case ROTL16(0x300a, 4): sh4_op_subc(cpu); return;
        case ROTL16(0x300b, 4): sh4_op_subv(cpu); return;
        case ROTL16(0x2009, 4): sh4_op_and(cpu); return;
        case ROTL16(0x6007, 4): sh4_op_not(cpu); return;
        case ROTL16(0x200b, 4): sh4_op_or(cpu); return;
        case ROTL16(0x2008, 4): sh4_op_tst(cpu); return;
        case ROTL16(0x200a, 4): sh4_op_xor(cpu); return;
        case ROTL16(0x400c, 4): sh4_op_shad(cpu); return;
        case ROTL16(0x400d, 4): sh4_op_shld(cpu); return;
        case ROTL16(0xf00c, 4): sh4_op_fmov(cpu); return;
        case ROTL16(0xf008, 4): sh4_op_fmov_load(cpu); return;
        case ROTL16(0xf00a, 4): sh4_op_fmov_store(cpu); return;
        case ROTL16(0xf009, 4): sh4_op_fmov_restore(cpu); return;
        case ROTL16(0xf00b, 4): sh4_op_fmov_save(cpu); return;
        case ROTL16(0xf006, 4): sh4_op_fmov_index_load(cpu); return;
        case ROTL16(0xf007, 4): sh4_op_fmov_index_store(cpu); return;
        case ROTL16(0xf000, 4): sh4_op_fadd_fr(cpu); return;
        case ROTL16(0xf001, 4): sh4_op_fsub_fr(cpu); return;
        case ROTL16(0xf002, 4): sh4_op_fmul_fr(cpu); return;
        case ROTL16(0xf00e, 4): sh4_op_fmac(cpu); return;
        case ROTL16(0xf003, 4): sh4_op_fdiv_fr(cpu); return;
        case ROTL16(0xf004, 4): sh4_op_fcmp_eq_fr(cpu); return;
        case ROTL16(0xf005, 4): sh4_op_fcmp_gt_fr(cpu); return;
    }

    switch ((cpu->opcode & 0xf000) >> 12) {
        case 0xe000 >> 12: sh4_op_movi(cpu); return;
        case 0x9000 >> 12: sh4_op_movwi(cpu); return;
        case 0xd000 >> 12: sh4_op_movli(cpu); return;
        case 0x5000 >> 12: sh4_op_movll4(cpu); return;
        case 0x1000 >> 12: sh4_op_movls4(cpu); return;
        case 0x7000 >> 12: sh4_op_addi(cpu); return;
        case 0xa000 >> 12: sh4_op_bra(cpu); return;
        case 0xb000 >> 12: sh4_op_bsr(cpu); return;
    }

    switch ((cpu->opcode & 0xff00) >> 8) {
        case 0xc700 >> 8: sh4_op_mova(cpu); return;
        case 0x8400 >> 8: sh4_op_movbl4(cpu); return;
        case 0x8500 >> 8: sh4_op_movwl4(cpu); return;
        case 0x8000 >> 8: sh4_op_movbs4(cpu); return;
        case 0x8100 >> 8: sh4_op_movws4(cpu); return;
        case 0xc400 >> 8: sh4_op_movblg(cpu); return;
        case 0xc500 >> 8: sh4_op_movwlg(cpu); return;
        case 0xc600 >> 8: sh4_op_movllg(cpu); return;
        case 0xc000 >> 8: sh4_op_movbsg(cpu); return;
        case 0xc100 >> 8: sh4_op_movwsg(cpu); return;
        case 0xc200 >> 8: sh4_op_movlsg(cpu); return;
        case 0x8800 >> 8: sh4_op_cmpim(cpu); return;
        case 0xc900 >> 8: sh4_op_andi(cpu); return;
        case 0xcd00 >> 8: sh4_op_andm(cpu); return;
        case 0xcb00 >> 8: sh4_op_ori(cpu); return;
        case 0xcf00 >> 8: sh4_op_orm(cpu); return;
        case 0xc800 >> 8: sh4_op_tsti(cpu); return;
        case 0xcc00 >> 8: sh4_op_tstm(cpu); return;
        case 0xca00 >> 8: sh4_op_xori(cpu); return;
        case 0xce00 >> 8: sh4_op_xorm(cpu); return;
        case 0x8b00 >> 8: sh4_op_bf(cpu); return;
        case 0x8f00 >> 8: sh4_op_bfs(cpu); return;
        case 0x8900 >> 8: sh4_op_bt(cpu); return;
        case 0x8d00 >> 8: sh4_op_bts(cpu); return;
        case 0xc300 >> 8: sh4_op_trapa(cpu); return;
    }

    uint16_t opcode_f0ff = cpu->opcode & 0xf0ff;

    switch (ROTL16(opcode_f0ff, 4)) {
        case ROTL16(0x0029, 4): sh4_op_movt(cpu); return;
        case ROTL16(0x4015, 4): sh4_op_cmppl(cpu); return;
        case ROTL16(0x4011, 4): sh4_op_cmppz(cpu); return;
        case ROTL16(0x4010, 4): sh4_op_dt(cpu); return;
        case ROTL16(0x401b, 4): sh4_op_tas(cpu); return;
        case ROTL16(0x4024, 4): sh4_op_rotcl(cpu); return;
        case ROTL16(0x4025, 4): sh4_op_rotcr(cpu); return;
        case ROTL16(0x4004, 4): sh4_op_rotl(cpu); return;
        case ROTL16(0x4005, 4): sh4_op_rotr(cpu); return;
        case ROTL16(0x4020, 4): sh4_op_shal(cpu); return;
        case ROTL16(0x4021, 4): sh4_op_shar(cpu); return;
        case ROTL16(0x4000, 4): sh4_op_shll(cpu); return;
        case ROTL16(0x4008, 4): sh4_op_shll2(cpu); return;
        case ROTL16(0x4018, 4): sh4_op_shll8(cpu); return;
        case ROTL16(0x4028, 4): sh4_op_shll16(cpu); return;
        case ROTL16(0x4001, 4): sh4_op_shlr(cpu); return;
        case ROTL16(0x4009, 4): sh4_op_shlr2(cpu); return;
        case ROTL16(0x4019, 4): sh4_op_shlr8(cpu); return;
        case ROTL16(0x4029, 4): sh4_op_shlr16(cpu); return;
        case ROTL16(0x0023, 4): sh4_op_braf(cpu); return;
        case ROTL16(0x0003, 4): sh4_op_bsrf(cpu); return;
        case ROTL16(0x402b, 4): sh4_op_jmp(cpu); return;
        case ROTL16(0x400b, 4): sh4_op_jsr(cpu); return;
        case ROTL16(0x400e, 4): sh4_op_ldcsr(cpu); return;
        case ROTL16(0x4007, 4): sh4_op_ldcmsr(cpu); return;
        case ROTL16(0x401e, 4): sh4_op_ldcgbr(cpu); return;
        case ROTL16(0x4017, 4): sh4_op_ldcmgbr(cpu); return;
        case ROTL16(0x402e, 4): sh4_op_ldcvbr(cpu); return;
        case ROTL16(0x4027, 4): sh4_op_ldcmvbr(cpu); return;
        case ROTL16(0x403e, 4): sh4_op_ldcssr(cpu); return;
        case ROTL16(0x4037, 4): sh4_op_ldcmssr(cpu); return;
        case ROTL16(0x404e, 4): sh4_op_ldcspc(cpu); return;
        case ROTL16(0x4047, 4): sh4_op_ldcmspc(cpu); return;
        case ROTL16(0x40fa, 4): sh4_op_ldcdbr(cpu); return;
        case ROTL16(0x40f6, 4): sh4_op_ldcmdbr(cpu); return;
        case ROTL16(0x400a, 4): sh4_op_ldsmach(cpu); return;
        case ROTL16(0x4006, 4): sh4_op_ldsmmach(cpu); return;
        case ROTL16(0x401a, 4): sh4_op_ldsmacl(cpu); return;
        case ROTL16(0x4016, 4): sh4_op_ldsmmacl(cpu); return;
        case ROTL16(0x402a, 4): sh4_op_ldspr(cpu); return;
        case ROTL16(0x4026, 4): sh4_op_ldsmpr(cpu); return;
        case ROTL16(0x00c3, 4): sh4_op_movcal(cpu); return;
        case ROTL16(0x0093, 4): sh4_op_ocbi(cpu); return;
        case ROTL16(0x00a3, 4): sh4_op_ocbp(cpu); return;
        case ROTL16(0x00b3, 4): sh4_op_ocbwb(cpu); return;
        case ROTL16(0x0083, 4): sh4_op_pref(cpu); return;
        case ROTL16(0x0002, 4): sh4_op_stcsr(cpu); return;
        case ROTL16(0x4003, 4): sh4_op_stcmsr(cpu); return;
        case ROTL16(0x0012, 4): sh4_op_stcgbr(cpu); return;
        case ROTL16(0x4013, 4): sh4_op_stcmgbr(cpu); return;
        case ROTL16(0x0022, 4): sh4_op_stcvbr(cpu); return;
        case ROTL16(0x4023, 4): sh4_op_stcmvbr(cpu); return;
        case ROTL16(0x003a, 4): sh4_op_stcsgr(cpu); return;
        case ROTL16(0x4032, 4): sh4_op_stcmsgr(cpu); return;
        case ROTL16(0x0032, 4): sh4_op_stcssr(cpu); return;
        case ROTL16(0x4033, 4): sh4_op_stcmssr(cpu); return;
        case ROTL16(0x0042, 4): sh4_op_stcspc(cpu); return;
        case ROTL16(0x4043, 4): sh4_op_stcmspc(cpu); return;
        case ROTL16(0x00fa, 4): sh4_op_stcdbr(cpu); return;
        case ROTL16(0x40f2, 4): sh4_op_stcmdbr(cpu); return;
        case ROTL16(0x000a, 4): sh4_op_stsmach(cpu); return;
        case ROTL16(0x4002, 4): sh4_op_stsmmach(cpu); return;
        case ROTL16(0x001a, 4): sh4_op_stsmacl(cpu); return;
        case ROTL16(0x4012, 4): sh4_op_stsmmacl(cpu); return;
        case ROTL16(0x002a, 4): sh4_op_stspr(cpu); return;
        case ROTL16(0x4022, 4): sh4_op_stsmpr(cpu); return;
        case ROTL16(0xf08d, 4): sh4_op_fldi0(cpu); return;
        case ROTL16(0xf09d, 4): sh4_op_fldi1(cpu); return;
        case ROTL16(0xf01d, 4): sh4_op_flds(cpu); return;
        case ROTL16(0xf00d, 4): sh4_op_fsts(cpu); return;
        case ROTL16(0xf05d, 4): sh4_op_fabs_fr(cpu); return;
        case ROTL16(0xf04d, 4): sh4_op_fneg_fr(cpu); return;
        case ROTL16(0xf06d, 4): sh4_op_fsqrt_fr(cpu); return;
        case ROTL16(0xf07d, 4): sh4_op_fsrra(cpu); return;
        case ROTL16(0xf02d, 4): sh4_op_float_single(cpu); return;
        case ROTL16(0xf03d, 4): sh4_op_ftrc_single(cpu); return;
        case ROTL16(0xf0ed, 4): sh4_op_fipr(cpu); return;
        case ROTL16(0x406a, 4): sh4_op_ldsfpscr(cpu); return;
        case ROTL16(0x006a, 4): sh4_op_stsfpscr(cpu); return;
        case ROTL16(0x4066, 4): sh4_op_ldsmfpscr(cpu); return;
        case ROTL16(0x4062, 4): sh4_op_stsmfpscr(cpu); return;
        case ROTL16(0x405a, 4): sh4_op_ldsfpul(cpu); return;
        case ROTL16(0x005a, 4): sh4_op_stsfpul(cpu); return;
        case ROTL16(0x4056, 4): sh4_op_ldsmfpul(cpu); return;
        case ROTL16(0x4052, 4): sh4_op_stsmfpul(cpu); return;
    }

    switch (cpu->opcode & 0xffff) {
        case 0x0019: sh4_op_div0u(cpu); return;
        case 0x000b: sh4_op_rts(cpu); return;
        case 0x0028: sh4_op_clrmac(cpu); return;
        case 0x0048: sh4_op_clrs(cpu); return;
        case 0x0008: sh4_op_clrt(cpu); return;
        case 0x0038: sh4_op_ldtlb(cpu); return;
        case 0x0009: sh4_op_nop(cpu); return;
        case 0x002b: sh4_op_rte(cpu); return;
        case 0x0058: sh4_op_sets(cpu); return;
        case 0x0018: sh4_op_sett(cpu); return;
        case 0x001b: sh4_op_sleep(cpu); return;
        case 0xfbfd: sh4_op_frchg(cpu); return;
        case 0xf3fd: sh4_op_fschg(cpu); return;
    }

    // To-do: Optimize the following
    switch (cpu->opcode & 0xf08f) {
        case 0x408e: sh4_op_ldcrn_bank(cpu); return;
        case 0x4087: sh4_op_ldcmrn_bank(cpu); return;
        case 0x0082: sh4_op_stcrm_bank(cpu); return;
        case 0x4083: sh4_op_stcmrm_bank(cpu); return;
    }

    switch (cpu->opcode & 0xf11f) {
        case 0xf00c: sh4_op_fmov_dr(cpu); return;
        case 0xf10c: sh4_op_fmov_drxd(cpu); return;
        case 0xf01c: sh4_op_fmov_xddr(cpu); return;
        case 0xf11c: sh4_op_fmov_xdxd(cpu); return;
        case 0xf000: sh4_op_fadd_dr(cpu); return;
        case 0xf001: sh4_op_fsub_dr(cpu); return;
        case 0xf002: sh4_op_fmul_dr(cpu); return;
        case 0xf003: sh4_op_fdiv_dr(cpu); return;
        case 0xf004: sh4_op_fcmp_eq_dr(cpu); return;
        case 0xf005: sh4_op_fcmp_gt_dr(cpu); return;
    }

    switch (cpu->opcode & 0xf10f) {
        case 0xf008: sh4_op_fmov_load_dr(cpu); return;
        case 0xf108: sh4_op_fmov_load_xd(cpu); return;
        case 0xf009: sh4_op_fmov_restore_dr(cpu); return;
        case 0xf109: sh4_op_fmov_restore_xd(cpu); return;
        case 0xf006: sh4_op_fmov_index_load_dr(cpu); return;
        case 0xf106: sh4_op_fmov_index_load_xd(cpu); return;
    }

    switch (cpu->opcode & 0xf01f) {
        case 0xf00a: sh4_op_fmov_store_dr(cpu); return;
        case 0xf01a: sh4_op_fmov_store_xd(cpu); return;
        case 0xf00b: sh4_op_fmov_save_dr(cpu); return;
        case 0xf01b: sh4_op_fmov_save_xd(cpu); return;
        case 0xf007: sh4_op_fmov_index_store_dr(cpu); return;
        case 0xf017: sh4_op_fmov_index_store_xd(cpu); return;
    }

    switch (cpu->opcode & 0xf3ff) {
        case 0xf1fd: sh4_op_ftrv(cpu); return;
    }

    switch (cpu->opcode & 0xf1ff) {
        case 0xf05d: sh4_op_fabs_dr(cpu); return;
        case 0xf04d: sh4_op_fneg_dr(cpu); return;
        case 0xf06d: sh4_op_fsqrt_dr(cpu); return;
        case 0xf02d: sh4_op_float_double(cpu); return;
        case 0xf03d: sh4_op_ftrc_double(cpu); return;
        case 0xf0bd: sh4_op_fcnvds(cpu); return;
        case 0xf0ad: sh4_op_fcnvsd(cpu); return;
        case 0xf0fd: sh4_op_fsca(cpu); return;
    }

    printf("Unimplemented opcode %04x\n", cpu->opcode);

    exit(1);
}

#undef ROTL16

void sh4_cycle(sh4_state* cpu) {
    cpu->opcode = cpu->bus.read16(cpu->bus.udata, cpu->pc[0]);

    cpu->pc[0] = cpu->pc[1];
    cpu->pc[1] = cpu->pc[0] + 2;

    sh4_exec(cpu);
}

void sh4_destroy(sh4_state* cpu) {
    free(cpu);
}

uint32_t sh4_get_reg(sh4_state* cpu, int index) {
    if (index < 8)
        return cpu->rb[cpu->sr.rb && cpu->sr.md][index];

    return cpu->r[index - 8];
}

void sh4_set_reg(sh4_state* cpu, int index, uint32_t value) {
    if (index < 8) {
        cpu->rb[cpu->sr.rb && cpu->sr.md][index] = value;

        return;
    }

    cpu->r[index - 8] = value;
}

void sh4_set_pc(sh4_state* cpu, uint32_t pc) {
    cpu->pc[0] = pc;
    cpu->pc[1] = pc + 2;
}

void sh4_set_pc_delayed(sh4_state* cpu, uint32_t pc) {
    cpu->pc[1] = pc;
}