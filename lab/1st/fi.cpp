#include <iostream>
#include <fstream>
using namespace std;
long long F[100] = {1, 1};

long long Fi(int n)
{
    if (F[n] != 0)
        return F[n];
    long long re = 0;
    if (n == 0 || n == 1)
        re = 1;
    else
    {
        if (F[n - 1] != 0)
            re = F[n - 1] + F[n - 2];
        else if (F[n - 2] != 0)
        {
            F[n - 1] = Fi(n - 1);
            re = F[n - 1] + F[n - 2];
        }
        else
        {
            F[n - 2] = Fi(n - 2);
            F[n - 1] = Fi(n - 1);
            re = F[n - 1] + F[n - 2];
        }
    }
    return re;
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
    if (t < 0 || t > 90)
    {
        cerr << "WRONG!" << endl;
        return 0;
    }
    cerr << "F(" << t << ")=" << Fi(t);
    outfile.close();
}