#!/bin/sh

set -xe

CFLAGS="-Wall -Wextra"

clang $CFLAGS -o prog main.c
