# Multi-stage dockerfile to build a C++ CMake raylib-based app
FROM ubuntu:24.04 AS builder

ARG DEBIAN_FRONTEND=noninteractive
RUN apt-get update && apt-get install -y --no-install-recommends \
    ca-certificates \ 
    build-essential cmake git pkg-config \
    libgl1-mesa-dev libx11-dev libxcursor-dev libxrandr-dev libxi-dev libxinerama-dev \
    libxkbcommon-dev libudev-dev libasound2-dev libpulse-dev libdrm-dev \
    libjpeg-dev libfreetype6-dev libopenal-dev libsndfile1-dev \
    && update-ca-certificates \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /workspace

# Copy only CMakeLists.txt and dependencies first for better caching
COPY CMakeLists.txt ./
COPY external ./external
COPY include ./include
COPY src ./src
COPY assets ./assets

# Pre-fetch and build dependencies
RUN mkdir -p build && cd build && \
    cmake .. -DCMAKE_BUILD_TYPE=Release -DFETCHCONTENT_FULLY_DISCONNECTED=OFF && \
    cmake --build . --config Release -j$(nproc) --target imgui_lib rlimgui || true

# Now copy source code
COPY src ./src

# Final build
RUN cd build && \
    cmake .. -DCMAKE_BUILD_TYPE=Release && \
    cmake --build . --config Release -j$(nproc)

# -----------------------------

FROM ubuntu:24.04

RUN apt-get update && apt-get install -y --no-install-recommends \
    ca-certificates \
    libgl1-mesa-dri libx11-6 libxrandr2 libxinerama1 libxcursor1 libxi6 \
    libudev1 libopenal1 libsndfile1 libpulse0 \
    && update-ca-certificates \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY --from=builder /workspace/build/PlanetSim ./PlanetSim

CMD ["./PlanetSim"]