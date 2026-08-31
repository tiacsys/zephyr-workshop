FROM mcr.microsoft.com/devcontainers/base:debian-13

# Create zephyrproject directory
RUN mkdir -p /zephyrproject \
    && chown -R vscode:vscode /zephyrproject

# Install west and basic build dependencies
RUN apt-get update \
    && apt-get install -y --no-install-recommends \
    ccache \
    clangd \
    cmake \
    device-tree-compiler \
    file \
    g++-multilib \
    gcc \
    gcc-multilib \
    gperf \
    libmagic1 \
    libsdl2-dev \
    make \
    minicom \
    ninja-build \
    picocom \
    python3-dev \
    python3-jsonschema \
    python3-pip \
    python3-tk \
    python3-venv \
    ripgrep \
    screen \
    tio \
    wget \
    && apt-get clean -y \
    && rm -rf /var/lib/apt/lists/*

# Install west
RUN pip3 install --break-system-packages west
