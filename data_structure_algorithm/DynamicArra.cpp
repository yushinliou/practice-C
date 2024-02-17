#include <iostream>
#include <initializer_list>
#include <stdexcept>
#include <cassert>     // For Test
#include <random>     // For Test
#include <functional> // For Test

// 型態 T 會支援預設建構、複製建構與複製賦值
template<typename T>
class DynamicArray {
public:
    DynamicArray() = default;
    DynamicArray(std::initializer_list<T> l);
    explicit DynamicArray(size_t count);
    DynamicArray(DynamicArray<T>&& rhs) noexcept;
    DynamicArray(const DynamicArray<T>& rhs);
    DynamicArray<T>& operator=(const DynamicArray<T>& rhs);
    DynamicArray<T>& operator=(DynamicArray<T>&& rhs) noexcept;
    ~DynamicArray();

    bool operator==(const DynamicArray<T>& rhs) const;
    bool operator!=(const DynamicArray<T>& rhs) const;

    T& operator[](size_t pos) ;
    const T& operator[](size_t pos) const;

    void Resize(size_t count);

    void PushBack(const T& val);
    void PushBack(T&& val);
    void PopBack();

    [[nodiscard]] size_t Find(const T& val) const;
    [[nodiscard]] size_t Count(const T& val) const;

    [[nodiscard]] DynamicArray<T> Concatenate(const DynamicArray<T>& other) const;
    [[nodiscard]] DynamicArray<T> operator+(const DynamicArray<T>& other) const;
    [[nodiscard]] DynamicArray<T> Repeat(size_t times) const;
    [[nodiscard]] DynamicArray<T> operator*(size_t times) const;

    [[nodiscard]] DynamicArray<T> Slice(size_t start, size_t stop) const;
    DynamicArray<T> Split(size_t pos);

    DynamicArray<T>& Unique();

    DynamicArray<T>& Reverse();
    DynamicArray<T>& Rotate(size_t step = 1);

    [[nodiscard]] size_t Size() const { return size_; }

private:
    size_t size_ = 0;
    size_t capacity_ = 0;
    T* elems_ = nullptr;
};

template<typename T>
std::ostream& operator<<(std::ostream& os, const DynamicArray<T>& v) {
    if (v.Size() == 0) return os << "[]";
    os << '[' << v[0];
    for (size_t i = 1; i < v.Size(); i++) {
        os << ", " << v[i];
    }
    return os << ']';
}

void Test1(); // Sample1
void Test2(); // Find, Count
void Test3(); // Reverse, Rotate
void Test4(); // Concatenate, operator+, Repeat, operator*
void Test5(); // Slice, Split, Unique
void Test6(); // All
void Test7(); // Find, Count
void Test8(); // Reverse, Rotate
void Test9(); // Concatenate, operator+, Repeat, operator*
void Test10(); // Slice, Split, Unique
void Test11(); // All

int main() {
    int id;
    std::cin >> id;
    void (*f[])() = {
            Test1, Test2, Test3, Test4, Test5,
            Test6, Test7, Test8, Test9, Test10,
            Test11
    };
    f[id-1]();
}

template<typename T>
DynamicArray<T>::DynamicArray(std::initializer_list<T> l) :
        size_{l.size()}, capacity_{size_}, elems_{new T[capacity_]} {
    size_t i = 0;
    for (const T& v: l) {
        elems_[i] = v;
        ++i;
    }
}

template<typename T>
DynamicArray<T>::DynamicArray(size_t count) :
        size_{count}, capacity_{size_}, elems_{new T[capacity_]{}} {
}

template<typename T>
DynamicArray<T>::DynamicArray(const DynamicArray<T>& rhs) :
        size_{rhs.size_}, capacity_{size_}, elems_{new T[capacity_]}
{
    for (size_t i = 0; i < size_; i++) {
        elems_[i] = rhs.elems_[i];
    }
}

template<typename T>
DynamicArray<T>::DynamicArray(DynamicArray<T>&& rhs) noexcept :
        size_{rhs.size_}, capacity_{rhs.capacity_}, elems_{rhs.elems_}
{
    rhs.size_ = 0;
    rhs.capacity_ = 0;
    rhs.elems_ = nullptr;
}

