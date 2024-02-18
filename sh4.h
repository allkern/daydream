#ifndef SH4_H
#define SH4_H

#include <stdint.h>

#define SR_T     0x00000001
#define SR_S     0x00000002
#define SR_IMASK 0x000000f0
#define SR_Q     0x00000100
#define SR_M     0x00000200
#define SR_FD    0x00008000
#define SR_BL    0x10000000
#define SR_RB    0x20000000
#define SR_MD    0x40000000

typedef uint32_t (*sh4_bus_read8_func)(void*, uint32_t);
typedef uint32_t (*sh4_bus_read16_func)(void*, uint32_t);
typedef uint32_t (*sh4_bus_read32_func)(void*, uint32_t);
typedef void (*sh4_bus_write8_func)(void*, uint32_t, uint32_t);
typedef void (*sh4_bus_write16_func)(void*, uint32_t, uint32_t);
typedef void (*sh4_bus_write32_func)(void*, uint32_t, uint32_t);

typedef struct {
    void* udata;
    sh4_bus_read8_func read8;
    sh4_bus_read16_func read16;
    sh4_bus_read32_func read32;
    sh4_bus_write8_func write8;
    sh4_bus_write16_func write16;
    sh4_bus_write32_func write32;
} sh4_bus;

typedef struct {
    sh4_bus bus;

    uint32_t rb[2][8];
    uint32_t r[8];

    union {
        uint32_t u32;

        struct {
            unsigned int t     : 1;
            unsigned int s     : 1;
            unsigned int res0  : 2;
            unsigned int imask : 4;
            unsigned int q     : 1;
            unsigned int m     : 1;
            unsigned int res1  : 5;
            unsigned int fd    : 1;
            unsigned int res2  : 12;
            unsigned int bl    : 1;
            unsigned int rb    : 1;
            unsigned int md    : 1;
            unsigned int res3  : 1;
        };
    } sr;

    uint32_t ssr;
    uint32_t gbr;
    uint32_t mach;
    uint32_t macl;
    uint32_t pr;
    uint32_t vbr;
    uint32_t pc[2];
    uint32_t spc;
    uint32_t sgr;
    uint32_t dbr;
    uint32_t opcode;

    union {
        uint32_t u32;

        struct {
            unsigned int rm     : 2;
            unsigned int flag   : 5;
            unsigned int enable : 5;
            unsigned int cause  : 6;
            unsigned int dn     : 1;
            unsigned int pr     : 1;
            unsigned int sz     : 1;
            unsigned int fr     : 1;
            unsigned int res0   : 10;
        };
    } fpscr;

    uint32_t fpul;

    union {
        union {
            uint32_t u32;
            float f;
        } f[16];

        union {
            uint64_t u64;
            double d;
        } d[8];

        struct {
            float f[4];
        } fv[4];

        struct {
            float f[16];
        } xmtrx;
    } fb[2];
} sh4_state;

sh4_state* sh4_create(void);
void sh4_init(sh4_state* cpu, sh4_bus bus);
void sh4_cycle(sh4_state* cpu);
void sh4_destroy(sh4_state* cpu);
uint32_t sh4_get_reg(sh4_state* cpu, int index);
void sh4_set_reg(sh4_state* cpu, int index, uint32_t value);
void sh4_set_pc(sh4_state* cpu, uint32_t pc);
void sh4_set_pc_delayed(sh4_state* cpu, uint32_t pc);

