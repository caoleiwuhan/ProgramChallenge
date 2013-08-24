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

const double EPSILON = 1e-7;


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
	string str;
	while (getline(cin, str))
	{
		if (str == "")
		{
			break;
		}
		double l, w;
		stringstream ss(str);
		ss >> l >> w;

		double ans = (l + w - sqrt(l * l + w * w - l * w)) / 6.0 + EPSILON;
		double res = w;
		if (l < w)
		{
			res = l;
		}
		//res /= 2.0;
		//res += EPSILON;

		printf("%.3lf ", ans);
		printf("%.3lf ", 0.0);
		printf("%.3lf\n", res * 0.5 + EPSILON);

	}

}

