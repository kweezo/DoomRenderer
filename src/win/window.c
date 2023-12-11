
#include "window.h"
#include "stdint.h"

LPCWSTR szWindowClass = L"Win32WindowClass";
HWND window;
BITMAPINFO bmi = {0};
uint8_t *scrnpxls;

uint16_t ww;

bool CreateAppWindow(uint32_t width, uint32_t height, bool fullscreen)
{
    WNDCLASS wc = {0};
    wc.lpfnWndProc = DefWindowProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = szWindowClass;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);

    RegisterClass(&wc);

    DWORD style = WS_OVERLAPPEDWINDOW;
    DWORD exStyle = 0;

    ww = width;
    if (fullscreen)
    {
        style = WS_POPUP;
        exStyle = WS_EX_TOPMOST;
    }

    window = CreateWindowEx(exStyle, szWindowClass, L"Win32 Window", style,
                            0, 0, width, height, NULL, NULL, GetModuleHandle(NULL), NULL);

    if (!window)
    {
        MessageBox(NULL, L"Call to CreateWindow failed!", L"Win32 Window", MB_ICONERROR);
        return false;
    }

    ShowWindow(window, SW_SHOWNORMAL);
    UpdateWindow(window);

    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = width;
    bmi.bmiHeader.biHeight = -height;
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 32;
    bmi.bmiHeader.biCompression = BI_RGB;

    return true;
}

void DestroyWindow()
{
    DestroyWindow(window);
}

void UpdateWindow()
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

// int main()
// {
//     if (CreateWindow(640, 480, false))
//     {
//         // Your application logic here

//         // For example, draw some pixels
//         COLORREF pixels[640 * 480]; // Assuming a buffer for pixel data
//         DrawPixels(pixels, 640, 480);

//         // Update and process messages
//         UpdateWindow();
//         MSG msg = {0};
//         while (GetMessage(&msg, NULL, 0, 0) > 0)
//         {
//             TranslateMessage(&msg);
//             DispatchMessage(&msg);
//         }

//         // Cleanup
//         DestroyWindow();
//     }

//     return 0;
// }