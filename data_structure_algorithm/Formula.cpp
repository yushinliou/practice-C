# include <iostream>
# include <string>
# include <vector>
# include <sstream>
# include <algorithm>
#include <ctype.h>

using namespace std;
bool isContainAlpha(const string &content){
    auto it = find_if(content.begin(), content.end(), ::isalpha);
    return (it != content.end());
}

using namespace std;
// template<typename T>
class cell{
    public:
        cell();
        cell(string content, int row, int col);
        // ~cell();
        bool getIsText(){return isText;}; // 回傳格式，True是文字，False是數字
        bool getIsFormula(){return isFormula;}
        string getOutput();
        string getText(){return text;}
        void doCaculate(const string &content);
        void doDecompose(const string &content);
        void deComposeFormula(const string &content);
        int evalExpression(const string &content, vector<vector<cell> > table, vector<vector<bool> > visit);
        int evalTerm(const string &content, vector<vector<cell> > table, vector<vector<bool> > visit);
    private:
        int row = 0;
        int col = 0;
        string text = "";
        long long int val = 0;
        bool isError = false;
        bool isText = false;
        bool isFormula = false;
        bool isBool = false;
        bool boolVal = false; //回傳的是不是bool表達式
        string left, right;
        vector<vector<int> > formulaElems;
};


void getTable(vector<vector<cell> > &table){

    string aLine;    
    char sep = ',';
    int i = 0, j = 0;

    while(getline(cin, aLine)){
        vector<cell> aRow;
        stringstream line_ss(aLine);
        string aCellContent;
        while(getline(line_ss, aCellContent, sep)){
            cell aCell(aCellContent, i, j);
            aRow.push_back(aCell);
            j++;
        }
        table.push_back(aRow);
        i++;
        j = 0;
    }
}

void initVisit(vector<vector<cell> > table, vector<vector<bool> > &visited){
    for(auto i = 0; i < table.size(); i++){
        vector<bool> rowVisited;
        for(auto j = 0; j < table[i].size(); j++){
            rowVisited.push_back(false);
        }
        visited.push_back(rowVisited);
    } 
}


int main(){

    vector<vector<cell> > table;
    vector<vector<bool> > visited;
    
    getTable(table); // 取得輸入
    // do eval
    initVisit(table, visited);
    for(auto i = 0; i < table.size(); i++){
        for(auto j = 0; j < table[i].size(); j++){
            if (table[i][j].getIsFormula()){
                table[i][j].evalExpression(table[i][j].getText(), table, visited);
                initVisit(table, visited);
            }
        }
    }

    // 檢查輸入結果
    for(auto i = 0; i < table.size(); i++){
        for(auto j = 0; j < table[i].size(); j++){
            cout << table[i][j].getOutput() << ",";
        }
        cout << endl;
    }
    return 0;
}



void cell::doCaculate(const string &content){
    int elem1 = 0, elem2 = 0;
    stringstream ss(content);
    char op;
    // 切割數字，operator
    ss >> elem1 >> op >> elem2;
    switch (op)
    {
    case ('+'):
        val = elem1 + elem2;
        break;
    case ('-'):
        val = elem1 - elem2;
        break;
    case ('*'):
        val = elem1 * elem2;
        break;
    case ('/'):
        if (elem2 == 0){isError = true;}
        else{val = elem1 / elem2;}
        break;
    case ('>'):
        isBool = true;
        boolVal = (elem1 > elem2);
        break;
    case ('<'):
        isBool = true;
        boolVal = (elem1 < elem2);
    default:
        break;
    }
    //記錄一下有沒有error
    if ((val > 10000000) | (val < -10000000)){
        isError = true;
    }
}


void cell::deComposeFormula(const string &content){
    //找到公式當中operator的位置(去除掉第一個位置不算)
    size_t op_pos = content.substr(1).find_first_of("+-*/><")+1;
    //找到公式當中第一個運算元
    string elem1 = content.substr(0, op_pos);
    vector<int> firstElem;
    if (isContainAlpha(elem1)){
    firstElem.push_back(elem1[0] - 'A');
    firstElem.push_back(stoi(elem1.substr(1)));        
    }
    else{firstElem.push_back(stoi(elem1));}
    formulaElems.push_back(firstElem);

    //找到公式當中第二運算元
    string elem2 = content.substr(op_pos+1);
    vector<int> secondElem;
    if (isContainAlpha(elem2)){
        secondElem.push_back(elem2[0] - 'A');
        secondElem.push_back(stoi(elem2.substr(1)));        
    }
    else{secondElem.push_back(stoi(elem2));}
    formulaElems.push_back(secondElem);
}

