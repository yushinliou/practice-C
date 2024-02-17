#include <cmath>
#include <string>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

string convert(int numGrade){
    string strGrade;
    if ((numGrade >= 0) & (numGrade <= 59)){ strGrade = "F";}
    else if ((numGrade >= 60) & (numGrade <= 62)){ strGrade = "C-";}
    else if ((numGrade >= 63) & (numGrade <= 66)){ strGrade = "C";}
    else if ((numGrade >= 67) & (numGrade <= 69)){ strGrade = "C+";}
    else if ((numGrade >= 70) & (numGrade <= 72)){ strGrade = "B-";}
    else if ((numGrade >= 73) & (numGrade <= 76)){ strGrade = "B";}
    else if ((numGrade >= 77) & (numGrade <= 79)){ strGrade = "B+";}
    else if ((numGrade >= 80) & (numGrade <= 84)){ strGrade = "A-";}
    else if ((numGrade >= 84) & (numGrade <= 89)){ strGrade = "A";}
    else if ((numGrade >= 90) & (numGrade <= 100)){ strGrade = "A+";}
    return strGrade;
}

int str2int(string strGrade){
    vector<string> ranks;
    ranks.push_back("X");
    ranks.push_back("F");
    ranks.push_back("C-");
    ranks.push_back("C");
    ranks.push_back("C+");
    ranks.push_back("B-");
    ranks.push_back("B");
    ranks.push_back("B+");
    ranks.push_back("A-");
    ranks.push_back("A");
    ranks.push_back("A+");
    int rankGrades[20] = {0, 50, 60, 65, 68, 70, 75, 78, 82, 87, 95};
    int resGrade;
    for (int i = 0; i < 11; i++){
        if (strGrade == ranks[i]){ return rankGrades[i];}
    }
    return 0;
}

bool rankAbig(const string& a, const string& b){
    if (a == b) return false;
    else if (((a[0] == 'F') & (b[0] == 'X')) | \
    ((a[0] == 'X') & (b[0] == 'F'))) return false;
    else if (a[0] == b[0]){
        return (a[1] < b[1]);
    }
    else return (a[0] < b[0]);
}


class Grade {
    friend ostream& operator<<(ostream& os, const Grade& p);
public:
    Grade();
    Grade(string strGrade);
    Grade(int numGrade);
    Grade(const char* strGrade);
    const Grade& operator=(const Grade& rhs);
    const Grade& operator=(int numGrade);
    const Grade& operator=(string strGrade);
    const Grade& operator=(char strGrade[5]);
    bool operator==(const Grade& rhs) const;
    bool operator!=(const Grade& rhs) const;
    bool operator<(const Grade& rhs) const;
    bool operator>(const Grade& rhs) const;
    bool operator<=(const Grade& rhs) const;
    bool operator>=(const Grade& rhs) const;
    operator bool() const{ return strGrade[0]!='X';}
    string GetRank() const;
    int GetScores() const;
    // Grade Average(const Grade& g1, const Grade& g2) const;
    void Reset();
private:
    string strGrade;
    double numGrade;
};

Grade::Grade(){
    this->strGrade = "X";
    this->numGrade = 0;
}
Grade::Grade(const char* g) {
    string strGrade = g;
    this->strGrade = g;
    this->numGrade = str2int(strGrade);
}
Grade::Grade(string strGrade){
    this->strGrade = strGrade;
    this->numGrade = str2int(strGrade);
}
Grade::Grade(int numGrade){
    this->numGrade = numGrade;
    this->strGrade = convert(numGrade);
}

