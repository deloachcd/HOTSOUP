#!/bin/sh -e

# create a debug build with a compilation database
# that LSP can use
cmake -H. -BDebug \
      -DCMAKE_BUILD_TYPE=Debug \
      -DCMAKE_EXPORT_COMPILE_COMMANDS=YES

if ! test -e compile_commands.json; then
    ln -s Debug/compile_commands.json .
fi

# make it
cd Debug
make
cd ..

if ! test -e entrypoint; then
    ln -s Debug/entrypoint .
fi
