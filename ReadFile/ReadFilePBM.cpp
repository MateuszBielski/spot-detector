#include "ReadFilePBM.h"
bool ReadFilePBM::OpenFile(string name)
{
    ifs.open(name);
//    ReadData();
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
    if(data != nullptr) {
        delete [] data;
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

    sizeX = stoi(params[0]);
    sizeY = stoi(params[1]);
    
    int dataSize = 2 * sizeX * sizeY;
    data = new char[dataSize];
    ifs.read(data, dataSize);
    
    ifs.close();
    char * dataAgregated = new char[dataSize/2];
    for(int i = 0 ; i < dataSize/2 ; i++)
    {
        dataAgregated[i] = data[i*2];
    }
    delete [] data;
    data = dataAgregated;
    ConvertDataToInt();
}

char* ReadFilePBM::RawData()
{
    return data;
}
void ReadFilePBM::ConvertDataToInt()
{
    for(int i = 0; i < sizeX * sizeY ; i++){
        char acell = data[i];
        dataInt.push_back(atoi(&acell));
    }
}
std::vector<int> ReadFilePBM::DataInt()
{
    return dataInt;
}
