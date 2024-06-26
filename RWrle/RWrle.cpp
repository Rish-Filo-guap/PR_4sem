//
// Created by Anton on 26.06.2024.
//
#include <fstream>
#include <iostream>
#include <thread>
#include <string>

//#include "../RWbmp/RWbmp.h"
#include "RWrle.h"


void WriteRLEFile(ReadBMP readBMP, std::string filename ,int mode){

    string newName = "images/rle/";

    //newName+=filename;
    string headerName =newName + "header_" +filename+ ".txt";
    //string headerName = newName+"_header.txt";
    newName+= GetModeStr(mode);
    string pixelsName =newName + "_pixels_"+ filename+   ".bin";
    //string pixelsName = newName + "_pixels.bin";

    WriteRLEFilePixels(readBMP.pixels, readBMP.infoheader.biWidth, readBMP.infoheader.biHeight, pixelsName, mode);
    WriteFileHeader(readBMP.infoheader, readBMP.fileheader, headerName, mode);


}
ReadBMP ReadRLEFile(std::string filename){
    string newName = "images/rle/";

    //newName+=filename;
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

    unsigned char bufer;

    //cout<<"```````````";
    int count = 0;
    for (unsigned int i = 0; i < readB.infoheader.biHeight; i++) {
        for (unsigned int j = 0; j < readB.infoheader.biWidth; j++) {
            // cout<<fileStream.gcount()<<endl;
            switch (mode) {

                case 0: {


                    break;
                }
                case 1: {
                    if (count == 0) {
                        read(fileStream, count, 4);
                        read(fileStream, bufer, 1);

                        cout<<endl<<(int)bufer;

                    }
                    rgbInfo[i][j].grayPixel = bufer;
                    count--;
                    //cout<<count<<" ";
                    //cout<<count<<"\t"<<(int)bufer<<endl;


                    //cout<<(char)bufer;
//                    while(count>0){
//                        count--;
//                        //cout<<j<<"\t "<<i<<"\t "<<bufer<<"\t "<<count<<endl;
//                    //for(int k=0; k<count && i<readB.infoheader.biHeight-1;k++){
//                        rgbInfo[j][i].grayPixel = bufer;
//                        i++;
//                        //cout<<i<<"\t "<<j<<"\t "<<bufer<<"\t "<<count<<endl;
//                        if(i>=readB.infoheader.biWidth){
//                            i=0;
//                            j++;
//
//                            //cout<<i<<" ";
//                        }
//                        if (j>=readB.infoheader.biHeight){
//                            break;
//                        }
//                        //cout<<count<<"!"<<endl;
//                        //cout<<j<<endl;
//                    //}
//                    }
//                        //if (count==1) cout<<j<<"\t "<<i<<"\t "<<bufer<<"\t "<<count<<endl;
                    break;
                }
            }


        }

    }


    readB.pixels = rgbInfo;
    fileStream.close();




}
void WriteRLEFilePixels(RGBQUAD** pixels, unsigned int biWidth, unsigned int biHeight, string filename, int mode){

    FILE *oFile;
    oFile = fopen( filename.c_str(), "wb");
    int count =1;
    int countz = 0;
    int countmax = 0;

    unsigned char pre;

    switch(mode) {
        case 0: {
            break;
        }
        case 1: {

            pre = pixels[0][0].grayPixel;
            break;
        }
    }
    for (unsigned int i = 0; i < biHeight; i++) {
        for (unsigned int j = 0; j < biWidth; j++) {

            switch(mode){
                case 0:{
//                    putc(pixels[i][j].rgbBlue & 0xFF, oFile);
//                    putc(pixels[i][j].rgbGreen & 0xFF, oFile);
//                    putc(pixels[i][j].rgbRed & 0xFF, oFile);
                    break;
                }
                case 1:{
                    if (pre !=pixels[i][j].grayPixel){

                        pre = pixels[i][j].grayPixel;
                        //putc(count, oFile);
                        putc(count, oFile);
                        putc(count >> 8, oFile);
                        putc(count >> 16, oFile);
                        putc(count >> 24, oFile);
                        //write_u32(count, oFile);
                        putc(pre, oFile);
                        //cout<<count<<"\t"<<(int)pre<<endl;
                        count =1;
                        countz++;
                    }else{
                        if(count>countmax) countmax=count;
                        count++;
                    }

                    break;
                }
            }


        }

    }
    putc(count, oFile);
    putc(pre, oFile);
    float d= (float)(biHeight*biWidth) / countz;
    cout<<d<<" "<<countmax<<endl;
    fclose(oFile);

}