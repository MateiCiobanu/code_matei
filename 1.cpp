#include <iostream>
using namespace std;

int nr_turnuri(int n)
{
    int p=1;
    while(n)
    {
        p*=2;
        n--;
    }
    return p-1;
}

int nr_monede(int n)
{
    int copie = n;
    int p=2;
    while(n)
    {
        p*=2;
        n--;
    }
    return p-(copie+2);
}


int main()
{
    /*int bani=1;
    int turnuri=1;
    int nerezolvat=0;
    int curent=1, maxim=1, urmator;
    int n = 5;
    while(maxim<5)
    {
        urmator = 1;
        if(urmator == curent)
        {
            urmator++;
            nerezolvat = urmator;
        }
        if(urmator == nerezolvat)
            urmator++;

        if(urmator == maxim)
            urmator++;

        curent = urmator;

        if(curent > maxim)
            maxim = curent;
        turnuri++;
        bani+=curent;
    }
    cout << bani << " " <<turnuri;*/
    int n;
    cin >> n;
    cout << nr_turnuri(n);
    cout << endl;
    cout << nr_monede(n);
    return 0;
}
