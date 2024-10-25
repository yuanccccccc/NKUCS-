#include <iostream>
#include <stack>
#include <queue>
using namespace std;

class graph
{
public:
	int **m;
	int **tc;
	int n;
	graph(int num)
	{
		n = num;
		m = new int *[n + 1];
		tc = new int *[n + 1];
		for (int i = 0; i < n + 1; i++)
		{
			m[i] = new int[n + 1]{};
			tc[i] = new int[n + 1]{};
		}
	}
	void undirectedTC();
	void add(int i, int j);
	void print();
	void dfs(int source, int *reach, int label);
	bool findpath(int source, int destination);
};

void graph::print()
{
	for (int row = 1; row < n + 1; row++)
	{
		cout << "与顶点" << row << "相连的有：";
		for (int col = 1; col < n + 1; col++)
		{
			if (m[row][col] == 1)
			{
				cout << col << " ";
			}
		}
		cout << endl;
	}
}

void graph::add(int i, int j)
{
	m[i][j] = 1;
	m[j][i] = 1;
}
void graph::dfs(int source, int *reach, int label)
{
	stack<int> s;
	s.push(source);
	while (!s.empty())
	{
		int w = s.top();
		s.pop();
		for (int i = 1; i < n + 1; i++)
		{
			if (m[w][i] == 1 && reach[i] == 0) // w行i列有关系，并且第i列未被标记过
			{
				s.push(i);
				reach[i] = label;
			}
		}
	}
}

bool graph::findpath(int source, int destination)
{
	queue<int> q;
	q.push(source);
	int *test;
	test = new int[n + 1]{};
	while (!q.empty())
	{
		int w = q.front();
		q.pop();
		if (w == destination)
			return true;
		for (int j = 1; j < n + 1; j++)
		{
			if (j != source && m[w][j] == 1 && test[j] == 0)
			{
				q.push(j);
				test[j] = 1;
			}
		}
	}
	return false;
}
void graph::undirectedTC()
{
	int *reach = new int[n + 1]{};
	int label = 1;
	for (int i = 1; i < n + 1; i++)
	{
		if (reach[i] == 0)
		{
			reach[i] = label;
			dfs(i, reach, label);
			label++;
		}
	}
	for (int i = 1; i < n + 1; i++)
	{
		for (int j = 1; j < n + 1; j++)
		{
			if (i != j && m[i][j] == 0 && reach[i] == reach[j])
			{
				tc[i][j] = tc[j][i] = 1;
			}
			else if (m[i][j] == 1 && reach[i] == reach[j])
			{
				m[i][j] = m[j][i] = 0;
				if (findpath(i, j) == true)
				{
					tc[i][j] = tc[j][i] = 1;
				}
				m[i][j] = m[j][i] = 1;
			}
		}
	}
}

int main()
{
	int n, i, j;
	cout << "请输入图的节点数：";
	cin >> n;
	graph g(n);
	cout << "输入图中无向边的起点和终点,当输入-1时停止:" << endl;
	cin >> i;
	while (i != -1)
	{
		cin >> j;
		g.add(i, j);
		cin >> i;
	}
	g.print();
	g.undirectedTC();
	cout << "传递闭包为：" << endl;
	for (int i = 1; i < n + 1; i++)
	{
		for (int j = 1; j < n + 1; j++)
		{
			cout << g.tc[i][j] << ' ';
		}
		cout << endl;
	}
}