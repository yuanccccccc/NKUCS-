#include <iostream>
#include <fstream>
using namespace std;

class Node
{
public:
    char le;
    Node *next = NULL;
    Node(char c) { le = c; }
    Node() {}
};
class Stack
{
public:
    Node *first = NULL;
    int size = 0;
    char pop()
    {
        char re = first->le;
        first = first->next;
        size--;
        return re;
    }
    void push(char c)
    {
        size++;
        Node *InsertNode = new Node(c);
        InsertNode->next = first;
        first = InsertNode;
    }
    void out()
    {
        if (size == 0)
            return;
        Node *tem = first;
        cout << tem->le;
        tem = tem->next;
        for (int i = 1; i < size; i++)
        {
            cout << " " << tem->le;
            tem = tem->next;
        }
        cout << endl;
    }
};
void delete_all(Stack &s, const char &x)
{
    Stack tem;
    int len = s.size;
    for (int i = 0; i < len; i++)
    {
        int con = s.pop();
        if (con == x)
        {
            continue;
        }
        tem.push(con);
    }
    len = tem.size;
    for (int i = 0; i < len; i++)
    {
        s.push(tem.pop());
    }
}
int main()
{
    ifstream outfile;
    outfile.open("input.txt", ios::out);
    if (!outfile)
    {
        cerr << "WRONG!" << endl;
        return 0;
    }
    Stack c;
    char let;
    outfile >> let;
    char tem;
    while (outfile >> tem)
    {
        c.push(tem);
    }
    outfile.close();
    delete_all(c, let);
    c.out();
    cout << endl;
}