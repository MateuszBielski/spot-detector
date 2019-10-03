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
void ReadFilePBM::AddUpValuesToTheirLeftCentersInRows()
{
    for(int r = 0 ; r < sizeY ; r++){
        int first,center,last;
        bool insideDetectedArea = false;
        bool prevInsideDetectedArea = false;
        bool stepInDetectedArea = false;
        bool stepOutDetectedArea = false;
        int sum = 0;
        for(int c = 0; c < sizeX ; c++){
            int currentIndex = c + r * sizeX;
            int& currentElement = dataInt[currentIndex];
            insideDetectedArea = currentElement > 0 ? true : false;
            stepInDetectedArea = !prevInsideDetectedArea && insideDetectedArea;
            stepOutDetectedArea = prevInsideDetectedArea && !insideDetectedArea;
            if(stepInDetectedArea)first = currentIndex;
            
            if(insideDetectedArea){
                sum += currentElement;
                currentElement = 0;
                cout<<" sum: "<<sum;
            }
            if(stepOutDetectedArea){
                last = currentIndex - 1;
                center = (int)floor((last + first)/2.0);
                dataInt[center] = sum;
                sum = 0;
                cout<<" center "<<center;
            }
            prevInsideDetectedArea = insideDetectedArea;
        }
    }
}
