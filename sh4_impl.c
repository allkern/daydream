#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define M_PI 3.14159265358979323846

#include "sh4.h"
#include "sh4_dis.h"

#define N ((cpu->opcode >> 8) & 0xf)
#define M ((cpu->opcode >> 4) & 0xf)
#define D (cpu->opcode & 0xff)
#define PC (cpu->pc[0] - 2)
#define SE8(v) ((int32_t)(v << 24) >> 24)
#define SE16(v) ((int32_t)(v << 16) >> 16)
#define FR(n) cpu->fb[cpu->fpscr.fr].f[n]

#define ERROR_EXIT(msg) { puts(msg); exit(1); }

uint32_t bus_read8(sh4_state* cpu, uint32_t addr) {
    return cpu->bus.read8(cpu->bus.udata, addr);
}

uint32_t bus_read16(sh4_state* cpu, uint32_t addr) {
    return cpu->bus.read16(cpu->bus.udata, addr);
}

uint32_t bus_read32(sh4_state* cpu, uint32_t addr) {
    return cpu->bus.read32(cpu->bus.udata, addr);
}

void bus_write8(sh4_state* cpu, uint32_t addr, uint32_t data) {
    cpu->bus.write8(cpu->bus.udata, addr, data);
}

void bus_write16(sh4_state* cpu, uint32_t addr, uint32_t data) {
    cpu->bus.write16(cpu->bus.udata, addr, data);
}

void bus_write32(sh4_state* cpu, uint32_t addr, uint32_t data) {
    cpu->bus.write32(cpu->bus.udata, addr, data);
}

