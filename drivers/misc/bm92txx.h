/*
 * bm92txx.h
 *
 * Copyright (c) 2020-2022 CTCaer <ctcaer@gmail.com>
 *
 * Authors:
 *     CTCaer <ctcaer@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <linux/extcon-provider.h>

/* Registers */
#define ALERT_STATUS_REG    0x02
#define STATUS1_REG         0x03
#define STATUS2_REG         0x04
#define COMMAND_REG         0x05 /* Send special command */
#define CONFIG1_REG         0x06 /* Controller Configuration 1 */
#define DEV_CAPS_REG        0x07
#define READ_PDOS_SRC_REG   0x08 /* Data size: 28 */
#define CONFIG2_REG         0x17 /* Controller Configuration 2 */
#define DP_STATUS_REG       0x18
#define DP_ALERT_EN_REG     0x19
#define VENDOR_CONFIG_REG   0x1A /* Vendor Configuration 1 */
#define UNKOWN_1C_REG       0x1C /* HOS reads it. 2 bytes. DP sth */
#define UNKOWN_1D_REG       0x1D /* HOS reads it. 2 bytes. DP sth */
#define AUTO_NGT_FIXED_REG  0x20 /* Data size: 4 */
#define AUTO_NGT_BATT_REG   0x23 /* Data size: 4 */
#define SYS_CONFIG1_REG     0x26 /* System Configuration 1 */
#define SYS_CONFIG2_REG     0x27 /* System Configuration 2 */
#define CURRENT_PDO_REG     0x28 /* Data size: 4 */
#define CURRENT_RDO_REG     0x2B /* Data size: 4 */
#define ALERT_ENABLE_REG    0x2E
#define SYS_CONFIG3_REG     0x2F /* System Configuration 3 */
#define SET_RDO_REG         0x30 /* Data size: 4 */
#define PDOS_SNK_CONS_REG   0x33 /* PDO Sink Consumer. Data size: 16 */
#define PDOS_SRC_PROV_REG   0x3C /* PDO Source Provider. Data size: 28 */
#define FW_TYPE_REG         0x4B
#define FW_REVISION_REG     0x4C
#define MAN_ID_REG          0x4D
#define DEV_ID_REG          0x4E
#define REV_ID_REG          0x4F
#define INCOMING_VDM_REG    0x50 /* Max data size: 28 */
#define OUTGOING_VDM_REG    0x60 /* Max data size: 28 */

/* ALERT_STATUS_REG */
#define ALERT_SNK_FAULT     BIT(0)
#define ALERT_SRC_FAULT     BIT(1)
#define ALERT_CMD_DONE      BIT(2)
#define ALERT_PLUGPULL      BIT(3)
#define ALERT_DP_EVENT      BIT(6)
#define ALERT_DR_SWAP       BIT(10)
#define ALERT_VDM_RECEIVED  BIT(11)
#define ALERT_CONTRACT      BIT(12)
#define ALERT_SRC_PLUGIN    BIT(13)
#define ALERT_PDO           BIT(14)

/* STATUS1_REG */
#define STATUS1_FAULT_MASK    (3 << 0)
#define STATUS1_SPDSRC2       BIT(3) /* VBUS2 enabled */
#define STATUS1_LASTCMD_SHIFT 4
#define STATUS1_LASTCMD_MASK  (7 << STATUS1_LASTCMD_SHIFT)
#define STATUS1_INSERT        BIT(7)  /* Cable inserted */
#define STATUS1_DR_SHIFT      8
#define STATUS1_DR_MASK       (3 << STATUS1_DR_SHIFT)
#define STATUS1_VSAFE         BIT(10) /* 0: No power, 1: VSAFE 5V or PDO */
#define STATUS1_CSIDE         BIT(11) /* Type-C Plug Side. 0: CC1 Side Valid, 1: CC2 Side Valid */
#define STATUS1_SRC_MODE      BIT(12) /* 0: Sink Mode, 1: Source mode (OTG) */
#define STATUS1_CMD_BUSY      BIT(13) /* Command in progress */
#define STATUS1_SPDSNK        BIT(14) /* Sink mode */
#define STATUS1_SPDSRC1       BIT(15) /* VBUS enabled */

