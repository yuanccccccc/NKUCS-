#include <iostream>
using namespace std;

class sparematrix
{
public:
    int row;  // 行数
    int cols; // 列数
    int *element;
    int len; // 数组长度
    sparematrix operator*(sparematrix a);
    bool find(int i, int j);
    int search(int i, int j);
    friend ostream &operator<<(ostream &cout, const sparematrix &m);
    friend istream &operator>>(istream &cin, const sparematrix m);
};
int main()
{
    sparematrix a, b;
    cout << "请输入a矩阵的行列以及数组长度" << endl;
    cin >> a.row >> a.cols >> a.len;
    a.element = new int[a.len];
    cout << "请输入矩阵的数组元素" << endl;
    for (int i = 0; i < a.len; i++)
    {
        cin >> a.element[i];
    }
    cout << "请输入b矩阵的行列以及数组长度" << endl;
    cin >> b.row >> b.cols >> b.len;
    b.element = new int[b.len];
    cout << "请输入矩阵的数组元素" << endl;
    for (int i = 0; i < b.len; i++)
    {
        cin >> b.element[i];
    }
    sparematrix r = a.operator*(b);
    cout << r.row << " " << r.cols << " " << r.len << endl;
    for (int i = 0; i < r.len; i++)
    {
        cout << r.element[i] << " ";
    }
}

sparematrix sparematrix::operator*(sparematrix a)
{
    sparematrix r;
    r.row = row;
    r.cols = a.cols;
    int k = 0;
    int *tem = new int[3 * r.row * r.cols];
    for (int i = 1; i <= row; i++)
    {
        for (int j = 1; j <= a.cols; j++)
        {
            int t = 0;
            for (int m = 1; m <= cols; m++)
            {
                if (find(i, m) && a.find(m, j))
                {
                    t += element[3 * search(i, m) + 2] * a.element[3 * a.search(m, j)];
                }
            }
            if (t != 0)
            {
                tem[3 * k] = i;
                tem[3 * k + 1] = j;
                tem[3 * k + 2] = t;
                k++;
            }
        }
    }
    r.len = k * 3;
    r.element = new int[3 * k];
    for (int i = 0; i < r.len; i++)
    {
        r.element[i] = tem[i];
    }
    return r;
}

bool sparematrix::find(int i, int j)
{
    for (int k = 0; k < len / 3; k++)
    {
        if (element[k] == i && element[k + 1] == j)
        {
            return true;
        }
    }
    return false;
}

int sparematrix::search(int i, int j)
{
    if (find(i, j))
    {
        for (int k = 0; k < len / 3; k++)
        {
            if (element[k] == i && element[k + 1] == j)
            {
                return k;
            }
        }
    }
    return -1;
}