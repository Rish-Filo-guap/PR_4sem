//
// Created by Anton on 26.06.2024.
//
#include <fstream>
#include <iostream>
#include <thread>
#include <string>

#include "RWrle.h"


void WriteRLEFile(ReadBMP readBMP, std::string filename ,int mode){

    string newName = "images/rle/";

    string headerName =newName + "header_" +filename+ ".txt";
    newName+= GetModeStr(mode);
    string pixelsName =newName + "_pixels_"+ filename+   ".bin";

    WriteRLEFilePixels(readBMP.pixels, readBMP.infoheader.biWidth, readBMP.infoheader.biHeight, pixelsName, mode);
    WriteFileHeader(readBMP.infoheader, readBMP.fileheader, headerName, mode);


}
ReadBMP ReadRLEFile(std::string filename){
    string newName = "images/rle/";

    string headerName =newName + "header_" +filename+ ".txt";
    ReadBMP readB;
    ReadFileHeader(readB, headerName);
    int mode=readB.infoheader.mode;

    newName+= GetModeStr(mode);
    string pixelsName =newName + "_pixels_"+ filename+   ".bin";

    ReadRLEFilePixels(readB, pixelsName, mode);
    return readB;

}
void ReadRLEFilePixels(ReadBMP &readB,string pixelsName, int mode) {

    ifstream fileStream(pixelsName, ifstream::binary);


    RGBQUAD **rgbInfo = new RGBQUAD *[readB.infoheader.biHeight];

    for (unsigned int i = 0; i < readB.infoheader.biHeight; i++) {
        rgbInfo[i] = new RGBQUAD[readB.infoheader.biWidth];
    }
    switch (mode) {

        case 0: {
            unsigned char buferR;
            unsigned char buferG;
            unsigned char buferB;
            int count = 0;
            for (unsigned int i = 0; i < readB.infoheader.biHeight; i++) {
                for (unsigned int j = 0; j < readB.infoheader.biWidth; j++) {

                    if (count == 0) {
                        read(fileStream, count, 4);
                        read(fileStream, buferR, 1);
                        read(fileStream, buferG, 1);
                        read(fileStream, buferB, 1);


                    }
                    count--;
                    rgbInfo[i][j].rgbRed = buferR;
                    rgbInfo[i][j].rgbGreen = buferG;
                    rgbInfo[i][j].rgbBlue = buferB;


                }

            }
            break;
        }
        case 1: {
            unsigned char bufer;
            int count = 0;

            for (unsigned int i = 0; i < readB.infoheader.biHeight; i++) {
                for (unsigned int j = 0; j < readB.infoheader.biWidth; j++) {

                    if (count == 0) {
                        read(fileStream, count, 4);
                        read(fileStream, bufer, 1);
                    }
                    count--;
                    rgbInfo[i][j].grayPixel = bufer;
                }

            }


            break;
        }
    }
    readB.pixels = rgbInfo;
    fileStream.close();
}
bool RGBQUADIsEqual(RGBQUAD a, RGBQUAD b){
    if (a.rgbRed == b.rgbRed && a.rgbGreen == b.rgbGreen && a.rgbBlue == b.rgbBlue)
        return true;
    else
        return false;
}
void WriteRLEFilePixels(RGBQUAD** pixels, unsigned int biWidth, unsigned int biHeight, string filename, int mode){

    FILE *oFile;
    oFile = fopen( filename.c_str(), "wb");
    int count =0;

    switch(mode) {
        case 0: {

            RGBQUAD pre;
            pre = pixels[0][0];

            for (unsigned int i = 0; i < biHeight; i++) {
                for (unsigned int j = 0; j < biWidth; j++) {

                    if (!RGBQUADIsEqual(pre,pixels[i][j])){

                        putc(count, oFile);
                        putc(count >> 8, oFile);
                        putc(count >> 16, oFile);
                        putc(count >> 24, oFile);

                        putc(pre.rgbRed, oFile);
                        putc(pre.rgbGreen, oFile);
                        putc(pre.rgbBlue, oFile);
                        pre = pixels[i][j];
                        count =1;
                    }
                    else count++;
                }
            }

            putc(count, oFile);
            putc(count >> 8, oFile);
            putc(count >> 16, oFile);
            putc(count >> 24, oFile);

            putc(pre.rgbRed, oFile);
            putc(pre.rgbGreen, oFile);
            putc(pre.rgbBlue, oFile);

            break;
        }
        case 1: {

            unsigned char pre;
            pre = pixels[0][0].grayPixel;

            for (unsigned int i = 0; i < biHeight; i++) {
                for (unsigned int j = 0; j < biWidth; j++) {

                    if (pre != pixels[i][j].grayPixel){

                        putc(count, oFile);
                        putc(count >> 8, oFile);
                        putc(count >> 16, oFile);
                        putc(count >> 24, oFile);

                        putc(pre, oFile);
                        pre = pixels[i][j].grayPixel;

                        count =1;
                    }
                    else count++;
                }
            }

            putc(count, oFile);
            putc(count >> 8, oFile);
            putc(count >> 16, oFile);
            putc(count >> 24, oFile);
            putc(pre, oFile);

            break;
        }
    }

    fclose(oFile);

}