#define LASTCMD_COMPLETE   0
#define LASTCMD_ABORTED    2
#define LASTCMD_INVALID    4
#define LASTCMD_REJECTED   6
#define LASTCMD_TERMINATED 7

#define DATA_ROLE_NONE  0
#define DATA_ROLE_UFP   1
#define DATA_ROLE_DFP   2
#define DATA_ROLE_ACC   3

/* STATUS2_REG */
#define STATUS2_PDOI_MASK    BIT(3)
#define STATUS2_VCONN_ON     BIT(9)
#define STATUS2_ACC_SHIFT    10
#define STATUS2_ACC_MASK     (3 << STATUS2_ACC_SHIFT) /* Accesory mode */
#define STATUS2_EM_CABLE     BIT(12) /* Electronically marked cable. Safe for 1.3A */
#define STATUS2_OTG_INSERT   BIT(13)

#define PDOI_SRC_OR_NO  0
#define PDOI_SNK        1

#define ACC_DISABLED    0
#define ACC_AUDIO       1
#define ACC_DEBUG       2
#define ACC_VCONN       3

/* DP_STATUS_REG */
#define DP_STATUS_PIN_CFG_DONE BIT(1) /* Pin configured or sth */
#define DP_STATUS_SIGNAL_ON    BIT(7) /* TV/Monitor connected. link channel enabled or hpd channel or something */
#define DP_STATUS_INSERT       BIT(14)
#define DP_STATUS_DP_EN        BIT(15)

/* CONFIG1_REG */
#define CONFIG1_AUTO_DR_SWAP          BIT(1)
#define CONFIG1_SLEEP_REQUEST         BIT(4)
#define CONFIG1_AUTONGTSNK_VAR_EN     BIT(5)
#define CONFIG1_AUTONGTSNK_FIXED_EN   BIT(6)
#define CONFIG1_AUTONGTSNK_EN         BIT(7)
#define CONFIG1_AUTONGTSNK_BATT_EN    BIT(8)
#define CONFIG1_VINOUT_DELAY_EN       BIT(9) /* VIN/VOUT turn on delay enable */
#define CONFIG1_VINOUT_TIME_ON_SHIFT  10 /* VIN/VOUT turn on delay */
#define CONFIG1_VINOUT_TIME_ON_MASK   (3 << CONFIG1_VINOUT_TIME_ON_SHIFT)
#define CONFIG1_SPDSRC_SHIFT          14
#define CONFIG1_SPDSRC_MASK           (3 << CONFIG1_SPDSRC_SHIFT)

#define VINOUT_TIME_ON_1MS    0
#define VINOUT_TIME_ON_5MS    1
#define VINOUT_TIME_ON_10MS   2
#define VINOUT_TIME_ON_20MS   3

#define SPDSRC12_ON           0 /* SPDSRC 1/2 on */
#define SPDSRC2_ON            1
#define SPDSRC1_ON            2
#define SPDSRC12_OFF          3 /* SPDSRC 1/2 off */

/* CONFIG2_REG */
#define CONFIG2_PR_SWAP_MASK      (3 << 0)
#define CONFIG2_DR_SWAP_SHIFT     2
#define CONFIG2_DR_SWAP_MASK      (3 << CONFIG2_DR_SWAP_SHIFT)
#define CONFIG2_VSRC_SWAP         BIT(4) /* VCONN source swap. 0: Reject, 1: Accept */
#define CONFIG2_NO_USB_SUSPEND    BIT(5)
#define CONFIG2_EXT_POWERED       BIT(7)
#define CONFIG2_TYPEC_AMP_SHIFT   8
#define CONFIG2_TYPEC_AMP_MASK    (3 << CONFIG2_TYPEC_AMP_SHIFT)

