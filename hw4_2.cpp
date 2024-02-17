# include <iostream>
using namespace std;

int findWorst(int order, int weight_h, int weight_s, const int revenues[],
const int human_need[100], const int source_need[100], const int accept[100])
{
    // compute cp value for each order
    float cps[100] = {0};

    cout << "cp:" << endl;
    
    for (int i = 0; i < order; i++){
        cps[i] = ((revenues[i]) /
        ((weight_h * human_need[i]) + (weight_s * source_need[i])));
        cout << cps[i] << " ";
        cout << "revenues[i]:" << revenues[i]<< "/" <<
        ((weight_h * human_need[i]) + (weight_s * source_need[i])) << endl;
    }
    
    for(int i = 0; i < order; i++){
        // cout << "i:" << i << endl;
        // go through all current accept order and try to find the minum
        for (int i = 0; i < order; i++){
            if (accept[i] == 1){
                // record the first order's cp value
                if (i == 0){
                    cp_min = cps[i];
                    min_order = i;
                }
                // compare with other cp value, if orther order have smaller cp
                if (cps[i] < cp_min){
                    // record it number
                    // record current minum
                    cout << cp_min << " < " << cp_min << endl;
                    cp_min = cps[i];
                    min_order = i;
                }
                else if (cps[i] == cp_min){
                    // if this order's revenue smaller than current cp minum order 
                    if (revenues[i] < revenues[min_order]){
                        // renow the min order number
                        cp_min = cps[i];
                        min_order = i;
                    }
                }
            }
        }

        accept[min_order] = 0; // drop order
        cout << "drop:" << min_order+1 << endl;
        // count current order need how many human and source
        human_sum = 0;
        source_sum = 0;
        revenues_sum = 0;
        // cout << "hi" << endl;
        for (int i = 0; i < order; i++){
            if (accept[i] == 1){
                human_sum += human_needs[i];
                source_sum += source_needs[i];
                revenues_sum += revenues[i];
            }
        }
        cout << "current huamn_sum:" << human_sum << " human" << human <<  endl;
        cout << "current source_sum:" << source_sum << " source" << source << endl;
        if ((human_sum <= human) & (source_sum <= source)){
            cout << "break huamn_sum:" << human_sum << " human" << human <<  endl;
            cout << "break source_sum:" << source_sum << " source" << source << endl;
            cout << "break!" << endl;
            break;
        }
    }
    return;
}

void print_ans(int order, int source_sum, int human_sum, int revenue_sum,
const int accept[100])
{
    for (int i = 0; i < order-1; i ++){
        cout << accept[i] << ",";
    }
    cout << accept[order-1] << ";" << revenue_sum;
    return;
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
    int droup_num = 0;

    cin >> Order >> Weight_h >> Weight_s >> Human >> Source;

    // cin revenue for each order and count overall need
    for (int i = 0; i < Order; i++){
        cin >> Revenue[i];
        Revenue_sum += Revenue[i];
    }

    // cin human force need for each order and count overall need
    for (int i = 0; i < Order; i++){
        cin >> Human_need[i];
        Human_sum += Human_need[i];
    }

    // cin source need for each order and count overall need
    for (int i = 0; i < Order; i++){
        cin >> Source_need[i];
        Source_sum += Source_need[i];
    }

    // by defult, we accept all order
    for (int i = 0; i < Order; i++){
        Accept[i] = 1;
    }

    // test whether current accept list is ok
    // if not ok, find worst and drop it
    //break loop if accept list is ok

    while((Source_sum > Source) & (Human_sum > Human)){
        droup_num = findWorst(Order, Weight_h, Weight_s,
                    Revenue, Human_need, Source_need, Accept);
        Accept = dropOrder(Accept, drop_num);
    }
    
    print_ans(Order, Source_sum, Human_sum, Revenue_sum, Accept); //


    
    int current_order = 0;
    int min_order = 0;


    // 如果有多張訂單的 C/P 值都同為最小，則選擇丟棄營收較低的訂單；
    //若還是有多個選擇，則選擇丟棄編號較小的訂單。
    return 0;
}
