#!/bin/bash

gcc -o bin/doom src/**/*.c -g -lX11 -lm
./bin/doom