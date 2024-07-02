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
void BubbleSort(vector<Pcolor> &arr);



#endif //PR_4SEM_RWHAF_H
