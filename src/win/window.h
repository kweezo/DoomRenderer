#ifndef WINDOWS_WINDOW_H
#define WINDOWS_WINDOW_H

#include <windows.h>
#include <stdbool.h>
#include <stdint.h>

extern uint8_t *scrnpxls;
extern uint16_t ww;

bool CreateAppWindow(uint32_t width, uint32_t height, bool fullscreen);
void DrawPixels(uint32_t width, uint32_t height);
void DestroyAppWindow();
void UpdateAppWindow();

#endif