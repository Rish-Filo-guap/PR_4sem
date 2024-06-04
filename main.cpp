#include <iostream>
#include <fstream>
#include <cstring>
#include <string.h>
#include <sstream>
#include "bmpRW.h"
using namespace std;
ReadBMP ReadBMPfile(const char* fileName);
void WriteBMPfile(ReadBMP readBMP);
int main()
{
    ReadBMP read;

    for (int i = 1; i < 15; i++) {
    stringstream ss;
    ss << i<<".bmp";
    string b = ss.str();
    const char* a = b.c_str();
    cout <<"!" << ss.str()<< endl;
	read = ReadBMPfile(b.c_str());
    WriteBMPfile(read);

    }

}