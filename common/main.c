/*
 * (C) Copyright 2000
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

/* #define	DEBUG	*/

#include <common.h>
#include <autoboot.h>
#include <cli.h>
#include <version.h>
#include <asm/gpio.h>

DECLARE_GLOBAL_DATA_PTR;

/*
 * Board-specific Platform code can reimplement show_boot_progress () if needed
 */
extern int reset_button_status(void);
__weak void show_boot_progress(int val) {}

static void modem_init(void)
{
#ifdef CONFIG_MODEM_SUPPORT
	debug("DEBUG: main_loop:   gd->do_mdm_init=%lu\n", gd->do_mdm_init);
	if (gd->do_mdm_init) {
		char *str = getenv("mdm_cmd");

		setenv("preboot", str);  /* set or delete definition */
		mdm_init(); /* wait for modem connection */
	}
#endif  /* CONFIG_MODEM_SUPPORT */
}

static int cmd_exec(const char* command)
{
debug("Run \"%s\":\n",command);

	return (run_command(command,0) >= 0);
}

static void run_preboot_environment_command(void)
{
#ifdef CONFIG_PREBOOT
	char *p;

	p = getenv("preboot");
	if (p != NULL) {
# ifdef CONFIG_AUTOBOOT_KEYED
		int prev = disable_ctrlc(1);	/* disable Control C checking */
# endif

		run_command_list(p, -1, 0);

# ifdef CONFIG_AUTOBOOT_KEYED
		disable_ctrlc(prev);	/* restore Control C checking */
# endif
	}
#endif /* CONFIG_PREBOOT */
}

/* We come here after U-Boot is initialised and ready to process commands */
void main_loop(void)
{
	const char *s;
	int counter = 0;
	bootstage_mark_name(BOOTSTAGE_ID_MAIN_LOOP, "main_loop");

	while(reset_button_status()){		
		udelay(100000);
		gpio_toggle(MX28_PAD_SSP0_DATA3__GPIO_2_3);
		gpio_toggle(MX28_PAD_SSP0_CMD__GPIO_2_8);
		gpio_toggle(MX28_PAD_SSP0_DETECT__GPIO_2_9);
		if (!reset_button_status()){
			gpio_direction_output (MX28_PAD_SSP0_DATA3__GPIO_2_3, 1);
			gpio_direction_output (MX28_PAD_SSP0_CMD__GPIO_2_8, 1);
			gpio_direction_output (MX28_PAD_SSP0_DETECT__GPIO_2_9, 1);
			break;
		}
		counter++;
		if (counter >= 30)
			cmd_exec("run factory_reset");	
	}

#ifndef CONFIG_SYS_GENERIC_BOARD
	puts("Warning: Your board does not use generic board. Please read\n");
	puts("doc/README.generic-board and take action. Boards not\n");
	puts("upgraded by the late 2014 may break or be removed.\n");
#endif

	modem_init();
#ifdef CONFIG_VERSION_VARIABLE
	setenv("ver", version_string);  /* set version variable */
#endif /* CONFIG_VERSION_VARIABLE */

	cli_init();

	run_preboot_environment_command();

#if defined(CONFIG_UPDATE_TFTP)
	update_tftp(0UL);
#endif /* CONFIG_UPDATE_TFTP */

	s = bootdelay_process();
	if (cli_process_fdt(&s))
		cli_secure_boot_cmd(s);

	autoboot_command(s);

	cli_loop();
}
