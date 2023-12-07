#!/bin/bash

gcc src/**/*.c -o bin/doom.a -lX11
./bin/doom.a
