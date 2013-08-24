#include <iostream>

using namespace std;

// const int COL = 1003 * 10;

// map1��������ʾÿ�����ֵ��ض�λ���Ƿ��к��
int map1[10][3] = 
{
	1, 0, 1, // 0
	0, 0, 0, // 1
	1, 1, 1, // 2
	1, 1, 1, // 3
	0, 1, 0, // 4
	1, 1, 1, // 5
	1, 1, 1, // 6
	1, 0, 0, // 7
	1, 1, 1, // 8
	1, 1, 1  // 9
};

// map2:��ʾ����������Ƿ�������
int map2[10][2] = 
{
	1, 1, // 0
	0, 1, // 1
	0, 1, // 2
	0, 1, // 3
	1, 1, // 4
	1, 0, // 5
	1, 0, // 6
	0, 1, // 7
	1, 1, // 8
	1, 1  // 9
};

// map3:��ʾ����������Ƿ�������
int map3[10][2] = 
{
	1, 1, // 0
	0, 1, // 1
	1, 0, // 2
	0, 1, // 3
	0, 1, // 4
	0, 1, // 5
	1, 1, // 6
	0, 1, // 7
	1, 1, // 8
	0, 1  // 9
};

void HandleMap1(int s, int digit, char chs[], int &cur, int level)
{
	chs[cur++] = ' ';
	if (map1[digit][level] == 1)
	{
		for (int j = 0; j < s; ++j)
		{
			chs[cur++] = '-';
		}
	}
	else
	{
		for (int j = 0; j < s; ++j)
		{
			chs[cur++] = ' ';
		}
	}
	chs[cur++] = ' ';
}

void HandleMap23(int map23[][2], int s, int digit, char chs[], int &cur)
{
	if (map23[digit][0] == 1)
	{		
		chs[cur++] = '|';		
	}
	else
	{
		chs[cur++] = ' ';		
	}
	// �м���s���ո�
	for (int i = 0; i < s; ++i)
	{
		chs[cur++] = ' ';
	}
	if (map23[digit][1] == 1)
	{		
		chs[cur++] = '|';		
	}
	else
	{
		chs[cur++] = ' ';		
	}
}

// ��i��
void PrintChar(int s, int num[], int size, char chs[], int i)
{
	// ��ǰchs�еĴ���λ��
	int cur = 0;
	if (i == 0)
	{
		for (int index = 0; index < size; ++index)
		{
			// һ����5�����
			HandleMap1(s, num[index], chs, cur, 0);
			chs[cur++] = ' ';
		}	
	}
	else if (i == 1)
	{
		for (int index = 0; index < size; ++index)
		{
			HandleMap23(map2, s, num[index], chs, cur);
			chs[cur++] = ' ';
		}
	}
	else if (i == s + 1)
	{
		for (int index = 0; index < size; ++index)
		{
			HandleMap1(s, num[index], chs, cur, 1);	
			chs[cur++] = ' ';
		}
	}
	else if (i == s + 2)
	{
		for (int index = 0; index < size; ++index)
		{
			HandleMap23(map3, s, num[index], chs, cur);
			chs[cur++] = ' ';
		}
	}
	else if (i == 2 * s + 2)
	{
		for (int index = 0; index < size; ++index)
		{
			HandleMap1(s, num[index], chs, cur, 2);	
			chs[cur++] = ' ';
		}
	}
	else
	{
		// ����һ���ظ���ʲôҲ����			
	}
	// Ҫ�����һ���ո�ȥ��

	chs[--cur] = '\0';	
	cout << chs << endl;
}
/*
	����n����n��ÿһλ�����Ӹߵ��ͷ���num��
	����λ��
*/
void ParseNToArr(int n, int num[], int &size)
{
	size = 0;
	while (n > 0)
	{
		num[size++] = n % 10;
		n /= 10;
	}
	for (int i = 0; i < size / 2; ++i)
	{
		int tmp = num[i];
		num[i] = num[size - i - 1];
		num[size - i - 1] = tmp;
	}
}

void Test()
{
	int n = 123;
	int num[5];
	int size = 0;
	ParseNToArr(n, num, size);
}


int main()
{
	//cout << "Test" << endl;	
	//cout << '|' << endl;

	// һ�����ü���-��ʾ
	int s = 0;
	// Ҫ��ʾ������
	int n = 0;	
	// ��n��ÿ��λ����num�� 
	int num[10];
	// ���ÿһ��
	// char chs[COL];

	while (cin >> s >> n)
	{
		if (s == 0 && n == 0)
		{
			break;
		}
		// ����n������
		// n����λ��
		int size = 0;
		ParseNToArr(n, num, size);
		// ������
		int row = 2 * s + 3;
		// ������:ÿһ�����ֺ�����һ���ո�
		int col = (s + 3) * size;
		char *chs = new char[col + 1];
		//for (int i = 0; i < col; ++i)
		//{
		//	cout << "*";
		//}
		//cout << endl;
		// ��Ҫһ��һ�е����
		for (int i = 0; i < row; ++i)
		{
			PrintChar(s, num, size, chs, i);
		}
		cout << endl;		
	}

	// Test();

	return 0;
}