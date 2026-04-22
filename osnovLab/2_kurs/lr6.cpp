#include "lr6.hpp"

int Massiv::getN(){
    return n;
}
void Massiv::print(){
    cout<<"Massiv "<<name<<" iz n = "<<n<<":"<<endl;
    cout<<"[";
    for(int i=0; i<n; i++){
        cout<<" "<<m[i];
        if(i<n-1)cout<<",";
        else cout<<" ]"<<endl;
    }
    
}

void Massiv::zapolnenie_mass(){
    for(int i=0; i<n;i++){
        m[i] = rand()%100 + (rand()%100)/100.0;
        if (rand()%2==0) m[i]*=-1;
    }
}
void Massiv::set_name(string _name){
    name=_name;
}

void Massiv::massiv_1(){
    for (int i=0;i<n;i++){
        m[i]=1;
    }
}

double Massiv::get_element(int index){
    if (index<0 || index>=n){
        throw error_invalid_index();
    }
    return m[index];
}

void Massiv::func1(){
    double sum=0;
    for(int i=0;i<n;i++) if(i%2!=0) sum+=m[i];
    cout<<"Sum massive "<<name<<" of odd numbers : "<<sum<<endl;
}

void Massiv::func2(){
    double sum=0;
    int index1=n+1;
    int index2=n+1;
    for(int i=0;i<n;i++){
        if(m[i]<0){index1=i; break;}
    }
    if (index1==n+1) throw error_no_negative();
    for(int i=n; i>=0;i--){
        if(m[i]<0){
            index2=i;
            break;
        }
    }
    if (index2==index1) throw error("Only one negative element");
    for(int i=index1+1;i<index2;i++){
        sum+=m[i];
    }
    cout<<"Sum massive "<<name<<" of elements between negative numbers : "<<sum<<endl;}

void Massiv::primitive_fill(){
    for(int i=0;i<n;i++){
        m[i]=i * (i%2==0 ? -1 : 1);
    }
}

void Massiv::set_element(int index, double a){
    m[index]=a;
}

int main(){
    srand(time(NULL));

    try{
        Massiv m1;
        m1.set_name("m1");
        m1.print();
        m1.func1();
        m1.func2();
    }
    catch(const error &err){
        cout<<"Massiv m1 error: "<<err.what()<<endl;
    }
    catch (const error_invalid_index &err){
        cout<<"Massiv m1 error: "<<err.what()<<endl;
    }
    catch(const error_no_negative &err){
        cout<<"Massiv m1 error: "<<err.what()<<endl;
    }
    catch(const exception){
        cout<<"Somthing wrong..."<<endl;
    }

    cout<<endl<<"---------------------"<<endl<<endl;

    try{
        Massiv m2(3, "m2");
        m2.print();
        m2.func1();
        m2.func2();
    }
    catch(const error &err){
        cout<<"Massiv m2 error: "<<err.what()<<endl;
    }
    catch (const error_invalid_index &err){
        cout<<"Massiv m2 error: "<<err.what()<<endl;
    }
    catch(const error_no_negative &err){
        cout<<"Massiv m2 error: "<<err.what()<<endl;
    }
    catch(const exception){
        cout<<"Somthing wrong..."<<endl;
    }

    cout<<endl<<"---------------------"<<endl<<endl;

    try{
        Massiv m3(15, "m3");
        m3.massiv_1();
        m3.print();
        m3.func1();
        m3.func2();
    }
    catch(const error &err){
        cout<<"Massiv m3 error: "<<err.what()<<endl;
    }
    catch(const error_no_negative &err){
        cout<<"Massiv m3 error: "<<err.what()<<endl;
    }
    catch (const error_invalid_index &err){
        cout<<"Massiv m3 error: "<<err.what()<<endl;
    }
    catch(const exception){
        cout<<"Somthing wrong..."<<endl;
    }
    
    cout<<endl<<"---------------------"<<endl<<endl;

    try{
        Massiv m4(12, "m4");
        m4.primitive_fill();
        m4.print();
        m4.func1();
        m4.func2();
    }
    catch(const error &err){
        cout<<"Massiv m4 error: "<<err.what()<<endl;
    }

    catch (const error_invalid_index &err){
        cout<<"Massiv m4 error: "<<err.what()<<endl;
    }
    catch(const error_no_negative &err){
        cout<<"Massiv m4 error: "<<err.what()<<endl;
    }
    catch(const exception){
        cout<<"Somthing wrong..."<<endl;
    }

    cout<<endl<<"---------------------"<<endl<<endl;

    try{
        Massiv m5(12, "m4");
        m5.massiv_1();
        m5.set_element(1,-1);
        m5.print();
        m5.func1();
        m5.func2();
    }
    catch(const error &err){
        cout<<"Massiv m5 error: "<<err.what()<<endl;
    }

    catch (const error_invalid_index &err){
        cout<<"Massiv m5 error: "<<err.what()<<endl;
    }
    catch(const error_no_negative &err){
        cout<<"Massiv m5 error: "<<err.what()<<endl;
    }
    catch(const exception){
        cout<<"Somthing wrong..."<<endl;
    }
    
    return 0;
}