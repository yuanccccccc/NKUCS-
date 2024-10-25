// 数据结构作业10.1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
// 使用BFS求最短路径

#include <iostream>
#include <queue>
using namespace std;
class node
{
public:
    int data;
    node *next;
    node *pre;
    node(int d)
    {
        data = d;
        next = NULL;
        pre = NULL;
    }
};

class list
{
public:
    node *head;
    list()
    {
        head = new node(0);
    }
    void append(int d);
    void print();
    node *find(int d);
    node *rfind(int d, list *L, int n);
};
void list::append(int d)
{
    node *newnode = new node(d);
    if (head->next == NULL)
        head->next = newnode;
    else
    {
        node *p = head;
        while (p->next != NULL)
        {
            p = p->next;
        }
        p->next = newnode;
    }
}

void list::print()
{
    node *p = head;
    while (p)
    {
        p = p->next;
        if (p)
            cout << p->data << ' ';
    }
    cout << endl;
}
node *list::find(int d)
{
    node *p = head;
    while (p)
    {
        if (p && p->data == d)
            return p;
        p = p->next;
    }
    return NULL;
}

void bfs(int source, list *L, bool *reach)
{
    for (int i = 0; i < 100; i++)
    {
        reach[i] = 1;
    }
    queue<int> Q;
    Q.push(source);
    while (!Q.empty())
    {
        int w = Q.front();
        Q.pop();
        node *p = L[w].head->next;
        for (p; p != NULL; p = p->next)
        {
            if (reach[p->data])
            {
                Q.push(p->data);
                p->pre = L[w].head;
                reach[p->data] = 0;
            }
        }
    }
}
node *rfind(int d, list *L, int n)
{
    node *t = 0;
    for (int i = 1; i <= n; i++)
    {
        if (L[i].find(d) != NULL)
        {
            if (L[i].find(d)->pre != NULL)
            {
                t = L[i].find(d);
            }
        }
    }
    return t;
}
int main()
{
    list *L;
    int n;
    cin >> n;
    int m;
    int d;
    L = new list[n + 1];
    bool *reach = new bool[100];

    for (int i = 1; i <= n; i++)
    {
        cin >> m;
        L[i].head = new node(i);
        for (int j = 0; j < m; j++)
        {
            cin >> d;
            L[i].append(d);
        }
    }
    int sour;
    int targ;
    cout << "起始点：";
    cin >> sour;
    cout << "终止点：";
    cin >> targ;
    bfs(sour, L, reach);
    int sum = 0;
    int *path;
    int index = 1;
    path = new int[100];
    node *t = rfind(targ, L, n);
    while (t)
    {
        path[index] = t->data;
        t = t->pre;
        t = rfind(t->data, L, n);
        sum++;
        index++;
    }

    path[0] = sum + 1;
    cout << "路径长度为:" << path[0] << endl;
    cout << "路径为：" << sour << ' ';
    for (int i = sum; i >= 1; i--)
        cout << path[i] << ' ';

    delete[] path;
    delete[] L;
    delete[] reach;
    return 0;
}