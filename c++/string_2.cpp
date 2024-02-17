# include <iostream>
# include <string.h>
# include <ctype.h>
# include <vector>
using namespace std;

int isSpecial(char check){
    int isSpecial = 0;
    char assign[7] = {'.', ',', ':', '!', '?', ';', ')'};
    for (int i = 0; i < strlen(assign); i++){
        if (check == assign[i]){
            isSpecial = 1;
            break;
        }
    }
    return isSpecial;
}

int isPunct(char check){
    int isPunct = 0;
    char assign[9] = {'.', ',', ':', '!', '?', ';', ')', '(', '-'};
    for (int i = 0; i < strlen(assign); i++){
        if (check == assign[i]){
            isPunct = 1;
            break;
        }
    }
    return isPunct;
}

void dropSpace(const char ary[500], const int n, vector <char> &oneSpace){
    int ct = 0;
    int spaceCt = 0;
    for (int i = 0; i < n; i++){
        if (i == 0){
            oneSpace.push_back(ary[i]);
        }
        else if (ary[i] != ' '){
            oneSpace.push_back(ary[i]);
            // ct++;
        }
        else if ((ary[i] == ' ') and (ary[i-1] != ' ')){
            oneSpace.push_back(ary[i]);
            // ct++;
        }
    }
}

void dropPunctSpace(vector <char> &noPunctSpace, vector <char> oneSpace){
    for (int i = 0; i < oneSpace.size(); i++){
        if (oneSpace[i] == ' '){
            if (isPunct(oneSpace[i-1]) or isPunct(oneSpace[i+1])){
                continue;
            }
            else{
                noPunctSpace.push_back(oneSpace[i]);
            }
        }
        else{
            noPunctSpace.push_back(oneSpace[i]);
        }

    }
}

void addSpace(vector <char> &finalString, vector <char> noPunctSpace){
    // 在「(」前面加一個空白
    for (int i = 0; i < noPunctSpace.size(); i++){
        if ( i == noPunctSpace.size()-1 ){ // 如果是最後一個字符，直接存
            finalString.push_back(noPunctSpace[i]);
        }
        else if (noPunctSpace[i] == '('){ // 如果是「(」就在前面加一個空白
            finalString.push_back(' ');
            finalString.push_back(noPunctSpace[i]);
        }
        else if (isSpecial(noPunctSpace[i])){ // 如果是指定字符
            if (isPunct(noPunctSpace[i+1]) != 1){ // 如果後面不是標點符號
                finalString.push_back(noPunctSpace[i]); // 寫符號再加上空白
                finalString.push_back(' ');
            }
            else{
                finalString.push_back(noPunctSpace[i]); // 如果是標點符號，就直接寫不加上空白
            }
        }
        else{
            finalString.push_back(noPunctSpace[i]);
        }
    }
}

int isspace(int c);
int ispunct(int c);

int main()
{
    char str[500] = {'0'};
    vector <char> OneSpace;
    vector <char> NoPunctSpace;
    vector <char> finalString;

    cin.get(str, 200); // 從鍵盤讀取一行字串
    dropSpace(str, strlen(str), OneSpace); // 先移除掉所有的連續空白
    // cout << endl << "OneSpace" << endl;
    // 確認移除所有連續空白的結果
    /*for (int i = 0; i < OneSpace.size(); i++){
        cout << OneSpace[i];
    }*/
    // cout << endl << "no Punct" << endl;
    // 接著移除掉所有標點符號前後的空白
    dropPunctSpace(NoPunctSpace, OneSpace);
    /*for (int i = 0; i < NoPunctSpace.size(); i++){
        cout << NoPunctSpace[i] << NoPunctSpace[i+1] << endl;
    }*/

    // 接著在需要的地方插入空白
    addSpace(finalString, NoPunctSpace);
    // cout << endl << "final:" << endl;
    for (int i = 0; i < finalString.size(); i++){
        cout << finalString[i];
    }
    return 0;
}