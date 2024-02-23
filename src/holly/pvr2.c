#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "pvr2.h"

pvr2_state* pvr2_create() {
    return malloc(sizeof(pvr2_state));
}

void pvr2_init(pvr2_state* pvr2, vram_state* vram) {
    memset(pvr2, 0, sizeof(pvr2_state));

    pvr2->vram = vram;
}

uint32_t pvr2_read32(void* udata, uint32_t addr) {
    pvr2_state* pvr2 = udata;

    switch (addr) {
        case PVR2_ID:          return 0x17fd11db;
        case PVR2_REVISION:    return 0x00000011;
        case PVR2_SPG_CONTROL: return pvr2->spg_control;
    }

    printf("unhandled PVR2 read %08x\n", addr);

    return 0;
}

uint32_t pvr2_read16(void* udata, uint32_t addr) {
    pvr2_state* pvr2 = udata;

    return 0;
}

uint32_t pvr2_read8(void* udata, uint32_t addr) {
    pvr2_state* pvr2 = udata;

    return 0;
}

void pvr2_write32(void* udata, uint32_t addr, uint32_t data) {
    pvr2_state* pvr2 = udata;

    switch (addr) {
        case PVR2_ID:                   pvr2->id = data; return;
        case PVR2_REVISION:             pvr2->revision = data; return;
        case PVR2_SOFTRESET:            pvr2->softreset = data; return;
        case PVR2_STARTRENDER:          pvr2->startrender = data; return;
        case PVR2_TEST_SELECT:          pvr2->test_select = data; return;
        case PVR2_PARAM_BASE:           pvr2->param_base = data; return;
        case PVR2_REGION_BASE:          pvr2->region_base = data; return;
        case PVR2_SPAN_SOFT_CFG:        pvr2->span_soft_cfg = data; return;
        case PVR2_VO_BORDER_COL:        pvr2->vo_border_col = data; return;
        case PVR2_FB_R_CTRL:            pvr2->fb_r_ctrl = data; return;
        case PVR2_FB_W_CTRL:            pvr2->fb_w_ctrl = data; return;
        case PVR2_FB_LINESTRIDE:        pvr2->fb_linestride = data; return;
        case PVR2_FB_R_SOF1:            pvr2->fb_r_sof1 = data; return;
        case PVR2_FB_R_SOF2:            pvr2->fb_r_sof2 = data; return;
        case PVR2_FB_R_SIZE:            pvr2->fb_r_size = data; return;
        case PVR2_FB_W_SOF1:            pvr2->fb_w_sof1 = data; return;
        case PVR2_FB_W_SOF2:            pvr2->fb_w_sof2 = data; return;
        case PVR2_FB_X_CLIP:            pvr2->fb_x_clip = data; return;
        case PVR2_FB_Y_CLIP:            pvr2->fb_y_clip = data; return;
        case PVR2_FPU_SHAD_SCALE:       pvr2->fpu_shad_scale = data; return;
        case PVR2_FPU_CULL_VAL:         pvr2->fpu_cull_val = data; return;
        case PVR2_FPU_PARAM_CFG:        pvr2->fpu_param_cfg = data; return;
        case PVR2_HALF_OFFSET:          pvr2->half_offset = data; return;
        case PVR2_FPU_PREP_VAL:         pvr2->fpu_prep_val = data; return;
        case PVR2_ISP_BACKGND_D:        pvr2->isp_backgnd_d = data; return;
        case PVR2_ISP_BACKGND_T:        pvr2->isp_backgnd_t = data; return;
        case PVR2_ISP_FEED_CFG:         pvr2->isp_feed_cfg = data; return;
        case PVR2_SDRAM_REFRESH:        pvr2->sdram_refresh = data; return;
        case PVR2_SDRAM_ARB_CFG:        pvr2->sdram_arb_cfg = data; return;
        case PVR2_SDRAM_CFG:            pvr2->sdram_cfg = data; return;
        case PVR2_FOG_COL_RAM:          pvr2->fog_col_ram = data; return;
        case PVR2_FOG_COL_VERT:         pvr2->fog_col_vert = data; return;
        case PVR2_FOG_DENSITY:          pvr2->fog_density = data; return;
        case PVR2_FOG_CLAMP_MAX:        pvr2->fog_clamp_max = data; return;
        case PVR2_FOG_CLAMP_MIN:        pvr2->fog_clamp_min = data; return;
        case PVR2_SPG_TRIGGER_POS:      pvr2->spg_trigger_pos = data; return;
        case PVR2_SPG_HBLANK_INT:       pvr2->spg_hblank_int = data; return;
        case PVR2_SPG_VBLANK_INT:       pvr2->spg_vblank_int = data; return;
        case PVR2_SPG_CONTROL:          pvr2->spg_control = data; return;
        case PVR2_SPG_HBLANK:           pvr2->spg_hblank = data; return;
        case PVR2_SPG_LOAD:             pvr2->spg_load = data; return;
        case PVR2_SPG_VBLANK:           pvr2->spg_vblank = data; return;
        case PVR2_SPG_WIDTH:            pvr2->spg_width = data; return;
        case PVR2_TEXT_CONTROL:         pvr2->text_control = data; return;
        case PVR2_VO_CONTROL:           pvr2->vo_control = data; return;
        case PVR2_VO_STARTX:            pvr2->vo_startx = data; return;
        case PVR2_VO_STARTY:            pvr2->vo_starty = data; return;
        case PVR2_SCALER_CTL:           pvr2->scaler_ctl = data; return;
        case PVR2_PAL_RAM_CTRL:         pvr2->pal_ram_ctrl = data; return;
        case PVR2_SPG_STATUS:           pvr2->spg_status = data; return;
        case PVR2_FB_BURSTCTRL:         pvr2->fb_burstctrl = data; return;
        case PVR2_FB_C_SOF:             pvr2->fb_c_sof = data; return;
        case PVR2_Y_COEFF:              pvr2->y_coeff = data; return;
        case PVR2_PT_ALPHA_REF:         pvr2->pt_alpha_ref = data; return;
        case PVR2_TA_OL_BASE:           pvr2->ta_ol_base = data; return;
        case PVR2_TA_ISP_BASE:          pvr2->ta_isp_base = data; return;
        case PVR2_TA_OL_LIMIT:          pvr2->ta_ol_limit = data; return;
        case PVR2_TA_ISP_LIMIT:         pvr2->ta_isp_limit = data; return;
        case PVR2_TA_NEXT_OPB:          pvr2->ta_next_opb = data; return;
        case PVR2_TA_ITP_CURRENT:       pvr2->ta_itp_current = data; return;
        case PVR2_TA_GLOB_TILE_CLIP:    pvr2->ta_glob_tile_clip = data; return;
        case PVR2_TA_ALLOC_CTRL:        pvr2->ta_alloc_ctrl = data; return;
        case PVR2_TA_LIST_INIT:         pvr2->ta_list_init = data; return;
        case PVR2_TA_YUV_TEX_BASE:      pvr2->ta_yuv_tex_base = data; return;
        case PVR2_TA_YUV_TEX_CTRL:      pvr2->ta_yuv_tex_ctrl = data; return;
        case PVR2_TA_YUV_TEX_CNT:       pvr2->ta_yuv_tex_cnt = data; return;
        case PVR2_TA_LIST_CONT:         pvr2->ta_list_cont = data; return;
        case PVR2_TA_NEXT_OPB_INIT:     pvr2->ta_next_opb_init = data; return;
        case PVR2_FOG_TABLE_START:      pvr2->fog_table_start = data; return;
        case PVR2_TA_OL_POINTERS_START: pvr2->ta_ol_pointers_start = data; return;
        case PVR2_PALETTE_RAM_START:    pvr2->palette_ram_start = data; return;
    }

    //printf("unhandled PVR2 write %08x (%08x)\n", addr, data);
}

void pvr2_write16(void* udata, uint32_t addr, uint32_t data) {
    pvr2_state* pvr2 = udata;
}

void pvr2_write8(void* udata, uint32_t addr, uint32_t data) {
    pvr2_state* pvr2 = udata;
}

void* pvr2_get_display(pvr2_state* pvr2) {
    return pvr2->vram->buf + pvr2->fb_r_sof1;
}

void pvr2_destroy(pvr2_state* pvr2) {
    free(pvr2);
}