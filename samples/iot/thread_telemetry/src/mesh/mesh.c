/*
 * Copyright (c) 2026 TiaC Systems
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/init.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

#include <openthread.h>
#include <openthread/thread.h>

#include "mesh.h"

LOG_MODULE_REGISTER(mesh, CONFIG_TELEMETRY_MESH_LOG_LEVEL);

static otDeviceRole mesh_role(void)
{
	otInstance *ot = openthread_get_default_instance();
	otDeviceRole role;

	if (ot == NULL) {
		return OT_DEVICE_ROLE_DISABLED;
	}

	/*
	 * Recursive on purpose: the state changed callback below already runs
	 * with this mutex held, and a Zephyr k_mutex re-locks for its owner.
	 */
	openthread_mutex_lock();
	role = otThreadGetDeviceRole(ot);
	openthread_mutex_unlock();

	return role;
}

bool mesh_is_attached(void)
{
	switch (mesh_role()) {
	case OT_DEVICE_ROLE_CHILD:
	case OT_DEVICE_ROLE_ROUTER:
	case OT_DEVICE_ROLE_LEADER:
		return true;
	default:
		return false;
	}
}

const char *mesh_role_name(void)
{
	return otThreadDeviceRoleToString(mesh_role());
}

static void on_state_changed(otChangedFlags flags, void *context)
{
	ARG_UNUSED(context);

	if ((flags & OT_CHANGED_THREAD_ROLE) == 0) {
		return;
	}

	LOG_INF("Thread role is now %s", mesh_role_name());
}

static struct openthread_state_changed_callback state_callback = {
	.otCallback = on_state_changed,
};

static int mesh_init(void)
{
	int ret;

	/*
	 * The OpenThread instance is created by the L2, at POST_KERNEL, so it
	 * exists by the time any APPLICATION level hook runs.
	 */
	ret = openthread_state_changed_callback_register(&state_callback);
	if (ret) {
		LOG_ERR("Failed to register the OpenThread state callback: %d", ret);
		return ret;
	}

	return 0;
}

SYS_INIT(mesh_init, APPLICATION, CONFIG_TELEMETRY_MESH_INIT_PRIORITY);
