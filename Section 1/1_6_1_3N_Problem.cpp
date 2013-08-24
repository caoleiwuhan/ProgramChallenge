#include <iostream>
#include <cassert>

using namespace std;

/*
	����һ����������֪��������С��1000 000��
	�����������ѭ���ڳ���
	���Ϊż��������2�����Ϊ������3*N+1��ֱ��NΪ1.
	
*/
int NumberOfNode(int num)
{
	// num����֤Ϊ����,��С��1000000
	assert(num >= 1 && num <= 1000000);
	// ѭ���ڳ���
	int node = 1;
	while (num != 1)
	{
		// ���������
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
	������������i��j
	���i��j֮�䣨����i��j��������ѭ���ڵ����ֵ
	ѭ������i��j֮�����е������ҳ����ֵ
*/
int MaxOfNode(int i, int j)
{
	// ��߽�
	int left = i;
	// �ұ߽�
	int right = j;
	if (i > j)
	{
		left = j;
		right = i;
	}
	// ��¼���ֵ
	int max = 0;
	for (int index = left; index <= right; ++index)
	{
		// ��ǰ���Ľڵ�ֵ
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