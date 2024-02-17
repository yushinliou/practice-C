# include <iostream>
using namespace std;

int main()
{
    int max_need = 0, price = 0, cost = 0;
    double px[20] = {0};
    int sell = 0;
    double profit = 0, max_profit = 0;
    int max_profit_quqntity = 0;

    cin >> max_need >> price >> cost;
    // cin probability function
    for (int i = 0; i <= max_need; i++){
        cin >> px[i];
    }
    // try dif quantity
    for (int i = 0; i <= max_need ;i++){
        //cout << "i: " << i << endl;
        // in this quantity, we have dif probability in sell 0, 1, 2 ... max_need
        // go through different probability
        for (int j = 0; j <= max_need; j++){
            // if the corresponding sell > quantity
            if (j >= i){
                // we can only sell quantity
                sell = i;
            }
            else{
                sell = j;
            }
            profit += sell * (px[j] * 0.01) * price;
            //cout << sell << "*" << (px[j] * 0.01) << "*" << price << "\n";
            //cout << "sell: " << sell << " ";
        }
        // reduce the cost and get expect profit in this quantity
        profit -= cost * i;
        // if this quantity can bring more than previous
        if (profit > max_profit){
            // record it
            max_profit = profit;
            max_profit_quqntity = i;
        }
        // return to 0 so that we can go next round
    profit = 0;
    }
    cout << max_profit_quqntity << ",";
    cout << max_profit;
    return 0;
}