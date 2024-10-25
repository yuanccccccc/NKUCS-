#include <iostream>
using namespace std;
// 输入哈希表计算的除数
// 然后输入数据的个数
// 再输入要删除的数据
// 最后输入-1输出操作后的哈希表
class Node
{
public:
    int data;
    Node *next = NULL;
    Node(int num)
    {
        data = num;
    }
};
class List
{
public:
    int len = 0;
    Node *first = NULL;
    Node *tail = NULL;
    void Insert(int data);
    void output();
    void Delete(int num);
};
class hashtable
{
public:
    int len;                      // 同时是除数
    Node *tailNode = new Node(0); // 共享的尾节点
    List *l;                      // 空桶数组
    int column = 0;
    hashtable(int num)
    {
        len = num;
        l = new List[len];
    }
    void Insert(int data)
    {
        int n = data % len;
        l[n].Insert(data);
        l[n].tail->next = tailNode;
        column++;
    }
    void output();
    void Delete(int num);
};
bool Find(int *a, int len, int num)
{
    for (int i = 0; i < len; i++)
    {
        if (a[i] == num)
            return true;
    }
    return false;
}
int main()
{
    int yushu;
    cout << "请输入除数" << endl;
    cin >> yushu; // 输入余数
    hashtable t(yushu);
    int len;
    cout << "请输入要储存的数据个数" << endl;
    cin >> len; // 输入的数的长度
    int *num = new int[len];
    cout << "请输入要储存的数据" << endl;
    for (int i = 0; i < len; i++) // 输入数据
    {
        cin >> num[i];
        t.Insert(num[i]);
    }
    int n; // 要删除的数
    cout << "请输入要删除的数" << endl;
    while (true)
    {
        cout << "输入-1输出当前结果并结束程序" << endl;
        if (t.column == 0)
        {
            cout << "哈希表已经为空" << endl;
            return 0;
        }
        cin >> n; // 输入
        if (n == -1)
            break;
        if (!Find(num, len, n))
        {
            cout << "要删除的数据不存在" << endl;
            continue;
        }
        t.Delete(n);
    }
    t.output();
}

void List::Insert(int data)
{
    Node *InsertNode = new Node(data);
    if (len == 0)
    {
        first = InsertNode;
        tail = InsertNode;
    }
    else if (data < first->data)
    {
        InsertNode->next = first;
        first = InsertNode;
    }
    else if (data > tail->data)
    {
        tail->next = InsertNode;
        tail = tail->next;
    }
    else if (data = tail->data)
    {
        return;
    }
    else
    {
        Node *tem = first;
        while (tem->next)
        {
            if (tem->next->data > data)
            {
                InsertNode->next = tem->next;
                tem->next = InsertNode;
                return;
            }
            tem = tem->next;
        }
    }
    len++;
}

void List::output()
{
    if (len == 0)
    {
        cout << "该链表为空" << endl;
        return;
    }
    Node *tem = first;
    for (int i = 0; i < len; i++)
    {
        if (i == len - 1)
            cout << tem->data << endl;
        else
            cout << tem->data << " ";
        tem = tem->next;
    }
}

void List::Delete(int num)
{
    if (first->data == num)
    {
        Node *DeleteNode = first;
        first = DeleteNode->next;
        delete DeleteNode;
        len--;
        return;
    }
    Node *tem = first;
    while (tem->next)
    {
        if (tem->next->data == num)
        {
            Node *DeleteNode = tem->next;
            tem->next = DeleteNode->next;
            delete DeleteNode;
            len--;
            return;
        }
        tem = tem->next;
    }
    cout << "删除的数据不存在" << endl;
}

void hashtable::output()
{
    for (int i = 0; i < len; i++)
    {
        cout << i << ":";
        l[i].output();
    }
}
void hashtable::Delete(int num)
{
    int n = num % len;
    l[n].Delete(num);
    column--;
}