#include <iostream>
#include <cmath>

using namespace std;

int vvod(char* str,int &size){
    char a='0';
    int n=0;
    for(;cin.get(a) and a!='\n';n++){
        if(n>=size-1){
            size*=2;
            char* str_i = new char[size];
            for(int i=0;i<n;i++){
                str_i[i]=str[i];
            }
            delete []str;
            str=str_i;
        }
        str[n]=a;
    }
    str[n]='\0';
    return n;
}


void vvivod(char* arr){
    cout<<arr;
    cout<<endl;
}

int main(){
    int size = 256;
    char *str1=new char [size];
    char *str2= new char [size];
    cout<<"Vvedite pervyu stroky"<<endl;
    int l1=vvod(str1, size);
    cout<<str1<<endl;
    cout<<"Vvedite vtoryu stroky"<<endl;
    int l2=vvod(str2, size);
    vvivod(str2);
    int i=0, k=0;
    while (i<l1){
        if (str1[i]==str2[k]){
            cout<<"Simvol: "<<str1[i]<<" == "<<str2[k]<<endl;
            cout<<"Pozition: i = "<<i<<" & k = "<<k<<endl;
            break;
        }
        if (k<l2){
            k++;
        }
        else{
            if (i>=l1-1){
                cout<<"Stroki ne soderzat odinakovih simvolod"<<endl;
            }
            k=0;
            i++;
        }
        
    }
    
    delete[] str1;
    delete[] str2;
}