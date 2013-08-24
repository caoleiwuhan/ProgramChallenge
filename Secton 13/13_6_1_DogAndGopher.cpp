#include <iostream>
#include <cstdlib>
#include <vector>
#include <map>
#include <string>
#include <cstring>
#include <fstream>
#include <cassert>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include <queue>
#include <hash_map>


using namespace std;

//#define _MY_DEBUG_

const int MAX_PORT_NUM = 1001;

long long ports[MAX_PORT_NUM][2];


/*
	MainStructure: 主结构
*/
void MainStructure();

/*
	Process
*/
void Process();

bool IsGhohperCanEscape(long long ghX, long long ghY, 
	long long dogX, long long dogY, int index);


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
	string str;
	while (getline(cin, str))
	{
		if (str == "")
		{
			break;
		}
		int portNum;
		long long gopherX, gopherY;
		long long dogX, dogY;
		stringstream ss(str);
		double tmpX, tmpY;
		ss >> portNum >> tmpX >> tmpY;
		gopherX = (long long)(tmpX * 1000);
		gopherY = (long long)(tmpY * 1000);
		ss >> tmpX >> tmpY;
		dogX = (long long)(tmpX * 1000);
		dogY = (long long)(tmpY * 1000);

		for (int i = 0; i < portNum; ++i)
		{
			cin >> tmpX >> tmpY;
			ports[i][0] = (long long)(tmpX * 1000);
			ports[i][1] = (long long)(tmpY * 1000);
		}
		cin.ignore();
		cin.ignore();

		bool isEscape = false;
		for (int i = 0; i < portNum; ++i)
		{
			if (IsGhohperCanEscape(gopherX, gopherY, dogX, dogY, i))
			{
				double ansX = ((double)ports[i][0]) / 1000;
				double ansY = ((double)ports[i][1]) / 1000;
				printf("The gopher can escape through the hole at (%.3lf,%.3lf).\n", ansX, ansY);	
				isEscape = true;
				break;
			}			
		}
		if (!isEscape)
		{
			cout << "The gopher cannot escape." << endl;
		}
	}
}

bool IsGhohperCanEscape(long long ghX, long long ghY, long long dogX, 
	long long dogY, int index)
{
	long long portX = ports[index][0];
	long long portY = ports[index][1];

	long long ghLen = (ghX - portX) * (ghX - portX) + (ghY - portY) * (ghY - portY);
	long long dogLen = (dogX - portX) * (dogX - portX) + (dogY - portY) * (dogY - portY);

	if (4 * ghLen <= dogLen)
	{
		return true;
	}
	return false;
}