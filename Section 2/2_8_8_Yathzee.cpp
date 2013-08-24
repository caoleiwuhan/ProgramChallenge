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

// 骰子数
const int TOU_ZI_NUM = 5;
// 游戏轮数：13:0->12
const int PLAY_NUM = 13;

/*
	MainStructure: 主结构
*/
void MainStructure();

/*
	Process：处理每一组数据
*/
void Process();

/*
	Handle：处理每一组中的每一个实例
*/
void Handle(int touzi[][TOU_ZI_NUM]);

void Handle2(int touzi[][TOU_ZI_NUM]);


/*
	回溯法计算
	//flags	：某一组是否计算过
	ans		：结果
	best	：最大值
	//bestMap ：最大值时的映射-bestMap[i] = j	:第i个积分规则应用于第j个数据
	cur		：当前结果
	curBest	：当前之和
	curMap	：当前映射
	step	：步骤
*/
void DFS(int touzi[][TOU_ZI_NUM], int ans[], int &best, int cur[], int curBest, 
	int curMap[], int step);


void DFS2(int points[][PLAY_NUM], int ans[], int &best, int cur[], int curBest, 
	int curMap[], int step);


/*
	是否满足奖励规则
*/
bool IsPrize(int ans[]);

/*
	拷贝intVec
*/
void CopyIntVec(int dest[], int src[], int size);

/*
	num是否在arr中？
*/
bool IsNumInArr(int num, int arr[], int size);

/*
	第index组作为第step个规则计算的得分
*/
int CalculatePoint(int arr[], int step);

// Rule0：点数为num的和
int Rule0(int arr[], int num);

// Rule6：所有点数和
int Rule6(int arr[]);

// Rule7：三同
int Rule7(int arr[]);

// Rule8：四同
int Rule8(int arr[]);

// Rule9：五同
int Rule9(int arr[]);

// Rule10：小顺
int Rule10(int arr[]);

// Rule11：大顺
int Rule11(int arr[]);

// Rule12：葫芦
int Rule12(int arr[]);

