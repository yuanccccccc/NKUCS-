#include <iostream>
#include <fstream>
#include <string>
#include <queue>
using namespace std;

class tree
{
public:
    char root = ' ';
    int level; // 层数
    tree *right = NULL;
    tree *left = NULL;
    tree(string da, int dadlevel)
    {
        level = dadlevel + 1;
        if (da.length() == 0) // 长度为零则不生成
        {
            return;
        }
        else if (da.length() == 1) // 为一则直接设为头
        {
            root = da[0];
        }
        else
        {
            int pos;                  // 剪切位置
            if (da.length() % 2 != 0) // 长度为奇数取最中间的位置
                pos = (da.length() - 1) / 2;
            else // 偶数取中点右边的位置
                pos = da.length() / 2;
            root = da[pos];                                  // 将截取位置的字符设为根
            if (pos != 0)                                    // 截取长度不为零
                left = new tree(da.substr(0, pos), level);   // 根节点左边的部分生成左子树
            if (pos + 1 != da.length())                      // 不能从最后一个元素开始截取
                right = new tree(da.substr(pos + 1), level); // 根节点右边部分生成树
        }
    }
    void visit();    // 逐层访问
    int width();     // 最大宽度
    int leaves();    // 叶节点数量
    void exchange(); // 交换
    void Output()    // 输出
    {
        if (right) // 输出右子树
        {
            right->Output();
        }
        for (int i = 0; i < level; i++) // 按照层数Tab
        {
            cout << "    ";
        }
        cout << root << endl;
        if (left) // 输出左子树
        {
            left->Output();
        }
    }
};

int main()
{
    string tr;
    cin >> tr;
    tree t(tr, -1);
    t.Output();
    t.visit();
    cout << t.leaves() << endl;
    t.exchange();
    t.Output();
    cout << t.width() << endl;
    return 0;
}

void tree::visit()
{
    queue<tree *> tr;
    tr.push(this);      // 将树放入队列
    while (!tr.empty()) // 树不为空
    {
        if (tr.front()->left)
            tr.push(tr.front()->left); // 将左子树放入
        if (tr.front()->right)
            tr.push(tr.front()->right);  // 将右子树放入
        cout << tr.front()->root << " "; // 将当前第一个位置的元素输出
        tr.pop();                        // 然后出队
    }
    cout << endl;
}

int tree::width()
{
    int re = 0;
    queue<tree *> tr;
    tr.push(this);
    int len = 1;
    while (true)
    {
        if (tr.empty()) // 为空就结束
            break;
        while (len > 0) // 将上一层的所有元素出队，且将下一层入队
        {
            if (tr.front()->left)
                tr.push(tr.front()->left);
            if (tr.front()->right)
                tr.push(tr.front()->right);
            tr.pop();
            len--;
        }
        len = tr.size(); // 将长度放入len，进行比较及下一次循环
        if (len > re)
            re = len;
    }
    return re;
}

int tree::leaves()
{
    if (left == nullptr && right == nullptr) // 都为空时说明为叶节点
    {
        return 1;
    }
    else if (left && right) // 都不为空则返回左右子树的叶节点数目
    {
        return this->left->leaves() + this->right->leaves();
    }
    else if (right) // 仅有右子树，返回右子树的叶节点数目
    {
        return right->leaves();
    }
    else // 仅有左子树，返回左子树的叶节点数目
        return left->leaves();
}

void tree::exchange()
{
    if (this->left || this->right) // 左右都存在交换
    {
        swap(this->left, this->right);
    }
    if (this->left) // 左子树存在时交换左子树的左右子树
        this->left->exchange();
    if (this->right) // 右子树存在时交换右子树的左右子树
        this->right->exchange();
}