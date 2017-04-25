/*
 * Freescale MX28EVK board
 *
 * (C) Copyright 2011 Freescale Semiconductor, Inc.
 *
 * Author: Fabio Estevam <fabio.estevam@freescale.com>
 *
 * Based on m28evk.c:
 * Copyright (C) 2011 Marek Vasut <marek.vasut@gmail.com>
 * on behalf of DENX Software Engineering GmbH
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <asm/gpio.h>
#include <asm/io.h>
#include <asm/arch/imx-regs.h>
#include <asm/arch/iomux-mx28.h>
#include <asm/arch/clock.h>
#include <asm/arch/sys_proto.h>
#include <linux/mii.h>
#include <miiphy.h>
#include <netdev.h>
#include <errno.h>

DECLARE_GLOBAL_DATA_PTR;

#define	MUX_CONFIG_GPMI	(MXS_PAD_3V3 | MXS_PAD_12MA | MXS_PAD_NOPULL)
#define MUX_CONFIG_GPIO	(MXS_PAD_3V3 | MXS_PAD_4MA | MXS_PAD_NOPULL)

/*
 * Functions
 */
int board_early_init_f(void)
{
	int i;

	/* IO0 clock at 480MHz */
	mxs_set_ioclk(MXC_IOCLK0, 480000);
	/* IO1 clock at 480MHz */
	mxs_set_ioclk(MXC_IOCLK1, 480000);
	// LED.TOP
	mxs_iomux_setup_pad (MX28_PAD_SSP0_DATA3__GPIO_2_3 | MUX_CONFIG_GPIO);
	gpio_direction_output (MX28_PAD_SSP0_DATA3__GPIO_2_3, 1);
	// LED.MID
	mxs_iomux_setup_pad (MX28_PAD_SSP0_CMD__GPIO_2_8 | MUX_CONFIG_GPIO);
	gpio_direction_output (MX28_PAD_SSP0_CMD__GPIO_2_8, 1);
	// LED.BOT
	mxs_iomux_setup_pad (MX28_PAD_SSP0_DETECT__GPIO_2_9 | MUX_CONFIG_GPIO);
	gpio_direction_output (MX28_PAD_SSP0_DETECT__GPIO_2_9, 1);
	//GSM.SIMDET
	//mxs_iomux_setup_pad (MX28_PAD_SSP1_DATA0__GPIO_2_14 | MUX_CONFIG_GPIO);
	//gpio_direction_output (MX28_PAD_SSP1_DATA0__GPIO_2_14, 0);
	// USB0.VCCEN
	mxs_iomux_setup_pad (MX28_PAD_I2C0_SDA__GPIO_3_25 | MUX_CONFIG_GPIO);
	gpio_direction_output (MX28_PAD_I2C0_SDA__GPIO_3_25, 0);
	//GSM.PWRKEY
	mxs_iomux_setup_pad (MX28_PAD_SSP2_MOSI__GPIO_2_17 | MUX_CONFIG_GPIO);
	gpio_direction_output (MX28_PAD_SSP2_MOSI__GPIO_2_17, 0);
	//GSM.VCCEN#
	mxs_iomux_setup_pad (MX28_PAD_SSP2_SS0__GPIO_2_19 | MUX_CONFIG_GPIO);
	gpio_direction_output (MX28_PAD_SSP2_SS0__GPIO_2_19, 1);
	//+5V35.OFF
	mxs_iomux_setup_pad (MX28_PAD_LCD_D14__GPIO_1_14 | MUX_CONFIG_GPIO);
	gpio_direction_output (MX28_PAD_LCD_D14__GPIO_1_14, 1);
	/* SSP0 clock at 96MHz */
	//mxs_set_sspclk(MXC_SSPCLK0, 96000, 0);
	/* SSP2 clock at 160MHz */
//	mxs_set_sspclk(MXC_SSPCLK2, 160000, 0);

#ifdef	CONFIG_CMD_USB
//    while (1) {}

//	mxs_iomux_setup_pad(MX28_PAD_SSP2_SS1__USB1_OVERCURRENT);
//	mxs_iomux_setup_pad(MX28_PAD_AUART2_RX__GPIO_3_8 |
//			MXS_PAD_4MA | MXS_PAD_3V3 | MXS_PAD_NOPULL);
//	gpio_direction_output(MX28_PAD_AUART2_RX__GPIO_3_8, 1);
#endif

//	mxs_iomux_setup_pad(MX28_PAD_I2C0_SDA__GPIO_3_25 | MXS_PAD_4MA | MXS_PAD_1V8 | MXS_PAD_NOPULL);
//	gpio_direction_output(MX28_PAD_I2C0_SDA__GPIO_3_25, 0);

/*	mxs_iomux_setup_pad (MX28_PAD_GPMI_D00__GPIO_0_0 | MUX_CONFIG_GPMI);
	gpio_direction_output (MX28_PAD_GPMI_D00__GPIO_0_0, 0);
	mxs_iomux_setup_pad (MX28_PAD_GPMI_D01__GPIO_0_1 | MUX_CONFIG_GPMI);
	gpio_direction_output (MX28_PAD_GPMI_D01__GPIO_0_1, 0);
	mxs_iomux_setup_pad (MX28_PAD_GPMI_D02__GPIO_0_2 | MUX_CONFIG_GPMI);
	gpio_direction_output (MX28_PAD_GPMI_D02__GPIO_0_2, 0);
	mxs_iomux_setup_pad (MX28_PAD_GPMI_D03__GPIO_0_3 | MUX_CONFIG_GPMI);
	gpio_direction_output (MX28_PAD_GPMI_D03__GPIO_0_3, 0);
	mxs_iomux_setup_pad (MX28_PAD_GPMI_D04__GPIO_0_4 | MUX_CONFIG_GPMI);
	gpio_direction_output (MX28_PAD_GPMI_D04__GPIO_0_4, 0);
	mxs_iomux_setup_pad (MX28_PAD_GPMI_D05__GPIO_0_5 | MUX_CONFIG_GPMI);
	gpio_direction_output (MX28_PAD_GPMI_D05__GPIO_0_5, 0);
	mxs_iomux_setup_pad (MX28_PAD_GPMI_D06__GPIO_0_6 | MUX_CONFIG_GPMI);
	gpio_direction_output (MX28_PAD_GPMI_D06__GPIO_0_6, 0);
	mxs_iomux_setup_pad (MX28_PAD_GPMI_D07__GPIO_0_7 | MUX_CONFIG_GPMI);
	gpio_direction_output (MX28_PAD_GPMI_D07__GPIO_0_7, 0);
	mxs_iomux_setup_pad (MX28_PAD_GPMI_CE0N__GPIO_0_16 | MUX_CONFIG_GPMI);
	gpio_direction_output (MX28_PAD_GPMI_CE0N__GPIO_0_16, 0);
	mxs_iomux_setup_pad (MX28_PAD_GPMI_RDY0__GPIO_0_20 | MUX_CONFIG_GPMI);
	gpio_direction_output (MX28_PAD_GPMI_RDY0__GPIO_0_20, 0);
	mxs_iomux_setup_pad (MX28_PAD_GPMI_RDN__GPIO_0_24 | MUX_CONFIG_GPMI);
	gpio_direction_output (MX28_PAD_GPMI_RDN__GPIO_0_24, 0);
	mxs_iomux_setup_pad (MX28_PAD_GPMI_WRN__GPIO_0_25 | MUX_CONFIG_GPMI);
	gpio_direction_output (MX28_PAD_GPMI_WRN__GPIO_0_25, 0);
	mxs_iomux_setup_pad (MX28_PAD_GPMI_ALE__GPIO_0_26 | MUX_CONFIG_GPMI);
	gpio_direction_output (MX28_PAD_GPMI_ALE__GPIO_0_26, 0);
	mxs_iomux_setup_pad (MX28_PAD_GPMI_CLE__GPIO_0_27 | MUX_CONFIG_GPMI);
	gpio_direction_output (MX28_PAD_GPMI_CLE__GPIO_0_27, 0);
	mxs_iomux_setup_pad (MX28_PAD_GPMI_RESETN__GPIO_0_28 | MUX_CONFIG_GPMI);
	gpio_direction_output (MX28_PAD_GPMI_RESETN__GPIO_0_28, 0);

	while (1) {
		for (i = 0; i < 100; i++ ) {
			gpio_set_value (MX28_PAD_GPMI_D00__GPIO_0_0, 1);
			gpio_set_value (MX28_PAD_GPMI_D00__GPIO_0_0, 0);
		}
		for (i = 0; i < 100; i++ ) {
			gpio_set_value (MX28_PAD_GPMI_D01__GPIO_0_1, 1);
			gpio_set_value (MX28_PAD_GPMI_D01__GPIO_0_1, 0);
		}
		for (i = 0; i < 100; i++ ) {
			gpio_set_value (MX28_PAD_GPMI_D02__GPIO_0_2, 1);
			gpio_set_value (MX28_PAD_GPMI_D02__GPIO_0_2, 0);
		}
		for (i = 0; i < 100; i++ ) {
			gpio_set_value (MX28_PAD_GPMI_D03__GPIO_0_3, 1);
			gpio_set_value (MX28_PAD_GPMI_D03__GPIO_0_3, 0);
		}
		for (i = 0; i < 100; i++ ) {
			gpio_set_value (MX28_PAD_GPMI_D04__GPIO_0_4, 1);
			gpio_set_value (MX28_PAD_GPMI_D04__GPIO_0_4, 0);
		}
		for (i = 0; i < 100; i++ ) {
			gpio_set_value (MX28_PAD_GPMI_D05__GPIO_0_5, 1);
			gpio_set_value (MX28_PAD_GPMI_D05__GPIO_0_5, 0);
		}
		for (i = 0; i < 100; i++ ) {
			gpio_set_value (MX28_PAD_GPMI_D06__GPIO_0_6, 1);
			gpio_set_value (MX28_PAD_GPMI_D06__GPIO_0_6, 0);
		}
		for (i = 0; i < 100; i++ ) {
			gpio_set_value (MX28_PAD_GPMI_D07__GPIO_0_7, 1);
			gpio_set_value (MX28_PAD_GPMI_D07__GPIO_0_7, 0);
		}
		for (i = 0; i < 100; i++ ) {
			gpio_set_value (MX28_PAD_GPMI_CE0N__GPIO_0_16, 1);
			gpio_set_value (MX28_PAD_GPMI_CE0N__GPIO_0_16, 0);
		}
		for (i = 0; i < 100; i++ ) {
			gpio_set_value (MX28_PAD_GPMI_RDY0__GPIO_0_20, 1);
			gpio_set_value (MX28_PAD_GPMI_RDY0__GPIO_0_20, 0);
		}
		for (i = 0; i < 100; i++ ) {
			gpio_set_value (MX28_PAD_GPMI_RDN__GPIO_0_24, 1);
			gpio_set_value (MX28_PAD_GPMI_RDN__GPIO_0_24, 0);
		}
		for (i = 0; i < 100; i++ ) {
			gpio_set_value (MX28_PAD_GPMI_WRN__GPIO_0_25, 1);
			gpio_set_value (MX28_PAD_GPMI_WRN__GPIO_0_25, 0);
		}
		for (i = 0; i < 100; i++ ) {
			gpio_set_value (MX28_PAD_GPMI_ALE__GPIO_0_26, 1);
			gpio_set_value (MX28_PAD_GPMI_ALE__GPIO_0_26, 0);
		}
		for (i = 0; i < 100; i++ ) {
			gpio_set_value (MX28_PAD_GPMI_CLE__GPIO_0_27, 1);
			gpio_set_value (MX28_PAD_GPMI_CLE__GPIO_0_27, 0);
		}
		for (i = 0; i < 100; i++ ) {
			gpio_set_value (MX28_PAD_GPMI_RESETN__GPIO_0_28, 1);
			gpio_set_value (MX28_PAD_GPMI_RESETN__GPIO_0_28, 0);
		}
	}*/
	/* Power on LCD */
//	gpio_direction_output(MX28_PAD_LCD_RESET__GPIO_3_30, 1);

	/* Set contrast to maximum */
//	gpio_direction_output(MX28_PAD_PWM2__GPIO_3_18, 1);

	return 0;
}

