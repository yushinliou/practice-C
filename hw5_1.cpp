# include <iostream>
using namespace std;
// compute combin

long long int combine(int N, int M){
    double ans = 0;
    double up = 0, down = 0;
    if (N == M){
        return 1;
    }
    for (int i = N; i > M; i--){
        if (i == N){
            up = N;
            down = 1;
            ans = up / down;
            // cout << "up" << up << " down" << down << endl;
            // cout << "ans " << ans << endl;
            // ans = (up / down) * ans;
        }
        else{
            up --;
            down++;
            ans *= (up / down);
            // cout << "up" << up << " down" << down << endl;
            // cout << "ans " << ans << endl;
        }
    }
    return ans;
}

int main()
{
    long long int n = 0, m = 0;
    cin >> n >> m;
    cout << combine(n, m);

    return 0;
}