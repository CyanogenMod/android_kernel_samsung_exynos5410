#include <linux/kernel.h>
#include <linux/platform_device.h>
#include <linux/gpio.h>
#include <mach/gpio-exynos.h>
#include <plat/gpio-cfg.h>
#include <plat/devs.h>
#include <plat/ehci.h>
#include <linux/msm_charm.h>
#include <mach/mdm2.h>
#include "mdm_private.h"

#include <mach/dev.h>

static struct resource mdm_resources[] = {
	{
		.start	= GPIO_MDM2AP_ERR_FATAL,
		.end	= GPIO_MDM2AP_ERR_FATAL,
		.name	= "MDM2AP_ERRFATAL",
		.flags	= IORESOURCE_IO,
	},
	{
		.start	= GPIO_AP2MDM_ERR_FATAL,
		.end	= GPIO_AP2MDM_ERR_FATAL,
		.name	= "AP2MDM_ERRFATAL",
		.flags	= IORESOURCE_IO,
	},
	{
		.start	= GPIO_MDM2AP_STATUS,
		.end	= GPIO_MDM2AP_STATUS,
		.name	= "MDM2AP_STATUS",
		.flags	= IORESOURCE_IO,
	},
	{
		.start	= GPIO_AP2MDM_STATUS,
		.end	= GPIO_AP2MDM_STATUS,
		.name	= "AP2MDM_STATUS",
		.flags	= IORESOURCE_IO,
	},
	{
		.start	= GPIO_AP2MDM_PON_RESET_N,
		.end	= GPIO_AP2MDM_PON_RESET_N,
		.name	= "AP2MDM_SOFT_RESET",
		.flags	= IORESOURCE_IO,
	},
	{
		.start	= GPIO_AP2MDM_PMIC_RESET_N,
		.end	= GPIO_AP2MDM_PMIC_RESET_N,
		.name	= "AP2MDM_PMIC_PWR_EN",
		.flags	= IORESOURCE_IO,
	},
	{
		.start	= GPIO_AP2MDM_WAKEUP,
		.end	= GPIO_AP2MDM_WAKEUP,
		.name	= "AP2MDM_WAKEUP",
		.flags	= IORESOURCE_IO,
	},
};

#ifdef CONFIG_MDM_HSIC_PM
static struct resource mdm_pm_resource[] = {
	{
		.start	= GPIO_AP2MDM_HSIC_PORT_ACTIVE,
		.end	= GPIO_AP2MDM_HSIC_PORT_ACTIVE,
		.name	= "AP2MDM_HSIC_ACTIVE",
		.flags	= IORESOURCE_IO,
	},
	{
		.start	= GPIO_MDM2AP_HSIC_PWR_ACTIVE,
		.end	= GPIO_MDM2AP_HSIC_PWR_ACTIVE,
		.name	= "MDM2AP_DEVICE_PWR_ACTIVE",
		.flags	= IORESOURCE_IO,
	},
	{
		.start	= GPIO_MDM2AP_HSIC_RESUME_REQ,
		.end	= GPIO_MDM2AP_HSIC_RESUME_REQ,
		.name	= "MDM2AP_RESUME_REQ",
		.flags	= IORESOURCE_IO,
	},
};

static int exynos_frequency_lock(struct device *dev);
static int exynos_frequency_unlock(struct device *dev);

static struct mdm_hsic_pm_platform_data mdm_hsic_pm_pdata = {
	.freqlock = ATOMIC_INIT(0),
	.freq_lock = exynos_frequency_lock,
	.freq_unlock = exynos_frequency_unlock,
};

struct platform_device mdm_pm_device = {
	.name		= "mdm_hsic_pm0",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(mdm_pm_resource),
	.resource	= mdm_pm_resource,
};
#endif

static struct mdm_platform_data mdm_platform_data = {
	.mdm_version = "3.0",
	.ramdump_delay_ms = 3000,
	.early_power_on = 1,
	.sfr_query = 0,
	.vddmin_resource = NULL,
#ifdef CONFIG_USB_EHCI_S5P
	.peripheral_platform_device_ehci = &s5p_device_ehci,
#endif
#ifdef CONFIG_USB_OHCI_S5P
	.peripheral_platform_device_ohci = &s5p_device_ohci,
#endif
	.ramdump_timeout_ms = 120000,
};

static int exynos_frequency_lock(struct device *dev)
{
	return 0;
}

static int exynos_frequency_unlock(struct device *dev)
{
	return 0;
}

struct platform_device mdm_device = {
	.name		= "mdm2_modem",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(mdm_resources),
	.resource	= mdm_resources,
};

static int __init init_mdm_modem(void)
{
	int ret;
	pr_info("%s: registering modem dev, pm dev\n", __func__);

	mdm_pm_device.dev.platform_data = &mdm_hsic_pm_pdata;
	((struct mdm_hsic_pm_platform_data *)
	 mdm_pm_device.dev.platform_data)->dev =
		&mdm_pm_device.dev;
#ifdef CONFIG_MDM_HSIC_PM
	ret = platform_device_register(&mdm_pm_device);
	if (ret < 0) {
		pr_err("%s: fail to register mdm hsic pm dev(err:%d)\n",
								__func__, ret);
		return ret;
	}
#endif
	mdm_device.dev.platform_data = &mdm_platform_data;
	ret = platform_device_register(&mdm_device);
	if (ret < 0) {
		pr_err("%s: fail to register mdm modem dev(err:%d)\n",
								__func__, ret);
		return ret;
	}
	return 0;
}
module_init(init_mdm_modem);
