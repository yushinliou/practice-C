#include <string>
#include <vector>
#include <iostream>
#include <algorithm> // For Test
#include <random>    // For Test

struct IStringDatabase {
    virtual void Add(const std::string&) = 0;
    virtual bool Remove(const std::string&) = 0;
    virtual std::vector<std::string> StartsWith(const std::string& prefix) = 0;
    virtual ~IStringDatabase() {}
};

// [YOUR CODE WILL BE PLACED HERE]
# include <unordered_map>
using namespace std;

class TrieNode {
public:
    bool is_end_of_word;
    int counter;
    unordered_map<char, TrieNode*> children;

    TrieNode() {
        is_end_of_word = false;
        counter = 0;
    }

    ~TrieNode() {
        for (auto& child : children) {
            delete child.second;
        }
    }
};
 
class StringDatabase : public IStringDatabase {
public:
    StringDatabase(){
        root = new TrieNode;
    }
    void Add(const std::string& word) override {
        if(word.empty()) { return; }
        else if (search(word)){return;}

        TrieNode* current = root;
        for (auto c : word){
            if (current->children.find(c) == current->children.end()){
                current->children[c] = new TrieNode();
            }
        current = current->children[c];
        current->children[c]->counter++;
        }
        current->is_end_of_word = true;
    }
    bool search(const string & word){
        TrieNode* current = root;
        for(auto c : word){
            if (current->children.find(c) == current->children.end()) {
                return false;
            }
            current = current->children[c];
        }
        return current->is_end_of_word;
    }
    bool Remove(const std::string& s) override {
        // 搜尋字典樹中是否有該字串，如果沒有就回傳 false
        TrieNode* current = root;
        for (auto c : s) {
            if (current->children.find(c) == current->children.end()) {
                return false;
            }
            current = current->children[c];
            current->children[c]->counter--;
        }

        // 將該字串的 is_end_of_word 標記設為 false
        current->is_end_of_word = false;
        return true;
    }

    void dfs(TrieNode* node, string word, vector<string>& res){
        if(node->is_end_of_word){
            res.push_back(word);
        }
        for(auto& child:node->children){
            dfs(child.second, word+child.first, res);
        }
    }
    std::vector<std::string> StartsWith(const std::string& prefix) override {
        TrieNode* current = root;
        vector<string> res;
        for (auto c: prefix){
            if (current->children.find(c) == current->children.end()){
                return res;
            }
            current = current->children[c];
        }
        dfs(current, prefix, res);
        sort(res.begin(), res.end());
        return res;
    }

private:
    TrieNode* root;
};



void Test1(); // Sample1
void Test2(); // Add, StartsWith
void Test3(); // Add, StartsWith
void Test4(); // Add, StartsWith
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

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v) {
    os << '[';
    if (v.size() > 0) {
        os << v[0];
        for (size_t i = 1; i < v.size(); ++i) {
            os << ", " << v[i];
        }
    }
    return os << ']';
}

namespace Feis {}

void Test1() {
    IStringDatabase&& db = StringDatabase();
    db.Add("Helloworld");
    db.Add("HelloWorld");
    db.Add("Hello");
    db.Add("Helloworld");
    db.Add("Hello");
    db.Add("Hi");

    std::cout << "01) " << db.StartsWith("Hello") << std::endl;
    std::cout << "02) " << db.StartsWith("hello") << std::endl;
    std::cout << "03) " << db.StartsWith("H") << std::endl;

    db.Remove("Helloworld");
    db.Remove("Hi");
    std::cout << "04) " << db.StartsWith("H") << std::endl;
}

void Test2() {}
void Test3() {}
void Test4() {}
void Test5() {}
void Test6() {}
void Test7() {}