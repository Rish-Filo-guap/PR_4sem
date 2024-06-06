//
// Created by Anton on 05.06.2024.
//

#ifndef PR_4SEM_BMPRW_H
#define PR_4SEM_BMPRW_H

#endif //PR_4SEM_BMPRW_H


// CIEXYZTRIPLE stuff
typedef int FXPT2DOT30;

 struct CIEXYZ{
    FXPT2DOT30 ciexyzX;
    FXPT2DOT30 ciexyzY;
    FXPT2DOT30 ciexyzZ;
} ;

 struct CIEXYZTRIPLE{
    CIEXYZ  ciexyzRed;
    CIEXYZ  ciexyzGreen;
    CIEXYZ  ciexyzBlue;
} ;

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
    unsigned int   biAlphaMask;
    unsigned int   biCSType;
    CIEXYZTRIPLE   biEndpoints;
    unsigned int   biGammaRed;
    unsigned int   biGammaGreen;
    unsigned int   biGammaBlue;
    unsigned int   biIntent;
    unsigned int   biProfileData;
    unsigned int   biProfileSize;
    unsigned int   biReserved;
} ;

// rgb quad
 struct RGBQUAD {
    unsigned char  rgbBlue;
    unsigned char  rgbGreen;
    unsigned char  rgbRed;
    unsigned char  rgbReserved;
} ;

struct ReadBMP{
    RGBQUAD** pixels;
    BITMAPINFOHEADER infoheader;
    BITMAPFILEHEADER fileheader;
};
// read bytes
template <typename Type>
void read(std::ifstream& fp, Type& result, std::size_t size) {
    fp.read(reinterpret_cast<char*>(&result), size);
}

// bit extract
unsigned char bitextract(const unsigned int byte, const unsigned int mask);

static void write_u16(unsigned short input, FILE* fp);
static void write_u32(unsigned int input, FILE* fp);

ReadBMP ReadBMPfile(std::string fileName);
void WriteBMPfile(ReadBMP readBMP, std::string filename);

