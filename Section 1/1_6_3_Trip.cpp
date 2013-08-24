#include <iostream>
#include <cstdio>

using namespace std;

/*
	�����������棡����
*/

/*
	���룺money���飬ѧ����
	����ÿ��ѧ����money
*/
void InputMoney(double money[], int stuNum)
{
	for (int i = 0; i < stuNum; ++i)
	{
		cin >> money[i];
	}
}

/*
	����num
	��һ��double�����������뱣��2λС��
*/
double ChangeNum(double num)
{
	return ((int)(num * 100 + 0.5)) / 100.0;
}

/*
	����money��ѧ���������ػ��ѵ�ƽ����
*/
double AverageMoney(double money[], int stuNum)
{
	double average = 0.0;
	double total = 0.0;
	for (int i = 0; i < stuNum; ++i)
	{
		total += money[i];
	}
	total = ChangeNum(total);
	average = ChangeNum(total / stuNum);
	return average;
}

/*
	���룺ÿ��ѧ���Ļ��ѣ�ѧ����
	�����ܽ�����
	����ܽ�����
*/
double TotalMoney(double money[], int stuNum)
{
	// 1.����ƽ����:�Ѿ��������뱣����λС��
	double average = AverageMoney(money, stuNum);
	double ans1 = 0.0;
	double ans2 = 0.0;

	for (int i = 0; i < stuNum; ++i)
	{
		if (money[i] > average)
		{
			ans1 += (money[i] - average);
		}
		else
		{
			ans2 += (average - money[i]);
		}
	}
	if (ans1 > ans2)
	{
		ans1 = ans2;
	}
	return ans1;
}

void TestOutPut()
{
	double d1 = 36.02;
	double d2 = d1 / 4;
	d2 = ChangeNum(d2);
	double d3 = 15.00 - d2;
	double d4 = 15.01 - d2;
	double d5 = d3 + d4;
	

	printf("%.2f\n", d1);
	printf("%.2f\n", d2);
	printf("%.2f\n", d3);
	printf("%.2f\n", d4);
	printf("%.2f\n", d5);
}

int main()
{
	// ѧ����
	int stuNum = 0;
	// �洢ÿ��ѧ����Ǯ����������1000
	double money[1000];
	// ���׵���Ǯ��
	double total = 0.0;
	while (cin >> stuNum)
	{
		if (stuNum == 0)
		{
			break;
		}
		// ����ѧ����Ǯ��
		InputMoney(money, stuNum);
		// �����ܵĽ���Ǯ��
		total = TotalMoney(money, stuNum);
		printf("$%.2f\n", total);
	}

	//TestOutPut();
	return 0;
}

