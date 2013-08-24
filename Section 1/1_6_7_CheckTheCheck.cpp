#include <iostream>
#include <cstdio>
#include <string>

using namespace std;

// 棋盘边界
const int BOARD = 8;

// 棋盘，尝试从1开始
char chessboard[BOARD + 1][BOARD + 1];

/*
	读入棋盘，并且返回是否结束标志
*/
bool InitChessBoard();

/*
	处理棋盘
*/
void HandleChessBoard(int count);

/*
	判断x、y是否超出边界
*/
bool IsOutOfBound(int x, int y);

/*
	卒的情况：
	传入卒子的位置、大小写情况，判断是否将军
*/
bool IsPawnOK(int x, int y, char p);


/*
	车：
	传入车的位置、大小写情况，判断是否将军
	注意不能越过去！
*/
bool IsRookOK(int x, int y, char p);

bool IsRookOKHelp(int x, int y, char k);

/*
	象：
	传入车的位置、大小写情况，判断是否将军
	注意不能越过去！
*/
bool IsBishopOK(int x, int y, char p);

bool IsBishopOKHelp(int x, int y, char k);

/*
	皇后
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
	马
*/
bool IsKnightOK(int x, int y, char p);
bool IsKnightOKHelp(int x, int y, char p);

/*
	国王：
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
	测试程序
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
	//读入棋盘

	int count = 1;
	bool isFinish = InitChessBoard();
	// 判断是否结束
	while (!isFinish)
	{
		// 处理棋盘
		HandleChessBoard(count++);
		// 略过空行

		getchar();
		getchar();

		// 初始化棋盘
		isFinish = InitChessBoard();
	}

	//Test();

	return 0;
}

bool InitChessBoard()
{
	// 如果有王说明没结束，否则说明结束了
	int count = 0;
	// 要读入的char
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
	// 黑王是否被将
	bool isBlackCheck = false;
	// 白王是否被将
	bool isWriteCheck = false;
	// 只要有一个被将，则停止
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
		// 他妈的！！！一个单词打错了！！！white->write
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
	// 黑方卒子
	if (p == 'p')
	{
		// 左下角
		int nX = x + 1;
		int nY = y - 1;
		// 判断是否超出边界
		if (!IsOutOfBound(nX, nY))
		{
			// 判断是否可以将军
			if (chessboard[nX][nY] == 'K')
			{
				return true;
			}
		}
		// 右下角
		nX = x + 1;
		nY = y + 1;
		// 判断是否超出边界
		if (!IsOutOfBound(nX, nY))
		{
			// 判断是否可以将军
			if (chessboard[nX][nY] == 'K')
			{
				return true;
			}
		}
	}
	// 白方卒子
	if (p == 'P')
	{
		// 左上角
		int nX = x - 1;
		int nY = y - 1;
		// 判断是否超出边界
		if (!IsOutOfBound(nX, nY))
		{
			// 判断是否可以将军
			if (chessboard[nX][nY] == 'k')
			{
				return true;
			}
		}
		// 右上角
		nX = x - 1;
		nY = y + 1;
		// 判断是否超出边界
		if (!IsOutOfBound(nX, nY))
		{
			// 判断是否可以将军
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
	// 黑车
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
	// 四个方向延伸
	// 1.向下
	for (int i = x + 1; i <= BOARD; ++i)
	{
		// 不能出界而且没有棋子
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
	// 2.向上
	for (int i = x - 1; i >= 1; --i)
	{
		// 不能出界而且没有棋子
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
	// 3.向左
	for (int i = y - 1; i >= 1; --i)
	{
		// 不能出界而且没有棋子
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
	// 4.向右
	for (int i = y + 1; i <= BOARD; ++i)
	{
		// 不能出界而且没有棋子
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
	// 四个方向延伸
	// 1.向右下
	for (int i = x + 1, j = y + 1; i <= BOARD && j <= BOARD; ++i, ++j)
	{
		// 不能出界而且没有棋子
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
	// 2.向左上
	for (int i = x - 1, j = y - 1; i >= 1 && j >= 1; --i, --j)
	{
		// 不能出界而且没有棋子
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
	// 3.向右上：x--、y++
	for (int i = x - 1, j = y + 1; i >= 1 && j <= BOARD; --i, ++j)
	{
		// 不能出界而且没有棋子
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
	// 4.向左下：x++、y--
	for (int i = x + 1, j = y - 1; i <= BOARD && j >= 1; ++i, --j)
	{
		// 不能出界而且没有棋子
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
	// 黑象
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