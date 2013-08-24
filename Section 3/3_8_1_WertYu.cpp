#include <iostream>
#include <cstdlib>
#include <vector>
#include <set>
#include <string>
#include <fstream>

using namespace std;

//#define _MY_DEBUG_

/*
	MainStructure: ���ṹ
*/
void MainStructure();

/*
	Process������ÿһ������
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
	string outputStr = "C:/Users/cao/Desktop/�㷨/Ҫ������/�㷨/2��ս���/input/0000001.outp";
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
	// �����������Щ��ĸ�ǺϷ��ģ�
	// �����ж��У�
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
		// �������input�е���ĸ
		int index = 0;
		int len = input.size();
		while (index < len)
		{
			// �õ�
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
//	//	// �������input�е���ĸ
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