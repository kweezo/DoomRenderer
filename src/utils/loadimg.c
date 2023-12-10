#include "loadimg.h"

#define PADDING_BASE 4
#define WIDTH_OFFSET 0x12
#define HEIGHT_OFFSET 0x16
#define COLOR_SIZE_OFFSET 0x1C
#define PIXEL_ARRAY_ADDRESS 0x0A
#define HEADER_SIZE 0x46
#define X_OFFSET 64 // FIND OUT WHY AND FIX PERFORMANCE TOO BAD


ImageData LoadBMP(const char* path){
    FILE *fptr = fopen(path, "r");

    ImageData imgDat;
    imgDat.w = -1;
    imgDat.h = -1;
    imgDat.dat = NULL;

    if(fptr == NULL){
        fprintf(stderr, "Failed to load %s\n", path);
        return imgDat;
    }

    unsigned char header[HEADER_SIZE];

    fread(header, 1, HEADER_SIZE, fptr);


    imgDat.w = *(int32_t*)&header[WIDTH_OFFSET];
    imgDat.h = *(int32_t*)&header[HEIGHT_OFFSET];

    int16_t bpp = (*(u_int16_t*)&header[COLOR_SIZE_OFFSET])/8;
    u_int8_t padding = (PADDING_BASE - bpp);

    imgDat.dat = malloc(imgDat.w*imgDat.h*4);

    fseek(fptr, *(u_int32_t*)&header[PIXEL_ARRAY_ADDRESS], SEEK_SET);// go to start of pixel array

    
    if(bpp == PADDING_BASE){
        if(imgDat.w % 4 == 0){
            fread(imgDat.dat, 1, imgDat.w*imgDat.h*4, fptr);
        }
        else{
            for(int32_t i = 0; i < imgDat.h; i++){
                fread(imgDat.dat+(i*imgDat.h*4), 1, imgDat.w, fptr);
                fseek(fptr, ftell(fptr)+imgDat.w%4, SEEK_SET);
            }
        }
    }
    else{
        if(imgDat.w % 4 == 0){
            for(int32_t i = 0; i < imgDat.w * imgDat.h * 4; i += 4){
               fread((imgDat.dat+i), 1, bpp, fptr);
               for(u_int8_t y = 0; y < padding; y++){
                    imgDat.dat[i+(bpp-y)] = 255;
               }
            }
        }
        else{
            for(int32_t y = 0; y < imgDat.h; y++){
                for(int32_t x = 0; x < imgDat.w; x++){
                    fread(imgDat.dat + (y*imgDat.w+x)*4, 1, bpp, fptr);
                    for(u_int8_t y = 0; y < padding; y++){
                        imgDat.dat[(y*imgDat.w+x)*4+(bpp-y)] = 255;
                    }
                }
                fseek(fptr, ftell(fptr)+imgDat.w%4, SEEK_SET);
            }
        }
    }

    for(int32_t x = 0; x < imgDat.w; x++){
        for(int32_t y = 0; y < floor(imgDat.h/2); y++){
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