template<typename T>
DynamicArray<T>::~DynamicArray() {
    delete[] elems_;
}

template<typename T>
DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray<T>& rhs) {
    if (this == &rhs) {
        return *this;
    }
    Resize(rhs.size_);
    for (size_t i = 0; i < size_; i++) {
        elems_[i] = rhs.elems_[i];
    }
    return *this;
}

template<typename T>
DynamicArray<T>& DynamicArray<T>::operator=(DynamicArray<T>&& rhs) noexcept {
    size_ = rhs.size_;
    capacity_ = rhs.capacity_;
    std::swap(elems_, rhs.elems_);
    return *this;
}

template<typename T>
void DynamicArray<T>::Resize(size_t count) {
    if (count <= capacity_) {
        for (size_t i = size_; i < count; i++) {
            elems_[i] = T{};
        }
        size_ = count;
        return;
    }

    size_t newCapacity = std::max(count, 2 * (capacity_ + 1));

    T* newElems = new T[newCapacity]{};
    for (size_t i = 0; i < size_; i++) {
        newElems[i] = elems_[i];
    }
    delete[] elems_;

    size_ = count;
    capacity_ = newCapacity;
    elems_ = newElems;
}

template<typename T>
void DynamicArray<T>::PushBack(const T& val) {
    Resize(Size()+1);
    operator[](Size()-1) = val;
}

template<typename T>
void DynamicArray<T>::PushBack(T&& val) {
    Resize(Size()+1);
    operator[](Size()-1) = std::move(val);
}

template<typename T>
void DynamicArray<T>::PopBack() {
    if (size_ == 0) {
        throw std::out_of_range("PopBack(): Array is empty.");
    }
    Resize(Size()-1);
}

template<typename T>
T& DynamicArray<T>::operator[](size_t pos) {
    if (pos >= size_) {
        throw std::out_of_range{ "operator[](pos): " + std::to_string(pos) + " >= " + std::to_string(size_)};
    }
    return elems_[pos];
}

template<typename T>
const T& DynamicArray<T>::operator[](size_t pos) const {
    return const_cast<DynamicArray*>(this)->operator[](pos);
}

namespace Feis { /* HIDDEN */ }

