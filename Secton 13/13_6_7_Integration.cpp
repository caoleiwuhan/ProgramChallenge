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
const double PI = acos(0.0) * 2.0;


/*
	MainStructure: ���ṹ
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
	 double a;
	 string str;
     while(getline(cin, str))
     {
		 if (str == "")
		 {
			 break;
		 }
		 stringstream ss(str);
		 ss >> a;

         double z = ( 1 - sqrt( 3.0 ) / 4.0 - PI / 6.0 ) * a * a;
         double y = ( 1 - PI / 4.0 ) * a * a - 2 * z;
         double x = a * a - 4.0 * ( y + z );
         printf( "%.3f %.3f %.3f\n", x, 4.0 * y, 4.0 * z );
     }    
}

