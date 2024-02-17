# include <iostream>
using namespace std;

int findWorst(int order, int weight_h, int weight_s, const int revenues[100],
const int human_need[100], const int source_need[100], const int accept[100])
{
    int worst = 0;
    float cps[100] = {0};
    float cp_up = 0, cp_down = 0;
    float cp_min = 0;
    int ct = 0;
    // compute all cp value
    // cout << "cp:" << endl;
    for (int i = 0; i < order; i++){
        cp_up = revenues[i];
        cp_down = ((weight_h * human_need[i]) + (weight_s * source_need[i]));
        cps[i] = cp_up / cp_down;
        //cout << cps[i] << " ";
    }
    //cout << endl;
    cp_min = cps[0];
    worst = 0;

    // go through all order and find worst
    for (int i = 0; i < order; i++){
        // 如果這個訂單現在有接
        if (accept[i] == 1){
            // 看這是第幾個訂單，如果是第一個
            if (ct == 0){
                // 把他當成是最小的那個
                cp_min = cps[i];
                worst = i;
                ct ++;
                //cout << "now min cp:" << i+1 << " " << cp_min << endl; 
            }
            else{ // 如果不是第一張訂單的話
                // 看他有沒有小於等於現在記錄到的
                if (cps[i] <= cp_min){
                // 如果有，而且是等於的狀況
                    if (cps[i] == cp_min){
                        // 看他有沒有比現在最小的營收更小，如果有
                        if (revenues[i] < revenues[worst]){
                            // 記下來
                            cp_min = cps[i];
                            worst = i;
                            //cout << "now min cp:" << i+1 << " " << cp_min << endl; 
                        }
                    }
                    else{ // 如果小於，直接記下來
                        worst = i;
                        cp_min = cps[i];
                        //cout << "now min cp:" << i+1 << " " << cp_min << endl; 
                    }
                }  
            }
        }
        else{
            continue;
        }
    }
    return worst;
}
// 測試現在的接單量有沒有超過
int keepDrop(int order, int human, int source, 
const int human_need[100], const int source_need[100], int accept[100])
{
    int keepdrop = 0;
    int human_sum = 0, source_sum = 0;
    // sum up all human and source need
    for (int i = 0; i < order; i++){
        if (accept[i] == 1){
            human_sum += human_need[i];
            source_sum += source_need[i];
        }
    }
    // determine whether need to keep drop order
    if ((human_sum <= human) & (source_sum <= source)){
        keepdrop = 0;
    }
    else{
        keepdrop = 1;
    }
    return keepdrop;
}
// print accept order and maxium revenue
void print_ans(int order, int source_sum, int human_sum, int revenue[100],
const int accept[100])
{
    int revenue_sum = 0;
    for (int i = 0; i < order-1; i ++){
    }
    for (int i = 0; i < order; i++){
        if (accept[i] == 1){
            revenue_sum += revenue[i];
        }
    }
    return;
}

int weightBestRev(int order, int human, int source, int weight_h, int weight_s, const int revenues[100],
const int human_need[100], const int source_need[100], int accept[100])
{
    int weight_best_revenue = 0;
    int drop = 0;
    // go through all order
    for (int i = 0; i < order; i++){
    // if we need to keep drop order
    if (keepDrop(order, human, source, human_need, source_need, accept) == 1){
        // find worst case
        drop = findWorst(order, weight_h, weight_s,
        revenues, human_need, source_need, accept);
        // drop it
        accept[drop] = 0;
    }
    else{
        break;
    }
    }

    for (int i=0; i < order; i++){
        // 如果這筆訂單有要
        if (accept[i] == 1){
            // 加上他的利潤
            weight_best_revenue += revenues[i];
        }
    }
    return weight_best_revenue;
}

int main(){

    // cin variable
    int Order = 0, Weight_h = 0, Weight_s = 0, Human = 0, Source = 0;
    int Revenue[100] = {0};
    int Human_need[100] = {0};
    int Source_need[100] = {0};

    // compute
    int Human_sum = 0, Source_sum = 0, Revenue_sum = 0;
    float Cps[100] = {0};
    float Cp_min = 0;
    int Accept[100] = {1};
    int drop = 0;
    int best_revenue = 0, current_revenue = 0;
    int best_w_h = 0, best_w_s = 0;

    //cin >> Order >> Weight_h >> Weight_s >> Human >> Source;
    cin >> Order >> Human >> Source;

    // cin revenue for each order and count overall need
    for (int i = 0; i < Order; i++){
        cin >> Revenue[i];
    }

    // cin human force need for each order and count overall need
    for (int i = 0; i < Order; i++){
        cin >> Human_need[i];
    }

    // cin source need for each order and count overall need
    for (int i = 0; i < Order; i++){
        cin >> Source_need[i];
    }
    
    //Weight_h = 2;
    //Weight_s = 3;
    for (int w_h = 0; w_h <= 5; w_h++){
        for(int w_s = 0; w_s <=5; w_s++){
            if ((w_s==0) & (w_h==0)){
                continue;
            }
            else{
                // by defult, we accept all order
                for (int i = 0; i < Order; i++){
                    Accept[i] = 1;
                }
                current_revenue = weightBestRev(Order, Human, Source,
                w_h, w_s, Revenue, Human_need, Source_need, Accept); // count current 
                // initial if this is the first weight combination
                if ((w_h == 0) & (w_s == 1)){
                    best_revenue = current_revenue;
                    best_w_h = w_h;
                    best_w_s = w_s;
                }
                else{
                    // 如果找到一樣或者更大的利潤
                    if (best_revenue <= current_revenue){
                        // 如果一樣
                        if (best_revenue == current_revenue){
                            // 往下比勞動力權重
                            if (w_h <= best_w_h){
                                // 如果勞動力權重一樣
                                if (w_h == best_w_h){
                                    // 往下比資源權重
                                    if(w_s < best_w_s){
                                        // 記下當前最佳利潤
                                        best_revenue = current_revenue;
                                        best_w_h = w_h;
                                        best_w_s = w_s;
                                    }
                                }
                                else{ // 如果勞動力權重比較小就直接記下來
                                    best_revenue = current_revenue;
                                    best_w_h = w_h;
                                    best_w_s = w_s;
                                }
                            }
                        }
                        else{ // 如果利潤比較小就直接記下來
                            best_revenue = current_revenue;
                            best_w_h = w_h;
                            best_w_s = w_s;
                        }
                    }
                }


            }
        }
    }
    // 印出答案
    cout << best_w_h << "," << best_w_s << "," << best_revenue << endl;

    return 0;
}