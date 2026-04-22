#include <iostream>

using namespace std;
double vvod(){
    int x=0;
    cin>>x;
    return x;
}

int main(){
    double s[5][5];
    double x[5][5];
    double s1=0;
    double x1=0;
    bool a=0;
    bool b=0;
    for (int i=0; i<=5; i++){
        for (int j=0; j<=5; j++){
            cout<<"Vvedite znachenir S["<<i<<"]["<<j<<"]"<<endl;
            s[i][j]=vvod();
            cout<<"Vvedite znachenir X["<<i<<"]["<<j<<"]"<<endl;
            x[i][j]=vvod();
        }
    }

    for (int i=0; i<=5; i++){
        for (int j=0; j<=5; j++){
            s1+=s[i][j];
            x1+=x[i][j];
        }
    }
    if (s1>0)a=1;
    if (x1>0)b=1;
    cout<<"A = "<<a<<endl<<"B = "<<b<<endl;
}