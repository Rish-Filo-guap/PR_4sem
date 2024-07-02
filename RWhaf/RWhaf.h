//
// Created by Anton on 02.07.2024.
//
#pragma once
#ifndef PR_4SEM_RWHAF_H
#define PR_4SEM_RWHAF_H

#include <string>
#include <vector>
#include "../forAll/forAll.h"

void WriteHafFile(ReadBMP readBMP, std::string filename, int mode);
void WriteHafFilePixels(RGBQUAD** pixels, unsigned int biWidth, unsigned int biHeight, string filename, int mode);

ReadBMP ReadHafFile(std::string filename);
void ReadHafFilePixels(ReadBMP &readB,string pixelsName, int mode);

struct Pcolor{
    unsigned char color;
    int probability;
    Pcolor(char color, int probability){
        this->color = color;
        this->probability= probability;

    }
};
class Node;
void BubbleSort(vector<Node> &arr);

class Node{
public:
    int sum;
    unsigned char color;
    bool havecolor = false;
    Node* r=NULL;
    Node* l=NULL;

    Node(){};

    void SetNodes(Node left, Node right){
       // cout<<"!";
        r = &right;
        //cout<<"!";
        l = &left;
       // cout<<"!";
        sum = r->sum+l->sum;
    }
    void GetCodes(string code){
        if(havecolor) {
        cout<<code<<"!!\t"<<(int)color<<endl;
        return;
        }

        else{
            if (l!=NULL)
            l->GetCodes(code+"0");

            if (r!=NULL)
            r->GetCodes(code+"1");

        }

    }


};





#endif //PR_4SEM_RWHAF_H
