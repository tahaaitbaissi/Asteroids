#! /usr/bin/env bash

set -ex

gcc src/*.c -o main -lraylib -lm
