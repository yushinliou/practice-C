# include <iostream>
# include <vector>
# include <string>
# include <algorithm>
using namespace std;
// sort 參考 https://blog.gtwang.org/programming/c-sorting-algorithms-implementation/
// 參考：詢問chat gpt 請他介紹c++ template的用法
// 輸入數字只有一個的狀況底下會RE

int isAbiger(string a, string b){
    int twoNegative = 0;
    string numberA;
    string numberB;

    if ((a[0] == '-') & (b[0] != '-')){ return 0;} // 如果a是負數但是b不是，那就一定a沒比較大
    else if ((a[0] != '-') & (b[0] == '-')){ return 1;} // 如果a是不是負數但是b是，那就一定a比較大
    else if ((a[0] == '-') & (b[0] == '-')){ // 兩者皆為負數
        twoNegative = 1; // 記錄一下正在比較負數
        numberA = a.substr(1, a.size()); // 只截取數字部分去除掉正負號
        numberB = b.substr(1, b.size());
    }
    else{
        numberA = a;
        numberB = b;
    }
    // 接下來先比較長度
    if (numberA.size() != numberB.size()){ // 如果長度比得出來
        if (numberA.size() > numberB.size()){ // 如果A比較長
            if (twoNegative == 0){ return 1;} // 並且不是在比較兩個負數，那就是A大
            else{return 0;} // 如果是在比較兩個負數，那就是A沒有比較大了
        }
        else{ // 不然如果是B比較長
            if (twoNegative == 0){ return 0;} // 並且不是在比較兩個負數，那就是B大
            else{return 1;} // 如果是在比較兩個負數，那就是A比較大了
        }
    }
    else{ // 長度比較不出來，就來比較位元
        for(int i = 0; i < numberA.size(); i++){
            if (numberA[i] > numberB[i]){ // 如果A比較大
                if (twoNegative == 0){ return 1;} // 不是在比較負數，就是他真的比較大
                else{ return 0;}
                }
            else if (numberA[i] < numberB[i]){ // 如果B比較大
                if (twoNegative == 0){ return 0;} // 不是在比較負數，就是他真的比較大
                else{ return 1;}
                }
        }
    }
    return 0;
}

class Integer{
    friend std::ostream& operator<<(std::ostream& os, const Integer& p){
        os << p.number;
        return os;
    }
    friend std::istream& operator>>(std::istream& is, Integer& p){
        getline(is, p.number);
        return is;
    }
    public:
        Integer(){this->number = "0";}
        Integer(string number){this->number = number;}
        const Integer& operator=(const Integer& I){
            this->number = I.number;
            return *this;
        }
        bool operator>(const Integer& I) const;
    private:
        string number;
};
bool Integer::operator>(const Integer& I) const{
    if (isAbiger(this->number, I.number)){return true;}
    else{return false;}
}

void vecSort(vector<Integer>& data){
    Integer tmp;
    for (int i = 0; i < data.size(); i++){
        for (int j = 0; j < i; j++){
            if (data[i] > data[j]){
                tmp = data[j];
                data[j] = data[i];
                data[i] = tmp;
            }
        }
    }
}

class TopFourIntegers{
    public:
        void Add(Integer x);
        Integer Last();
    private:
        vector<Integer> data;
};
// problem in compare
void TopFourIntegers::Add(Integer x){
    if ((data.size()) < 4){
        data.push_back(x);
    }
    if (data.size() == 3){
        vecSort(data);
    }
    else if(x > data.back()){
        data.pop_back();
        data.push_back(x);
        vecSort(data);
    }
}
Integer TopFourIntegers::Last(){
    Integer x = data.back();
    return x;
}

// [YOUR CODE WILL BE PLACED HERE]



int main() {
    Integer integer;
    TopFourIntegers integers;
    std::cin >> integer;

    while (std::cin >> integer) {
        integers.Add(std::move(integer)); // intergers內加入move interger
    }
    std::cout << integers.Last() << std::endl; // 輸出intergers最後一行
    return 0;
}