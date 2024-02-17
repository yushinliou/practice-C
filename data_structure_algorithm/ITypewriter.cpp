#include <string>

class ITypewriter {
    public:
        virtual ~ITypewriter() {}

        virtual void Put(char c) = 0;
        virtual void Put(const char* s) = 0;
        virtual void Put(std::string s) = 0;

        virtual std::string ToString() const = 0;
        virtual size_t Size() const = 0;

        virtual void Backspace() = 0;
        virtual void Delete() = 0;

        virtual void ToggleMode() = 0;

        virtual void Left() = 0;
        virtual void Right() = 0;

        virtual void Home() = 0;
        virtual void End() = 0;

        virtual void ClearAll() = 0;
        virtual void ClearToEndOfLine() = 0;

};

// [YOUR CODE WILL BE PLACED HERE]
// 使用chatgpt產生程式碼，手動針對tostring做時間複雜度優化
#include <iostream>
using namespace std;
class Typewriter : public ITypewriter {
    private:
        std::string buffer;
        bool insert_mode = true;
        size_t cursor_pos = 0;

    public:
        virtual void Put(char c) override {
            if (insert_mode) {
                buffer.insert(cursor_pos, 1, c);
                cursor_pos++;
            } else {
                if (cursor_pos < buffer.size()) {
                    buffer[cursor_pos] = c;
                    cursor_pos++;
                } else {
                    buffer.push_back(c);
                    cursor_pos++;
                }
            }
        }

        virtual void Put(const char* s) override {
            std::string str(s);
            Put(str);
        }

        virtual void Put(std::string s) override {
            if (insert_mode) {
                buffer.insert(cursor_pos, s);
                cursor_pos += s.size();
            } else {
                if (cursor_pos < buffer.size()) {
                    buffer.replace(cursor_pos, s.size(), s);
                    cursor_pos += s.size();
                } else {
                    buffer.append(s);
                    cursor_pos += s.size();
                }
            }
        }

        virtual std::string ToString() const override {
            std::string str = buffer;
            if (cursor_pos == buffer.size()) {
                if (insert_mode) {
                    str += "_";
                } else {
                    str += "|";
                }
            }
            else{
                if (insert_mode){
                    str.insert(cursor_pos, "_");
                }
                else{
                    str.insert(cursor_pos, "|");
                }
            }
            return str;
        }

        virtual size_t Size() const override {
            return buffer.size();
        }

        virtual void Backspace() override {
            if (cursor_pos > 0) {
                cursor_pos--;
                buffer.erase(cursor_pos, 1);
            }
        }

        virtual void Delete() override {
            if (cursor_pos < buffer.size()) {
                buffer.erase(cursor_pos, 1);
            }
        }

        virtual void ToggleMode() override {
            insert_mode = !insert_mode;
        }

        virtual void Left() override {
            if (cursor_pos > 0) {
                cursor_pos--;
            }
        }

        virtual void Right() override {
            if (cursor_pos < buffer.size()) {
                cursor_pos++;
            }
        }

        virtual void Home() override {
            cursor_pos = 0;
        }

        virtual void End() override {
            cursor_pos = buffer.size();
        }

        virtual void ClearAll() override {
            buffer.clear();
            cursor_pos = 0;
        }

        virtual void ClearToEndOfLine() override {
            if (cursor_pos < buffer.size()) {
                buffer.erase(cursor_pos, buffer.size() - cursor_pos);
            }
        }

};

#include <algorithm>
#include <cassert>    // For Test
#include <random>     // For Test
#include <functional> // For Test
#include <iostream>
#include <vector>

void Test1(); // Sample1
void Test2(); // ToString, Put
void Test3(); // ToString, Put, Size
void Test4(); // ToString, Put, Size, Backspace 
void Test5(); // ToString, Put, Size, Left, Right
void Test6(); // ToString, Put, Size, Left, Right, Home, End
void Test7(); // ToString, Put, Size, Left, Right, Home, Backspace, Delete
void Test8(); // ToString, Put, Size, Left, Right, Home, ClearAll, ClearToEnfOfLine
void Test9(); // ToString, Put, Size, Left, Right, Home, ToggleMode
void Test10(); // All

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int id;
    std::cin >> id;
    void (*f[])() = { Test1, Test2, Test3, Test4, Test5, Test6, Test7, Test8, Test9, Test10};
    f[id-1]();
}

namespace Feis {}

void Test1() {
    Typewriter t;
    ITypewriter& tw = t;

    std::cout << "01) " << tw.ToString() << std::endl;

    tw.Put('H');
    std::cout << "02) " << tw.ToString() << std::endl;

    std::cout << "03) " << tw.Size() << std::endl;

    tw.Put("ello");
    std::cout << "04) " << tw.ToString() << std::endl;

    std::cout << "05) " << tw.Size() << std::endl;

    tw.Put(std::string(" world!"));
    std::cout << "06) " << tw.ToString() << std::endl;

    std::cout << "07) " << tw.Size() << std::endl;

    tw.Backspace();
    std::cout << "08) " << tw.ToString() << std::endl;

    tw.Left();
    std::cout << "09) " << tw.ToString() << std::endl;

    for (size_t i = 1; i <= 9; ++i) {
        tw.Left();
    }
    std::cout << "10) " << tw.ToString() << std::endl;

    tw.ToggleMode();
    std::cout << "11) " << tw.ToString() << std::endl;

    tw.Put('a');
    std::cout << "12) " << tw.ToString() << std::endl;

    tw.Put("ppy");
    std::cout << "13) " << tw.ToString() << std::endl;

    tw.Put(std::string("!!!"));
    std::cout << "14) " << tw.ToString() << std::endl;

    tw.ClearToEndOfLine();
    std::cout << "15) " << tw.ToString() << std::endl;

    tw.Home();
    std::cout << "16) " << tw.ToString() << std::endl;

    tw.Left();
    std::cout << "17) " << tw.ToString() << std::endl;

    tw.Delete();
    std::cout << "18) " << tw.ToString() << std::endl;

    tw.ToggleMode();
    std::cout << "19) " << tw.ToString() << std::endl;

    tw.Put("Be ");
    std::cout << "20) " << tw.ToString() << std::endl;

    tw.Right();
    std::cout << "21) " << tw.ToString() << std::endl;

    tw.Delete();
    std::cout << "22) " << tw.ToString() << std::endl;

    tw.ClearAll();
    std::cout << "23) " << tw.ToString() << std::endl;

    tw.Put("Be happy");
    std::cout << "24) " << tw.ToString() << std::endl;

    tw.Home();
    std::cout << "25) " << tw.ToString() << std::endl;

    tw.End();
    std::cout << "26) " << tw.ToString() << std::endl;
}

void Test2() {}
void Test3() {}
void Test4() {}
void Test5() {}
void Test6() {}
void Test7() {}
void Test8() {}
void Test9() {}
void Test10() {}