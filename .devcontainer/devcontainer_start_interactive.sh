#!/bin/bash

# Start the devcontainer in interactive mode
# Usage: ./.devcontainer/devcontainer_start_interactive.sh
#
# After entering the container, complete setup with:
#   bash zephyr-workshop/.devcontainer/post-create.sh

set -e

# Build image if needed
docker build -t zephyr-workshop-dev .devcontainer/

# Run container interactively with workspace mounted at the west root layout
docker run -it --rm \
    -v "$(pwd):/zephyrproject/zephyr-workshop" \
    -w /zephyrproject \
    zephyr-workshop-dev \
    bash
