//check if program is running in windows or linux and include the appropriate header
#ifdef _WIN32
#include "../win/window.h"
#else
#include "../lnx/window.h"
#endif

#include "../utils/loadimg.h"

int main(){
    CreateWindow(3860, 2160, false);

    ImageData img = LoadBMP("res/test1.bmp");
    


    while(true){
    for(int x = 0; x < img.w; x++){
        for(int y = 0; y < img.h; y++){
            scrnpxls[(y*ww+x)*4 + 0 ] = img.dat[(y*img.w+x)*4 + 0 ];
            scrnpxls[(y*ww+x)*4 + 1 ] = img.dat[(y*img.w+x)*4 + 1 ];
            scrnpxls[(y*ww+x)*4 + 2 ] = img.dat[(y*img.w+x)*4 + 2 ];
            scrnpxls[(y*ww+x)*4 + 3 ] = img.dat[(y*img.w+x)*4 + 3 ];
        }
    }
        UpdateWindow();
    }

    DestroyWindow();
}