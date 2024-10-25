#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class queue
{
public:
    int *arr;
    int right;
    int len;     // 长度
    int num = 0; // 目前已经有的个数
    queue(int inlen)
    {
        len = inlen;
        arr = new int[len];
    }
    bool IsEmpty();       // 是否空的
    bool IsFull();        // 是否满的
    void Left();          // 输出最左边元素
    void Right();         // 输出最右边的元素
    void AddLeft(int n);  // 在左边插入元素
    void AddRight(int n); // 在右边插入元素
    void DeleteLeft();    // 删除最左边元素
    void DeleteRight();   // 删除最右边元素
    void output();
};

int main()
{
    int len;
    cin >> len;
    queue q(len);
    ifstream infile("input.txt"); // 打开文件
    string line;                  // 定义一个字符串变量，用来存储每一行的内容
    while (getline(infile, line))
    { // 循环读取每一行，直到文件结束
        if (line.substr(0, 7) == "AddLeft" && line.length() == 9)
            q.AddLeft(line[8] - 48);
        else if (line.substr(0, 8) == "AddRight" && line.length() == 10)
        {
            q.AddRight(line[9] - 48);
        }
        else if (line == "DeleteRight")
        {
            q.DeleteRight();
        }
        else if (line == "DeleteLeft")
        {
            q.DeleteLeft();
        }
        else if (line == "IsFull")
        {
            if (q.IsFull())
            {
                cout << "Yes" << endl;
            }
            else
            {
                cout << "No" << endl;
            }
        }
        else if (line == "IsEmpty")
        {
            if (q.IsEmpty())
            {
                cout << "Yes" << endl;
            }
            else
            {
                cout << "No" << endl;
            }
        }
        else if (line == "End")
        {
            break;
        }
        else if (line == "Left")
        {
            q.Left();
        }
        else if (line == "Right")
        {
            q.Right();
        }
        else
            cout << "Wrong" << endl;
    }
    infile.close(); // 关闭文件
    return 0;
}

bool queue::IsEmpty()
{
    if (num == 0)
        return true;
    else
        return false;
}

bool queue::IsFull()
{
    if (num == len)
        return true;
    else
        return false;
}

void queue::Left()
{
    cout << *arr << endl;
}

void queue::Right()
{
    cout << right << endl;
}

void queue::AddLeft(int n)
{
    if (IsFull())
    {
        cout << "FULL" << endl;
        return;
    }
    for (int i = len - 1; i > 0; i--)
    {
        arr[i] = arr[i - 1];
    }
    arr[0] = n;
    right = arr[num++];
    output();
}

void queue::AddRight(int n)
{
    if (IsFull())
    {
        cout << "FULL" << endl;
        return;
    }
    arr[num] = n;
    right = arr[num++];
    output();
}

void queue::DeleteLeft()
{
    if (num == 0)
    {
        cout << "EMPTY" << endl;
        return;
    }
    for (int i = 0; i < len - 1; i++)
    {
        arr[i] = arr[i + 1];
    }
    right = arr[num--];
    output();
}

void queue::DeleteRight()
{
    if (num == 0)
    {
        cout << "EMPTY" << endl;
        return;
    }
    right = 0;
    right = arr[num--];
}

void queue::output()
{
    for (int i = 0; i < num; i++)
    {
        if (i == num - 1)
            cout << arr[i] << endl;
        else
            cout << arr[i] << " ";
    }
}
