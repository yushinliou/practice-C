#include <utility>
#include <vector>
#include <iostream>
#include <initializer_list>
#include <algorithm>
#include <cassert>    // For Test
#include <random>     // For Test
#include <functional> // For Test

// 模板參數 T 的合法型態會支援：
// - 值初始化：歸零
// - 複製語意：複製建構與賦值
// - 同型態間的比較運算：==, !=, >, >=, <, <=
// 符合以上要求的可能型態有：int, double, std::string 等等
template<typename T>
class Multiset {
    using iterator = typename std::vector<T>::iterator;
    using const_iterator = typename std::vector<T>::const_iterator;
public:
    Multiset() = default;
    Multiset(const Multiset&) = default;
    Multiset(std::initializer_list<T> l);

    void Add(const T&);
    void Remove(const T&);

    [[nodiscard]] bool Empty() const noexcept;
    [[nodiscard]] size_t Size() const noexcept;

    void Swap(Multiset<T>& other);
    void Clear();

    [[nodiscard]] bool Contains(const T&) const;
    size_t Count(const T&) const;

    [[nodiscard]] iterator begin() {
        return repr_.begin();
    }
    [[nodiscard]] iterator end() {
        return repr_.end();
    }
    [[nodiscard]] const_iterator begin() const {
        return repr_.begin();
    }
    [[nodiscard]] const_iterator end() const {
        return repr_.end();
    }

private:
    std::vector<T> repr_;
};

template<typename T>
std::ostream& operator<<(std::ostream& os, const Multiset<T>& s) {
    std::vector<T> output(s.begin(), s.end());
    std::sort(std::begin(output), std::end(output));
    os << '{';
    if (output.size() > 0) {
        os << output[0];
        for (size_t i = 1; i < output.size(); ++i) {
            os << ", " << output[i];
        }
    }
    os << '}';
    return os;
}

void Test1(); // Sample1
void Test2(); // Constructor
void Test3(); // Constructor, Add, Remove
void Test4(); // Constructor, Add, Remove, Empty, Size
void Test5(); // Constructor, Add, Remove, Swap, Clear
void Test6(); // Constructor, Add, Remove, Empty, Size, Contains, Count
void Test7(); // All

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int id;
    std::cin >> id;
    void (*f[])() = { Test1, Test2, Test3, Test4, Test5, Test6, Test7 };
    f[id-1]();
}

namespace Feis { /* HIDDEN */ }

void Test1() {
    // 實作建構子，可以用 {...} 初始化
    {
        Multiset<int> a = {3, 1, 7, 2, 3, 4, 2};
        std::cout << "01) " << a << std::endl;

        // 依序印出:
        // 01) {1, 2, 2, 3, 3, 4, 7}
    }

    // 實作 Add(val) 方法，新增值為 val 的元素到多重集內
    // 實作 Remove(val) 方法，從多重集內移除一個值與 val 相等 (==) 的元素
    // - 如果沒有任何元素的值與 val 相等 (==)，則不會發生任何效果
    {
        Multiset<int> a = {3, 1, 7};

        a.Add(5);
        std::cout << "02) " << a << std::endl;

        a.Add(3);
        std::cout << "03) " << a << std::endl;

        a.Remove(3);
        std::cout << "04) " << a << std::endl;

        a.Remove(5);
        std::cout << "05) " << a << std::endl;

        a.Remove(6);
        std::cout << "06) " << a << std::endl;

        // 依序印出:
        // 02) {1, 3, 5, 7}
        // 03) {1, 3, 3, 5, 7}
        // 04) {1, 3, 5, 7}
        // 05) {1, 3, 7}
        // 06) {1, 3, 7}
    }

    // 實作 Empty() 方法，回傳該多重集是否為空
    // 實作 Size() 方法，回傳該多重集內有多少元素
    {
        Multiset<int> a = {3, 1, 7, 2, 3, 4, 2};
        Multiset<std::string> b;
        std::cout << "07) " << std::boolalpha << a.Empty() << std::endl;
        std::cout << "08) " << a.Size() << std::endl;
        std::cout << "09) " << b.Size() << std::endl;
        std::cout << "10) " << std::boolalpha << b.Empty() << std::endl;

        // 依序印出:
        // 07) false
        // 08) 7
        // 09) 0
        // 10) true
    }

    // 實作 Swap(other) 方法，與集合 other 交換內容
    // 實作 Clear() 方法，清除內容，讓集合為空
    {
        Multiset<int> a = {3, 9, 5};
        Multiset<int> b = {3, 9, 1, 7, 5, 3};

        std::cout << "11) " << a << std::endl;
        std::cout << "12) " << b << std::endl;

        a.Swap(b);
        std::cout << "13) " << a << std::endl;
        std::cout << "14) " << b << std::endl;

        a.Clear();
        std::cout << "15) " << a << std::endl;

        // 依序印出:
        // 11) {3, 5, 9}
        // 12) {1, 3, 3, 5, 7, 9}
        // 13) {1, 3, 3, 5, 7, 9}
        // 14) {3, 5, 9}
        // 15) {}
    }

    // 實作 Contains(val) 方法，回傳該多重集內是否有元素值與 val 相等 (==)
    // 實作 Count(val) 方法，回傳該多重集內有多少個元素與 val 的值相等 (==)
    {
        Multiset<int> a = {3, 1, 7, 2, 3, 4, 2};

        std::cout << "16) " << std::boolalpha << a.Contains(3) << std::endl;
        std::cout << "17) " << a.Count(3) << std::endl;

        std::cout << "18) " << std::boolalpha << a.Contains(5) << std::endl;
        std::cout << "19) " << a.Count(5) << std::endl;

        // 16) true
        // 17) 2
        // 18) false
        // 19)
    }
}

