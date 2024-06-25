#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <sstream>
#include <chrono>
#include <thread>
#include "RWbmp/RWbmp.h"
#include "RWbin/RWbin.h"
using namespace std;

int main()
{
    ReadBMP binread;
    ReadBMP read;
    auto start = chrono::system_clock::now();
    for (int i = 1; i < 15; i++) {

    stringstream ss;
    ss << i;
    string name=ss.str();
    ss<<".bmp";
    string filename = ss.str();

    cout << ss.str()<< endl;


	read = ReadBMPfile(filename);
    WriteBinFile(read, name, 1);


    binread = ReadBinFile(name);



    //thread th(WriteBMPfile,read, filename, 0);
   // cout<<filename<<"))"<<endl;
    //WriteBMPfile(read, "wb_"+filename, 1);

    WriteBMPfile(binread,"new_" +filename);


   // th.join();

    }
    auto end = chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    cout <<endl<< elapsed_seconds.count()<<endl;
}
