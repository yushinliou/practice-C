# include <iostream>
# include <string.h>
# include <string>
# include <cstring>
# include <ctype.h>
using namespace std;
const int MAX_MYSTR = 20;
class MyString{
    private:
        char *chars;
        char *name;
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
        void operator-(const MyString& s);
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
    delete [] chars;
    chars = new char[s.length()+1];
    strcpy(chars, s.c_str());
    return *this;
}

const MyString &MyString::operator=(const char* c){
    delete [] chars;
    chars = new char[2];
    strcpy(chars, c);
    return *this;
}
const MyString &MyString::operator=(const MyString& m){
    delete [] chars;
    delete [] name;
    chars = new char[strlen(m.chars)+1];
    name = new char[strlen(m.name)+1];
    strcpy(chars, m.chars);
    strcpy(name, m.name);
    return *this;
}
char& MyString::operator[](int i){
    return chars[i];
}
void MyString::operator-(const MyString& s){

    string ori = chars, sub = s.chars;
    string tmp1, tmp2;
    for(int i = 0; i < 6000; i++){
        if (string::npos == ori.find(sub)){
            break;
        }
        tmp1 = ori.substr(0, ori.find(sub));
        tmp2 = ori.substr(ori.find(sub)+sub.length(), ori.length()-(ori.find(sub)+sub.length()));
        ori = tmp1+tmp2;
    }
    delete [] chars;
    chars = new char[ori.length()+1];
    strcpy(chars, ori.c_str());
}
// 執行字串內容的相加
const MyString MyString::operator+(const MyString& s2){
    string sum = string(chars) + string(s2.chars);
    delete [] chars;
    chars = new char[sum.length()+1];
    strcpy(chars, sum.c_str());
    return *this;
}
// 執行字串內容的相乘 "ab" * 3 = "ababab"
const MyString MyString::operator*(int j){
    string sum;
    string original = chars;
    for (int i = 0; i < j ;i++){
        sum+=original;
    }
    delete [] chars;
    chars = new char[sum.length()+1];
    strcpy(chars, sum.c_str());
    return *this;
} 
/*function*/
const string MyString::getStr(){
    return this->chars;
}
const string MyString::getName(){
    string strName = name;
    return strName;
}
void MyString::printString(){
    string strChars = chars;
    cout << strChars;
}
void MyString::set_chars(string inString){
    chars = new char[inString.length()+1];
    strcpy(chars, inString.c_str());
}
void MyString::set_name(string name){
    delete [] this->name;
    this->name = new char[name.length()+1];
    strcpy(this->name, name.c_str());
}
/*constructor*/
MyString::MyString(){
    chars = new char[2];
    name = new char[2];
    strcpy(chars, "\0");
    strcpy(name, "\0");
}

MyString::MyString(string inString, string name){
    chars = new char[inString.length()+1];
    strcpy(chars, inString.c_str());
    this->name = new char[name.length()+1];
    strcpy(this->name, name.c_str());
}

MyString::MyString(string inString){
    chars = new char[inString.length()+1];
    strcpy(chars, inString.c_str());
}

MyString::MyString(const MyString& m){
    chars = new char[strlen(m.chars)+1];
    strcpy(chars, m.chars);
    name = new char[strlen(m.name)+1];
    strcpy(name, m.name); 
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
    else if (cmdName == "subtractObject"){
        return 5;
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
    // asignIdx 是要被指定的那個物件相對應在MyString List當中的編號
    for (int i = 0; i < MAX_MYSTR; i++){
        if (MyStringList[i].getName() == name){
            asignIdx = i;
        }
    }

    if (asignIsIndex){ // 有索引的狀況，要修改特定索引的內容
        MyStringList[asignIdx][inputIdx] = dec1and2[1]; // dec1and2 一定是 "A"一類的格式，所以取第一個位置
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
    else{ // 如果有索引的話，先把索引抓出來轉成數字
        indexStr = name.substr(name.find("[")+1, name.length()-name.find("[")-2);
        index = stoi(indexStr);
        name = name.substr(0, name.find("["));
        // 遍歷所有類別找到相對應的名稱，輸出字串內容
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

    // set新物件的名稱
    res.set_name(name);
    // 如果沒有找到"，代表不是要用字串宣告，是要執行assign/+/*這幾種操作
    if (string::npos == cmdContent.find("\"")){
        if (string::npos != cmdContent.find("+")){ // 找到加號，執行相加
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
        // 把字串去除掉頭尾的"，接著再set到類別當中
        res.set_chars(inputChars.substr(1, inputChars.length()-2));
        return res;
    }
    return res;
}
// 相減的函式
void subtractObject(string cmdContent, MyString MyStringList[MAX_MYSTR]){
    // name要被減的物件的名稱，subname是要減別人的類別名稱
    string name, subName;
    // 這兩個物件名稱分別對應到MyStringList當中編號多少的類別
    int nameIdx, subNameIdx;
    // 切開字串空白以前的是要被減的類別名稱，後半部則是減別人的
    name = cmdContent.substr(0, cmdContent.find(" "));
    subName = cmdContent.substr(cmdContent.find(" ")+1, cmdContent.length());
    // 遍歷物件名稱，找出來對應的編號
    for (int i = 0; i < MAX_MYSTR; i++){
        if (MyStringList[i].getName() == name){
            nameIdx = i;
        }
        if (MyStringList[i].getName() == subName){
            subNameIdx = i;
        }
    }
    // 執行相減
    MyStringList[nameIdx] - MyStringList[subNameIdx];
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
        // 取得輸入，首先先判斷是什麼樣的指令類型：宣告、相減...
        getline(cin, aCmd);
        cmdType = getCmdType(aCmd, cmdContent);
        // 如果是宣告，呼叫宣告的函式，會回傳一個新建立的物件到MyString list當中
        if (cmdType == 1){
            strList[listCt] = declare(cmdContent, strList);
            // 紀錄目前有多少個物件被宣告了
            listCt ++;
        } // 其餘按照指令類型呼叫相對應的函式
        else if (cmdType == 2){
            assignObject(cmdContent, strList);
        }
        else if (cmdType == 3){
            print(cmdContent, strList);
        }
        else if (cmdType == 4){
            assignString(cmdContent, strList);
        }
        else if (cmdType == 5){
            subtractObject(cmdContent, strList);
        }
    }

    // string a = "s0", b = "s1";
    // string astr = "1212", bstr = "012012 012012";
    // cout << (string::npos == bstr.find(astr));


    return 0;
}