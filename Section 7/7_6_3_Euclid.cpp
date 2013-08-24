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
	MainStructure: ���ṹ
*/
void MainStructure();

/*
	Process
*/
void Process();


/*
	ŷ������㷨
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
	string inputStr = "C:/Users/cao/Desktop/�㷨/Ҫ������/�㷨/2��ս���/input/1.inp";
	//string inputStr = "D:/2��ս���/input/110205.inp";
	string outputStr = "C:/Users/cao/Desktop/�㷨/Ҫ������/�㷨/2��ս���/input/1.outp";
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
	x��y����ȷ����
	���x��y����Ҫ����
		(x+q*k, y-p*k)Ҳ����Ҫ��
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