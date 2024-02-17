# include <iostream>
using namespace std;

#include <initializer_list>
#include <iostream>
#include <random>
#include <cassert>

// T 為支援預設建構、複製建構、複製賦值的型態
template<typename T, size_t kMaximumSize = 100>
class BoundedSizeDynamicArray {
public:
    // constructs the bounded size dynamic array
    BoundedSizeDynamicArray() = default;
    BoundedSizeDynamicArray(std::initializer_list<T> l);

    // access specified element
    T& operator[](size_t pos);
    const T& operator[](size_t pos) const;

    // TODO: access the first element
    T& Front();
    [[nodiscard]] const T& Front() const;

    // TODO: access the last element
    T& Back();
    [[nodiscard]] const T& Back() const;

    // changes the number of elements stored
    void Resize(size_t n);

    // TODO: inserts an element to the beginning
    void PushFront(const T& val);
    void PushFront(T&& val);

    // TODO: removes the first element
    void PopFront();

    // adds an element to the end
    void PushBack(const T& val);
    void PushBack(T&& val);

    // removes the last element
    void PopBack();

    // TODO: inserts an element in the middle
    void PushMiddle(const T& val);
    void PushMiddle(T&& val);

    // TODO: removes an element in the middle
    void PopMiddle();

    // TODO: clears the contents
    void Clear() noexcept;

    // TODO: checks whether the container is empty
    [[nodiscard]] bool Empty() const noexcept;

    // returns the number of elements
    [[nodiscard]] size_t Size() const noexcept;

    // returns the maximum possible number of elements
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

void Test1(); // Sample1
void Test2(); // Front, Back
void Test3(); // PushFront, PopFront // WA
void Test4(); // PushMiddle, PopMiddle
void Test5(); // Clear, Empty
void Test6(); // All
void Test7(); // PushFront, PopFront // WA
void Test8(); // PushMiddle, PopMiddle
void Test9(); // All

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    void (*f[])() = {Test1, Test2, Test3, Test4, Test5, Test6, Test7, Test8, Test9};
    int id;
    std::cin >> id;
    f[id-1]();
}

