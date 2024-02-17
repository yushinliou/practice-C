#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <random>
using namespace std; 
struct IOrderedNumberInputStream {
    virtual unsigned long long Get() = 0;
    virtual bool IsEndOfStream() const = 0;
    virtual ~IOrderedNumberInputStream() {}
};

class OrderedRandomNumberSequence : public IOrderedNumberInputStream {
public:
    OrderedRandomNumberSequence(size_t s, unsigned seed) : size_(s), curr_index_{0}, random_generator_{seed}, last_value_{0} {}
    OrderedRandomNumberSequence(const OrderedRandomNumberSequence&) = delete;
    OrderedRandomNumberSequence& operator=(const OrderedRandomNumberSequence&) = delete;
    unsigned long long Get() {
        ++curr_index_;
        last_value_ = last_value_ + random_generator_() % 100;
        // cout << "{" << last_value_ << "}";
        return last_value_;
    }
    bool IsEndOfStream() const {
        return curr_index_ >= size_;
    }
private:
    size_t size_;
    size_t curr_index_;
    std::mt19937 random_generator_;
    unsigned long long last_value_;
};

// [YOUR CODE WILL BE PLACED HERE]
// [YOUR CODE WILL BE PLACED HERE]
#include <queue>
using namespace std; 

class CompositeOrderedNumberInputStream : public IOrderedNumberInputStream {
public:
    CompositeOrderedNumberInputStream(const std::vector<IOrderedNumberInputStream*>& inputs) 
        : inputs_(inputs), min_heap_{}, result_{0} {
        // 走遍所有的input
        for (auto input : inputs_) {
            // 當input還沒有取到盡頭
            if (!input->IsEndOfStream()) {
                // min_heap是構造元素是std::pair<unsigned long long, IOrderedNumberInputStream*>
                // emplace的功能是構造min_heap的構造元素，input的值（input->Get）, input到min heap再加入到min_heap當中
                min_heap_.emplace(input->Get(), input);
            }
        }
        // cout << endl;
    }
    unsigned long long Get() override {
        if (min_heap_.empty()) {
            return result_;
        }
        // min_pair是min_heap最頂端的pair 即最小數字的pair
        auto min_pair = min_heap_.top();
        // 把最頂端的元素拿掉
        min_heap_.pop();
        // result是min_heap最頂端的pair的數字，也就是當前輸入流當中最小的數字
        result_ = min_pair.first;

        // 看這個最頂端的pair是不是輸入流當中的最後一個元素
        auto input = min_pair.second;
        if (!input->IsEndOfStream()) {
            min_heap_.emplace(input->Get(), input);
        }
        return result_;
    }
    bool IsEndOfStream() const override {
        for (auto input : inputs_) {
            if (!input->IsEndOfStream()) {
                return false;
            }
        }
        if (!min_heap_.empty()){
            return false;
        }
        return true;
    }
private:
    std::vector<IOrderedNumberInputStream*> inputs_;
    std::priority_queue<std::pair<unsigned long long, IOrderedNumberInputStream*>,
                        std::vector<std::pair<unsigned long long, IOrderedNumberInputStream*>>,
                        std::greater<std::pair<unsigned long long, IOrderedNumberInputStream*>>> min_heap_;
    unsigned long long result_;
};

// [My CODE END IN HERE]

std::ostream& operator<<(std::ostream&, IOrderedNumberInputStream&);

void Test1(); // Sample1
void Test2(); // All
void Test3(); // All
void Test4(); // All
void Test5(); // All
void Test6(); // All
void Test7(); // All

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int id;
    std::cin >> id;
    void (*f[])() = { Test1, Test2, Test3, Test4, Test5, Test6, Test7};
    f[id-1]();
}

std::ostream& operator<<(std::ostream& os, IOrderedNumberInputStream& input) {
    bool isFirst = true;
    os << '[';
    while (!input.IsEndOfStream()) {
        if (!isFirst) {
            os << ", ";
        } else {
            isFirst = false;
        }
        os << input.Get();
    }
    return os << ']';
}

namespace Feis {}

void Test1() {
    // OrderedRandomNumberSequence
    {
        OrderedRandomNumberSequence a1(10, 10), b1(10, 20);
        std::cout << "01) " << a1 << std::endl;
        std::cout << "02) " << b1 << std::endl;
    }

    // CompositeOrderedNumberInputStream (1)
    {
        OrderedRandomNumberSequence a1(10, 10), b1(10, 20);
        CompositeOrderedNumberInputStream o1({&a1, &b1});
        std::cout << "03) " << o1 << std::endl;
    }

    // CompositeOrderedNumberInputStream (2)
    {
        OrderedRandomNumberSequence a1(10, 10), b1(10, 20), a2(20, 30), b2(0, 40), c2(10, 50), d1(5, 60);
        // cout << "a1 " << a1 << endl;
        // cout << "b1 " << b1 << endl;
        // cout << "a2 " << a2 << endl;
        // cout << "b2 " << b2 << endl;
        // cout << "c2 " << c2 << endl;
        // cout << "d1 " << d1 << endl;
        CompositeOrderedNumberInputStream o1({&a1, &b1});
        CompositeOrderedNumberInputStream o2({&a2, &b2, &c2});
        CompositeOrderedNumberInputStream o3({&d1});
        CompositeOrderedNumberInputStream o4({&o1, &o2, &o3});
        // cout << "___________04___________" << endl; 
        std::cout << "04) " << o4 << std::endl;
    }
}

void Test2() {}
void Test3() {}
void Test4() {}
void Test5() {}
void Test6() {}
void Test7() {}