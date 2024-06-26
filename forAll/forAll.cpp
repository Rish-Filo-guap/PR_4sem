//
// Created by Anton on 25.06.2024.
//
#include <fstream>
#include <iostream>
#include <thread>
#include <string>

#include "forAll.h"
using  namespace std;

string GetModeStr(int mode){

    switch(mode){
        case 0:
            return "rgb_";
        case 1:
            return "wb_";
        default:
            return "";
    };
}

void write_int(unsigned int a, ofstream* out){
    *out<<a<<endl;
}
void write_short(unsigned short a, ofstream* out){
    *out<<a<<endl;
}


void WriteFileHeader(BITMAPINFOHEADER infoheader, BITMAPFILEHEADER fileheader, string filename, int mode){

    ofstream oFile;
    oFile.open(filename);


    // заголовк изображения

    write_short(fileheader.bfType, &oFile);
    write_int(fileheader.bfSize, &oFile);
    write_short(fileheader.bfReserved1, &oFile);
    write_short(fileheader.bfReserved2, &oFile);
    write_int(fileheader.bfOffBits, &oFile);

    // информация изображения

    write_int(infoheader.biSize, &oFile);

    // bmp core

    write_int(infoheader.biWidth, &oFile);
    write_int(infoheader.biHeight, &oFile);
    write_short(infoheader.biPlanes, &oFile);
    write_short(infoheader.biBitCount, &oFile);


    // bmp v1

    write_int(infoheader.biCompression, &oFile);
    write_int(infoheader.biSizeImage, &oFile);
    write_int(infoheader.biXPelsPerMeter, &oFile);
    write_int(infoheader.biYPelsPerMeter, &oFile);
    write_int(infoheader.biClrUsed, &oFile);
    write_int(infoheader.biClrImportant, &oFile);

    write_short(mode, &oFile);
    oFile.close();
}
void ReadFileHeader(ReadBMP &readB,string headerName){
    ifstream in(headerName);
    string line;
    if(in.is_open()){
        getline(in, line);
        readB.fileheader.bfType = stoi(line);


        getline(in, line);
        readB.fileheader.bfSize = stoi(line);

        getline(in, line);
        readB.fileheader.bfReserved1 = stoi(line);

        getline(in, line);
        readB.fileheader.bfReserved2 = stoi(line);

        getline(in, line);
        readB.fileheader.bfOffBits = stoi(line);


        getline(in, line);
        readB.infoheader.biSize = stoi(line);


        getline(in, line);
        readB.infoheader.biWidth = stoi(line);

        getline(in, line);
        readB.infoheader.biHeight = stoi(line);

        getline(in, line);
        readB.infoheader.biPlanes = stoi(line);

        getline(in, line);
        readB.infoheader.biBitCount = stoi(line);


        getline(in, line);
        readB.infoheader.biCompression = stoi(line);

        getline(in, line);
        readB.infoheader.biSizeImage = stoi(line);

        getline(in, line);
        readB.infoheader.biXPelsPerMeter= stoi(line);

        getline(in, line);
        readB.infoheader.biYPelsPerMeter = stoi(line);

        getline(in, line);
        readB.infoheader.biClrUsed = stoi(line);

        getline(in, line);
        readB.infoheader.biClrImportant = stoi(line);

        getline(in, line);
        readB.infoheader.mode = stoi(line);

    }
    in.close();
}
