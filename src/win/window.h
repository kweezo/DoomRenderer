#ifndef WINDOWS_WINDOW_H
#define WINDOWS_WINDOW_H
#include <windows.h>
HWND CreateAppWindow(HINSTANCE hInstance, LPCWSTR title, int width, int height);
void DestroyAppWindow(HWND hwnd);
void DrawPixels(HWND hwnd, const COLORREF* pixels, int width, int height);
#endif