#define PR_SWAP_ALWAYS_REJECT         0
#define PR_SWAP_ACCEPT_SNK_REJECT_SRC 1 /* Accept when power sink */
#define PR_SWAP_ACCEPT_SRC_REJECT_SNK 2 /* Accept when power source */
#define PR_SWAP_ALWAYS_ACCEPT         3

#define DR_SWAP_ALWAYS_REJECT         0
#define DR_SWAP_ACCEPT_UFP_REJECT_DFP 1 /* Accept when device */
#define DR_SWAP_ACCEPT_DFP_REJECT_UFP 2 /* Accept when host */
#define DR_SWAP_ALWAYS_ACCEPT         3

#define TYPEC_AMP_0_5A_5V   0
#define TYPEC_AMP_1_5A_5V   1
#define TYPEC_AMP_3_0A_5V   2

/* SYS_CONFIG1_REG */
#define SYS_CONFIG1_PLUG_MASK           (0xF << 0)
#define SYS_CONFIG1_USE_AUTONGT         BIT(6)
#define SYS_CONFIG1_PDO_SNK_CONS        BIT(8)
#define SYS_CONFIG1_PDO_SNK_CONS_SHIFT  9 /* Number of Sink PDOs */
#define SYS_CONFIG1_PDO_SNK_CONS_MASK   (7 << SYS_CONFIG1_PDO_SNK_CONS_SHIFT)
#define SYS_CONFIG1_PDO_SRC_PROV        BIT(12)
#define SYS_CONFIG1_DOUT4_SHIFT         13
#define SYS_CONFIG1_DOUT4_MASK          (3 << SYS_CONFIG1_DOUT4_SHIFT)
#define SYS_CONFIG1_WAKE_ON_INSERT      BIT(15)

#define PLUG_TYPE_C      9
#define PLUG_TYPE_C_3A   10
#define PLUG_TYPE_C_5A   11

#define DOUT4_PDO4       0
#define DOUT4_PDO5       1
#define DOUT4_PDO6       2
#define DOUT4_PDO7       3

/* SYS_CONFIG2_REG */
#define SYS_CONFIG2_NO_COMM_UFP          BIT(0) /* Force no USB comms Capable UFP */
#define SYS_CONFIG2_NO_COMM_DFP          BIT(1) /* Force no USB comms Capable DFP */
#define SYS_CONFIG2_NO_COMM_ON_NO_BATT   BIT(2) /* Force no USB comms on dead battery */
#define SYS_CONFIG2_AUTO_SPDSNK_EN       BIT(6) /* Enable SPDSNK without SYS_RDY */
#define SYS_CONFIG2_BST_EN               BIT(8)
#define SYS_CONFIG2_PDO_SRC_PROV_SHIFT   9 /* Number of Source provisioned PDOs */
#define SYS_CONFIG2_PDO_SRC_PROV_MASK    (7 << SYS_CONFIG2_PDO_SRC_PROV_SHIFT)

/* VENDOR_CONFIG_REG */
#define VENDOR_CONFIG_OCP_DISABLE  BIT(2) /* Disable Over-current protection */

/* DEV_CAPS_REG */
#define DEV_CAPS_ALERT_STS  BIT(0)
#define DEV_CAPS_ALERT_EN   BIT(1)
#define DEV_CAPS_VIN_EN     BIT(2)
#define DEV_CAPS_VOUT_EN0   BIT(3)
#define DEV_CAPS_SPDSRC2    BIT(4)
#define DEV_CAPS_SPDSRC1    BIT(5)
#define DEV_CAPS_SPRL       BIT(6)
#define DEV_CAPS_SPDSNK     BIT(7)
#define DEV_CAPS_OCP        BIT(8)  /* Over current protection */
#define DEV_CAPS_DP_SRC     BIT(9)  /* DisplayPort capable Source */
#define DEV_CAPS_DP_SNK     BIT(10) /* DisplayPort capable Sink */
#define DEV_CAPS_VOUT_EN1   BIT(11)

