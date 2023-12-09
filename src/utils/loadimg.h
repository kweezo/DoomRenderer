#ifndef LOADIMG_H
#define LOADIMG_H

#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct {
    int32_t w;
    int32_t h;
    u_int8_t* dat;
} ImageData;

ImageData LoadBMP(const char* path);

#endif