/*
 * Copyright (c) 2026 TiaC Systems
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef MESH_H
#define MESH_H

#include <stdbool.h>

/** @brief Whether the node is attached to the Thread mesh. */
bool mesh_is_attached(void);

/** @brief Current Thread device role: "disabled", "detached", "child", ... */
const char *mesh_role_name(void);

#endif /* MESH_H */
