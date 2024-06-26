//
// Created by Anton on 26.06.2024.
//
#pragma once
#ifndef PR_4SEM_RWRLE_H
#define PR_4SEM_RWRLE_H

#include <string>
#include "../forAll/forAll.h"
using namespace std;

void WriteRLEFile(ReadBMP readBMP, std::string filename ,int mode);
void WriteRLEFilePixels(RGBQUAD** pixels, unsigned int biWidth, unsigned int biHeight, string filename, int mode);

ReadBMP ReadRLEFile(std::string filename);
void ReadRLEFilePixels(ReadBMP &readB,string pixelsName, int mode);
#endif //PR_4SEM_RWRLE_H