/* COMMAND_REG command list */
#define ABORT_LASTCMD_SENT_CMD    0x0101
#define PR_SWAP_CMD               0x0303 /* Power Role swap request */
#define PS_RDY_CMD                0x0505 /* Power supply ready */
#define GET_SRC_CAP_CMD           0x0606 /* Get Source capabilities */
#define SEND_RDO_CMD              0x0707
#define PD_HARD_RST_CMD           0x0808 /* Hard reset link */
#define STORE_SYSCFG_CMD          0x0909 /* Store system configuration */
#define UPDATE_PDO_SRC_PROV_CMD   0x0A0A /* Update PDO Source Provider */
#define GET_SNK_CAP_CMD           0x0B0B /* Get Sink capabilities */
#define STORE_CFG2_CMD            0x0C0C /* Store controller configuration 2 */
#define SYS_RESET_CMD             0x0D0D /* Full USB-PD IC reset */
#define RESET_PS_RDY_CMD          0x1010 /* Reset power supply ready */
#define SEND_VDM_CMD              0x1111 /* Send VMD SOP */
#define SEND_VDM_1_CMD            0x1212 /* Send VMD SOP'  EM cable near end */
#define SEND_VDM_2_CMD            0x1313 /* Send VMD SOP'' EM cable far end */
#define SEND_VDM_1_DBG_CMD        0x1414 /* Send VMD SOP'  debug */
#define SEND_VDM_2_DBG_CMD        0x1515 /* Send VMD SOP'' debug */
#define ACCEPT_VDM_CMD            0x1616 /* Receive VDM */
#define MODE_ENTERED_CMD          0x1717 /* Alt mode entered */
#define DR_SWAP_CMD               0x1818 /* Data Role swap request */
#define VC_SWAP_CMD               0x1919 /* VCONN swap request */
#define BIST_REQ_CARR_M2_CMD      0x2424 /* Request BIST carrier mode 2 */
#define BIST_TEST_DATA_CMD        0x2B2B /* Send BIST test data */
#define PD_SOFT_RST_CMD           0x2C2C /* Reset power and get new PDO/Contract */
#define BIST_CARR_M2_CONT_STR_CMD 0x2F2F /* Send BIST carrier mode 2 continuous string */
#define DP_ENTER_MODE_CMD         0x3131 /* Discover DP Alt mode */
#define DP_STOP_CMD               0x3232 /* Cancel DP Alt mode discovery */
#define START_HPD_CMD             0x3434 /* Start handling HPD */
#define DP_CFG_AND_START_HPD_CMD  0x3636 /* Configure and enter selected DP Alt mode and start handling HPD */
#define STOP_HPD_CMD              0x3939 /* Stop handling HPD */
#define STOP_HPD_EXIT_DP_CMD      0x3B3B /* Stop handling HPD and exit DP Alt mode */

/* General defines */
#define PDO_TYPE_FIXED  0
#define PDO_TYPE_BATT   1
#define PDO_TYPE_VAR    2

#define PDO_INFO_DR_DATA   (1 << 5)
#define PDO_INFO_USB_COMM  (1 << 6)
#define PDO_INFO_EXT_POWER (1 << 7)
#define PDO_INFO_HP_CAP    (1 << 8)
#define PDO_INFO_DR_POWER  (1 << 9)

/* VDM/VDO */
#define VDM_CMD_RESERVED    0x00
#define VDM_CMD_DISC_ID     0x01
#define VDM_CMD_DISC_SVID   0x02
#define VDM_CMD_DISC_MODE   0x03
#define VDM_CMD_ENTER_MODE  0x04
#define VDM_CMD_EXIT_MODE   0x05
#define VDM_CMD_ATTENTION   0x06
#define VDM_CMD_DP_STATUS   0x10
#define VDM_CMD_DP_CONFIG   0x11

#define VDM_ACK   0x40
#define VDM_NAK   0x80
#define VDM_BUSY  0xC0
#define VDM_UNSTRUCTURED   0x00
#define VDM_STRUCTURED     0x80

