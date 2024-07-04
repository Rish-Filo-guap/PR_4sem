//
// Created by Anton on 04.07.2024.
//
#pragma once
#ifndef PR_4SEM_RWARI_H
#define PR_4SEM_RWARI_H

#include <string>
#include <vector>
#include "../forAll/forAll.h"

void WriteAriFile(ReadBMP readBMP, std::string filename, int mode);
void WriteAriFilePixels(RGBQUAD** pixels, unsigned int biWidth, unsigned int biHeight, string filename, int mode);

ReadBMP ReadAriFile(std::string filename);
void ReadAriFilePixels(ReadBMP &readB,string pixelsName, int mode);

struct PColor{
    unsigned char color;
    int probability;
//    PColor(char color, int probability){
//        this->color = color;
//        this->probability= probability;
//
//    }
};

#endif //PR_4SEM_RWARI_H
