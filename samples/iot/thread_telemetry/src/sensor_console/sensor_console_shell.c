/*
 * Copyright (c) 2026 TiaC Systems
 * SPDX-License-Identifier: Apache-2.0
 *
 * The console log has nothing to command, only something to report.
 * Compiled only when CONFIG_TELEMETRY_SHELL is set.
 */

#include <zephyr/shell/shell.h>

#include "app_status.h"

static void sensor_console_status(const struct shell *sh)
{
	APP_STATUS_PRINT(sh, "Log every", "%d s", CONFIG_TELEMETRY_SENSOR_CONSOLE_INTERVAL_S);
}

APP_STATUS_ENTRY_DEFINE(c_sensor_console, sensor_console_status);