// 建構子
cell::cell(string content, int row, int col){
    this->row = row;
    this->col = col;
    if (content[0] == '#'){ // 如果是文字，直接去掉開頭存起來
        isText = true;
        content.erase(0, 1);
        text = content;
    }
    else if (content[0] == '='){ // 如果是公式
        content.erase(0, 1); // 先把等號移掉
        if (!isContainAlpha(content)){ // 如果裡面不包含字母，代表是純粹的運算公式
            doCaculate(content); // 計算運算結果
        }
        else{ // 紀錄是公式，把等號以後的部分記錄下來，等等再回頭處理
            isFormula = true;
            text = content;
        }
    }
    else { // 如果上面都不是，就是數字，如果溢位記錄一下error
        val = stoi(content);
        if ((val > 10000000) | (val < -10000000)){
            isError = true;
        }
    }
}
//取得輸出
string cell::getOutput(){
    string output; //如果值溢位，或者記錄到是error，就輸出error
    if ((isError) | (val > 10000000) | (val < -10000000)){
        output = "ERROR";
    }
    else if (isText){
        output = text;
    }
    else if (isBool){
        if (boolVal){output = "true";}
        else{output = "false";}
    }
    else{
        output = to_string(val);
    }
    return output;
}

int cell::evalTerm(const string &content, vector<vector<cell> > table, vector<vector<bool> > visit) {
    // string content = text;
    if (!isContainAlpha(content)) { // 如果項目是數字，直接轉換為整數並返回
        return stoi(content);
    } else { // 如果項目是表格中的單元格，先找到對應的 Cell 物件，然後評估其值
        int row = stoi(content.substr(1));
        int col = content[0] - 'A';
        // cout << visit.size() << endl;
        if (visit[row][col]){
            isError = true;
            return 0;
        }
        cell getCell(table[row][col]);
        visit[row][col] = true;
        if (getCell.getIsText()){
            getCell.isError = true;
        }
        if (getCell.getIsFormula()){
            getCell.evalExpression(getCell.getText(), table, visit);
        }
        return getCell.val;
    }
}


int cell::evalExpression(const string &content, vector<vector<cell> > table, vector<vector<bool> > visit) {
    // cout << "content1:" << content << endl;
    // 找到 content 字串中最後一個運算符號的位置
    size_t op_pos = content.substr(1).find_first_of("+-*/><")+1;
    // 如果沒有找到運算符號，表示只有一個項目，直接評估並返回其值
    if (op_pos == 0) {
        // cout << "content2:" << content << endl;
        return evalTerm(content, table, visit);
    } else {
        // 否則，分解成左右兩個部分，分別評估它們的值
        char op = content[op_pos]; // 取得運算符號
        string left = content.substr(0, op_pos); // 取得左側運算式字串
        string right = content.substr(op_pos+1); // 取得右側運算式字串
        int left_val = evalExpression(left, table, visit); // 評估左側運算式的值
        int right_val = evalExpression(right, table, visit); // 評估右側運算式的值
        cout << left_val << "," << right_val << endl;
        // 根據運算符號，計算左右兩側的值並返回
        switch (op) {
            isFormula = false;
            case '+':
                val = left_val + right_val;
                return left_val + right_val;
            case '-':
                val = left_val - right_val;
                return left_val - right_val;
            case '*':
                val = left_val * right_val;
                return left_val * right_val;
            case '/':
                cout << left_val << " "  << right_val << endl;
                if (right_val == 0) { // 檢查除數是否為零，若是則拋出異常
                    isError = true;
                    return 0;
                }
                else{
                    val = left_val / right_val;
                    return left_val / right_val; // 計算除法結果並返回
                }
            case '>':
                isBool = true;
                boolVal = left_val > right_val;
                return left_val > right_val;
            case '<':
                isBool = true;
                boolVal = left_val < right_val;
                return left_val < right_val;
        }
    }
}