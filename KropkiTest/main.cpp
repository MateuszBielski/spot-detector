#include <gtest/gtest.h>
#include <string.h>
#include <algorithm>
#include "../ReadFile/ReadFilePBM.cpp"

using namespace std;

#define nameTestedFile "../kropkiTest10x10.pbm"//

int main(int argc, char **argv)
{
	testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
    
}
bool OpenFile(string name){
    return true;
}

//TEST(OpenFile, PreparationsCompleted)
//{
//    GTEST_FAIL();
//}

TEST(OpenFile,isOpenedAndClosed)
{
    ReadFilePBM fileToTest;
    ASSERT_EQ(true,fileToTest.OpenFile(nameTestedFile));
    fileToTest.~ReadFilePBM();
    ASSERT_FALSE(fileToTest.isOpen());
}
TEST(OpenFilePBM,ReadSize)
{
    ReadFilePBM fileToTest;
    fileToTest.OpenFile(nameTestedFile);
    fileToTest.ReadData();
    ASSERT_EQ(10,fileToTest.getSizeX());
}

TEST(FileBPM,DataLoadedCorrectly)
{
    ReadFilePBM fileToTest;
    fileToTest.OpenFile(nameTestedFile);
    fileToTest.ReadData();
    string result (fileToTest.RawData()+3*10,(size_t)10);
    ASSERT_EQ("0001111000",result);
}

TEST(FileBPM,ConvertDataToInt)
{
    ReadFilePBM fileToTest;
    fileToTest.OpenFile(nameTestedFile);
    fileToTest.ReadData();
    auto data = fileToTest.DataInt();
    int result = 0;
    for(int i = 30 ; i < 40 ; i++)result += data[i];
    ASSERT_EQ(4,result);
}

TEST(FileBPM,AddUpInRows)
{
    ReadFilePBM fileToTest;
    fileToTest.OpenFile(nameTestedFile);
    fileToTest.ReadData();
    fileToTest.AddUpValuesToTheirLeftCentersInRows();
    auto data = fileToTest.DataInt();
    string result ("");
    for(int i = 30 ; i < 40 ; i++)result += std::to_string(data[i]);
    ASSERT_EQ("0000400000",result);
}
TEST(FileBPM,AddUpInRowsMultipleAreas)
{
    ReadFilePBM fileToTest;
    fileToTest.OpenFile("../kropkiTest12x12.pbm");
    fileToTest.ReadData();
    fileToTest.AddUpValuesToTheirLeftCentersInRows();
    auto data = fileToTest.DataInt();
    string result ("");
    for(int i = 3*12 ; i < 4*12 ; i++)result += std::to_string(data[i]);
    ASSERT_EQ("000400000300",result);
}
TEST(FileBPM,AddUpInColumnsMultipleAreas)
{
    ReadFilePBM fileToTest;
    fileToTest.OpenFile("../kropkiTest12x12.pbm");
    fileToTest.ReadData();
    fileToTest.AddUpValuesToTheirUpCentersInColumns();
    auto data = fileToTest.DataInt();
    string result ("");
    for(int i = 0 ; i < 12 ; i++)result += std::to_string(data[6+i*12]);
    ASSERT_EQ("000020004000",result);
}
TEST(FileBPM,CountedAreasInCenters)
{
    ReadFilePBM fileToTest;
    fileToTest.OpenFile("../kropkiTest12x12.pbm");
    fileToTest.ReadData();
    fileToTest.AddUpValuesToTheirLeftCentersInRows();
    fileToTest.AddUpValuesToTheirUpCentersInColumns();
    auto data = fileToTest.DataInt();
    string result ("");
    auto writeAppend = [&result](int n) { if(n > 0)result += std::to_string(n)+','; };
    std::for_each(data.begin(), data.end(), writeAppend);
    ASSERT_EQ("5,24,12,",result);
}