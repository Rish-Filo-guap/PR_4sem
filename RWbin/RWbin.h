//
// Created by Anton on 05.06.2024.
//
#pragma once
#ifndef PR_4SEM_RWBIN_H
#define PR_4SEM_RWBIN_H

#include <string>
#include "../forAll/forAll.h"
using namespace std;

void WriteBinFile(ReadBMP readBMP, std::string filename ,int mode);
ReadBMP ReadBinFile(std::string filename);

void ReadFileHeader(ReadBMP &readB,string headerName);
void ReadBinFilePixels(ReadBMP &readB,string pixelsName, int mode);

void WriteBinFilePixels(RGBQUAD** pixels, unsigned int biWidth, unsigned int biHeight, string filename, int mode);
void WriteFileHeader(BITMAPINFOHEADER infoheader, BITMAPFILEHEADER fileheader, string filename, int mode);
#endif //PR_4SEM_RWBIN_H
