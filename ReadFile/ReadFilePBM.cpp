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
    AddUpValues([this](int b, int a){return a + b * sizeX;});
}
void ReadFilePBM::AddUpValuesToTheirUpCentersInColumns()
{
    AddUpValues([this](int a, int b){return a + b * sizeX;});
}

void ReadFilePBM::AddUpValues(CalculateIndex calculateIndex)
{
    for(int j = 0 ; j < sizeX ; j++){
        int first,center,last;
        bool insideDetectedArea = false;
        bool prevInsideDetectedArea = false;
        bool stepInDetectedArea = false;
        bool stepOutDetectedArea = false;
        int sum = 0;
        for(int k = 0; k < sizeY ; k++){
            int& currentElement = dataInt[calculateIndex(j,k)];
            insideDetectedArea = currentElement > 0 ? true : false;
            stepInDetectedArea = !prevInsideDetectedArea && insideDetectedArea;
            stepOutDetectedArea = prevInsideDetectedArea && !insideDetectedArea;
            if(stepInDetectedArea)first = k;
            
            if(insideDetectedArea){
                sum += currentElement;
                currentElement = 0;
            }
            if(stepOutDetectedArea){
                last = k - 1;
                center = (int)floor((last + first)/2.0);
                dataInt[calculateIndex(j,center)] = sum;
                sum = 0;
            }
            prevInsideDetectedArea = insideDetectedArea;
        }
    }
}
string ReadFilePBM::CalculatedRadius()
{
    ReadData();
    AddUpValuesToTheirLeftCentersInRows();
    AddUpValuesToTheirUpCentersInColumns();
    string result;
    std::for_each(dataInt.begin(), dataInt.end(), [this](int n) { if(n > 0)radius.push_back((int)ceil(sqrt(n/3.14))); });
    std::for_each(radius.begin(),radius.end(),[&result](int n){result +=std::to_string(n)+','; });
    return result;
}
