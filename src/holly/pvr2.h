#ifndef PVR2_H
#define PVR2_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdlib.h>

#include "vram.h"

#define PVR2_ID                   0x00000000 // 0x005f8000
#define PVR2_REVISION             0x00000004 // 0x005f8004
#define PVR2_SOFTRESET            0x00000008 // 0x005f8008
#define PVR2_STARTRENDER          0x00000014 // 0x005f8014
#define PVR2_TEST_SELECT          0x00000018 // 0x005f8018
#define PVR2_PARAM_BASE           0x00000020 // 0x005f8020
#define PVR2_REGION_BASE          0x0000002c // 0x005f802c
#define PVR2_SPAN_SOFT_CFG        0x00000030 // 0x005f8030
#define PVR2_VO_BORDER_COL        0x00000040 // 0x005f8040
#define PVR2_FB_R_CTRL            0x00000044 // 0x005f8044
#define PVR2_FB_W_CTRL            0x00000048 // 0x005f8048
#define PVR2_FB_LINESTRIDE        0x0000004c // 0x005f804c
#define PVR2_FB_R_SOF1            0x00000050 // 0x005f8050
#define PVR2_FB_R_SOF2            0x00000054 // 0x005f8054
#define PVR2_FB_R_SIZE            0x0000005c // 0x005f805c
#define PVR2_FB_W_SOF1            0x00000060 // 0x005f8060
#define PVR2_FB_W_SOF2            0x00000064 // 0x005f8064
#define PVR2_FB_X_CLIP            0x00000068 // 0x005f8068
#define PVR2_FB_Y_CLIP            0x0000006c // 0x005f806c
#define PVR2_FPU_SHAD_SCALE       0x00000074 // 0x005f8074
#define PVR2_FPU_CULL_VAL         0x00000078 // 0x005f8078
#define PVR2_FPU_PARAM_CFG        0x0000007c // 0x005f807c
#define PVR2_HALF_OFFSET          0x00000080 // 0x005f8080
#define PVR2_FPU_PREP_VAL         0x00000084 // 0x005f8084
#define PVR2_ISP_BACKGND_D        0x00000088 // 0x005f8088
#define PVR2_ISP_BACKGND_T        0x0000008c // 0x005f808c
#define PVR2_ISP_FEED_CFG         0x00000098 // 0x005f8098
#define PVR2_SDRAM_REFRESH        0x000000a0 // 0x005f80a0
#define PVR2_SDRAM_ARB_CFG        0x000000a4 // 0x005f80a4
#define PVR2_SDRAM_CFG            0x000000a8 // 0x005f80a8
#define PVR2_FOG_COL_RAM          0x000000b0 // 0x005f80b0
#define PVR2_FOG_COL_VERT         0x000000b4 // 0x005f80b4
#define PVR2_FOG_DENSITY          0x000000b8 // 0x005f80b8
#define PVR2_FOG_CLAMP_MAX        0x000000bc // 0x005f80bc
#define PVR2_FOG_CLAMP_MIN        0x000000c0 // 0x005f80c0
#define PVR2_SPG_TRIGGER_POS      0x000000c4 // 0x005f80c4
#define PVR2_SPG_HBLANK_INT       0x000000c8 // 0x005f80c8
#define PVR2_SPG_VBLANK_INT       0x000000cc // 0x005f80cc
#define PVR2_SPG_CONTROL          0x000000d0 // 0x005f80d0
#define PVR2_SPG_HBLANK           0x000000d4 // 0x005f80d4
#define PVR2_SPG_LOAD             0x000000d8 // 0x005f80d8
#define PVR2_SPG_VBLANK           0x000000dc // 0x005f80dc
#define PVR2_SPG_WIDTH            0x000000e0 // 0x005f80e0
#define PVR2_TEXT_CONTROL         0x000000e4 // 0x005f80e4
#define PVR2_VO_CONTROL           0x000000e8 // 0x005f80e8
#define PVR2_VO_STARTX            0x000000ec // 0x005f80ec
#define PVR2_VO_STARTY            0x000000f0 // 0x005f80f0
#define PVR2_SCALER_CTL           0x000000f4 // 0x005f80f4
#define PVR2_PAL_RAM_CTRL         0x00000108 // 0x005f8108
#define PVR2_SPG_STATUS           0x0000010c // 0x005f810c
#define PVR2_FB_BURSTCTRL         0x00000110 // 0x005f8110
#define PVR2_FB_C_SOF             0x00000114 // 0x005f8114
#define PVR2_Y_COEFF              0x00000118 // 0x005f8118
#define PVR2_PT_ALPHA_REF         0x0000011c // 0x005f811c
#define PVR2_TA_OL_BASE           0x00000124 // 0x005f8124
#define PVR2_TA_ISP_BASE          0x00000128 // 0x005f8128
#define PVR2_TA_OL_LIMIT          0x0000012c // 0x005f812c
#define PVR2_TA_ISP_LIMIT         0x00000130 // 0x005f8130
#define PVR2_TA_NEXT_OPB          0x00000134 // 0x005f8134
#define PVR2_TA_ITP_CURRENT       0x00000138 // 0x005f8138
#define PVR2_TA_GLOB_TILE_CLIP    0x0000013c // 0x005f813c
#define PVR2_TA_ALLOC_CTRL        0x00000140 // 0x005f8140
#define PVR2_TA_LIST_INIT         0x00000144 // 0x005f8144
#define PVR2_TA_YUV_TEX_BASE      0x00000148 // 0x005f8148
#define PVR2_TA_YUV_TEX_CTRL      0x0000014c // 0x005f814c
#define PVR2_TA_YUV_TEX_CNT       0x00000150 // 0x005f8150
#define PVR2_TA_LIST_CONT         0x00000160 // 0x005f8160
#define PVR2_TA_NEXT_OPB_INIT     0x00000164 // 0x005f8164
#define PVR2_FOG_TABLE_START      0x00000200 // 0x005f8200
#define PVR2_TA_OL_POINTERS_START 0x00000600 // 0x005f8600
#define PVR2_PALETTE_RAM_START    0x00001000 // 0x005f9000

