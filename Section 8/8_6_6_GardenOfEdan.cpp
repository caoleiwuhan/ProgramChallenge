#include <iostream>
#include <cstdlib>
#include <vector>
#include <set>
#include <string>
#include <cstring>
#include <fstream>
#include <cassert>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include <sstream>

using namespace std;

#define _MY_DEBUG_

/*
	MainStructure: 主结构
*/
void MainStructure();

/*
	Process
*/
void Process();


int main()
{
	MainStructure();
	return 0;
}


void MainStructure()
{
	
#ifdef _MY_DEBUG_
	string inputStr = "C:/Users/cao/Desktop/算法/要看的书/算法/2挑战编程/input/1.inp";
	//string inputStr = "D:/2挑战编程/input/110205.inp";
	string outputStr = "C:/Users/cao/Desktop/算法/要看的书/算法/2挑战编程/input/1.outp";
	ifstream fin;
	fin.open(inputStr);		

	cin.rdbuf(fin.rdbuf());	

	/*
	ofstream fout;
	fout.open(outputStr.c_str());
	cout.rdbuf(fout.rdbuf());
	*/

#endif

	Process();
			
}
void Process()
{
	// 自动机编号
	int aNum = 0;
	// 字符长度
	int sLen = 0;
	string str;
	string codeStr;
	while (getline(cin, str))
	{
		if (str == "")
		{
			break;
		}
		stringstream ss(str);
		ss >> aNum >> sLen >> codeStr;


	}
}

