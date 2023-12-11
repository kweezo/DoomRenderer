
#ifndef WINDOWS_WINDOW_H
#define WINDOWS_WINDOW_H
#include <windows.h>
#include <stdbool.h>
uint8_t *scrnpxls;
bool CreateAppWindow(int width, int height, bool fullscreen);
void DrawPixels(const COLORREF *pixels, int width, int height);
void DestroyWindow();
void UpdateWindow();
#endif