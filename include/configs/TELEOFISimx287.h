/*
 * Copyright (C) 2011 Marek Vasut <marek.vasut@gmail.com>
 * on behalf of DENX Software Engineering GmbH
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */
#ifndef __CONFIGS_TELEOFISimx287_H__
#define __CONFIGS_TELEOFISimx287_H__

/* System configurations */
#define CONFIG_MX28				/* i.MX28 SoC */
#define MACH_TYPE_TELEOFISimx287	3613			
#define CONFIG_MACH_TYPE	MACH_TYPE_TELEOFISimx287			
#define CONFIG_ENV_OVERWRITE

/* U-Boot Commands */
#define CONFIG_SYS_NO_FLASH
#include <config_cmd_default.h>
#define CONFIG_DISPLAY_CPUINFO	

#define CONFIG_CMD_ASKENV					
#define CONFIG_CMD_CACHE
#define CONFIG_CMD_DATE
#define CONFIG_CMD_DHCP
#define CONFIG_CMD_FS_GENERIC	
#define CONFIG_CMD_GPIO
#define CONFIG_CMD_GREPENV
#define CONFIG_CMD_NAND
#define CONFIG_CMD_NAND_TRIMFFS
#define CONFIG_CMD_NET
#define CONFIG_CMD_PING
#define CONFIG_CMD_SETEXPR	
#define CONFIG_CMD_USB

#define CONFIG_MXS_OCOTP
#define CONFIG_CMD_FUSE
#define CONFIG_CMD_MEMTEST

#define CONFIG_REGEX				/* Enable regular expression support */	

/* Memory configuration */
#define CONFIG_NR_DRAM_BANKS		1			/* 1 bank of DRAM */
#define PHYS_SDRAM_1				0x40000000	/* Base address */
#define PHYS_SDRAM_1_SIZE			0x40000000	/* Max 128 MB RAM */

#define CONFIG_SYS_SDRAM_BASE		PHYS_SDRAM_1

/* Environment */
#define CONFIG_ENV_SIZE				(256 * 1024)	/* 256kB VOVS */
#define CONFIG_ENV_IS_IN_NAND		1

/* Environment is in NAND */
#if defined(CONFIG_CMD_NAND) && defined(CONFIG_ENV_IS_IN_NAND)
#define CONFIG_ENV_SECT_SIZE		0x20000 	/* // 128k but parse this !!! 	// VOVS */
#define CONFIG_ENV_RANGE			0x40000		/* // 256k for environment		// was (2 * CONFIG_ENV_SECT_SIZE)*/					
#define CONFIG_ENV_OFFSET			0x300000 	/* // 3 MB (after uboot)		// VOVS */


#define CONFIG_CMD_UBI
#define CONFIG_CMD_MTDPARTS
#define CONFIG_RBTREE
#define CONFIG_LZO
#define CONFIG_MTD_DEVICE
#define CONFIG_MTD_PARTITIONS
#define MTDIDS_DEFAULT			"nand0=gpmi-nand"
#else
#define CONFIG_ENV_IS_NOWHERE	
#endif

/* FEC Ethernet on SoC */
#ifdef CONFIG_CMD_NET
#define CONFIG_FEC_MXC		
#endif

/* HW Watchdog*/
#define CONFIG_HW_WATCHDOG
#define CONFIG_GPIO_WDT
#define WDGRES_PIN					MX28_PAD_LCD_D13__GPIO_1_13
/* RTC */
#ifdef CONFIG_CMD_DATE
/* Use the internal RTC in the MXS chip */
#define CONFIG_RTC_INTERNAL
#ifdef CONFIG_RTC_INTERNAL
#define CONFIG_RTC_MXS
#else
#define CONFIG_RTC_M41T62
#define CONFIG_SYS_I2C_RTC_ADDR		0x68
#define CONFIG_SYS_M41T11_BASE_YEAR	2000
#endif
#endif

/* USB */
#ifdef CONFIG_CMD_USB
#define CONFIG_EHCI_MXS_PORT0
#define CONFIG_EHCI_MXS_PORT1				
#define CONFIG_USB_MAX_CONTROLLER_COUNT	2
#define CONFIG_USB_STORAGE
#endif


/* Booting Linux */
#define CONFIG_AUTOBOOT
#define CONFIG_AUTOBOOT_KEYED
#define CONFIG_AUTOBOOT_PROMPT		\
	"Type password to abort autoboot in %d seconds\n", bootdelay
#define CONFIG_BOOTDELAY			3
#define CONFIG_AUTOBOOT_STOP_STR2 "root" /*default password*/


		/*was ttyAMA0*/
#define CONFIG_BOOTARGS		"console=ttyAPP4,115200 usbcore.autosuspend=-1 rootfstype=ubifs ubi.mtd=1 root=ubi0:rootfs_a rw mtdparts=gpmi-nand:5m(bootloader),-(root)"
#define CONFIG_BOOTCOMMAND	"run nand_boot"
#define CONFIG_LOADADDR		0x42000000
#define CONFIG_SYS_LOAD_ADDR	CONFIG_LOADADDR
#define CONFIG_SERVERIP 	192.168.88.11
#define CONFIG_IPADDR 	 	192.168.88.1
#define CONFIG_ETHADDR  	00:11:22:33:44:55
#define CONFIG_ETH1ADDR  	00:11:22:33:44:66

