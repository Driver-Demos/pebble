/*
 * Copyright 2024 Google LLC
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "sdk_defs.h"

#include <string.h>

// If Dialog ever updates the number of registers or the default values of the registers, one can:
//   1. Set `DEFAULT_REGISTER_DEBUG` to 1
//   2. Update/Add/Remove the register values using `REG_SETF`
//   3. Flash and boot the dialog chip.
//   4. Attach GDB to ble chip and type `p/x ALL_REGISTERS`
//   5. Copy, reformat, and paste output to the squashed register values.

#define DEFAULT_REGISTER_DEBUG 0

#if DEFAULT_REGISTER_DEBUG
typedef struct AllRegisters {
  // DCDC
  uint16_t DCDC_CTRL_0_REG;
  uint16_t DCDC_CTRL_1_REG;
  uint16_t DCDC_CTRL_2_REG;
  uint16_t DCDC_V14_0_REG;
  uint16_t DCDC_V14_1_REG;
  uint16_t DCDC_V18_0_REG;
  uint16_t DCDC_V18_1_REG;
  uint16_t DCDC_VDD_0_REG;
  uint16_t DCDC_VDD_1_REG;
  uint16_t DCDC_V18P_0_REG;
  uint16_t DCDC_V18P_1_REG;
  uint16_t DCDC_RET_0_REG;
  uint16_t DCDC_RET_1_REG;
  uint16_t DCDC_TRIM_REG;
  uint16_t DCDC_TEST_0_REG;
  uint16_t DCDC_TEST_1_REG;
  uint16_t DCDC_IRQ_CLEAR_REG;
  uint16_t DCDC_IRQ_MASK_REG;

  // CRG_TOP
  uint16_t BANDGAP_REG;
  uint16_t BOD_STATUS_REG;
  uint16_t FORCE_SLEEP_REG;
  uint16_t LDOS_DISABLE_REG;
  uint16_t AON_SPARE_REG;

  // QSPIC
  uint32_t  QSPIC_CTRLMODE_REG;
  uint32_t  QSPIC_BURSTCMDA_REG;
  uint32_t  QSPIC_BURSTCMDB_REG;
  uint32_t  QSPIC_WRITEDATA_REG;
  uint32_t  QSPIC_DUMMYDATA_REG;
  uint32_t  QSPIC_ERASECTRL_REG;
  uint32_t  QSPIC_ERASECMDA_REG;
  uint32_t  QSPIC_ERASECMDB_REG;
  uint32_t  QSPIC_BURSTBRK_REG;
  uint32_t  QSPIC_STATUSCMD_REG;
  uint32_t  QSPIC_CHCKERASE_REG;
  uint32_t  QSPIC_GP_REG;
  uint32_t  QSPIC_UCODE_START;

  // GPREG
  uint16_t  PLL_SYS_CTRL1_REG;
  uint16_t  PLL_SYS_CTRL2_REG;
  uint16_t  PLL_SYS_CTRL3_REG;
  uint16_t  PLL_SYS_TEST_REG;

  // CACHE
  uint32_t  CACHE_CTRL1_REG;
  uint32_t  CACHE_LNSIZECFG_REG;
  uint32_t  CACHE_ASSOCCFG_REG;
  uint32_t  CACHE_CTRL2_REG;
  uint32_t  CACHE_CTRL3_REG;
  uint32_t  CACHE_MRM_HITS_REG;
  uint32_t  CACHE_MRM_MISSES_REG;
  uint32_t  CACHE_MRM_CTRL_REG;
  uint32_t  CACHE_MRM_TINT_REG;
  uint32_t  CACHE_MRM_THRES_REG;
  uint32_t  SWD_RESET_REG;
} AllRegisters;

static AllRegisters ALL_REGISTERS;

#endif // DEFAULT_REGISTER_DEBUG


void default_registers_restore(void) {
  DCDC->DCDC_CTRL_0_REG = 0x2f24;
  DCDC->DCDC_CTRL_1_REG = 0x5410;
  DCDC->DCDC_CTRL_2_REG = 0x882d;
  DCDC->DCDC_V14_0_REG = 0xa1a4;
  DCDC->DCDC_V14_1_REG = 0xd890;
  DCDC->DCDC_V18_0_REG = 0xe3e4;
  DCDC->DCDC_V18_1_REG = 0xbc90;
  DCDC->DCDC_VDD_0_REG = 0xc304;
  DCDC->DCDC_VDD_1_REG = 0xec90;
  DCDC->DCDC_V18P_0_REG = 0xe3e4;
  DCDC->DCDC_V18P_1_REG = 0xbc90;
  DCDC->DCDC_RET_0_REG = 0xaaa6;
  DCDC->DCDC_RET_1_REG = 0xaa46;
  DCDC->DCDC_TRIM_REG = 0x0;
  DCDC->DCDC_TEST_0_REG = 0x0;
  DCDC->DCDC_TEST_1_REG = 0x0;
  DCDC->DCDC_IRQ_CLEAR_REG = 0x0;
  DCDC->DCDC_IRQ_MASK_REG = 0x0;
  CRG_TOP->BANDGAP_REG = 0x0;
  CRG_TOP->BOD_STATUS_REG = 0x7;
  CRG_TOP->FORCE_SLEEP_REG = 0x1;
  CRG_TOP->LDOS_DISABLE_REG = 0x0;
  CRG_TOP->AON_SPARE_REG = 0x0;
  QSPIC->QSPIC_CTRLBUS_REG = 0x0;
  QSPIC->QSPIC_CTRLMODE_REG = 0x0;
  QSPIC->QSPIC_BURSTCMDA_REG = 0x0;
  QSPIC->QSPIC_BURSTCMDB_REG = 0x0;
  QSPIC->QSPIC_WRITEDATA_REG = 0x0;
  QSPIC->QSPIC_DUMMYDATA_REG = 0x0;
  QSPIC->QSPIC_ERASECTRL_REG = 0x0;
  QSPIC->QSPIC_ERASECMDA_REG = 0x0;
  QSPIC->QSPIC_ERASECMDB_REG = 0x0;
  QSPIC->QSPIC_BURSTBRK_REG = 0x0;
  QSPIC->QSPIC_STATUSCMD_REG = 0x0;
  QSPIC->QSPIC_CHCKERASE_REG = 0x0;
  QSPIC->QSPIC_GP_REG = 0x0;
  QSPIC->QSPIC_UCODE_START = 0x0;
  GPREG->PLL_SYS_CTRL1_REG = 0x100;
  GPREG->PLL_SYS_CTRL2_REG = 0x2006;
  GPREG->PLL_SYS_CTRL3_REG = 0x3c09;
  GPREG->PLL_SYS_TEST_REG = 0x70;
  CACHE->CACHE_CTRL1_REG = 0x0;
  CACHE->CACHE_LNSIZECFG_REG = 0x0;
  CACHE->CACHE_ASSOCCFG_REG = 0x2;
  CACHE->CACHE_CTRL2_REG = 0x0;
  CACHE->CACHE_CTRL3_REG = 0x22;
  CACHE->CACHE_MRM_HITS_REG = 0x0;
  CACHE->CACHE_MRM_MISSES_REG = 0x0;
  CACHE->CACHE_MRM_CTRL_REG = 0x0;
  CACHE->CACHE_MRM_TINT_REG = 0x0;
  CACHE->CACHE_MRM_THRES_REG = 0x0;
  CACHE->SWD_RESET_REG = 0x0;

#if DEFAULT_REGISTER_DEBUG
  // DCDC
  REG_SETF(DCDC, DCDC_CTRL_0_REG, DCDC_FAST_STARTUP, 0x0);
  REG_SETF(DCDC, DCDC_CTRL_0_REG, DCDC_BROWNOUT_LV_MODE, 0x1);
  REG_SETF(DCDC, DCDC_CTRL_0_REG, DCDC_IDLE_CLK_DIV, 0x1);
  REG_SETF(DCDC, DCDC_CTRL_0_REG, DCDC_PRIORITY, 0xE4);
  REG_SETF(DCDC, DCDC_CTRL_0_REG, DCDC_FW_ENABLE, 0x1);
  REG_SETF(DCDC, DCDC_CTRL_0_REG, DCDC_MODE, 0);

  REG_SETF(DCDC, DCDC_CTRL_1_REG, DCDC_STARTUP_DELAY, 0xA);
  REG_SETF(DCDC, DCDC_CTRL_1_REG, DCDC_GLOBAL_MAX_IDLE_TIME, 0x20);
  REG_SETF(DCDC, DCDC_CTRL_1_REG, DCDC_TIMEOUT, 0x10);

  REG_SETF(DCDC, DCDC_CTRL_2_REG, DCDC_TIMEOUT_IRQ_TRIG, 0x8);
  REG_SETF(DCDC, DCDC_CTRL_2_REG, DCDC_TIMEOUT_IRQ_RES, 0x8);
  REG_SETF(DCDC, DCDC_CTRL_2_REG, DCDC_TUNE, 0x0);
  REG_SETF(DCDC, DCDC_CTRL_2_REG, DCDC_LSSUP_TRIM, 0x5);
  REG_SETF(DCDC, DCDC_CTRL_2_REG, DCDC_HSGND_TRIM, 0x5);

  REG_SETF(DCDC, DCDC_V14_0_REG, DCDC_V14_FAST_RAMPING, 0x1);
  REG_SETF(DCDC, DCDC_V14_0_REG, DCDC_V14_VOLTAGE, 0x8);
  REG_SETF(DCDC, DCDC_V14_0_REG, DCDC_V14_CUR_LIM_MAX_HV, 0xD);
  REG_SETF(DCDC, DCDC_V14_0_REG, DCDC_V14_CUR_LIM_MIN, 0x4);

  REG_SETF(DCDC, DCDC_V14_1_REG, DCDC_V14_ENABLE_HV, 0x1);
  REG_SETF(DCDC, DCDC_V14_1_REG, DCDC_V14_ENABLE_LV, 0x1);
  REG_SETF(DCDC, DCDC_V14_1_REG, DCDC_V14_CUR_LIM_MAX_LV, 0x6);
  REG_SETF(DCDC, DCDC_V14_1_REG, DCDC_V14_IDLE_HYST, 0x4);
  REG_SETF(DCDC, DCDC_V14_1_REG, DCDC_V14_IDLE_MIN, 0x10);

  REG_SETF(DCDC, DCDC_V18_0_REG, DCDC_V18_FAST_RAMPING, 0x1);
  REG_SETF(DCDC, DCDC_V18_0_REG, DCDC_V18_VOLTAGE, 0x18);
  REG_SETF(DCDC, DCDC_V18_0_REG, DCDC_V18_CUR_LIM_MAX_HV, 0x1F);
  REG_SETF(DCDC, DCDC_V18_0_REG, DCDC_V18_CUR_LIM_MIN, 0x4);

  REG_SETF(DCDC, DCDC_V18_1_REG, DCDC_V18_ENABLE_HV, 0x1);
  REG_SETF(DCDC, DCDC_V18_1_REG, DCDC_V18_ENABLE_LV, 0x0);
  REG_SETF(DCDC, DCDC_V18_1_REG, DCDC_V18_CUR_LIM_MAX_LV, 0xF);
  REG_SETF(DCDC, DCDC_V18_1_REG, DCDC_V18_IDLE_HYST, 0x4);
  REG_SETF(DCDC, DCDC_V18_1_REG, DCDC_V18_IDLE_MIN, 0x10);

  REG_SETF(DCDC, DCDC_VDD_0_REG, DCDC_VDD_FAST_RAMPING, 0x1);
  REG_SETF(DCDC, DCDC_VDD_0_REG, DCDC_VDD_VOLTAGE, 0x10);
  REG_SETF(DCDC, DCDC_VDD_0_REG, DCDC_VDD_CUR_LIM_MAX_HV, 0x18);
  REG_SETF(DCDC, DCDC_VDD_0_REG, DCDC_VDD_CUR_LIM_MIN, 0x4);

  REG_SETF(DCDC, DCDC_VDD_1_REG, DCDC_VDD_ENABLE_HV, 0x1);
  REG_SETF(DCDC, DCDC_VDD_1_REG, DCDC_VDD_ENABLE_LV, 0x1);
  REG_SETF(DCDC, DCDC_VDD_1_REG, DCDC_VDD_CUR_LIM_MAX_LV, 0xB);
  REG_SETF(DCDC, DCDC_VDD_1_REG, DCDC_VDD_IDLE_HYST, 0x4);
  REG_SETF(DCDC, DCDC_VDD_1_REG, DCDC_VDD_IDLE_MIN, 0x10);

  REG_SETF(DCDC, DCDC_V18P_0_REG, DCDC_V18P_FAST_RAMPING, 0x1);
  REG_SETF(DCDC, DCDC_V18P_0_REG, DCDC_V18P_VOLTAGE, 0x18);
  REG_SETF(DCDC, DCDC_V18P_0_REG, DCDC_V18P_CUR_LIM_MAX_HV, 0x1F);
  REG_SETF(DCDC, DCDC_V18P_0_REG, DCDC_V18P_CUR_LIM_MIN, 0x4);

  REG_SETF(DCDC, DCDC_V18P_1_REG, DCDC_V18P_ENABLE_HV, 0x1);
  REG_SETF(DCDC, DCDC_V18P_1_REG, DCDC_V18P_ENABLE_LV, 0x0);
  REG_SETF(DCDC, DCDC_V18P_1_REG, DCDC_V18P_CUR_LIM_MAX_LV, 0xF);
  REG_SETF(DCDC, DCDC_V18P_1_REG, DCDC_V18P_IDLE_HYST, 0x4);
  REG_SETF(DCDC, DCDC_V18P_1_REG, DCDC_V18P_IDLE_MIN, 0x10);

  REG_SETF(DCDC, DCDC_RET_0_REG, DCDC_V18P_RET_CYCLES, 0x5);
  REG_SETF(DCDC, DCDC_RET_0_REG, DCDC_V18P_CUR_LIM_RET, 0xA);
  REG_SETF(DCDC, DCDC_RET_0_REG, DCDC_VDD_RET_CYCLES, 0x5);
  REG_SETF(DCDC, DCDC_RET_0_REG, DCDC_VDD_CUR_LIM_RET, 0x6);

  REG_SETF(DCDC, DCDC_RET_1_REG, DCDC_V18_RET_CYCLES, 0x5);
  REG_SETF(DCDC, DCDC_RET_1_REG, DCDC_V18_CUR_LIM_RET, 0xA);
  REG_SETF(DCDC, DCDC_RET_1_REG, DCDC_V14_RET_CYCLES, 0x2);
  REG_SETF(DCDC, DCDC_RET_1_REG, DCDC_V14_CUR_LIM_RET, 0x6);

  REG_SETF(DCDC, DCDC_TRIM_REG, DCDC_P_COMP_MAN_TRIM, 0x0);
  REG_SETF(DCDC, DCDC_TRIM_REG, DCDC_P_COMP_TRIM, 0x0);
  REG_SETF(DCDC, DCDC_TRIM_REG, DCDC_N_COMP_MAN_TRIM, 0x0);
  REG_SETF(DCDC, DCDC_TRIM_REG, DCDC_N_COMP_TRIM, 0x0);

  REG_SETF(DCDC, DCDC_TEST_0_REG, DCDC_FORCE_COMP_CLK, 0x0);
  REG_SETF(DCDC, DCDC_TEST_0_REG, DCDC_FORCE_CURRENT, 0x0);
  REG_SETF(DCDC, DCDC_TEST_0_REG, DCDC_OUTPUT_MONITOR, 0x0);
  REG_SETF(DCDC, DCDC_TEST_0_REG, DCDC_ANA_TEST, 0x0);
  REG_SETF(DCDC, DCDC_TEST_0_REG, DCDC_FORCE_IDLE, 0x0);
  REG_SETF(DCDC, DCDC_TEST_0_REG, DCDC_FORCE_V18P, 0x0);
  REG_SETF(DCDC, DCDC_TEST_0_REG, DCDC_FORCE_VDD, 0x0);
  REG_SETF(DCDC, DCDC_TEST_0_REG, DCDC_FORCE_V18, 0x0);
  REG_SETF(DCDC, DCDC_TEST_0_REG, DCDC_FORCE_V14, 0x0);
  REG_SETF(DCDC, DCDC_TEST_0_REG, DCDC_FORCE_FW, 0x0);
  REG_SETF(DCDC, DCDC_TEST_0_REG, DCDC_FORCE_NSW, 0x0);
  REG_SETF(DCDC, DCDC_TEST_0_REG, DCDC_FORCE_PSW, 0x0);

  REG_SETF(DCDC, DCDC_TEST_1_REG, DCDC_COMP_CLK, 0x0);
  REG_SETF(DCDC, DCDC_TEST_1_REG, DCDC_TEST_CURRENT, 0x0);
  REG_SETF(DCDC, DCDC_TEST_1_REG, DCDC_TEST_REG, 0x0);

  REG_SETF(DCDC, DCDC_IRQ_CLEAR_REG, DCDC_BROWN_OUT_IRQ_CLEAR, 0x0);
  REG_SETF(DCDC, DCDC_IRQ_CLEAR_REG, DCDC_V18P_TIMEOUT_IRQ_CLEAR, 0x0);
  REG_SETF(DCDC, DCDC_IRQ_CLEAR_REG, DCDC_VDD_TIMEOUT_IRQ_CLEAR, 0x0);
  REG_SETF(DCDC, DCDC_IRQ_CLEAR_REG, DCDC_V18_TIMEOUT_IRQ_CLEAR, 0x0);
  REG_SETF(DCDC, DCDC_IRQ_CLEAR_REG, DCDC_V14_TIMEOUT_IRQ_CLEAR, 0x0);

  REG_SETF(DCDC, DCDC_IRQ_MASK_REG, DCDC_BROWN_OUT_IRQ_MASK, 0x0);
  REG_SETF(DCDC, DCDC_IRQ_MASK_REG, DCDC_V18P_TIMEOUT_IRQ_MASK, 0x0);
  REG_SETF(DCDC, DCDC_IRQ_MASK_REG, DCDC_VDD_TIMEOUT_IRQ_MASK, 0x0);
  REG_SETF(DCDC, DCDC_IRQ_MASK_REG, DCDC_V18_TIMEOUT_IRQ_MASK, 0x0);
  REG_SETF(DCDC, DCDC_IRQ_MASK_REG, DCDC_V14_TIMEOUT_IRQ_MASK, 0x0);


  // CRG_TOP
  REG_SETF(CRG_TOP, BANDGAP_REG, BYPASS_COLD_BOOT_DISABLE, 0x0);
  REG_SETF(CRG_TOP, BANDGAP_REG, LDO_SLEEP_TRIM, 0x0);
  REG_SETF(CRG_TOP, BANDGAP_REG, BGR_ITRIM, 0x0);
  REG_SETF(CRG_TOP, BANDGAP_REG, BGR_TRIM, 0x0);

  REG_SETF(CRG_TOP, BOD_STATUS_REG, BOD_VBAT_LOW, 0x0);
  REG_SETF(CRG_TOP, BOD_STATUS_REG, BOD_V33_LOW, 0x0);
  REG_SETF(CRG_TOP, BOD_STATUS_REG, BOD_1V8_FLASH_LOW, 0x0);
  REG_SETF(CRG_TOP, BOD_STATUS_REG, BOD_1V8_PA_LOW, 0x0);
  REG_SETF(CRG_TOP, BOD_STATUS_REG, BOD_VDD_LOW, 0x0);

  REG_SETF(CRG_TOP, FORCE_SLEEP_REG, FORCE_BLE_SLEEP, 0x0); // GUESS
  REG_SETF(CRG_TOP, FORCE_SLEEP_REG, FORCE_FTDF_SLEEP, 0x0); // GUESS

  REG_SETF(CRG_TOP, LDOS_DISABLE_REG, LDOS_DISABLE, 0x0); // GUESS

  REG_SETF(CRG_TOP, AON_SPARE_REG, OSC16_HOLD_AMP_REG, 0x0); // GUESS
  REG_SETF(CRG_TOP, AON_SPARE_REG, OSC16_SH_DISABLE, 0x0); // GUESS
  REG_SETF(CRG_TOP, AON_SPARE_REG, EN_BATSYS_RET, 0x0); // GUESS
  REG_SETF(CRG_TOP, AON_SPARE_REG, EN_BUSSYS_RET, 0x0); // GUESS


  // QSPIC
  REG_SETF(QSPIC, QSPIC_CTRLBUS_REG, QSPIC_DIS_CS, 0x0);
  REG_SETF(QSPIC, QSPIC_CTRLBUS_REG, QSPIC_EN_CS, 0x0);
  REG_SETF(QSPIC, QSPIC_CTRLBUS_REG, QSPIC_SET_QUAD, 0x0);
  REG_SETF(QSPIC, QSPIC_CTRLBUS_REG, QSPIC_SET_DUAL, 0x0);
  REG_SETF(QSPIC, QSPIC_CTRLBUS_REG, QSPIC_SET_SINGLE, 0x0);

  REG_SETF(QSPIC, QSPIC_CTRLMODE_REG, QSPIC_USE_32BA, 0x0);
  REG_SETF(QSPIC, QSPIC_CTRLMODE_REG, QSPIC_FORCENSEQ_EN, 0x0);
  REG_SETF(QSPIC, QSPIC_CTRLMODE_REG, QSPIC_PCLK_MD, 0x0);
  REG_SETF(QSPIC, QSPIC_CTRLMODE_REG, QSPIC_RPIPE_EN, 0x0);
  REG_SETF(QSPIC, QSPIC_CTRLMODE_REG, QSPIC_RXD_NEG, 0x0);
  REG_SETF(QSPIC, QSPIC_CTRLMODE_REG, QSPIC_HRDY_MD, 0x0);
  REG_SETF(QSPIC, QSPIC_CTRLMODE_REG, QSPIC_IO3_DAT, 0x0);
  REG_SETF(QSPIC, QSPIC_CTRLMODE_REG, QSPIC_IO2_DAT, 0x0);
  REG_SETF(QSPIC, QSPIC_CTRLMODE_REG, QSPIC_IO3_OEN, 0x0);
  REG_SETF(QSPIC, QSPIC_CTRLMODE_REG, QSPIC_IO2_OEN, 0x0);
  REG_SETF(QSPIC, QSPIC_CTRLMODE_REG, QSPIC_CLK_MD, 0x0);
  REG_SETF(QSPIC, QSPIC_CTRLMODE_REG, QSPIC_AUTO_MD, 0x0);

  REG_SETF(QSPIC, QSPIC_BURSTCMDA_REG, QSPIC_DMY_TX_MD, 0x0);
  REG_SETF(QSPIC, QSPIC_BURSTCMDA_REG, QSPIC_EXT_TX_MD, 0x0);
  REG_SETF(QSPIC, QSPIC_BURSTCMDA_REG, QSPIC_ADR_TX_MD, 0x0);
  REG_SETF(QSPIC, QSPIC_BURSTCMDA_REG, QSPIC_INST_TX_MD, 0x0);
  REG_SETF(QSPIC, QSPIC_BURSTCMDA_REG, QSPIC_EXT_BYTE, 0x0);
  REG_SETF(QSPIC, QSPIC_BURSTCMDA_REG, QSPIC_INST_WB, 0x0);
  REG_SETF(QSPIC, QSPIC_BURSTCMDA_REG, QSPIC_INST, 0x0);

  REG_SETF(QSPIC, QSPIC_BURSTCMDB_REG, QSPIC_DMY_FORCE, 0x0);
  REG_SETF(QSPIC, QSPIC_BURSTCMDB_REG, QSPIC_CS_HIGH_MIN, 0x0);
  REG_SETF(QSPIC, QSPIC_BURSTCMDB_REG, QSPIC_WRAP_SIZE, 0x0);
  REG_SETF(QSPIC, QSPIC_BURSTCMDB_REG, QSPIC_WRAP_LEN, 0x0);
  REG_SETF(QSPIC, QSPIC_BURSTCMDB_REG, QSPIC_WRAP_MD, 0x0);
  REG_SETF(QSPIC, QSPIC_BURSTCMDB_REG, QSPIC_INST_MD, 0x0);
  REG_SETF(QSPIC, QSPIC_BURSTCMDB_REG, QSPIC_DMY_NUM, 0x0);
  REG_SETF(QSPIC, QSPIC_BURSTCMDB_REG, QSPIC_EXT_HF_DS, 0x0);
  REG_SETF(QSPIC, QSPIC_BURSTCMDB_REG, QSPIC_EXT_BYTE_EN, 0x0);
  REG_SETF(QSPIC, QSPIC_BURSTCMDB_REG, QSPIC_DAT_RX_MD, 0x0);

  REG_SETF(QSPIC, QSPIC_WRITEDATA_REG, QSPIC_WRITEDATA, 0x0);

  REG_SETF(QSPIC, QSPIC_DUMMYDATA_REG, QSPIC_DUMMYDATA, 0x0);

  REG_SETF(QSPIC, QSPIC_ERASECTRL_REG, QSPIC_ERASE_EN, 0x0);
  REG_SETF(QSPIC, QSPIC_ERASECTRL_REG, QSPIC_ERS_ADDR, 0x0);

  REG_SETF(QSPIC, QSPIC_ERASECMDA_REG, QSPIC_RES_INST, 0x0);
  REG_SETF(QSPIC, QSPIC_ERASECMDA_REG, QSPIC_SUS_INST, 0x0);
  REG_SETF(QSPIC, QSPIC_ERASECMDA_REG, QSPIC_WEN_INST, 0x0);
  REG_SETF(QSPIC, QSPIC_ERASECMDA_REG, QSPIC_ERS_INST, 0x0);

  REG_SETF(QSPIC, QSPIC_ERASECMDB_REG, QSPIC_RESSUS_DLY, 0x0);
  REG_SETF(QSPIC, QSPIC_ERASECMDB_REG, QSPIC_ERSRES_HLD, 0x0);
  REG_SETF(QSPIC, QSPIC_ERASECMDB_REG, QSPIC_ERS_CS_HI, 0x0);
  REG_SETF(QSPIC, QSPIC_ERASECMDB_REG, QSPIC_EAD_TX_MD, 0x0);
  REG_SETF(QSPIC, QSPIC_ERASECMDB_REG, QSPIC_RES_TX_MD, 0x0);
  REG_SETF(QSPIC, QSPIC_ERASECMDB_REG, QSPIC_SUS_TX_MD, 0x0);
  REG_SETF(QSPIC, QSPIC_ERASECMDB_REG, QSPIC_WEN_TX_MD, 0x0);
  REG_SETF(QSPIC, QSPIC_ERASECMDB_REG, QSPIC_ERS_TX_MD, 0x0);

  REG_SETF(QSPIC, QSPIC_BURSTBRK_REG, QSPIC_SEC_HF_DS, 0x0);
  REG_SETF(QSPIC, QSPIC_BURSTBRK_REG, QSPIC_BRK_TX_MD, 0x0);
  REG_SETF(QSPIC, QSPIC_BURSTBRK_REG, QSPIC_BRK_SZ, 0x0);
  REG_SETF(QSPIC, QSPIC_BURSTBRK_REG, QSPIC_BRK_EN, 0x0);
  REG_SETF(QSPIC, QSPIC_BURSTBRK_REG, QSPIC_BRK_WRD, 0x0);

  REG_SETF(QSPIC, QSPIC_STATUSCMD_REG, QSPIC_STSDLY_SEL, 0x0);
  REG_SETF(QSPIC, QSPIC_STATUSCMD_REG, QSPIC_RESSTS_DLY, 0x0);
  REG_SETF(QSPIC, QSPIC_STATUSCMD_REG, QSPIC_BUSY_VAL, 0x0);
  REG_SETF(QSPIC, QSPIC_STATUSCMD_REG, QSPIC_RSTAT_RX_MD, 0x0);
  REG_SETF(QSPIC, QSPIC_STATUSCMD_REG, QSPIC_RSTAT_TX_MD, 0x0);
  REG_SETF(QSPIC, QSPIC_STATUSCMD_REG, QSPIC_RSTAT_INST, 0x0);

  REG_SETF(QSPIC, QSPIC_CHCKERASE_REG, QSPIC_CHCKERASE, 0x0);

  REG_SETF(QSPIC, QSPIC_GP_REG, QSPIC_PADS_SLEW, 0x0);
  REG_SETF(QSPIC, QSPIC_GP_REG, QSPIC_PADS_DRV, 0x0);

  REG_SETF(QSPIC, QSPIC_UCODE_START, QSPIC_UCODE_X, 0x0);


  // GPREG
  REG_SETF(GPREG, PLL_SYS_CTRL1_REG, PLL_R_DIV, 0x1);
  REG_SETF(GPREG, PLL_SYS_CTRL1_REG, LDO_PLL_VREF_HOLD, 0x0);
  REG_SETF(GPREG, PLL_SYS_CTRL1_REG, LDO_PLL_ENABLE, 0x0);
  REG_SETF(GPREG, PLL_SYS_CTRL1_REG, PLL_EN, 0x0);

  REG_SETF(GPREG, PLL_SYS_CTRL2_REG, PLL_SEL_MIN_CUR_INT, 0x0);
  REG_SETF(GPREG, PLL_SYS_CTRL2_REG, PLL_DEL_SEL, 0x2);
  REG_SETF(GPREG, PLL_SYS_CTRL2_REG, PLL_N_DIV, 0x6);

  REG_SETF(GPREG, PLL_SYS_CTRL3_REG, PLL_RECALIB, 0x0); // GUESS
  REG_SETF(GPREG, PLL_SYS_CTRL3_REG, PLL_START_DEL, 0xF);
  REG_SETF(GPREG, PLL_SYS_CTRL3_REG, PLL_ICP_SEL, 0x9);

  REG_SETF(GPREG, PLL_SYS_TEST_REG, PLL_LOCK_DET_RES_CNT, 0x0);
  REG_SETF(GPREG, PLL_SYS_TEST_REG, PLL_SEL_R_DIV_TEST, 0x0);
  REG_SETF(GPREG, PLL_SYS_TEST_REG, PLL_SEL_N_DIV_TEST, 0x0);
  REG_SETF(GPREG, PLL_SYS_TEST_REG, PLL_CHANGE, 0x0);
  REG_SETF(GPREG, PLL_SYS_TEST_REG, PLL_OPEN_LOOP, 0x0);
  REG_SETF(GPREG, PLL_SYS_TEST_REG, PLL_TEST_VCTR, 0x0);
  REG_SETF(GPREG, PLL_SYS_TEST_REG, PLL_MIN_CURRENT, 0x38);
  REG_SETF(GPREG, PLL_SYS_TEST_REG, PLL_DIS_LOOPFILT, 0x0);


  // CACHE
  REG_SETF(CACHE, CACHE_CTRL1_REG, CACHE_RES1, 0x0);
  REG_SETF(CACHE, CACHE_CTRL1_REG, CACHE_FLUSH, 0x0);

  REG_SETF(CACHE, CACHE_LNSIZECFG_REG, CACHE_LINE, 0x0);

  REG_SETF(CACHE, CACHE_ASSOCCFG_REG, CACHE_ASSOC, 0x2);

  REG_SETF(CACHE, CACHE_CTRL2_REG, ENABLE_ALSO_QSPIFLASH_CACHED, 0x0);
  REG_SETF(CACHE, CACHE_CTRL2_REG, ENABLE_ALSO_OTP_CACHED, 0x0);
  REG_SETF(CACHE, CACHE_CTRL2_REG, CACHE_CGEN, 0x0);
  REG_SETF(CACHE, CACHE_CTRL2_REG, CACHE_WEN, 0x0);
  REG_SETF(CACHE, CACHE_CTRL2_REG, CACHE_LEN, 0x0);

  REG_SETF(CACHE, CACHE_CTRL3_REG, CACHE_CONTROLLER_RESET, 0x0);
  REG_SETF(CACHE, CACHE_CTRL3_REG, CACHE_RAM_SIZE_RESET_VALUE, 0x2);
  REG_SETF(CACHE, CACHE_CTRL3_REG, CACHE_LINE_SIZE_RESET_VALUE, 0x0);
  REG_SETF(CACHE, CACHE_CTRL3_REG, CACHE_ASSOCIATIVITY_RESET_VALUE, 0x2);

  REG_SETF(CACHE, CACHE_MRM_HITS_REG, MRM_HITS, 0x0);

  REG_SETF(CACHE, CACHE_MRM_MISSES_REG, MRM_MISSES, 0x0);

  REG_SETF(CACHE, CACHE_MRM_CTRL_REG, MRM_IRQ_THRES_STATUS, 0x0);
  REG_SETF(CACHE, CACHE_MRM_CTRL_REG, MRM_IRQ_TINT_STATUS, 0x0);
  REG_SETF(CACHE, CACHE_MRM_CTRL_REG, MRM_IRQ_MASK, 0x0);
  REG_SETF(CACHE, CACHE_MRM_CTRL_REG, MRM_START, 0x0);

  REG_SETF(CACHE, CACHE_MRM_TINT_REG, MRM_TINT, 0x0);

  REG_SETF(CACHE, CACHE_MRM_THRES_REG, MRM_THRES, 0x0);

  REG_SETF(CACHE, SWD_RESET_REG, SWD_HW_RESET_REQ, 0x0);

  // DCDC
  ALL_REGISTERS.DCDC_CTRL_0_REG = DCDC->DCDC_CTRL_0_REG;
  ALL_REGISTERS.DCDC_CTRL_1_REG = DCDC->DCDC_CTRL_1_REG;
  ALL_REGISTERS.DCDC_CTRL_2_REG = DCDC->DCDC_CTRL_2_REG;
  ALL_REGISTERS.DCDC_V14_0_REG = DCDC->DCDC_V14_0_REG;
  ALL_REGISTERS.DCDC_V14_1_REG = DCDC->DCDC_V14_1_REG;
  ALL_REGISTERS.DCDC_V18_0_REG = DCDC->DCDC_V18_0_REG;
  ALL_REGISTERS.DCDC_V18_1_REG = DCDC->DCDC_V18_1_REG;
  ALL_REGISTERS.DCDC_VDD_0_REG = DCDC->DCDC_VDD_0_REG;
  ALL_REGISTERS.DCDC_VDD_1_REG = DCDC->DCDC_VDD_1_REG;
  ALL_REGISTERS.DCDC_V18P_0_REG = DCDC->DCDC_V18P_0_REG;
  ALL_REGISTERS.DCDC_V18P_1_REG = DCDC->DCDC_V18P_1_REG;
  ALL_REGISTERS.DCDC_RET_0_REG = DCDC->DCDC_RET_0_REG;
  ALL_REGISTERS.DCDC_RET_1_REG = DCDC->DCDC_RET_1_REG;
  ALL_REGISTERS.DCDC_TRIM_REG = DCDC->DCDC_TRIM_REG;
  ALL_REGISTERS.DCDC_TEST_0_REG = DCDC->DCDC_TEST_0_REG;
  ALL_REGISTERS.DCDC_TEST_1_REG = DCDC->DCDC_TEST_1_REG;

  ALL_REGISTERS.DCDC_IRQ_CLEAR_REG = DCDC->DCDC_IRQ_CLEAR_REG;
  ALL_REGISTERS.DCDC_IRQ_MASK_REG = DCDC->DCDC_IRQ_MASK_REG;

  // CRG_TOP
  ALL_REGISTERS.BANDGAP_REG = CRG_TOP->BANDGAP_REG;
  ALL_REGISTERS.BOD_STATUS_REG = CRG_TOP->BOD_STATUS_REG;
  ALL_REGISTERS.FORCE_SLEEP_REG = CRG_TOP->FORCE_SLEEP_REG;
  ALL_REGISTERS.LDOS_DISABLE_REG = CRG_TOP->LDOS_DISABLE_REG;
  ALL_REGISTERS.AON_SPARE_REG = CRG_TOP->AON_SPARE_REG;

  // QSPIC
  ALL_REGISTERS.QSPIC_CTRLMODE_REG = QSPIC->QSPIC_CTRLMODE_REG;
  ALL_REGISTERS.QSPIC_BURSTCMDA_REG = QSPIC->QSPIC_BURSTCMDA_REG;
  ALL_REGISTERS.QSPIC_BURSTCMDB_REG = QSPIC->QSPIC_BURSTCMDB_REG;
  ALL_REGISTERS.QSPIC_WRITEDATA_REG = QSPIC->QSPIC_WRITEDATA_REG;
  ALL_REGISTERS.QSPIC_DUMMYDATA_REG = QSPIC->QSPIC_DUMMYDATA_REG;
  ALL_REGISTERS.QSPIC_ERASECTRL_REG = QSPIC->QSPIC_ERASECTRL_REG;
  ALL_REGISTERS.QSPIC_ERASECMDA_REG = QSPIC->QSPIC_ERASECMDA_REG;
  ALL_REGISTERS.QSPIC_ERASECMDB_REG = QSPIC->QSPIC_ERASECMDB_REG;
  ALL_REGISTERS.QSPIC_BURSTBRK_REG = QSPIC->QSPIC_BURSTBRK_REG;
  ALL_REGISTERS.QSPIC_STATUSCMD_REG = QSPIC->QSPIC_STATUSCMD_REG;
  ALL_REGISTERS.QSPIC_CHCKERASE_REG = QSPIC->QSPIC_CHCKERASE_REG;
  ALL_REGISTERS.QSPIC_GP_REG = QSPIC->QSPIC_GP_REG;
  ALL_REGISTERS.QSPIC_UCODE_START = QSPIC->QSPIC_UCODE_START;

  // GPREG
  ALL_REGISTERS.PLL_SYS_CTRL1_REG = GPREG->PLL_SYS_CTRL1_REG;
  ALL_REGISTERS.PLL_SYS_CTRL2_REG = GPREG->PLL_SYS_CTRL2_REG;
  ALL_REGISTERS.PLL_SYS_CTRL3_REG = GPREG->PLL_SYS_CTRL3_REG;
  ALL_REGISTERS.PLL_SYS_TEST_REG = GPREG->PLL_SYS_TEST_REG;

  // CACHE
  ALL_REGISTERS.CACHE_CTRL1_REG = CACHE->CACHE_CTRL1_REG;
  ALL_REGISTERS.CACHE_LNSIZECFG_REG = CACHE->CACHE_LNSIZECFG_REG;
  ALL_REGISTERS.CACHE_ASSOCCFG_REG = CACHE->CACHE_ASSOCCFG_REG;
  ALL_REGISTERS.CACHE_CTRL2_REG = CACHE->CACHE_CTRL2_REG;
  ALL_REGISTERS.CACHE_CTRL3_REG = CACHE->CACHE_CTRL3_REG;
  ALL_REGISTERS.CACHE_MRM_HITS_REG = CACHE->CACHE_MRM_HITS_REG;
  ALL_REGISTERS.CACHE_MRM_MISSES_REG = CACHE->CACHE_MRM_MISSES_REG;
  ALL_REGISTERS.CACHE_MRM_CTRL_REG = CACHE->CACHE_MRM_CTRL_REG;
  ALL_REGISTERS.CACHE_MRM_TINT_REG = CACHE->CACHE_MRM_TINT_REG;
  ALL_REGISTERS.CACHE_MRM_THRES_REG = CACHE->CACHE_MRM_THRES_REG;
  ALL_REGISTERS.SWD_RESET_REG = CACHE->SWD_RESET_REG;

#endif // DEFAULT_REGISTER_DEBUG
}
