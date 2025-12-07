#!/usr/bin/env bash

set -x

if [[ $# -eq 0 ]]; then
    echo 'provide arg: $1'
    exit 1
fi

build/"$1"
