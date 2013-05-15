#
# Makefile for the sensor drivers.
#

# Each configuration option enables a list of files.
obj-$(CONFIG_SENSORS_SSP)		+= ssp_dev.o ssp_i2c.o ssp_data.o ssp_sysfs.o\
						ssp_input.o ssp_firmware.o ssp_debug.o

obj-$(CONFIG_SENSORS_SYSFS)		+= sensors_core.o

obj-$(CONFIG_SENSORS_SSP_K330)	+= accel_k330.o gyro_k330.o

obj-$(CONFIG_SENSORS_SSP_CM36651)	+= light_cm36651.o prox_cm36651.o

obj-$(CONFIG_SENSORS_SSP_CM3323)	+= light_cm3323.o

obj-$(CONFIG_SENSORS_SSP_MAX88920)	+= prox_max88920.o gesture_max88920.o

obj-$(CONFIG_SENSORS_SSP_AK8963C)	+= ssp_ak8963c.o magnetic_ak8963c.o

obj-$(CONFIG_SENSORS_SSP_AK8963C_DOEPLUS)	+= ssp_ak8963c_doeplus.o magnetic_ak8963c.o

obj-$(CONFIG_SENSORS_SSP_BMP182)	+= pressure_bmp182.o

obj-$(CONFIG_SENSORS_SSP_SHTC1)		+= temphumidity_shtc1.o

obj-$(CONFIG_SENSORS_SSP_AT32UC3L0128)	+= mcu_at32uc3l0128.o

obj-$(CONFIG_SENSORS_SSP_ATUC128L5HAR)	+= mcu_atuc128l5har.o

obj-$(CONFIG_SENSORS_SSP_SENSORHUB)	+= ssp_sensorhub.o

obj-$(CONFIG_SENSORS_SSP_C12SD)		+= ssp_c12sd.o

obj-$(CONFIG_SENSORS_SSP_ATSN01P)	+= grip/atsn01p.o

obj-$(CONFIG_SENSORS_SSP_SX9500)	+= grip/sx9500.o
