#!/bin/sh

set -xe

CFLAGS="-Wall -Wextra"

clang $CFLAGS -o frequency_counter main.c
