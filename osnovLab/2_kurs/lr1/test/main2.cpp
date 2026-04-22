#include <iostream>
#include <iomanip>
const int colls=5;
const int rows =5;
using namespace std;
double vvod(){
    double x=0;
    cin>>x;
    return x;
}

bool raschet (double s[colls][rows]){
    int s1=0;
    for (int i=0; i<colls; i++){
        for (int j=0; j<rows; j++){
            s1+= s[i][j] >= 0 ? 1 : -1;
        }
    }
    if (s1>0){
        return 1;
    }
    else{
        return 0;
    }
}

void vivod(char l,bool a, double s[colls][rows]){
    if (l =='a'){
        cout<<"A = "<<a<<endl;
        cout<< "S: "<<endl;
    }
    else{
        cout<<"B = "<<a<<endl;
        cout<<"X: "<<endl;
    }
    for (int i=0; i<colls; i++){
        for (int j=0; j<rows; j++){
            cout<<setw(6)<< s[i][j]<<" ";
        }
        cout<<endl;
    }
    
}


int main(){
    double s[colls][rows];
    double x[colls][rows];
    bool a=0;
    bool b=0;
    for (int i=0; i<colls; i++){
        for (int j=0; j<rows; j++){
            cout<<"Vvedite znachenir S["<<i<<"]["<<j<<"]"<<endl;
            s[i][j]=vvod();
            cout<<"Vvedite znachenir X["<<i<<"]["<<j<<"]"<<endl;
            x[i][j]=vvod();
        }
    }
    a=raschet(s);
    b=raschet(x);
    vivod('a', a, s);
    vivod('b', b, x);

}