/* Extra Environment */
#define CONFIG_PREBOOT		
#define CONFIG_HOSTNAME		TELEOFISimx287

/* all here ??? */
#define CONFIG_EXTRA_ENV_SETTINGS										\
	"mtdparts=mtdparts=gpmi-nand:"										\
				"5m(bootloader),"										\
				"-(root)\0"												\
	"hostname=imx287\0"													\
	"bootstopkey2=root\0"												\
	"update_nand_full_filename=u-boot.nand\0"							\
	"update_nand_stride=0x40\0"	/* MX28 datasheet ch. 12.12 */			\
	"update_nand_count=0x4\0"	/* MX28 datasheet ch. 12.12 */			\
	"filesize_rootfs=2000000\0"                                 		\
	"update_nand_get_fcb_size="	/* Get size of FCB blocks */			\
		"nand device 0 ; "												\
		"nand info ; "													\
		"setexpr fcb_sz ${update_nand_stride} * ${update_nand_count};"	\
		"setexpr update_nand_fcb ${fcb_sz} * ${nand_writesize}\0"		\
	"fuse_burning="	/* Get size of FCB blocks */						\
		"fuse prog -y 3 0 04000000 ; "									\
		"fuse prog -y 3 1 00100000 ; "									\
		"fuse prog -y 3 7 00100001\0"									\
	"update_nand_full="		/* Update FCB, DBBT and FW */				\
		"if tftp ${update_nand_full_filename} ; then "					\
		"run update_nand_get_fcb_size ; "								\
		"nand scrub -y 0x0 ${filesize} ; "								\
		"nand write.raw ${loadaddr} 0x0 ${fcb_sz} ; "					\
		"setexpr update_off ${loadaddr} + ${update_nand_fcb} ; " 		\
		"setexpr update_sz ${filesize} - ${update_nand_fcb} ; " 		\
		"nand write ${update_off} ${update_nand_fcb} ${update_sz} ; " 	\
		"fi\0"															\
	"erase_all="		/* Update FCB, DBBT and FW */					\
		"if tftp zero.img ; then "										\
		"run update_nand_get_fcb_size ; "								\
		"nand write ${loadaddr} 0x0 ${filesize} ; "						\
		"nand write ${loadaddr} 0x4000000 ${filesize} ; "				\
		"nand write ${loadaddr} 0x8000000 ${filesize} ; "				\
		"nand write ${loadaddr} 0xBF20000 ${filesize} ; "				\
		"fi\0"															\
	"update_system="													\
		"if tftp 0x42000000 root ; then "								\
		"setenv filesize_rootfs ${filesize} ; "							\
		"nand erase.part root ; "										\
		"ubi part root ; "												\
		"ubi create kernel_a 0x500000 ; "								\
		"ubi create kernel_b 0x500000 ; "								\
		"ubi create rootfs_a 0x2A00000 ; "								\
		"ubi create rootfs_b 0x2A00000 ; " 								\
		"ubi create rootfs_data 0x2800000 ; "							\
		"ubi create extra_ubi ; "										\
		"ubi write 0x42000000 rootfs_a ${filesize_rootfs} ; "			\
		"ubi write 0x42000000 rootfs_b ${filesize_rootfs} ; "			\
		"fi ;"															\
		"if tftp 0x42000000 kernel ; then "								\
		"setenv filesize_kernel ${filesize} ; "							\
		"saveenv ; "													\
		"ubi part root ; "												\
		"ubi write 0x42000000 kernel_a ${filesize_kernel} ; "			\
		"ubi write 0x42000000 kernel_b ${filesize_kernel} ; "			\
		"fi\0"															\
	"try_boot="															\
		"ubi part root ; "												\
		"ubi read 0x42000000 kernel_${image} ; "						\
		"bootm 0x42000000 - 0x42400000\0" 								\
	"nand_boot="														\
		"if test ${boot_status} = upgrade ; then "						\
		"setenv bootargs console=ttyAPP4,115200 usbcore.autosuspend=-1 "\
			"rootfstype=ubifs ubi.mtd=1 root=ubi0:rootfs_${image} "		\
			"rw mtdparts=gpmi-nand:5m(bootloader),-(root); "			\
			"setenv boot_status try; "									\
			"saveenv; "													\
			"run try_boot ; "											\
		"fi ; "															\
		"if test ${boot_status} = try ; then "							\
			"if test ${image} = a ; then "								\
				"setenv image b ; "										\
			"else "														\
				"setenv image a ; "										\
			"fi ; "														\
			"setenv boot_status upgrade ; "								\
			"boot ; "													\
		"fi ;"							 								\
		"run try_boot \0"												\
	"factory_reset="													\
		"ubi part root ; "												\
		"ubi remove rootfs_data ; "										\
		"ubi create rootfs_data \0"										\
	"boot_status=normal\0"												\
	"image=a"

/* The rest of the configuration is shared */
#include <configs/mxs.h>

#endif /* __CONFIGS_TELEOFISimx287_H__ */
