#include <gtest/gtest.h>
#include <string.h>
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