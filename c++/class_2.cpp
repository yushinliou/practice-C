# include <iostream>
# include <string.h>
# include <string>
# include <ctype.h>
using namespace std;
const int MAX_MYSTR = 20;
class MyString{
    private:
        string chars;
        string name;
    public:
        void set_chars(string inString);
        void set_name(string name);
        void printString();
        MyString();
        MyString(char* c);
        MyString(string inString, string name);
        MyString(string inString);
        MyString(const MyString& m);
        ~MyString();
        const string getStr();
        const string getName();
        const MyString operator+(const MyString& s2);
        const MyString operator*(int j);
        const MyString& operator=(const MyString& m);
        const MyString& operator=(const string& s);
        const MyString& operator=(const char* c);
        char& operator[](int i);
};
/*operator*/
const MyString &MyString::operator=(const string& s){
    chars = s;
    return *this;
}

const MyString &MyString::operator=(const char* c){
    chars = c;
    return *this;
}
const MyString &MyString::operator=(const MyString& m){
    chars = m.chars;
    name = m.name;
    return *this;
}
char& MyString::operator[](int i){
    return chars[i];
}
const MyString MyString::operator+(const MyString& s2){
    chars = chars + s2.chars;
    return *this;
}
// operator+(operator+(a, b), c)
const MyString MyString::operator*(int j){
    string original = chars;
    for (int i = 0; i < j-1 ;i++){
        chars+=original;
    }
    return *this;
} 
/*function*/
const string MyString::getStr(){
    return this->chars;
}
const string MyString::getName(){
    return this->name;
}
void MyString::printString(){
    cout << chars;
}
void MyString::set_chars(string inString){
    chars = inString;
}
void MyString::set_name(string name){
    this->name = name;
}
/*constructor*/
MyString::MyString(){
    chars="";
    name="";
}

MyString::MyString(string inString, string name){
    chars=inString;
    this->name = name;
}

MyString::MyString(string inString){
    chars=inString;
}
MyString::MyString(const MyString& m){
    chars=m.chars;
    name=m.name;
}

/*destructor*/
MyString::~MyString(){
}

// 讀取一行指令，回傳這個指令的內容，以及這個指令的類型
// declare assign print 分別對應到 1 2 3
int getCmdType(const string aCmd, string &cmdContent){
    string cmdName;
    cmdName = aCmd.substr(0, aCmd.find(" "));
    cmdContent = aCmd.substr(aCmd.find(" ")+1, aCmd.length());
    if (cmdName == "declare"){
        return 1;
    }
    else if (cmdName == "assignObject"){
        return 2;
    }
    else if (cmdName == "print"){
        return 3;
    }
    else if (cmdName == "assignString"){
        return 4;
    }
    else{
        return 0;
    }
}
void assignString(string cmdContent, MyString MyStringList[MAX_MYSTR]){
    string name, inputChars;
    string dec1and2, decName1, decName2;
    MyString dec1, dec2;
    MyString res;
    char charInput;
    int multipleTime = 0;
    int asignIdx = 0;
    int inputIdx = 0;
    int asignIsIndex = 0;
    string inputIdxStr;
    // 先把資料再切分成要assign的物件名稱，宣告的行為，也就是使用第一個空白斷開

    name = cmdContent.substr(0, cmdContent.find(" "));
    // 如果名稱是有索引取值的話，把索引inputIdx、真正的物件名稱name抓出來
    if (string::npos != name.find("[")){
        inputIdxStr = name.substr(name.find("[")+1, name.length()-name.find("[")-2);
        inputIdx = stoi(inputIdxStr);
        name = name.substr(0, name.find("["));
        asignIsIndex = 1; // 紀錄這個輸入是要索引取值
    }
    dec1and2 = cmdContent.substr(cmdContent.find(" ")+1, cmdContent.length());

    for (int i = 0; i < MAX_MYSTR; i++){
        if (MyStringList[i].getName() == name){
            asignIdx = i; // 找一下要被asign的物件是第幾個
        }
    }

    if (asignIsIndex){ // 有索引的狀況
        MyStringList[asignIdx][inputIdx] = dec1and2[1]; // 因為字串長度一定是一，取位置一的字元
    }
    else{ // 非索引單純物件名稱的狀況
        dec1and2 = dec1and2.substr(1, dec1and2.length()-2);
        MyStringList[asignIdx] = dec1and2;
    }
    MyStringList[asignIdx].set_name(name);
}


