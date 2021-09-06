#!/bin/bash -e

# VERSION CONSTANTS
# Set these to desired versions before running!

# Note that special keyword 'latest' can be used for
# COMMIT_SHA variables, and does exactly what you'd
# expect it to
GLM_RELEASE=0.9.9.8
GLFW_RELEASE=3.3.3
GL3W_COMMIT_SHA=latest
STB_COMMIT_SHA=latest

if [[ ! -d deps ]]; then
    mkdir deps
fi

cd deps

# Pull down dependency archives from GitHub
if [[ ! -e "glm-${GLM_RELEASE}.zip" && ! -d glm ]]; then
    wget https://github.com/g-truc/glm/releases/download/${GLM_RELEASE}/glm-${GLM_RELEASE}.zip
fi
if [[ ! -d gl3w ]]; then
    git clone https://github.com/skaslev/gl3w
    if [[ ! $GL3W_COMMIT_SHA == "latest" ]]; then
        cd gl3w
        git checkout $GL3W_COMMIT_SHA
    fi
fi
if [[ ! -d glfw && ! -e "glfw-$GLFW_RELEASE.zip" ]]; then
    wget https://github.com/glfw/glfw/releases/download/$GLFW_RELEASE/glfw-$GLFW_RELEASE.zip
fi
if [[ ! -d stb ]]; then
	if [[ ! $STB_COMMIT_SHA == "latest" ]]; then
		REMOTE_PATH=$STB_COMMIT_SHA
	else
		REMOTE_PATH=master
	fi
	wget https://raw.githubusercontent.com/nothings/stb/$REMOTE_PATH/stb_image.h
fi

# Unpack zipped dependency archives
if [[ ! -d glfw && -e glfw-$GLFW_RELEASE.zip ]]; then
    unzip glfw-$GLFW_RELEASE.zip
    mv glfw-$GLFW_RELEASE glfw
    rm glfw-$GLFW_RELEASE.zip
fi
if [[ ! -d glm && -e glm-$GLM_RELEASE.zip ]]; then
    unzip glm-$GLM_RELEASE.zip
    rm glm-$GLM_RELEASE.zip
fi

# Use script to generate gl3w.c and gl3w.h
cd gl3w
python3 gl3w_gen.py
cd ..
