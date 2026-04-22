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
#include <iostream>
#include <stdlib.h>

using namespace std;

int vvod_int(){
    int x=0;
    cin>>x;
    while (cin.fail()){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout<<"Vvedite znachenie zanovo";
        cin>>x;

    }
    return x;
}
void test(int* m[]){
    int** m_1=m;
    for (int i=0; i<5;i++){
        for(int k=0;k<10;k++){
            // m[i][k]=0;
            cout<<m_1[i][k]<<" ";
        }
        cout<<""<<endl;
    }
}

void sdvig_vpravo(int j, int l, int* m[]){
    int** m_1=m;
    int m_2=0;
    int k_1=0;
    for (int i = 0; i < j; i++) {
        int k_1 = m[i][l - 1]; // Сохраняем последний элемент
        for (int k = l - 1; k > 0; k--) {
            m_1[i][k] = m_1[i][k - 1]; // Сдвиг вправо
        }
        m_1[i][0] = k_1; // Переносим сохраненный элемент в начало
    }
}

int main (){
    
    int j=5, l=10,n=0, a=0, b=0, colichestvo=0, znach=0, i_1=0, k_1=0, m_1=0;
    // int *m= new int [5];
    int **m;
    m= new int* [j];
    for (int i =0; i < l; ++i){
        m[i]=new int [l];
    }

    bool flag=false;
    for (int i=0; i<5;i++){
        for(int k=0;k<10;k++){
            m[i][k]=0;
            cout<<m[i][k]<<" ";
        }
        cout<<""<<endl;
    }
    cout<<"Vvedite scolko znacheniy vi hotite vvesti v masiv"<<endl;
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

    cout<<"Vvedite fasle esli hotite vipolnt` sdvig vpravo, ili vvedite true esli hotite vspolnit` sdig vniz"<<endl;
    cin>>flag;
    while (cin.fail()){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout<<"Vvedite znachenie zanovo";
        cin>>flag;
        
    }


    for (int i=0; i<j;i++){
        for(int k=0;k<l;k++){
            // m[i][k]=0;
            cout<<m[i][k]<<" ";
        }
        cout<<""<<endl;
    }

    cout<<""<<endl;
    // if (!flag){
    //     for (int i=0; i<j; i++){
    //         k_1=m[i][l];
    //         for(int k=l-1; k>0; k--){
    //             m_1=m[i][k-1];
    //             m[i][k-1]=m[i][k];
    //             m[i][k]=m_1;
    //             if(k-1==l){
    //                 m[i][0]=k_1;
    //             }
    //             m_1=0;
    //         }
    //         k_1=0;
    //     }
    // }
    // else{
    //     for (int k=0; k<l; k++){
    //         k_1=m[k][j];
    //         for(int i=j-1; i>0; i--){
    //             m_1=m[i-1][k];
    //             m[i-1][k]=m[i][k];
    //             m[i][k]=m_1;
    //             if(i-1==l){
    //                 m[0][k]=k_1;
    //             }
    //             m_1=0;
    //         }
    //         k_1=0;
    //     }
    // }
    
    for (int i=0;i<12;i++){
        sdvig_vpravo (j, l, m);

    }
    

// void vvivod(int j, int l, int* m[]){
//     for (int i=0; i<j;i++){
//         for(int k=0;k<l;k++){
//             m[i][k]=0;
//             cout<<m[i][k]<<" ";
//         }
//         cout<<""<<endl;
//     }
// }

    for (int i=0; i<j;i++){
        for(int k=0;k<l;k++){
            // m[i][k]=0;
            cout<<m[i][k]<<" ";
        }
        cout<<""<<endl;
    }

    cout<<" "<<endl;

    
    //Ydalenie massiva
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