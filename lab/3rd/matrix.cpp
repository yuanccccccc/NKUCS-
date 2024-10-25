#include <iostream>
using namespace std;

class lm
{
public:
    lm(int theside);
    lm(const lm &l);
    void set(int i, int j, int value);
    void outside();
    int side; // 方阵的行列数
    int *element;
};
class um
{
public:
    um(int theside);
    um(const um &u);
    void set(int i, int j, int value);
    void output();
    int side;
    int *element;
};
um tran(lm m)
{
    um r(m.side);
    r.element = m.element;
    return r;
}
int main()
{
    lm l(3);
    l.set(1, 1, 1);
    l.set(2, 1, 2);
    l.set(2, 2, 3);
    l.set(3, 1, 4);
    l.set(3, 2, 5);
    l.set(3, 3, 6);
    tran(l).output();
}
lm::lm(int theside)
{
    if (theside < 0)
        throw "方阵边长越界";
    side = theside;
    int num = (side + 1) * side / 2;
    element = new int(num);
}
lm::lm(const lm &l)
{
    side = l.side;
    element = l.element;
}
void lm::set(int i, int j, int value)
{
    element[(i - 1) * i / 2 + j - 1] = value;
}
um::um(int theside)
{
    if (theside < 0)
        throw "方阵边长越界";
    side = theside;
    int num = (side + 1) * side / 2;
    element = new int(num);
}

um::um(const um &u)
{
    side = u.side;
    element = u.element;
}

void um::set(int i, int j, int value)
{
    element[(j - 1) * j / 2 + i - 1] = value;
}

void um::output()
{
    for (int i = 0; i < side; i++)
    {
        for (int j = 0; j < i; j++)
        {
            cout << 0 << " ";
        }
        for (int j = i; j < side; j++)
        {
            if (j == side - 1)
            {
                cout << element[(j + 1) * j / 2 + i] << endl;
            }
            else
            {
                cout << element[(j + 1) * j / 2 + i] << " ";
            }
        }
    }
}
