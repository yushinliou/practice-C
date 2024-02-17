# include <iostream>
using namespace std;
int main()
{
    int i = 0;
    // member = how many people in the team
    // limit = the high limit
    int member = 0, limit = 0;
    // ct = counter, to record how many people higher than limit
    int ct[3] = {0};
    // member's high
    int high = 0, position = 0;
    cin >> member >> limit;

    // if there are x people in the group, 
    for (i = 0 ; i < member ; i = i + 1)
    {
        cin >> high >> position;
        switch(position)
        {
            case 1:
            if (high >= (limit * 12))
            {
                ct[0] ++;
            }
            break;
        }
        switch(position)
        {
            case 2:
            if (high >= (limit * 12))
            {
                ct[1] ++;
            }
            break;
        }
        switch(position)
        {
            case 3:
            if (high >= (limit * 12))
            {
                ct[2] ++;
            }
            break;
        }
    }
    for (i = 0; i < 2; i++)
    {
        cout << ct[i] << ",";
    }
    cout << ct[2];
    return 0;
}