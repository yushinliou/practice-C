#include <initializer_list>
#include <iostream>
#include <random>
#include <cassert>

// T 為支援預設建構、複製建構、複製賦值與相等比較 (==) 的型態
template<typename T, size_t kMaximumSize = 100>
class BoundedSizeDynamicArray {
public:
    BoundedSizeDynamicArray() = default;
    BoundedSizeDynamicArray(std::initializer_list<T> l);

    T& operator[](size_t pos);
    const T& operator[](size_t pos) const;

    bool operator==(const BoundedSizeDynamicArray<T, kMaximumSize>& other) noexcept;
    bool operator!=(const BoundedSizeDynamicArray<T, kMaximumSize>& other) noexcept;

    void Resize(size_t n);

    void PushBack(const T& val);
    void PushBack(T&& val);

    void PopBack();

    void Fill(const T& val);
    void Erase(size_t pos);
    void Insert(size_t pos, const T& val);
    void Insert(size_t pos, T&& val);
    void Remove(const T& val);
    void Swap(BoundedSizeDynamicArray<T, kMaximumSize>& other) noexcept;

    [[nodiscard]] size_t Size() const noexcept;
    [[nodiscard]] size_t Capacity() const noexcept;

private:
    size_t size_ = 0;
    T elems_[kMaximumSize];
};

template<typename T, size_t kMaximumSize>
std::ostream& operator<<(std::ostream& os, const BoundedSizeDynamicArray<T, kMaximumSize>& v) {
    os << '[';
    if (v.Size() > 0) {
        os << v[0];
        for (size_t i = 1; i < v.Size(); i++) {
            os << ", " << v[i];
        }
    }
    return os << ']';
}

void Test1(); // sample1
void Test2(); // Insert, Erase
void Test3(); // operator==, operator!=
void Test4(); // Remove, Fill //
void Test5(); // Swap
void Test6(); // All //
void Test7(); // Insert, Erase
void Test8(); // Remove, Fill // 
void Test9(); // Swap
void Test10(); // All //

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    void (*f[])() = {
            Test1, Test2, Test3, Test4, Test5,
            Test6, Test7, Test8, Test9, Test10 };
    int id;
    std::cin >> id;
    f[id-1]();
}


void Test1() {
    // 實作 Erase(pos) 方法將陣列中第 pos 號元素移除
    // - pos 由 0 開始數
    // - 若 pos 大於陣列長度，則移除最後一個元素
    // - 若陣列為空，則丟出帶有 "Erase(pos): Array is empty." 訊息的 std::out_of_range 例外。
    // - 若丟出例外，陣列需保持丟出例外之前的狀態
    // 實作 Insert(pos, val) 方法插入值為 val 的新元素在第 pos 號的位置
    // - pos 由 0 開始數
    // - 若 pos 大於陣列長度，則插入在最後
    // - 若容量 (Capacity) 已滿，則丟出帶有 "Insert(pos, val): Capacity is full." 訊息的 std::out_of_range 例外
    // - 若丟出例外，陣列需保持丟出例外之前的狀態
    {
        BoundedSizeDynamicArray<int, 8> a = {3, 7, 2, 1, 5};

        a.Insert(0, 9);
        std::cout << a << std::endl; // 印出 [9, 3, 7, 2, 1, 5]

        a.Insert(6, 7);
        std::cout << a << std::endl; // 印出 [9, 3, 7, 2, 1, 5, 7]

        a.Insert(3, -5);
        std::cout << a << std::endl; // 印出 [9, 3, 7, -5, 2, 1, 5, 7]

        try {
            a.Insert(1, 9);
        } catch (const std::out_of_range& e) {
            std::cout << e.what() << std::endl; // 印出 "Insert(pos, val): Capacity is full."
        }

        a.Erase(0);
        std::cout << a << std::endl; // 印出 [3, 7, -5, 2, 1, 5, 7]

        a.Erase(6);
        std::cout << a << std::endl; // 印出 [3, 7, -5, 2, 1, 5]

        a.Erase(3);
        std::cout << a << std::endl; // 印出 [3, 7, -5, 1, 5]

        a.Resize(0);

        try {
            a.Erase(0);
        } catch (const std::out_of_range& e) {
            std::cout << e.what() << std::endl; // 印出 "Erase(pos): Array is empty."
        }

        a.Insert(10, 9);
        std::cout << a << std::endl; // 印出 [9]

        a.Erase(10);
        std::cout << a << std::endl; // 印出 []

        BoundedSizeDynamicArray<BoundedSizeDynamicArray<int>> b = {{1, 2}};
        std::cout << b << std::endl; // 印出 [[1, 2]]

        b.Insert(0, {3, 4});
        std::cout << b << std::endl; // 印出 [[3, 4], [1, 2]]

        b.Erase(0);
        std::cout << b << std::endl; // 印出 [[1, 2]]
    }

    // 實作 operator==(other) 運算，比較兩陣列長度與內容值是否完全相等 (==)
    // 實作 operator!=(other) 運算，比較兩陣列長度或內容值是否有任何不相等 (!=)
    {
        BoundedSizeDynamicArray<int> a = {3, 7, 2, 1, 5};
        BoundedSizeDynamicArray<int> b = {3, 7, 2, 1, 5};
        BoundedSizeDynamicArray<int> c = {3, 7, 2, 1};
        BoundedSizeDynamicArray<int> d = {3, 7, 9, 1};


        std::cout << std::boolalpha << (a == a) << std::endl; // 印出 true
        std::cout << std::boolalpha << (a == b) << std::endl; // 印出 true
        std::cout << std::boolalpha << (a == c) << std::endl; // 印出 false
        std::cout << std::boolalpha << (c == d) << std::endl; // 印出 false
    }

    // 實作 Fill(val) 方法將陣列中所有元素都賦值為 val
    // 實作 Remove(val) 方法，移除陣列中所有值相等於 (==) val 的元素
    {
        BoundedSizeDynamicArray<int> a = {};

        a.Remove(7);
        std::cout << a << std::endl; // 印出 [3, 2, 1, 5]

        a.Fill(10);
        std::cout << a << std::endl; // 印出 [10, 10, 10, 10]

        BoundedSizeDynamicArray<BoundedSizeDynamicArray<int>> b;
        b.Resize(5);
        std::cout << b << std::endl; // 印出 [[], [], [], [], []]

        b.Fill({1, 2});
        std::cout << b << std::endl; // 印出 [[1, 2], [1, 2], [1, 2], [1, 2], [1, 2]]

        b.Remove({1, 2});
        std::cout << b << std::endl; // 印出 []
    }

    // 實作 Swap(other) 方法，與 other 陣列交換
    {
        BoundedSizeDynamicArray<int> a = {3, 7, 2, 1, 5};
        BoundedSizeDynamicArray<int> c = {3, 7, 9};

        std::cout << a << std::endl; // 印出 [3, 7, 2, 1, 5]
        std::cout << c << std::endl; // 印出 [3, 7, 9]

        a.Swap(c);
        std::cout << a << std::endl; // 印出 [3, 7, 9]
        std::cout << c << std::endl; // 印出 [3, 7, 2, 1, 5]

        a.Swap(c);
        std::cout << a << std::endl; // 印出 [3, 7, 2, 1, 5]
        std::cout << c << std::endl; // 印出 [3, 7, 9]
    }
}

