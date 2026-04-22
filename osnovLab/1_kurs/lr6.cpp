// // Для обнаружения утечек памяти
// #define _CRTDBG_MAP_ALLOC
// #include <stdlib.h>
// #include <crtdbg.h>

// #ifdef _DEBUG
// #ifndef DBG_NEW
// #define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// #define newDBG_NEW
// #endif
// #endif

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <stdlib.h>

using namespace std;

int vvod_int(){
    int x=0;
    cin>>x;
    while (cin.fail()){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout<<"Vvedite znachenie zanovo"<<endl;
        cin>>x;

    }
    return x;
}

void sdvig_vpravo(int j, int l, int** m){
    int k_1=m[0][0];
    for (int i = 0; i < j; i++) {
        int k_1 = m[i][l - 1];
        for (int k = l - 1; k > 0; k--) {
            m[i][k] = m[i][k - 1];
        }
        m[i][0] = k_1;
    }
}

void sdvig_vniz(int j, int l, int** m) {
    int k_1=m[0][0];
    for (int k = 0; k < l; k++) {
        k_1 = m[j - 1][k];
        for (int i = j - 1; i > 0; i--) {
            m[i][k] = m[i - 1][k];
        }
        m[0][k] = k_1;
    }
}




int main (){
    
    int j=5, l=10,n=0, a=0, b=0, colichestvo=0, znach=0, i_1=0, k_1=0, m_1=0;
    int **m=new int* [j];
    for (int i = 0; i < j; i++){
        m[i]=new int [l];
    }

    bool flag=false;

    for (int i=0; i<j;i++){
        for(int k=0;k<l;k++){
            m[i][k]=0;
            cout<<m[i][k]<<" ";
        }
        cout<<""<<endl;
    }

    cout<<endl<<"Vvedite scolko znacheniy vi hotite vvesti v masiv"<<endl;
    colichestvo=vvod_int();
    while (colichestvo){
        cout<<"Vedte poziciu po strochke"<<endl;
        a=vvod_int();
        cout<<"Vedte poziciu po stolbcu"<<endl;
        b=vvod_int();
        cout<<"Vedte znachenie"<<endl;
        znach=vvod_int();
        
        if (a>j || b>l){
            continue;
        }
        else{
            m[a][b]=znach;
            colichestvo--;
        }
    }

    cout<<"Vvedite (0) esli hotite vipolnit` sdvig vpravo, ili vvedite (1) esli hotite vipolnit` sdig vniz"<<endl;
    cin>>flag;
    while (cin.fail()){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout<<"Vvedite znachenie zanovo"<<endl;
        cin>>flag;
        
    }
    cout<<"Vvedite na skol`ko vi hotite vipolnit` sdvig"<<endl;
    n=vvod_int();

    cout<<""<<endl;

    for (int i=0; i<j;i++){
        for(int k=0;k<l;k++){
            // m[i][k]=0;
            cout<<m[i][k]<<" ";
        }
        cout<<""<<endl;
    }

    cout<<""<<endl;
    
    for (int i=0;i<n;i++){
        if (!flag)sdvig_vpravo (j, l, m);
        else sdvig_vniz(j,l,m);
    }
    


    for (int i=0; i<j;i++){
        for(int k=0;k<l;k++){
            // m[i][k]=0;
            cout<<m[i][k]<<" ";
        }
        cout<<""<<endl;
    }

    cout<<" "<<endl;

    
    //Ydalenie massiva

    for (int i=0; i<j;i++){
        delete[] m[i];
    }

    delete[] m;

    // // Для обнаружения утечек памяти
    // _CrtSetReportMode( _CRT_WARN, _CRTDBG_MODE_FILE );
    // _CrtSetReportFile( _CRT_WARN, _CRTDBG_FILE_STDOUT );
    // _CrtSetReportMode( _CRT_ERROR, _CRTDBG_MODE_FILE );
    // _CrtSetReportFile( _CRT_ERROR, _CRTDBG_FILE_STDOUT );
    // _CrtSetReportMode( _CRT_ASSERT, _CRTDBG_MODE_FILE );
    // _CrtSetReportFile( _CRT_ASSERT, _CRTDBG_FILE_STDOUT );
    // _CrtDumpMemoryLeaks();
}