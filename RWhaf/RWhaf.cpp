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
               // cout<<i<<")\t"<<a[i]<<endl;
            }
            vector<Node> p;

            for(int i=0; i<=255;i++){
                if (a[i]!=0){
                    Node n;
                    n.color =i;
               //     cout<<"n"<<n.color<<endl;
                    n.sum = a[i];
                    n.havecolor=true;
                    p.push_back(n);
                //Pcolor b = Pcolor(i, a[i]);
                //cout<<(int)b.color<<endl;

                }
            }
            cout<<endl;
            BubbleSortNodes(p);
            for (int i=0; i<p.size();i++){
               // cout<<(int)p[i].color<<endl;
               //cout<<<<endl;
                cout<<(int)p[i].color<<")\t"<<p[i].sum<<endl;
            }

            cout<<endl;

            Node *w = new Node();
            Node *wr = new Node();
            wr->color=3;
            wr->sum=2;
            Node *wl = new Node();
            wl->sum=6;
            wl->color=4;
            w->SetNodes(*wl, *wr);
            cout<<(int)w->r->color;
            cout<<endl;
            cout<<(int)w->l->color;
            cout<<endl;




            while (p.size()>1){
                Node *n = new  Node();
                //cout<<"#"<<p.size()<<endl;
                n->SetNodes(p[0],p[1]);
                p.erase(p.cbegin());
                p.erase(p.cbegin());
                p.push_back(*n);
               // cout<<(int)n->r->color<<"\t "<<(int)n->l->color<<endl;
               // cout<<(int)n->r->havecolor<<"\t "<<(int)n->l->havecolor<<endl;
                BubbleSortNodes(p);
//                for (int i=0; i<p.size();i++){
//                    cout<<")\t"<<p[i].sum<<endl;
//                }
//                cout<<"@"<<endl;
            }
//            cout<<"#"<<p.size()<<endl;
//            cout<<endl;
//            cout<<"1 "<<(int)p[0].l->color<<"\t"<<p[0].l->havecolor<<endl;
//
//            cout<<"2 "<<(int)p[0].r->l->color<<"\t"<<p[0].r->l->havecolor<<endl;
//            cout<<"3 "<<(int)p[0].r->r->color<<"\t"<<p[0].r->r->havecolor<<endl;
//
//            cout<<"4 "<<(int)p[0].r->r->r->color<<"\t"<<p[0].r->r->r->havecolor<<endl;
//            cout<<"4 "<<(int)p[0].r->r->l->color<<"\t"<<p[0].r->r->l->havecolor<<endl;

            //cout<<"4"<<(int)p[0].l->l->color<<"\t"<<p[0].l->l->havecolor<<endl;
            //cout<<(int)p[0].l->r->color<<"\t"<<p[0].r->r->havecolor<<endl;
            p[0].GetCodes("");
            cout<<endl;
            p[0].GetCodeint(0);
            vector<CodeColor> v;
            p[0].GetCodeVector(0, v);
            cout<<endl;
            for(int i = 0; i<v.size();i++){
                cout<<v[i].code<<"\t"<<(int)v[i].color<<endl;

            }
            BubbleSortCodeColors(v);
            cout<<endl;
            for(int i = 0; i<v.size();i++){
                cout<<v[i].code<<"\t"<<(int)v[i].color<<endl;

            }
            cout<<endl;
            cout<<SearchColor(v[1].color,v);
            break;
        }
    }

    fclose(oFile);

}
void ReadHafFilePixels(ReadBMP &readB,string pixelsName, int mode) {

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

int SearchColor(unsigned char key, vector<CodeColor> v){

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
        cout<<endl;
        return -1; // Цель не найдена


}