# include <iostream>
# include <cstring>
# include<cctype>

int isalpha(int c);
int toupper(int c);

using namespace std;

void bool2idx(int city_num, int isCityHos[80], int isCityHosIdx[80], int &cur_hos_num){
    int ct = 0;
    for (int i = 0; i < city_num; i++){
        if (isCityHos[i] == 1){
            isCityHosIdx[ct] = i+1;
            ct++;
            // cout << isCityHosIdx[ct-1] << endl;
        }
    }
    cur_hos_num = ct;
}

void distanceSum(const int city_num, const int l, const int distance[80][80],
int isCityHos[80], int &good_ct, int &dis_sum){

    int isCityHosIdx[80] = {0};
    int cur_hos_num = 0;
    dis_sum = 0; // 記得要歸零，不然會累計上輪的資訊
    good_ct = 0;
    // 根據布林陣列生成現在有的醫院數量，以及醫院的idx
    bool2idx(city_num, isCityHos, isCityHosIdx, cur_hos_num);

    int min_distance = 0;

    // 程式數量、目前有的醫院數量，距離矩陣，醫院編號矩陣，最短距離矩陣
    for (int i = 0; i<city_num;i++){ // i是城市編號從零開始
        // 走遍所有醫院，找出距離最近的醫院距離
        for (int j=0; j < cur_hos_num;j++){ // j是第j座醫院，編號是hos[j]
            if (j == 0){
                min_distance = distance[i][isCityHosIdx[j]-1];
            }
            else{
                if ((distance[i][isCityHosIdx[j]-1]) < min_distance){
                    min_distance = (distance[i][isCityHosIdx[j]-1]); // 因為給定的醫院編號從1開始所以要減一
                }
            }
        }
        dis_sum += min_distance; // 存到mindis[i]裏面
        if (min_distance <= l){ // 紀錄他是不是幸福城市
            good_ct++;
        }
    }
}

int main(){

    // 城市數量，醫院數量、幸福城市限制，目標
    int city_num = 0, hos_num = 0, l = 0, target = 0;
    int distance[80][80] = {0}; // 距離陣列
    char city_name[80][80]; // 城市名稱陣列

    // 輸入城市數量，醫院數量、幸福城市限制，目標
    cin >> city_num >> hos_num >> l >> target;

    // 輸入距離
    for (int i = 0; i < city_num; i++){
        for (int j = 0; j < city_num; j++){
            cin >> distance[i][j];
        }
    }

    // 輸入城市名稱
    cin.ignore(); // 忽略換行字元，才能順利讀取
    for(int i=0; i < city_num; i++){
        cin.getline(city_name[i], 80);
    }

    // 處理城市名稱
    char new_city_name[80][80];
    int isSpace = 0;
    int name_ct = 0;

    
    for (int i = 0; i < city_num; i++){
        name_ct = 0; // 存當前的程式名稱紀錄到第幾個字了，每次要歸零
        for (int j = 0; j < strlen(city_name[i])+1; j++){
            if (isalpha(city_name[i][j])){ // 如果是字母
                new_city_name[i][name_ct] = tolower(city_name[i][j]); // 全部轉換成小寫
                name_ct++; // 每多紀錄一個字要加一
            }
            else if (city_name[i][j] == ' '){ // 如果看到空白
                if (city_name[i][j+1] != ' '){ // 而且後面也是空白
                    new_city_name[i][name_ct] = '-'; // 把空白存成"-"
                    name_ct++;
                }
            }
            else if (j == strlen(city_name[i])){ // 如果是最後一個元素了
                new_city_name[i][name_ct] = '\0'; // 紀錄結束符號
                name_ct++;
            }
        }
    }

    int good_ct, dis_sum = 0;
    int min_dis_sum = 0;
    int max_good_ct = 0;
    int next_city = 0;

    int findNoHos = 0;
    int noHos_num = city_num;
    int try_city = 0;

    int isCityHos[80] = {0}; // 各個城市有沒有醫院的布林陣列
    int tmpisCityHos[80] = {0};
    int isCityHosIdx[80] = {0}; // 紀錄目前有醫院的城市編號

    for (int k = 0; k < hos_num; k++){ // 題目讓我們蓋多少醫院，我們就走幾次
        for (int i = 0; i < noHos_num; i++){ // 目前有多少城市沒有醫院就挑幾個比，目前進行的是第i個沒醫院的城市
            for (int j = 0; j < city_num; j++){ // 走遍紀錄城市有沒有醫院的矩陣
                if (isCityHos[j] == 0){ // 如果這個城市沒醫院
                    if (findNoHos == i){ // 而且他是我們找到的第i個沒醫院的城市
                        tmpisCityHos[j] = 1; // 把他改成有醫院嘗試看看
                        try_city = j; // 紀錄一下這輪嘗試的是第幾個城市
                    }
                    else{
                        tmpisCityHos[j] = isCityHos[j]; // 其他照舊
                    }
                    findNoHos++; // 紀錄這是第幾個沒醫院的城市
                }
                else{
                    tmpisCityHos[j] = isCityHos[j]; // 其他照舊
                }
            }
            findNoHos = 0; // 要歸零，方便下一輪找第i個沒醫院的城市
            distanceSum(city_num, l, distance, tmpisCityHos, good_ct, dis_sum);
            if (i == 0){ // 如果是第一個沒醫院的城市，紀錄他就是最好的備選
                min_dis_sum = dis_sum;
                max_good_ct = good_ct;
                next_city = try_city;
            }
            else if (target == 0){ // 往後就以題目給訂的標準決定，零代表以最短距離為主
                if (min_dis_sum > dis_sum){ // 如果下個沒醫院的城市蓋了醫院距離更短，就更新數字
                    min_dis_sum = dis_sum;
                    max_good_ct = good_ct;
                    next_city = try_city;
                }
            }
            else if (target == 1){ // 1代表以幸福城市數量為主
                if (good_ct > max_good_ct){ // 如果下個沒醫院的城市幸福城市數量更多，就更新數字
                    min_dis_sum = dis_sum;
                    max_good_ct = good_ct;
                    next_city = try_city;
                }
            }
        }    
        isCityHos[next_city] = 1; // 把挑出來蓋醫院最好的城市改成有蓋醫院
        noHos_num--; // 沒醫院的城市少一
        cout << new_city_name[next_city] << endl; // 輸出該城市名稱
    }

    distanceSum(city_num, l, distance, isCityHos, good_ct, dis_sum); // 計算最終結果幸福城市數量跟總距離
    cout << dis_sum << ";" << good_ct;

    return 0;
}