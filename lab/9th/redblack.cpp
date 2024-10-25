#include <iostream>
using namespace std;
enum Color
{
    red,
    black
};

class Node
{
public:
    Color color = red;
    Node *left = NULL;
    Node *right = NULL;
    Node *father = NULL;
    int data = 0;
    Node() {}
    Node(int dat)
    {
        data = dat;
    }
    void out()
    {
        if (left)
            left->out();
        cout << data << "(" << color << ") ";
        if (right)
            right->out();
    }
};
class rbTree
{
public:
    int num = 0;
    Node *root = NULL;
    void out()
    {
        cout << "(root:" << root->data << ") ";
        root->out();
        cout << endl;
    }
    void Insert(int da)
    {
        Node *InsertNode = new Node(da);
        if (num == 0)
        {
            root = InsertNode;
            root->color = black;
            num++;
            return;
        }
        Node *tem = root;
        while (tem)
        {
            if (da == tem->data)
                return;
            else if (da > tem->data && tem->right)
            {
                tem = tem->right;
                continue;
            }
            else if (da < tem->data && tem->left)
            {
                tem = tem->left;
                continue;
            }
            else
                break;
        }
        num++;           // 个数增加
        if (tem == root) // 根节点的插入
        {
            if (da > tem->data)
            {
                tem->right = InsertNode;
                InsertNode->father = root;
            }
            else
            {
                tem->left = InsertNode;
                InsertNode->father = root;
            }
            return;
        }
        if (da > tem->data) // 非根节点的插入
        {
            tem->right = InsertNode;
            InsertNode->father = tem;
        }
        else
        {
            tem->left = InsertNode;
            InsertNode->father = tem;
        }
        if (tem->color == red) // 父节点为red
        {
            adjust(InsertNode);
        }
    }
    void Delete(int da)
    {
        if (num == 0) // 如果为空则返回
            return;
        Node *tem = root;
        while (tem)
        {
            if (tem->data == da)
                break;
            else if (tem->data > da && tem->left)
                tem = tem->left;
            else if (tem->data < da && tem->right)
                tem = tem->right;
            else
                return; // 要删除的节点不存在
        }
        num--;
        Node *de;                      // 实际上删除的节点
        if (!tem->left && !tem->right) // 叶节点
        {
            del(tem);
            if (tem->data < tem->father->data)
                tem->father->left = NULL;
            else
                tem->father->right = NULL;
        }
        else // 内部节点的删除
        {
            if (tem->left) // 左子树不为空
            {
                Node *t = tem->left;
                while (t->right)
                    t = t->right; // 得到左子树最右边的元素
                de = t;
                del(de);
                if (de->father->data > de->data)
                {
                    de->father->left = de->left;
                    if (de->left)
                        de->father->left->father = de->father;
                }
                else
                {
                    de->father->right = de->left;
                    if (de->left)
                        de->father->right->father = de->father;
                }
                tem->data = t->data;
            }
            else // 左子树为空，该节点肯定是黑色的，且该节点只有一个红节点为孩子
            {
                Node *te = tem->left == NULL ? tem->right : tem->left;
                if (tem->data < tem->father->data)
                    tem->father->left = te;
                else
                    tem->father->right = te;
                te->father = tem->father;
            }
        }
    }
    void del(Node *t) // 对真正删除的节点进行调整
    {
        if (!t->right && !t->left && t->color == red) // 如果是叶节点且为红色
        {                                             // 直接清空就可以
            if (t->father->data < t->data)
                t->father->right = NULL;
            else
                t->father->left = NULL;
        }
        else
        {
            if (t->color == red)                                 // 如果不是叶的红色节点，父节点一定是黑色
            {                                                    // 左节点向上移动一个
                Node *te = t->left == NULL ? t->right : t->left; // t唯一的孩子
                if (t->father->data > t->data)
                    t->father->left = te;
                else
                    t->father->right = te;
                te->father = t->father;
            }
            else // 黑色节点
            {
                bool Right = t->father->right == t; // t为父节点的右孩子
                Node *f = t->father;
                Node *u = Right ? t->father->left : t->father->right; // t的兄弟节点
                Node *w = Right ? u->left : u->right;
                if (u->color == black) // u为黑色
                {
                    if (w == NULL ? true : w->color == black)
                    {
                        Node *r = Right ? u->right : u->left;
                        if (r == NULL ? true : r->color == black)
                        {
                            if (f->color == red)
                                swap(f->color, u->color);
                            else // 全都是黑色的
                            {    // 向上进行递归遍历
                                if (f != root)
                                {
                                    f->color = red;
                                    del(f); // 重新进行调整
                                }
                            }
                        }
                        else
                        {
                            if (Right)
                            {
                                ni(u);
                                shun(f);
                            }
                            else
                            {
                                shun(u);
                                ni(f);
                            }
                        }
                    }
                    else
                    {
                        Color fc = f->color; // 父节点的颜色
                        if (Right)
                            shun(f);
                        else
                            ni(f);
                        f->color = black;
                        w->color = black;
                        u->color = fc;
                        return;
                    }
                }
                else // u为红色，f一定为黑色
                {
                    Node *r = Right ? u->right : u->left;
                    Node *s = Right ? r->left : r->right;
                    if (s->color == red)
                    {
                        if (Right)
                        {
                            ni(u);
                            shun(f);
                        }
                        else
                        {
                            shun(u);
                            ni(f);
                        }
                        s->color = black;
                    }
                    else
                    {
                        Node *rl = Right ? r->right : r->left;
                        if (Right)
                        {
                            ni(r);
                            ni(u);
                            shun(f);
                        }
                        else
                        {
                            shun(r);
                            shun(u);
                            ni(f);
                        }
                        t->color = black;
                    }
                }
            }
        }
    }
    bool judge(Node *t) // 判断当前节点是不是为异常节点
    {
        if (t->father->color == red)
            return false;
        return true;
    }
    void adjust(Node *t) // 当节点为红节点且父节点为红色节点时
    {
        Node *father = t->father;  // 父亲
        Node *gp = father->father; // 祖父节点
        if ((gp->left == NULL ? true : gp->left->color == black) ||
            (gp->right == NULL ? true : gp->right->color == black))
        // 旋转变色
        {
            if (gp->left == father && father->left == t)
            {
                shun(gp);
                father->color = black;
                gp->color = red;
            }
            else if (gp->left == father)
            {
                ni(father);
                shun(gp);
                gp->color = red;
                t->color = black;
            }
            else if (father->left == t)
            {
                shun(father);
                ni(gp);
                gp->color = red;
                t->color = black;
            }
            else
            {
                ni(gp);
                father->color = black;
                gp->color = red;
            }
        }
        else // 不转变色
        {
            gp->left->color = black;
            gp->right->color = black;
            if (gp != root)
                gp->color = red;
            else
                return;
        }
        if (!judge(gp)) // 不转变色会导致该子树的根节点为红色，可能会需要向上回溯
            adjust(gp);
        return;
    }
    void shun(Node *t) // 顺时针旋转
    {
        Node *l = t->left;
        if (t == root) // 子树的根节点进行调整
        {
            root = l;
            l->father = NULL;
        }
        else
        {
            l->father = t->father;
            if (l->father->data > l->data)
                l->father->left = l;
            else
                l->father->right = l;
        }
        if (l->right != NULL)
        {
            t->left = l->right;
            t->left->father = t;
        }
        else
            t->left = NULL;
        l->right = t;
        t->father = l;
    }
    void ni(Node *t) // 逆时针旋转
    {
        Node *r = t->right;
        if (t == root) // 子树的根节点进行调整
        {
            root = r;
            r->father = NULL;
        }
        else
        {
            r->father = t->father;
            if (r->father->data > r->data)
                r->father->left = r;
            else
                r->father->right = r;
        }
        if (r->left != NULL)
        {
            t->right = r->left;
            t->right->father = t;
        }
        else
            t->right = NULL;
        r->left = t;
        t->father = r;
    }
};
int main()
{
    rbTree t;
    int i, num;
    while (true)
    {
        cin >> i;
        if (i == 1)
        {
            cin >> num;
            t.Insert(num);
            cout << "INSERT:" << num << endl;
            t.out();
        }
        else if (i == 0)
        {
            cin >> num;
            t.Delete(num);
            cout << "DELETE:" << num << endl;
            t.out();
        }
        else
        {
            cout << "Exit" << endl;
            return 0;
        }
    }
}