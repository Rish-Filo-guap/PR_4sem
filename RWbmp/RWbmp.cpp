//
// Created by Anton on 05.06.2024.
//
#include <iostream>
#include <fstream>
#include <cstdio>

#include "RWbmp.h"

using namespace std;



ReadBMP ReadBMPfile(string fileName)
{


    // открываем файл
    string folder = "images/old/";
    string newName = folder;
    newName += fileName;
    std::ifstream fileStream(newName.c_str(), std::ifstream::binary);


    // заголовки изображения
    BITMAPFILEHEADER fileHeader;
    read(fileStream, fileHeader.bfType, sizeof(fileHeader.bfType));
    read(fileStream, fileHeader.bfSize, sizeof(fileHeader.bfSize));
    read(fileStream, fileHeader.bfReserved1, sizeof(fileHeader.bfReserved1));
    read(fileStream, fileHeader.bfReserved2, sizeof(fileHeader.bfReserved2));
    read(fileStream, fileHeader.bfOffBits, sizeof(fileHeader.bfOffBits));



    // информация изображения
    BITMAPINFOHEADER fileInfoHeader;
    read(fileStream, fileInfoHeader.biSize, sizeof(fileInfoHeader.biSize));

    // bmp core
    if (fileInfoHeader.biSize >= 12) {
        read(fileStream, fileInfoHeader.biWidth, sizeof(fileInfoHeader.biWidth));
        read(fileStream, fileInfoHeader.biHeight, sizeof(fileInfoHeader.biHeight));
        read(fileStream, fileInfoHeader.biPlanes, sizeof(fileInfoHeader.biPlanes));
        read(fileStream, fileInfoHeader.biBitCount, sizeof(fileInfoHeader.biBitCount));
    }

    // получаем информацию о битности
    int colorsCount = fileInfoHeader.biBitCount >> 3;
    if (colorsCount < 3) {
        colorsCount = 3;
    }

    int bitsOnColor = fileInfoHeader.biBitCount / colorsCount;
    int maskValue = (1 << bitsOnColor) - 1;

    // bmp v1
    if (fileInfoHeader.biSize >= 40) {
        read(fileStream, fileInfoHeader.biCompression, sizeof(fileInfoHeader.biCompression));
        read(fileStream, fileInfoHeader.biSizeImage, sizeof(fileInfoHeader.biSizeImage));
        read(fileStream, fileInfoHeader.biXPelsPerMeter, sizeof(fileInfoHeader.biXPelsPerMeter));
        read(fileStream, fileInfoHeader.biYPelsPerMeter, sizeof(fileInfoHeader.biYPelsPerMeter));
        read(fileStream, fileInfoHeader.biClrUsed, sizeof(fileInfoHeader.biClrUsed));
        read(fileStream, fileInfoHeader.biClrImportant, sizeof(fileInfoHeader.biClrImportant));
    }

    //// bmp v2
//    fileInfoHeader.biRedMask = 0;
//    fileInfoHeader.biGreenMask = 0;
//    fileInfoHeader.biBlueMask = 0;

//    if (fileInfoHeader.biSize >= 52) {
//        read(fileStream, fileInfoHeader.biRedMask, sizeof(fileInfoHeader.biRedMask));
//        read(fileStream, fileInfoHeader.biGreenMask, sizeof(fileInfoHeader.biGreenMask));
//        read(fileStream, fileInfoHeader.biBlueMask, sizeof(fileInfoHeader.biBlueMask));
//    }

    // если маска не задана, то ставим маску по умолчанию
    if (fileInfoHeader.biRedMask == 0 || fileInfoHeader.biGreenMask == 0 || fileInfoHeader.biBlueMask == 0) {
        fileInfoHeader.biRedMask = maskValue << (bitsOnColor * 2);
        fileInfoHeader.biGreenMask = maskValue << bitsOnColor;
        fileInfoHeader.biBlueMask = maskValue;
    }



    // rgb info
    RGBQUAD** rgbInfo = new RGBQUAD * [fileInfoHeader.biHeight];

    for (unsigned int i = 0; i < fileInfoHeader.biHeight; i++) {
        rgbInfo[i] = new RGBQUAD[fileInfoHeader.biWidth];
    }

    // определение размера отступа в конце каждой строки
    int linePadding = ((fileInfoHeader.biWidth * (fileInfoHeader.biBitCount / 8)) % 4) & 3;

    // чтение
    unsigned int bufer;

    for (unsigned int i = 0; i < fileInfoHeader.biHeight; i++) {
        for (unsigned int j = 0; j < fileInfoHeader.biWidth; j++) {
            read(fileStream, bufer, fileInfoHeader.biBitCount / 8);

            rgbInfo[i][j].rgbRed = bitextract(bufer, fileInfoHeader.biRedMask);
            rgbInfo[i][j].rgbGreen = bitextract(bufer, fileInfoHeader.biGreenMask);
            rgbInfo[i][j].rgbBlue = bitextract(bufer, fileInfoHeader.biBlueMask);
            rgbInfo[i][j].rgbReserved = bitextract(bufer, fileInfoHeader.biAlphaMask);
        }
        fileStream.seekg(linePadding, std::ios_base::cur);
    }

    // вывод
    ReadBMP read;
    //read.name = fileName.c_str();
    read.pixels = rgbInfo;
    read.infoheader = fileInfoHeader;
    read.fileheader = fileHeader;

    return read;
}
void WriteBMPfile(ReadBMP readBMP, string filename) {


    FILE* oFile;

    const char* folder = "images/new/";
    string newName = folder;

    newName += filename;
   // cout<<"rw "<<filename<<endl;
    oFile = fopen( newName.c_str(), "wb");


    // заголовк изображения
    write_u16(readBMP.fileheader.bfType, oFile);
    write_u32(readBMP.fileheader.bfSize, oFile);
    write_u16(readBMP.fileheader.bfReserved1, oFile);
    write_u16(readBMP.fileheader.bfReserved2, oFile);
    write_u32(readBMP.fileheader.bfOffBits, oFile);



    // информация изображения
    //BITMAPINFOHEADER fileInfoHeader;
    write_u32(readBMP.infoheader.biSize, oFile);

    // bmp core
    if (readBMP.infoheader.biSize >= 12) {
        write_u32(readBMP.infoheader.biWidth, oFile);
        write_u32(readBMP.infoheader.biHeight, oFile);
        write_u16(readBMP.infoheader.biPlanes, oFile);
        write_u16(readBMP.infoheader.biBitCount, oFile);
    }



    // bmp v1
    if (readBMP.infoheader.biSize >= 40) {
        write_u32(readBMP.infoheader.biCompression, oFile);
        write_u32(readBMP.infoheader.biSizeImage, oFile);
        write_u32(readBMP.infoheader.biXPelsPerMeter, oFile);
        write_u32(readBMP.infoheader.biYPelsPerMeter, oFile);
        write_u32(readBMP.infoheader.biClrUsed, oFile);
        write_u32(readBMP.infoheader.biClrImportant, oFile);
    }




    for (unsigned int i = 0; i < readBMP.infoheader.biHeight; i++) {
        for (unsigned int j = 0; j < readBMP.infoheader.biWidth; j++) {
            //unsigned char graypixel = readBMP.pixels[i][j].rgbRed * 0.2126 + 0.7152 * readBMP.pixels[i][j].rgbGreen + readBMP.pixels[i][j].rgbBlue * 0.0722;

            /*putc(graypixel & 0xFF, oFile);
            putc(graypixel & 0xFF, oFile);
            putc(graypixel & 0xFF, oFile);*/

            putc(readBMP.pixels[i][j].rgbBlue & 0xFF, oFile);
            putc(readBMP.pixels[i][j].rgbGreen & 0xFF, oFile);
            putc(readBMP.pixels[i][j].rgbRed & 0xFF, oFile);

        }

    }
    fclose(oFile);

}
unsigned char bitextract(const unsigned int byte, const unsigned int mask) {
    if (mask == 0) {
        return 0;
    }

    // определение количества нулевых бит справа от маски
    int
            maskBufer = mask,
            maskPadding = 0;

    while (!(maskBufer & 1)) {
        maskBufer >>= 1;
        maskPadding++;
    }

    // применение маски и смещение
    return (byte & mask) >> maskPadding;
}
static void write_u16(unsigned short input, FILE* fp)
{
    putc(input, fp);
    putc(input >> 8, fp);
}

static void write_u32(unsigned int input, FILE* fp)
{
    putc(input, fp);
    putc(input >> 8, fp);
    putc(input >> 16, fp);
    putc(input >> 24, fp);
}