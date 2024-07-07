#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <sstream>
#include <chrono>
#include <thread>
//#include "forAll/forAll.h"
#include "RWbmp/RWbmp.h"
#include "RWbin/RWbin.h"
#include "RWrle/RWrle.h"
#include "RWhaf/RWhaf.h"

using namespace std;

int main()
{
    ReadBMP binread;
    ReadBMP rleread;
    ReadBMP hafread;
    ReadBMP read;
    auto start = chrono::system_clock::now();
  //  for (int i = 12; i <= 26; i++) {
    int i =26;
    stringstream ss;
    ss << i;
    string name=ss.str();
    ss<<".bmp";
    string filename = ss.str();

    cout << ss.str()<< endl;


	read = ReadBMPfile(filename);
    WriteBinFile(read, name, 1);
    binread = ReadBinFile(name);
    WriteBMPfile(binread,"bin_" +filename);

    WriteHafFile(read, name, 1);
    hafread = ReadHafFile(name);
    WriteBMPfile(hafread,"haf_" +filename);

    WriteRLEFile(read, name, 1);
    rleread = ReadRLEFile(name);
    WriteBMPfile(rleread, "rle_"+filename, 1);

    //thread th(WriteBMPfile,read, filename, 0);
   // cout<<filename<<"))"<<endl;
    //WriteBMPfile(read, "wb_"+filename, 1);

    //rleread = ReadRLEFile(name);
    //WriteBMPfile(rleread,"rle_" +filename);


   // th.join();
       // _sleep(1000);
   // }
    auto end = chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    cout <<endl<< elapsed_seconds.count()<<endl;
}
