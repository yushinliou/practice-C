# include <iostream>
using namespace std;
int main()
{
    int number;
    // 從鍵盤讀取數字
    cin >> number;
    // 輸出數字/12，因為是整數型態，不會顯示小數點
    cout << number / 12;
    cout << ",";
    // 輸出數字除以12的餘數
    cout << number % 12;
    return 0;
}