void Test2() { /* HIDDEN */ }
void Test3() { /* HIDDEN */ }
void Test4() { /* HIDDEN */ }
void Test5() { /* HIDDEN */ }
void Test6() { /* HIDDEN */ }
void Test7() { /* HIDDEN */ }
void Test8() { /* HIDDEN */ }
void Test9() { /* HIDDEN */ }
void Test10() { /* HIDDEN */ }

template<typename T, size_t kMaximumSize>
BoundedSizeDynamicArray<T, kMaximumSize>::BoundedSizeDynamicArray(std::initializer_list<T> l) {
    assert(l.size() <= kMaximumSize);
    size_ = 0;
    for (const T& e : l) {
        elems_[size_] = e;
        ++size_;
    }
}

template<typename T, size_t kMaximumSize>
T& BoundedSizeDynamicArray<T, kMaximumSize>::operator[](size_t pos) {
    assert(pos < size_);
    return elems_[pos];
}

template<typename T, size_t kMaximumSize>
const T& BoundedSizeDynamicArray<T, kMaximumSize>::operator[](size_t pos) const {
    assert(pos < size_);
    return elems_[pos];
}

template<typename T, size_t kMaximumSize>
void BoundedSizeDynamicArray<T, kMaximumSize>::Resize(size_t n) {
    if (n > kMaximumSize) {
        throw std::length_error("Resize(n): n is too large.");
    }
    for (size_t i = size_; i < n; ++i) {
        elems_[i] = T{};  // Zero out the newly added element
    }
    size_ = n;
}

template<typename T, size_t kMaximumSize>
void BoundedSizeDynamicArray<T, kMaximumSize>::PushBack(const T& val) {
    if (size_ == kMaximumSize) {
        throw std::out_of_range("PushBack(val): Capacity is full.");
    }
    ++size_;
    elems_[size_-1] = val;
}

template<typename T, size_t kMaximumSize>
void BoundedSizeDynamicArray<T, kMaximumSize>::PushBack(T&& val) {
    if (size_ == kMaximumSize) {
        throw std::out_of_range("PushBack(val): Capacity is full.");
    }
    ++size_;
    elems_[size_-1] = std::move(val);
}

template<typename T, size_t kMaximumSize>
size_t BoundedSizeDynamicArray<T, kMaximumSize>::Size() const noexcept {
    return size_;
}

