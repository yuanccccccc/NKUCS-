#include <iostream>
#include <cmath>
using namespace std;

class hashtable
{
public:
    int *value;
    bool *never;
    bool *empty;
    int m;
    void Insert(int num);
    void Delete(int num);
    void out();
    void recom();
    double compare();
    hashtable(int n)
    {
        m = n;
        value = new int[m];
        never = new bool[m];
        empty = new bool[m];
        for (int i = 0; i < m; i++)
        {
            value[i] = 0;
            never[i] = true;
            empty[i] = true;
        }
    }
};
int main()
{
    int len; // 输入空桶的个数
    cout << "输入空桶的个数" << endl;
    cin >> len;
    hashtable initial(len);
    int num;
    int nlen;
    cout << "请输入要储存的数据个数" << endl;
    cin >> nlen;
    if (nlen > len)
        cout << "空桶数量不足" << endl;
    cout << "请输入要存储的数据" << endl;
    for (int i = 0; i < min(len, nlen); i++)
    {
        cin >> num;
        initial.Insert(num);
    }
    int pos; // 要删除的数
    cout << "请输入要删除的位置" << endl;
    while (true)
    {
        cin >> pos;
        if (pos == -1)
        {
            initial.out();
            return 0;
        }
        else if (pos >= len || pos < 0)
        {
            cout << "删除位置非法" << endl;
            continue;
        }
        initial.Delete(pos);
        bool e = true;
        for (int i = 0; i < initial.m; i++)
        {
            if (initial.empty[i] == 0)
            {
                e = false;
                break;
            }
        }
        if (e)
        {
            cout << "哈希表已经空了" << endl;
            return 0;
        }
    }
}

void hashtable::Insert(int num)
{
    bool full = true;
    for (int i = 0; i < m; i++)
    {
        if (empty[i] == 1)
        {
            full = false;
            break;
        }
    }
    if (full)
    {
        cout << "哈希表已经满了" << endl;
        return;
    }
    int n = num % m;
    while (empty[n] == false)
    {
        n++;
        if (n >= m)
        {
            n %= m;
        }
    }
    value[n] = num;
    empty[n] = false;
    never[n] = false;
    if (compare() > 0.6)
        recom();
    out();
}

void hashtable::Delete(int pos)
{
    if (empty[pos] == true)
    {
        cout << "该位置为空" << endl;
        return;
    }
    empty[pos] = true;
    if (compare() > 0.6)
        recom();
    out();
}

void hashtable::out()
{
    for (int i = 0; i < m; i++)
    {
        if (empty[i] == false)
        {
            cout << value[i] << " ";
        }
    }
    cout << endl;
}

void hashtable::recom()
{
    hashtable a(m);
    for (int i = 0; i < m; i++)
    {
        if (empty[i] == false)
            a.Insert(value[i]);
    }
    m = a.m;
    value = a.value;
    never = a.never;
    empty = a.empty;
    cout << "哈希表已重排" << endl;
}

double hashtable::compare()
{
    double emp = 0;
    double nev = 0;
    for (int i = 0; i < m; i++)
    {
        if (empty[i] == true)
            emp++;
        if (never[i] == false && empty[i] == true)
            nev++;
    }
    return nev / emp;
}
