//
// Created by Anton on 05.06.2024.
//
#pragma once
#ifndef PR_4SEM_BMPRW_H
#define PR_4SEM_BMPRW_H

#include "../forAll/forAll.h"

// CIEXYZTRIPLE stuff



// bit extract
unsigned char bitextract(const unsigned int byte, const unsigned int mask);



ReadBMP ReadBMPfile(std::string fileName);
void WriteBMPfile(ReadBMP readBMP, std::string filename, int mode);
void WriteBMPfile(ReadBMP readBMP, std::string filename);

static void write_u16(unsigned short input, FILE* fp);
static void write_u32(unsigned int input, FILE* fp);

#endif //PR_4SEM_BMPRW_H
