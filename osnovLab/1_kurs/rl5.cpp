#include <iostream>
#include <cmath>
#include <cstdlib>

using namespace std;

int vvod_int (){
    int x1 =0;
    cin>>x1;
    while (cin.fail() && x1<0){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout<<"Неправильно введено значение, повторите ввод\n ";
        cin>>x1;
    }
    return x1;
}
double vvod_double (){
    double x2 =0;
    cin>>x2;
    while (cin.fail()){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout<<"Неправильно введено значение, повторите ввод\n ";
        cin>>x2;
    }
    return x2;
}

int collich(int n, double m[]){
    int o=0, oshib=1, poz_b=n+1, poz_a=poz_b+1, co=0;
    double a=0, b=0;
    while (poz_a>poz_b or poz_a>n or poz_b>n){
        cout<<"Введите а"<<endl;
        a=vvod_double();
        cout<<"Введите b"<<endl;
        b=vvod_double();
        for (int i=0; i<n; i++){
            if (m[i]==a){
                poz_a=i;
                break;
            } 

        }
        for(int i=0; i<n; i++){
            if (m[i]==b) poz_b=i;
        }
        if (poz_a<poz_b and poz_a<=n and poz_b<=n) break;
        
        cout<<"Ошибка! Введите значения заново"<<endl;
        poz_b=n+1;
        poz_a=poz_b+1;
    }
    return poz_b-poz_a+1;
}

double sum_znach (int n, double m[], bool &flag){
    double sum =0, max=m[0];
    int count=0;
    for (int i=0;i<n;i++){
        if (m[i] > max){
            count = i;
        }
    }
    if (count >=n-1){
        flag =true;
    }
    for (int i=count+1; i<n;++i)sum+=m[i];
    return sum;
}

void perevorot(int n, double m_arr[]){
    int a=0;
    double m_1=0;
    while (a<n-1){
        if ((m_arr[a] * m_arr[a]) < (m_arr[a+1] * m_arr[a+1])){
            m_1=m_arr[a];
            m_arr[a]=m_arr[a+1];
            m_arr[a+1]=m_1;
            a=0;
        }
        else{
            a++;
        }     
    }
    cout<<""<<endl;
    for (int i=0; i<n; i++){
        cout<<m_arr[i]<<endl;
    }
    cout<<""<<endl;
}

int main(){
    const int n=5;
    int co=0, sum=0;
    double m[5], m_arr[5];
    bool flag=false;

    for (int i=0; i<n; i++){
        cout<<"Введите элемент "<< i+1<<endl;
        m[i]=vvod_double();
        m_arr[i]=m[i];
        
    }
    co=collich(n, m);
    sum=sum_znach(n, m,flag);
    cout<<"Значений: " << co <<endl;

    if (flag==true){
        cout<<"Максимальное значение масива является последним элементом масива"<<endl;
    }
    else{
        cout<<"Сумма: "<<sum<<endl;
    }

    perevorot(n,m_arr);
    
}