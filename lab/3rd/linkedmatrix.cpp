#include <iostream>
using namespace std;

class Node
{
public:
    int data;
    Node *next = NULL;
    int col;

    Node() {}
    Node(Node &m)
    {
        data = m.data;
        next = m.next;
        col = m.col;
    }
    Node(int pos, int dat)
    {
        col = pos;
        data = dat;
    }
};

class firstNode
{
public:
    int row;
    firstNode *next = NULL;
    Node *first = NULL;
    int len = 0;

    firstNode() {}
    firstNode(firstNode &m)
    {
        row = m.row;
        next = m.next;
        first = m.first;
        len = m.len;
    }
    firstNode(int r)
    {
        row = r;
    }
    void Insert(int c, int data)
    {
        if (len == 0)
        {
            first = new Node(c, data);
            len++;
            return;
        }
        if (c < first->col)
        {
            Node *InsertNode = new Node(c, data);
            InsertNode->next = first;
            first = InsertNode;
            len++;
            return;
        }
        Node *tem = first;
        while (tem->next)
        {
            if (c < tem->next->col)
            {
                Node *InsertNode = new Node(c, data);
                InsertNode->next = tem->next;
                tem->next = InsertNode;
                len++;
                return;
            }
            tem = tem->next;
        }
        Node *InsertNode = new Node(c, data);
        tem->next = InsertNode;
        len++;
        return;
    }
    int getdata(int c);
};

class lm
{
public:
    firstNode *first = NULL;
    int rowlen = 0;
    int row; // 矩阵行数
    int col; // 矩阵列数

    void Insert(int ro);
    bool Find(int ro);
    void input(int row, int col, int data); // 存储元素
    int getdata(int i, int j);
    friend ostream &operator<<(ostream &cout, lm m)
    {
        for (int i = 1; i <= m.row; i++)
        {
            cout << m.getdata(i, 1);
            for (int j = 2; j <= m.col; j++)
            {
                cout << " " << m.getdata(i, j);
            }
            cout << endl;
        }
        return cout;
    }
    friend istream &operator>>(istream &cin, lm &m)
    {
        cin >> m.row >> m.col;
        int data;
        for (int i = 1; i <= m.row; i++)
        {
            for (int j = 1; j <= m.col; j++)
            {
                cin >> data;
                m.input(i, j, data);
            }
        }
        return cin;
    }
    friend lm operator+(lm a, lm b)
    {
        lm r;
        for (int i = 1; i <= a.row; i++)
        {
            for (int j = 1; j <= a.col; j++)
            {
                int data = a.getdata(i, j) + b.getdata(i, j);
                if (data != 0)
                {
                    r.input(i, j, data);
                }
            }
        }
        return r;
    }
    friend lm operator-(lm a, lm b)
    {
        lm r;
        for (int i = 1; i <= a.row; i++)
        {
            for (int j = 1; j <= a.col; j++)
            {
                int data = a.getdata(i, j) - b.getdata(i, j);
                if (data != 0)
                {
                    r.input(i, j, data);
                }
            }
        }
        return r;
    }
    friend lm operator*(lm a, lm b)
    {
        lm r;
        r.row = a.row;
        r.col = b.col;
        for (int i = 1; i <= a.row; i++)
        {
            for (int j = 1; j <= b.col; j++)
            {
                int data = 0;
                for (int k = 1; k <= a.col; k++)
                {
                    data += a.getdata(i, k) * b.getdata(k, j);
                }
                if (data != 0)
                {
                    r.input(i, j, data);
                }
            }
        }
        return r;
    }
};
int main()
{
    lm m, n;
    cin >> m >> n;
    cout << m << n;
    lm r = m * n;
    cout << r;
}

void lm::Insert(int ro)
// 插入一行firstnode到合适的位置
{
    if (rowlen == 0)
    {
        first = new firstNode(ro);
        rowlen++;
        return;
    }
    if (ro < first->row)
    {
        firstNode *InsertNode = new firstNode(ro);
        InsertNode->next = first;
        first = InsertNode;
        rowlen++;
        return;
    }
    firstNode *tem = first;
    while (tem->next)
    {
        if (ro < tem->next->row)
        {
            firstNode *InsertNode = new firstNode(ro);
            InsertNode->next = tem->next;
            tem->next = InsertNode;
            rowlen++;
            return;
        }
        tem = tem->next;
    }
    firstNode *InsertNode = new firstNode(ro);
    tem->next = InsertNode;
    rowlen++;
    return;
}

bool lm::Find(int ro)
// 查找是否已经存在某一行
{
    firstNode *tem = first;
    while (tem)
    {
        if (tem->row == ro)
        {
            return true;
        }
        tem = tem->next;
    }
    return false;
}

void lm::input(int row, int col, int data)
// 将某个值插入到矩阵中
{
    if (data == 0)
    {
        return;
    }
    if (!Find(row))
    {
        Insert(row);
    }
    firstNode *tem = first;
    while (tem)
    {
        if (tem->row == row)
        {
            tem->Insert(col, data);
            return;
        }
        tem = tem->next;
    }
}

int lm::getdata(int i, int j)
{
    if (!Find(i))
        return 0;
    firstNode *tem = first;
    while (tem)
    {
        if (tem->row == i)
        {
            return tem->getdata(j);
        }
        tem = tem->next;
    }
}

int firstNode::getdata(int c)
{
    Node *tem = first;
    while (tem)
    {
        if (tem->col == c)
        {
            return tem->data;
        }
        tem = tem->next;
    }
    return 0;
}
