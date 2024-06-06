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
    //cout<<"\t bmp read";
    WriteBinFile(read, name);
    //cout<<"\t bin write";


    binread = ReadBinFile(name);
    //cout<<"\t bin read";



    thread th(WriteBMPfile,read, filename);
    //WriteBMPfile(read, filename);

    WriteBMPfile(binread,"new_" +filename);
    //cout<<"\t bmps write"<<endl;


    th.join();

    }
    auto end = chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    cout <<endl<< elapsed_seconds.count()<<endl;
}