//#include "window.h"
//
//LPCWSTR szWindowClass = L"Win32WindowClass";
//
//HWND CreateAppWindow(HINSTANCE hInstance, LPCWSTR title, int width, int height) {
//    // Register the window class
//    WNDCLASS wc = { 0 };
//    wc.lpfnWndProc = DefWindowProc;
//    wc.hInstance = hInstance;
//    wc.lpszClassName = szWindowClass;
//    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
//
//    RegisterClass(&wc);
//
//    // Create the window
//    HWND hwnd = CreateWindow(szWindowClass, title, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, width, height, NULL, NULL, hInstance, NULL);
//
//    if (!hwnd) {
//        MessageBox(NULL, "Call to CreateWindow failed!", "Win32 Window", MB_ICONERROR);
//        return NULL;
//    }
//
//    // Show and update the window
//    ShowWindow(hwnd, SW_SHOWNORMAL);
//    UpdateWindow(hwnd);
//
//    return hwnd;
//}
//
//void DestroyAppWindow(HWND hwnd) {
//    DestroyWindow(hwnd);
//}
//
//void DrawPixels(HWND hwnd, const COLORREF* pixels, int width, int height) {
//    HDC hdc = GetDC(hwnd);
//
//    BITMAPINFO bmi = { 0 };
//    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
//    bmi.bmiHeader.biWidth = width;
//    bmi.bmiHeader.biHeight = -height; // negative height to indicate a top-down DIB
//    bmi.bmiHeader.biPlanes = 1;
//    bmi.bmiHeader.biBitCount = 32; // assuming 32 bits per pixel (8 bits for each color channel + 8-bit alpha)
//    bmi.bmiHeader.biCompression = BI_RGB;
//
//    SetDIBitsToDevice(hdc, 0, 0, width, height, 0, 0, 0, height, pixels, &bmi, DIB_RGB_COLORS);
//
//    ReleaseDC(hwnd, hdc);
//}