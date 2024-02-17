# include <iostream>
using namespace std;

int main(){
    // range
    // 1 <= max_need <= 20, 1 <= price_num <= 5, 1 <= cost <= 100;
    int max_need = 1, price_num = 1, cost = 1;
    // price 100, 200, 300, ... , 1000 
    int price[10] = {0};
    // px = 0 1 2 .. 100
    float px[100][100] = {0};

    float profit = 0;
    float max_profit = -1000000, max_quantity = 0, max_price = 0;
    int sell = 0;

    cin >> max_need >> price_num >> cost;

    // read possible price
    for (int i = 0; i < price_num; i++){
        cin >> price[i];
    }
    /*
    for (int i = 0; i < price_num; i++){
        cout << price[i] << " ";
    }*/
    // try diferent quantity

    for (int i=0; i < price_num; i++){
        for (int j=0; j < max_need; j++){
            cin >> px[i][j];
        }
    }

    for (int i = 0; i <= max_need; i++){
        // in this quantity, try diefferent price
        for (int j = 0; j < price_num; j++){
            // in this quantity and price, go throught dif probability
            for (int k = 0; k <= max_need; k++){
                if (k >= i){
                    sell = i;
                }
                else{
                    sell = k;
                }
                profit += price[j] * sell * px[j][k];
            }
        profit -= cost * i;
        if ((i == 0) & (j == 0)){
            max_profit = profit;
            max_quantity = i;
            max_price = price[j];
        }
        // 當同時有數組的單位零售價格或進貨量都可以達到最大預期利潤時
        // 先選擇單位零售價格price[j]最小的那一組輸出
        // 若還有數組的單位零售價格都一樣，則選擇進貨量最小i的輸出。
        else if (profit >= max_profit){
            max_profit = profit;
            if (price[j] <= max_price){
                max_price = price[j];
                if (i <= max_quantity){
                    max_quantity = i;
                }
            }
        }
        }
    profit = 0;
    }
    cout << max_price << "," << max_quantity << "," << max_profit;

    return 0;
}


