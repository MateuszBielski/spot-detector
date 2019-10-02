#ifndef READFILEPBM_H
#define READFILEPBM_H

#include <string>
#include <fstream>

using namespace std;

class ReadFilePBM {
public:
    ~ReadFilePBM();
    bool OpenFile(string name);
    void ReadData();
    bool isOpen();
    int getSizeX();
    void ConvertDataToIntArrayXY();
private:
    std::ifstream ifs;
    int sizeX, sizeY;
    
};

#endif