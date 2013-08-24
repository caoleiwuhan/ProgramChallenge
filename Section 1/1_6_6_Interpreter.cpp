#include <iostream>
#include <cstring>
#include <string>
#include <cstdio>

using namespace std;

// register
int reg[11];
// memory
int memory[1010];

/*
	����memory����ʼ�������㣬
	����һ��ִ�еĴ���
*/
int Execute();

/*
	����һ����λ�����õ��ڶ�λ������λ��ֵ
*/
void ParseNum(int num, int &n2, int &n3);

void Test();


//int main()
//{
//	//cout << "Test" << endl;
//	int count = 0;	
//	cin >> count;
//
//	char ch;
//	// �����һ������
//	ch = cin.get();
//
//	while (count--)
//	{
//		memset(memory, 0, sizeof(memory));
//		memset(reg, 0, sizeof(reg));
//		// �ڴ��index
//		int index = 0;
//		// �ӿ���̨�����ڴ����
//		int num = 0;
//
//		while (true)
//		{
//			ch = cin.get();
//			ch = cin.peek();
//			if (ch == '\n')
//			{
//				break;
//			}
//			else
//			{
//				cin >> num;
//				memory[index++] = num;
//			}
//		}
//		cout << Execute() << endl;
//		if (count)
//		{
//			cout << endl;
//		}
//	}
//	return 0;
//}


int main()
{
	int count = 0;	
	cin >> count;

	getchar();
	getchar();

	char buf[11];

	while (count--)
	{
		memset(memory, 0, sizeof(memory));
		memset(reg, 0, sizeof(reg));
		// �ڴ��index
		int index = 0;
		// �ӿ���̨�����ڴ����
		int num = 0;

		while (gets(buf))
		{			
			if (buf[0] == '\0')
			{
				break;
			}			
			sscanf(buf, "%d", &memory[index]);
			++index;			
		}

		cout << Execute() << endl;
		if (count)
		{
			cout << endl;
		}
	}

	return 0;
}

int Execute()
{
	// ָ��ִ�е�����
	int ans = 0;
	// ��0��ʼ
	// �ڴ��е�index
	int curIndex = 0;
	// ��ǰִ�е�ָ��
	int instr = memory[curIndex];

	while (instr != 100)
	{
		// ��һ��
		++curIndex;
		++ans;
		// ��ǰָ�������
		int kind = instr / 100;
		int d = 0;
		int n = 0;
		int s = 0;
		int a = 0;
		switch(kind)
		{
		case 2:
			ParseNum(instr, d, n);
			// ���Ĵ�����ֵ��Ϊn
			reg[d] = n;
			break;
		case 3:			
			ParseNum(instr, d, n);
			// ���Ĵ�����ֵ����N
			reg[d] = (reg[d] + n) % 1000;
			break;
		case 4:
			ParseNum(instr, d, n);
			// ���Ĵ�����ֵ����N
			reg[d] = (reg[d] * n) % 1000;
			break;
		case 5:
			ParseNum(instr, d, s);
			// ��s��ֵ����d
			reg[d] = reg[s];
			break;
		case 6:
			ParseNum(instr, d, s);
			// ��s��ֵ�ӵ�d
			reg[d] = (reg[d] + reg[s]) % 1000;
			break;
		case 7:
			ParseNum(instr, d, s);
			// ��s��ֵ�˸�d
			reg[d] = (reg[d] * reg[s]) % 1000;
			break;
		case 8:
			ParseNum(instr, d, a);
			reg[d] = memory[reg[a]];
			break;
		case 9:
			ParseNum(instr, s, a);
			memory[reg[a]] = reg[s];
			break;		
		case 0:
			ParseNum(instr, d, s);
			if (reg[s])
			{
				curIndex = reg[d];
			}
			break;
		}
		instr = memory[curIndex];
	}
	++ans;
	return ans;
}


void ParseNum(int num, int &n2, int &n3)
{
	n3 = num % 10;
	n2 = (num / 10) % 10;
}

void Test()
{
	// ����078
	//int num;
	//cin >> num;
	//memory[0] = num;

	memset(memory, 0, sizeof(memory));
	memset(reg, 0, sizeof(reg));

	memory[0] = 299;
	memory[1] = 492;
	memory[2] = 495;
	memory[3] = 399;
	memory[4] = 492;
	memory[5] = 495;
	memory[6] = 399;
	memory[7] = 283;
	memory[8] = 279;
	memory[9] = 689;
	memory[10] = 78;
	memory[11] = 100;
	memory[12] = 0;
	memory[13] = 0;
	memory[14] = 0;
	Execute();
}