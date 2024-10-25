#include <iostream>
using namespace std;

void changelength(int *&a, int alen, int blen)
{
    int *b = new int[blen];
    for (int i = 0; i < alen; i++)
    {
        b[i] = a[i];
    }
    a = b;
}

class maxheap
{
public:
    int *array; // 数组从第一位开始存起
    int maxcol; // 最大容量
    int maxele; // 最大元素
    int minele; // 最小元素
    int num;    // 元素个数
    void Insert(int data);
    int pop();                                         // 删除最大元素
    void makeheap(int a[], int len, int max, int min); // 建立堆
    void recome();
    void out();
};
int main()
{
    int n;
    cin >> n;
    int *a = new int[n];
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    maxheap h;
    h.makeheap(a, n, 100, 0);
    h.out();
    h.Insert(3);
    h.Insert(7);
    int num = h.num;
    for (int i = 0; i < num; i++) // 提取出最大元素
        h.pop();
}

void maxheap::Insert(int data)
{
    for (int i = 0; i < num; i++)
    {
        if (array[i + 1] == data)
        {
            return;
        }
    }
    if (data > maxele || data < minele) // 假如是非法就退出
        return;
    if (num >= maxcol)
    { // 数组长度加倍
        changelength(array, 2 * maxcol + 1, 4 * maxcol + 1);
    }
    int pos = num + 1; // 放在最后的位置
    while (array[pos / 2] < data)
    { // 假如根小于插入数据，根下移
        array[pos] = array[pos / 2];
        pos /= 2; // 准备插入的位置减半
    }
    array[pos] = data;
    num++;
    for (int i = num + 1; i < 2 * num + 1; i++)
    {
        array[i] = minele;
    }
    out();
}

int maxheap::pop()
{
    int r = array[1];
    int child = 1;
    array[1] = array[num];
    while (child <= num)
    {
        int c = 2 * child;
        if (c < num && array[c] < array[c + 1])
            c++;
        if (array[c] > array[child])
        {
            swap(array[c], array[child]);
            child = c;
        }
        else
            break;
    }
    array[num--] = minele;
    out();
    return r;
}

void maxheap::makeheap(int a[], int len, int max, int min)
{
    maxele = max;
    minele = min;
    num = len;
    maxcol = 2 * len;
    array = new int[2 * maxcol + 1];
    for (int i = 0; i < len; i++)
    {
        array[i + 1] = a[i];
    }
    array[0] = maxele;
    for (int i = len + 1; i < 2 * len + 1; i++)
    {
        array[i] = minele;
    }
    recome();
}

void maxheap::recome()
{
    for (int i = num / 2; i > 0; i--)
    {
        int a = array[i];
        int c = 2 * i;
        while (c <= num)
        {
            if (c < num && array[c] < array[c + 1])
                c++;
            if (a > array[c])
                break;
            array[c / 2] = array[c];
            c *= 2;
        }
        array[c / 2] = a;
    }
}

void maxheap::out()
{
    if (num == 0)
        return;
    cout << "num:" << num << endl;
    cout << "最大元素：" << array[0] << endl;
    for (int i = 1; i < num + 1; i++)
    {
        cout << array[i] << " ";
    }
    cout << "          ";
    for (int i = num + 1; i < 2 * num + 1; i++)
        cout << array[i] << " ";
    cout << endl;
    // cout << array[num + 1];
}
