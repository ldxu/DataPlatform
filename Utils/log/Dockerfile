# Use a base image with Ubuntu (or you can use Debian)
FROM ubuntu:20.04

# Set environment variables to avoid interactive prompts during installation
ENV DEBIAN_FRONTEND=noninteractive

# Install dependencies: build-essential (for G++), CMake, and other necessary utilities
RUN apt-get update && \
    apt-get install -y \
    build-essential \
    valgrind \
    libc6-dbg \
    libpthread-stubs0-dev \
    gdb \
    cmake \
    g++-10 \
    wget \
    git \
    && rm -rf /var/lib/apt/lists/*

# Set g++-10 as the default g++ compiler
RUN update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-10 100

# Set up the working directory in the container
WORKDIR /workspace

# Optionally, copy your project files into the container
# COPY . /workspace

# Set the default command
CMD ["bash"]
