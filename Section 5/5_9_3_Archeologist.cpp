#include <iostream>
#include <cstdlib>
#include <vector>
#include <set>
#include <string>
#include <cstring>
#include <fstream>
#include <cassert>
#include <stack>


using namespace std;

#define _MY_DEBUG_


const int MAX_INT_LENGTH = 10000;
/*
	数据结构
*/
struct BigNum
{
	unsigned int arr[MAX_INT_LENGTH];	// 保存每一位
	int length;							// 个数长度
	
	BigNum()
	{ // 默认为0，因此长度为1
		length = 1;
		memset(arr, 0, sizeof(arr));

	}
	BigNum(unsigned int num)
	{
		memset(arr, 0, sizeof(arr));
		(*this) = num;
	}

	BigNum operator = (unsigned int num)
	{
		int count = 0;
		while (num > 0)
		{
			arr[count++] = num % 10;
			num /= 10;
		}
		length = count;
		return (*this);
	}
	// 乘以2操作
	BigNum operator *= (unsigned int num)
	{
		if (length == 1 && arr[0] == 0)
		{
			return (*this);
		}
		int count = length;
		int carry = 0;
		for (int i = 0; i <= count; ++i)
		{
			unsigned tmp = arr[i] * num;
			tmp += carry;
			arr[i] = tmp % 10;
			carry = tmp / 10;
		}
		if (arr[count])
		{
			++length;
		}

		return (*this);
	}

	unsigned ConverToUInt()
	{
		unsigned num = 0;
		for (int i = length - 1; i >= 0; --i)
		{
			num = num * 10 + arr[i];
		}
		return num;
	}

	void PrintNum()
	{
		for (int i = length - 1; i >= 0; --i)
		{
			cout << char('0' + arr[i]);			 
		}
		cout << endl;	
	}
};


/*
	MainStructure: 主结构
*/
void MainStructure();

/*
	Process：处理每一组数据
*/
void Process();

/*
	Test BigNum
*/
void Test();

/*
	判断是否match
*/
bool IsMatch(BigNum &bn, BigNum &powNum);

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
	string outputStr = "C:/Users/cao/Desktop/算法/要看的书/算法/2挑战编程/input/0000001.outp";
	ifstream fin;
	fin.open(inputStr);	
	

	cin.rdbuf(fin.rdbuf());	

	//ofstream fout;
	//fout.open(outputStr.c_str());

	//cout.rdbuf(fout.rdbuf());
#endif

	Process();
	//Test();
		
}

void Test()
{
	// 
	BigNum n1;
	n1.PrintNum();

	BigNum n2(100);
	n2.PrintNum();

	n2 = 999;
	n2.PrintNum();

	n2 *= 2;
	n2.PrintNum();
}

void Process()
{
	unsigned int num = 0;
	while (cin >> num)
	{
		BigNum bn(num);
		BigNum powNum(64);
		int count = 6;
		while (!IsMatch(bn, powNum))
		{
			if (powNum.length >= MAX_INT_LENGTH)
			{
				break;
			}
			powNum *= 2;
			++count;
		}
		// 如果超过了20位，认为不存在
		if (powNum.length < MAX_INT_LENGTH)
		{
			cout << count << endl;
		}
		else
		{
			cout << "no power of 2" << endl;
		}
	}

}


bool IsMatch(BigNum &bn, BigNum &powNum)
{
	// 长度
	if (powNum.length <= bn.length * 2)
	{
		return false;
	}
	// 要比较的长度
	int len = bn.length;
	// 两者的长度差
	int absLen = powNum.length - bn.length;
	for (int i = 0; i < len; ++i)
	{
		if (bn.arr[i] != powNum.arr[absLen + i])
		{
			return false;
		}
	}
	return true;
}