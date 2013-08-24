
#include <string>
#include <cstring>
#include <iostream>
#include <queue>
#include <map>

using namespace std;

#define MAXN 100
#define EARLIER 18
#define LATER 6
#define HOURS 24
#define NO_ROUTE (-1)

// ��ǰ·�ߵ�״̬������ city ��־��ǰ����ĳ��У�time ��ʾ�����ʱ�䣬litres ��ʾ�Ѿ�ʹ�õ�Ѫ����
class state
{
public:
	int city, time, litres;

	// ʹ��Ѫ���ٵ�·���ȴ���
	bool operator<(const state at) const
	{
		return litres > at.litres;
	}
	state(int _city, int _time, int _litres)
	{
		city = _city;
		time = _time;
		litres = _litres;
	}
};

// ��·�ߡ�
class route
{
public:
	int departure;		// ����ʱ�䡣
	int arrive;		// ����ʱ�䡣
	int to;			// ������С�

	route(int _dep, int _arr, int _to)
	{
		departure = _dep;
		arrive = _arr;
		to = _to;
	}
};

// ����֮��Ļ�·�ߡ�
vector < route > edges[MAXN + 1];

// ʹ�����ȶ��еķ������������д���ʼ���� from �� �յ���� to ��·�ߡ��ڴ˹����У��ȴ���ʹ��Ѫ
// ���ٵ�·�ߣ������ֵ�ǰ·�ߵ�״̬ state ����־�ĳ��� city �Ѿ�ΪĿ����� to ʱ��������ǰ��Ҫ
// Ѫ�����ٵ�·�߼�Ϊ�� state ���ߵ�·�ߡ�
int travel(int from, int to)
{
	// �������ȶ��У���ҪѪ���ٵ�·���ȴ���
	priority_queue < state > states;

	// ����ǰ����Ϊ from������ʱ��Ϊ 18:00 ��״̬��ӵ����ȶ����У���ʾ�Ѿ���һ������ĵ�
	// ����������ʼ���� from������ʱ��С����ʼ���� from �����п��û�·�ߵĳ���ʱ�䣬��ǰ
	// �Ѿ�ʹ��Ѫ��Ϊ 0 ����
	states.push(state(from, EARLIER, 0));

	// ��������е�·��״̬��
	while (!states.empty())
	{
		// ȡ�����׵�·��״̬����
		state current = states.top();
		states.pop();

		// ����ǰ�����Ѿ�ΪĿ����У���ֱ�ӷ��ص�ǰ·����ʹ�õ�Ѫ����
		if (current.city == to)
			return current.litres;

		// ������ǰ����������������еĻ�·�ߣ�������������Ƿ���Ҫȡ�� 1 ����Ѫ��
		for (int r = 0; r < edges[current.city].size(); r++)
		{
			int used = current.litres;
			// ������ʱ�����ڸû�·�߳���ʱ�䣬�����ڴ˳�վͣ��һ�����磬ȡѪ 1 ����
			if (current.time > edges[current.city][r].departure)
				used++;

			states.push(state(edges[current.city][r].to,edges[current.city][r].arrive, used));
		}

	}

	// ��ʼ������Ŀ���������ͨ·�ߡ�
	return NO_ROUTE;
}

int main(int ac, char *av[])
{
	int test, routes, cases = 1;
	int from, to;
	string start, destination;
	int departure, traveling;

	cin >> test;
	while (test--)
	{
		map < string, int > cities;

		for (int i = 0; i < MAXN + 1; i++)
			edges[i].clear();

		cin >> routes;
		for (int i = 1; i <= routes; i++)
		{
			// ������ʼ���յ���С�����ʱ�䡢����ʱ�䣬��������뵽 map �С�
			cin >> start >> destination >> departure >> traveling;

			if (cities.find(start) == cities.end())
			{
				from = cities.size();
				cities[start] = from;
			}
			else
				from = cities[start];

			if (cities.find(destination) == cities.end())
			{
				to = cities.size();
				cities[destination] = to;
			}
			else
				to = cities[destination];

			// ����������·������ӵ�����ͼ�С�������ʱ��Ϊ�賿������� 24 Сʱ
			// ��ͳһʱ����㡣
			departure += (departure <= LATER ? HOURS : 0);
			if (departure >= EARLIER
				&& (departure + traveling) <= (HOURS + LATER))
				edges[from].push_back(route(departure,
						(departure + traveling), to));
		}

		// �����͵�����С�
		cin >> start >> destination;

		cout << "Test Case " << cases++ << "." << endl;

		// ���������������ʼ��Ŀ�������ͬ��
		if (start == destination)
		{
			cout << "Vladimir needs 0 litre(s) of blood." << endl;
			continue;
		}

		// ���������������ʼ��Ŀ����в������������С�
		if (cities.find(start) == cities.end()
			|| cities.find(destination) == cities.end())
		{
			cout << "There is no route Vladimir can take." << endl;
			continue;
		}

		// ȡ����ʼ��Ŀ����е���š�
		from = cities[start];
		to = cities[destination];

		// ��������·�����ҵ��ӳ��� from ������ to ���������Ѫ����
		int litres = travel(from, to);

		if (litres == NO_ROUTE)
			cout << "There is no route Vladimir can take." << endl;
		else
			cout << "Vladimir needs " << litres << " litre(s) of blood." << endl;
	}

	return 0;
}