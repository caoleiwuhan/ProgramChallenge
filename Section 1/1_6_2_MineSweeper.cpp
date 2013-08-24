#include <iostream>

using namespace std;

/*
	输入char数组、row、column
	输出扫雷棋盘
*/
void ReadMine(char mine[][100], int row, int column)
{
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < column; ++j)
		{
			cin >> mine[i][j];
		}
	}
}

// 定义Map
int map[9][2] = 
{
	// 上面三个
	-1,-1,
	-1, 0,
	-1, 1,
	// 中间三个
	0, -1,
	0, 0,
	0, 1,
	// 下面三个
	1, -1,
	1, 0,
	1, 1
};

/*
	传入i、j，row、col
	判断是否出界
*/
bool IsInBoundary(int row, int col, int i, int j)
{
	if (i >= 0 && i < row &&
		j >= 0 && j < col)
	{
		return true;
	}
	return false;
}

/*
	输入mine、row、column、i、j
	输出（i，j）的mine个数
	计算周围8个位置的mine
*/
int NumberOfMine(char mine[][100], int row, int column, int i, int j)
{
	// 周围雷的个数
	int num = 0;
	for (int index = 0; index < 9; ++index)
	{
		// 新的边界row
		int newRow = i + map[index][0];
		// 新的边界col
		int newCol = j + map[index][1];
		// 判断是否出界
		if (IsInBoundary(row, column, newRow, newCol))
		{
			if (mine[newRow][newCol] == '*')
			{
				++num;
			}
		}
	}
	return num;
}

/*
	输入棋盘，row、column
	输出ans
*/
void CalMine(char mine[][100], int row, int column, char ans[][100])
{
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < column; ++j)
		{
			// 如果当前位置是雷
			if (mine[i][j] == '*')
			{
				ans[i][j] = '*';
			}
			else
			{
				// 将结果转换为char类型
				ans[i][j] = (char)(NumberOfMine(mine, row, column, i, j) + '0');
			}
		}
	}
}

/*
	输入计算过的ans
	输出扫雷结果
*/
void PrintMine(char ans[][100], int row, int column, int fieldCount)
{
	cout << "Field #" << fieldCount << ":" << endl;
	//Field #x:
	//printf("Field #%d:\n", fieldCount);
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < column; ++j)
		{
			cout << ans[i][j];
		}
		cout << endl;
	}	
}

int main()
{
	//cout << "MineSweeper" << endl;
	// 记录处理的总个数，从一开始
	int fieldCount = 1;
	// 行数
	int row = 0;
	// 列数
	int column = 0;
	// 扫雷棋盘，最大行列数不超过100
	char mine[100][100];
	// 保存计算结果
	char ans[100][100];
	
	while (cin >> row >> column)
	{
		// 结束条件
		if (row == 0 && column == 0)
		{			
			break;
		}
		// 读入扫雷棋盘
		ReadMine(mine, row, column);
		// 计算扫雷
		CalMine(mine, row, column, ans);
		if (fieldCount != 1)
		{
			cout << endl;
		}
		// 打印输出结果
		PrintMine(ans, row, column, fieldCount++);		
	}
}