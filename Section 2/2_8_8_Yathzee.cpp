#include <iostream>
#include <cstdlib>
#include <vector>
#include <set>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

#define _MY_DEBUG_

// ������
const int TOU_ZI_NUM = 5;
// ��Ϸ������13:0->12
const int PLAY_NUM = 13;

/*
	MainStructure: ���ṹ
*/
void MainStructure();

/*
	Process������ÿһ������
*/
void Process();

/*
	Handle������ÿһ���е�ÿһ��ʵ��
*/
void Handle(int touzi[][TOU_ZI_NUM]);

void Handle2(int touzi[][TOU_ZI_NUM]);


/*
	���ݷ�����
	//flags	��ĳһ���Ƿ�����
	ans		�����
	best	�����ֵ
	//bestMap �����ֵʱ��ӳ��-bestMap[i] = j	:��i�����ֹ���Ӧ���ڵ�j������
	cur		����ǰ���
	curBest	����ǰ֮��
	curMap	����ǰӳ��
	step	������
*/
void DFS(int touzi[][TOU_ZI_NUM], int ans[], int &best, int cur[], int curBest, 
	int curMap[], int step);


void DFS2(int points[][PLAY_NUM], int ans[], int &best, int cur[], int curBest, 
	int curMap[], int step);


/*
	�Ƿ����㽱������
*/
bool IsPrize(int ans[]);

/*
	����intVec
*/
void CopyIntVec(int dest[], int src[], int size);

/*
	num�Ƿ���arr�У�
*/
bool IsNumInArr(int num, int arr[], int size);

/*
	��index����Ϊ��step���������ĵ÷�
*/
int CalculatePoint(int arr[], int step);

// Rule0������Ϊnum�ĺ�
int Rule0(int arr[], int num);

// Rule6�����е�����
int Rule6(int arr[]);

// Rule7����ͬ
int Rule7(int arr[]);

// Rule8����ͬ
int Rule8(int arr[]);

// Rule9����ͬ
int Rule9(int arr[]);

// Rule10��С˳
int Rule10(int arr[]);

// Rule11����˳
int Rule11(int arr[]);

// Rule12����«
int Rule12(int arr[]);

/*
	Ԥ�ȼ���PLAY_NUM���ݵ�PLAY_NUM�ַ���ķ���
*/
void CalAllPoints(int touzi[][TOU_ZI_NUM], int points[][PLAY_NUM]);

int main()
{
	MainStructure();
	return 0;
}

void MainStructure()
{
	
#ifdef _MY_DEBUG_
	string inputStr = "C:/Users/cao/Desktop/�㷨/Ҫ������/�㷨/2��ս���/input/1.inp";
	//string inputStr = "D:/2��ս���/input/110208.inp";
	string outputStr = "C:/Users/cao/Desktop/�㷨/Ҫ������/�㷨/2��ս���/input/0000001.outp";
	ifstream fin;
	fin.open(inputStr);	

	cin.rdbuf(fin.rdbuf());	

	ofstream fout;
	fout.open(outputStr);

	//cout.rdbuf(fout.rdbuf());
	Process();

#endif
		
}

void Process()
{
	// ÿʮ���н���һ�δ���
	// Ӧ�ñ������ݣ�
	int touzi[PLAY_NUM][TOU_ZI_NUM];
	// ����������
	string str;
	while (getline(cin, str))
	{
		if (str == "")
		{
			break;
		}
		// ������һ��
		stringstream ss(str);
		ss >> touzi[0][0];
		ss >> touzi[0][1];
		ss >> touzi[0][2];
		ss >> touzi[0][3];
		ss >> touzi[0][4];
		
		// �������µ�12��
		for (int i = 1; i < PLAY_NUM; ++i)
		{
			for (int j = 0; j < TOU_ZI_NUM; ++j)
			{
				cin >> touzi[i][j];
			}
		}
		// ����
		//Handle(touzi);
		Handle2(touzi);
	}
}

