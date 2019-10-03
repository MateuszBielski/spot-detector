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
    void ConvertDataToInt();
    char* RawData();
    std::vector<int> DataInt();
private:
    std::ifstream ifs;
    int sizeX, sizeY;
    char * data = nullptr;
    std::vector<int> dataInt;
};

#endif