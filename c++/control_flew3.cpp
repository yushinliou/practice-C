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
    // the highest member in the group
    int highest_id_1 = 0, highest_id_2 = 0, highest_id_3 = 0;
    int highest_1 = 0, highest_2 = 0, highest_3 = 0;

    // read member and high limit
    cin >> member >> limit;
    // if there are x people in the group, 
    for (i = 0 ; i < member ; i = i + 1)
    {
        // read person's high and his/her position
        cin >> high >> position;
        // deal with different position
        switch(position)
        {
            // if it is position `
            case 1:
            // high is higher than so far highest one in position one
            if (high > highest_1)
            {
                // record the new highest
                highest_1 = high;
                // record this people's id
                highest_id_1 = i + 1;
            }
            break;
        }
        switch(position)
        {
            case 2:
            if (high > highest_2)
            {
                highest_2 = high;
                highest_id_2 = i + 1;
            }
            break;
        }
        switch(position)
        {
            case 3:
            if (high > highest_3)
            {
                highest_3 = high;
                highest_id_3 = i + 1;
            }
            break;
        }
    }
    cout << highest_id_1 << "," << highest_id_2 << ',' << highest_id_3;
    return 0;
}