//
// Created by Anton on 02.07.2024.
//
#include <fstream>
#include <iostream>
#include <thread>
#include <string>
#include <vector>

#include "RWhaf.h"



using namespace std;

void WriteHafFile(ReadBMP readBMP, std::string filename ,int mode){

    string newName = "images/haf/";

    string headerName =newName + "header_" +filename+ ".txt";
    newName+= GetModeStr(mode);
    string pixelsName =newName + "_pixels_"+ filename+   ".bin";

    WriteHafFilePixels(readBMP.pixels, readBMP.infoheader.biWidth, readBMP.infoheader.biHeight, pixelsName, mode);
    WriteFileHeader(readBMP.infoheader, readBMP.fileheader, headerName, mode);


}
ReadBMP ReadHafFile(std::string filename){
    string newName = "images/haf/";

    string headerName =newName + "header_" +filename+ ".txt";
    ReadBMP readB;
    ReadFileHeader(readB, headerName);
    int mode=readB.infoheader.mode;

    newName+= GetModeStr(mode);
    string pixelsName =newName + "_pixels_"+ filename+   ".bin";

    ReadHafFilePixels(readB, pixelsName, mode);
    return readB;

}
void WriteHafFilePixels(RGBQUAD** pixels, unsigned int biWidth, unsigned int biHeight, string filename, int mode){

    FILE *oFile;
    oFile = fopen( filename.c_str(), "wb");
    int count =0;

    switch(mode) {
        case 0: {

            break;

        }
        case 1: {

           // unsigned char pre;
            //pre = pixels[0][0].grayPixel;
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
            for(int i=0; i<256;i++){
                cout<<i<<")\t"<<a[i]<<endl;
            }
            vector<Node> p;

            for(int i=0; i<256;i++){
                if (a[i]!=0){
                    Node n;
                    n.color =i;
                    n.sum = a[i];
                    p.push_back(n);
                //Pcolor b = Pcolor(i, a[i]);
               // cout<<(int)b.color<<endl;

                }
            }
            cout<<endl;
            BubbleSort(p);
            for (int i=0; i<p.size();i++){
               // cout<<(int)p[i].color<<endl;
               cout<<"!"<<endl;
                cout<<(int)p[i].color<<")\t"<<p[i].sum<<endl;
            }
            break;
        }
    }

    fclose(oFile);

}
void ReadHafFilePixels(ReadBMP &readB,string pixelsName, int mode) {

}

void BubbleSort(vector<Node> &arr)
{
    int i, j;
    for (i = 0; i < arr.size() - 1; i++)

        for (j = 0; j < arr.size() - i - 1; j++)
            if (arr[j].sum > arr[j + 1].sum)
                swap(arr[j], arr[j + 1]);
}