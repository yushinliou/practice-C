# include <iostream>
using namespace std;
int main()
{
    int i = 0;
    int times = 0;
    int length = 0, type = 0;
    // 第一行讀入要做幾次
    cin >> times;
    // 重複輸入 times 次
    for (i = 0 ; i < times ; i = i + 1)
    {
        // 讀入單位類型，長度
        cin >> type >> length;
        // 如果是英吋
        if (type == 0)
        {
            cout << length / 12;
            cout << ",";
            cout << length % 12 << endl;
        }
        // 如果是英呎
        if (type == 1)
        {
            cout << length * 12 << endl;
        }
    }
    return 0;
}