/* VDM Discover ID */
#define VDO_ID_TYPE_NONE        0
#define VDO_ID_TYPE_PD_HUB      1
#define VDO_ID_TYPE_PD_PERIPH   2
#define VDO_ID_TYPE_PASS_CBL    3
#define VDO_ID_TYPE_ACTI_CBL    4
#define VDO_ID_TYPE_ALTERNATE   5

/* VDM Discover Mode Caps [From device (UFP_U) to host (DFP_U)] */
#define VDO_DP_UFP_D       BIT(0) /* DisplayPort Sink */
#define VDO_DP_DFP_D       BIT(1) /* DisplayPort Source */
#define VDO_DP_SUPPORT     BIT(2)
#define VDO_DP_RECEPTACLE  BIT(6)

/* VDM DP Configuration [From host (DFP_U) to device (UFP_U)] */
#define VDO_DP_U_DFP_D     BIT(0) /* UFP_U as DisplayPort Source */
#define VDO_DP_U_UFP_D     BIT(1) /* UFP_U as DisplayPort Sink */
#define VDO_DP_SUPPORT     BIT(2)
#define VDO_DP_RECEPTACLE  BIT(6)

/* VDM Mode Caps and DP Configuration pins */
#define VDO_DP_PIN_A   BIT(0)
#define VDO_DP_PIN_B   BIT(1)
#define VDO_DP_PIN_C   BIT(2)
#define VDO_DP_PIN_D   BIT(3)
#define VDO_DP_PIN_E   BIT(4)
#define VDO_DP_PIN_F   BIT(5)

/* Known VID/SVID */
#define VID_NINTENDO      0x057E
#define PID_NIN_DOCK      0x2003
#define PID_NIN_CHARGER   0x2004

#define SVID_NINTENDO     VID_NINTENDO
#define SVID_DP           0xFF01

/* Nintendo dock VDM Commands */
#define VDM_NCMD_LED_CONTROL         0x01 /* Reply size 12 */
#define VDM_NCMD_DEVICE_STATE        0x16 /* Reply size 12 */
#define VDM_NCMD_DP_SIGNAL_DISABLE   0x1C /* Reply size 8 */
#define VDM_NCMD_HUB_RESET           0x1E /* Reply size 8 */
#define VDM_NCMD_HUB_CONTROL         0x20 /* Reply size 8 */

/* Nintendo dock VDM Request Type */
#define VDM_ND_READ    0
#define VDM_ND_WRITE   1

/* Nintendo dock VDM Reply Status */
#define VDM_ND_BUSY    1

/* Nintendo dock VDM Request/Reply Source */
#define VDM_ND_HOST    1
#define VDM_ND_DOCK    2

/* Nintendo dock VDM Message Type */
#define VDM_ND_REQST   0x00
#define VDM_ND_REPLY   0x40

/* Nintendo dock identifiers and limits */
#define DOCK_ID_VOLTAGE_MV  5000u
#define DOCK_ID_CURRENT_MA  500u
#define DOCK_INPUT_VOLTAGE_MV             15000u
#define DOCK_INPUT_CURRENT_LIMIT_MIN_MA   2600u
#define DOCK_INPUT_CURRENT_LIMIT_MAX_MA   3000u

/* Power limits */
#define PD_05V_CHARGING_CURRENT_LIMIT_MA   2000u
#define PD_09V_CHARGING_CURRENT_LIMIT_MA   2000u
#define PD_12V_CHARGING_CURRENT_LIMIT_MA   1500u
#define PD_15V_CHARGING_CURRENT_LIMIT_MA   1200u

#define NON_PD_POWER_RESERVE_UA   2500000u
#define PD_POWER_RESERVE_UA       4500000u

#define PD_INPUT_CURRENT_LIMIT_MIN_MA   0u
#define PD_INPUT_CURRENT_LIMIT_MAX_MA   3000u
#define PD_INPUT_VOLTAGE_LIMIT_MAX_MV   17000u

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
