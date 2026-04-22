#include <iostream>
#include <stdlib.h>
#include <cstdlib>

using namespace std;

void PrintList(int *m, int n){
    for (int i=0; i<=n-1;i++){
        cout<<m[i]<<"   ";
        if (i!=0 && i%25==0){
            cout<<endl;
        }
    }
}

void sort(int *m1, int n, int &s, int &p){
    int count=0;
    int num=0;
    int i=0;
    int a=0;
    while(true){
        if(count<=n-1){
            if(m1[count]<m1[num]){
                num=count;
                s++;
            }
            count++;
        }
        else{
            a=m1[i];
            m1[i]=m1[num];
            m1[num]=a;
            i++;
            num=i;
            count=i;
            p++;
        }
        if(i==n-1) break;
    }
}

int main(){
    int count_srav=0;
    int count_perest=0;
    int n=100;
    cout<<"Vvedite collichestvo elementov masiva: ";
    cin>>n;
    cout<<endl;
    int m[n];
    int m1[n];
    
    for (int i=0; i<=n-1; i++){
        m[i]=rand() % 100;
        m1[i]=m[i];
        // m[i]=i;
    }
    sort(m1,n, count_srav, count_perest);
    cout<<"Ishodniy massiv: "<<endl;
    PrintList(m, n);
    cout<<endl;
    cout<<"Otsortirovanniy massiv: "<<endl;
    PrintList(m1,n);
    cout<<endl;
    cout<<"Kollichestvo sravneniy: "<<count_srav<<endl;
    cout<<"Kollichestvo perestanovok: "<<count_perest<<endl;
}