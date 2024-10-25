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
void output(Node *tem)
{
    if (tem == NULL)
        return;
    cout << tem->da;
    tem = tem->next;
    while (tem)
    {
        cout << " " << tem->da;
        tem = tem->next;
    }
    cout << endl;
}
void split(chain c)
{
    if (c.len < 0)
        return;
    Node *tem1 = c.first;
    Node *firsta = tem1;
    Node *tem2 = tem1->next;
    Node *firstb = tem2;
    for (int i = 0; i < c.len - 1; i++)
    {
        if (i % 2 == 0)
        {
            tem1->next = tem2->next;
            if (tem2->next)
                tem2->next->last = tem1;
            tem1 = tem1->next;
        }
        else
        {
            tem2->next = tem1->next;
            if (tem1->next)
                tem1->next->last = tem2;
            tem2 = tem2->next;
        }
    }
    output(firsta);
    output(firstb);
}
int main()
{
    chain c;
    for (int i = 0; i < 1; i++)
    {
        c.Insert(i);
    }
    output(c.first);
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