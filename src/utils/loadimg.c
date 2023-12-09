#include "loadimg.h"

#define PADDING_BASE 0x20
#define WIDTH_OFFSET 0x12
#define HEIGHT_OFFSET 0x16
#define X_OFFSET 64 // FIND OUT WHY AND FIX PERFORMANCE TOO BAD


ImageData LoadBMP(const char* path){
    //todo add os/2 1.x support
    FILE *fptr = fopen(path, "r");

    ImageData imgDat;
    imgDat.w = -1;
    imgDat.h = -1;

    if(fptr == NULL){
        fprintf(stderr, "Failed to load %s\n", path);
        return imgDat;
    }

    unsigned char header[54];

    fread(header, 1, 54, fptr);


    imgDat.w = *(int32_t*)&header[WIDTH_OFFSET];
    imgDat.h = *(int32_t*)&header[HEIGHT_OFFSET];

//todo add padding    int16_t bpp = *(u_int16_t*)&header[28];
//todo add padding and fix the bloody offset   u_int8_t padding = PADDING_BASE - bpp;

    imgDat.dat = malloc(imgDat.w*imgDat.h*4);


    fread(imgDat.dat, 1, 4 * imgDat.w * imgDat.h, fptr);

    for(int32_t x = 0; x < imgDat.w; x++){
        for(int32_t y = 0; y < imgDat.h/2; y++){
            int32_t flipY = imgDat.h - y - 1;

            u_int8_t tmp[4] = {
                imgDat.dat[(y*imgDat.w+x) * 4 + 0 ],
                imgDat.dat[(y*imgDat.w+x) * 4 + 1 ],
                imgDat.dat[(y*imgDat.w+x) * 4 + 2 ],
                imgDat.dat[(y*imgDat.w+x) * 4 + 3 ]
            };


            imgDat.dat[(y*imgDat.w+x)*4 + 0] = imgDat.dat[(flipY*imgDat.w+x)*4 + 0];
            imgDat.dat[(y*imgDat.w+x)*4 + 1] = imgDat.dat[(flipY*imgDat.w+x)*4 + 1];
            imgDat.dat[(y*imgDat.w+x)*4 + 2] = imgDat.dat[(flipY*imgDat.w+x)*4 + 2];
            imgDat.dat[(y*imgDat.w+x)*4 + 3] = imgDat.dat[(flipY*imgDat.w+x)*4 + 3];

            imgDat.dat[(flipY*imgDat.w+x)*4 + 0] = tmp[0];
            imgDat.dat[(flipY*imgDat.w+x)*4 + 1] = tmp[1];
            imgDat.dat[(flipY*imgDat.w+x)*4 + 2] = tmp[2];
            imgDat.dat[(flipY*imgDat.w+x)*4 + 3] = tmp[3];

        }
    }    


    fclose(fptr);


    return imgDat;
}