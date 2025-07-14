#!/bin/bash
set -e

# Navigate to the project root
cd "$(dirname "$0")"

# Create build directory if it doesn't exist
mkdir -p opt
cd opt

# Run cmake and make
cmake ../engine
make -j$(nproc)

cp my3DEngine ../