typedef struct {
    vram_state* vram;

    uint32_t id;
    uint32_t revision;
    uint32_t softreset;
    uint32_t startrender;
    uint32_t test_select;
    uint32_t param_base;
    uint32_t region_base;
    uint32_t span_soft_cfg;
    uint32_t vo_border_col;
    uint32_t fb_r_ctrl;
    uint32_t fb_w_ctrl;
    uint32_t fb_linestride;
    uint32_t fb_r_sof1;
    uint32_t fb_r_sof2;
    uint32_t fb_r_size;
    uint32_t fb_w_sof1;
    uint32_t fb_w_sof2;
    uint32_t fb_x_clip;
    uint32_t fb_y_clip;
    uint32_t fpu_shad_scale;
    uint32_t fpu_cull_val;
    uint32_t fpu_param_cfg;
    uint32_t half_offset;
    uint32_t fpu_prep_val;
    uint32_t isp_backgnd_d;
    uint32_t isp_backgnd_t;
    uint32_t isp_feed_cfg;
    uint32_t sdram_refresh;
    uint32_t sdram_arb_cfg;
    uint32_t sdram_cfg;
    uint32_t fog_col_ram;
    uint32_t fog_col_vert;
    uint32_t fog_density;
    uint32_t fog_clamp_max;
    uint32_t fog_clamp_min;
    uint32_t spg_trigger_pos;
    uint32_t spg_hblank_int;
    uint32_t spg_vblank_int;
    uint32_t spg_control;
    uint32_t spg_hblank;
    uint32_t spg_load;
    uint32_t spg_vblank;
    uint32_t spg_width;
    uint32_t text_control;
    uint32_t vo_control;
    uint32_t vo_startx;
    uint32_t vo_starty;
    uint32_t scaler_ctl;
    uint32_t pal_ram_ctrl;
    uint32_t spg_status;
    uint32_t fb_burstctrl;
    uint32_t fb_c_sof;
    uint32_t y_coeff;
    uint32_t pt_alpha_ref;
    uint32_t ta_ol_base;
    uint32_t ta_isp_base;
    uint32_t ta_ol_limit;
    uint32_t ta_isp_limit;
    uint32_t ta_next_opb;
    uint32_t ta_itp_current;
    uint32_t ta_glob_tile_clip;
    uint32_t ta_alloc_ctrl;
    uint32_t ta_list_init;
    uint32_t ta_yuv_tex_base;
    uint32_t ta_yuv_tex_ctrl;
    uint32_t ta_yuv_tex_cnt;
    uint32_t ta_list_cont;
    uint32_t ta_next_opb_init;
    uint32_t fog_table_start;
    uint32_t ta_ol_pointers_start;
    uint32_t palette_ram_start;
} pvr2_state;

pvr2_state* pvr2_create();
void pvr2_init(pvr2_state* pvr2, vram_state* vram);
uint32_t pvr2_read32(void* udata, uint32_t addr);
uint32_t pvr2_read16(void* udata, uint32_t addr);
uint32_t pvr2_read8(void* udata, uint32_t addr);
void pvr2_write32(void* udata, uint32_t addr, uint32_t data);
void pvr2_write16(void* udata, uint32_t addr, uint32_t data);
void pvr2_write8(void* udata, uint32_t addr, uint32_t data);
void* pvr2_get_display(pvr2_state* pvr2);
void pvr2_destroy(pvr2_state* pvr2);

#ifdef __cplusplus
}
#endif

#endif