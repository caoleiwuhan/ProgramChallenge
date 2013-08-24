#include <iostream>

using namespace std;

/*
	����char���顢row��column
	���ɨ������
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

// ����Map
int map[9][2] = 
{
	// ��������
	-1,-1,
	-1, 0,
	-1, 1,
	// �м�����
	0, -1,
	0, 0,
	0, 1,
	// ��������
	1, -1,
	1, 0,
	1, 1
};

/*
	����i��j��row��col
	�ж��Ƿ����
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
	����mine��row��column��i��j
	�����i��j����mine����
	������Χ8��λ�õ�mine
*/
int NumberOfMine(char mine[][100], int row, int column, int i, int j)
{
	// ��Χ�׵ĸ���
	int num = 0;
	for (int index = 0; index < 9; ++index)
	{
		// �µı߽�row
		int newRow = i + map[index][0];
		// �µı߽�col
		int newCol = j + map[index][1];
		// �ж��Ƿ����
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
	�������̣�row��column
	���ans
*/
void CalMine(char mine[][100], int row, int column, char ans[][100])
{
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < column; ++j)
		{
			// �����ǰλ������
			if (mine[i][j] == '*')
			{
				ans[i][j] = '*';
			}
			else
			{
				// �����ת��Ϊchar����
				ans[i][j] = (char)(NumberOfMine(mine, row, column, i, j) + '0');
			}
		}
	}
}

/*
	����������ans
	���ɨ�׽��
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
	// ��¼������ܸ�������һ��ʼ
	int fieldCount = 1;
	// ����
	int row = 0;
	// ����
	int column = 0;
	// ɨ�����̣����������������100
	char mine[100][100];
	// ���������
	char ans[100][100];
	
	while (cin >> row >> column)
	{
		// ��������
		if (row == 0 && column == 0)
		{			
			break;
		}
		// ����ɨ������
		ReadMine(mine, row, column);
		// ����ɨ��
		CalMine(mine, row, column, ans);
		if (fieldCount != 1)
		{
			cout << endl;
		}
		// ��ӡ������
		PrintMine(ans, row, column, fieldCount++);		
	}
}