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
    ASSERT_EQ(10,fileToTest.getSizeX());
}

TEST(FileBPM,ConvertDataToIntArrayXY)
{
    ReadFilePBM fileToTest;
    fileToTest.OpenFile(nameTestedFile);
    string result;
//    fileToTest.ConvertDataToIntArrayXY();
//    reusult = 
    ASSERT_EQ("0001111000",result);
    
}