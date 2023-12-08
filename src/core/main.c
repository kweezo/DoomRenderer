//check if program is running in windows or linux and include the appropriate header
#ifdef _WIN32
#include "../win/window.h"
#else
#include "../lnx/window.h"
#endif

int main(){
    CreateWindow(3860, 2160, false);

    while(true){

        UpdateWindow();
    }

    DestroyWindow();
}