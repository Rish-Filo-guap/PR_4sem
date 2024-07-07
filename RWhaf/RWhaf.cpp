//
// Created by Anton on 02.07.2024.
//
#include <fstream>
#include <iostream>
#include <thread>
#include <string>
#include <vector>
#include <bitset>

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

    switch(mode) {
        case 0: {

            break;

        }
        case 1: {
            int *a =  new int[256];

            for(int i=0; i<256;i++){
                a[i]=0;
            }

            for (unsigned int i = 0; i < biHeight; i++) {
                for (unsigned int j = 0; j < biWidth; j++) {

                    a[(int)pixels[i][j].grayPixel]++;
                }
            }

            vector<Node> p;

            for(int i=0; i<=255;i++){
                if (a[i]!=0){
                    Node n;
                    n.color =i;
                    n.sum = a[i];
                    n.havecolor=true;
                    p.push_back(n);
                }
            }

            BubbleSortNodes(p);

            while (p.size()>1){
                Node *n = new  Node();

                n->SetNodes(p[0],p[1]);
                p.erase(p.cbegin());
                p.erase(p.cbegin());
                p.push_back(*n);

                BubbleSortNodes(p);
            }

            vector<CodeColor> v;

            p[0].GetCodeVector("", v);
            BubbleSortCodeColors(v);

//            for(int i=0; i<v.size();i++){
//                cout<<v[i].code<<"\t"<<(int)v[i].color<<endl;
//            }

            string strPixels = "";

            for (unsigned int i = 0; i < biHeight; i++) {
                for (unsigned int j = 0; j < biWidth; j++) {
                    string temp = "";
                    temp = SearchColor(pixels[i][j].grayPixel, v);
                    strPixels+=temp;
                }
            }
            //cout<<strPixels<<endl;
            //пишем кол-во кодов в таблице
            unsigned char codeCount = v.size();
            putc(codeCount, oFile);
            //пишем таблицу
            for (int i=0; i<v.size();i++){
                char codeLenght = v[i].code.size();
                unsigned int chCode=0;
                for (int j =0; j<v[i].code.size();j++){
                    chCode = chCode<<1;
                    if (v[i].code[j]=='1') chCode+=1;

                }

                putc(chCode, oFile);
                putc(chCode >> 8, oFile);
                putc(chCode >> 16, oFile);
                putc(chCode >> 24, oFile);
                putc(codeLenght, oFile);

                putc(v[i].color, oFile);

            }

            //cout<<strPixels;
            //заполняем до делимости по 8 символов
            unsigned char mod = strPixels.size()%8;
            for (int i=0; i<mod;i++){
                strPixels+="0";
            }
            //пишем кол-во добавленных в конце символов
            putc(mod, oFile);

            //пишем коды пикселей
            unsigned char ch=0;
            for (int i =0; i<strPixels.size();i++){
                ch = ch<<1;
                if (strPixels[i]=='1') ch+=1;

                if(i>0 && i%8==7){
                    putc(ch, oFile);
                    ch=0;
                }
            }
            break;
        }
    }

    fclose(oFile);

}
void ReadHafFilePixels(ReadBMP &readB,string pixelsName, int mode) {
    ifstream fileStream(pixelsName, ifstream::binary);

    RGBQUAD **rgbInfo = new RGBQUAD *[readB.infoheader.biHeight];
    for (unsigned int i = 0; i < readB.infoheader.biHeight; i++) {
        rgbInfo[i] = new RGBQUAD[readB.infoheader.biWidth];
    }
    switch (mode) {

        case 0: {
            break;
        }
        case 1: {
            unsigned char count;
            read(fileStream, count, 1);
            vector<CodeColor> v;
            //cout<<charToBits(char(170));
            for(int i=0; i<count;i++){
                unsigned char color;
                unsigned char codeLength;
                unsigned int code;
                read(fileStream, code, 4);
                read(fileStream, codeLength, 1);
                read(fileStream, color, 1);
                v.push_back(CodeColor(color,  ClearZero(intToBits(code), codeLength)));
            }

//            for(int i=0; i<v.size();i++){
//                cout<<v[i].code<<"\t"<<(int)v[i].color<<endl;
//            }

            unsigned char mod;
            read(fileStream, mod, 1);
            char buffer;
            string strPixels;
            while(fileStream.read(&buffer,1)){
                strPixels+= charToBits(buffer);
            }
            //cout<<strPixels<<endl;
            //cout<<strPixels.size();
           // cout<<strPixels;
            for(int i=0; i<mod;i++){
                strPixels.pop_back();
            }
            int k=0;
            string search="";
            int h=0;
            int w=0;
            while(k<strPixels.size() && h<=readB.infoheader.biHeight){
                search+=strPixels[k];
                int i=0;
                while(i<v.size() && h<readB.infoheader.biHeight && search!=""){
                   // cout<<h<<" ";
                    if(v[i].code==search){

                        search="";
                        rgbInfo[h][w].grayPixel=v[i].color;
                        w++;
                        if(w==readB.infoheader.biWidth) {
                            h++;
                            w=0;
                        }
                    //cout<<w<<"\t "<<h<<endl;
                    }
                    i++;
                }
                k++;


            }

            break;
        }
    }
    readB.pixels = rgbInfo;
}
string charToBits(char c) {
    // Преобразуем char в int (так как std::bitset работает с целыми числами)
    int i = static_cast<int>(c);
    // Создаем объект std::bitset с размером 8 бит (1 байт)
    std::bitset<8> bits(i);
    // Преобразуем биты в строку

    return bits.to_string();
}
string intToBits(unsigned int c) {
    // Преобразуем char в int (так как std::bitset работает с целыми числами)

    // Создаем объект std::bitset с размером 8 бит (1 байт)
    std::bitset<24> bits(c);
    // Преобразуем биты в строку

    return bits.to_string();
}
string ClearZero(string a, char length){
    string b="";

    for (int i=a.size()-1; i>=a.size()-length;i--){
        b+=a[i];
    }
    string c="";
    for (int i=b.size()-1;i>=0;i--){
        c+=b[i];
    }
    return c;

}





void BubbleSortNodes(vector<Node> &arr)
{
    int i, j;
    for (i = 0; i < arr.size() - 1; i++)

        for (j = 0; j < arr.size() - i - 1; j++)
            if (arr[j].sum > arr[j + 1].sum)
                swap(arr[j], arr[j + 1]);
}
void BubbleSortCodeColors(vector<CodeColor> &arr)
{
    int i, j;
    for (i = 0; i < arr.size() - 1; i++)

        for (j = 0; j < arr.size() - i - 1; j++)
            if (arr[j].color > arr[j + 1].color)
                swap(arr[j], arr[j + 1]);
}

string SearchColor(unsigned char key, vector<CodeColor> v){

    int left = 0;
    int right = v.size()-1;
        while (left <= right) {
            int mid = left + (right - left) / 2; // Предотвращение переполнения

            if (v[mid].color == key) {
                return v[mid].code; // Цель найдена
            } else if (v[mid].color < key) {

                left = mid + 1; // Искать в правой половине
            } else {

                right = mid - 1; // Искать в левой половине
            }
        }
       // cout<<endl;
        return ""; // Цель не найдена


}