void Handle(int touzi[][TOU_ZI_NUM])
{
	// ����Ĭ�ϴ�С����
	for (int i = 0; i < PLAY_NUM; ++i)
	{
		sort(touzi[i], touzi[i + 1]);
	}

	// ���������ʱÿһ��ķ���
	int ans[PLAY_NUM];
	// �ܷ�
	int best = 0;	

	int curBest = 0;
	// ��ǰÿһ��ĵ÷����
	int cur[PLAY_NUM];
	// ��ǰ��ÿһ��Ӧ�õĹ���
	int curMap[PLAY_NUM];
	// ��ʼ��curMapΪ-1
	for (int i = 0; i < PLAY_NUM; ++i)
	{
		curMap[i] = -1;
	}
	DFS(touzi, ans, best, cur, curBest, curMap, 0);
	// ��ӡ���
	for (int i = 0; i < PLAY_NUM; ++i)
	{
		cout << ans[i] << " ";
	}
	// �Ƿ���
	if (IsPrize(ans))
	{
		cout << 0 << " ";
	}
	else
	{
		cout << 35 << " ";
	}
	// �ܷ�
	cout << best << endl;
}

void DFS(int touzi[][TOU_ZI_NUM], int ans[], int &best, int cur[], 
	int curBest, int curMap[], int step)
{
	if (step == PLAY_NUM)
	{
		if (IsPrize(cur))
		{
			curBest += 35;
		}
		// �ж��Ƿ����best
		if (curBest > best)
		{
			best = curBest;
			CopyIntVec(ans, cur, PLAY_NUM);
		}
		return;
	}
	else
	{
		// ǰstep���Ѿ���ɣ����ǵ�step+1���û����cur��������һ��
		for (int i = 0; i < PLAY_NUM; ++i)
		{
			// i�Ƿ񱻼����?:��ʾ��i������Ӧ�õ�step������
			if (!IsNumInArr(i, curMap, step))
			{
				// ���û�м��������i����Ϊ��ǰҪ����������������»���
				curMap[step] = i; // ��step������Ӧ���ڵ�i������
				int point = CalculatePoint(touzi[i], step);
				curBest += point;
				// ��step�ĵ÷�
				cur[step] = point;
				// ����
				DFS(touzi, ans, best, cur, curBest, curMap, step + 1);
				// ��ԭ
				curBest -= point;
				curMap[step] = -1;
				cur[step] = point;
			}
		}
	}
}

bool IsPrize(int ans[])
{
	// ǰ����÷ִ��ڵ���63
	int total = 0;
	for (int i = 0; i < 6; ++i)
	{
		total += ans[i];
	}
	if (total >= 63)
	{
		return true;
	}
	return false;
}

void CopyIntVec(int dest[], int src[], int size)
{
	for (int i = 0; i < size; ++i)
	{
		dest[i] = src[i];
	}
}

bool IsNumInArr(int num, int arr[], int size)
{
	for (int i = 0; i < size; ++i)
	{
		if (num == arr[i])
		{
			return true;
		}
	}
	return false;
}

int CalculatePoint(int arr[], int step)
{
	switch(step)
	{
	case 0:
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
		return Rule0(arr, step + 1);
		break;
	case 6:
		return Rule6(arr);
		break;
	case 7:
		return Rule7(arr);
		break;
	case 8:
		return Rule8(arr);
		break;
	case 9:
		return Rule9(arr);
		break;
	case 10:
		return Rule10(arr);
		break;
	case 11:
		return Rule11(arr);
		break;
	case 12:
		return Rule12(arr);
		break;
	}
	return 0;
}


// Rule0������Ϊnum�ĺ�
int Rule0(int arr[], int num)
{
	int total = 0;
	for (int i = 0; i < TOU_ZI_NUM; ++i)
	{
		if (arr[i] == num)
		{
			total += num;
		}
	}
	return total;
}

// Rule6�����е�����
int Rule6(int arr[])
{
	int total = 0;
	for (int i = 0; i < TOU_ZI_NUM; ++i)
	{
		total += arr[i];
	}
	return total;
}

// Rule7����ͬ
int Rule7(int arr[])
{
	if ((arr[0] == arr[1] && arr[1] == arr[2]) ||
		(arr[1] == arr[2] && arr[2] == arr[3]) ||
		(arr[2] == arr[3] && arr[3] == arr[4]))
	{
		return Rule6(arr);
	}
	return 0;
}

// Rule8����ͬ
int Rule8(int arr[])
{
	if ((arr[0] == arr[1] && arr[1] == arr[2] && arr[2] == arr[3]) ||
	(arr[1] == arr[2] && arr[2] == arr[3] && arr[3] == arr[4]))	
	{
		return Rule6(arr);
	}
	return 0;
}

