#include <iostream>
#include <queue>
using namespace std;
class Node
{
public:
    int data;
    Node *left = NULL;
    Node *right = NULL;
    Node *father = NULL;
    int h = 1; // 节点高度
    Node() {}
    Node(int da)
    {
        data = da;
    }
    int getbf()
    {
        if (left && right)
            return left->h - right->h;
        else if (left)
            return left->h;
        else if (right)
            return -right->h;
        else
            return 0;
    }
    void out()
    {
        if (left)
            left->out();
        cout << data << " ";
        if (right)
            right->out();
    }
    int getheight()
    {
        if (left && right)
            return max(left->h, right->h) + 1;
        else if (left)
            return left->h + 1;
        else if (right)
            return right->h + 1;
        else
            return 1;
    }
};
class AVLTree
{
public:
    Node *root = NULL;
    int num = 0;
    Node *Find(int dat)
    {
        Node *tem = root;
        while (tem)
        {
            if (tem->data == dat)
            {
                return tem;
            }
            else if (tem->data > dat)
                tem = tem->right;
            else
                tem = tem->left;
        }
        return NULL;
    }
    void Insert(int da)
    {
        Node *InsertNode = new Node(da);
        if (num == 0)
        {
            root = InsertNode;
            num++;
            return;
        }
        Node *ap = NULL; // 插入路径中最后一个插入前getbf()不为0的节点
        bool dir = 0;
        Node *tem = root; // 需要插入节点的父节点
        while (tem)
        {
            if (tem->getbf() != 0)
            {
                ap = tem;
                if ((tem->getbf() == -1 && da < tem->data) || (tem->getbf() == 1 && da > tem->data))
                    dir = 1;
                else
                    dir = 0;
            }
            if (tem->data == da)
                return; // 该数据已经存在
            else if (tem->data > da && tem->left)
            {
                tem = tem->left;
                continue;
            }
            else if (tem->data < da && tem->right)
            {
                tem = tem->right;
                continue;
            }
            else
                break;
        }
        num++;
        if (tem->data > da)
        {
            if (!tem->right)
                tem->h++;
            InsertNode->father = tem;
            tem->left = InsertNode;
        }
        else
        {
            if (!tem->left)
                tem->h++;
            InsertNode->father = tem;
            tem->right = InsertNode;
        }
        if (ap == NULL) // 插入前平衡因子全为0
            return;
        else
        {
            Node *t = ap;
            while (t->father != tem) // 调整tem之前的树高
            {
                if (t == tem)
                    break;
                if (da < t->data)
                {
                    t->left->h++;
                    t = t->left;
                }
                else
                {
                    t->right->h++;
                    t = t->right;
                }
            }
            if (dir == 1) // 插入时插到了比较矮的树中
            {
                Node *t = ap;
                while (t->father != tem)
                {
                    if (t == tem)
                        break;
                    if (t->data > da)
                    {
                        t->left->h++;
                        t = t->left;
                    }
                    else
                    {
                        t->right->h++;
                        t = t->right;
                    }
                }
            }
            else
            {
                if (da < ap->data) // L
                {
                    if (da < ap->left->data) // LL
                        right(ap);
                    else // LR
                    {
                        left(ap->left);
                        right(ap);
                    }
                }
                else // R
                {
                    if (da > ap->right->data) // RR
                        left(ap);
                    else // RL
                    {
                        right(ap->right);
                        left(ap);
                    }
                }
            }
        }
        root->h++;
    }
    void Delete(int da)
    {
    }
    void getleave()
    {
        queue<Node *> q;
        q.push(root);
        int ceng = 1;
        bool pan = 1;
        while (!q.empty() && pan)
        {
            for (int i = 0; i < ceng; i++)
            {
                Node *tem = q.front();
                if (tem->right && tem->left)
                {
                    q.push(tem->left);
                    q.push(tem->right);
                }
                else if (tem->left)
                    q.push(tem->left);
                else if (tem->right)
                    q.push(tem->right);
                else
                {
                    pan = 0;
                    cout << tem->data << " ";
                }
                q.pop();
            }
            ceng = q.size();
        }
    }
    void out()
    {
        cout << "root:" << root->data;
        root->out();
        cout << "height:" << root->getheight();
        cout << "最近的叶节点:";
        getleave();
        cout << endl;
    }
    void right(Node *t) // 顺时针旋转
    {
        Node *a = t;
        Node *b = a->left;
        Node *br = b->right;
        if (t == this->root)
            root = b;
        else
        {
            if (a->father->data > a->data)
                a->father->left = b;
            else
                a->father->right = b;
            b->father = a->father;
        }
        a->left = br;
        if (br != NULL)
        {
            br->father = a;
        }
        b->right = a;
        a->father = b;
        a->h = a->getheight();
        b->h = b->getheight();
    }
    void left(Node *t) // 逆时针旋转
    {
        Node *a = t;
        Node *b = a->right;
        Node *bl = b->left;
        if (t == this->root)
            root = b;
        else
        {
            if (a->father->data > a->data)
                a->father->left = b;
            else
                a->father->right = b;
            b->father = a->father;
        }
        a->right = bl;
        if (bl != NULL)
        {
            bl->father = a;
        }
        b->left = a;
        a->father = b;
        a->h = a->getheight();
        b->h = b->getheight();
    }
};
int main()
{
    AVLTree t;
    int num;
    while (true)
    {
        cin >> num;
        if (num == 0)
        {
            return 0;
        }
        t.Insert(num);
        t.out();
    }
}