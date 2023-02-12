/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright (C) 2011 Samsung Electronics
 *
 * Configuration settings for the SAMSUNG TINY4412 (EXYNOS4412) board.
 */

#ifndef __CONFIG_TINY4412_H
#define __CONFIG_TINY4412_H

#include <configs/exynos4-common.h>

/* High Level Configuration Options */
#define CONFIG_EXYNOS4412		1	/* which is a EXYNOS4412 SoC */
#define CONFIG_TINY4412			1	/* working with TINY4412*/

#define CONFIG_SYS_DCACHE_OFF		1

/* TINY4412 has 4 bank of DRAM */
#define CONFIG_SYS_SDRAM_BASE		0x40000000
#define PHYS_SDRAM_1			CONFIG_SYS_SDRAM_BASE
#define SDRAM_BANK_SIZE			(256 << 20)	/* 256 MB */

/* memtest works on */
#define CONFIG_SYS_MEMTEST_START	CONFIG_SYS_SDRAM_BASE
#define CONFIG_SYS_MEMTEST_END		(CONFIG_SYS_SDRAM_BASE + 0x6000000)
#define CONFIG_SYS_LOAD_ADDR		(CONFIG_SYS_SDRAM_BASE + 0x3E00000)

#define CONFIG_MACH_TYPE		MACH_TYPE_TINY4412

/* select serial console configuration */

/* Console configuration */
#define CONFIG_DEFAULT_CONSOLE		"console=ttySAC0,115200n8\0"

#define CONFIG_SYS_MEM_TOP_HIDE	(1 << 20)	/* ram console */

#define CONFIG_SYS_MONITOR_BASE	0x00000000

/* Power Down Modes */
#define S5P_CHECK_SLEEP			0x00000BAD
#define S5P_CHECK_DIDLE			0xBAD00000
#define S5P_CHECK_LPA			0xABAD0000

/* MMC SPL */
#define COPY_BL2_FNPTR_ADDR	0x02020030
#define CONFIG_SPL_TEXT_BASE	0x02023400

#define CONFIG_EXTRA_ENV_SETTINGS \
	"loadaddr=0x40007000\0" \
	"rdaddr=0x48000000\0" \
	"kerneladdr=0x40007000\0" \
	"ramdiskaddr=0x48000000\0" \
	"console=ttySAC0,115200n8\0" \
	"mmcdev=0\0" \
	"bootenv=uEnv.txt\0" \
	"loadbootenv=load mmc ${mmcdev} ${loadaddr} ${bootenv}\0" \
	"importbootenv=echo Importing environment from mmc ...; " \
		"env import -t $loadaddr $filesize\0" \
        "loadbootscript=load mmc ${mmcdev} ${loadaddr} boot.scr\0" \
        "bootscript=echo Running bootscript from mmc${mmcdev} ...; " \
                "source ${loadaddr}\0"
#define CONFIG_BOOTCOMMAND \
	"if mmc rescan; then " \
		"echo SD/MMC found on device ${mmcdev};" \
		"if run loadbootenv; then " \
			"echo Loaded environment from ${bootenv};" \
			"run importbootenv;" \
		"fi;" \
		"if test -n $uenvcmd; then " \
			"echo Running uenvcmd ...;" \
			"run uenvcmd;" \
		"fi;" \
		"if run loadbootscript; then " \
			"run bootscript; " \
		"fi; " \
	"fi;" \
	"load mmc ${mmcdev} ${loadaddr} uImage; bootm ${loadaddr} "

#define CONFIG_CLK_1000_400_200

/* MIU (Memory Interleaving Unit) */
#define CONFIG_MIU_2BIT_21_7_INTERLEAVED

#define CONFIG_SYS_MMC_ENV_DEV		0
#define CONFIG_ENV_SIZE			(16 << 10)	/* 16 KB */
#define RESERVE_BLOCK_SIZE		(512)
#define BL1_SIZE			(8 << 10) 	/* 8K reserved for BL1 */
#define BL2_SIZE			(16 << 10)	/* 16K reserved for BL1 */
#define TINY4412_ENV_SIZE       (16 << 10) /*16 K reserved for ENV*/
#define CONFIG_ENV_OFFSET		(RESERVE_BLOCK_SIZE + BL1_SIZE)

#define CONFIG_SPL_MAX_FOOTPRINT	(14 * 1024)

#ifdef CONFIG_SPL_BUILD
#define CONFIG_SYS_INIT_SP_ADDR		0x02040000
#else
#define CONFIG_SYS_INIT_SP_ADDR		0x42E00000
#endif

#define COPY_BL2_SIZE		0x4000
#define BL2_START_OFFSET	((RESERVE_BLOCK_SIZE + BL1_SIZE) / 512)
#define BL2_SIZE_BLOC_COUNT	(COPY_BL2_SIZE / 512)

/* U-Boot copy size from boot Media to DRAM.*/
#define COPY_UBOOT_SIZE		0xC8000 //800KB
#define UBOOT_START_OFFSET	((RESERVE_BLOCK_SIZE + BL1_SIZE + BL2_SIZE) / 512)
#define UBOOT_SIZE_BLOC_COUNT	(COPY_UBOOT_SIZE / 512)

#endif	/* __CONFIG_TINY4412_H */