void Test1()  {
    // 實作 Find(val) 方法，回傳第一個與指定值 (val) 相等的元素所在位置的索引號
    // - 當陣列中沒有元素與該值相等時，則回傳陣列的長度
    // 實作 Count(val) 方法，回傳陣列內與指定值 (val) 相等的元素個數
    {
        DynamicArray<int> a = {3, 9, 1, 7, 5, 6, 3};
        std::cout << a.Find(3) << std::endl; // 印出 0
        std::cout << a.Find(4) << std::endl; // 印出 7
        std::cout << a.Find(5) << std::endl; // 印出 4

        std::cout << a.Count(3) << std::endl; // 印出 2
        std::cout << a.Count(4) << std::endl; // 印出 0
        std::cout << a.Count(5) << std::endl; // 印出 1
    }

    // 實作 Reverse() 方法，將陣列內的元素前後順序反轉後回傳陣列本身
    // - [1, 2, 3] 陣列呼叫 Reverse() 方法後會變成 [3, 2, 1]
    // 實作 Rotate(step) 方法，將陣列內的元素旋轉 step 次後回傳陣列本身
    // - 每旋轉 (rotate) 一次的意思是將所有元素都往右邊移動一格，而原本最右邊的元素移動到第一格
    // - [1, 2, 3, 4] 執行 Rotate(1) 會變成 [4, 1, 2, 3]
    // - [1, 2, 3, 4] 執行 Rotate(3) 會變成 [2, 3, 4, 1]
    {
        DynamicArray<int> a = {3, 9, 1, 7, 5, 6, 3};

        std::cout << a.Reverse() << std::endl; // 印出 [3, 6, 5, 7, 1, 9, 3]
        std::cout << a << std::endl;           // 印出 [3, 6, 5, 7, 1, 9, 3]

        std::cout << a.Rotate() << std::endl;  // 印出 [3, 3, 6, 5, 7, 1, 9]
        std::cout << a << std::endl;           // 印出 [3, 3, 6, 5, 7, 1, 9]

        std::cout << a.Rotate(3) << std::endl; // 印出 [7, 1, 9, 3, 3, 6, 5]
        std::cout << a << std::endl;                // 印出 [7, 1, 9, 3, 3, 6, 5]
    }

    // 實作 Concatenate(other) 方法，回傳一個新的陣列，該陣列為兩個陣列前後串接的的結果
    // - 對 [1, 2, 3, 4] 陣列呼叫 Concatenate() 且 other 為 [5, 6] 陣列的話，會回傳 [1, 2, 3, 4, 5, 6] 陣列
    // 實作加法 (+) 運算子，回傳一個新的陣列，該陣列為兩個陣列前後串接的的結果
    // 實作 Repeat(times) 方法，傳入一個非負整數表示串接次數 (times) 後回傳一個新的陣列，該陣列為原本陣列重複串接指定次數的結果
    // - 對 [1, 2] 陣列呼叫 Repeat() 且 times 為 3 的話，則會回傳 [1, 2, 1, 2, 1, 2] 陣列
    // 實作乘法 (*) 運算，讓物件可以跟一個非負整數相乘。會回傳一個新的陣列，該陣列為原本陣列重複串接指定次數的結果
    // - 將 [1, 2] 陣列乘上 3 時，會得到 [1, 2, 1, 2, 1, 2] 陣列
    {
        DynamicArray<int> a = {3, 9, 1, 7};
        DynamicArray<int> b = {4};

        std::cout << a.Concatenate(b) << std::endl; // 印出 [3, 9, 1, 7, 4, 6, 5]

        std::cout << a << std::endl; // 印出 [3, 9, 1, 7]
        std::cout << b << std::endl; // 印出 [4, 6, 5]

        std::cout << (a + b) << std::endl; // 印出 [3, 9, 1, 7, 4, 6, 5]

        std::cout << a << std::endl; // 印出 [3, 9, 1 ,7]
        std::cout << b << std::endl; // 印出 [4, 6, 5]
        std::cout << "Mytest______" << std::endl; // 印出 [4, 6, 5]
        std::cout << b.Repeat(3) << std::endl; // 印出 [4, 6, 5, 4, 6, 5, 4, 6, 5]
        std::cout << b << std::endl;                // 印出 [4, 6, 5]

        std::cout << (b * 3) << std::endl;          // 印出 [4, 6, 5, 4, 6, 5, 4, 6, 5]
        std::cout << b << std::endl;                // 印出 [4, 6, 5]
    }

    // 實作 Slice(start, end) 方法，創建並回傳由原陣列的指定範圍 [start, end) 構成的子陣列
    // - 起點 (start) 與終點 (end) 用陣列元素位置的索引號 (從 0 開始數) 表示
    // - 範圍 (range) 包含起點 (start) 但不包含終點 (end) : 回傳的子陣列由原本陣列的第 start, start+1, start+2, ... 到 end-1 號元素所構成
    // - 對 [1, 2, 3, 4] 陣列呼叫 Slice(1, 3) 會回傳新的 [2, 3] 陣列
    // - 如果起點 (start) 大於終點 (end)，則回傳空陣列 []
    // - 如果 [start, end) 的範圍超過陣列大小時，則取不到的元素就取不到，不會發生例外
    // - 對 [1, 2, 3, 4] 陣列呼叫 Slice(1, 10) 會回傳新的 [2, 3, 4] 陣列
    // - 對 [1, 2, 3, 4] 陣列呼叫 Slice(10, 20) 會回傳空陣列 []
    // 實作 Split(pos) 方法，給定一個切割位置 (pos)，將切割位置前的元素保留在原有陣列，但回傳一個包含切割位置以後 (包含切割位置) 所有元素的新陣列
    // - 對 [4, 5, 6, 7] 陣列呼叫 Split(2) 會將原有陣列縮小變成 [4, 5]，並回傳一個新陣列 [6, 7]
    // - 當切割位置超過陣列範圍時，則原有陣列不變並回傳空陣列 []，不會發生例外。
    {
        DynamicArray<int> a = {3, 9, 1, 7};
        std::cout << a.Slice(1, 3) << std::endl; // 印出 [9, 1]
        std::cout << a << std::endl;                       // 印出 [3, 9, 1, 7]
        std::cout << a.Slice(3, 1) << std::endl; // 印出 []
        std::cout << a << std::endl;                       // 印出 [3, 9, 1, 7]
        std::cout << a.Slice(0, 10) << std::endl;// 印出 [3, 9, 1, 7]
        std::cout << a << std::endl;                       // 印出 [3, 9, 1, 7]
        std::cout << a.Slice(6, 10) << std::endl;// 印出 []
        std::cout << a << std::endl;                       // 印出 [3, 9, 1, 7]

        std::cout << a.Split(2) << std::endl; // 印出 [1, 7]
        std::cout << a << std::endl;              // 印出 [3, 9]
    }

    // 實作 operator==(other) 回傳與 other 陣列的長度跟內容值是否都相等 (==)
    // 實作 operator!=(other) 回傳與 other 陣列的長度或內容值是否有任何一個不相等 (!=)
    // 實作 Unique() 方法，將陣列內重複出現的元素都去除，只保留出現在最前面位置的同值元素，並回傳去除重複元素的陣列本身
    // - 對 [1, 2, 3, 4, 1, 2, 3] 陣列呼叫 Unique() 方法，會將原有陣列改為 [1, 2, 3, 4]
    {
        DynamicArray<int> a = {5, 3, 2, 8, 7, 9};
        DynamicArray<int> b = {5, 3, 3, 5, 2, 8, 7, 3, 9, 5};

        std::cout << std::boolalpha << (a == b) << std::endl;  // 印出 false
        std::cout << std::boolalpha <<  (a != b) << std::endl; // 印出 true

        std::cout << b.Unique() << std::endl; // 印出 [5, 3, 2, 8, 7, 9]
        std::cout << b << std::endl;          // 印出 [5, 3, 2, 8, 7, 9]

        std::cout << std::boolalpha <<  (a == b) << std::endl; // 印出 true
        std::cout << std::boolalpha <<  (a != b) << std::endl; // 印出 false
    }
}

