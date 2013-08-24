#include <iostream>
#include <cstdio>
#include <string>

using namespace std;

// ���̱߽�
const int BOARD = 8;

// ���̣����Դ�1��ʼ
char chessboard[BOARD + 1][BOARD + 1];

/*
	�������̣����ҷ����Ƿ������־
*/
bool InitChessBoard();

/*
	��������
*/
void HandleChessBoard(int count);

/*
	�ж�x��y�Ƿ񳬳��߽�
*/
bool IsOutOfBound(int x, int y);

/*
	��������
	�������ӵ�λ�á���Сд������ж��Ƿ񽫾�
*/
bool IsPawnOK(int x, int y, char p);


/*
	����
	���복��λ�á���Сд������ж��Ƿ񽫾�
	ע�ⲻ��Խ��ȥ��
*/
bool IsRookOK(int x, int y, char p);

bool IsRookOKHelp(int x, int y, char k);

/*
	��
	���복��λ�á���Сд������ж��Ƿ񽫾�
	ע�ⲻ��Խ��ȥ��
*/
bool IsBishopOK(int x, int y, char p);

bool IsBishopOKHelp(int x, int y, char k);

/*
	�ʺ�
*/
bool IsQueenOK(int x, int y, char p);

int knightMap[8][2] = 
{
	-1, 2,
	-2, 1,
	-2, -1,
	-1, -2,
	1, -2,
	2, -1,
	2, 1,
	1, 2
};

/*
	��
*/
bool IsKnightOK(int x, int y, char p);
bool IsKnightOKHelp(int x, int y, char p);

/*
	������
*/
bool IsKingOK(int x, int y, char p);
bool IsKingOKHelp(int x, int y, char p);
int kingMap[8][2] = 
{
	-1, 0,
	-1, 1,
	0, 1,
	1, 1,
	1, 0,
	1, -1,
	0, -1,
	-1, -1
};


/*
	���Գ���
*/
void Test()
{
	//chessboard[1][1] = 'r';
	//chessboard[1][2] = 'n';
	//chessboard[1][3] = 'b';
	//chessboard[1][4] = 'q';
	//chessboard[1][5] = 'k';
	//chessboard[1][6] = '.';
	//chessboard[1][7] = 'n';
	//chessboard[1][8] = 'r';

	//chessboard[2][1] = 'p';
	//chessboard[2][2] = 'p';
	//chessboard[2][3] = 'p';
	//chessboard[2][4] = '.';
	//chessboard[2][5] = '.';
	//chessboard[2][6] = 'p';
	//chessboard[2][7] = 'p';
	//chessboard[2][8] = 'p';

	//chessboard[3][1] = '.';
	//chessboard[3][2] = '.';
	//chessboard[3][3] = '.';
	//chessboard[3][4] = '.';
	//chessboard[3][5] = 'p';
	//chessboard[3][6] = '.';
	//chessboard[3][7] = '.';
	//chessboard[3][8] = '.';

	//chessboard[4][1] = '.';
	//chessboard[4][2] = '.';
	//chessboard[4][3] = '.';
	//chessboard[4][4] = 'p';
	//chessboard[4][5] = '.';
	//chessboard[4][6] = '.';
	//chessboard[4][7] = '.';
	//chessboard[4][8] = '.';

	//chessboard[5][1] = '.';
	//// 
	//chessboard[5][2] = '.';
	//chessboard[5][3] = 'P';
	//chessboard[5][4] = 'P';
	//chessboard[5][5] = '.';
	//chessboard[5][6] = '.';
	//chessboard[5][7] = '.';
	//chessboard[5][8] = '.';

	//chessboard[6][1] = '.';
	//chessboard[6][2] = '.';
	//chessboard[6][3] = '.';
	//chessboard[6][4] = '.';
	//chessboard[6][5] = '.';
	//chessboard[6][6] = 'N';
	//chessboard[6][7] = '.';
	//chessboard[6][8] = '.';
	//
	//chessboard[7][1] = 'P';
	//chessboard[7][2] = 'P';
	//chessboard[7][3] = '.';
	//chessboard[7][4] = '.';
	//chessboard[7][5] = 'P';
	//chessboard[7][6] = 'P';
	//chessboard[7][7] = 'P';
	//chessboard[7][8] = 'P';

	//chessboard[8][1] = 'R';
	//chessboard[8][2] = 'N';
	//chessboard[8][3] = 'B';
	//chessboard[8][4] = 'Q';
	//chessboard[8][5] = 'K';
	//chessboard[8][6] = 'B';
	//chessboard[8][7] = '.';
	//chessboard[8][8] = 'R';

	//HandleChessBoard(1);

	string str;
	getline(cin, str);
	cout << str << endl;

	getline(cin, str);
	cout << str << endl;

	getline(cin, str);
	cout << str << endl;

}

