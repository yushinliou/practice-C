# include <iostream>
using namespace std;
int main()
{
    int length = 0, type = 0;
    // 依序讀入單位的類型，長度
    cin >> type >> length;
    // 如果輸入是英吋的話
    if (type == 0)
    {
        // 輸出英吋 / 12的結果
        cout << length / 12;
        cout << ",";
        // 輸出英吋 / 12的餘數
        cout << length % 12;
    }
    // 如果輸入是英尺的話
    if (type == 1)
    {
        // 輸出英尺轉英吋
        cout << length * 12;
    }
    return 0;
}