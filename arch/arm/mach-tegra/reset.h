/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * arch/arm/mach-tegra/reset.h
 *
 * CPU reset dispatcher.
 *
 * Copyright (c) 2011-2014, NVIDIA CORPORATION.  All rights reserved.
 * 
 */

#ifndef __MACH_TEGRA_RESET_H
#define __MACH_TEGRA_RESET_H

#define TEGRA_RESET_MASK_PRESENT	0
#define TEGRA_RESET_MASK_LP1		1
#define TEGRA_RESET_MASK_LP2		2
#define TEGRA_RESET_STARTUP_SECONDARY	3
#define TEGRA_RESET_STARTUP_LP2		4
#define TEGRA_RESET_STARTUP_LP1		5
#define TEGRA_RESET_TF_PRESENT		6
#define TEGRA_RESET_C0_L2_TAG_LATENCY	7
#define TEGRA_RESET_C0_L2_DATA_LATENCY	8
#define TEGRA_RESET_C1_L2_TAG_LATENCY	9
#define TEGRA_RESET_C1_L2_DATA_LATENCY	10
#define TEGRA_RESET_MASK_MC_CLK		11
#define TEGRA_RESET_SECURE_FW_PRESENT	12
#define TEGRA_RESET_DATA_SIZE		13

#ifdef CONFIG_ARM64
#define RESET_DATA(x)	((TEGRA_RESET_##x)*8)
#else
#define RESET_DATA(x)	((TEGRA_RESET_##x)*4)
#endif

#define RESET_DATA(x)	((TEGRA_RESET_##x)*4)

#ifndef __ASSEMBLY__

#include <linux/cpumask.h>

extern unsigned long __tegra_cpu_reset_handler_data[TEGRA_RESET_DATA_SIZE];

void __tegra_cpu_reset_handler_start(void);
void __tegra_cpu_reset_handler(void);
void __tegra_cpu_reset_handler_end(void);
void tegra_secondary_startup(void);

#ifdef CONFIG_PM_SLEEP
#define tegra_cpu_lp1_mask ((unsigned long *)(IO_ADDRESS(TEGRA_RESET_HANDLER_BASE + \
		((ulong)&__tegra_cpu_reset_handler_data[TEGRA_RESET_MASK_LP1] - \
		 (ulong)__tegra_cpu_reset_handler_start))))

#define tegra_mc_clk_mask ((unsigned long *)(IO_ADDRESS(TEGRA_RESET_HANDLER_BASE + \
		((ulong)&__tegra_cpu_reset_handler_data[TEGRA_RESET_MASK_MC_CLK] - \
		 (ulong)__tegra_cpu_reset_handler_start))))

#define tegra_cpu_reset_handler_ptr ((u32 *)(IO_ADDRESS(TEGRA_RESET_HANDLER_BASE + \
		((ulong)__tegra_cpu_reset_handler_data - \
		 (ulong)__tegra_cpu_reset_handler_start))))

#define tegra_cpu_lp2_mask ((cpumask_t *)(IO_ADDRESS(TEGRA_RESET_HANDLER_BASE + \
		((ulong)&__tegra_cpu_reset_handler_data[TEGRA_RESET_MASK_LP2] - \
		 (ulong)__tegra_cpu_reset_handler_start))))
#endif

#define tegra_cpu_c0_l2_tag_latency \
	__tegra_cpu_reset_handler_data[TEGRA_RESET_C0_L2_TAG_LATENCY]

#define tegra_cpu_c0_l2_tag_latency_iram \
	((ulong *)(IO_ADDRESS(TEGRA_RESET_HANDLER_BASE +			\
	((ulong)&__tegra_cpu_reset_handler_data[TEGRA_RESET_C0_L2_TAG_LATENCY] \
	 - (ulong)__tegra_cpu_reset_handler_start))))

#define tegra_cpu_c0_l2_data_latency \
	__tegra_cpu_reset_handler_data[TEGRA_RESET_C0_L2_DATA_LATENCY]

#define tegra_cpu_c0_l2_data_latency_iram \
	((ulong *)(IO_ADDRESS(TEGRA_RESET_HANDLER_BASE +			\
	((ulong)&__tegra_cpu_reset_handler_data[TEGRA_RESET_C0_L2_DATA_LATENCY] \
	 - (ulong)__tegra_cpu_reset_handler_start))))

#define tegra_cpu_c1_l2_tag_latency \
	__tegra_cpu_reset_handler_data[TEGRA_RESET_C1_L2_TAG_LATENCY]

#define tegra_cpu_c1_l2_tag_latency_iram \
	((ulong *)(IO_ADDRESS(TEGRA_RESET_HANDLER_BASE +			\
	((ulong)&__tegra_cpu_reset_handler_data[TEGRA_RESET_C1_L2_TAG_LATENCY] \
	 - (ulong)__tegra_cpu_reset_handler_start))))

#define tegra_cpu_c1_l2_data_latency \
	__tegra_cpu_reset_handler_data[TEGRA_RESET_C1_L2_DATA_LATENCY]

#define tegra_cpu_c1_l2_data_latency_iram \
	((ulong *)(IO_ADDRESS(TEGRA_RESET_HANDLER_BASE +			\
	((ulong)&__tegra_cpu_reset_handler_data[TEGRA_RESET_C1_L2_DATA_LATENCY] \
	 - (ulong)__tegra_cpu_reset_handler_start))))

#define tegra_cpu_reset_handler_offset \
		((ulong)__tegra_cpu_reset_handler - \
		 (ulong)__tegra_cpu_reset_handler_start)

#define tegra_cpu_reset_handler_size \
		(__tegra_cpu_reset_handler_end - \
		 __tegra_cpu_reset_handler_start)

#ifdef CONFIG_PM_SLEEP
void tegra_cpu_reset_handler_save(void);
void tegra_cpu_reset_handler_restore(void);
#endif
#endif
#endif
