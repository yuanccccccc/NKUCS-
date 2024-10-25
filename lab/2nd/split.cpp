#include <iostream>
using namespace std;
class Node
{
public:
    int da;
    Node *next = nullptr;
    Node *last = nullptr;
    Node() {}
    Node(int data)
    {
        da = data;
    }
};
class chain
{
public:
    Node *first = nullptr;
    Node *tail = nullptr;
    int len = 0;
    void Insert(int data);
    void Output();
};

void split(chain c)
{
    chain a, b;
    Node *tem = c.first;
    for (int i = 0; i < c.len; i++)
    {
        if (i % 2 == 0)
            a.Insert(tem->da);
        else
            b.Insert(tem->da);
        tem = tem->next;
    }
    a.Output();
    b.Output();
}
int main()
{
    chain c;
    for (int i = 0; i < 5; i++)
    {
        c.Insert(i);
    }
    c.Output();
    split(c);
    return 0;
}
void chain::Insert(int data)
{
    Node *InsertNode = new Node(data);
    if (len == 0)
        first = InsertNode;
    else
    {
        tail->next = InsertNode;
        InsertNode->last = tail;
    }
    tail = InsertNode;
    len++;
}
void chain::Output()
{
    Node *tem = first;
    for (int i = 1; i < len; i++)
    {
        cout << tem->da << " ";
        tem = tem->next;
    }
    cout << tem->da << endl;
}