void Test2() { /* HIDDEN */ }
void Test3() { /* HIDDEN */ }
void Test4() { /* HIDDEN */ }
void Test5() { /* HIDDEN */ }
void Test6() { /* HIDDEN */ }
void Test7() { Test2(); }
void Test8() { Test3(); }
void Test9() { Test4(); }
void Test10() { Test5(); }
void Test11() { Test6(); }


// [YOUR CODE WILL BE PLACED HERE]
// [[nodiscard]] size_t Find(const T& val) const;
# include <algorithm>
// #include <unordered_set>
using std::swap;
using namespace std;
template<typename T>
size_t DynamicArray<T>::Find(const T& val) const{
    if (size_ == 0){return 0;}
    else{
        for(size_t i = 0; i < size_; i++){
            if (elems_[i] == val){return i;}
        }
        return size_;
    }
}
    
// [[nodiscard]] size_t Count(const T& val) const;
template<typename T>
size_t DynamicArray<T>::Count(const T& val) const{
    size_t ct = 0;
    if (size_ == 0){return ct;}
    else{
        for(size_t i = 0; i < size_; i++){
            if (elems_[i] == val){ct++;}
        }
        return ct;
    }
}
// DynamicArray<T>& Reverse();
// 實作 Reverse() 方法，將陣列內的元素前後順序反轉後回傳陣列本身
// reverse algorithm
template<typename T>
DynamicArray<T>& DynamicArray<T>::Reverse(){
    if (size_ < 2) return *this;
    if ((size_ % 2) == 0){
        for (size_t i = 0; i < (size_/2); i++){
            swap(elems_[size_-1-i], elems_[i]);
        }
    }
    else{
        for (size_t i = 0; i < (size_/2); i++){
            swap(elems_[size_-1-i], elems_[i]);
        }
    }
    return *this;
}