void assignObject(string cmdContent, MyString MyStringList[MAX_MYSTR]){
    string name, inputChars;
    string dec1and2, decName1, decName2;
    MyString dec1, dec2;
    MyString res;
    char charInput;
    int multipleTime = 0;
    int asignIdx = 0;
    int inputIdx = 0;
    int asignIsIndex = 0;
    string inputIdxStr;
    // 先把資料再切分成要assign的物件名稱，宣告的行為，也就是使用第一個空白斷開

    name = cmdContent.substr(0, cmdContent.find(" "));
    if (string::npos != name.find("[")){
        inputIdxStr = name.substr(name.find("[")+1, name.length()-name.find("[")-2);
        inputIdx = stoi(inputIdxStr);
        name = name.substr(0, name.find("["));
        asignIsIndex = 1;
    }
    dec1and2 = cmdContent.substr(cmdContent.find(" ")+1, cmdContent.length());

    for (int i = 0; i < MAX_MYSTR; i++){
        if (MyStringList[i].getName() == name){
            asignIdx = i;
        }
    }

    if (asignIsIndex){ // 有索引的狀況
        MyStringList[asignIdx][inputIdx] = dec1and2[1];
    }
    else{ // 非索引單純物件名稱的狀況
        if (string::npos != cmdContent.find("+")){ // 指定其他物件相加的狀況
            // 把第一個跟第二個的名稱切開
            decName1 = dec1and2.substr(0, dec1and2.find("+"));
            decName2 = dec1and2.substr(dec1and2.find("+")+1, dec1and2.length());
            // 遍歷目前有的清單，找名稱一樣的
            for (int i = 0; i < MAX_MYSTR; i++){
                if (decName1 == MyStringList[i].getName()){
                    dec1 = MyStringList[i];
                }
                if (decName2 == MyStringList[i].getName()){
                    dec2 = MyStringList[i];
                }
            }
            MyStringList[asignIdx] = dec1+dec2;
        }
        else if (string::npos != cmdContent.find("*")){ // 指定其他物件相乘的狀況
            decName1 = dec1and2.substr(0, dec1and2.find("*"));
            decName2 = dec1and2.substr(dec1and2.find("*")+1, dec1and2.length());
            multipleTime = stoi(decName2);
            // 遍歷目前有的清單，找名稱一樣的
            for (int i = 0; i < MAX_MYSTR; i++){
                if (decName1 == MyStringList[i].getName()){
                    dec1 = MyStringList[i];
                }
            }
                MyStringList[asignIdx] = dec1 * multipleTime;
        }
        else if (string::npos != cmdContent.find("\"")){
            MyStringList[asignIdx] = dec1and2;
        }
        else{ // 指定另外一個物件字串內容的狀況
            for (int i = 0; i < MAX_MYSTR; i++){
                if (dec1and2 == MyStringList[i].getName()){
                    MyStringList[asignIdx] = MyStringList[i];
                }
            }
        }
    MyStringList[asignIdx].set_name(name);
    }
}
// print command
void print(string cmdContent, MyString MyStringList[MAX_MYSTR]){
    string name, indexStr;
    int index = 0;
    // 先取出要印的名字
    name = cmdContent.substr(0, cmdContent.find(" "));
    // 如果沒找到中括號，代表不包含索引
    if (string::npos == name.find("[")){
        for (int i = 0; i < MAX_MYSTR; i++){
            if (name == MyStringList[i].getName()){
                cout << MyStringList[i].getStr() << endl;
            }
        }
    }
    else{ // 如果有索引的話，先把索引抓出來
        indexStr = name.substr(name.find("[")+1, name.length()-name.find("[")-2);
        index = stoi(indexStr);
        name = name.substr(0, name.find("["));
        for (int i = 0; i < MAX_MYSTR; i++){
            if (name == MyStringList[i].getName()){
                cout << MyStringList[i][index] << endl;
            }
        }
    }
}
// declare command
MyString declare(string cmdContent, MyString MyStringList[MAX_MYSTR]){
    string name, inputChars;
    string dec1and2, decName1, decName2;
    MyString dec1, dec2;
    MyString res;
    int multipleTime = 0;
    // 先把資料再切分成宣告物件的名稱，宣告的行為，也就是使用第一個空白斷開
    name = cmdContent.substr(0, cmdContent.find(" "));
    dec1and2 = cmdContent.substr(cmdContent.find(" ")+1, cmdContent.length());
    res.set_name(name);

    // cout << "name " << name << endl;
    // cout << "dec1and2 " << dec1and2 << endl;
    if (string::npos == cmdContent.find("\"")){
        if (string::npos != cmdContent.find("+")){
            // 把第一個跟第二個的名稱切開
            decName1 = dec1and2.substr(0, dec1and2.find("+"));
            decName2 = dec1and2.substr(dec1and2.find("+")+1, dec1and2.length());
            // 遍歷目前有的清單，找名稱一樣的
            for (int i = 0; i < MAX_MYSTR; i++){
                if (decName1 == MyStringList[i].getName()){
                    dec1 = MyStringList[i];
                }
                if (decName2 == MyStringList[i].getName()){
                    dec2 = MyStringList[i];
                }
            }
            res = dec1+dec2;
            res.set_name(name);
            return res;
        }
        else if (string::npos != cmdContent.find("*")){
            decName1 = dec1and2.substr(0, dec1and2.find("*"));
            decName2 = dec1and2.substr(dec1and2.find("*")+1, dec1and2.length());
            multipleTime = stoi(decName2);
            // 遍歷目前有的清單，找名稱一樣的
            for (int i = 0; i < MAX_MYSTR; i++){
                if (decName1 == MyStringList[i].getName()){
                    dec1 = MyStringList[i];
                }
            }
            res = dec1 * multipleTime;
            res.set_name(name);
            return res;
        }
        else{ // 如果都沒有代表是宣告一個空的字串
            for (int i = 0; i < MAX_MYSTR; i++){
                if (dec1and2 == MyStringList[i].getName()){
                    inputChars = MyStringList[i].getStr();
                }
            }
            res.set_chars(inputChars);
            return res;
        }
    }
    else{ // 如果有找到" 代表是用字串做宣告的
        inputChars = dec1and2;
        // cout << "name" << name;
        res.set_chars(inputChars.substr(1, inputChars.length()-2));
        // res.set_name(name);
        //cout << res.getName() << " " << res.getStr() << endl;
        return res;
    }
    return res;
}

int main(){

    int cmdNum = 0;
    int cmdType = 0;
    string aCmd, cmdContent;
    string decTarget, dec1, dec2;
    MyString strList[MAX_MYSTR];
    int listCt = 0;

    cin >> cmdNum;
    cin.ignore();
    for (int i = 0; i < cmdNum; i++){
        getline(cin, aCmd);
        cmdType = getCmdType(aCmd, cmdContent);
        if (cmdType == 1){
            strList[listCt] = declare(cmdContent, strList);
            listCt ++;
        }
        else if (cmdType == 2){
            assignObject(cmdContent, strList);
        }
        else if (cmdType == 3){
            print(cmdContent, strList);
        }
        else if (cmdType == 4){
            assignString(cmdContent, strList);
        }
    }

    // for (int i = 0; i < listCt; i++){
    //     cout << strList[i].getName() << " " << strList[i].getStr() << endl;
    // }

    // string a = "hi", b = "lo";
    // MyString tmp1(a, a), tmp2(b, b);
    // cout << tmp2.getName() << " " << tmp2.getStr() << endl;
    // tmp2 = tmp1 + tmp2;
    // cout << tmp2.getName() << " " << tmp2.getStr();
    return 0;
}