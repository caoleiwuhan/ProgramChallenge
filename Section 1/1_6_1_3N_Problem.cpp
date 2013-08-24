#include <iostream>
#include <cassert>

using namespace std;

/*
	输入一个整数（不知道正负）小于1000 000。
	输出该整数的循环节长度
	如果为偶数，除以2；如果为奇数，3*N+1，直到N为1.
	
*/
int NumberOfNode(int num)
{
	// num不保证为正数,但小于1000000
	assert(num >= 1 && num <= 1000000);
	// 循环节长度
	int node = 1;
	while (num != 1)
	{
		// 如果是奇数
		if (num & 1)
		{
			num = num * 3 + 1;
		}
		else
		{
			num /= 2;
		}
		++node;
	}

	return node;
}

/*
	输入两个整数i、j
	输出i、j之间（包括i、j）整数的循环节的最大值
	循环遍历i、j之间所有的数，找出最大值
*/
int MaxOfNode(int i, int j)
{
	// 左边界
	int left = i;
	// 右边界
	int right = j;
	if (i > j)
	{
		left = j;
		right = i;
	}
	// 记录最大值
	int max = 0;
	for (int index = left; index <= right; ++index)
	{
		// 当前数的节点值
		int cur = NumberOfNode(index);
		if (cur > max)
		{
			max = cur;
		}
	}
	return max;
}


int main()
{	
	//// Test NumberOfNode
	//cout << NumberOfNode(22) << endl;
	//cout << NumberOfNode(-4) << endl;
	//cout << NumberOfNode(100000) << endl;

	int num1 = 0;
	int num2 = 0;
	while (cin >> num1 >> num2)
	{
		int max = MaxOfNode(num1, num2);
		cout << num1 << " " << num2 << " " << max << endl;
	}

	return 0;
}