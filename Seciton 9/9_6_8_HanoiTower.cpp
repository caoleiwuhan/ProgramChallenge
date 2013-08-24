//#include <iostream>
//#include <cstdlib>
//#include <vector>
//#include <map>
//#include <string>
//#include <cstring>
//#include <fstream>
//#include <cassert>
//#include <cmath>
//#include <iomanip>
//#include <algorithm>
//#include <sstream>
//#include <queue>
//#include <hash_map>
//
//
//using namespace std;
//
//#define _MY_DEBUG_
//
//const int MAXV = 60;
//
//// ÿһ�������ϵ���
//int towers[MAXV];
//
//// ��������
//int nTower = 0;
//
//// ���
//int ans = 0;
//
//
//
///*
//	MainStructure: ���ṹ
//*/
//void MainStructure();
//
///*
//	Process
//*/
//void Process();
//
///*
//	curNum:��ǰ���ڴ������
//	curTower:��ǰ�Ѿ�ʹ�õ�������
//*/
//void dfs(int curNum, int curTower);
//
///*
//	�ж��Ƿ������
//		�����Ѿ����꣬�Ҳ�������Ҫ��
//*/
//bool IsFinished(int curNum, int curTower);
//
///*
//	�ж�һ�����Ƿ�����ȫƽ��
//*/	
//bool IsNumSqrt(int num);
//
//
//int main()
//{
//	MainStructure();
//	return 0;
//}
//
//
//void MainStructure()
//{
//	
//#ifdef _MY_DEBUG_
//	string inputStr = "C:/Users/cao/Desktop/�㷨/Ҫ������/�㷨/2��ս���/input/1.inp";
//	//string inputStr = "D:/2��ս���/input/110205.inp";
//	string outputStr = "C:/Users/cao/Desktop/�㷨/Ҫ������/�㷨/2��ս���/input/1.outp";
//	ifstream fin;
//	fin.open(inputStr);		
//
//	cin.rdbuf(fin.rdbuf());	
//
//	/*
//	ofstream fout;
//	fout.open(outputStr.c_str());
//	cout.rdbuf(fout.rdbuf());
//	*/
//
//#endif
//
//	Process();
//			
//}
//void Process()
//{
//	int count = 0;
//	cin >> count;
//	while (count--)
//	{
//		cin >> nTower;
//		memset(towers, 0, sizeof(towers));
//		ans = 0;
//		dfs(1, 0);
//		cout << ans << endl;
//	}
//}
//
//void dfs(int curNum, int curTower)
//{
//	if (IsFinished(curNum, curTower))
//	{
//		// ��ǰ����£���õĽ������tmp
//		int tmp = curNum - 1;
//		if (tmp > ans)
//		{
//			ans = tmp;
//		}
//		return;
//	}
//	// ѡȡ
//	for (int i = 0; i < curTower; ++i)
//	{
//		int curTmp = towers[i];
//		if (IsNumSqrt(curTmp + curNum))
//		{
//			towers[i] = curNum;
//			dfs(curNum + 1, curTower);
//			towers[i] = curTmp;
//		}		
//	}
//	// �����ŵ�һ���µ�tower��
//	if (curTower < nTower)
//	{
//		towers[curTower] = curNum;
//		dfs(curNum + 1, curTower + 1);
//	}
//}
//
//bool IsFinished(int curNum, int curTower)
//{
//	if (curTower < nTower)
//	{
//		return false;
//	}
//	for (int i = 0; i < curTower; ++i)
//	{
//		if (IsNumSqrt(towers[i] + curNum))
//		{
//			return false;
//		}
//	}
//	return true;
//}
//
//bool IsNumSqrt(int num)
//{
//	int s = sqrt(double(num));
//	if (s * s == num)
//	{
//		return true;
//	}
//	return false;
//}

#include<cstdio>

int main()
{
	int n,t;
	scanf("%d",&t);
	for(int i=1;i<=t;++i)
	{
		scanf("%d",&n);
		if(n==1)
		printf("1\n");
		else
		{
			int sum=1,temp=2;
			for(int j=2;j<=n;++j)
			{
				if(j%2==1)
				temp+=2;
				sum+=temp;
			}
			printf("%d\n",sum);
		}
	}
	return 0;
}


