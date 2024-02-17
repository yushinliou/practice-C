# include <iostream>
# include <map>
# include <vector>
# include <queue>
using namespace std;

// get input of an 2D integer array
void getInput(int arr[120][50], int i_num, int j_num)
{
  for (int i = 0; i < i_num; i++)
    for (int j = 0; j < j_num; j++)
      cin >> arr[i][j];
}
// cout output
void coutInput(int arr[120][50], int i_num, int j_num){
  for (int i = 0; i < i_num; i++){
    for (int j = 0; j < j_num; j++)
      cout << arr[i][j] << " ";  
    cout << endl;  
  }
}

int countShortage(int people, int target_day, const int shift_num,
const int assign_form[120][50], const int shifts[50][50], const int need[50][50]){
    
    int supply_day[24] = {0};
    int day_shortage = 0;
    int shift_idx = 0;

    for(int time = 0; time < 24; time++){ // 走遍24個時段
        for (int people_idx=0; people_idx < people; people_idx++){
            // 該時段的supply_會等於每個員工這個時段有沒有做的加總
            // assign_form[j][tmp_day]是第j個人他tmp_day天的班型號碼應該要減一因為零號班實際上是休息
            shift_idx = assign_form[people_idx][target_day] - 1;
            if (shift_idx == -1){
                shift_idx = shift_num; // 如果是負一，代表原始是零號休息班，也就是最末號輸入的班型
            }
            supply_day[time] += shifts[shift_idx][time];
            // cout << shift_idx << " ";
        }
        // cout << time << " " << supply_day[time] << "shift_idx" <<  << endl;
        if (need[target_day][time] > supply_day[time]){ // 如果該時段需求大於供給
            day_shortage += (need[target_day][time] - supply_day[time]);
        }
    }
    return day_shortage;
}

int sumShortage(int people, int day, const int shift_num,
const int assign_form[120][50], const int shifts[50][50], const int need[50][50]){
    int total_shortage = 0;
    for (int target_day = 0; target_day < day; target_day++){
        total_shortage += countShortage(people, target_day, shift_num, assign_form, shifts, need);
    }
    return total_shortage;
}

int main(){

    // 題目原始輸入
    // 員工數量people對應到ni; 次月天數day對應到nj; 班型數量form_num對應到nk; limit是nj天至少L天休的L
    int people = 0, day = 0, shifts_num = 0, limit = 0;
    // 休假希望權重w_need對應到w1, 超額夜班權重w_shift對應到w2, 蒐集到的休假希望數量need_num對應到R
    int w_hope = 0, w_shift = 0, hope_num = 0;
    int shifts[50][50] = {0}; // 班型矩陣，題目輸入第一大區塊
    int need[50][50] = {0}; // 人力需求矩陣，題目輸入第二大區塊
    int hope[3][50] = {0}; // 休假希望，題目輸入的第三大區塊
    int assign_form[120][50] = {1};

    map <int, queue<int> > staff_hope; // 員工編號：休假希望

    // 自定義
    vector <int> okOffway;
    vector <int> shift_vec;

    // 輸入
    cin >> people >> day >> shifts_num >> limit;
    cin >> w_hope >> w_shift >> hope_num;

    getInput(shifts, shifts_num+1, 24);
    getInput(need, day, 24);

    // 初始化
    for (int i = 1; i <= shifts_num; i++){
        shift_vec.push_back(i);
    }
    
    int lastWeekOff = 0;
    int total_off = 0;
    // 決定休假方式矩陣
    // 決定哪些休假方法是可行的
    for (int i = 0; i < 7; i++){
        total_off = (day/7) * 2; // 先算有完整七天的那些天會修到幾天
        if ((day % 7) != 0){ // 如果這個月還有剩餘的天的話
            if (i == 0){ // 如果是第七種休假方式最後一週一定放一天
                lastWeekOff = 1;
            }
            else{ // 如果不是第七種休假方式，看看這週除七剩下幾天
                if ((((day % 7) - i) <= 2) & (((day % 7) - i) > 0)){
                    lastWeekOff = 2;
                }
                else if (((day % 7) - i) == 0){
                    lastWeekOff = 1;
                }
                else{
                    lastWeekOff = 0;
                }
            }
        }
        // cout << (day % 7) - i << " " << i << " " << lastWeekOff << endl;
        if ((total_off + lastWeekOff) == limit){ // 把第七種休假方式儲存成第零種
                okOffway.push_back(i);
        }
    }

    // cout << "可行的休假方式" << endl;
    // for (int i = 0; i < okOffway.size(); i++){
    //     cout << okOffway[i] << " ";
    // }
    // cout << endl;

    // 初始化排班，剛開始都是1
    for (int i = 0; i < people; i++){
        for (int j = 0; j < day; j++){
            assign_form[i][j] = 1;
    }
    }

    // 分配休假
    int curOffWay = 0;
    int day_th = 0;
    for (int i = 0; i < people; i++){
        curOffWay = okOffway.front();
        //cout << "curOffWay " << curOffWay << endl;
        // cout << "people " << i << endl;
        for (int j = 0; j < day; j++){
            // 先確認一下這是一週當中的第幾天
            if (((j+1) % 7) != 0){
                day_th = (j+1) % 7;
            }
            else{
                day_th = 7;
            }
            if (curOffWay == 0){
                if ((day_th == 1) | (day_th == 7)){
                    assign_form[i][j] = 0;
                }
            }
            else if ((day_th == curOffWay) | (day_th == (curOffWay+1))){ // i = 0 是第7種休假方式
                assign_form[i][j] = 0;
            }
            // cout << assign_form[i][j] << " ";
        }
        // cout << endl;
        okOffway.erase(okOffway.begin()); // 移除第一個元素
        okOffway.push_back(curOffWay); // 把第一個元素加回去尾巴
    }

    // cout << "排休假之後" << endl;
    // for (int i = 0 ; i < people; i++){
    //     for (int j = 0; j < day; j++){
    //         cout << assign_form[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    // 分配班形
    int cur_shift = 0;
    for (int i = 0; i < day; i++){
        for (int j = 0; j < people; j++){
            if (assign_form[j][i] != 0){
                cur_shift = shift_vec.front();
                assign_form[j][i] = cur_shift;
                shift_vec.erase(shift_vec.begin());
                shift_vec.push_back(cur_shift);
            }
        }
    }
    // cout << "排班之後" << endl;
    // for (int i = 0 ; i < people; i++){
    //     for (int j = 0; j < day; j++){
    //         cout << assign_form[i][j] << ",";
    //     }
    //     cout << endl;
    // }


    cout << sumShortage(people, day, shifts_num, assign_form, shifts, need);

    return 0;

}