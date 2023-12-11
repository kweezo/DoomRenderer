#!/bin/bash

gcc -o bin/doom src/**/*.c -lX11 -lm
./bin/doom