#include <iostream>
#include <utility>
#include <vector>
#include <cassert>    // For Test
#include <random>     // For Test
#include <functional> // For Test

template<typename T>
struct IQueue {
    virtual ~IQueue() {}
    virtual bool Empty() const = 0;
    virtual void Enqueue(const T&) = 0;
    virtual T Dequeue() = 0;
    virtual const T& Peek() const = 0;
};

template<typename T>
struct ListNode {
    ListNode(T val) : val{std::move(val)}, next{nullptr} {}
    T val;
    ListNode* next;
};

template<typename T>
class LinkedQueue: public IQueue<T> {
    public:
        using ElemType = T;
        LinkedQueue();
        LinkedQueue(const LinkedQueue&);
        LinkedQueue& operator=(const LinkedQueue&);
        ~LinkedQueue();
        bool Empty() const;
        void Enqueue(const T&);
        T Dequeue();
        const T& Peek() const;
    private:
        ListNode<T>* node_;
};

template<typename T>
class ArrayQueue : public IQueue<T> {
    public:
        using ElemType = T;
        ArrayQueue();
        bool Empty() const;
        void Enqueue(const T&);
        T Dequeue();
        const T& Peek() const;
    private:
        std::vector<T> data_;
        int a_;
        int b_;
};

template<typename TQueue,
         typename = std::enable_if<
            std::is_base_of<
                IQueue<typename TQueue::ElemType>, TQueue>::value>>
std::ostream& operator<<(std::ostream& os, const TQueue& p) {
    TQueue q = p;
    bool isFirst = true;
    os << '[';
    while (!q.Empty()) {
        if (isFirst) {
            isFirst = false;
        } else {
            os << ", ";
        }
        os << q.Dequeue();
    }
    os << ']';
    return os;
}

void Test1(); // Sample1
void Test2(); // LinkedQueue
void Test3(); // LinkedQueue [Large Element]
void Test4(); // ArrayQueue
void Test5(); // ArrayQueue [Large Element]
void Test6(); // ArrayQueue and LinkedQueue

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int id;
    std::cin >> id;
    void (*f[])() = { Test1, Test2, Test3, Test4, Test5, Test6 };
    f[id-1]();
}

void Test1() {
    LinkedQueue<int> q1;
    std::cout << "01) " << q1 << std::endl;

    q1.Enqueue(3);
    std::cout << "02) " << q1 << std::endl;

    q1.Enqueue(5);
    std::cout << "03) " << q1 << std::endl;

    q1.Enqueue(7);
    std::cout << "04) " << q1 << std::endl;

    std::cout << "05) " << q1.Dequeue() << std::endl;

    std::cout << "06) " << q1.Peek() << std::endl;

    q1.Enqueue(9);
    std::cout << "07) " << q1 << std::endl;

    ArrayQueue<int> q2;
    std::cout << "08) " << q2 << std::endl;
    // std::cout << "________________" << std::endl;
    q2.Enqueue(3);
    std::cout << "09) " << q2 << std::endl;
    // std::cout << "________________" << std::endl;
    q2.Enqueue(5);
    std::cout << "10) " << q2 << std::endl;
    // std::cout << "________________" << std::endl;
    q2.Enqueue(7);
    std::cout << "11) " << q2 << std::endl;
    // std::cout << "________________" << std::endl;
    std::cout << "12) " << q2.Dequeue() << std::endl;
    // std::cout << "________________" << std::endl;
    std::cout << "13) " << q2.Peek() << std::endl;
    // std::cout << "________________" << std::endl;
    q2.Enqueue(9);
    std::cout << "14) " << q2 << std::endl;
}

namespace Feis {
}

void Test2() {
}
void Test3() {
}
void Test4() {
}
void Test5() {
}
void Test6() {
}

// [YOUR CODE WILL BE PLACED HERE]
using namespace std;
template<typename T>
LinkedQueue<T>::LinkedQueue() : node_{nullptr} {}

template<typename T>
LinkedQueue<T>::LinkedQueue(const LinkedQueue& rhs) {
    if (rhs.node_ == nullptr) {
        node_ = nullptr;
        return;
    }
    node_ = new ListNode<T>{rhs.node_->val};
    auto nodePtr = node_;
    auto rhsPtr = rhs.node_;
    while (rhsPtr->next != nullptr) {
        rhsPtr = rhsPtr->next;
        nodePtr->next = new ListNode<T>{rhsPtr->val};
        nodePtr = nodePtr->next;
    }
}

template<typename T>
LinkedQueue<T>& LinkedQueue<T>::operator=(const LinkedQueue& rhs) {
    if (this != &rhs) {
        auto tmp{rhs};
        std::swap(tmp.node_, node_);
    }
    return *this;
}



template<typename T>
LinkedQueue<T>::~LinkedQueue() {
    while (node_ != nullptr) {
        auto tmp = node_;
        node_ = node_->next;
        delete tmp;
    }
}

template<typename T>
bool LinkedQueue<T>::Empty() const {
    return node_ == nullptr;
}

template<typename T>
void LinkedQueue<T>::Enqueue(const T& val) {
    auto newNode = new ListNode<T>{val};
    if (node_ == nullptr) {
        node_ = newNode;
    } else {
        auto nodePtr = node_;
        while (nodePtr->next != nullptr) {
            nodePtr = nodePtr->next;
        }
        nodePtr->next = newNode;
    }
}

template<typename T>
T LinkedQueue<T>::Dequeue() {
    assert(node_ != nullptr);
    auto val = std::move(node_->val);
    auto tmp = node_;
    node_ = node_->next;
    delete tmp;
    return val;
}

template<typename T>
const T& LinkedQueue<T>::Peek() const {
    assert(node_ != nullptr);
    return node_->val;
}

template<typename T>
ArrayQueue<T>::ArrayQueue() : data_{16}, a_{0}, b_{0} {}

template<typename T>
bool ArrayQueue<T>::Empty() const {
    return a_ == b_;
}


template<typename T>
void ArrayQueue<T>::Enqueue(const T& val) {
    if (b_ == static_cast<int>(data_.size())) {
        if (a_ == 0) {
            data_.resize(static_cast<int>(data_.size() * 2), T{});
        } else {
            auto len = b_ - a_;
            std::move(data_.begin() + a_, data_.begin() + b_,
                      data_.begin());
            a_ = 0;
            b_ = len;
        }
    }
    data_[b_++] = val;
}

template<typename T>
T ArrayQueue<T>::Dequeue() {
    assert(!Empty());
    auto val = std::move(data_[a_]);
    ++a_;
    if (a_ > 32 && a_ > (b_ - a_) * 2) {
        auto len = b_ - a_;
        std::move(data_.begin() + a_, data_.begin() + b_,
                  data_.begin());
        a_ = 0;
        b_ = len;
        data_.resize(b_);
    }
    return val;
}

template<typename T>
const T& ArrayQueue<T>::Peek() const {
    assert(!Empty());
    return data_[a_];
}
