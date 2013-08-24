#include <iostream>
#include <cstdlib>
#include <vector>
#include <set>
#include <string>
#include <cstring>
#include <fstream>
#include <cassert>
#include <cmath>

using namespace std;

//#define _MY_DEBUG_

/*
	MainStructure: 主结构
*/
void MainStructure();

/*
	Process
*/
void Process();


/*
	欧几里得算法
*/
long gcd(long p, long q, long *x, long *y);

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
	unsigned a, b;
	while (cin >> a >> b)
	{
		long x, y;
		long ans = gcd(a, b, &x, &y);
		cout << x << ' ' << y << ' ' << ans << endl;
	}
}

/*
	x、y不是确定的
	如果x、y符合要求，则：
		(x+q*k, y-p*k)也符合要求
*/
long gcd(long p, long q, long *x, long *y)
{
	long x1, y1;
	long g;
	if (q > p)
	{
		return gcd(q, p, y, x);
	}

	if (q == 0)
	{
		*x = 1;
		*y = 0;
		return p;
	}

	g = gcd(q, p % q, &x1, &y1);
	*x = y1;
	*y = (x1 - long(p / (double)q) * y1);

	return g;
}