/*
 * Copyright (c) 2026 TiaC Systems
 * SPDX-License-Identifier: Apache-2.0
 *
 * The whole node in the first stage of the workshop: read the sensor every
 * few seconds and print the reading. No display, no radio.
 */

#include <zephyr/init.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

#include "env_sensor.h"

LOG_MODULE_REGISTER(sensor_console, CONFIG_TELEMETRY_SENSOR_CONSOLE_LOG_LEVEL);

static void sensor_console_work_handler(struct k_work *work);
static K_WORK_DELAYABLE_DEFINE(sensor_console_work, sensor_console_work_handler);

static void sensor_console_work_handler(struct k_work *work)
{
	char temp_str[ENV_SENSOR_STR_SIZE];
	char hum_str[ENV_SENSOR_STR_SIZE];
	struct sensor_value temp;
	struct sensor_value hum;
	int ret;

	ARG_UNUSED(work);

	ret = env_sensor_read(&temp, &hum);
	if (ret == 0) {
		LOG_INF("%s C, %s %%rH", env_sensor_str(temp_str, sizeof(temp_str), &temp),
			env_sensor_str(hum_str, sizeof(hum_str), &hum));
	}

	k_work_reschedule(&sensor_console_work,
			  K_SECONDS(CONFIG_TELEMETRY_SENSOR_CONSOLE_INTERVAL_S));
}

static int sensor_console_init(void)
{
	LOG_INF("Logging a reading every %d s", CONFIG_TELEMETRY_SENSOR_CONSOLE_INTERVAL_S);

	k_work_reschedule(&sensor_console_work, K_NO_WAIT);

	return 0;
}

SYS_INIT(sensor_console_init, APPLICATION, CONFIG_TELEMETRY_SENSOR_CONSOLE_INIT_PRIORITY);
