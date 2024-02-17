#include <iostream>
#include <initializer_list>
#include <stdexcept>
#include <cassert>
#include <random>
#include <functional>

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

    [[nodiscard]] bool operator==(const DynamicArray<T>& rhs) const;
    [[nodiscard]] bool operator!=(const DynamicArray<T>& rhs) const;

    [[nodiscard]] T& operator[](size_t pos) ;
    [[nodiscard]] const T& operator[](size_t pos) const;

    [[nodiscard]] T& Front();
    [[nodiscard]] const T& Front() const;
    [[nodiscard]] T& Back();
    [[nodiscard]] const T& Back() const;

    void Resize(size_t count);

    void PushBack(const T& val);
    void PushBack(T&& val);

    void PopBack();

    void PushFront(const T& val);
    void PushFront(T&& val);

    void PopFront();

    void Insert(size_t pos, const T& val);
    void Insert(size_t pos, T&& val);
    void Erase(size_t pos);

    void Fill(const T& v);
    void Assign(size_t count, const T& val);
    void Clear() noexcept;
    void Remove(const T& val);
    void Swap(DynamicArray<T>& other);

    [[nodiscard]] size_t Size() const noexcept { return size_; }

    [[nodiscard]] size_t Capacity() const noexcept { return capacity_; }
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

