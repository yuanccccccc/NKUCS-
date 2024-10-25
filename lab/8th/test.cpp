#include <iostream>
#include <string.h>
#include <cmath>
#include <fstream>
using namespace std;
class treenode
{
public:
    int data;
    treenode *leftchild = NULL;
    treenode *rightchild = NULL;
    int height;
    treenode(int n)
    {
        data = n;
    }
    treenode(){};
};
class queue
{
public:
    treenode *q[100];
    int tail = 0;
    int size = 0;
    queue &push(treenode *r)
    {
        if (r != NULL)
        {
            q[tail] = r;
            tail++;
        }
        size++;
        return *this;
    }
    treenode *pop()
    {
        if (tail != 0)
        {
            treenode *temp = q[0];
            for (int i = 0; i < tail - 1; i++)
            {
                q[i] = q[i + 1];
            }
            tail--;
            size--;
            return temp;
        }
        else
            return NULL;
    }
    bool empty()
    {
        if (size == 0)
        {
            return true;
        }
        else
            return false;
    }
};
class AVL
{
public:
    treenode *root = NULL;
    void Insert(int n, treenode *&r);
    void LL(treenode *&temp);
    void LR(treenode *&temp);
    void RR(treenode *&temp);
    void RL(treenode *&temp);
    void Delete(int n, treenode *&r);
    int hight(treenode *temp);
    void zuijin();
    void output(treenode *root, int i);
    int getheight(treenode *t);
};
int AVL::getheight(treenode *t)
{
    if (t == NULL)
        return 0;
    else
        return t->height;
}
int AVL::hight(treenode *temp)
{
    if (temp == NULL)
        return 0;
    int l = hight(temp->leftchild);
    int r = hight(temp->rightchild);
    if (l > r)
        return l + 1;
    else
        return r + 1;
}

void AVL::Insert(int n, treenode *&r)
{ // 递归插入
    if (r == NULL)
    {
        r = new treenode(n);
    }
    else if (n < r->data)
    {
        Insert(n, r->leftchild);
        if (getheight(r->leftchild) - getheight(r->rightchild) == 2)
        {
            if (getheight(r->leftchild->leftchild) > getheight(r->leftchild->rightchild))
                LL(r);
            else
                LR(r);
        }
    }
    else if (n > r->data)
    {
        Insert(n, r->rightchild);
        if (getheight(r->rightchild) - getheight(r->leftchild) == 2)
        {
            if (getheight(r->rightchild->rightchild) > getheight(r->rightchild->leftchild))
                RR(r);
            else
                RL(r);
        }
    }
    else
    { // 当该节点已经存在时
        return;
    }
    // 确保r的左右孩子在插入后均已更新成新的高度
    r->height = hight(r);
}
void AVL::LL(treenode *&temp)
{
    treenode *cur = temp->leftchild;
    temp->leftchild = cur->rightchild;
    cur->rightchild = temp;
    temp->height = hight(temp);
    cur->height = hight(cur);
    temp = cur;
}
void AVL::RR(treenode *&temp)
{
    treenode *cur = temp->rightchild;
    temp->rightchild = cur->leftchild;
    cur->leftchild = temp;
    temp->height = hight(temp);
    cur->height = hight(cur);
    temp = cur;
}
void AVL::LR(treenode *&temp)
{ // LR型是先对temp节点的左孩子进行RR旋转，再对temp进行LL旋
    RR(temp->leftchild);
    LL(temp);
}
void AVL::RL(treenode *&temp)
{ // RL型是先对temp节点的右孩子进行LL旋转，再对temp进行RR旋转
    LL(temp->rightchild);
    RR(temp);
}
void AVL::Delete(int n, treenode *&r)
{
    if (r == NULL)
        return; // 没有n
    if (n < r->data)
    {
        Delete(n, r->leftchild);
    }
    else if (n > r->data)
    {
        Delete(n, r->rightchild);
    }
    else
    {
        if (r->leftchild != NULL && r->rightchild != NULL)
        {
            treenode *t = r->leftchild;
            while (t->rightchild != NULL)
            {
                t = t->rightchild;
            }
            r->data = t->data;
            Delete(r->data, r->leftchild);
        }
        else
        {
            if (r->leftchild == NULL && r->leftchild == NULL)
            {
                delete r;
                r = NULL;
            }
            else if (r->leftchild == NULL && r->rightchild != NULL)
            {
                r = r->rightchild;
            }
            else if (r->rightchild == NULL && r->leftchild != NULL)
            {
                r = r->leftchild;
            }
            return;
        }
    }
    if (getheight(r->leftchild) - getheight(r->rightchild) == 2)
    {
        if (getheight(r->leftchild->leftchild) > getheight(r->leftchild->rightchild))
            LL(r);
        else
            LR(r);
    }
    else if (getheight(r->rightchild) - getheight(r->leftchild) == 2)
    {
        if (getheight(r->rightchild->rightchild) > getheight(r->rightchild->leftchild))
            RR(r);
        else
            RL(r);
    }
    r->height = hight(r);
}

void AVL::output(treenode *root, int i)
{
    if (root)
    {
        i++;
        output(root->rightchild, i);
        for (int j = 0; j < i; j++)
            cout << "     ";
        if (root != NULL)
            cout << root->data << endl;
        output(root->leftchild, i);
    }
}
void AVL::zuijin()
{
    queue a;
    treenode *temp;
    a.push(root);
    while (true)
    {
        if (a.empty())
            break;
        int l = a.size;
        int e = 0;
        while (l > 0)
        {
            temp = a.pop();
            l--;
            if (temp->leftchild == NULL && temp->rightchild == NULL)
            {
                cout << temp->data << " ";
                e = 1;
            }
            a.push(temp->leftchild);
            a.push(temp->rightchild);
        }
        if (e == 1)
            break;
    }
    return;
}
int main()
{
    AVL a;
    ifstream infile = ifstream("TextFile1.txt");
    int b;
    for (int i = 1; i <= 13; i++)
    {
        infile >> b;
        a.Insert(b, a.root);
    }
    a.output(a.root, -1);
    cout << "树的高度为：" << a.root->height << endl;
    cout << "距离根最近的叶节点的值为:";
    a.zuijin();
    cout << endl;
    for (int i = 1; i <= 3; i++)
    {
        infile >> b;
        a.Delete(b, a.root);
    }
    a.output(a.root, -1);
    cout << "树的高度为：" << a.root->height << endl;
    cout << "距离根最近的叶节点的值为:";
    a.zuijin();
    return 0;
}