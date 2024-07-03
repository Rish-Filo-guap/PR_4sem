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

struct CodeColor{
    unsigned char color;
    int code;
    CodeColor(char color, int code){
        this->color = color;
        this->code= code;

    }
};
class Node;
void BubbleSortNodes(vector<Node> &arr);
void BubbleSortCodeColors(vector<CodeColor> &arr);
int SearchColor(unsigned char color, vector<CodeColor> v);

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
       r = new Node;
        *r = right;
        //cout<<"!";
        l = new Node;
        *l = left;
       // cout<<"!";
        sum = r->sum+l->sum;
    }
    void GetCodes(string code){
        if(havecolor) {
        cout<<code<<"\t"<<(int)color<<endl;
        return;
        }

        else{
            if (l!=NULL)
            l->GetCodes(code+"0");

            if (r!=NULL)
            r->GetCodes(code+"1");

        }

    }
    void GetCodeint(int code){
        if(havecolor) {
            cout<<code<<"\t"<<(int)color<<endl;
            return;
        }

        else{
            if (l!=NULL)
                l->GetCodeint(code<<1);

            if (r!=NULL)
                r->GetCodeint((code<<1) + 1);

        }

    }
    void GetCodeVector(int code, vector<CodeColor> &v){
        if(havecolor) {
            CodeColor a = CodeColor(color,code);
            v.push_back(a);

            //cout<<code<<"!!\t"<<(int)color<<endl;
            return;
        }

        else{
            if (l!=NULL)
                l->GetCodeVector(code<<1, v);

            if (r!=NULL)
                r->GetCodeVector((code<<1) + 1, v);

        }

    }

};





#endif //PR_4SEM_RWHAF_H
