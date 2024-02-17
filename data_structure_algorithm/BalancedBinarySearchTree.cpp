#include <iostream>
#include <random>
#include <functional>
#include <cassert>

// 模板參數 T 的合法型態會支援：
// - 值初始化：歸零
// - 複製語意：複製建構與賦值
// - 同型態間的比較運算：==, !=, >, >=, <, <=
// 符合以上要求的可能型態有：int, double, std::string 等等
template<typename T>
struct Node {
    T data;
    int meta{};
    Node<T>* left{};
    Node<T>* right{};
    explicit Node(const T& data) : data{data} {}
};

template<typename T>
class BalancedBinarySearchTreeSet {
public:
    BalancedBinarySearchTreeSet() = default;
    BalancedBinarySearchTreeSet(const BalancedBinarySearchTreeSet<T>&) = delete;
    ~BalancedBinarySearchTreeSet();
    BalancedBinarySearchTreeSet<T>& operator=(const BalancedBinarySearchTreeSet<T>&) = delete;
    [[nodiscard]] bool Contains(const T &) const;
    bool Add(const T &data);
    bool Remove(const T &);
    [[nodiscard]] std::vector<T> ToVector() const;
    [[nodiscard]] size_t Size() const { return size_; }
    [[nodiscard]] int Height() const;

private:
    Node<T> *root_{};
    size_t size_{};
};

void Test1(); // Sample1
void Test2(); // Add
void Test3(); // Add, ToVector
void Test4(); // Add, Remove, ToVector
void Test5(); // Add, Remove, ToVector

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int id;
    std::cin >> id;
    void (*f[])() = { Test1, Test2, Test3, Test4, Test5 };
    f[id-1]();
}

namespace {
    template<typename T>
    int GetHeight(Node<T>* root) {
        if (!root) return -1;
        return std::max(GetHeight(root->left), GetHeight(root->right)) + 1;
    }

    template<typename T>
    bool ValidateHeight(BalancedBinarySearchTreeSet<T>& s) {
        return s.Height() <= (2 * log(s.Size() + 2) + 2);
    }
    template<typename T>
    bool Contains(Node<T>* root, const T& data) {
        if (!root) {
            return false;
        }
        if (data < root->data) {
            return Contains(root->left, data);
        }
        if (root->data < data) {
            return Contains(root->right, data);
        }
        return true;
    }
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const BalancedBinarySearchTreeSet<T>& s) {
    std::vector<T> v = s.ToVector();
    os << "{";
    for (size_t i = 0; i < v.size(); ++i) {
        if (i > 0) {
            os << ", ";
        }
        os << v[i];
    }
    os << "}";
    return os;
}

template<typename T>
bool BalancedBinarySearchTreeSet<T>::Contains(const T& data) const {
    return ::Contains(root_, data);
}

template<typename T>
int BalancedBinarySearchTreeSet<T>::Height() const {
    return GetHeight(root_);
}

namespace Feis { /* HIDDEN */ }

void Test1() {
    std::cout << std::boolalpha;

    // 實作 Add(val) 方法
    // - 如果要新增的值 val 尚未存在集合中，則將 val 加入集合並回傳 true
    // - 如果要新增的值 val 已經存在集合中，則回傳 false 而不發生其他作用
    {
        BalancedBinarySearchTreeSet<int> s;
        std::cout << "01) " << ValidateHeight(s) << std::endl;
        std::cout << "02) " << s.Contains(3) << std::endl;
        std::cout << "03) " << s.Add(3) << std::endl;
        std::cout << "04) " << s.Add(5) << std::endl;
        std::cout << "05) " << s.Contains(3) << std::endl;
        std::cout << "06) " << s.Add(3) << std::endl;
        std::cout << "07) " << s.Size() << std::endl;
        std::cout << "08) " << ValidateHeight(s) << std::endl;
    }

    // 實作 ToVector() 方法，回傳一個由集合內所有元素所構成的陣列
    // - 陣列中的元素值由小到大排序
    {
        BalancedBinarySearchTreeSet<int> s;
        s.Add(3);
        s.Add(9);
        s.Add(7);
        std::cout << "09) " << s << std::endl;
        s.Add(1);
        s.Add(5);
        std::cout << "10) " << s << std::endl;
        std::cout << "11) " << ValidateHeight(s) << std::endl;
    }

    // 實作 Remove(val) 方法，移除值為 val 的元素
    // - 如果要新增的值 val 已經存在集合中，則將 val 從集合移除並回傳 true
    // - 如果要新增的值 val 尚未存在集合中，則回傳 false 而不發生其他作用
    {
        BalancedBinarySearchTreeSet<int> s;
        s.Add(3);
        s.Add(9);
        s.Add(7);
        std::cout << "14) " << s << std::endl;
        std::cout << "16) " << s.Remove(9) << std::endl;
        std::cout << "12) " << s.Remove(1) << std::endl;
        std::cout << "13) " << s.Remove(3) << std::endl;
        // std::cout << "test) " << s.Remove(3) << std::endl;
        // std::cout << "14) " << s << std::endl;
        // std::cout << "15) " << s.Remove(7) << std::endl;
        // std::cout << "16) " << s.Remove(9) << std::endl;
        std::cout << "17) " << s << std::endl;
    }
}

