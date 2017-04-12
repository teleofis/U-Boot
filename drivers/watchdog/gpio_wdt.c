/*
 * watchdog.c - driver for i.mx on-chip watchdog
 *
 * Licensed under the GPL-2 or later.
 */

#include <common.h>
#include <asm/io.h>
#include <watchdog.h>
#include <asm/arch/imx-regs.h>
#include <asm/gpio.h>

#ifdef CONFIG_GPIO_WDT
static int watchdog_toggle=1;
void hw_watchdog_reset(void)
{
	mxs_iomux_setup_pad (WDGRES_PIN | MXS_PAD_3V3 | MXS_PAD_4MA | MXS_PAD_NOPULL);
	if (watchdog_toggle) {
		
		gpio_toggle(WDGRES_PIN);
	}else{
		gpio_direction_output (WDGRES_PIN, 1);
	}
}

void hw_watchdog_init(void)
{
	hw_watchdog_reset();
}

int do_wdog_toggle(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	if (argc != 2)
		goto usage;

	if (strncmp(argv[1], "on", 2) == 0)
		watchdog_toggle = 1;
	else if (strncmp(argv[1], "off", 3) == 0)
		watchdog_toggle = 0;
	else
		goto usage;

	return 0;
usage:
	printf("Usage: wdogtoggle %s\n", cmdtp->usage);
	return 1;
}

U_BOOT_CMD(
	wdogtoggle, CONFIG_SYS_MAXARGS, 2, do_wdog_toggle,
	"toggle GPIO pin to service watchdog",
	"[on/off] - Switch watchdog toggling via GPIO pin on/off"
);

#endif

