# include <iostream>
using namespace std;
// int findWorst (int itemCount , int weightH , int weightS , const Order orders []
// , const int currentSol []);

struct orderFeature
{
    /* data */
    int Revenue;
    int Human_need;
    int Source_need;
};

int findWorst(int order, int weight_h, int weight_s, const orderFeature orderF[],
const int accept[100])
{
    int worst = 0;
    float cps[100] = {0};
    float cp_up = 0, cp_down = 0;
    float cp_min = 0;
    int ct = 0;
    // compute all cp value
    // cout << "cp:" << endl;
    for (int i = 0; i < order; i++){
        cp_up = orderF[i].Revenue;
        cp_down = ((weight_h * orderF[i].Human_need) + (weight_s * orderF[i].Source_need));
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
                        if (orderF[i].Revenue < orderF[worst].Revenue){
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

int keepDrop(int order, int human, int source, 
const orderFeature orderF[], const int accept[100])
{
    int keepdrop = 0;
    int human_sum = 0, source_sum = 0;

    for (int i = 0; i < order; i++){
        if (accept[i] == 1){
            human_sum += orderF[i].Human_need;
            source_sum += orderF[i].Source_need;
        }
    }
    if ((human_sum <= human) & (source_sum <= source)){
        keepdrop = 0;
    }
    else{
        keepdrop = 1;
    }
    //cout << "current human sum:" << human_sum << " human" << human << endl;
    //cout << "current source sum:" << source_sum << " source" << source << endl;
    //cout << "keep drop:" << keepdrop << endl;
    return keepdrop;
}

void print_ans(int order, int source_sum, int human_sum, const orderFeature orderF[],
const int accept[100])
{
    int revenue_sum = 0;
    for (int i = 0; i < order-1; i ++){
        cout << accept[i] << ",";
    }
    for (int i = 0; i < order; i++){
        if (accept[i] == 1){
            revenue_sum += orderF[i].Revenue;
        }
    }
    cout << accept[order-1] << ";" << revenue_sum;
    return;
}

int main(){

    // cin variable
    int Order = 0, Weight_h = 0, Weight_s = 0, Human = 0, Source = 0;
    // int Revenue[100] = {0};
    // int Human_need[100] = {0};
    // int Source_need[100] = {0};
    
    struct orderFeature orderF[100];
    
    // compute
    int Human_sum = 0, Source_sum = 0, Revenue_sum = 0;
    float Cps[100] = {0};
    float Cp_min = 0;
    int Accept[100] = {1};
    int drop = 0;

    cin >> Order >> Weight_h >> Weight_s >> Human >> Source;

    // cin revenue for each order and count overall need
    for (int i = 0; i < Order; i++){
        cin >> orderF[i].Revenue;
        Revenue_sum += orderF[i].Revenue;
    }

    // cin human force need for each order and count overall need
    for (int i = 0; i < Order; i++){
        cin >> orderF[i].Human_need;
        Human_sum += orderF[i].Human_need;
    }

    // cin source need for each order and count overall need
    for (int i = 0; i < Order; i++){
        cin >> orderF[i].Source_need;
        Source_sum += orderF[i].Source_need;
    }

    // by defult, we accept all order
    for (int i = 0; i < Order; i++){
        Accept[i] = 1;
    }

    if ((Human_sum <= Human) & (Source_sum <= Source)){
        print_ans(Order, Source_sum, Human_sum, orderF, Accept);
        return 0;
    }
    else{
        for (int i = 0; i < Order; i++){
            if (keepDrop(Order, Human, Source, orderF, Accept) == 1){
                drop = findWorst(Order, Weight_h, Weight_s,
                orderF, Accept);
                Accept[drop] = 0;
                //cout << "drop" << drop+1 << endl;
            }
            else{
                break;
            }
        }
    }
    
    print_ans(Order, Source_sum, Human_sum, orderF, Accept);

    return 0;
}