template<typename T, size_t kMaximumSize>
size_t BoundedSizeDynamicArray<T, kMaximumSize>::Capacity() const noexcept {
    return kMaximumSize;
}

template<typename T, size_t kMaximumSize>
void BoundedSizeDynamicArray<T, kMaximumSize>::PopBack() {
    assert(size_ > 0);
    --size_;
}

// [YOUR CODE WILL BE PLACED HERE]

// [YOUR CODE WILL BE PLACED HERE]
// BoundedSizeDynamicArray() = default;
// BoundedSizeDynamicArray(std::initializer_list<T> l);
// T& operator[](size_t pos);
// const T& operator[](size_t pos) const;

// bool operator==(const BoundedSizeDynamicArray<T, kMaximumSize>& other) noexcept;
// bool operator!=(const BoundedSizeDynamicArray<T, kMaximumSize>& other) noexcept;
using std::swap;

template<typename T, size_t kMaximumSize>
bool BoundedSizeDynamicArray<T, kMaximumSize>::operator==(const BoundedSizeDynamicArray<T, kMaximumSize>& other) noexcept{
    if (this->size_ != other.Size()){return false;}
    else if ((size_ == 0) & (other.Size() == 0)){return true;}
    else{
        for (size_t i = 0; i < size_; i++){
            if (elems_[i] != other[i]){ return false;}
        }        
    }
    return true;
}
template<typename T, size_t kMaximumSize>
bool BoundedSizeDynamicArray<T, kMaximumSize>::operator!=(const BoundedSizeDynamicArray<T, kMaximumSize>& other) noexcept{
    if (*this == other){return false;}
    else{return true;}
}

// void Insert(size_t pos, const T& val);
// void Insert(size_t pos, T&& val);
template<typename T, size_t kMaximumSize>
void BoundedSizeDynamicArray<T, kMaximumSize>::Insert(size_t pos, const T& val){
    //std::cout << "pos" << pos << " " << "size" << size_-1 << "(pos > size_-1)" << (pos > size_-1);
    if (size_ == kMaximumSize){throw std::out_of_range("Insert(pos, val): Capacity is full.");}
    else if (size_ == 0) {elems_[0]=val;}
    else if ((pos > size_-1)){elems_[size_]=val;}
    else {
        for (size_t i = size_; i > pos; i--){
            elems_[i] = elems_[i-1];
        }
        elems_[pos] = val;
    }
    size_ ++;
}
template<typename T, size_t kMaximumSize>
void BoundedSizeDynamicArray<T, kMaximumSize>::Insert(size_t pos, T&& val){
    //std::cout << "pos" << pos << " " << "size" << size_-1 << "(pos > size_-1)" << (pos > size_-1);
    if (size_ == kMaximumSize){throw std::out_of_range("Insert(pos, val): Capacity is full.");}
    else if (size_ == 0) {elems_[0]=val;}
    else if (pos > size_-1){elems_[size_]=val;}
    else {
        for (size_t i = size_; i > pos; i--){
            elems_[i] = elems_[i-1];
        }
        elems_[pos] = val;
    }
    size_ ++;
}
// void Erase(size_t pos);
template<typename T, size_t kMaximumSize>
void BoundedSizeDynamicArray<T, kMaximumSize>::Erase(size_t pos){
    if (size_ == 0){throw std::out_of_range("Erase(pos): Array is empty.");}
    else if (pos > size_-1){size_--;}
    else {
        for (size_t i = pos; i < size_; i++){
            elems_[i] = elems_[i+1];
        }
        size_ --;
    }
    
}
// void Fill(const T& val);
template<typename T, size_t kMaximumSize>
void BoundedSizeDynamicArray<T, kMaximumSize>::Fill(const T& val){
    if (size_ != 0){
        for (size_t i = 0; i < size_; i++){
            elems_[i] = val;
        }        
    }
}
// void Remove(const T& val);
template<typename T, size_t kMaximumSize>
void BoundedSizeDynamicArray<T, kMaximumSize>::Remove(const T& val){
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
// chatgpt詢問實作swap的函式
// void Swap(BoundedSizeDynamicArray<T, kMaximumSize>& other) noexcept
template<typename T, size_t kMaximumSize>
void BoundedSizeDynamicArray<T, kMaximumSize>::Swap(BoundedSizeDynamicArray<T, kMaximumSize>& other) noexcept{
    if (size_ == 0)
    if (size_ > other.size_){
        size_t large = size_;
    }
    else{size_t large = other.size_;}
    swap(size_, other.size_);
    for (size_t i = 0; i < kMaximumSize; i++){
        swap(elems_[i], other.elems_[i]);
    }
}


// void Resize(size_t n);
// void PushBack(const T& val);
// void PushBack(T&& val);

// void PopBack();








// [[nodiscard]] size_t Size() const noexcept;
// [[nodiscard]] size_t Capacity() const noexcept;