int main()
{
	//cout << "Test" << endl;
	//��������

	int count = 1;
	bool isFinish = InitChessBoard();
	// �ж��Ƿ����
	while (!isFinish)
	{
		// ��������
		HandleChessBoard(count++);
		// �Թ�����

		getchar();
		getchar();

		// ��ʼ������
		isFinish = InitChessBoard();
	}

	//Test();

	return 0;
}

bool InitChessBoard()
{
	// �������˵��û����������˵��������
	int count = 0;
	// Ҫ�����char
	char ch;
	for (int i = 1; i <= BOARD; ++i)
	{
		for (int j = 1; j <= BOARD; ++j)
		{
			cin >> ch;
			if (ch == '.')
			{
				++count;
			}
			chessboard[i][j] = ch;
		}
	}
	if (count == BOARD * BOARD)
	{
		return true;
	}
	return false;
}

void HandleChessBoard(int count)
{
	// �����Ƿ񱻽�
	bool isBlackCheck = false;
	// �����Ƿ񱻽�
	bool isWriteCheck = false;
	// ֻҪ��һ����������ֹͣ
	for (int i = 1; i <= BOARD && !isBlackCheck && !isWriteCheck; ++i)
	{
		for (int j = 1; j <= BOARD && !isBlackCheck && !isWriteCheck; ++j)
		{
			char ch = chessboard[i][j];
			switch(ch)
			{
			case 'p':
				isWriteCheck = IsPawnOK(i, j, ch);
				break;
			case 'P':
				isBlackCheck = IsPawnOK(i, j, ch);
				break;
			case 'n':
				isWriteCheck = IsKnightOK(i, j, ch);
				break;
			case 'N':
				isBlackCheck = IsKnightOK(i, j, ch);
				break;
			case 'b':
				isWriteCheck = IsBishopOK(i, j, ch);
				break;
			case 'B':
				isBlackCheck = IsBishopOK(i, j, ch);
				break;
			case 'r':
				isWriteCheck = IsRookOK(i, j, ch);
				break;
			case 'R':
				isBlackCheck = IsRookOK(i, j, ch);
				break;
			case 'q':
				isWriteCheck = IsQueenOK(i, j, ch);
				break;
			case 'Q':
				isBlackCheck = IsQueenOK(i, j, ch);
				break;
			case 'k':
				isWriteCheck = IsKingOK(i, j, ch);
				break;
			case 'K':
				isBlackCheck = IsKingOK(i, j, ch);
				break;
			}
		}
	}
	if (isBlackCheck)
	{
		cout << "Game #" << count << ": black king is in check." << endl;
		//printf("Game #%d: black king is in check.\n", count);  
	}
	else if (isWriteCheck)
	{
		// ����ģ�����һ�����ʴ���ˣ�����white->write
		cout << "Game #" << count << ": white king is in check." << endl;
		//printf("Game #%d: white king is in check.\n", count);  
	}
	else
	{
		cout << "Game #" << count << ": no king is in check." << endl;
		//printf("Game #%d: no king is in check.\n", count);  
	}
}

bool IsPawnOK(int x, int y, char p)
{
	// �ڷ�����
	if (p == 'p')
	{
		// ���½�
		int nX = x + 1;
		int nY = y - 1;
		// �ж��Ƿ񳬳��߽�
		if (!IsOutOfBound(nX, nY))
		{
			// �ж��Ƿ���Խ���
			if (chessboard[nX][nY] == 'K')
			{
				return true;
			}
		}
		// ���½�
		nX = x + 1;
		nY = y + 1;
		// �ж��Ƿ񳬳��߽�
		if (!IsOutOfBound(nX, nY))
		{
			// �ж��Ƿ���Խ���
			if (chessboard[nX][nY] == 'K')
			{
				return true;
			}
		}
	}
	// �׷�����
	if (p == 'P')
	{
		// ���Ͻ�
		int nX = x - 1;
		int nY = y - 1;
		// �ж��Ƿ񳬳��߽�
		if (!IsOutOfBound(nX, nY))
		{
			// �ж��Ƿ���Խ���
			if (chessboard[nX][nY] == 'k')
			{
				return true;
			}
		}
		// ���Ͻ�
		nX = x - 1;
		nY = y + 1;
		// �ж��Ƿ񳬳��߽�
		if (!IsOutOfBound(nX, nY))
		{
			// �ж��Ƿ���Խ���
			if (chessboard[nX][nY] == 'k')
			{
				return true;
			}
		}
	}
	return false;
}

bool IsOutOfBound(int x, int y)
{
	if (x >= 1 && x <= BOARD &&
		y >= 1 && y <= BOARD)
	{
		return false;
	}
	return true;
}

bool IsRookOK(int x, int y, char r)
{
	// �ڳ�
	if (r == 'r')
	{
		return IsRookOKHelp(x, y, 'K');
	}
	if (r == 'R')
	{
		return IsRookOKHelp(x, y, 'k');
	}	
}