int dram_init(void)
{
	return mxs_dram_init();
}

int reset_button_status(void){
	
	mxs_iomux_setup_pad (MX28_PAD_LCD_D15__GPIO_1_15 | MUX_CONFIG_GPIO);
	return gpio_get_value(MX28_PAD_LCD_D15__GPIO_1_15);
}

int board_init(void)
{
	/* Adress of boot parameters */
	gd->bd->bi_boot_params = PHYS_SDRAM_1 + 0x100;

	return 0;
}

#ifdef	CONFIG_CMD_MMC
static int mx28evk_mmc_wp(int id)
{
//    while (1) {}

	if (id != 0) {
		printf("MXS MMC: Invalid card selected (card id = %d)\n", id);
		return 1;
	}

	return gpio_get_value(MX28_PAD_SSP1_SCK__GPIO_2_12);
}

int board_mmc_init(bd_t *bis)
{
//    while (1) {}

	/* Configure WP as input */
//	gpio_direction_input(MX28_PAD_SSP1_SCK__GPIO_2_12);

	/* Configure MMC0 Power Enable */
//	gpio_direction_output(MX28_PAD_PWM3__GPIO_3_28, 0);

	return mxsmmc_initialize(bis, 0, mx28evk_mmc_wp, NULL);
}
#endif

