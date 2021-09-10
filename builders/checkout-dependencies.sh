#!/bin/sh -e

# Checkout all our submodule dependencies
git submodule init
git submodule update

# Generate gl3w.c and gl3w.h
cd deps/gl3w
python3 gl3w_gen.py
cd ..
