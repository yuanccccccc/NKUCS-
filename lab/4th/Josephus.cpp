#include <iostream>
#include <fstream>
using namespace std;

class Node
{
public:
    int data = 0;
    Node *next = NULL;
    Node(int t)
    {
        data = t;
    }
};

class stack
{
public:
    Node *first = NULL;
    int len = 0;
    void Insert();
    void Delete(Node *tem);
};

int main()
{
    ifstream outfile;
    outfile.open("input.txt", ios::out);
    if (!outfile)
    {
        cerr << "WRONG!" << endl;
        return 0;
    }
    int n, m;
    outfile >> n >> m;
    if (n < 3 || n > 100 || m < 1)
    {
        cerr << "WRONG!" << endl;
        return 0;
    }
    stack k;
    for (int i = 1; i <= n; i++)
    {
        k.Insert();
    }
    Node *tem = k.first;
    for (int i = 1; k.len != 1; i++)
    {
        if (i % m == 0)
        {
            k.Delete(tem);
            cout << tem->data << " ";
        }
        tem = tem->next;
    }
    cout << tem->data << endl;
    int *a = new int[n];
    for (int i = 0; i < n; i++)
    {
        a[i] = i + 1;
    }
    int t = n;
    int num = 1;
    for (int i = 0; t > 1; i++)
    {
        if (i > n - 1)
        {
            i = i - n;
        }
        if (num % m == 0 && a[i] != 0)
        {
            num++;
            cout << a[i] << " ";
            a[i] = 0;
            t--;
        }
        else if (a[i] != 0)
        {
            num++;
        }
    }
    for (int i = 0; i < n; i++)
    {
        if (a[i] != 0)
        {
            cout << a[i] << endl;
        }
    }
}

void stack::Insert()
{
    if (len == 0)
    {
        first = new Node(++len);
        first->next = first;
        return;
    }
    else
    {
        Node *tem = first;
        for (int i = 0; i < len - 1; i++)
        {
            tem = tem->next;
        }
        Node *InsertNode = new Node(++len);
        InsertNode->next = tem->next;
        tem->next = InsertNode;
    }
}

void stack::Delete(Node *tem)
{
    Node *t = tem;
    while (t->next != tem)
    {
        t = t->next;
    }
    t->next = t->next->next;
    len--;
}