#ifdef	CONFIG_CMD_NET

int board_eth_init(bd_t *bis)
{
//    while (1) {}

	struct mxs_clkctrl_regs *clkctrl_regs =
		(struct mxs_clkctrl_regs *)MXS_CLKCTRL_BASE;
	struct eth_device *dev;
	int ret;

	ret = cpu_eth_init(bis);
	if (ret)
		return ret;

	/* MX28EVK uses ENET_CLK PAD to drive FEC clock */
	writel(CLKCTRL_ENET_TIME_SEL_RMII_CLK | CLKCTRL_ENET_CLK_OUT_EN,
	       &clkctrl_regs->hw_clkctrl_enet);

	/* Power-on FECs */
//	gpio_direction_output(MX28_PAD_SSP1_DATA3__GPIO_2_15, 0);

	/* Reset FEC PHYs */
//	gpio_direction_output(MX28_PAD_ENET0_RX_CLK__GPIO_4_13, 0);
//	udelay(200);
//	gpio_set_value(MX28_PAD_ENET0_RX_CLK__GPIO_4_13, 1);

	ret = fecmxc_initialize_multi(bis, 0, 0, MXS_ENET0_BASE);
	if (ret) {
		puts("FEC MXS: Unable to init FEC0\n");
		return ret;
	}

	ret = fecmxc_initialize_multi(bis, 1, 3, MXS_ENET1_BASE);
	if (ret) {
		puts("FEC MXS: Unable to init FEC1\n");
		return ret;
	}

	dev = eth_get_dev_by_name("FEC0");
	if (!dev) {
		puts("FEC MXS: Unable to get FEC0 device entry\n");
		return -EINVAL;
	}

	dev = eth_get_dev_by_name("FEC1");
	if (!dev) {
		puts("FEC MXS: Unable to get FEC1 device entry\n");
		return -EINVAL;
	}

	return ret;
}

#endif
