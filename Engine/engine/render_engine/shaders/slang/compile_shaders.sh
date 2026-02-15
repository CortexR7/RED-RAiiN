#!/usr/bin/env bash

SLANGC="/home/cex7/devel_tools/bin/slangc"

VERTEX_SHADER="vertex_shader.slang"
FRAGMENT_SHADER="fragment_shader.slang"

OUTPUT_DIR="../../../../../SPIR-V"
VERTEX_OUT="$OUTPUT_DIR/vert.spv"
FRAGMENT_OUT="$OUTPUT_DIR/frag.spv"

# Ensure output directory exists
mkdir -p "$OUTPUT_DIR"

set -e

echo "Compiling vertex shader..."
"$SLANGC" "$VERTEX_SHADER" \
    -profile vs_6_0 \
    -entry main \
    -target spirv \
    -emit-spirv-directly \
    -o "$VERTEX_OUT"

echo "Vertex shader OK: $VERTEX_OUT"

echo "Compiling fragment shader..."
"$SLANGC" "$FRAGMENT_SHADER" \
    -profile ps_6_0 \
    -entry main \
    -target spirv \
    -emit-spirv-directly \
    -o "$FRAGMENT_OUT"

echo "Fragment shader OK: $FRAGMENT_OUT"

echo "All shaders compiled successfully."
