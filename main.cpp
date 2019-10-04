//#include <stdio.h>
#include <iostream>
#include <ReadFile/ReadFilePBM.h>

using namespace std;

int main(int argc, char **argv)
{
	ReadFilePBM fileToTest;
    fileToTest.OpenFile("../kropki.pbm");
    cout<<fileToTest.CalculatedRadius();
	return 0;
}
