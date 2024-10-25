#include <iostream>
#include <fstream>
using namespace std;
void output(bool a[], int len)
{
    char *c = new char[len];
    for (int i = 0; i < len; i++)
    {
        c[i] = 'a' + i;
    }
    for (int j = 0; j < len; j++)
    {
        if (a[j] == 1)
        {

            cout << c[j];
        }
    }
    cout << endl;
}
void subset(bool a[], int n, int len)
{

    if (n == 0)
    {
        output(a, len);
        delete[] a;
        return;
    }
    for (int i = 0; i < 2; i++)
    {
        bool *b = new bool[len];
        for (int i = 0; i < len; i++)
            b[i] = a[i];
        if (i == 1)
            b[n - 1] = 0;
        else
            b[n - 1] = 1;
        subset(b, n - 1, len);
    }
}
int main()
{
    ifstream outfile;
    outfile.open("input.txt", ios::out);
    if (!outfile)
    {
        cerr << "WRONG!" << endl;
        return 0;
    }
    int t;
    outfile >> t;
    if (t < 0 || t > 26)
    {
        cerr << "WRONG!" << endl;
        return 0;
    }
    bool *s = new bool[t];
    for (int i = 0; i < t; i++)
    {
        s[i] = 1;
    }
    subset(s, t, t);
    delete[] s;
}