// Rule9����ͬ
int Rule9(int arr[])
{
	if (arr[0] == arr[1] && arr[1] == arr[2] && arr[2] == arr[3] && arr[3] == arr[4])
	{
		return 50;
	}
	return 0;
}

// Rule10��С˳
int Rule10(int arr[])
{
	bool isOK1 = true;
	// ǰ�ĸ������ĸ�
	for (int i = 1; i < 4; ++i)
	{
		if (arr[i - 1] + 1 != arr[i])
		{
			isOK1 = false;
			break;
		}
	}
	bool isOK2 = true;
	for (int i = 2; i < 5; ++i)
	{
		if (arr[i - 1] + 1 != arr[i])
		{
			isOK2 = false;
			break;
		}
	}
	if (isOK1 || isOK2)
	{
		return 25;
	}
	return 0;
}

// Rule11����˳
int Rule11(int arr[])
{
	bool isOK = true;
	for (int i = 1; i < TOU_ZI_NUM; ++i)
	{
		if (arr[i - 1] + 1 != arr[i])
		{
			isOK = false;
			break;
		}
	}
	if (isOK)
	{
		return 35;
	}
	return 0;
}

// Rule12����«
int Rule12(int arr[])
{
	// Ѱ�ҳ���Ϊ3��	
	if (((arr[0] == arr[1] && arr[1] == arr[2]) && (arr[3] == arr[4])) ||
		((arr[2] == arr[3] && arr[3] == arr[4]) && (arr[0] == arr[1])))
	{
		return 40;
	}
	return 0;
}

void CalAllPoints(int touzi[][TOU_ZI_NUM], int points[][PLAY_NUM])
{
	for (int i = 0; i < PLAY_NUM; ++i)
	{
		for (int j = 0; j < PLAY_NUM; ++j)
		{
			// �����i�����ݵ�j�ַ�ʽ�ĵ÷�
			points[i][j] = CalculatePoint(touzi[i], j);
		}
	}
}

void Handle2(int touzi[][TOU_ZI_NUM])
{
	// ����Ĭ�ϴ�С����
	for (int i = 0; i < PLAY_NUM; ++i)
	{
		sort(touzi[i], touzi[i + 1]);
	}

	// ���������ʱÿһ��ķ���
	int ans[PLAY_NUM];
	// �ܷ�
	int best = 0;	

	int curBest = 0;
	// ��ǰÿһ��ĵ÷����
	int cur[PLAY_NUM];
	// ��ǰ��ÿһ��Ӧ�õĹ���
	int curMap[PLAY_NUM];
	// ��ʼ��curMapΪ-1
	for (int i = 0; i < PLAY_NUM; ++i)
	{
		curMap[i] = -1;
	}

	int points[PLAY_NUM][PLAY_NUM];
	// Ԥ�ȼ���÷֣�
	CalAllPoints(touzi, points);

	DFS2(points, ans, best, cur, curBest, curMap, 0);
	// ��ӡ���
	for (int i = 0; i < PLAY_NUM; ++i)
	{
		cout << ans[i] << " ";
	}
	// �Ƿ���
	if (IsPrize(ans))
	{
		cout << 0 << " ";
	}
	else
	{
		cout << 35 << " ";
	}
	// �ܷ�
	cout << best << endl;
}

void DFS2(int points[][PLAY_NUM], int ans[], int &best, int cur[], 
	int curBest, int curMap[], int step)
{
	if (step == PLAY_NUM)
	{
		if (IsPrize(cur))
		{
			curBest += 35;
		}
		// �ж��Ƿ����best
		if (curBest > best)
		{
			best = curBest;
			CopyIntVec(ans, cur, PLAY_NUM);
		}		
	}
	else
	{
		// ǰstep���Ѿ���ɣ����ǵ�step+1���û����cur��������һ��
		for (int i = 0; i < PLAY_NUM; ++i)
		{
			// i�Ƿ񱻼����?:��ʾ��i������Ӧ�õ�step������
			if (!IsNumInArr(i, curMap, step))
			{
				// ���û�м��������i����Ϊ��ǰҪ����������������»���
				curMap[step] = i; // ��step������Ӧ���ڵ�i������
				int point = points[i][step];
				curBest += point;
				// ��step�ĵ÷�
				cur[step] = point;
				// ����
				DFS2(points, ans, best, cur, curBest, curMap, step + 1);
				// ��ԭ
				curBest -= point;
				curMap[step] = -1;
				cur[step] = point;
			}
		}
	}
}