void sh4_op_mov(sh4_state* cpu) {
    sh4_set_reg(cpu, N, sh4_get_reg(cpu, M));
}
void sh4_op_movi(sh4_state* cpu) {
    sh4_set_reg(cpu, N, SE8(D));
}
void sh4_op_mova(sh4_state* cpu) {
    uint32_t data = (SE8(D) << 2) + (PC & 0xfffffffc) + 4;

    sh4_set_reg(cpu, 0, data);
}
void sh4_op_movwi(sh4_state* cpu) { puts("movwi unimplemented"); exit(1); }
void sh4_op_movli(sh4_state* cpu) {
    uint32_t data = bus_read32(cpu, (SE8(D) << 2) + (PC & 0xfffffffc) + 4);

    sh4_set_reg(cpu, N, data);
}
void sh4_op_movbl(sh4_state* cpu) {
    uint32_t data = bus_read32(cpu, sh4_get_reg(cpu, M));

    sh4_set_reg(cpu, N, SE8(data));
}
void sh4_op_movwl(sh4_state* cpu) { puts("movwl unimplemented"); exit(1); }
void sh4_op_movll(sh4_state* cpu) { puts("movll unimplemented"); exit(1); }
void sh4_op_movbs(sh4_state* cpu) {
    bus_write8(cpu, sh4_get_reg(cpu, N), sh4_get_reg(cpu, M));
}
void sh4_op_movws(sh4_state* cpu) {
    bus_write16(cpu, sh4_get_reg(cpu, N), sh4_get_reg(cpu, M));
}
void sh4_op_movls(sh4_state* cpu) {
    bus_write32(cpu, sh4_get_reg(cpu, N), sh4_get_reg(cpu, M));
}
void sh4_op_movbp(sh4_state* cpu) { puts("movbp unimplemented"); exit(1); }
void sh4_op_movwp(sh4_state* cpu) { puts("movwp unimplemented"); exit(1); }
void sh4_op_movlp(sh4_state* cpu) { puts("movlp unimplemented"); exit(1); }
void sh4_op_movbm(sh4_state* cpu) { puts("movbm unimplemented"); exit(1); }
void sh4_op_movwm(sh4_state* cpu) { puts("movwm unimplemented"); exit(1); }
void sh4_op_movlm(sh4_state* cpu) { puts("movlm unimplemented"); exit(1); }
void sh4_op_movbl4(sh4_state* cpu) { puts("movbl4 unimplemented"); exit(1); }
void sh4_op_movwl4(sh4_state* cpu) { puts("movwl4 unimplemented"); exit(1); }
void sh4_op_movll4(sh4_state* cpu) { puts("movll4 unimplemented"); exit(1); }
void sh4_op_movbs4(sh4_state* cpu) { puts("movbs4 unimplemented"); exit(1); }
void sh4_op_movws4(sh4_state* cpu) { puts("movws4 unimplemented"); exit(1); }
void sh4_op_movls4(sh4_state* cpu) { puts("movls4 unimplemented"); exit(1); }
void sh4_op_movbl0(sh4_state* cpu) { puts("movbl0 unimplemented"); exit(1); }
void sh4_op_movwl0(sh4_state* cpu) { puts("movwl0 unimplemented"); exit(1); }
void sh4_op_movll0(sh4_state* cpu) { puts("movll0 unimplemented"); exit(1); }
void sh4_op_movbs0(sh4_state* cpu) { puts("movbs0 unimplemented"); exit(1); }
void sh4_op_movws0(sh4_state* cpu) {
    bus_write16(cpu, sh4_get_reg(cpu, 0) + sh4_get_reg(cpu, N), sh4_get_reg(cpu, M));
}
void sh4_op_movls0(sh4_state* cpu) { puts("movls0 unimplemented"); exit(1); }
void sh4_op_movblg(sh4_state* cpu) { puts("movblg unimplemented"); exit(1); }
void sh4_op_movwlg(sh4_state* cpu) { puts("movwlg unimplemented"); exit(1); }
void sh4_op_movllg(sh4_state* cpu) { puts("movllg unimplemented"); exit(1); }
void sh4_op_movbsg(sh4_state* cpu) { puts("movbsg unimplemented"); exit(1); }
void sh4_op_movwsg(sh4_state* cpu) { puts("movwsg unimplemented"); exit(1); }
void sh4_op_movlsg(sh4_state* cpu) { puts("movlsg unimplemented"); exit(1); }
void sh4_op_movt(sh4_state* cpu) { puts("movt unimplemented"); exit(1); }
void sh4_op_swapb(sh4_state* cpu) { puts("swapb unimplemented"); exit(1); }
void sh4_op_swapw(sh4_state* cpu) { puts("swapw unimplemented"); exit(1); }
void sh4_op_xtrct(sh4_state* cpu) { puts("xtrct unimplemented"); exit(1); }
void sh4_op_add(sh4_state* cpu) {
    int n = N;

    sh4_set_reg(cpu, n, sh4_get_reg(cpu, n) + sh4_get_reg(cpu, M));
}
void sh4_op_addi(sh4_state* cpu) {
    int n = N;

    sh4_set_reg(cpu, n, sh4_get_reg(cpu, n) + SE8(D));
}
void sh4_op_addc(sh4_state* cpu) { puts("addc unimplemented"); exit(1); }
void sh4_op_addv(sh4_state* cpu) { puts("addv unimplemented"); exit(1); }
void sh4_op_cmpim(sh4_state* cpu) { puts("cmpim unimplemented"); exit(1); }
void sh4_op_cmpeq(sh4_state* cpu) { puts("cmpeq unimplemented"); exit(1); }
void sh4_op_cmphs(sh4_state* cpu) { puts("cmphs unimplemented"); exit(1); }
void sh4_op_cmpge(sh4_state* cpu) { puts("cmpge unimplemented"); exit(1); }
void sh4_op_cmphi(sh4_state* cpu) { puts("cmphi unimplemented"); exit(1); }
void sh4_op_cmpgt(sh4_state* cpu) { puts("cmpgt unimplemented"); exit(1); }
void sh4_op_cmppl(sh4_state* cpu) { puts("cmppl unimplemented"); exit(1); }
void sh4_op_cmppz(sh4_state* cpu) { puts("cmppz unimplemented"); exit(1); }
void sh4_op_cmpstr(sh4_state* cpu) { puts("cmpstr unimplemented"); exit(1); }
void sh4_op_div0s(sh4_state* cpu) { puts("div0s unimplemented"); exit(1); }
void sh4_op_div0u(sh4_state* cpu) { puts("div0u unimplemented"); exit(1); }
void sh4_op_div1(sh4_state* cpu) { puts("div1 unimplemented"); exit(1); }
void sh4_op_dmuls(sh4_state* cpu) { puts("dmuls unimplemented"); exit(1); }
void sh4_op_dmulu(sh4_state* cpu) { puts("dmulu unimplemented"); exit(1); }
void sh4_op_dt(sh4_state* cpu) {
    int n = N;

    sh4_set_reg(cpu, n, sh4_get_reg(cpu, n) - 1);

    cpu->sr.t = !sh4_get_reg(cpu, n);
}
void sh4_op_extsb(sh4_state* cpu) { puts("extsb unimplemented"); exit(1); }
void sh4_op_extsw(sh4_state* cpu) { puts("extsw unimplemented"); exit(1); }
void sh4_op_extub(sh4_state* cpu) {
    sh4_set_reg(cpu, N, sh4_get_reg(cpu, M) & 0xff);
}
void sh4_op_extuw(sh4_state* cpu) { puts("extuw unimplemented"); exit(1); }
void sh4_op_macl(sh4_state* cpu) { puts("macl unimplemented"); exit(1); }
void sh4_op_macw(sh4_state* cpu) { puts("macw unimplemented"); exit(1); }
void sh4_op_mull(sh4_state* cpu) {
    cpu->macl = sh4_get_reg(cpu, N) * sh4_get_reg(cpu, M);
}
void sh4_op_muls(sh4_state* cpu) { puts("muls unimplemented"); exit(1); }
void sh4_op_mulu(sh4_state* cpu) { puts("mulu unimplemented"); exit(1); }
void sh4_op_neg(sh4_state* cpu) {
    sh4_set_reg(cpu, N, 0 - sh4_get_reg(cpu, M));
}
void sh4_op_negc(sh4_state* cpu) { puts("negc unimplemented"); exit(1); }
void sh4_op_sub(sh4_state* cpu) {
int n = N;

    sh4_set_reg(cpu, n, sh4_get_reg(cpu, n) - sh4_get_reg(cpu, M));
}
void sh4_op_subc(sh4_state* cpu) { puts("subc unimplemented"); exit(1); }
void sh4_op_subv(sh4_state* cpu) { puts("subv unimplemented"); exit(1); }
void sh4_op_and(sh4_state* cpu) {
    int n = N;

    sh4_set_reg(cpu, n, sh4_get_reg(cpu, n) & sh4_get_reg(cpu, M));
}
void sh4_op_andi(sh4_state* cpu) { puts("andi unimplemented"); exit(1); }
void sh4_op_andm(sh4_state* cpu) { puts("andm unimplemented"); exit(1); }
void sh4_op_not(sh4_state* cpu) { puts("not unimplemented"); exit(1); }
void sh4_op_or(sh4_state* cpu) { puts("or unimplemented"); exit(1); }
void sh4_op_ori(sh4_state* cpu) { puts("ori unimplemented"); exit(1); }
void sh4_op_orm(sh4_state* cpu) { puts("orm unimplemented"); exit(1); }
void sh4_op_tas(sh4_state* cpu) { puts("tas unimplemented"); exit(1); }
void sh4_op_tst(sh4_state* cpu) { puts("tst unimplemented"); exit(1); }
void sh4_op_tsti(sh4_state* cpu) { puts("tsti unimplemented"); exit(1); }
void sh4_op_tstm(sh4_state* cpu) { puts("tstm unimplemented"); exit(1); }
void sh4_op_xor(sh4_state* cpu) {
    int n = N;

    sh4_set_reg(cpu, n, sh4_get_reg(cpu, n) ^ sh4_get_reg(cpu, M));
}
void sh4_op_xori(sh4_state* cpu) { puts("xori unimplemented"); exit(1); }
void sh4_op_xorm(sh4_state* cpu) { puts("xorm unimplemented"); exit(1); }
void sh4_op_rotcl(sh4_state* cpu) { puts("rotcl unimplemented"); exit(1); }
void sh4_op_rotcr(sh4_state* cpu) { puts("rotcr unimplemented"); exit(1); }
void sh4_op_rotl(sh4_state* cpu) { puts("rotl unimplemented"); exit(1); }
void sh4_op_rotr(sh4_state* cpu) { puts("rotr unimplemented"); exit(1); }
void sh4_op_shad(sh4_state* cpu) { puts("shad unimplemented"); exit(1); }
void sh4_op_shal(sh4_state* cpu) { puts("shal unimplemented"); exit(1); }
void sh4_op_shar(sh4_state* cpu) { puts("shar unimplemented"); exit(1); }
void sh4_op_shld(sh4_state* cpu) { puts("shld unimplemented"); exit(1); }
void sh4_op_shll(sh4_state* cpu) { puts("shll unimplemented"); exit(1); }
void sh4_op_shll2(sh4_state* cpu) {
    int n = N;

    sh4_set_reg(cpu, n, sh4_get_reg(cpu, n) << 2);
}
void sh4_op_shll8(sh4_state* cpu) {
    int n = N;

    sh4_set_reg(cpu, n, sh4_get_reg(cpu, n) << 8);
}
void sh4_op_shll16(sh4_state* cpu) {
    int n = N;

    sh4_set_reg(cpu, n, sh4_get_reg(cpu, n) << 16);
}
void sh4_op_shlr(sh4_state* cpu) {
    int n = N;

    uint32_t r = sh4_get_reg(cpu, n);

    cpu->sr.t = r & 1;

    sh4_set_reg(cpu, n, r >> 1);
}
void sh4_op_shlr2(sh4_state* cpu) {
    int n = N;

    sh4_set_reg(cpu, n, sh4_get_reg(cpu, n) >> 2);
}
void sh4_op_shlr8(sh4_state* cpu) { puts("shlr8 unimplemented"); exit(1); }
void sh4_op_shlr16(sh4_state* cpu) {
    int n = N;

    sh4_set_reg(cpu, n, sh4_get_reg(cpu, n) >> 16);
}
void sh4_op_bf(sh4_state* cpu) {
    if (cpu->sr.t)
        return;

    sh4_set_pc(cpu, PC + 4 + (SE8(D) << 1));
}
void sh4_op_bfs(sh4_state* cpu) {
    if (cpu->sr.t)
        return;

    sh4_set_pc_delayed(cpu, PC + 4 + (SE8(D) << 1));
}
void sh4_op_bt(sh4_state* cpu) { puts("bt unimplemented"); exit(1); }
void sh4_op_bts(sh4_state* cpu) { puts("bts unimplemented"); exit(1); }
void sh4_op_bra(sh4_state* cpu) {
    sh4_set_pc_delayed(cpu, PC + 4 + (SE8(D) << 1));
}
void sh4_op_braf(sh4_state* cpu) { puts("braf unimplemented"); exit(1); }
void sh4_op_bsr(sh4_state* cpu) { puts("bsr unimplemented"); exit(1); }
void sh4_op_bsrf(sh4_state* cpu) { puts("bsrf unimplemented"); exit(1); }
void sh4_op_jmp(sh4_state* cpu) { puts("jmp unimplemented"); exit(1); }
void sh4_op_jsr(sh4_state* cpu) { puts("jsr unimplemented"); exit(1); }
void sh4_op_rts(sh4_state* cpu) { puts("rts unimplemented"); exit(1); }
void sh4_op_clrmac(sh4_state* cpu) { puts("clrmac unimplemented"); exit(1); }
void sh4_op_clrs(sh4_state* cpu) { puts("clrs unimplemented"); exit(1); }
void sh4_op_clrt(sh4_state* cpu) { puts("clrt unimplemented"); exit(1); }
void sh4_op_ldcsr(sh4_state* cpu) { puts("ldcsr unimplemented"); exit(1); }
void sh4_op_ldcmsr(sh4_state* cpu) { puts("ldcmsr unimplemented"); exit(1); }
void sh4_op_ldcgbr(sh4_state* cpu) { puts("ldcgbr unimplemented"); exit(1); }
void sh4_op_ldcmgbr(sh4_state* cpu) { puts("ldcmgbr unimplemented"); exit(1); }
void sh4_op_ldcvbr(sh4_state* cpu) { puts("ldcvbr unimplemented"); exit(1); }
void sh4_op_ldcmvbr(sh4_state* cpu) { puts("ldcmvbr unimplemented"); exit(1); }
void sh4_op_ldcssr(sh4_state* cpu) { puts("ldcssr unimplemented"); exit(1); }
void sh4_op_ldcmssr(sh4_state* cpu) { puts("ldcmssr unimplemented"); exit(1); }
void sh4_op_ldcspc(sh4_state* cpu) { puts("ldcspc unimplemented"); exit(1); }
void sh4_op_ldcmspc(sh4_state* cpu) { puts("ldcmspc unimplemented"); exit(1); }
void sh4_op_ldcdbr(sh4_state* cpu) { puts("ldcdbr unimplemented"); exit(1); }
void sh4_op_ldcmdbr(sh4_state* cpu) { puts("ldcmdbr unimplemented"); exit(1); }
void sh4_op_ldcrn_bank(sh4_state* cpu) { puts("ldcrn_bank unimplemented"); exit(1); }
void sh4_op_ldcmrn_bank(sh4_state* cpu) { puts("ldcmrn_bank unimplemented"); exit(1); }
void sh4_op_ldsmach(sh4_state* cpu) { puts("ldsmach unimplemented"); exit(1); }
void sh4_op_ldsmmach(sh4_state* cpu) { puts("ldsmmach unimplemented"); exit(1); }
void sh4_op_ldsmacl(sh4_state* cpu) { puts("ldsmacl unimplemented"); exit(1); }
void sh4_op_ldsmmacl(sh4_state* cpu) { puts("ldsmmacl unimplemented"); exit(1); }
void sh4_op_ldspr(sh4_state* cpu) { puts("ldspr unimplemented"); exit(1); }
void sh4_op_ldsmpr(sh4_state* cpu) { puts("ldsmpr unimplemented"); exit(1); }
void sh4_op_ldtlb(sh4_state* cpu) { puts("ldtlb unimplemented"); exit(1); }
void sh4_op_movcal(sh4_state* cpu) { puts("movcal unimplemented"); exit(1); }
void sh4_op_nop(sh4_state* cpu) {
    /* Do nothing */
}
void sh4_op_ocbi(sh4_state* cpu) { puts("ocbi unimplemented"); exit(1); }
void sh4_op_ocbp(sh4_state* cpu) { puts("ocbp unimplemented"); exit(1); }
void sh4_op_ocbwb(sh4_state* cpu) { puts("ocbwb unimplemented"); exit(1); }
void sh4_op_pref(sh4_state* cpu) { puts("pref unimplemented"); exit(1); }
void sh4_op_rte(sh4_state* cpu) { puts("rte unimplemented"); exit(1); }
void sh4_op_sets(sh4_state* cpu) { puts("sets unimplemented"); exit(1); }
void sh4_op_sett(sh4_state* cpu) { puts("sett unimplemented"); exit(1); }
void sh4_op_sleep(sh4_state* cpu) { puts("sleep unimplemented"); exit(1); }
void sh4_op_stcsr(sh4_state* cpu) { puts("stcsr unimplemented"); exit(1); }
void sh4_op_stcmsr(sh4_state* cpu) { puts("stcmsr unimplemented"); exit(1); }
void sh4_op_stcgbr(sh4_state* cpu) { puts("stcgbr unimplemented"); exit(1); }
void sh4_op_stcmgbr(sh4_state* cpu) { puts("stcmgbr unimplemented"); exit(1); }
void sh4_op_stcvbr(sh4_state* cpu) { puts("stcvbr unimplemented"); exit(1); }
void sh4_op_stcmvbr(sh4_state* cpu) { puts("stcmvbr unimplemented"); exit(1); }
void sh4_op_stcsgr(sh4_state* cpu) { puts("stcsgr unimplemented"); exit(1); }
void sh4_op_stcmsgr(sh4_state* cpu) { puts("stcmsgr unimplemented"); exit(1); }
void sh4_op_stcssr(sh4_state* cpu) { puts("stcssr unimplemented"); exit(1); }
void sh4_op_stcmssr(sh4_state* cpu) { puts("stcmssr unimplemented"); exit(1); }
void sh4_op_stcspc(sh4_state* cpu) { puts("stcspc unimplemented"); exit(1); }
void sh4_op_stcmspc(sh4_state* cpu) { puts("stcmspc unimplemented"); exit(1); }
void sh4_op_stcdbr(sh4_state* cpu) { puts("stcdbr unimplemented"); exit(1); }
void sh4_op_stcmdbr(sh4_state* cpu) { puts("stcmdbr unimplemented"); exit(1); }
void sh4_op_stcrm_bank(sh4_state* cpu) { puts("stcrm_bank unimplemented"); exit(1); }
void sh4_op_stcmrm_bank(sh4_state* cpu) { puts("stcmrm_bank unimplemented"); exit(1); }
void sh4_op_stsmach(sh4_state* cpu) { puts("stsmach unimplemented"); exit(1); }
void sh4_op_stsmmach(sh4_state* cpu) { puts("stsmmach unimplemented"); exit(1); }
void sh4_op_stsmacl(sh4_state* cpu) {
    sh4_set_reg(cpu, N, cpu->macl);
}
void sh4_op_stsmmacl(sh4_state* cpu) { puts("stsmmacl unimplemented"); exit(1); }
void sh4_op_stspr(sh4_state* cpu) { puts("stspr unimplemented"); exit(1); }
void sh4_op_stsmpr(sh4_state* cpu) { puts("stsmpr unimplemented"); exit(1); }
void sh4_op_trapa(sh4_state* cpu) { puts("trapa unimplemented"); exit(1); }
void sh4_op_fmov(sh4_state* cpu) {
    FR(N).f = FR(M).f;
}
void sh4_op_fmov_load(sh4_state* cpu) {
    FR(N).u32 = bus_read32(cpu, sh4_get_reg(cpu, M));
}
void sh4_op_fmov_store(sh4_state* cpu) { puts("fmov_store unimplemented"); exit(1); }
void sh4_op_fmov_restore(sh4_state* cpu) { puts("fmov_restore unimplemented"); exit(1); }
void sh4_op_fmov_save(sh4_state* cpu) { puts("fmov_save unimplemented"); exit(1); }
void sh4_op_fmov_index_load(sh4_state* cpu) { puts("fmov_index_load unimplemented"); exit(1); }
void sh4_op_fmov_index_store(sh4_state* cpu) { puts("fmov_index_store unimplemented"); exit(1); }
void sh4_op_fmov_dr(sh4_state* cpu) { puts("fmov_dr unimplemented"); exit(1); }
void sh4_op_fmov_drxd(sh4_state* cpu) { puts("fmov_drxd unimplemented"); exit(1); }
void sh4_op_fmov_xddr(sh4_state* cpu) { puts("fmov_xddr unimplemented"); exit(1); }
void sh4_op_fmov_xdxd(sh4_state* cpu) { puts("fmov_xdxd unimplemented"); exit(1); }
void sh4_op_fmov_load_dr(sh4_state* cpu) { puts("fmov_load_dr unimplemented"); exit(1); }
void sh4_op_fmov_load_xd(sh4_state* cpu) { puts("fmov_load_xd unimplemented"); exit(1); }
void sh4_op_fmov_store_dr(sh4_state* cpu) { puts("fmov_store_dr unimplemented"); exit(1); }
void sh4_op_fmov_store_xd(sh4_state* cpu) { puts("fmov_store_xd unimplemented"); exit(1); }
void sh4_op_fmov_restore_dr(sh4_state* cpu) { puts("fmov_restore_dr unimplemented"); exit(1); }
void sh4_op_fmov_restore_xd(sh4_state* cpu) { puts("fmov_restore_xd unimplemented"); exit(1); }
void sh4_op_fmov_save_dr(sh4_state* cpu) { puts("fmov_save_dr unimplemented"); exit(1); }
void sh4_op_fmov_save_xd(sh4_state* cpu) { puts("fmov_save_xd unimplemented"); exit(1); }
void sh4_op_fmov_index_load_dr(sh4_state* cpu) { puts("fmov_index_load_dr unimplemented"); exit(1); }
void sh4_op_fmov_index_load_xd(sh4_state* cpu) { puts("fmov_index_load_xd unimplemented"); exit(1); }
void sh4_op_fmov_index_store_dr(sh4_state* cpu) { puts("fmov_index_store_dr unimplemented"); exit(1); }
void sh4_op_fmov_index_store_xd(sh4_state* cpu) { puts("fmov_index_store_xd unimplemented"); exit(1); }
void sh4_op_fldi0(sh4_state* cpu) { puts("fldi0 unimplemented"); exit(1); }
void sh4_op_fldi1(sh4_state* cpu) { puts("fldi1 unimplemented"); exit(1); }
void sh4_op_flds(sh4_state* cpu) { puts("flds unimplemented"); exit(1); }
void sh4_op_fsts(sh4_state* cpu) { puts("fsts unimplemented"); exit(1); }
void sh4_op_fabs_fr(sh4_state* cpu) { puts("fabs_fr unimplemented"); exit(1); }
void sh4_op_fneg_fr(sh4_state* cpu) { puts("fneg_fr unimplemented"); exit(1); }
void sh4_op_fadd_fr(sh4_state* cpu) {
    FR(N).f += FR(M).f;
}
void sh4_op_fsub_fr(sh4_state* cpu) { puts("fsub_fr unimplemented"); exit(1); }
void sh4_op_fmul_fr(sh4_state* cpu) {
    FR(N).f *= FR(M).f;
}
void sh4_op_fmac(sh4_state* cpu) { puts("fmac unimplemented"); exit(1); }
void sh4_op_fdiv_fr(sh4_state* cpu) {
    FR(N).f /= FR(M).f;
}
void sh4_op_fsqrt_fr(sh4_state* cpu) { puts("fsqrt_fr unimplemented"); exit(1); }
void sh4_op_fsrra(sh4_state* cpu) { puts("fsrra unimplemented"); exit(1); }
void sh4_op_fcmp_eq_fr(sh4_state* cpu) { puts("fcmp_eq_fr unimplemented"); exit(1); }
void sh4_op_fcmp_gt_fr(sh4_state* cpu) { puts("fcmp_gt_fr unimplemented"); exit(1); }
void sh4_op_float_single(sh4_state* cpu) {
    FR(N).f = (float)cpu->fpul;
}
void sh4_op_ftrc_single(sh4_state* cpu) {
    cpu->fpul = (long)FR(N).f;
}
void sh4_op_fipr(sh4_state* cpu) { puts("fipr unimplemented"); exit(1); }
void sh4_op_fsca(sh4_state* cpu) {
    if (cpu->fpscr.pr)
        ERROR_EXIT("fsca unsupported operation");

    int n = N;

    float t = (float)(cpu->fpul & 0x0000FFFF);
    long offset = 0x00010000;

    t = 2.0f * M_PI * t / offset;

    FR(n).f = sinf(t);
    FR(n + 1).f = cosf(t);
}
void sh4_op_ftrv(sh4_state* cpu) { puts("ftrv unimplemented"); exit(1); }
void sh4_op_fabs_dr(sh4_state* cpu) { puts("fabs_dr unimplemented"); exit(1); }
void sh4_op_fneg_dr(sh4_state* cpu) { puts("fneg_dr unimplemented"); exit(1); }
void sh4_op_fadd_dr(sh4_state* cpu) { puts("fadd_dr unimplemented"); exit(1); }
void sh4_op_fsub_dr(sh4_state* cpu) { puts("fsub_dr unimplemented"); exit(1); }
void sh4_op_fmul_dr(sh4_state* cpu) { puts("fmul_dr unimplemented"); exit(1); }
void sh4_op_fdiv_dr(sh4_state* cpu) { puts("fdiv_dr unimplemented"); exit(1); }
void sh4_op_fsqrt_dr(sh4_state* cpu) { puts("fsqrt_dr unimplemented"); exit(1); }
void sh4_op_fcmp_eq_dr(sh4_state* cpu) { puts("fcmp_eq_dr unimplemented"); exit(1); }
void sh4_op_fcmp_gt_dr(sh4_state* cpu) { puts("fcmp_gt_dr unimplemented"); exit(1); }
void sh4_op_float_double(sh4_state* cpu) { puts("float_double unimplemented"); exit(1); }
void sh4_op_ftrc_double(sh4_state* cpu) { puts("ftrc_double unimplemented"); exit(1); }
void sh4_op_fcnvds(sh4_state* cpu) { puts("fcnvds unimplemented"); exit(1); }
void sh4_op_fcnvsd(sh4_state* cpu) { puts("fcnvsd unimplemented"); exit(1); }
void sh4_op_ldsfpscr(sh4_state* cpu) { puts("ldsfpscr unimplemented"); exit(1); }
void sh4_op_stsfpscr(sh4_state* cpu) { puts("stsfpscr unimplemented"); exit(1); }
void sh4_op_ldsmfpscr(sh4_state* cpu) { puts("ldsmfpscr unimplemented"); exit(1); }
void sh4_op_stsmfpscr(sh4_state* cpu) { puts("stsmfpscr unimplemented"); exit(1); }
void sh4_op_ldsfpul(sh4_state* cpu) {
    cpu->fpul = sh4_get_reg(cpu, N);
}
void sh4_op_stsfpul(sh4_state* cpu) {
    sh4_set_reg(cpu, N, cpu->fpul);
}
void sh4_op_ldsmfpul(sh4_state* cpu) { puts("ldsmfpul unimplemented"); exit(1); }
void sh4_op_stsmfpul(sh4_state* cpu) { puts("stsmfpul unimplemented"); exit(1); }
void sh4_op_frchg(sh4_state* cpu) { puts("frchg unimplemented"); exit(1); }
void sh4_op_fschg(sh4_state* cpu) { puts("fschg unimplemented"); exit(1); }