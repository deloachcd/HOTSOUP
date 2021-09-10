#!/bin/sh -e

# Checkout all our submodule dependencies
git submodule init
git submodule update

# Generate gl3w.c and gl3w.h
cd deps/gl3w
if ! test -e include/GL/gl3w.h || ! test -e src/gl3w.c; then
	python3 gl3w_gen.py
fi
cd ..
