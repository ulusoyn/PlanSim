FROM ubuntu:24.04

ARG DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y --no-install-recommends \
    ca-certificates \
    build-essential \
    cmake \
    git \
    pkg-config \
    gdb \
    valgrind \
    clang \
    clang-format \
    clang-tidy \
    libgl1-mesa-dev \
    libx11-dev \
    libxcursor-dev \
    libxrandr-dev \
    libxi-dev \
    libxinerama-dev \
    libxkbcommon-dev \
    libudev-dev \
    libasound2-dev \
    libpulse-dev \
    libdrm-dev \
    libjpeg-dev \
    libfreetype6-dev \
    libopenal-dev \
    libsndfile1-dev \
    wget \
    curl \
    vim \
    nano \
    && update-ca-certificates \
    && rm -rf /var/lib/apt/lists/*

# vscode kullanıcısı oluştur
RUN useradd -m -s /bin/bash vscode \
    && echo "vscode ALL=(ALL) NOPASSWD:ALL" >> /etc/sudoers

# workspace klasörünü oluştur ve vscode'a ver
RUN mkdir -p /workspace && chown -R vscode:vscode /workspace

WORKDIR /workspace
USER vscode