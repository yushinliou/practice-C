# include <iostream>
# include <set>
using namespace std;

// remove element

// find current priority person id
int findPriority(int time[200], int money[200], int person[200], int start, int list_long){

    int cur_maxtime = 0, cur_maxperson = 0, cur_maxmoney = 0;

    // find current priority 
    for (int i = start; i < list_long; i++){
        if (i == start){
            cur_maxperson = person[i];
            cur_maxmoney = money[i];
            cur_maxtime = time[i];
        }
        else{
            if (time[i] >= cur_maxtime){
                if (time[i] == cur_maxtime){
                    if(money[i] >= cur_maxmoney){
                        if(money[i] == cur_maxmoney){
                            if(person[i] < cur_maxperson){
                                cur_maxperson = person[i];
                                cur_maxmoney = money[i];
                                cur_maxtime = time[i];
                            }
                        }
                        else{
                            cur_maxperson = person[i];
                            cur_maxmoney = money[i];
                            cur_maxtime = time[i];
                        }
                    }
                }
                else{
                    cur_maxperson = person[i];
                    cur_maxmoney = money[i];
                    cur_maxtime = time[i];
                }
            }
        }
    }
    return cur_maxperson+1;
}

void givecupon(int time[200], int money[200], int person[200],
const int cupon_num, int ok_member_num){

    int cur_time[200] = {0};
    int cur_money[200] = {0};
    int cur_person[200] = {0};

    int tmp_person = 0, tmp_time = 0, tmp_money = 0;
    int cur_ct = 0;

    // 初始化矩陣，當前矩陣會等於傳入矩陣
    for (int i = 0; i < ok_member_num; i++){
        cur_time[i] = time[i];
        cur_money[i] = money[i];
        cur_person[i] = person[i];
    }

    // 接著根據金額排序，如果下一個金額更高，把他交換往前
    for (int i = 0; i < ok_member_num; i++){
        for(int j = 0; j < ok_member_num-i; j++){
            tmp_money = money[j];
            tmp_person = person[j];
            tmp_time = time[j];  
            if (money[j+1] > money[j]){ // 如果第i個比目前紀錄得還要更大
                // 錢的順序交換
                money[j] = money[j+1];
                money[j+1] = tmp_money;
                // time
                time[j] = time[j+1];
                time[j+1] = tmp_time;
                // id也交換
                person[j] = person[j+1];
                person[j+1] = tmp_person;
            }
        }
    }
    
    // 接著根據時間排序，記錄目前最大時間，如果有更高的，把他交換往前排
    for (int i = 0; i < ok_member_num; i++){
        for(int j = 0; j < ok_member_num-i; j++){
            tmp_money = money[j];
            tmp_person = person[j];
            tmp_time = time[j];  
            if (time[j+1] > time[j]){ // 如果第j+1個比目前紀錄的時間還要更大
                // 錢的順序交換
                money[j] = money[j+1];
                money[j+1] = tmp_money;
                // time交換
                time[j] = time[j+1];
                time[j+1] = tmp_time;
                // id也交換
                person[j] = person[j+1];
                person[j+1] = tmp_person;
            }
        }
    }
    int out_num = 0;

    // 如果人比優惠券的數量多，以優惠券數量為主，多少優惠券印出多少人
    if (ok_member_num >= cupon_num){
        out_num = cupon_num;
    }
    else{
        out_num = ok_member_num; // 反之就以人數為主，把顧客全部都印出來
    }
    for (int i = 0; i < out_num-1; i++){
        cout << person[i]+1 << ","; // 輸出顧客編號+1(因為當初紀錄是從零開始)
    }
        cout << person[out_num-1]+1; // 最後一個輸出不要逗號
}

int main(){
    int person_num = 0, cupon_num = 0;
    int time[200] = {0};
    int money[200] = {0};
    int person[200] = {0};
    int tmp = 0, ct = 0;
    int vaild_num = 0;

    cin >> person_num >> cupon_num;
    
    // 輸入消費時間
    for (int i = 0; i < person_num; i++){
        cin >> tmp;
        if (tmp <= 12){ // 如果一年以內有來消費
            person[ct] = i; // 記下來，輸入的第i個顧客（i從零開始）
            time[ct] = tmp; // 第ct個符合一年內消費的顧客
            ct ++;
        }
    }

    vaild_num = ct;
    ct = 0;

    // 輸入消費金額
    for (int i = 0; i < person_num; i++){
        cin >> tmp;
        if (i == person[ct]){ // 如果現在這個輸入的編號有在一年以內消費的顧客名單裡面
            money[ct] = tmp; // 把他記錄下來，是第ct個符合資格的顧客
            ct ++; // 多一個一年內消費過的顧客，ct+1
        }
    }
    // 如果沒有任何一個人符合資格，直接結束程式
    if (ct == 0){
        return 0;
    }

    // 呼叫發優惠券的函數
    givecupon(time, money, person, cupon_num, ct);

    return 0;
}