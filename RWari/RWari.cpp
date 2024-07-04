//
// Created by Anton on 04.07.2024.
//
#include "RWari.h"


void WriteAriFile(ReadBMP readBMP, std::string filename, int mode){
    string newName = "images/ari/";

    string headerName =newName + "header_" +filename+ ".txt";
    newName+= GetModeStr(mode);
    string pixelsName =newName + "_pixels_"+ filename+   ".bin";

    WriteAriFilePixels(readBMP.pixels, readBMP.infoheader.biWidth, readBMP.infoheader.biHeight, pixelsName, mode);
    WriteFileHeader(readBMP.infoheader, readBMP.fileheader, headerName, mode);


}

ReadBMP ReadAriFile(std::string filename){
    string newName = "images/ari/";

    string headerName =newName + "header_" +filename+ ".txt";
    ReadBMP readB;
    ReadFileHeader(readB, headerName);
    int mode=readB.infoheader.mode;

    newName+= GetModeStr(mode);
    string pixelsName =newName + "_pixels_"+ filename+   ".bin";

    ReadAriFilePixels(readB, pixelsName, mode);
    return readB;
}

void WriteAriFilePixels(RGBQUAD** pixels, unsigned int biWidth, unsigned int biHeight, string filename, int mode){

    FILE *oFile;
    oFile = fopen( filename.c_str(), "wb");

    int *a =  new int[256];
    for(int i=0; i<256;i++){
        a[i]=0;
    }

    for (unsigned int i = 0; i < biHeight; i++) {
        for (unsigned int j = 0; j < biWidth; j++) {
            //cout<<(int)pixels[0][0].grayPixel<<endl;
            a[(int)pixels[i][j].grayPixel]++;
        }
    }
    vector<PColor> p;

    for(int i=0; i<=255;i++){
        if (a[i]!=0){
            PColor n;
            n.color =i;
            //     cout<<"n"<<n.color<<endl;
            n.sum = a[i];
            n.havecolor=true;
            p.push_back(n);
            //Pcolor b = Pcolor(i, a[i]);
            //cout<<(int)b.color<<endl;

        }
    }

}

void ReadAriFilePixels(ReadBMP &readB,string pixelsName, int mode){


}