# include <iostream>
# include <stdio.h>
# include <string.h>
# include <cstring>
# include <cstdlib>

const int MAX_MEMBER_NUM = 100;
const int MAX_NAME = 50;
const int MAX_DATE = 30;
const int MAX_NUMBER = 30;
const int STANDARD_YEAE = 1900;
const int AGEDATE[4] = {2022, 11, 1};

struct daytime
    {
        int year;
        int month;
        int date;
    };

using namespace std;
struct memberInfo{
    char birth[MAX_DATE];
    char number[MAX_NUMBER];
    char name[MAX_NAME];
    struct daytime birthdatetime;
    int age;
    int ageOk;
    int numberOk;
    int overallOk;
};
char *strtok(char *str, const char *delim);


void isOlder(const int tLimit, const int member_num, struct memberInfo member[]){

    for (int i = 0; i < member_num; i++){
        member[i].ageOk = 0; // 預設沒有符合年齡標準，往下檢查
        if(member[i].birthdatetime.year < (AGEDATE[0] - tLimit)){
            member[i].ageOk = 1;
        }
        else if (member[i].birthdatetime.year == (AGEDATE[0] - tLimit)){
            if (member[i].birthdatetime.month < AGEDATE[1]){
                member[i].ageOk = 1;
            }
            else if (member[i].birthdatetime.month == AGEDATE[1]){
                if (member[i].birthdatetime.date <= (AGEDATE[2]+1)){
                    member[i].ageOk = 1;
                }
            }
        }
    }
}

void numberOk(const int tLimit, const int member_num, const char conditX[10],
struct memberInfo member[]){
    char *number4;
    for (int i = 0; i < member_num; i++){
        number4 = strtok(member[i].number, "-");
        if (strcmp(number4, conditX) == 0){
            member[i].numberOk = 1;
        }
        else{
            member[i].numberOk = 0;
        }
    }
}

int overallOk(const int tLimit, const int member_num, const int target, const char conditX[10],
struct memberInfo member[]){
    int sum = 0;
    for (int i = 0; i < member_num; i++){
        member[i].overallOk = 0;
        if (target == 1){
            member[i].overallOk = member[i].ageOk;
        }
        else if (target == 2){
            member[i].overallOk = member[i].numberOk;
        }
        else if (target == 3){
            if ((member[i].ageOk == 1) | (member[i].numberOk == 1)){
                member[i].overallOk = 1;
            }
        }
        else if (target == 4){
            if ((member[i].ageOk == 1) & (member[i].numberOk == 1)){
                member[i].overallOk = 1;
            }
        }
        sum += member[i].overallOk;
    }
    return sum;
}

memberInfo findOldest(const int member_num, struct memberInfo member[]){
    memberInfo max_member;
    int ct = 0;
    for (int i = 0; i < member_num; i++){
        if (member[i].overallOk == 1){
            if (ct == 0){
                max_member = member[i]; // 用第一個人當基準
                ct++;
            }
            else{
                if (member[i].birthdatetime.year < max_member.birthdatetime.year){
                    max_member = member[i]; // 如果下一個人出生的年份更早，把它記錄下來
                }
                else if (member[i].birthdatetime.year == max_member.birthdatetime.year){ // 同年出生的話
                    if (member[i].birthdatetime.month < max_member.birthdatetime.month){
                        max_member = member[i]; // 如果下一個人出生月份更小，把它記錄下來
                    }
                    else if (member[i].birthdatetime.month == max_member.birthdatetime.month){ // 又同月出生的話
                        if (member[i].birthdatetime.date < max_member.birthdatetime.date){ // 如果下一個人出生日期更小，把它記錄下來
                            max_member = member[i];
                        }
                        else if (member[i].birthdatetime.date == max_member.birthdatetime.date){ // 如果又同一天出生
                            if (member[i].name[0] < max_member.name[0]){
                                max_member = member[i];
                            }
                        }
                    }
                }
            }
        }
    }
    return max_member;
}

int main(void){

    int target = 0, member_num = 0, tLimit = 0;
    char conditX[10];
    char original[MAX_MEMBER_NUM][MAX_NAME];
    struct memberInfo member[MAX_MEMBER_NUM]; 
    
    // 取得輸入
    cin >> member_num >> target >> tLimit;
    cin.ignore();
    cin.getline(conditX, 10);
    for (int i = 0; i < member_num; i++){
        cin.getline(original[i], 100);
    }

    const char* d = ","; // 字串切割符號
    char *p; // 用來儲存切割之後的字串

    char tmp[50]; 

    // 進一步把生日字串切割成年月日
    // const char* data_d = "/"; // 字串切割符號
    char *word;
    for (int i = 0; i < member_num; i++){
        // name
        word = strtok(original[i], ",");
        strcpy(member[i].name, word);
        // birth
        word = strtok(NULL, ",");
        strcpy(member[i].birth, word);
        // number
        // cout << word << endl;
        word = strtok(NULL, ",");
        strcpy(member[i].number, word);
        // cout << word << endl;
    }

    // 分別儲存出生年月日
    for (int i = 0; i < member_num; i++){
        word = strtok(member[i].birth, "/");
        member[i].birthdatetime.year = atoi(word);
        word = strtok(NULL, "/");
        member[i].birthdatetime.month = atoi(word);
        word = strtok(NULL, "/");
        member[i].birthdatetime.date = atoi(word);
    }

    // 檢查歲數是否符合限制
    isOlder(tLimit, member_num, member);
    // 檢查電話號碼是否符合限制
    numberOk(tLimit, member_num, conditX, member);

    int oksum = overallOk(tLimit, member_num, target, conditX, member);
    if (oksum == 0){
        cout << 0;
    }
    else{
        memberInfo max_member = findOldest(member_num, member);
        cout << max_member.name << "," << oksum;
    }
    return 0;
}