/*
	预先计算PLAY_NUM数据的PLAY_NUM种分类的分数
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
	string inputStr = "C:/Users/cao/Desktop/算法/要看的书/算法/2挑战编程/input/1.inp";
	//string inputStr = "D:/2挑战编程/input/110208.inp";
	string outputStr = "C:/Users/cao/Desktop/算法/要看的书/算法/2挑战编程/input/0000001.outp";
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
	// 每十三行进行一次处理
	// 应用暴力回溯？
	int touzi[PLAY_NUM][TOU_ZI_NUM];
	// 读入骰子数
	string str;
	while (getline(cin, str))
	{
		if (str == "")
		{
			break;
		}
		// 解析第一行
		stringstream ss(str);
		ss >> touzi[0][0];
		ss >> touzi[0][1];
		ss >> touzi[0][2];
		ss >> touzi[0][3];
		ss >> touzi[0][4];
		
		// 解析余下的12行
		for (int i = 1; i < PLAY_NUM; ++i)
		{
			for (int j = 0; j < TOU_ZI_NUM; ++j)
			{
				cin >> touzi[i][j];
			}
		}
		// 计算
		//Handle(touzi);
		Handle2(touzi);
	}
}

void Handle(int touzi[][TOU_ZI_NUM])
{
	// 排序：默认从小到大
	for (int i = 0; i < PLAY_NUM; ++i)
	{
		sort(touzi[i], touzi[i + 1]);
	}

	// 保存结果最大时每一组的分数
	int ans[PLAY_NUM];
	// 总分
	int best = 0;	

	int curBest = 0;
	// 当前每一组的得分情况
	int cur[PLAY_NUM];
	// 当前的每一组应用的规则
	int curMap[PLAY_NUM];
	// 初始化curMap为-1
	for (int i = 0; i < PLAY_NUM; ++i)
	{
		curMap[i] = -1;
	}
	DFS(touzi, ans, best, cur, curBest, curMap, 0);
	// 打印结果
	for (int i = 0; i < PLAY_NUM; ++i)
	{
		cout << ans[i] << " ";
	}
	// 是否奖励
	if (IsPrize(ans))
	{
		cout << 0 << " ";
	}
	else
	{
		cout << 35 << " ";
	}
	// 总分
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
		// 判断是否大于best
		if (curBest > best)
		{
			best = curBest;
			CopyIntVec(ans, cur, PLAY_NUM);
		}
		return;
	}
	else
	{
		// 前step项已经完成，考虑第step+1项，从没有在cur的数中找一项
		for (int i = 0; i < PLAY_NUM; ++i)
		{
			// i是否被计算过?:表示第i组数据应用第step个规则
			if (!IsNumInArr(i, curMap, step))
			{
				// 如果没有计算过，则将i设置为当前要计算的组数，并向下回溯
				curMap[step] = i; // 第step个规则应用于第i组数据
				int point = CalculatePoint(touzi[i], step);
				curBest += point;
				// 第step的得分
				cur[step] = point;
				// 回溯
				DFS(touzi, ans, best, cur, curBest, curMap, step + 1);
				// 还原
				curBest -= point;
				curMap[step] = -1;
				cur[step] = point;
			}
		}
	}
}

bool IsPrize(int ans[])
{
	// 前六项得分大于等于63
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


// Rule0：点数为num的和
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

// Rule6：所有点数和
int Rule6(int arr[])
{
	int total = 0;
	for (int i = 0; i < TOU_ZI_NUM; ++i)
	{
		total += arr[i];
	}
	return total;
}

// Rule7：三同
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

// Rule8：四同
int Rule8(int arr[])
{
	if ((arr[0] == arr[1] && arr[1] == arr[2] && arr[2] == arr[3]) ||
	(arr[1] == arr[2] && arr[2] == arr[3] && arr[3] == arr[4]))	
	{
		return Rule6(arr);
	}
	return 0;
}

// Rule9：五同
int Rule9(int arr[])
{
	if (arr[0] == arr[1] && arr[1] == arr[2] && arr[2] == arr[3] && arr[3] == arr[4])
	{
		return 50;
	}
	return 0;
}

// Rule10：小顺
int Rule10(int arr[])
{
	bool isOK1 = true;
	// 前四个、后四个
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

// Rule11：大顺
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

// Rule12：葫芦
int Rule12(int arr[])
{
	// 寻找长度为3的	
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
			// 计算第i组数据第j种方式的得分
			points[i][j] = CalculatePoint(touzi[i], j);
		}
	}
}

void Handle2(int touzi[][TOU_ZI_NUM])
{
	// 排序：默认从小到大
	for (int i = 0; i < PLAY_NUM; ++i)
	{
		sort(touzi[i], touzi[i + 1]);
	}

	// 保存结果最大时每一组的分数
	int ans[PLAY_NUM];
	// 总分
	int best = 0;	

	int curBest = 0;
	// 当前每一组的得分情况
	int cur[PLAY_NUM];
	// 当前的每一组应用的规则
	int curMap[PLAY_NUM];
	// 初始化curMap为-1
	for (int i = 0; i < PLAY_NUM; ++i)
	{
		curMap[i] = -1;
	}

	int points[PLAY_NUM][PLAY_NUM];
	// 预先计算得分：
	CalAllPoints(touzi, points);

	DFS2(points, ans, best, cur, curBest, curMap, 0);
	// 打印结果
	for (int i = 0; i < PLAY_NUM; ++i)
	{
		cout << ans[i] << " ";
	}
	// 是否奖励
	if (IsPrize(ans))
	{
		cout << 0 << " ";
	}
	else
	{
		cout << 35 << " ";
	}
	// 总分
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
		// 判断是否大于best
		if (curBest > best)
		{
			best = curBest;
			CopyIntVec(ans, cur, PLAY_NUM);
		}		
	}
	else
	{
		// 前step项已经完成，考虑第step+1项，从没有在cur的数中找一项
		for (int i = 0; i < PLAY_NUM; ++i)
		{
			// i是否被计算过?:表示第i组数据应用第step个规则
			if (!IsNumInArr(i, curMap, step))
			{
				// 如果没有计算过，则将i设置为当前要计算的组数，并向下回溯
				curMap[step] = i; // 第step个规则应用于第i组数据
				int point = points[i][step];
				curBest += point;
				// 第step的得分
				cur[step] = point;
				// 回溯
				DFS2(points, ans, best, cur, curBest, curMap, step + 1);
				// 还原
				curBest -= point;
				curMap[step] = -1;
				cur[step] = point;
			}
		}
	}
}