bool IsRookOKHelp(int x, int y, char k)
{
	// �ĸ���������
	// 1.����
	for (int i = x + 1; i <= BOARD; ++i)
	{
		// ���ܳ������û������
		if (IsOutOfBound(i, y))
		{
			break;
		}
		if (chessboard[i][y] != '.')
		{
			if (chessboard[i][y] == k)
			{
				return true;
			}
			break;
		}
	}
	// 2.����
	for (int i = x - 1; i >= 1; --i)
	{
		// ���ܳ������û������
		if (IsOutOfBound(i, y))
		{
			break;
		}
		if (chessboard[i][y] != '.')
		{
			if (chessboard[i][y] == k)
			{
				return true;
			}
			break;
		}
	}
	// 3.����
	for (int i = y - 1; i >= 1; --i)
	{
		// ���ܳ������û������
		if (IsOutOfBound(x, i))
		{
			break;
		}
		if (chessboard[x][i] != '.')
		{
			if (chessboard[x][i] == k)
			{
				return true;
			}
			break;
		}
	}
	// 4.����
	for (int i = y + 1; i <= BOARD; ++i)
	{
		// ���ܳ������û������
		if (IsOutOfBound(x, i))
		{
			break;
		}
		if (chessboard[x][i] != '.')
		{
			if (chessboard[x][i] == k)
			{
				return true;
			}
			break;
		}
	}
	return false;
}

bool IsBishopOKHelp(int x, int y, char k)
{
	// �ĸ���������
	// 1.������
	for (int i = x + 1, j = y + 1; i <= BOARD && j <= BOARD; ++i, ++j)
	{
		// ���ܳ������û������
		if (IsOutOfBound(i, j))
		{
			break;
		}
		if (chessboard[i][j] != '.')
		{
			if (chessboard[i][j] == k)
			{
				return true;
			}
			break;
		}
	}
	// 2.������
	for (int i = x - 1, j = y - 1; i >= 1 && j >= 1; --i, --j)
	{
		// ���ܳ������û������
		if (IsOutOfBound(i, j))
		{
			break;
		}
		if (chessboard[i][j] != '.')
		{
			if (chessboard[i][j] == k)
			{
				return true;
			}
			break;
		}
	}
	// 3.�����ϣ�x--��y++
	for (int i = x - 1, j = y + 1; i >= 1 && j <= BOARD; --i, ++j)
	{
		// ���ܳ������û������
		if (IsOutOfBound(i, j))
		{
			break;
		}
		if (chessboard[i][j] != '.')
		{
			if (chessboard[i][j] == k)
			{
				return true;
			}
			break;
		}
	}
	// 4.�����£�x++��y--
	for (int i = x + 1, j = y - 1; i <= BOARD && j >= 1; ++i, --j)
	{
		// ���ܳ������û������
		if (IsOutOfBound(i, j))
		{
			break;
		}
		if (chessboard[i][j] != '.')
		{
			if (chessboard[i][j] == k)
			{
				return true;
			}
			break;
		}
	}
	return false;
}

bool IsBishopOK(int x, int y, char p)
{
	// ����
	if (p == 'b')
	{
		return IsBishopOKHelp(x, y, 'K');
	}
	if (p == 'B')
	{
		return IsBishopOKHelp(x, y, 'k');
	}
}

bool IsQueenOK(int x, int y, char p)
{
	if (p == 'q')
	{
		return (IsRookOK(x, y, 'r') || IsBishopOK(x, y, 'b'));
	}
	if (p == 'Q')
	{
		return (IsRookOK(x, y, 'R') || IsBishopOK(x, y, 'B'));
	}
}

bool IsKnightOKHelp(int x, int y, char p)
{
	for (int i = 0; i < 8; ++i)
	{
		int nX = x + knightMap[i][0];
		int nY = y + knightMap[i][1];
		if (IsOutOfBound(nX, nY))
		{
			continue;
		}
		if (chessboard[nX][nY] == p)
		{
			return true;
		}
	}
	return false;
}
bool IsKnightOK(int x, int y, char p)
{
	if (p == 'n')
	{
		return IsKnightOKHelp(x, y, 'K');
	}
	if (p == 'N')
	{
		return IsKnightOKHelp(x, y, 'k');
	}
}

bool IsKingOK(int x, int y, char p)
{
	if (p == 'k')
	{
		return IsKingOKHelp(x, y, 'K');
	}
	if (p == 'K')
	{
		return IsKingOKHelp(x, y, 'k');
	}
}
bool IsKingOKHelp(int x, int y, char p)
{
	for (int i = 0; i < 8; ++i)
	{
		int nX = x + kingMap[i][0];
		int nY = y + kingMap[i][1];
		if (IsOutOfBound(nX, nY))
		{
			continue;
		}
		if (chessboard[nX][nY] == p)
		{
			return true;
		}
	}
	return false;
}