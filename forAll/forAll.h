//
// Created by Anton on 25.06.2024.
//
#ifndef PR_4SEM_FORALL_H
#define PR_4SEM_FORALL_H
#pragma once


#include <string>
using namespace std;


typedef int FXPT2DOT30;

// read bytes
template <typename Type>

void read(std::ifstream& fp, Type& result, std::size_t size) {
    fp.read(reinterpret_cast<char*>(&result), size);
}



// bitmap file header
struct BITMAPFILEHEADER{
    unsigned short bfType;
    unsigned int   bfSize;
    unsigned short bfReserved1;
    unsigned short bfReserved2;
    unsigned int   bfOffBits;
} ;

// bitmap info header
struct BITMAPINFOHEADER{
    unsigned int   biSize;
    unsigned int   biWidth;
    unsigned int   biHeight;
    unsigned short biPlanes;
    unsigned short biBitCount;
    unsigned int   biCompression;
    unsigned int   biSizeImage;
    unsigned int   biXPelsPerMeter;
    unsigned int   biYPelsPerMeter;
    unsigned int   biClrUsed;
    unsigned int   biClrImportant;
    unsigned int   biRedMask;
    unsigned int   biGreenMask;
    unsigned int   biBlueMask;
    unsigned int   mode;

} ;

// rgb quad
struct RGBQUAD {
    unsigned char  rgbBlue;
    unsigned char  rgbGreen;
    unsigned char  rgbRed;
    unsigned char  grayPixel;
} ;

struct ReadBMP{
    RGBQUAD** pixels;
    BITMAPINFOHEADER infoheader;
    BITMAPFILEHEADER fileheader;
};



string GetModeStr(int mode);




void write_int(unsigned int a, ofstream* out);
void write_short(unsigned short a, ofstream* out);


void WriteFileHeader(BITMAPINFOHEADER infoheader, BITMAPFILEHEADER fileheader, string filename, int mode);
void ReadFileHeader(ReadBMP &readB,string headerName);




#endif //PR_4SEM_FORALL_H