void Test2() { /* HIDDEN */ }
void Test3() { /* HIDDEN */ }
void Test4() { /* HIDDEN */ }
void Test5() { /* HIDDEN */ }
void Test6() { /* HIDDEN */ }
void Test7() { /* HIDDEN */ }

// [YOUR CODE WILL BE PLACED HERE]

// Multiset() = default;
// Multiset(const Multiset&) = default;
// Multiset(std::initializer_list<T> l);

template<typename T>
Multiset<T>::Multiset(std::initializer_list<T> l) : repr_(l) {
    std::sort(repr_.begin(), repr_.end());
}

// void Add(const T&);
// void Remove(const T&);
template<typename T>
void Multiset<T>::Add(const T& value) {
    auto it = std::upper_bound(repr_.begin(), repr_.end(), value);
    repr_.insert(it, value);
}

template<typename T>
void Multiset<T>::Remove(const T& value) {
    auto it = std::find(repr_.begin(), repr_.end(), value);
    if (it != repr_.end()) {
        repr_.erase(it);
    }
}
// 以下是可以移除掉所有value的做法
// auto range = std::equal_range(repr_.begin(), repr_.end(), value);
//     repr_.erase(range.first, range.second);

template<typename T>
bool Multiset<T>::Empty() const noexcept {
    return repr_.empty();
}

template<typename T>
size_t Multiset<T>::Size() const noexcept {
    return repr_.size();
}

template<typename T>
void Multiset<T>::Swap(Multiset<T>& other) {
    repr_.swap(other.repr_);
}

template<typename T>
void Multiset<T>::Clear() {
    repr_.clear();
}

template<typename T>
bool Multiset<T>::Contains(const T& value) const {
    return std::binary_search(repr_.begin(), repr_.end(), value);
}

template<typename T>
size_t Multiset<T>::Count(const T& value) const {
    auto range = std::equal_range(repr_.begin(), repr_.end(), value);
    return std::distance(range.first, range.second);
}

// [[nodiscard]] bool Empty() const noexcept;
// [[nodiscard]] size_t Size() const noexcept;

// void Swap(Multiset<T>& other);
// void Clear();

// [[nodiscard]] bool Contains(const T&) const;
// size_t Count(const T&) const;

// [[nodiscard]] iterator begin() {
//     return repr_.begin();
// }
// [[nodiscard]] iterator end() {
//     return repr_.end();
// }
// [[nodiscard]] const_iterator begin() const {
//     return repr_.begin();
// }
// [[nodiscard]] const_iterator end() const {
//     return repr_.end();
// }