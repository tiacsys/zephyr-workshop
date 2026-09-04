/*
 * Copyright (c) 2026 TiaC Systems
 * SPDX-License-Identifier: Apache-2.0
 *
 * The mesh state has nothing to command -- the OpenThread shell already
 * covers that -- only something to report. Compiled only when
 * CONFIG_TELEMETRY_SHELL is set.
 */

#include <zephyr/shell/shell.h>

#include "app_status.h"
#include "mesh.h"

static void mesh_status(const struct shell *sh)
{
	APP_STATUS_PRINT(sh, "Mesh role", "%s", mesh_role_name());
}

APP_STATUS_ENTRY_DEFINE(e_mesh, mesh_status);