// operator action
ostream& operator<<(ostream& os, const Grade& p){
    os << p.strGrade;
    return os;
}
const Grade& Grade::operator=(const Grade& rhs){
    this->strGrade = rhs.strGrade;
    this->numGrade = str2int(rhs.strGrade);
    return *this;
}
const Grade& Grade::operator=(string strGrade){
    this->strGrade = strGrade;
    this->numGrade = str2int(strGrade);
    return *this;
}
const Grade& Grade::operator=(char * strGrade){
    this->strGrade = strGrade;
    this->numGrade = str2int(strGrade);
    return *this;
}
const Grade& Grade::operator=(int numGrade){
    this->numGrade = numGrade;
    this->strGrade = convert(numGrade);
    return *this;
}
// operator bool
bool Grade::operator== (const Grade& rhs) const
{
    if ((this->strGrade[0] == 'X') & (rhs.strGrade[0] == 'F')){ return true;}
    else if ((this->strGrade[0] == 'F') & (rhs.strGrade[0] == 'X')){ return true;}
    else if ((this->strGrade == rhs.strGrade)){ return true;}
    else return false;
}
bool Grade::operator!= (const Grade& rhs) const
{
    if (*this == rhs){ return false;}
    else return true;
}
bool Grade::operator> (const Grade& rhs) const
{
    if (*this == rhs){ return false;} // if same, no smaller
    else return this->numGrade > rhs.numGrade;
    //else return rankAbig(this->strGrade, rhs.strGrade);
}
bool Grade::operator>= (const Grade& rhs) const
{
    if (*this == rhs){ return true;} // if same, no smaller
    else if (*this > rhs){ return true;}
    else return false;
}
bool Grade::operator< (const Grade& rhs) const
{
    if (*this == rhs){ return false;}
    else if (*this > rhs){ return false;}
    else return true;
}
bool Grade::operator<= (const Grade& rhs) const
{
    if (*this == rhs){ return true;}
    else if (*this > rhs){ return false;}
    else return true;
}

void Grade::Reset(){
    this->strGrade = "X";
    this->numGrade = 0;
}

string Grade::GetRank() const{
    return this->strGrade;
}
int Grade::GetScores() const{
    return this->numGrade;
}

Grade Average(const Grade& g1, const Grade& g2){
    Grade avgGrade = "X";
    if ((g1.GetRank()[0] == 'X') | (g2.GetRank()[0] == 'X')){ return avgGrade;}
    else{
        double g1f = g1.GetScores();
        double g2f = g2.GetScores();
        avgGrade = round((g1f + g2f)/2);
        return avgGrade;
    }
}

// [YOUR CODE WILL BE PLACED HERE]

#include <cmath>
#include <string>
#include <iostream>
#include <map>

void Test1(); // sample
void Test2(); // constructor: string
void Test3(); // constructor: int
void Test4(); // constructor: int, GetRank, GetScores
void Test5(); // constructor: int, comparison
void Test6(); // constructor: int, Average, GetScores
void Test7(); // constructors: default, string, int, copy, casting: bool, Reset

int main() {
    int id;
    std::cin >> id;
    void (*f[])() = { Test1, Test2, Test3, Test4, Test5, Test6, Test7 };
    f[id-1]();
}

