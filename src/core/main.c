// check if program is running in Windows or Linux and include the appropriate header
#ifdef _WIN32
#include "../win/window.h"
#else
// Include the appropriate header for Linux
#endif

#include "../utils/loadimg.h"

// int main()
// {
//     if (CreateAppWindow(1920, 1080, false))
//     {
//         ImageData img = LoadBMP("res/test1.bmp");

//         while (true)
//         {
//             for (int x = 0; x < img.w; x++)
//             {
//                 for (int y = 0; y < img.h; y++)
//                 {
//                     scrnpxls[(y * ww + x) * 4 + 0] = img.dat[(y * img.w + x) * 4 + 0];
//                     scrnpxls[(y * ww + x) * 4 + 1] = img.dat[(y * img.w + x) * 4 + 1];
//                     scrnpxls[(y * ww + x) * 4 + 2] = img.dat[(y * img.w + x) * 4 + 2];
//                     scrnpxls[(y * ww + x) * 4 + 3] = img.dat[(y * img.w + x) * 4 + 3];
//                 }
//             }
//             UpdateAppWindow();
//         }

//         DestroyAppWindow();
//     }

//     return 0;
// }

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    if (CreateAppWindow(1920, 1080, false))
    {
        ImageData img = LoadBMP("res/test1.bmp");

        MSG msg = {0};
        while (GetMessage(&msg, NULL, 0, 0) > 0)
        {
            for (int x = 0; x < img.w; x++)
            {
                for (int y = 0; y < img.h; y++)
                {
                    scrnpxls[(y * ww + x) * 4 + 0] = img.dat[(y * img.w + x) * 4 + 0];
                    scrnpxls[(y * ww + x) * 4 + 1] = img.dat[(y * img.w + x) * 4 + 1];
                    scrnpxls[(y * ww + x) * 4 + 2] = img.dat[(y * img.w + x) * 4 + 2];
                    scrnpxls[(y * ww + x) * 4 + 3] = img.dat[(y * img.w + x) * 4 + 3];
                }
            }
            UpdateAppWindow();
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        // Cleanup
        DestroyAppWindow();
    }

    return 0;
}