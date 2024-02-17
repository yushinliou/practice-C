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
    int high[100] = {0}, position[100] = {0};
    cin >> member >> limit;

    // read member's high
    for (i = 0; i < member; i ++){
        cin >> high[i];
    }
    // read member's position
    for (i = 0; i < member; i ++){
        cin >> position[i];
    }

    // if there are x people in the group
    for (i = 0 ; i < member ; i = i + 1)
    {
        // deal by different position
        switch(position[i])
        {
            // if it is position 1
            case 1:
            // and he/she is higher thant limit
            if (high[i] >= (limit * 12))
                ct[0] ++; // reord it
            break;
        }
        switch(position[i])
        {
            case 2:
            if (high[i] >= (limit * 12))
                ct[1] ++;
            break;
        }
        switch(position[i])
        {
            case 3:
            if (high[i] >= (limit * 12))
                ct[2] ++;
            break;
        }
    }
    // cout anawer
    for (i = 0; i < 2; i++)
        cout << ct[i] << ",";
    cout << ct[2];
    return 0;
}