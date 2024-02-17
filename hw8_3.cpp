# include <iostream>
using namespace std;

struct Purchase
{
    int itemID;
    int quantity;
    void setPurchase(int ID, int qtu);
};

class Member
{
    private:
        int id;
        int lastVisit;
        int avgMonthlyExp;
        char* name;
        Purchase* purchases;
    public:
        Member();
        Member(int idx, int last, int avg, char* n, Purchase* purch);
        ~Member();
        void makePurchase(int ID, int qty);
};


int main(){

    char aName[] = "rich";
    Purchase some[2];

    some[0].setPurchase(1, 20);
    some[1].setPurchase(1, 20);

    Member m1(0, 12, 11, aName, some);


    int people_num = 0, cupon_num = 0, ;
    int vaild_num = 0;

    Member memberList[110];

    // get input
    cin >> people_num >> cupon_num;
    getNameInput(memberList);
    getInfo(memberList, people_num);    // get money and last visit information
    vaild_num = getOkmember(okMemberList, memberList, people_num); // filt ok member

    // 如果沒有任何一個人符合資格，直接結束程式
    if (vaild_num == 0){
        return 0;
    }


    return 0;
}