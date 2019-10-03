#ifndef READFILEPBM_H
#define READFILEPBM_H

#include <string>
#include <fstream>
#include <cmath>

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
    void AddUpValuesToTheirLeftCentersInRows();
private:
    std::ifstream ifs;
    int sizeX, sizeY;
    char * data = nullptr;
    std::vector<int> dataInt;
};

#endif