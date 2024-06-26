//
// Created by Anton on 05.06.2024.
//
#include <fstream>
#include <iostream>
#include <thread>
#include <string>

#include "../RWbmp/RWbmp.h"

#include "RWbin.h"
using  namespace std;



ReadBMP ReadBinFile(string filename){

    string newName = "images/bin/";

    //newName+=filename;
    string headerName =newName + "header_" +filename+ ".txt";

    ReadBMP readB;
    ReadFileHeader(readB, headerName);
    int mode=readB.infoheader.mode;

    newName+= GetModeStr(mode);
    string pixelsName =newName + "_pixels_"+ filename+   ".bin";

    ReadBinFilePixels(readB, pixelsName, mode);
    return readB;

}


void WriteBinFile(ReadBMP readBMP, string filename, int mode){


    string newName = "images/bin/";

    //newName+=filename;
    string headerName =newName + "header_" +filename+ ".txt";
    //string headerName = newName+"_header.txt";
    newName+= GetModeStr(mode);
    string pixelsName =newName + "_pixels_"+ filename+   ".bin";
    //string pixelsName = newName + "_pixels.bin";

    WriteBinFilePixels(readBMP.pixels, readBMP.infoheader.biWidth, readBMP.infoheader.biHeight, pixelsName, mode);
    WriteFileHeader(readBMP.infoheader, readBMP.fileheader, headerName, mode);


}
void WriteBinFilePixels(RGBQUAD** pixels, unsigned int biWidth, unsigned int biHeight, string filename, int mode){

    FILE *oFile;
    oFile = fopen( filename.c_str(), "wb");

    for (unsigned int i = 0; i < biHeight; i++) {
        for (unsigned int j = 0; j < biWidth; j++) {

            switch(mode){
                case 0:{
                    putc(pixels[i][j].rgbBlue, oFile);
                    putc(pixels[i][j].rgbGreen, oFile);
                    putc(pixels[i][j].rgbRed, oFile);
                    break;
                }
                case 1:{
                    putc(pixels[i][j].grayPixel, oFile);
                    break;
                }
            }


        }

    }
    fclose(oFile);

}



void ReadBinFilePixels(ReadBMP &readB,string pixelsName, int mode){

    ifstream fileStream(pixelsName, ifstream::binary);

    RGBQUAD** rgbInfo = new RGBQUAD * [readB.infoheader.biHeight];

    for (unsigned int i = 0; i < readB.infoheader.biHeight; i++) {
        rgbInfo[i] = new RGBQUAD[readB.infoheader.biWidth];
    }

    unsigned int bufer;
    for (unsigned int i = 0; i < readB.infoheader.biHeight; i++) {
        for (unsigned int j = 0; j < readB.infoheader.biWidth; j++) {

            switch (mode) {

                case 0:{
                    read(fileStream, bufer, 1);
                    rgbInfo[i][j].rgbBlue = bufer;

                    read(fileStream, bufer, 1);
                    rgbInfo[i][j].rgbGreen = bufer;

                    read(fileStream, bufer, 1);
                    rgbInfo[i][j].rgbRed = bufer;

                    break;
                }
                case 1:{
                    read(fileStream, bufer, 1);
                    rgbInfo[i][j].grayPixel = bufer;
                    break;
                }
            }



        }
    }


    readB.pixels = rgbInfo;
    fileStream.close();
}