void Test1()
{
    // Grade 預設初始化後為『未給分』("X") 狀態
    {
        cout << "Test" << endl;
        Grade g;
        std::cout << g << std::endl; // 此時印出 "X"
        std::cout << g.GetRank() << std::endl; // 此時印出 "X"
        g = 0;
        std::cout << g.GetRank() << std::endl; // 此時印出 "F"
        cout << "Test" << endl;
    }

    // Grade 可用 C 風格字串或 C++字串 (std::string 型態) 表示等第成績以進行初始化或賦值運算
    // - 合法的字串包含 "A+", "A-", "A", "B+", "B-", "B", "C+", "C-", "C", "F", "X"
    // - 使用不在上述的字串進行初始化或賦值運算為《未定義行為》(undefined behavior)
    {
        Grade g1 = "A";
        std::cout << g1 << std::endl; // 此時印出 "A"

        g1 = "B+";
        std::cout << g1 << std::endl; // 此時印出 "B+"

        Grade g2 = std::string("A+");
        std::cout << g2 << std::endl; // 此時印出 "A+"

        g2 = std::string("C");
        std::cout << g2 << std::endl; // 此時印出 "C"

        const Grade g3 = g2;
        std::cout << g3 << std::endl; // 此時印出 "C"
    }

    // Grade 可用整數 (int) 表示百分制成績後進行初始化或賦值
    // - 如果輸入的整數超過百分制成績範圍 [0, 100] 的話是《未定義行為》(undefined behavior)
    {
        Grade g = 100;
        std::cout << g << std::endl; // 此時印出 "A+"

        g = 75;
        std::cout << g << std::endl; // 此時印出 "B"
    }

    // Grade 物件提供 GetRank() 操作，回傳其等第字串 (std::string 型態)
    {
        const Grade g1 = "A";
        std::string g2 = g1.GetRank();
        std::cout << g2 << std::endl;             // 印出 "A"
    }

    // Grade 物件提供 GetScores() 操作，回傳百分制分數 (int 型態)
    {
        const Grade g1 = "A";
        std::cout << g1.GetScores() << std::endl; // 此時印出 "87"

        const Grade g2 = 53;
        std::cout << g2.GetScores() << std::endl; // 此時印出 "53"

        const Grade g3 = "X";
        std::cout << g3.GetScores() << std::endl; // 此時印出 "0"
    }

    // Grade 物件可進行比較運算 (>, <, <=, >=, ==, !=)，回傳 bool 型態值
    // - 比較時，不管百分制分數高低，而只以等第高低比較：A+ > A > A- > B+ > B > B- > C+ > C > C- > F == X
    // - 比較時，不管百分制分數高低，同等第表示相等：A+ 與 A+ 相等，A+ 與 A 不相等
    // - 此外，比較時，F 與 X 是相等的
    {
        const Grade g1 = "A", g2 = "A+", g3 = "B-", g4 = "B-", g5 = "F", g6 = "X";
        std::cout << std::boolalpha << (g3 == g4) << std::endl;  // 印出 "true"
        std::cout << std::boolalpha << (g1 != g2) << std::endl;  // 印出 "true"
        std::cout << std::boolalpha << (g1 < g2) << std::endl;   // 印出 "true" // f
        // cout << "error" << g1.GetScores() << " " << "<" << " " << g2.GetScores() << endl;
        std::cout << std::boolalpha << (g1 > g2) << std::endl;   // 印出 "false" // t
        std::cout << std::boolalpha << (g3 <= g4) << std::endl;   // 印出 "true"
        std::cout << std::boolalpha << (g3 >= g4) << std::endl;   // 印出 "true"
        std::cout << std::boolalpha << (g1 <= g2) << std::endl;   // 印出 "true" // f
        std::cout << std::boolalpha << (g1 >= g2) << std::endl;   // 印出 "false" // t
        std::cout << std::boolalpha << (g5 == g6) << std::endl;  // 印出 "true"
        std::cout << std::boolalpha << (g4 > g5) << std::endl;   // 印出 "true"
        std::cout << std::boolalpha << (g6 < g2) << std::endl;   // 印出 "true"
        std::cout << std::boolalpha << (Grade(90) == Grade(100)) << std::endl;   // 印出 "true"
    }

    // 提供一般函式 Average(const Grade& g1, const Grade& g2) 回傳兩個成績 (g1 與 g2) 平均的結果
    // - 平均結果是將兩個成績的百分制分數 (g1 與 g2) 相加除二後，四捨五入到整數位。
    // - 平均結果需要在 [0, 100] 之間，否則為《未定義行為》(undefined behavior)
    // - g1 與 g2 如果原本有一個是未給分 ("X")，平均後為依舊需要是未給分 ("X")
    {
        Grade g1 = 80;
        Grade g2;
        std::cout << Average(g1, Grade(40)) << std::endl;      // 印出 "C-"
        std::cout << Average(g1, g2) << std::endl;             // 印出 "X"
        std::cout << Average(Grade(40), Grade(85)).GetScores() << std::endl; // 印出 "63"
    }

    // Grade 物件提供 Reset() 操作，將成績轉成未給分 ("X")
    {
        Grade g = "A+";
        g.Reset();
        std::cout << g << std :: endl; // 此時印出 "X"
    }

    // Grade 物件可隱性轉型成 bool 型態，表示是否已經給分**
    {
        const Grade g1 = "A+";
        bool isG1Graded = g1;
        std::cout << std::boolalpha << isG1Graded << std::endl; // 此時印出 "true"

        const Grade g2;
        bool isG2Graded = g2;
        std::cout << std::boolalpha << isG2Graded << std::endl; // 此時印出 "false"

        if (g1) {
            std::cout << "g1" << std::endl; // 印出 "g1"
        }

        if (g2) {
            std::cout << "g2" << std::endl; // 不會執行到
        }
    }
}

void Test2() {
    // HIDDEN
}

void Test3() {
    // HIDDEN
}

void Test4() {
    // HIDDEN
}

void Test5() {
    // HIDDEN
}

void Test6() {
    // HIDDEN
}

void Test7() {
    // HIDDEN
}