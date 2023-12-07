#include "window.h"

Display* dspl = NULL;
Window win;
GC gc;
XEvent event;

char* scrnpxls;

u_int16_t ww, wh;

bool CreateWindow(u_int16_t windowWidth, u_int16_t windowHeight, bool fullscreen){
    ww = windowWidth;
    wh = windowHeight;

    dspl = XOpenDisplay(NULL);
    win = XCreateSimpleWindow(dspl, DefaultRootWindow(dspl), 10, 10, ww, wh, 1,
    BlackPixel(dspl, DefaultScreen(dspl)), WhitePixel(dspl, DefaultScreen(dspl)));

    gc = XCreateGC(dspl, win, 0, NULL);

    XStoreName(dspl, win, "DOOM");

//    XSelectInput(dspl, win, 
//        ExposureMask | KeyPressMask);
    XSelectInput(dspl, win, ExposureMask);
    XMapWindow(dspl, win);

    scrnpxls = malloc(sizeof(u_int32_t) * ww*wh);
    for(u_int32_t i = 0; i < ww*wh; i++){
        scrnpxls[i] = rand() % 256;
    }


}

void UpdateWindow(){
    if(XPending(dspl) > 0){

    
        printf("fag\n");;
    XNextEvent(dspl, &event);

    if(event.type == Expose){
        Pixmap img = XCreateBitmapFromData(dspl, win, scrnpxls, ww, wh); 
        XCopyPlane(dspl, img, win, gc, 0, 0, ww, wh, 0, 0, 1);

        XFlush(dspl);
    }
    }
    else{
    usleep(10000);

    }
        
   
}

void DestroyWindow(){
    free(scrnpxls);
}