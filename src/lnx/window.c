#include "window.h"

Display* dspl = NULL;
Window win;
GC gc;
XEvent event;

u_int8_t* scrnpxls;

u_int16_t ww, wh;

void OnResize();

bool CreateWindow(u_int16_t windowWidth, u_int16_t windowHeight, bool fullscreen){
    //implement fullscreen
    ww = windowWidth;
    wh = windowHeight;

    dspl = XOpenDisplay(NULL);
    win = XCreateSimpleWindow(dspl, DefaultRootWindow(dspl), 10, 10, ww, wh, 1,
    BlackPixel(dspl, DefaultScreen(dspl)), WhitePixel(dspl, DefaultScreen(dspl)));

    gc = XCreateGC(dspl, win, 0, NULL);

    XStoreName(dspl, win, "DOOM");

    XSelectInput(dspl, win, KeyPressMask | PointerMotionMask | StructureNotifyMask);
    XMapWindow(dspl, win);
    
    XResizeWindow(dspl, win, ww, wh);

    scrnpxls = malloc(ww*wh*4); // test pattern
    for(u_int16_t x = 0; x < ww; x++){
        for(int16_t y = 0; y < wh; y++){
            scrnpxls[(y*ww+x)*4 + 0] = x%255;
            scrnpxls[(y*ww+x)*4 + 1] = y%255;
            scrnpxls[(y*ww+x)*4 + 2] = x%255;
            scrnpxls[(y*ww+x)*4 + 3] = 255;
        }
    }


}

void UpdateWindow(){
    while(XPending(dspl) > 0){
        XNextEvent(dspl, &event);

        if(event.type == ConfigureNotify){
            if(ww != event.xconfigure.width || wh != event.xconfigure.height){
                ww = event.xconfigure.width;
                wh = event.xconfigure.height;
                OnResize();
                printf("%i %i\n", ww, wh);
            }
        }
    }


    Pixmap img = XCreatePixmap(dspl, win, ww, wh, DefaultDepth(dspl, DefaultScreen(dspl))); 
    XImage *ximage = XCreateImage(dspl, DefaultVisual(dspl, DefaultScreen(dspl)),
                                  DefaultDepth(dspl, DefaultScreen(dspl)),
                                  ZPixmap, 0, scrnpxls, ww, wh, 32, 0);

    XPutImage(dspl, img, gc, ximage, 0, 0, 0, 0, ww, wh);
    XCopyArea(dspl, img, win, gc, 0, 0, ww, wh, 0, 0);
    XFreePixmap(dspl, img);

    XFlush(dspl);
}

void OnResize(){
    scrnpxls = realloc(ww*wh*4); // test pattern
    for(u_int16_t x = 0; x < ww; x++){
        for(int16_t y = 0; y < wh; y++){
            scrnpxls[(y*ww+x)*4 + 0] = x%255;
            scrnpxls[(y*ww+x)*4 + 1] = y%255;
            scrnpxls[(y*ww+x)*4 + 2] = x%255;
            scrnpxls[(y*ww+x)*4 + 3] = 255;
        }
    }
}

void DestroyWindow(){
    XDestroyWindow(dspl, win);
    free(scrnpxls);
}