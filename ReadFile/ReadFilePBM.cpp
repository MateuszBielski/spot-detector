#include "ReadFilePBM.h"
bool ReadFilePBM::OpenFile(string name)
{
    ifs.open(name);
    ReadData();
    return ifs.is_open();
}
int ReadFilePBM::getSizeX()
{
    return sizeX;
}
bool ReadFilePBM::isOpen()
{
    return ifs.is_open();
}
ReadFilePBM::~ReadFilePBM()
{
    if (ifs.is_open()) {
        ifs.close();
    }
}
void ReadFilePBM::ReadData()
{
    string firstLine, secondLine;
    getline(ifs, firstLine);
    getline(ifs,secondLine);
    string param;
    stringstream ss(secondLine);
    std::vector<std::string> params;
    while (getline(ss, param, (char)0x9)) {
        params.push_back(param);
    }
//    printf("%d ",(int)params.size());
    sizeX = stoi(params[0]);
    sizeY = stoi(params[1]);
    
    string nextLine;
    while (getline(ifs,nextLine))
    {
        
    }
}

