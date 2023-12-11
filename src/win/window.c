#include <windows.h>
#include <stdint.h>
#include <stdbool.h>

LPCWSTR szWindowClass = L"Win32WindowClass"; // Change the type to LPCWSTR
HWND window;
BITMAPINFO bmi = {0};
uint8_t *scrnpxls = NULL;
uint16_t ww = 0;

bool CreateAppWindow(uint32_t width, uint32_t height, bool fullscreen);
void DestroyAppWindow();
void UpdateAppWindow();
void DrawPixels(uint32_t width, uint32_t height);
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

bool CreateAppWindow(uint32_t width, uint32_t height, bool fullscreen)
{
    // Register the window class
    WNDCLASSW wc = {0}; // Use WNDCLASSW for wide character version
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = szWindowClass;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);

    if (!RegisterClassW(&wc))
    {
        DWORD error = GetLastError();
        // wprintf(L"Failed to register window class with error code %lu\n", error);
        return false;
    }

    // Set window styles based on fullscreen mode
    DWORD style = fullscreen ? WS_POPUP : WS_OVERLAPPEDWINDOW;
    DWORD exStyle = fullscreen ? WS_EX_TOPMOST : 0;

    // Create the window
    window = CreateWindowExW(exStyle, szWindowClass, L"Win32 Window", style,
                             0, 0, width, height, NULL, NULL, GetModuleHandle(NULL), NULL);

    if (!window)
    {
        DWORD error = GetLastError();

        MessageBoxW(NULL, L"Call to CreateWindow failed!", L"Win32 Window", MB_ICONERROR);
        return false;
    }

    // Show and update the window
    ShowWindow(window, SW_SHOWNORMAL);
    UpdateWindow(window);

    // Configure the bitmap information
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = width;
    bmi.bmiHeader.biHeight = -height; // Negative height for top-down bitmap
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 32;
    bmi.bmiHeader.biCompression = BI_RGB;

    return true;
}

void DestroyAppWindow()
{
    DestroyWindow(window);
}

void UpdateAppWindow()
{
    UpdateWindow(window);
}

void DrawPixels(uint32_t width, uint32_t height)
{
    HDC hdc = GetDC(window);
    SetDIBitsToDevice(hdc, 0, 0, width, height, 0, 0, 0, height, scrnpxls, &bmi, DIB_RGB_COLORS);
    ReleaseDC(window, hdc);
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}