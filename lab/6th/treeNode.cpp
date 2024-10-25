#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int kuohao(string s, int pos) // 括号匹配
{
    if (s[pos] == '(')
    {
        int kuo = 1;
        for (int i = pos + 1; i < s.length(); i++)
        {
            if (s[i] == '(')
            {
                kuo++;
            }
            else if (s[i] == ')')
            {
                kuo--;
            }
            if (kuo == 0)
                return i;
        }
    }
    else if (s[pos] == ')')
    {
        int kuo = 1;
        for (int i = pos - 1; i > 0; i--)
        {
            if (s[i] == ')')
            {
                kuo++;
            }
            else if (s[i] == '(')
            {
                kuo--;
            }
            if (kuo == 0)
                return i;
        }
    }
    return -1;
}
class tree
{
public:
    char head = ' ';
    int level;
    tree *right = NULL;
    tree *left = NULL;
    tree(string da, int dadlevel)
    {
        level = dadlevel + 1; // 层数加1
        if (da[0] == '(' && kuohao(da, 0) == da.length() - 1)
        // 式子最开头的括号和最后的括号匹配时去掉括号
        {
            da = da.substr(1, da.length() - 2);
        }
        if (da.length() == 1) // 长度为一直接设为根
        {
            head = da[0];
        }
        else
        {
            int pos;                        // 剪切位置
            if (da[da.length() - 1] == ')') // 末尾为括号时将整个括号截取为右子树
                pos = kuohao(da, da.length() - 1) - 1;
            else // 否则直接将倒数第二个字符（运算符）左侧的式子设为左子树
                pos = da.length() - 2;
            head = da[pos];
            left = new tree(da.substr(0, pos), level);   // 递归构造
            right = new tree(da.substr(pos + 1), level); // 递归构造
        }
    }
    void Output() // 输出
    {
        if (right)
        {
            right->Output();
        }
        for (int i = 0; i < level; i++) // 按照层数输出空格
        {
            cout << "    ";
        }
        cout << head << endl;
        if (left)
        {
            left->Output();
        }
    }
};
int main()
{
    ifstream infile("input.txt"); // 打开文件
    string line;
    infile >> line;
    tree t(line, -1);
    t.Output();
}