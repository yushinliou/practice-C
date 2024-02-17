# include <iostream>
using namespace std;

void findOptQty(int max_need, int price_num, int cost, 
const int price[10], const double px[100][100])
{
    int sell = 0;
    double profit = 0, max_profit = 0;
    int max_profit_quantity = 0, max_price = 0;

    // try dif quantity
    for (int i = 0; i <= max_need ;i++){
        //cout << "i: " << i << endl;

    // in this quantity, try dif price
    for (int k = 0; k < price_num; k++){
        // in this quantity and price, go through dif sell
        for (int j = 0; j <= max_need; j++){
        // if the corresponding sell > quantity
        if (j >= i){
            // we can only sell quantity
            sell = i;
        }
        else{
            sell = j;
        }
        profit += sell * (px[k][j] * 0.01) * price[k];
        //cout << sell << "*" << (px[j] * 0.01) << "*" << price << "\n";
        //cout << "sell: " << sell << " ";
        }
        // reduce the cost and get expect profit in this quantity
        profit -= cost * i;
        // if this quantity can bring more than previous
        if ((k == 0) & (i == 0)){
            max_profit = profit;
            max_profit_quantity = i;
            max_price = price[k];
        }
        else if (profit > max_profit){
            max_profit = profit;
            max_profit_quantity = i;
            max_price = price[k];       
        }
        else if (profit == max_profit){
            max_profit = profit;
            if (price[k] < max_price){
                max_price = price[k];
                max_profit_quantity = i;
            }
            else if (price[k] == max_price){
                if (i <= max_profit_quantity){
                    max_profit_quantity = i;
                }
            }
        }
        profit = 0;
        }
        // return to 0 so that we can go next round
    }
    // cout answer
    cout << max_price << ",";
    cout << max_profit_quantity << ",";
    cout << max_profit;

    return;
}

int main()
{
    int biggest_need = 0, price_number = 0, pay = 0;


    int prices[10] = {0};
    double possible[100][100] = {0};

    cin >> biggest_need >> price_number >> pay;

    // cin possible price
    for (int i = 0; i < price_number; i++){
        cin >> prices[i];
    }
    // cin probability function
    for (int j = 0; j < price_number; j++){
        for (int i = 0; i <= biggest_need; i++){
            cin >> possible[j][i];
        }
    }
    // call function
    findOptQty(biggest_need, price_number, pay, prices, possible);


    return 0;
}

