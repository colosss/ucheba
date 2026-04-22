#include <iostream>
#include <cmath>

using namespace std;

int vvod(char* str,int &size){
    char a;
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
int lenght (char *str1){
    int n=0;
    for(;str1[n]!='\0'; n++)
    return n;
}

int zadanie(char*str1, char* str2, int l1, int l2, bool &f){
    int i=0, k=0;
    while (i<l1 && !f){
        if (k<l2){
            if (str1[i]==str2[k]){
                // cout<<"Simvol: "<<str1[i]<<" == "<<str2[k]<<endl;
                // cout<<"Pozition: i = "<<i<<" & k = "<<k<<endl;
                f=true;
                return k;
            }
            k++;
        }
        else{
            k=0;
            i++;
        }
    }
    return k;
    

}

int main(){
    int size = 256;
    char *str1=new char [size];
    char *str2= new char [size];
    bool f =false;
    cout<<"Vvedite pervyu stroky"<<endl;
    int l1=vvod(str1, size);
    cout<<str1<<endl;
    cout<<"Vvedite vtoryu stroky"<<endl;
    int l2=vvod(str2, size);
    cout<<str2<<endl;
    int a=0;
    a=zadanie(str1, str2, l1,l2,f);

    if (!f)cout<<"Stroki ne soderzat odinakovih simvolod"<<endl;
    else cout<<"Pozicia sovpodauhego simvola vo vtoroi stroke: "<<a<<endl;
    
    delete[] str1;
    delete[] str2;
}