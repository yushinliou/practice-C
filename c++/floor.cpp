# include <iostream>
# include <iomanip>
#include <cmath>
#include <math.h>
using namespace std;

int myRand(int r, int a=75, int c=74, int m=32768) {

    return (a * r + c) % m; 
}


int main(){

    float a = 75, c = 74, m = 32768;
    int s = 0, k = 0;
    float x = 0, y = 0;
    float convert_x = 0, convert_y = 0;

    cin >> s >> k;

    int r = s;

    for(int i = 0; i < k; i++) {

        x = myRand(r, a, c, m);
        r = x;
        y = myRand(r, a, c, m);
        r = y;

        convert_x = (-1 + (2 * (x / 32767))) * 100;
        convert_y = (-1 + (2 * (y / 32767))) * 100;

        if (convert_x < 0){
            cout << "-" << floor(-convert_x) << ",";
        }
        else{
            cout << floor(convert_x) << ",";
        }

        if (convert_y < 0){
            cout << "-" << floor(-convert_y) << endl;
        }
        else{
            cout << floor(convert_y) << endl;
        }        
    }

    return 0;
}