// [[nodiscard]] DynamicArray<T> Concatenate(const DynamicArray<T>& other) const;
template<typename T>
DynamicArray<T> DynamicArray<T>::Concatenate(const DynamicArray<T>& other) const{
    if (size_ == 0){return other;}
    else if (other.size_ == 0){return *this;}
    else{
        DynamicArray<T> newAry = *this;
        size_t newSize = size_+other.size_, j = 0;
        newAry.Resize(newSize);
        for(size_t i = size_; i < newSize; i++){
            newAry[i] = other[j];
            j++;
        }
        return newAry;
    }
}
// [[nodiscard]] DynamicArray<T> operator+(const DynamicArray<T>& other) const;
template<typename T>
DynamicArray<T> DynamicArray<T>::operator+(const DynamicArray<T>& other) const{
    return Concatenate(other);
}

// [[nodiscard]] DynamicArray<T> Repeat(size_t times) const;
template<typename T>
DynamicArray<T> DynamicArray<T>::Repeat(size_t times) const{
    DynamicArray<T> newAry;
    if (size_ == 0){return newAry;}
    else{
        newAry.Resize(size_*times);
        for (size_t i = 0; i < times; i++){
            for (size_t j = 0; j < size_; j++){
                newAry[(size_*i)+j] = elems_[j];
            }
        }
        return newAry;
    }
}
// [[nodiscard]] DynamicArray<T> operator*(size_t times) const;
template<typename T>
DynamicArray<T> DynamicArray<T>::operator*(size_t times) const{
    return Repeat(times);
}

// [[nodiscard]] DynamicArray<T> Slice(size_t start, size_t stop) const;
template<typename T>
DynamicArray<T> DynamicArray<T>::Slice(size_t start, size_t stop) const{
    DynamicArray<T> newAry;
    if (stop > size_){stop = size_;}
    if (start > stop){return newAry;}
    else{
        size_t j = 0;
        newAry.Resize(stop-start);
        for (size_t i = start; i < stop; i++){
            newAry[j] = elems_[i];
            j++;
        }
        return newAry;
    }
}
// DynamicArray<T> Split(size_t pos);
template<typename T>
DynamicArray<T> DynamicArray<T>::Split(size_t pos){
    DynamicArray<T> newAry;
    if (pos >= size_){return newAry;}
    else{
        size_t j = 0;
        newAry.Resize(size_-pos);
        for (size_t i = pos; i < size_; i++){
            newAry[j] = elems_[i];
            j++;
        }
        Resize(pos);
        return newAry;
    }
}

template<typename T>
bool DynamicArray<T>::operator==(const DynamicArray<T>& rhs) const{
    if (size_ != rhs.Size()){return false;}
    else if ((size_ == 0) & (rhs.Size() == 0)){return true;}
    else{
        for (size_t i = 0; i < size_; i++){
            if (elems_[i] != rhs[i]){ return false;}
        }        
    }
    return true;
}
template<typename T>
bool DynamicArray<T>::operator!=(const DynamicArray<T>& rhs) const{
    if (*this == rhs){return false;}
    else{return true;}
}

// DynamicArray<T>& Unique();
// 
template<typename T>
DynamicArray<T>& DynamicArray<T>::Unique(){
    if (size_ == 0) return *this;
    else{
        bool duplicated = false;
        size_t uniCt = 1; //不重複元素的個數(至少第一個一定不重複)
        for (size_t i = 1; i < size_; i++){
            duplicated = false;
            for(size_t j = 0; j < uniCt; j++){
                if (elems_[j] == elems_[i]){
                    duplicated = true;
                    break;
                }
            }
            if (duplicated != true){
                elems_[uniCt] = elems_[i];
                uniCt++;
                }
        }
        Resize(uniCt); //調整陣列大小為不重複元素的個數
    }
    return *this;
}

// DynamicArray<T>& Rotate(size_t step = 1);
// 詢問chatGpt實作unque的演算法，並提供前面類別的程式碼，說明不能用vector/set
template<typename T>
DynamicArray<T>& DynamicArray<T>::Rotate(size_t step){
    DynamicArray<T> half2;
    size_t k = step % size_;
    if (size_ < 2){return *this;} // 如果是空的或者是一直接返回，不需要處理
    else if (size_ == 2){
        for (size_t i = 0; i < step; i++){
            Reverse();
        }
        return *this;
    }
    else{
        Reverse();
        half2 = Split(k);
        Reverse();
        half2.Reverse();
        *this = Concatenate(half2);
        return *this;
    }
}

// [[nodiscard]] size_t Size() const { return size_; }