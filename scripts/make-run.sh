#!/bin/sh -e

if test -z $1; then
    echo "USAGE: $(basename "$0") <make_script>"
    exit 1
else
    MAKE_SCRIPT=$1
fi

TARGET=entrypoint
$MAKE_SCRIPT

# If we're already running TARGET, kill it
RUNNING_TARGET=$(ps -ax |\
                     grep $TARGET |\
                     grep -v grep |\
                     head -n 1 |\
                     awk '{ print $1 }')
if ! test -z $RUNNING_TARGET; then
    kill $RUNNING_TARGET
fi

./$TARGET
