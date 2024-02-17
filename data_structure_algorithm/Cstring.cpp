# include <iostream>
# include <algorithm>
# include <string>
# include <vector>
using namespace std;

int isAbiger(string a, string b){
    int twoNegative = 0;
    string numberA;
    string numberB;

    if ((a[0] == '-') & (b[0] != '-')){ return 0;} // 如果a是負數但是b不是，那就一定a沒比較大
    else if ((a[0] != '-') & (b[0] == '-')){ return 1;} // 如果a是不是負數但是b是，那就一定a比較大
    else if ((a[0] == '-') & (b[0] == '-')){ // 兩者皆為負數
        twoNegative = 1; // 記錄一下正在比較負數
        numberA = a.substr(1, a.size()); // 只截取數字部分去除掉正負號
        numberB = b.substr(1, b.size());
    }
    else{
        numberA = a;
        numberB = b;
    }
    // 接下來先比較長度
    if (numberA.size() != numberB.size()){ // 如果長度比得出來
        if (numberA.size() > numberB.size()){ // 如果A比較長
            if (twoNegative == 0){ return 1;} // 並且不是在比較兩個負數，那就是A大
            else{return 0;} // 如果是在比較兩個負數，那就是A沒有比較大了
        }
        else{ // 不然如果是B比較長
            if (twoNegative == 0){ return 0;} // 並且不是在比較兩個負數，那就是B大
            else{return 1;} // 如果是在比較兩個負數，那就是A比較大了
        }
    }
    else{ // 長度比較不出來，就來比較位元
        for(int i = 0; i < numberA.size(); i++){
            if (numberA[i] > numberB[i]){ // 如果A比較大
                if (twoNegative == 0){ return 1;} // 不是在比較負數，就是他真的比較大
                else{ return 0;}
                }
            else if (numberA[i] < numberB[i]){ // 如果B比較大
                if (twoNegative == 0){ return 0;} // 不是在比較負數，就是他真的比較大
                else{ return 1;}
                }
        }
    }
    return 0;
}


int main()
{
    string number;
    string tmp;
    vector<string> arr;
    vector<string> top; // top 是最小，由小堆到大
    unsigned long long int n = 0;
    arr.reserve(1000000); // 預分配 vector 的容量

    // 讀取輸入
    while (getline(cin, number)){
        arr.push_back(number);
        n+=1; // 計算有多少行
    }
    long long int miniIndex = 0;
    
    if (n < 4){
        sort(arr.begin(), arr.end(), isAbiger);
        cout << arr.back();
        exit(0);
    }

    for(int i = 0; i < n; i++){
        if (i < 4){ // 剛開始的時候先填滿最大的堆疊
            top.push_back(arr[i]);
        }
        if (i == 3){
            sort(top.begin(), top.end(), isAbiger); // 把top 由小到大排列
        }
        else if (isAbiger(arr[i], top[3])){ // 接下來開始比較，如果下面的數字比隊尾巴更大
            // 那就把堆疊頂端丟掉把新元素插進來
            top.pop_back();
            top.push_back(arr[i]);
            sort(top.begin(), top.end(), isAbiger);
        }
    }

    cout << top[3] << endl;

    return 0;
}
