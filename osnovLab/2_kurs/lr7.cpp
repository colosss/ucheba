#include "lr7.hpp"

template <typename T>
void Massiv<T>::print(){
        for (int i=data.size()-1;i>=0;--i){
            cout << double(data[i])<<setw(7);
        }
        cout << endl;
    }

template <typename T>
void rand_massiv(vector<T> & data, int const size){
    for (int i=0;i<size;++i){
            T sign = (rand()%2) ? 1 : -1;
            data[i]=((rand()%10)+(T(rand()%10))/10) * sign;
            // data.push_back( (rand()%10) * sign );
        }
}
template <typename T>
double Massiv<T>::func1(){
    double max=double(data[0]);
    // for (int i=0;i<size;++i){
    //     if(double(data[i])>max){
    //         max=double(data[i]);
    //     }
    // }

    max = *max_element(data.begin(), data.end());
    return max;
}

template <typename T>
void Massiv<T>::func2(){
    double k= func1();
    for (int i=0;i<size;++i){
        data[i]=data[i]+k;
    }
}

template <typename T>
void Massiv<T>::func3(){
    int i=0;
    double k=data[0];
    while (i!=size-1){
        if((data[i]*data[i])<(data[i+1]*data[i+1])){
            k=data[i];
            data[i]=data[i+1];
            data[i+1]=k;
            i=0;
        }
        else i++;
    }
}

int main(){
    srand(time(NULL));
    int size=10-(-10);
    vector<int> vec(size);
    rand_massiv(vec,size);
    Massiv<int> m = Massiv(vec,size);

    cout<<"First massiv:"<<endl;
    m.print();
    cout<<"Max element = "<<m.func1()<<endl;
    m.func3();
    cout<<"After func3 sort absolut massiv:"<<endl;
    m.print();
    m.func2();
    cout<<"After func2 elements plus max:"<<endl;
    m.print();

    cout<<endl<<"--------------------------------"<<endl;

    cout<<endl<<"Second massiv:"<<endl;

    vector<double> vec1(size);
    rand_massiv(vec1,size);
    Massiv<double> m1 = Massiv(vec1,size);
    m1.print();
    cout<<"Max element = "<<m1.func1()<<endl;
    m1.func3();
    cout<<"After func3 sort absolut massiv:"<<endl;
    m1.print();
    m1.func2();
    cout<<"After func2 elements plus max:"<<endl;
    m1.print();


    cout<<endl<<"--------------------------------"<<endl;


    cout<<endl<<"Third massiv:"<<endl;

    vector<char> vec2(size);
    rand_massiv(vec2,size);
    Massiv<char> m2 = Massiv(vec2,size);
    m2.print();
    cout<<"Max element = "<<m2.func1()<<endl;
    m2.func3();
    cout<<"After func3 sort absolut massiv:"<<endl;
    m2.print();
    m2.func2();
    cout<<"After func2 elements plus max:"<<endl;
    m2.print();
    cout<<endl;

}