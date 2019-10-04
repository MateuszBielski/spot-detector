#ifndef READFILEPBM_H
#define READFILEPBM_H

#include <string>
#include <fstream>
#include <cmath>
#include <functional>
#include <sstream>

using namespace std;

typedef std::function<int(int,int)> CalculateIndex;

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
    void AddUpValuesToTheirUpCentersInColumns();
    string CalculatedRadius();
private:
    std::ifstream ifs;
    int sizeX, sizeY;
    char * data = nullptr;
    std::vector<int> dataInt, radius;
    
    
    void AddUpValues(CalculateIndex);
};

#endif