#include <iostream>
#include <cstdlib>
#include <vector>
#include <set>
#include <cstring>
#include <fstream>

using namespace std;

#define _MY_DEBUG_


/*
	MainStructure: ���ṹ
*/
void MainStructure();





int main()
{
	MainStructure();
	return 0;
}

void MainStructure()
{
	
#ifdef _MY_DEBUG_
	string inputStr = "C:/Users/cao/Desktop/�㷨/Ҫ������/�㷨/2��ս���/input/110201.inp";
	//string inputStr = "D:/2��ս���/input/110203.inp";
	string outputStr = "C:/Users/cao/Desktop/�㷨/Ҫ������/�㷨/2��ս���/input/0000001.outp";
	ifstream fin;
	fin.open(inputStr);	

	cin.rdbuf(fin.rdbuf());	

	ofstream fout;
	fout.open(outputStr);

	//cout.rdbuf(fout.rdbuf());

#endif
		
}


