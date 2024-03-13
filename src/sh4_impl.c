#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define M_PI 3.14159265358979323846

#include "sh4.h"
#include "sh4_dis.h"

#define N ((cpu->opcode >> 8) & 0xf)
#define M ((cpu->opcode >> 4) & 0xf)
#define D4 (cpu->opcode & 0xf)
#define D8 (cpu->opcode & 0xff)
#define D12 (cpu->opcode & 0xfff)
#define PC (cpu->pc[0] - 2)
#define SE8(v) ((int32_t)(v << 24) >> 24)
#define SE12(v) ((int32_t)(v << 20) >> 20)
#define SE16(v) ((int32_t)(v << 16) >> 16)
#define S16(v) ((int32_t)((int16_t)(v)))
#define FR(n) cpu->fb[cpu->fpscr.fr].f[n]
#define R(n) *sh4_get_reg(cpu, n)

#define ERROR_EXIT(msg) { puts(msg); exit(1); }

uint32_t bus_read8(sh4_state* cpu, uint32_t addr) {
    return cpu->bus.read8(cpu->bus.udata, addr);
}

uint32_t bus_read16(sh4_state* cpu, uint32_t addr) {
    return cpu->bus.read16(cpu->bus.udata, addr);
}

uint32_t bus_read32(sh4_state* cpu, uint32_t addr) {
    if (addr == 0xa05f6900)
        return 8;

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
    R(N) = R(M);
}
void sh4_op_movi(sh4_state* cpu) {
    R(N) = SE8(D8);
}
void sh4_op_mova(sh4_state* cpu) {
    R(0) = (D8 << 2) + (PC & 0xfffffffc) + 4;
}
void sh4_op_movwi(sh4_state* cpu) {
    R(N) = SE16(bus_read16(cpu, (D8 << 1) + PC + 4));
}
void sh4_op_movli(sh4_state* cpu) {
    R(N) = bus_read32(cpu, (D8 << 2) + (PC & 0xfffffffc) + 4);
}
void sh4_op_movbl(sh4_state* cpu) {
    R(N) = SE8(bus_read8(cpu, R(M)));
}
void sh4_op_movwl(sh4_state* cpu) {
    R(N) = SE16(bus_read16(cpu, R(M)));
}
void sh4_op_movll(sh4_state* cpu) {
    R(N) = bus_read32(cpu, R(M));
}
void sh4_op_movbs(sh4_state* cpu) {
    bus_write8(cpu, R(N), R(M));
}
void sh4_op_movws(sh4_state* cpu) {
    bus_write16(cpu, R(N), R(M));
}
void sh4_op_movls(sh4_state* cpu) {
    bus_write32(cpu, R(N), R(M));
}
void sh4_op_movbp(sh4_state* cpu) {
    int n = N;
    int m = M;

    uint32_t* rm = sh4_get_reg(cpu, m);

    R(n) = SE8(bus_read8(cpu, *rm));

    if (n != m)
        *rm += 1;
}
void sh4_op_movwp(sh4_state* cpu) { puts("movwp unimplemented"); exit(1); }
void sh4_op_movlp(sh4_state* cpu) {
    int n = N;
    int m = M;

    uint32_t* rm = sh4_get_reg(cpu, m);

    R(n) = bus_read32(cpu, *rm);

    if (n != m)
        *rm += 4;
}
void sh4_op_movbm(sh4_state* cpu) { puts("movbm unimplemented"); exit(1); }
void sh4_op_movwm(sh4_state* cpu) {
    uint32_t* rn = sh4_get_reg(cpu, N);

    *rn -= 2;

    bus_write16(cpu, *rn, R(M));
}
void sh4_op_movlm(sh4_state* cpu) {
    uint32_t* rn = sh4_get_reg(cpu, N);

    *rn -= 4;

    bus_write32(cpu, *rn, R(M));
}
void sh4_op_movbl4(sh4_state* cpu) {
    R(0) = SE8(bus_read8(cpu, D4 + R(M)));
}
void sh4_op_movwl4(sh4_state* cpu) {
    R(0) = SE16(bus_read16(cpu, (D4 << 1) + R(M)));
}
void sh4_op_movll4(sh4_state* cpu) {
    R(N) = bus_read32(cpu, (D4 << 2) + R(M));
}
void sh4_op_movbs4(sh4_state* cpu) {
    bus_write8(cpu, D4 + R(M), R(0));
}
void sh4_op_movws4(sh4_state* cpu) {
    bus_write16(cpu, (D4 << 1) + R(M), R(0));
}
void sh4_op_movls4(sh4_state* cpu) {
    bus_write32(cpu, (D4 << 2) + R(N), R(M));
}
void sh4_op_movbl0(sh4_state* cpu) {
    R(N) = SE8(bus_read8(cpu, R(0) + R(M)));
}
void sh4_op_movwl0(sh4_state* cpu) {
    R(N) = SE16(bus_read16(cpu, R(0) + R(M)));
}
void sh4_op_movll0(sh4_state* cpu) {
    R(N) = bus_read32(cpu, R(0) + R(M));
}
void sh4_op_movbs0(sh4_state* cpu) {
    bus_write8(cpu, R(0) + R(N), R(M));
}
void sh4_op_movws0(sh4_state* cpu) {
    bus_write16(cpu, R(0) + R(N), R(M));
}
void sh4_op_movls0(sh4_state* cpu) {
    bus_write32(cpu, R(0) + R(N), R(M));
}
void sh4_op_movblg(sh4_state* cpu) { puts("movblg unimplemented"); exit(1); }
void sh4_op_movwlg(sh4_state* cpu) { puts("movwlg unimplemented"); exit(1); }
void sh4_op_movllg(sh4_state* cpu) { puts("movllg unimplemented"); exit(1); }
void sh4_op_movbsg(sh4_state* cpu) { puts("movbsg unimplemented"); exit(1); }
void sh4_op_movwsg(sh4_state* cpu) { puts("movwsg unimplemented"); exit(1); }
void sh4_op_movlsg(sh4_state* cpu) { puts("movlsg unimplemented"); exit(1); }
void sh4_op_movt(sh4_state* cpu) {
    R(N) = (uint32_t)cpu->sr.t;
}
void sh4_op_swapb(sh4_state* cpu) { puts("swapb unimplemented"); exit(1); }
void sh4_op_swapw(sh4_state* cpu) {
    // uint32_t rm = R(M);

    // R(N) = ((rm >> 8) | (rm << 8)) & 0xffff;
    uint32_t rm = R(M);

    R(N) = (rm >> 16) | (rm << 16);
}
void sh4_op_xtrct(sh4_state* cpu) { puts("xtrct unimplemented"); exit(1); }
void sh4_op_add(sh4_state* cpu) {
    R(N) += R(M);
}
void sh4_op_addi(sh4_state* cpu) {
    R(N) += SE8(D8);
}
void sh4_op_addc(sh4_state* cpu) {
    uint32_t* rn = sh4_get_reg(cpu, N);

    unsigned long tmp0, tmp1;

    tmp1 = *rn + R(M);
    tmp0 = *rn;

    *rn = tmp1 + (uint32_t)cpu->sr.t;

    cpu->sr.t = tmp0 > tmp1;

    if (tmp1 > *rn)
        cpu->sr.t = 1;
}
void sh4_op_addv(sh4_state* cpu) { puts("addv unimplemented"); exit(1); }
void sh4_op_cmpim(sh4_state* cpu) {
    cpu->sr.t = R(0) == SE8(D8);
}
void sh4_op_cmpeq(sh4_state* cpu) {
    cpu->sr.t = R(N) == R(M);
}
void sh4_op_cmphs(sh4_state* cpu) {
    cpu->sr.t = R(N) >= R(M);
}
void sh4_op_cmpge(sh4_state* cpu) {
    cpu->sr.t = ((int32_t)R(N)) >= ((int32_t)R(M));
}
void sh4_op_cmphi(sh4_state* cpu) { puts("cmphi unimplemented"); exit(1); }
void sh4_op_cmpgt(sh4_state* cpu) {
    cpu->sr.t = (long)R(N) > (long)R(M);
}
void sh4_op_cmppl(sh4_state* cpu) { puts("cmppl unimplemented"); exit(1); }
void sh4_op_cmppz(sh4_state* cpu) {
    cpu->sr.t = ((int32_t)R(N)) >= 0;
}
void sh4_op_cmpstr(sh4_state* cpu) {
    uint32_t t = R(N) ^ R(M);

    cpu->sr.t = !(
        (t & 0xff000000) &&
        (t & 0x00ff0000) &&
        (t & 0x0000ff00) &&
        (t & 0x000000ff)
    );
}
void sh4_op_div0s(sh4_state* cpu) {
    cpu->sr.q = !!(R(N) & 0x80000000);
    cpu->sr.m = !!(R(M) & 0x80000000);
    cpu->sr.t = cpu->sr.m != cpu->sr.q;
}
void sh4_op_div0u(sh4_state* cpu) {
    cpu->sr.q = 0;
    cpu->sr.m = 0;
    cpu->sr.t = 0;
}
void sh4_op_div1(sh4_state* cpu) {
    unsigned long tmp0, tmp2;
    unsigned char old_q, tmp1;

    uint32_t* rn = sh4_get_reg(cpu, N);

    old_q = cpu->sr.q;

    cpu->sr.q = (*rn & 0x80000000) != 0;

    tmp2 = R(M);

    *rn = (*rn << 1) | (uint32_t)cpu->sr.t;

    if (old_q == 0) {
        if (cpu->sr.m == 0) {
            tmp0 = *rn;
            *rn -= tmp2;
            tmp1 = *rn > tmp0;

            cpu->sr.q = cpu->sr.q ? !tmp1 : !!tmp1;
        } else {
            tmp0 = *rn;
            *rn += tmp2;
            tmp1 = *rn < tmp0;

            cpu->sr.q = cpu->sr.q ? !!tmp1 : !tmp1;
        }
    } else {
        if (!cpu->sr.m) {
            tmp0 = *rn;
            *rn += tmp2;
            tmp1 = *rn < tmp0;

            cpu->sr.q = cpu->sr.q ? !tmp1 : !!tmp1;
        } else {
            tmp0 = *rn;
            *rn -= tmp2;
            tmp1 = *rn > tmp0;

            cpu->sr.q = cpu->sr.q ? !!tmp1 : !tmp1;
        }
    }

    cpu->sr.t = cpu->sr.q == cpu->sr.m;
}
void sh4_op_dmuls(sh4_state* cpu) { puts("dmuls unimplemented"); exit(1); }
void sh4_op_dmulu(sh4_state* cpu) { puts("dmulu unimplemented"); exit(1); }
void sh4_op_dt(sh4_state* cpu) {
    uint32_t* rn = sh4_get_reg(cpu, N);

    *rn -= 1;

    cpu->sr.t = !(*rn);
}
void sh4_op_extsb(sh4_state* cpu) {
    R(N) = SE8(R(M));
}
void sh4_op_extsw(sh4_state* cpu) {
    R(N) = SE16(R(M));
}
void sh4_op_extub(sh4_state* cpu) {
    R(N) = R(M) & 0xff;
}
void sh4_op_extuw(sh4_state* cpu) { puts("extuw unimplemented"); exit(1); }
void sh4_op_macl(sh4_state* cpu) { puts("macl unimplemented"); exit(1); }
void sh4_op_macw(sh4_state* cpu) { puts("macw unimplemented"); exit(1); }
void sh4_op_mull(sh4_state* cpu) {
    cpu->macl = R(N) * R(M);
}
void sh4_op_muls(sh4_state* cpu) {
    cpu->macl = SE16(R(N)) * SE16(R(M));
}
void sh4_op_mulu(sh4_state* cpu) {
    cpu->macl = (R(N) & 0xffff) * (R(M) & 0xffff);
}
void sh4_op_neg(sh4_state* cpu) {
    sh4_set_reg(cpu, N, 0 - R(M));
}
void sh4_op_negc(sh4_state* cpu) { puts("negc unimplemented"); exit(1); }
void sh4_op_sub(sh4_state* cpu) {
    R(N) -= R(M);
}
void sh4_op_subc(sh4_state* cpu) {
    uint32_t tmp0, tmp1;
    uint32_t* rn = sh4_get_reg(cpu, N);
    uint32_t rm = R(M);

    tmp0 = *rn;
    tmp1 = *rn - rm;

    *rn = tmp1 - (uint32_t)cpu->sr.t;

    cpu->sr.t = tmp0 < tmp1;

    if (tmp1 < *rn)
        cpu->sr.t = 1;
}
void sh4_op_subv(sh4_state* cpu) { puts("subv unimplemented"); exit(1); }
void sh4_op_and(sh4_state* cpu) {
    R(N) &= R(M);
}
void sh4_op_andi(sh4_state* cpu) {
    R(0) &= D8;
}
void sh4_op_andm(sh4_state* cpu) { puts("andm unimplemented"); exit(1); }
void sh4_op_not(sh4_state* cpu) {
    R(N) = ~R(M);
}
void sh4_op_or(sh4_state* cpu) {
    R(N) |= R(M);
}
void sh4_op_ori(sh4_state* cpu) {
    R(0) |= D8;
}
void sh4_op_orm(sh4_state* cpu) { puts("orm unimplemented"); exit(1); }
void sh4_op_tas(sh4_state* cpu) { puts("tas unimplemented"); exit(1); }
void sh4_op_tst(sh4_state* cpu) {
    cpu->sr.t = !(R(N) & R(M));
}
void sh4_op_tsti(sh4_state* cpu) {
    cpu->sr.t = !(R(0) & D8);
}
void sh4_op_tstm(sh4_state* cpu) { puts("tstm unimplemented"); exit(1); }
void sh4_op_xor(sh4_state* cpu) {
    R(N) ^= R(M);
}
void sh4_op_xori(sh4_state* cpu) { puts("xori unimplemented"); exit(1); }
void sh4_op_xorm(sh4_state* cpu) { puts("xorm unimplemented"); exit(1); }
void sh4_op_rotcl(sh4_state* cpu) {
    uint32_t* rn = sh4_get_reg(cpu, N);

    unsigned int msb = !!(*rn & 0x80000000);

    *rn = (*rn << 1) | cpu->sr.t;

    cpu->sr.t = msb;
}
void sh4_op_rotcr(sh4_state* cpu) {
    uint32_t* rn = sh4_get_reg(cpu, N);

    unsigned int lsb = !!(*rn & 1);

    *rn = (*rn >> 1) | (cpu->sr.t << 31);

    cpu->sr.t = lsb;
}
void sh4_op_rotl(sh4_state* cpu) { puts("rotl unimplemented"); exit(1); }
void sh4_op_rotr(sh4_state* cpu) {
    uint32_t* rn = sh4_get_reg(cpu, N);

    cpu->sr.t = *rn & 1;

    *rn = (*rn >> 1) | (cpu->sr.t << 31);
}
void sh4_op_shad(sh4_state* cpu) { puts("shad unimplemented"); exit(1); }
void sh4_op_shal(sh4_state* cpu) { puts("shal unimplemented"); exit(1); }
void sh4_op_shar(sh4_state* cpu) {
    uint32_t* rn = sh4_get_reg(cpu, N);

    cpu->sr.t = *rn & 1;

    *rn = (*rn >> 1) | (*rn & 0x80000000);
}
void sh4_op_shld(sh4_state* cpu) {
    uint32_t* rn = sh4_get_reg(cpu, N);
    uint32_t* rm = sh4_get_reg(cpu, M);

    if (((int32_t)*rm) >= 0)
        *rn <<= *rm & 0x1f;
    else if (*rm == 0)
        *rn = 0;
    else
        *rn = (uint32_t)*rn >> ((~(*rm) & 0x1f) + 1);
}
void sh4_op_shll(sh4_state* cpu) {
    uint32_t* rn = sh4_get_reg(cpu, N);

    cpu->sr.t = !!(*rn & 0x80000000);

    *rn <<= 1;
}
void sh4_op_shll2(sh4_state* cpu) {
    R(N) <<= 2;
}
void sh4_op_shll8(sh4_state* cpu) {
    R(N) <<= 8;
}
void sh4_op_shll16(sh4_state* cpu) {
    R(N) <<= 16;
}
void sh4_op_shlr(sh4_state* cpu) {
    uint32_t* rn = sh4_get_reg(cpu, N);

    cpu->sr.t = *rn & 1;

    *rn >>= 1;
}
void sh4_op_shlr2(sh4_state* cpu) {
    R(N) >>= 2;
}
void sh4_op_shlr8(sh4_state* cpu) {
    R(N) >>= 8;
}
void sh4_op_shlr16(sh4_state* cpu) {
    R(N) >>= 16;
}
void sh4_op_bf(sh4_state* cpu) {
    if (cpu->sr.t)
        return;

    sh4_set_pc(cpu, PC + 4 + (SE8(D8) << 1));
}
void sh4_op_bfs(sh4_state* cpu) {
    if (cpu->sr.t)
        return;

    sh4_set_pc_delayed(cpu, PC + 4 + (SE8(D8) << 1));
}
void sh4_op_bt(sh4_state* cpu) { 
    if (!cpu->sr.t)
        return;

    sh4_set_pc(cpu, PC + 4 + (SE8(D8) << 1));
}
void sh4_op_bts(sh4_state* cpu) {
    if (!cpu->sr.t)
        return;

    sh4_set_pc_delayed(cpu, PC + 4 + (SE8(D8) << 1));
}
void sh4_op_bra(sh4_state* cpu) {
    sh4_set_pc_delayed(cpu, PC + 4 + (SE8(D8) << 1));
}
void sh4_op_braf(sh4_state* cpu) { puts("braf unimplemented"); exit(1); }
void sh4_op_bsr(sh4_state* cpu) {
    cpu->pr = PC + 4;

    sh4_set_pc_delayed(cpu, (SE12(D12) << 1) + PC + 4);
}
void sh4_op_bsrf(sh4_state* cpu) { puts("bsrf unimplemented"); exit(1); }
void sh4_op_jmp(sh4_state* cpu) {
    sh4_set_pc_delayed(cpu, R(N));
}
void sh4_op_jsr(sh4_state* cpu) {
    cpu->pr = PC + 4;

    sh4_set_pc_delayed(cpu, R(N));
}
void sh4_op_rts(sh4_state* cpu) {
    sh4_set_pc_delayed(cpu, cpu->pr);
}
void sh4_op_clrmac(sh4_state* cpu) { puts("clrmac unimplemented"); exit(1); }
void sh4_op_clrs(sh4_state* cpu) { puts("clrs unimplemented"); exit(1); }
void sh4_op_clrt(sh4_state* cpu) { puts("clrt unimplemented"); exit(1); }
void sh4_op_ldcsr(sh4_state* cpu) {
    cpu->sr.u32 = R(N);
}
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
void sh4_op_ldspr(sh4_state* cpu) {
    cpu->pr = R(N);
}
void sh4_op_ldsmpr(sh4_state* cpu) {
    uint32_t* rn = sh4_get_reg(cpu, N);

    cpu->pr = bus_read32(cpu, *rn);

    *rn += 4;
}
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
void sh4_op_stcsr(sh4_state* cpu) {
    R(N) = cpu->sr.u32;
}
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
    R(N) = cpu->macl;
}
void sh4_op_stsmmacl(sh4_state* cpu) { puts("stsmmacl unimplemented"); exit(1); }
void sh4_op_stspr(sh4_state* cpu) { puts("stspr unimplemented"); exit(1); }
void sh4_op_stsmpr(sh4_state* cpu) {
    uint32_t* rn = sh4_get_reg(cpu, N);

    *rn -= 4;

    bus_write32(cpu, *rn, cpu->pr);
}
void sh4_op_trapa(sh4_state* cpu) { puts("trapa unimplemented"); exit(1); }
void sh4_op_fmov(sh4_state* cpu) {
    FR(N).f = FR(M).f;
}
void sh4_op_fmov_load(sh4_state* cpu) {
    FR(N).u32 = bus_read32(cpu, R(M));
}
void sh4_op_fmov_store(sh4_state* cpu) {
    bus_write32(cpu, R(N), FR(M).u32);
}
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
void sh4_op_fabs_fr(sh4_state* cpu) {
    FR(N).u32 &= 0x7fffffff;
}
void sh4_op_fneg_fr(sh4_state* cpu) { puts("fneg_fr unimplemented"); exit(1); }
void sh4_op_fadd_fr(sh4_state* cpu) {
    FR(N).f += FR(M).f;
}
void sh4_op_fsub_fr(sh4_state* cpu) {
    FR(N).f -= FR(M).f;
}
void sh4_op_fmul_fr(sh4_state* cpu) {
    FR(N).f *= FR(M).f;
}
void sh4_op_fmac(sh4_state* cpu) {
    FR(N).f += FR(M).f * FR(0).f;
}
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

    float t = (float)(cpu->fpul & 0x0000FFFF);

    t = 2.0f * M_PI * t / 0x00010000L;

    int n = N;

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
    cpu->fpul = R(N);
}
void sh4_op_stsfpul(sh4_state* cpu) {
    R(N) = cpu->fpul;
}
void sh4_op_ldsmfpul(sh4_state* cpu) { puts("ldsmfpul unimplemented"); exit(1); }
void sh4_op_stsmfpul(sh4_state* cpu) { puts("stsmfpul unimplemented"); exit(1); }
void sh4_op_frchg(sh4_state* cpu) { puts("frchg unimplemented"); exit(1); }
void sh4_op_fschg(sh4_state* cpu) { puts("fschg unimplemented"); exit(1); }