void Test2() { /* HIDDEN */ }
void Test3() { /* HIDDEN */ }
void Test4() { /* HIDDEN */ }
void Test5() { /* HIDDEN */ }

// [YOUR CODE WILL BE PLACED HERE]
// # include <stack>
# include <stack>
namespace {
    template<typename T>
    int GetBalanceFactor(Node<T>* node) {
        if (!node) return 0;
        return GetHeight(node->left) - GetHeight(node->right);
    }
    
    template<typename T>
    Node<T>* RotateLeft(Node<T>* node) {
        Node<T>* newRoot = node->right;
        node->right = newRoot->left;
        newRoot->left = node;
        return newRoot;
    }
    
    template<typename T>
    Node<T>* RotateRight(Node<T>* node) {
        Node<T>* newRoot = node->left;
        node->left = newRoot->right;
        newRoot->right = node;
        return newRoot;
    }
    
    template<typename T>
    Node<T>* InsertNode(Node<T>* root, const T& data) {
        if (!root) {
            return new Node<T>(data);
        }
        
        if (data < root->data) {
            root->left = InsertNode(root->left, data);
        } else if (root->data < data) {
            root->right = InsertNode(root->right, data);
        } else {
            return root; // Value already exists, no change needed
        }
        
        int balanceFactor = GetBalanceFactor(root);
        
        // Left Left Case
        if (balanceFactor > 1 && data < root->left->data) {
            return RotateRight(root);
        }
        
        // Right Right Case
        if (balanceFactor < -1 && root->right->data < data) {
            return RotateLeft(root);
        }
        
        // Left Right Case
        if (balanceFactor > 1 && root->left->data < data) {
            root->left = RotateLeft(root->left);
            return RotateRight(root);
        }
        
        // Right Left Case
        if (balanceFactor < -1 && data < root->right->data) {
            root->right = RotateRight(root->right);
            return RotateLeft(root);
        }
        
        return root;
    }
}

template<typename T>
bool BalancedBinarySearchTreeSet<T>::Add(const T& data) {
    if (Contains(data)) {
        return false;
    }
    
    root_ = InsertNode(root_, data);
    size_++;
    return true;
}

template<typename T>
BalancedBinarySearchTreeSet<T>::~BalancedBinarySearchTreeSet() {
    // 使用後序遍歷刪除節點
    std::function<void(Node<T>*)> deleteNode = [&](Node<T>* node) {
        if (node) {
            deleteNode(node->left);
            deleteNode(node->right);
            delete node;
            node = nullptr;  // 将指针设置为 nullptr
        }
    };

    deleteNode(root_);
}

template<typename T>
std::vector<T> BalancedBinarySearchTreeSet<T>::ToVector() const {
    std::vector<T> result;
    if (root_ == nullptr) {
        return result;
    }

    result.reserve(500);  // 预留足够的空间

    std::function<void(Node<T>*, std::vector<T>&)> inorderTraversal = [&](Node<T>* node, std::vector<T>& res) {
        if (node == nullptr) {
            return;
        }
        if (node->left) {
            inorderTraversal(node->left, res);
        }
        res.push_back(node->data);
        if (node->right) {
            inorderTraversal(node->right, res);
        }
    };

    inorderTraversal(root_, result);

    return result;
}


template<typename T>
bool BalancedBinarySearchTreeSet<T>::Remove(const T& val) {
    // Helper function to find the minimum value in a subtree
    auto findMin = [](Node<T>* node) -> Node<T>* {
        while (node && node->left) {
            node = node->left;
        }
        return node;
    };

    // Helper function to remove a node from the tree
    std::function<bool(Node<T>*&, const T&)> removeNode = [&](Node<T>*& node, const T& data) -> bool {
        if (!node) {
            return false;  // Node not found
        }
        if (data < node->data) {
            return removeNode(node->left, data);
        }
        if (node->data < data) {
            return removeNode(node->right, data);
        }

        if (!node->left && !node->right) {
            // Case 1: Node has no children
            delete node;
            node = nullptr;
        } else if (!node->left) {
            // Case 2: Node has only right child
            Node<T>* temp = node;
            node = node->right;
            delete temp;
        } else if (!node->right) {
            // Case 3: Node has only left child
            Node<T>* temp = node;
            node = node->left;
            delete temp;
        } else {
            // Case 4: Node has both left and right children
            Node<T>* temp = findMin(node->right);
            node->data = temp->data;
            return removeNode(node->right, temp->data);
        }

        size_--;  // Update the size counter
        return true;  // Node removed
    };

    if (!root_) {
        return false;  // 空樹，無法刪除節點
    }
    return removeNode(root_, val);
}