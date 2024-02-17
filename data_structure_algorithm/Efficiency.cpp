# include <iostream>
# include <vector>
#include <iomanip>
using namespace std;

int main()
{
    int stuN = 0; // number of students
    cin >> stuN;

    // 二維陣列
    int n = 100; // 10 行
    float ** nums = new float * [n]; // 創建指向 int* 的指標數組，表示 N 行
    for (int i = 0; i < n; i++) {
        nums[i] = new float[20]; // 為每行創建一個包含 9 個 int 的數組，表示 9 列
    }

    float hwSum = 0;
    float finalScore = 0;
    // 輸入原始成績
    for (int i = 0; i < stuN; i++) {
        // 輸入單位學生的成績
        for (int j = 0; j < 9; j++) {
            cin >> nums[i][j]; // 輸入成績
        }
        hwSum = 0; // 先清空成積
        for (int j = 0; j < 5; j++){
            hwSum += nums[i][j];
        }
        if (hwSum > 500){ hwSum = 500;}
        hwSum = (hwSum / 500) * 100;
        if (nums[i][6] > 100){nums[i][6] = 100;}
        if (nums[i][7] > 100){nums[i][7] = 100;}
        nums[i][10] = (hwSum * 0.5) \
         + (nums[i][5] * 0.12) \
         + (nums[i][6] * 0.14) \
         + (nums[i][7] * 0.14) \
         + nums[i][8];
    }

    for (int i = 0; i < stuN; i++) {
        cout << fixed << setprecision(2) << setfill('0') \
         << setw(2) << nums[i][10] << endl;
    }



    // 使用完畢後記得釋放動態分配的內存
    for (int i = 0; i < n; i++) {
        delete [] nums[i]; // 釋放每行的數組
    }
    delete[] nums; // 釋放指向每行數組的指標數組

    
    return 0;
}