void Test1();  // sample1
void Test2();  // Back, Clear 
void Test3();  // PushFront, PopFront // RE
void Test4();  // Insert, Erase 
void Test5();  // operator==, operator!=, Remove, Fill
void Test6();  // Swap, Assign
void Test7();  // All // RE
void Test8();  // PushFront, PopFront // RE
void Test9();  // Insert, Erase
void Test10(); // operator==, operator!=, Remove, Fill
void Test11(); // Swap, Assign
void Test12(); // All // RE

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int id;
    std::cin >> id;
    void (*f[])() = {
            Test1,  Test2, Test3, Test4, Test5,
            Test6,  Test7, Test8, Test9, Test10,
            Test11, Test12
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
    else{
        Resize(Size()-1);
    }
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

template<typename T>
T& DynamicArray<T>::Front() {
    if (size_ == 0) {
        throw std::out_of_range("Front(): Array is empty.");
    }
    return elems_[0];
}

template<typename T>
const T& DynamicArray<T>::Front() const {
    return const_cast<DynamicArray*>(this)->Front();
}

void Test1()  {
    // 實作 Back() 方法回傳最後一個元素 (element)
    // - 當陣列為空時，丟出訊息為 "Back(): Array is empty." 的 std::out_of_range 例外。
    // - 當有例外丟出時，物件維持呼叫 Back() 前的狀態。
    {
        DynamicArray<int> a = {3, 9, 1, 7, 5};
        const DynamicArray<int>& b = a;

        std::cout << a.Front() << std::endl; // 印出 3
        std::cout << a.Back() << std::endl;  // 印出 5
        std::cout << b.Front() << std::endl; // 印出 3
        std::cout << b.Back() << std::endl;  // 印出 5

        DynamicArray<int> c;

        try {
            std::cout << c.Front() << std::endl;
        } catch (const std::out_of_range& e) {
            std::cout << e.what() << std::endl; // 印出 "Front(): Array is empty."
        }
        std::cout << c << std::endl; // 印出 []

        try {
            std::cout << c.Back() << std::endl;
        } catch (const std::out_of_range& e) {
            std::cout << e.what() << std::endl; // 印出 "Back(): Array is empty."
        }
        std::cout << c << std::endl; // 印出 []
    }

    // 實作 PushFront(val) 方法在陣列最前面插入一個值為 val 的新元素 (element)
    // 實作 PopFront() 方法移除陣列最前面的元素 (element)
    // - 當陣列為空時，丟出訊息為 "PopFront(): Array is empty." 的例外。
    // - 當有例外丟出時，物件維持呼叫 PopFront() 前的狀態。
    {
        DynamicArray<int> a = {0};
        std::cout << a << std::endl; // 印出 []
        std::cout << "Mytest___1" << std::endl;
        for (size_t i = 1; i <= 3; i++) {
            a.PushFront(i);
            std::cout << a << std::endl;  // 依序印出 [1] -> [2, 1] -> [3, 2, 1]
        }
        std::cout << "Mytest___2" << std::endl;
        // a = {0};
        // for (size_t i = 1; i <= 3; i++) {
        //     a.PopBack();
        //     std::cout << a << std::endl; // 依序印出 [3, 2] -> [3] -> []
        // }
        std::cout << "Mytest___3" << std::endl;
        a = {0};
        for (size_t i = 1; i <= 3; i++) {
            a.PushFront(std::move(i));
            std::cout << a << std::endl; // 依序印出 [1] -> [2, 1] -> [3, 2, 1]
        }
        std::cout << "Mytest___4" << std::endl;
        a = {1,2,3};
        // for (size_t i = 1; i <= 3; i++) {
        //     a.PopFront();
        //     std::cout << a << std::endl; // 依序印出 [2, 1] -> [1] -> []
        // }
        for (size_t i = 0; i < 10; i++) {
            try {
                a.PopFront();
            } catch (const std::out_of_range &e) {
                std::cout << e.what() << std::endl;
            }
            std::cout << a << std::endl;
        }
    }

    // 實作 operator==(other) 回傳與 other 陣列的長度跟內容值是否都相等 (==)
    // 實作 operator!=(other) 回傳與 other 陣列的長度或內容值是否有任何一個不相等 (!=)
    // 實作 Remove(val) 方法，移除陣列中所有值等於 (==) val 的元素
    // 實作 Fill(val) 方法將陣列中所有元素都賦值為 val
    // 實作 Clear() 方法以移除陣列中所有元素 (element)，讓陣列為空
    {
        DynamicArray<int> a;
        DynamicArray<int> b;
        std::cout << std::boolalpha << (a == b) << std::endl; // 印出 false
        std::cout << std::boolalpha << (a != b) << std::endl; // 印出 true
        a.Resize(3);
        std::cout << std::boolalpha << (a == b) << std::endl; // 印出 true
        std::cout << std::boolalpha << (a != b) << std::endl; // 印出 false

        DynamicArray<int> d;
        //DynamicArray<int> d{};
        d.Remove(9);
        std::cout << d << std::endl; // 印出 [3, 1, 2, 1, 7]
        // d.Fill(9);
        std::cout << d << std::endl; // 印出 [9, 9, 9, 9, 9]
        d.Clear();
        std::cout << d << std::endl; // 印出 []
        DynamicArray<DynamicArray<int>> c{{3, 9}, {0, 8}};
        c.Remove({1});
        std::cout << c << std::endl; // 印出 [[0, 8]]
    }

    // 實作 Insert(pos, val) 方法插入值為 val 的新元素在第 pos 號的位置 (位置從 0 開始編號)
    // - 當插入位置 (pos) 大於陣列長度時，丟出訊息為 "Insert(pos, val): 位置編號 > 陣列長度" 的 std::out_of_range 例外。
    // - 當有例外丟出時，物件維持呼叫 Insert(pos, val) 前的狀態。
    // 實作 Erase(pos) 方法移除在第 pos 號位置的元素 (位置從 0 開始編號)
    // - 當移除位置 (pos) 大於或等於陣列長度時，丟出訊息為 "Erase(pos): 位置編號 >= 陣列長度" 的 std::out_of_range 例外
    // - 當有例外丟出時，物件維持呼叫 Erase(pos) 前的狀態。
    {
        DynamicArray<int> values{0, 3, 1, 4, 1, 4, 2, 0, 5, 3};

        DynamicArray<int> d;

        for (size_t i = 0; i < 10; i++) {
            try {
                int k = values[i];
                d.Insert(k, k);
            } catch (const std::out_of_range &e) {
                std::cout << e.what() << std::endl;
            }
            std::cout << d << std::endl;
        }
        // 依序印出 [0]
        //         Insert(pos, val): 3 > 1
        //         [0]
        //         [0, 1]
        //         Insert(pos, val): 4 > 2
        //         [0, 1]
        //         [0, 1, 1]
        //         Insert(pos, val): 4 > 3
        //         [0, 1, 1]
        //         [0, 1, 2, 1]
        //         [0, 0, 1, 2, 1]
        //         [0, 0, 1, 2, 1, 5]
        //         [0, 0, 1, 3, 2, 1, 5]
        d.Clear();
        for (size_t i = 0; i < 10; i++) {
            try {
                d.Erase(values[i]);
            } catch (const std::out_of_range &e) {
                std::cout << e.what() << std::endl;
            }
            std::cout << d << std::endl;
        }
        // 依序印出 [0, 1, 3, 2, 1, 5]
        //        [0, 1, 3, 1, 5]
        //        [0, 3, 1, 5]
        //        Erase(pos): 4 >= 4
        //        [0, 3, 1, 5]
        //        [0, 1, 5]
        //        Erase(pos): 4 >= 3
        //        [0, 1, 5]
        //        [0, 1]
        //        [1]
        //        Erase(pos): 5 >= 1
        //        [1]
        //        Erase(pos): 3 >= 1
        //        [1]

        for (size_t i = 0; i < 10; i++) {
            try {
                int k = values[i];
                d.Insert(k, values[i]);
            } catch (const std::out_of_range &e) {
                std::cout << e.what() << std::endl;
            }
            std::cout << d << std::endl;
        }
        // 依序印出 [0, 1]
        //        Insert(pos, val): 3 > 2
        //        [0, 1]
        //        [0, 1, 1]
        //        Insert(pos, val): 4 > 3
        //        [0, 1, 1]
        //        [0, 1, 1, 1]
        //        [0, 1, 1, 1, 4]
        //        [0, 1, 2, 1, 1, 4]
        //        [0, 0, 1, 2, 1, 1, 4]
        //        [0, 0, 1, 2, 1, 5, 1, 4]
        //        [0, 0, 1, 3, 2, 1, 5, 1, 4]
    }

    // 實作 Swap(other) 方法，與其他陣列 (other) 交換
    {
        DynamicArray<int> a;
        DynamicArray<int> b;
        a.Clear();
        b.Clear();
        std::cout << a << std::endl; // 印出 [3, 9, 1, 2]
        std::cout << b << std::endl; // 印出 [7, 6, 5]
        a.Swap(b);
        std::cout << a << std::endl; // 印出 [7, 6, 5]
        std::cout << b << std::endl; // 印出 [3, 9, 1, 2]
    }

    // 實作 Assign(count, val)，將陣列內容改為由指定個數 (count) 的指定值 (val) 構成
    {
        DynamicArray<int> a;
        a.Assign(1, 0);
        std::cout << a << std::endl; // 印出 [1, 1, 1, 1, 1, 1, 1]
    }
}

namespace Feis { /* HIDDEN */ }

void Test2() { /* HIDDEN */ }
void Test3() { /* HIDDEN */ }
void Test4() { /* HIDDEN */ }
void Test5() { /* HIDDEN */ }
void Test6() { /* HIDDEN */ }
void Test7() { /* HIDDEN */ }
void Test8() { Test3(); }
void Test9() { Test4(); }
void Test10() { Test5(); }
void Test11() { Test6(); }
void Test12() { Test7(); }

// [YOUR CODE WILL BE PLACED HERE]
// [YOUR CODE WILL BE PLACED HERE]
# include <string>
using std::swap;
using namespace std;
// [[nodiscard]] T& Back();
// [[nodiscard]] const T& Back() const;
// Back, 回傳最後面的元素
template<typename T>
T& DynamicArray<T>::Back() {
    if (size_ == 0) {
        throw out_of_range("Back(): Array is empty.");
    }
    else{
        return operator[](Size()-1);
    }
}

template<typename T>
const T& DynamicArray<T>::Back() const {
    if (size_ == 0) {
        throw out_of_range("Back(): Array is empty.");
    }
    else{
        return operator[](Size()-1);
    }
}
// 實作 PushFront(val) 方法在陣列最前面插入一個值為 val 的新元素 (element)
// void PushFront(const T& val); // void PushFront(T&& val);
template<typename T>
void DynamicArray<T>::PushFront(const T& val) {
    Resize(Size()+1);
    if (size_ == 1){
        operator[](0) = val;
    }
    else {
        if (size_ == 2){
            operator[](1) = move(elems_[0]);
            operator[](0) = val;
        }
        else{
            for(size_t i = size_-1; i > 0; i--){
                // cout << "i" << i << "i-1" << i-1 << endl;
                operator[](i) = elems_[i-1];
            }
            operator[](0) = val;
        }
    }
}
// template<typename T>
// void DynamicArray<T>::PushFront(T&& val){
//     return const_cast<DynamicArray*>(this)->PushFront(val);
// }我把我下面的程式碼提供給chat gpt，以下是他提供給我的修改建議
template<typename T>
void DynamicArray<T>::PushFront(T&& val){
    Resize(Size()+1);
    if (size_ == 1){
        operator[](0) = move(val);
    }
    else {
        if (size_ == 2){
            operator[](1) = move(elems_[0]);
            operator[](0) = move(val);
        }
        else{
            for(size_t i = size_-1; i > 0; i--){
                operator[](i) = move(elems_[i-1]);
            }
            operator[](0) = move(val);
        }
    }
}

// void PopFront();
template<typename T>
void DynamicArray<T>::PopFront(){
    if (size_ == 0){
        throw out_of_range("PopFront(): Array is empty.");
    }
    else{
        if (size_ == 1){
            PopBack();
        }
        else{
            for (size_t i = 0; i < size_-1; i++){
                operator[](i) = move(elems_[i+1]);
            }
            Resize(Size()-1);
        } 
    }
}

// [[nodiscard]] bool operator==(const DynamicArray<T>& rhs) const;
// [[nodiscard]] bool operator!=(const DynamicArray<T>& rhs) const;
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
// void Remove(const T& val);
template<typename T>
void DynamicArray<T>::Remove(const T& val){
    if (size_ != 0){
        size_t ori_size = size_;
        for (size_t i = ori_size-1; i > 0; i--){
            if (elems_[i] == val){
                this->Erase(i);
            }
        }
        if (elems_[0] == val){
            this->Erase(0);
        }
    }
}

// void Fill(const T& v);
template<typename T>
void DynamicArray<T>::Fill(const T& val){
    if (size_ != 0){
        for (size_t i = 0; i < size_; i++){
            operator[](i) = val;
        }        
    }
}
// Clear()
// 我詢問了童浩庭同學，他回答我可以直接用resize 0 來清除內容
template<typename T>
void DynamicArray<T>::Clear() noexcept{
    if (size_ != 0){
    Resize(0);
    }
}

// void Insert(size_t pos, const T& val);
// void Insert(size_t pos, T&& val);
template<typename T>
void DynamicArray<T>::Insert(size_t pos, const T& val){
    // cout << "star inset" << endl;
    if (pos > size_){
        string errorMsg = "Insert(pos, val): ";
        errorMsg += to_string(pos);
        errorMsg += " > ";
        errorMsg += to_string(size_);
        throw out_of_range(errorMsg);
    }
    else{
        // cout << "star re" << endl;
        Resize(Size()+1);
        // cout << size_ << *this << "insert " << val << "in" << pos << endl;
        if (size_ == 0){
            operator[](0) = val;
        }
        else{
            for (size_t i = size_-1; i > pos; i--){
                operator[](i) = elems_[i-1];
            }
            operator[](pos) = val;
        }
    }
}

template<typename T>
void DynamicArray<T>::Insert(size_t pos, T&& val){
    // cout << "star inset" << endl;
    if (pos > size_){
        string errorMsg = "Insert(pos, val): ";
        errorMsg += to_string(pos);
        errorMsg += " > ";
        errorMsg += to_string(size_);
        throw out_of_range(errorMsg);
    }
    else{
        // cout << "star re" << endl;
        Resize(Size()+1);
        // cout << size_ << *this << "insert " << val << "in" << pos << endl;
        if (size_ == 0){
            operator[](0) = val;
        }
        else{
            for (size_t i = size_-1; i > pos; i--){
                operator[](i) = move(elems_[i-1]);
            }
            operator[](pos) = move(val);
        }
    }
}


// void Erase(size_t pos);
// 詢問了chat Gpt要怎麼丟出自定義的錯誤訊息// checkB2 erase
template<typename T>
void DynamicArray<T>::Erase(size_t pos){
    std::string errorMsg = "Erase(pos): ";
    errorMsg += std::to_string(pos);
    errorMsg += " >= ";
    errorMsg += std::to_string(size_);
    if (pos >= size_){
        throw out_of_range(errorMsg);
    }
    else if (size_ != 0){
        for (size_t i = pos; i < size_-1; i++){ // size=3, pos=1
            operator[](i) = move(elems_[i+1]);
        }
        Resize(Size()-1);
    }
}
// void Swap(DynamicArray<T>& other);
template<typename T>
void DynamicArray<T>::Swap(DynamicArray<T>& other){
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
    std::swap(elems_, other.elems_);
}

// void Assign(size_t count, const T& val);
template<typename T>
void DynamicArray<T>::Assign(size_t count, const T& val) {
    Resize(count);
    if (count != 0){
        for (size_t i = 0; i < count; i++){
            operator[](i) = val;
        }
    }
}

// operator[](Size()-1) = std::move(val);