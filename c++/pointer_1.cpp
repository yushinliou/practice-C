#include <iostream>
#include <set>
using namespace std;

// find max prefer value in a given set
void findMaxPrefer(std::set<int> Toy, std::set<int> Guy,
                   int Prefer[30][30], int *max_guy, int *max_toy)
{
    int max_prefer = 0;
    //int j = *max_toy, i = *max_guy;
    set<int>::iterator iter, jter;

    for (iter = Guy.begin(); iter != Guy.end(); iter++){
        for (jter = Toy.begin(); jter!= Toy.end(); jter++){
            // cout << Prefer[*iter][*jter] << " ";
            if ((iter == Guy.begin()) & (jter == Toy.begin())){
                *max_guy = *iter;
                *max_toy = *jter;
                max_prefer = Prefer[*iter][*jter];
            }
            else if(Prefer[*iter][*jter] >= max_prefer){
                if(Prefer[*iter][*jter] == max_prefer){
                    if (*jter <= *max_toy){
                        if (*jter == *max_toy){
                            if(*iter < *max_guy){
                                    *max_guy = *iter;
                                    *max_toy = *jter;
                                    max_prefer = Prefer[*iter][*jter];
                                
                            }
                        }
                        else{
                            *max_guy = *iter;
                            *max_toy = *jter;
                            max_prefer = Prefer[*iter][*jter];
                        }
                    }
                }
                else{
                    *max_guy = *iter;
                    *max_toy = *jter;
                    max_prefer = Prefer[*iter][*jter];
                }
            }
        }
        //cout << endl;
    }
}

int giveToy(std::set<int> Toy, std::set<int> Guy,
int Prefer[30][30], const int guy_num){

    int max_guy = 0, max_toy = 0;
    int p_sum = 0;
    set<int>::iterator iter, jter;

    for (int i = 0; i < guy_num; i++){
        // cout << "i:" << i << endl;
        for (iter = Guy.begin(); iter != Guy.end(); iter++){
            // cout << *iter << " ";
        }
        //cout << endl;
        for (iter = Toy.begin(); iter != Toy.end(); iter++){
            // cout << *iter << " ";
        }
        // cout << endl;
        findMaxPrefer(Toy, Guy, Prefer, &max_guy, &max_toy);
        // cout << "guy, toy:" << max_guy << " " << max_toy << endl;
        // cout << "max Prefer:" << Prefer[max_guy][max_toy] << endl;
        Toy.erase(max_toy);
        Guy.erase(max_guy);
        p_sum += Prefer[max_guy][max_toy];
    }

    return p_sum;
}

// Driver code
int main()
{
    int toy_num = 0, guy_num = 0;
    int prefer[30][30] = {0};

    std:: set<int> toy, guy;

    cin >> toy_num >> guy_num;

    for (int i = 0;i < guy_num; i++){
        for (int j = 0; j < toy_num; j++){
            cin >> prefer[i][j];
        }
    }

    for (int i = 0; i < toy_num; i++){
        toy.insert(i);
    }
    for (int i = 0; i < guy_num; i++){
        guy.insert(i);
    }
    cout << giveToy(toy, guy, prefer, guy_num);

	return 0;
}



