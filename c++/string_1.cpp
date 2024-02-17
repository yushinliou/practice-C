# include <iostream>
# include <vector> 
# include <algorithm>
using namespace std;

void getInput(int ary[150], int n){
for (int i = 0; i < n; i++){
        cin >> ary[i];
    }
}
int solution(int ary[], int n){
    int max = 0;
    int *longestAry = 0;
    longestAry = (int *)malloc(sizeof(int) * n);

    for (int i = 0;i < n; i++){
        for(int j = 0;j < i; j++){
            if ((ary[i] >= ary[j]) & (longestAry[i] <= longestAry[j]+1)){
                longestAry[i] = longestAry[j] + 1;
            }
        }
    }

    for (int i = 0; i < n; i++){
        if(max <= longestAry[i]){
            max = longestAry[i];
        }
    }
    free(longestAry);
    return max;
}
int main()
{
    int n = 0; // 有多少數字
    int ary[150]; // 原始輸入數列
    int cut[150]; // 紀錄每個位置的數字比前面的增加多少
    int up = 0, down = 0;
    int change = 0;
    vector<int> d_ary;

    
    cin >> n; // 從鍵盤讀取數列有多少數

    getInput(ary, n);
    cout << n - solution(ary, n) -1;

    return 0;
}