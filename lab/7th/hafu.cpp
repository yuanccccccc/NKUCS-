#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Node
{
public:
    Node *left = NULL;
    Node *right = NULL;
    string ma = "";
    char fu;
    Node() {}
    Node(char c)
    {
        fu = c;
    }
    void tian(string c)
    {
        ma = c + ma;
        if (this->left == NULL || this->right == NULL)
            return;
        this->left->tian(c);
        this->right->tian(c);
    }
};
class Htree
{
public:
    Node *root;
    vector<Node *> a;
    int weight = 0;
    int number = 0; // 编码字符个数
    char *fuhao = NULL;
    string *bianma = NULL;
    Htree() {}
    Htree(char c, int weigh)
    {
        this->root = new Node(c);
        this->weight = weigh;
    }
    Htree(int w[])
    {
        int n = 0; // 统计出现的字符个数
        for (int i = 0; i < 26; i++)
        {
            if (w[i] > 0)
                n++;
        }
        // 将数据放入最小堆
        priority_queue<Htree, vector<Htree>, greater<Htree>> minheap;
        for (int i = 0; i < 26; i++)
        {
            if (w[i] > 0)
            {
                char c = (char)(i + 'a');
                Htree h(c, w[i]);
                minheap.push(h);
            }
        }
        number = n;
        // 进行树的构造
        for (int i = 1; i < n; i++) // 合并n-1次
        {
            Htree h1 = minheap.top();
            minheap.pop();
            Htree h2 = minheap.top();
            minheap.pop();
            minheap.push(hebing(h1, h2));
        }
        // 找到树中所有的叶节点
        queue<Node *> q;
        q.push(minheap.top().root);
        while (!q.empty())
        {
            if (q.front()->left != NULL && q.front()->right != NULL)
            {
                q.push(q.front()->left);
                q.push(q.front()->right);
            }
            else
                this->a.push_back(q.front());
            q.pop();
        }
        // 将编码和字符对应储存
        fuhao = new char[a.size()];
        bianma = new string[a.size()];
        for (int i = 0; i < a.size(); i++)
        {
            fuhao[i] = this->a[i]->fu;
            bianma[i] = this->a[i]->ma;
        }
    }
    Htree hebing(Htree h1, Htree h2)
    {
        Htree h;
        h.root = new Node();
        h1.root->tian("0");
        h2.root->tian("1");
        h.root->left = h1.root;
        h.root->right = h2.root;
        h.weight = h1.weight + h2.weight;
        return h;
    }
    friend bool operator>(const Htree h1, const Htree h2)
    {
        return h1.weight > h2.weight;
    }
    friend bool operator<(const Htree h1, const Htree h2)
    {
        return h1.weight < h2.weight;
    }
};

int main()
{
    string s;
    cin >> s;
    int w[26] = {0};
    for (int i = 0; i < s.length(); i++)
    {
        int t = s[i];
        w[t - 97]++;
    }
    for (int i = 0; i < 26; i++)
    {
        if (w[i] == 0)
            continue;
        cout << (char)(i + 'a') << ":" << w[i] << endl;
    }
    Htree he(w);
    for (int i = 0; i < he.number; i++)
    {
        cout << he.fuhao[i] << he.bianma[i] << endl;
    }
    string istr;
    cin >> istr;
    while (istr.length() != 0)
    {
        for (int i = 0; i < he.number; i++)
        {
            if (istr.substr(0, he.bianma[i].length()) == he.bianma[i])
            {
                cout << he.fuhao[i];
                istr = istr.substr(he.bianma[i].length());
            }
        }
    }
    return 0;
}