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
    int assign_form[120][50] = {0};

    map <int, queue<int> > staff_hope; // 員工編號：休假希望

    // 輸入
    cin >> people >> day >> shifts_num >> limit;
    cin >> w_hope >> w_shift >> hope_num;

    getInput(shifts, shifts_num+1, 24);
    getInput(need, day, 24);
    getInput(assign_form, people, day);

    // coutInput(assign_form, people, day);

    cout << sumShortage(people, day, shifts_num, assign_form, shifts, need);
    return 0;

}