void sh4_op_mov(sh4_state* cpu);
void sh4_op_movi(sh4_state* cpu);
void sh4_op_mova(sh4_state* cpu);
void sh4_op_movwi(sh4_state* cpu);
void sh4_op_movli(sh4_state* cpu);
void sh4_op_movbl(sh4_state* cpu);
void sh4_op_movwl(sh4_state* cpu);
void sh4_op_movll(sh4_state* cpu);
void sh4_op_movbs(sh4_state* cpu);
void sh4_op_movws(sh4_state* cpu);
void sh4_op_movls(sh4_state* cpu);
void sh4_op_movbp(sh4_state* cpu);
void sh4_op_movwp(sh4_state* cpu);
void sh4_op_movlp(sh4_state* cpu);
void sh4_op_movbm(sh4_state* cpu);
void sh4_op_movwm(sh4_state* cpu);
void sh4_op_movlm(sh4_state* cpu);
void sh4_op_movbl4(sh4_state* cpu);
void sh4_op_movwl4(sh4_state* cpu);
void sh4_op_movll4(sh4_state* cpu);
void sh4_op_movbs4(sh4_state* cpu);
void sh4_op_movws4(sh4_state* cpu);
void sh4_op_movls4(sh4_state* cpu);
void sh4_op_movbl0(sh4_state* cpu);
void sh4_op_movwl0(sh4_state* cpu);
void sh4_op_movll0(sh4_state* cpu);
void sh4_op_movbs0(sh4_state* cpu);
void sh4_op_movws0(sh4_state* cpu);
void sh4_op_movls0(sh4_state* cpu);
void sh4_op_movblg(sh4_state* cpu);
void sh4_op_movwlg(sh4_state* cpu);
void sh4_op_movllg(sh4_state* cpu);
void sh4_op_movbsg(sh4_state* cpu);
void sh4_op_movwsg(sh4_state* cpu);
void sh4_op_movlsg(sh4_state* cpu);
void sh4_op_movt(sh4_state* cpu);
void sh4_op_swapb(sh4_state* cpu);
void sh4_op_swapw(sh4_state* cpu);
void sh4_op_xtrct(sh4_state* cpu);
void sh4_op_add(sh4_state* cpu);
void sh4_op_addi(sh4_state* cpu);
void sh4_op_addc(sh4_state* cpu);
void sh4_op_addv(sh4_state* cpu);
void sh4_op_cmpim(sh4_state* cpu);
void sh4_op_cmpeq(sh4_state* cpu);
void sh4_op_cmphs(sh4_state* cpu);
void sh4_op_cmpge(sh4_state* cpu);
void sh4_op_cmphi(sh4_state* cpu);
void sh4_op_cmpgt(sh4_state* cpu);
void sh4_op_cmppl(sh4_state* cpu);
void sh4_op_cmppz(sh4_state* cpu);
void sh4_op_cmpstr(sh4_state* cpu);
void sh4_op_div0s(sh4_state* cpu);
void sh4_op_div0u(sh4_state* cpu);
void sh4_op_div1(sh4_state* cpu);
void sh4_op_dmuls(sh4_state* cpu);
void sh4_op_dmulu(sh4_state* cpu);
void sh4_op_dt(sh4_state* cpu);
void sh4_op_extsb(sh4_state* cpu);
void sh4_op_extsw(sh4_state* cpu);
void sh4_op_extub(sh4_state* cpu);
void sh4_op_extuw(sh4_state* cpu);
void sh4_op_macl(sh4_state* cpu);
void sh4_op_macw(sh4_state* cpu);
void sh4_op_mull(sh4_state* cpu);
void sh4_op_muls(sh4_state* cpu);
void sh4_op_mulu(sh4_state* cpu);
void sh4_op_neg(sh4_state* cpu);
void sh4_op_negc(sh4_state* cpu);
void sh4_op_sub(sh4_state* cpu);
void sh4_op_subc(sh4_state* cpu);
void sh4_op_subv(sh4_state* cpu);
void sh4_op_and(sh4_state* cpu);
void sh4_op_andi(sh4_state* cpu);
void sh4_op_andm(sh4_state* cpu);
void sh4_op_not(sh4_state* cpu);
void sh4_op_or(sh4_state* cpu);
void sh4_op_ori(sh4_state* cpu);
void sh4_op_orm(sh4_state* cpu);
void sh4_op_tas(sh4_state* cpu);
void sh4_op_tst(sh4_state* cpu);
void sh4_op_tsti(sh4_state* cpu);
void sh4_op_tstm(sh4_state* cpu);
void sh4_op_xor(sh4_state* cpu);
void sh4_op_xori(sh4_state* cpu);
void sh4_op_xorm(sh4_state* cpu);
void sh4_op_rotcl(sh4_state* cpu);
void sh4_op_rotcr(sh4_state* cpu);
void sh4_op_rotl(sh4_state* cpu);
void sh4_op_rotr(sh4_state* cpu);
void sh4_op_shad(sh4_state* cpu);
void sh4_op_shal(sh4_state* cpu);
void sh4_op_shar(sh4_state* cpu);
void sh4_op_shld(sh4_state* cpu);
void sh4_op_shll(sh4_state* cpu);
void sh4_op_shll2(sh4_state* cpu);
void sh4_op_shll8(sh4_state* cpu);
void sh4_op_shll16(sh4_state* cpu);
void sh4_op_shlr(sh4_state* cpu);
void sh4_op_shlr2(sh4_state* cpu);
void sh4_op_shlr8(sh4_state* cpu);
void sh4_op_shlr16(sh4_state* cpu);
void sh4_op_bf(sh4_state* cpu);
void sh4_op_bfs(sh4_state* cpu);
void sh4_op_bt(sh4_state* cpu);
void sh4_op_bts(sh4_state* cpu);
void sh4_op_bra(sh4_state* cpu);
void sh4_op_braf(sh4_state* cpu);
void sh4_op_bsr(sh4_state* cpu);
void sh4_op_bsrf(sh4_state* cpu);
void sh4_op_jmp(sh4_state* cpu);
void sh4_op_jsr(sh4_state* cpu);
void sh4_op_rts(sh4_state* cpu);
void sh4_op_clrmac(sh4_state* cpu);
void sh4_op_clrs(sh4_state* cpu);
void sh4_op_clrt(sh4_state* cpu);
void sh4_op_ldcsr(sh4_state* cpu);
void sh4_op_ldcmsr(sh4_state* cpu);
void sh4_op_ldcgbr(sh4_state* cpu);
void sh4_op_ldcmgbr(sh4_state* cpu);
void sh4_op_ldcvbr(sh4_state* cpu);
void sh4_op_ldcmvbr(sh4_state* cpu);
void sh4_op_ldcssr(sh4_state* cpu);
void sh4_op_ldcmssr(sh4_state* cpu);
void sh4_op_ldcspc(sh4_state* cpu);
void sh4_op_ldcmspc(sh4_state* cpu);
void sh4_op_ldcdbr(sh4_state* cpu);
void sh4_op_ldcmdbr(sh4_state* cpu);
void sh4_op_ldcrn_bank(sh4_state* cpu);
void sh4_op_ldcmrn_bank(sh4_state* cpu);
void sh4_op_ldsmach(sh4_state* cpu);
void sh4_op_ldsmmach(sh4_state* cpu);
void sh4_op_ldsmacl(sh4_state* cpu);
void sh4_op_ldsmmacl(sh4_state* cpu);
void sh4_op_ldspr(sh4_state* cpu);
void sh4_op_ldsmpr(sh4_state* cpu);
void sh4_op_ldtlb(sh4_state* cpu);
void sh4_op_movcal(sh4_state* cpu);
void sh4_op_nop(sh4_state* cpu);
void sh4_op_ocbi(sh4_state* cpu);
void sh4_op_ocbp(sh4_state* cpu);
void sh4_op_ocbwb(sh4_state* cpu);
void sh4_op_pref(sh4_state* cpu);
void sh4_op_rte(sh4_state* cpu);
void sh4_op_sets(sh4_state* cpu);
void sh4_op_sett(sh4_state* cpu);
void sh4_op_sleep(sh4_state* cpu);
void sh4_op_stcsr(sh4_state* cpu);
void sh4_op_stcmsr(sh4_state* cpu);
void sh4_op_stcgbr(sh4_state* cpu);
void sh4_op_stcmgbr(sh4_state* cpu);
void sh4_op_stcvbr(sh4_state* cpu);
void sh4_op_stcmvbr(sh4_state* cpu);
void sh4_op_stcsgr(sh4_state* cpu);
void sh4_op_stcmsgr(sh4_state* cpu);
void sh4_op_stcssr(sh4_state* cpu);
void sh4_op_stcmssr(sh4_state* cpu);
void sh4_op_stcspc(sh4_state* cpu);
void sh4_op_stcmspc(sh4_state* cpu);
void sh4_op_stcdbr(sh4_state* cpu);
void sh4_op_stcmdbr(sh4_state* cpu);
void sh4_op_stcrm_bank(sh4_state* cpu);
void sh4_op_stcmrm_bank(sh4_state* cpu);
void sh4_op_stsmach(sh4_state* cpu);
void sh4_op_stsmmach(sh4_state* cpu);
void sh4_op_stsmacl(sh4_state* cpu);
void sh4_op_stsmmacl(sh4_state* cpu);
void sh4_op_stspr(sh4_state* cpu);
void sh4_op_stsmpr(sh4_state* cpu);
void sh4_op_trapa(sh4_state* cpu);
void sh4_op_fmov(sh4_state* cpu);
void sh4_op_fmov_load(sh4_state* cpu);
void sh4_op_fmov_store(sh4_state* cpu);
void sh4_op_fmov_restore(sh4_state* cpu);
void sh4_op_fmov_save(sh4_state* cpu);
void sh4_op_fmov_index_load(sh4_state* cpu);
void sh4_op_fmov_index_store(sh4_state* cpu);
void sh4_op_fmov_dr(sh4_state* cpu);
void sh4_op_fmov_drxd(sh4_state* cpu);
void sh4_op_fmov_xddr(sh4_state* cpu);
void sh4_op_fmov_xdxd(sh4_state* cpu);
void sh4_op_fmov_load_dr(sh4_state* cpu);
void sh4_op_fmov_load_xd(sh4_state* cpu);
void sh4_op_fmov_store_dr(sh4_state* cpu);
void sh4_op_fmov_store_xd(sh4_state* cpu);
void sh4_op_fmov_restore_dr(sh4_state* cpu);
void sh4_op_fmov_restore_xd(sh4_state* cpu);
void sh4_op_fmov_save_dr(sh4_state* cpu);
void sh4_op_fmov_save_xd(sh4_state* cpu);
void sh4_op_fmov_index_load_dr(sh4_state* cpu);
void sh4_op_fmov_index_load_xd(sh4_state* cpu);
void sh4_op_fmov_index_store_dr(sh4_state* cpu);
void sh4_op_fmov_index_store_xd(sh4_state* cpu);
void sh4_op_fldi0(sh4_state* cpu);
void sh4_op_fldi1(sh4_state* cpu);
void sh4_op_flds(sh4_state* cpu);
void sh4_op_fsts(sh4_state* cpu);
void sh4_op_fabs_fr(sh4_state* cpu);
void sh4_op_fneg_fr(sh4_state* cpu);
void sh4_op_fadd_fr(sh4_state* cpu);
void sh4_op_fsub_fr(sh4_state* cpu);
void sh4_op_fmul_fr(sh4_state* cpu);
void sh4_op_fmac(sh4_state* cpu);
void sh4_op_fdiv_fr(sh4_state* cpu);
void sh4_op_fsqrt_fr(sh4_state* cpu);
void sh4_op_fsrra(sh4_state* cpu);
void sh4_op_fcmp_eq_fr(sh4_state* cpu);
void sh4_op_fcmp_gt_fr(sh4_state* cpu);
void sh4_op_float_single(sh4_state* cpu);
void sh4_op_ftrc_single(sh4_state* cpu);
void sh4_op_fipr(sh4_state* cpu);
void sh4_op_fsca(sh4_state* cpu);
void sh4_op_ftrv(sh4_state* cpu);
void sh4_op_fabs_dr(sh4_state* cpu);
void sh4_op_fneg_dr(sh4_state* cpu);
void sh4_op_fadd_dr(sh4_state* cpu);
void sh4_op_fsub_dr(sh4_state* cpu);
void sh4_op_fmul_dr(sh4_state* cpu);
void sh4_op_fdiv_dr(sh4_state* cpu);
void sh4_op_fsqrt_dr(sh4_state* cpu);
void sh4_op_fcmp_eq_dr(sh4_state* cpu);
void sh4_op_fcmp_gt_dr(sh4_state* cpu);
void sh4_op_float_double(sh4_state* cpu);
void sh4_op_ftrc_double(sh4_state* cpu);
void sh4_op_fcnvds(sh4_state* cpu);
void sh4_op_fcnvsd(sh4_state* cpu);
void sh4_op_ldsfpscr(sh4_state* cpu);
void sh4_op_stsfpscr(sh4_state* cpu);
void sh4_op_ldsmfpscr(sh4_state* cpu);
void sh4_op_stsmfpscr(sh4_state* cpu);
void sh4_op_ldsfpul(sh4_state* cpu);
void sh4_op_stsfpul(sh4_state* cpu);
void sh4_op_ldsmfpul(sh4_state* cpu);
void sh4_op_stsmfpul(sh4_state* cpu);
void sh4_op_frchg(sh4_state* cpu);
void sh4_op_fschg(sh4_state* cpu);

#endif