/*
 * bq2419x-charger.h -- BQ24190/BQ24192/BQ24192i/BQ24193 Charger driver
 *
 * Copyright (c) 2013-2017, NVIDIA CORPORATION.  All rights reserved.
 *
 * Author: Laxman Dewangan <ldewangan@nvidia.com>
 * Author: Syed Rafiuddin <srafiuddin@nvidia.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any kind,
 * whether express or implied; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
 * 02111-1307, USA
 */
#include <linux/extcon-provider.h>

#define MAX_STR_PRINT 50

#define bq_chg_err(bq, fmt, ...)			\
		dev_err(bq->dev, "Charging Fault: " fmt, ##__VA_ARGS__)

#define BQ2419X_INPUT_VINDPM_OFFSET	3880
#define BQ2419X_CHARGE_ICHG_OFFSET	512
#define BQ2419X_PRE_CHG_IPRECHG_OFFSET	128
#define BQ2419X_PRE_CHG_TERM_OFFSET	128
#define BQ2419X_CHARGE_VOLTAGE_OFFSET	3504
#define BQ2419x_OTG_ENABLE_TIME		msecs_to_jiffies(30000)
#define BQ2419X_PC_USB_LP0_THRESHOLD	95
#define BQ2419x_TEMP_H_CHG_DISABLE	50
#define BQ2419x_TEMP_L_CHG_DISABLE	0

/* Redefimition for compiler */
struct extcon_dev {
	/* Optional user initializing data */
	const char *name;
	const unsigned int *supported_cable;
	const u32 *mutually_exclusive;

	/* Internal data. Please do not set. */
	struct device dev;
	struct raw_notifier_head nh_all;
	struct raw_notifier_head *nh;
	struct list_head entry;
	int max_supported;
	spinlock_t lock;	/* could be called by irq handler */
	u32 state;
	u32 last_state_in_suspend;
	bool uevent_in_suspend;
	bool is_suspend;
	struct notifier_block pm_nb;

	/* /sys/class/extcon/.../cable.n/... */
	struct device_type extcon_dev_type;
	struct extcon_cable *cables;

	/* /sys/class/extcon/.../mutually_exclusive/... */
	struct attribute_group attr_g_muex;
	struct attribute **attrs_muex;
	struct device_attribute *d_attrs_muex;
};
