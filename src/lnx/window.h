#ifndef LINUX_WINDOW_H
#define LINUX_WINDOW_H

#include <X11/Xlib.h>

#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

bool CreateWindow(u_int16_t windowWidth, u_int16_t windowHeight, bool fullscreen);

void UpdateWindow();
void DestroyWindow();

extern char* scrnpxls;

#endif