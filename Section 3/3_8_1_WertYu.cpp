#include <iostream>
#include <cstdlib>
#include <vector>
#include <set>
#include <string>
#include <fstream>

using namespace std;

//#define _MY_DEBUG_

/*
	MainStructure: 主结构
*/
void MainStructure();

/*
	Process：处理每一组数据
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
	string outputStr = "C:/Users/cao/Desktop/算法/要看的书/算法/2挑战编程/input/0000001.outp";
	ifstream fin;
	fin.open(inputStr);	

	cin.rdbuf(fin.rdbuf());	

	//ofstream fout;
	//fout.open(outputStr);
	//cout.rdbuf(fout.rdbuf());
#endif

	Process();		
}

void Process()
{
	// cout << "Test" << endl;
	// 搞清楚都有哪些字母是合法的！
	// 可能有多行！
	string keys = "1234567890-=WERTYUIOP[]SDFGHJKL;'XCVBNM,./ \\";
	string maps = "`1234567890-QWERTYUIOP[ASDFGHJKL;ZXCVBNM,. ]";

	string input;

	while (getline(cin, input))
	{
		if (input == "")
		{
			break;
		}
		string outputs;
		// 逐个解析input中的字母
		int index = 0;
		int len = input.size();
		while (index < len)
		{
			// 得到
			char ch = input[index++];
			size_t pos = keys.find(ch);
			if (pos != string::npos)
			{
				outputs.append(1, maps[pos]);
			}
			else
			{
				outputs.append(1, ch);
			}
		}
		cout << outputs << endl;
	}
}
//
//void Process()
//{
//	string keys = "1234567890-=WERTYUIOP[]SDFGHJKL;'XCVBNM,./ \\";
//	string maps = "`1234567890-QWERTYUIOP[ASDFGHJKL;ZXCVBNM,. ]";
//	string ss = "`1234567890-=QWERTYUIOP[]\\ASDFGHJKL;'ZXCVBNM,./";
//
//	//string input;
//
//	//while (getline(cin, input))
//	//{
//	//	string outputs;
//	//	// 逐个解析input中的字母
//	//	int index = 0;
//	//	int len = input.size();
//	//	while (index < len)
//	//	{		
//	//		if (input[index] == ' ')
//	//		{
//	//			cout << ' ';
//	//		}
//	//		else
//	//		{
//	//			cout << ss[ss.find_first_of(input[index]) - 1];
//	//		}
//	//		++index;
//	//	}
//	//		
//	//	cout << endl;
//	//}
//
//	string keyboard = "`1234567890-=QWERTYUIOP[]\\ASDFGHJKL;'ZXCVBNM,./";  
//	   string line;  
//
//		while(getline(cin, line))  
//		{  
//			for (int i = 0; i < line.length(); i++)  
//			{
//				if (line[i] == ' ')  
//				{
//					cout << " ";  
//				}
//				else  
//				{
//					cout << keyboard[keyboard.find_first_of(line[i]) - 1];  
//				}        
//			}
//			cout << endl;  
//		}  
//}