void Test1() {
    // Resize
    {
        BoundedSizeDynamicArray<int> a;
        std::cout << a << std::endl;
        a.Resize(5);
        std::cout << a << std::endl;
        try {
            a.Resize(a.Capacity() + 1);
        } catch (const std::length_error& e) {
            std::cout << e.what() << std::endl;
        }
        std::cout << a << std::endl;
    }

    // 實作 Front() 方法回傳第一個元素 (element)
    // - 當陣列為空時為《未定義行為》
    // 實作 Back() 方法回傳最後一個元素 (element)
    // - 當陣列為空時為《未定義行為》
    {
        BoundedSizeDynamicArray<int> a{};
        const BoundedSizeDynamicArray<int> b = a;

        std::cout << "a.Front():  " << a.Front() << std::endl; // 印出 3
        std::cout << "a.Back():   " << a.Back() << std::endl;  // 印出 2

        std::cout << "b.Front():  " << b.Front() << std::endl; // 印出 3
        std::cout << "b.Back():   " << b.Back() << std::endl;  // 印出 2

        a.PushBack(10);
        std::cout << "a.Back():   " << a.Back() << std::endl;  // 印出 10

        BoundedSizeDynamicArray<BoundedSizeDynamicArray<int>> c;
        c.PushBack(b);
        std::cout << c << std::endl; // 印出 [[3, 7, 1, 5, 2]]

        c.PushBack(BoundedSizeDynamicArray<int>{7, 5, 8});
        std::cout << c << std::endl; // 印出 [[3, 7, 1, 5, 2], [7, 5, 8]]
    }

    // 實作 PushFront() 方法在陣列最前面插入一個新元素 (element)
    // - 當插入後造成陣列大小 (size) 超過可容許容量 (capacity) 時，丟出帶有訊息 "PushFront(val): Capacity is full." 的 std::out_of_range 例外，並保持插入前的狀態。
    // 實作 PopFront() 方法移除陣列最前面的元素 (element)
    // - 當陣列為空時為《未定義行為》
    {
        // BoundedSizeDynamicArray<int> a{3, 7, 1, 5, 2};
        BoundedSizeDynamicArray<int> a{3,8,9};
        std::cout << "testPushFront____" << endl;
        for (int i = 1; i <= 5; i++) {
            a.PushFront(i);
            std::cout << a << std::endl;
            // 依序印出 [1, 3, 7, 1, 5, 2]
            //         [2, 1, 3, 7, 1, 5, 2]
            //         [3, 2, 1, 3, 7, 1, 5, 2]
            //         [4, 3, 2, 1, 3, 7, 1, 5, 2]
            //         [5, 4, 3, 2, 1, 3, 7, 1, 5, 2]
        }
        std::cout << "testPopFront____" << endl;
        a = {3,8,9};
        // std::cout << a << std::endl;
        for (int i = 1; i <= 5; i++) {
            a.PopFront();
            std::cout << a << std::endl;
            // 依序印出 [4, 3, 2, 1, 3, 7, 1, 5, 2]
            //         [3, 2, 1, 3, 7, 1, 5, 2]
            //         [2, 1, 3, 7, 1, 5, 2]
            //         [1, 3, 7, 1, 5, 2]
            //         [3, 7, 1, 5, 2]
        }

        BoundedSizeDynamicArray<BoundedSizeDynamicArray<int>> c;
        std::cout << "test____" << endl;
        c.PushFront({});
        std::cout << c << std:: endl; // 印出 [[3, 7]]
        c.PushFront({4, 9, 6});
        std::cout << c << std::endl;  // 印出 [[4, 9, 6], [3, 7]]

        BoundedSizeDynamicArray<int, 3> d{0, 1, 2};
        std::cout << d << std::endl;
        try {
            d.PushFront(3);
        } catch (const std::out_of_range& e) {
            std::cout << e.what() << std::endl;
        }
        std::cout << d << std::endl;
    }

    // 實作 PushMiddle() 方法在陣列中間插入一個新元素 (element)
    // - 若陣列為空，則插入在第一個位置
    // - 否則，若陣列長度為奇數 $2N-1$，則插入在從第一個開始數的第 $N$ 個元素後。
    // - 否則，若陣列長度為偶數 $2N$，則插入在從第一個開始數的第 $N$ 個元素後。
    // - 當插入後造成陣列大小 (size) 超過可容許容量 (capacity) 時，丟出帶有訊息 "PushMiddle(val): Capacity is full." 的 std::out_of_range 例外，並保持插入前的狀態。
    // 實作 PopMiddle() 方法移除陣列中間的元素 (element)
    // - 當陣列為空時為《未定義行為》
    // - 否則，若陣列長度為奇數 $2N-1$，則移除從第一個開始數的第 $N$ 個元素。
    // - 否則，若陣列長度為偶數 $2N$，則移除從第一個開始數的第 $N+1$ 個元素。
    {
        BoundedSizeDynamicArray<int> a{};
        //std::cout << "error______" << endl;
        for (int i = 1; i <= 5; i++) {
            a.PushMiddle(i);
            std::cout << a << std::endl;
            // 依序印出 [3, 7, 1, 1, 5, 2]
            //         [3, 7, 1, 2, 1, 5, 2]
            //         [3, 7, 1, 2, 3, 1, 5, 2]
            //         [3, 7, 1, 2, 4, 3, 1, 5, 2]
            //         [3, 7, 1, 2, 4, 5, 3, 1, 5, 2]

        }
        // std::cout << "error______" << endl;

        for (int i = 1; i <= 5; i++) {
            a.PopMiddle();
            std::cout << a << std::endl;
            // 依序印出 [3, 7, 1, 2, 4, 3, 1, 5, 2]
            //         [3, 7, 1, 2, 3, 1, 5, 2]
            //         [3, 7, 1, 2, 1, 5, 2]
            //         [3, 7, 1, 1, 5, 2]
            //         [3, 7, 1, 5, 2]
        }

        BoundedSizeDynamicArray<int, 3> d{0, 1, 2};
        std::cout << d << std::endl;
        try {
            d.PushMiddle(3);
        } catch (const std::out_of_range& e) {
            std::cout << e.what() << std::endl;
        }
        std::cout << d << std::endl;
    }

    // 實作 Clear() 方法以移除陣列中所有元素 (element)，讓陣列為空
    // 實作 Empty() 方法回傳陣列是否為空
    {
        BoundedSizeDynamicArray<int> a{};
        std::cout << std::boolalpha << "a.Empty():  " << a.Empty() << std::endl; // 印出 false

        const BoundedSizeDynamicArray<int> b = a;
        std::cout << std::boolalpha << "b.Empty():  " << b.Empty() << std::endl; // 印出 false

        BoundedSizeDynamicArray<int> c;
        std::cout << std::boolalpha << "c.Empty():  " << c.Empty() << std::endl; // 印出 true

        a.Clear();
        std::cout << std::boolalpha << "a.Empty():  " << a.Empty() << std::endl; // 印出 true
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

// // TODO: access the first element
// T& Front();
// [[nodiscard]] const T& Front() const;
template<typename T, size_t kMaxiumSize>
T& BoundedSizeDynamicArray<T, kMaxiumSize>::Front(){
    return elems_[0];
}
template<typename T, size_t kMaxiumSize>
const T& BoundedSizeDynamicArray<T, kMaxiumSize>::Front() const{
    return elems_[0];
}
// // TODO: access the last element
// T& Back();
// [[nodiscard]] const T& Back() const;
template<typename T, size_t kMaxiumSize>
T& BoundedSizeDynamicArray<T, kMaxiumSize>::Back(){
    return elems_[size_-1];
}
template<typename T, size_t kMaxiumSize>
const T& BoundedSizeDynamicArray<T, kMaxiumSize>::Back() const{
    return elems_[size_-1];
}


// Push Front
template<typename T, size_t kMaximumSize>
void BoundedSizeDynamicArray<T, kMaximumSize>::PushFront(const T& val) {
    if (size_ == kMaximumSize) {
        throw std::out_of_range("PushFront(val): Capacity is full.");
    }
    ++size_;
    for (size_t i = size_-1; i > 0; i--){
        elems_[i] = elems_[i-1];
    }
    elems_[0] = val;
}
template<typename T, size_t kMaximumSize>
void BoundedSizeDynamicArray<T, kMaximumSize>::PushFront(T&& val) {
    if (size_ == kMaximumSize) {
        throw std::out_of_range("PushFront(val): Capacity is full.");
    }
    ++size_;
    for (size_t i = size_-1; i > 0; i--){
        elems_[i] = std::move(elems_[i-1]);
    }
    elems_[0] = val;
}
// // TODO: removes the first element
// void PopFront();
template <typename T, size_t kMaxiumSize>
void BoundedSizeDynamicArray<T, kMaxiumSize>::PopFront(){
    if (size_ != 0){
        for (size_t i = 0; i < size_-1; ++i){
            elems_[i] = std::move(elems_[i+1]);
        }
        --size_;
    }
}

// // TODO: inserts an element in the middle
// void PushMiddle(const T& val);
// void PushMiddle(T&& val);
template <typename T, size_t kMaxiumSize>
void BoundedSizeDynamicArray<T, kMaxiumSize>::PushMiddle(const T& val){
    if (size_ == kMaxiumSize){throw std::out_of_range("PushMiddle(val): Capacity is full.");}
    size_t targetPos = 0;
    if (size_ == 0){
        elems_[0] = val;
    }
    else { // 偶數
        if (size_ % 2 == 0){targetPos = size_/2;}
        else{ targetPos = (size_/2) +1;// 5 -> 2*3-1 -> 4 pos3
        }
    }
    for (size_t i = size_; i > targetPos; i--){
        elems_[i] = std::move(elems_[i-1]);
    }
    ++size_;
    elems_[targetPos] = val;
}

template <typename T, size_t kMaxiumSize>
void BoundedSizeDynamicArray<T, kMaxiumSize>::PushMiddle(T&& val){
    if (size_ == kMaxiumSize){throw std::out_of_range("PushMiddle(val): Capacity is full.");}
    size_t targetPos = 0;
    if (size_ == 0){
        elems_[0] = val;
    }
    else { // 偶數
        if (size_ % 2 == 0){targetPos = size_/2;}
        else{ targetPos = (size_/2) +1;}// 5 -> 2*3-1 -> 4 pos3
    }
    for (size_t i = size_; i > targetPos; i--){
        elems_[i] = std::move(elems_[i-1]);
    }
    ++size_;
    elems_[targetPos] = val;
}
// // TODO: removes an element in the middle
// void PopMiddle();
template <typename T, size_t kMaxiumSize>
void BoundedSizeDynamicArray<T, kMaxiumSize>::PopMiddle(){
    size_t targetPos = 0;
    if (size_ == 0){
        throw std::out_of_range("PushFront(val): Capacity is full.");
    }
    else { // 偶數
        targetPos = (size_/2); // 5
    }

    // cout << size_ << " " << targetPos;
    for (size_t i = targetPos; i < size_-1; i++){
        elems_[i] = std::move(elems_[i+1]);
    }
    --size_;
}
// // TODO: clears the contents
// void Clear() noexcept;
template <typename T, size_t kMaxiumSize>
void BoundedSizeDynamicArray<T, kMaxiumSize>::Clear() noexcept{
    size_ = 0;
}
// // TODO: checks whether the container is empty
// [[nodiscard]] bool Empty() const noexcept;
template <typename T, size_t kMaxiumSize>
bool BoundedSizeDynamicArray<T, kMaxiumSize>::Empty() const noexcept{
    return (size_ == 0);
}

