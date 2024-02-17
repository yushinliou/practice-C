# include <iostream>
using namespace std;
int main()
{
    int i = 0;
    // member = how many people in the team
    // limit = the high limit
    int member = 0, limit = 0;
    // ct = counter, to record how many people higher than limit
    int ct = 0;
    // member's high
    int high[20] = {0};
    cin >> member >> limit;
    // if there are x people in the group, 
    for (i = 0 ; i < member ; i = i + 1)
    {
        cin >> high[i];
        if (high[i] >= (limit * 12))
        {
            ct++;
        }
    }
    cout << ct;
    return 0;
}