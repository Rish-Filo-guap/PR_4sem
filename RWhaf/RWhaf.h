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
    char color=-1;
    Node* r;
    Node* l;

    Node(){};

    void SetNodeL(Node left){
        *l = left;
    }
    void SetNodeR(Node right){
        *r = right;
    }
    void SetNodeL(Pcolor left){
        l->sum = left.probability;
        l->color = left.color;
    }
    void SetNodeR(Pcolor right){
        r->sum = right.probability;
        r->color = right.color;
    }
    void CalcSum(){

        sum = r->sum+l->sum;
    }


};





#endif //PR_4SEM_RWHAF_H
