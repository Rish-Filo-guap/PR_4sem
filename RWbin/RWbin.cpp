//
// Created by Anton on 05.06.2024.
//
#include <fstream>
#include <iostream>
#include <fstream>
#include <thread>
#include <string>

#include "../RWbmp/RWbmp.h"
using  namespace std;

void WriteBinFilePixels(RGBQUAD** pixels, unsigned int biWidth, unsigned int biHeight, string filename);
void WriteFileHeader(BITMAPINFOHEADER infoheader, BITMAPFILEHEADER fileheader, string filename);


void WriteBinFile(ReadBMP readBMP, string filename){


    string newName = "images/bin/";

    newName+=filename;
    string headerName = newName;
    headerName+="_header.txt";
    string pixelsName = newName + "_pixels.bin";

    WriteBinFilePixels(readBMP.pixels, readBMP.infoheader.biWidth, readBMP.infoheader.biHeight, pixelsName);

    WriteFileHeader(readBMP.infoheader, readBMP.fileheader, headerName);

}
void WriteBinFilePixels(RGBQUAD** pixels, unsigned int biWidth, unsigned int biHeight, string filename){

    FILE *oFile;
    oFile = fopen( filename.c_str(), "w");

    for (unsigned int i = 0; i < biHeight; i++) {
        for (unsigned int j = 0; j < biWidth; j++) {
            //unsigned char graypixel = readBMP.pixels[i][j].rgbRed * 0.2126 + 0.7152 * readBMP.pixels[i][j].rgbGreen + readBMP.pixels[i][j].rgbBlue * 0.0722;
            putc(pixels[i][j].rgbBlue, oFile);
            putc(pixels[i][j].rgbGreen, oFile);
            putc(pixels[i][j].rgbRed, oFile);


        }

    }
    fclose(oFile);

}
void write_int(unsigned int a, ofstream* out){
    *out<<a<<endl;
}
void write_short(unsigned short a, ofstream* out){
    *out<<a<<endl;
}

void WriteFileHeader(BITMAPINFOHEADER infoheader, BITMAPFILEHEADER fileheader, string filename){

    ofstream oFile;
    oFile.open(filename);


    // заголовк изображения

    write_short(fileheader.bfType, &oFile);
    write_int(fileheader.bfSize, &oFile);
    write_short(fileheader.bfReserved1, &oFile);
    write_short(fileheader.bfReserved2, &oFile);
    write_int(fileheader.bfOffBits, &oFile);

    // информация изображения
    //BITMAPINFOHEADER fileInfoHeader;
    write_int(infoheader.biSize, &oFile);

    // bmp core
    if (infoheader.biSize >= 12) {
        write_int(infoheader.biWidth, &oFile);
        write_int(infoheader.biHeight, &oFile);
        write_short(infoheader.biPlanes, &oFile);
        write_short(infoheader.biBitCount, &oFile);
    }

    // bmp v1
    if (infoheader.biSize >= 40) {
        write_int(infoheader.biCompression, &oFile);
        write_int(infoheader.biSizeImage, &oFile);
        write_int(infoheader.biXPelsPerMeter, &oFile);
        write_int(infoheader.biYPelsPerMeter, &oFile);
        write_int(infoheader.biClrUsed, &oFile);
        write_int(infoheader.biClrImportant, &oFile);
    }
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



    }
    in.close();
}
void ReadBinFilePixels(ReadBMP &readB,string pixelsName){

    ifstream fileStream(pixelsName, ifstream::binary);

    RGBQUAD** rgbInfo = new RGBQUAD * [readB.infoheader.biHeight];

    for (unsigned int i = 0; i < readB.infoheader.biHeight; i++) {
        rgbInfo[i] = new RGBQUAD[readB.infoheader.biWidth];
    }

    unsigned char bufer;

    for (unsigned int i = 0; i < readB.infoheader.biHeight; i++) {
        for (unsigned int j = 0; j < readB.infoheader.biWidth; j++) {
            int size=256;
            //read(fileStream, bufer, size);
            read(fileStream, bufer,  sizeof(unsigned char));
            rgbInfo[i][j].rgbBlue=bufer;
            //fileStream.read((char *)&bufer, sizeof (bufer));
           // cout<<bufer<<" ";
            read(fileStream, bufer,  sizeof(unsigned char));
            rgbInfo[i][j].rgbGreen=bufer;
            //cout<<bufer<<" ";

            read(fileStream, bufer, sizeof(unsigned char));
            rgbInfo[i][j].rgbRed=bufer;
            //cout<<bufer<<" ";
            //read(fileStream, bufer, size);
            //readB.pixels[i][j].rgbGreen=10;

            //read(fileStream, bufer, size);
            //readB.pixels[i][j].rgbRed=10;

        }

    }
            cout<<pixelsName[11]<<endl;
    readB.pixels = rgbInfo;
    fileStream.close();
}

ReadBMP ReadBinFile(string filename){

    string newName = "images/bin/";

    newName+=filename;
    string headerName = newName + "_header.txt";
    string pixelsName = newName + "_pixels.bin";

    ReadBMP readB;
    string Name =filename;
    Name= "new_" + Name;


    //cout<<" "<<filename<<endl;
    ReadFileHeader(readB, headerName);
    ReadBinFilePixels(readB, pixelsName);
    return readB;

}