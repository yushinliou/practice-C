#include <iostream>
#include <sstream>
#include <string>
# include <string.h>
#include <stdio.h>
# include <vector>
# include <algorithm>
using namespace std;

char *strtok(char *str, const char *delim);
char *strncpy( char *dest, const char *src, size_t count );

class Member{
    public:
        int id;
        int lastVisit;
        int avgMonthlyExp;
        char* name;

    void giveMem(string aName){

        int nameSize = 0;
        nameSize = aName.size();
        name = new char [nameSize];
        for (int i = 0; i < nameSize+1; i++){
            name[i] = aName[i];
        }
    }
        
    void freemem(){
        delete [] name;
    }
};

void getInfo(Member memberList[110], const int person_num){
    for (int i = 0; i < person_num; i++){
        cin >> memberList[i].lastVisit;
        memberList[i].id = i;
    }
    for (int i = 0; i < person_num; i++){
        cin >> memberList[i].avgMonthlyExp;
    }
}

int getOkmember(Member okMemberList[110], Member memberList[110], const int people_num){
    int ct = 0;
    for (int i = 0; i < people_num; i++){
        if (memberList[i].lastVisit <= 12){
            okMemberList[ct] = memberList[i];
            ct ++;
        }
    }
    return ct;
}

void getNameInput(Member memberList[110]){

    string totalName;

    vector<string> res;

    cin.ignore();
    getline(cin, totalName);

    // cin >> totalName;
	int n = totalName.size();
    char* str = new char[totalName.size() + 1];
	strcpy(str, totalName.c_str());
    string dem = ",";
    char* d = new char[dem.size()+1];
    strcpy(d, dem.c_str());

    char* p = strtok(str, d);
    int name_ct = 0;
    while(p){
        string tmp = p;
        memberList[name_ct].giveMem(tmp);
        res.push_back(tmp);
        p = strtok(NULL, d);
        name_ct ++;
        //cout << tmp << endl;
    }
    delete[] d;
}

void givecupon(Member memberList[110], Member cuponMember[11],
const int cupon_num, int ok_member_num){

    Member tmpMember;

    for (int i = 0; i < ok_member_num; i++){
        for (int j = i+1; j < ok_member_num; j++){
            tmpMember = memberList[i];
            if (memberList[i].lastVisit < memberList[j].lastVisit){
                memberList[i] = memberList[j];
                memberList[j] = tmpMember;
            }
            else if (memberList[i].lastVisit == memberList[j].lastVisit){
                if (memberList[i].avgMonthlyExp < memberList[j].avgMonthlyExp){
                    memberList[i] = memberList[j];
                    memberList[j] = tmpMember;
                }
            }
        }
    }

    int out_num = 0;

    if (ok_member_num >= cupon_num){
        out_num = cupon_num;
    }
    else{
        out_num = ok_member_num;
    }

    for (int i = 0; i < out_num; i++){
        if (i == out_num-1){
            cout << memberList[i].name;
        }
        else{
            cout << memberList[i].name << ",";
        }
    }
}

int main(){

    int people_num = 0, cupon_num = 0;
    int vaild_num = 0;
    Member memberList[110], okMemberList[110], cuponMember[11];

    // get input
    cin >> people_num >> cupon_num;
    getNameInput(memberList);
    getInfo(memberList, people_num);    // get money and last visit information
    vaild_num = getOkmember(okMemberList, memberList, people_num); // filt ok member

    // 如果沒有任何一個人符合資格，直接結束程式
    if (vaild_num == 0){
        return 0;
    }
    givecupon(okMemberList, cuponMember, cupon_num, vaild_num);

    return 0;
}