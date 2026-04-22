#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <fstream>
#include <vector>

using namespace std;

struct HashItems{
    string item;
    int collisions=0;
    bool flag=true;
};
struct HashMassiv{
    HashItems massiv[3000];
};

void standart_key(string &key){
    key="bcccbb";
}

void generate_key(string &key){
    string a="";
    for(int i=0;i<=5;i++){
        if(rand()%100<50)a+="b";
        else a+="c";
    }
}

string generate_chislo(){
    return to_string(rand() % 10);
}

string generate_bucv(){
    char c = 'A' + rand() % 26;
    return string(1, c);
}

string generate_hash_by_key(const string &key){
    string hash;
    for(int i=0;i<=5;i++){
        if(key[i]=='b'){
            hash+=generate_bucv();
        }
        else{
            hash+=generate_chislo();
        }
    }
    return hash;
}

int HashSum(string hash){
    int sum=0;
    for (int i=0; i<=5;i++){
        sum+=hash[i];
    }
    return sum;
}

void AddAtPosition(HashMassiv &hash, string key, int &pos){
    if(hash.massiv[pos].flag){
        hash.massiv[pos].item=generate_hash_by_key(key);
        cout<<"Success add at position: "<<pos<<" kesh: "<<hash.massiv[pos].item<<endl;
        hash.massiv[pos].flag=false;
        pos=0;
    }
    else cout<<"Positoion: "<<pos<<" is occupied"<<endl;
    pos=0;
}

void AddAtAll(HashMassiv &hash, string key){
    for (int i=0; i<3000; i++){
        if(hash.massiv[i].flag){
            hash.massiv[i].item=generate_hash_by_key(key);
            hash.massiv[i].flag=false;
        }
    }
}

void Hashfunction(HashMassiv &hash, string key, int col){
    int min=0;
    int max=0;
    int t=0;
    for (int i=0;i<=5;i++){
        if(key[i]=='b'){
            min+='A';
            max+='Z';
        }
        else{
            min+='0';
            max+='9';
        }
    }
    
    for(int i=0;i<col;i++){
        string temp=generate_hash_by_key(key);
        t=HashSum(temp);
        t=(t-min)*(3000/(max-min));
        if(!hash.massiv[t].flag){
            for(int j=1;j<=3000;j++){
                hash.massiv[t].collisions+=1;
                t=(t+j*j)%3000;
                if(hash.massiv[t].flag){
                    break;
                }
            }
        }
        if(hash.massiv[t].flag){
            hash.massiv[t].item=temp;
            hash.massiv[t].flag=false;
        }
    }
    t=0;
}

void DeleteAll(HashMassiv &hash){
    for(int i=0; i<3000; i++){
        hash.massiv[i].flag=true;
    }
}

void DeleteAtPosition(HashMassiv &hash, int &pos){
    hash.massiv[pos].flag=true;
    pos=0;
}

void PrintAll(HashMassiv &hash){
    cout<<"Hash masiv:"<<endl;
    cout<<"[";
    for(int i=0; i<3000;i++){
        if(i==2999) cout<<hash.massiv[i].item<<"]"<<endl;
        else if((i+1)%20!=0){
            if(hash.massiv[i].flag)cout<<"******"<<", ";
            else cout<< hash.massiv[i].item<<", ";
        }
        else{
            if(hash.massiv[i].flag)cout<<"******"<<","<<endl;
            else cout<<hash.massiv[i].item<<","<<endl;
        } 
    }
}

void PrintCollisions(HashMassiv &hash){
    cout<<"Hash collisions:"<<endl;
    cout<<"[";
    for(int i=0; i<3000;i++){
        if(i==2999) cout<<hash.massiv[i].collisions<<"]"<<endl;
        else if((i+1)%20!=0){
            cout<< hash.massiv[i].collisions<<", ";
        }
        else{
            cout<<hash.massiv[i].collisions<<","<<endl;
        } 
    }
}

void ExportCollisionsToCSV(HashMassiv &hash, const string& filename = "collisions.csv") {
    ofstream file(filename);
    
    if (!file.is_open()) {
        cout << "Ошибка создания файла!" << endl;
        return;
    }
    
    file << "Index,Collisions,Hash" << endl;
    
    for(int i = 0; i < 3000; i++) {
        file << i << "," << hash.massiv[i].collisions << ",";
        if(hash.massiv[i].flag) {
            file << "EMPTY";
        } else {
            file << hash.massiv[i].item;
        }
        file << endl;
    }
    
    file.close();
    cout << "Данные о коллизиях экспортированы в файл: " << filename << endl;
}

void ExportCollisionsStats(HashMassiv &hash, const string& filename = "collisions_stats.csv") {
    ofstream file(filename);
    
    if (!file.is_open()) {
        cout << "Ошибка создания файла!" << endl;
        return;
    }
    
    vector<int> collision_counts;
    for(int i = 0; i < 3000; i++) {
        collision_counts.push_back(hash.massiv[i].collisions);
    }
    
    file << "Position,CollisionCount,Occupied" << endl;
    
    for(int i = 0; i < 3000; i++) {
        file << i << "," << hash.massiv[i].collisions << ",";
        if(hash.massiv[i].flag) {
            file << "0";  // 0 для пустой ячейки
        } else {
            file << "1";  // 1 для занятой ячейки
        }
        file << endl;
    }
    
    file.close();
    cout << "Статистика коллизий экспортирована в файл: " << filename << endl;
    
    // Дополнительная статистика
    int total_collisions = 0;
    int max_collisions = 0;
    int occupied_cells = 0;
    
    for(int i = 0; i < 3000; i++) {
        total_collisions += hash.massiv[i].collisions;
        if(hash.massiv[i].collisions > max_collisions) {
            max_collisions = hash.massiv[i].collisions;
        }
        if(!hash.massiv[i].flag) {
            occupied_cells++;
        }
    }
    
    cout << "Общее количество коллизий: " << total_collisions << endl;
    cout << "Максимальное количество коллизий в одной ячейке: " << max_collisions << endl;
    cout << "Занято ячеек: " << occupied_cells << "/3000" << endl;
    if(occupied_cells > 0) {
        cout << "Среднее количество коллизий на занятую ячейку: " 
             << (double)total_collisions / occupied_cells << endl;
    }
}

int main(){
    srand(time(NULL));
    string key;
    HashMassiv hash;

    standart_key(key);

    int count=0;
    bool flag_cikl=true;
    int pos=0;

    while(flag_cikl){
        switch (count)
        {
        case 0:
            cout<<"***************************************************"<<endl;
            cout<<"1-add, 2-delete, 3-Print/CSV, 4-key, 5-Exit"<<endl;
            cin>>count;
            break;
        case 1:
            cout<<"***************************************************"<<endl;
            cout<<"1-AddAtPosition, 2-AddAtAll, 3-Add by hash function, 4-Back, 5-Exit"<<endl;
            cin>>count;
            count=count+10;
            break;
        case 2:
            cout<<"***************************************************"<<endl;
            cout<<"1-DeleteAtPosition, 2-DeleteAll, 3-Back, 4-Exit"<<endl;
            cin>>count;
            if (count==3 or count ==4) count=count+11;
            else count=count+20;
            break;
        case 3:
            cout<<"***************************************************"<<endl;
            cout<<"1-Print at position, 2-Print all, 3-Export as CSV, 4-Print collisions, 5-Back, 6-Exit"<<endl;
            cin>>count;
            if (count==5 or count ==6) count=count+10-1;
            else count=count+40;
            break;
        case 4:
            cout<<"***************************************************"<<endl;
            cout<<"1-Set standart key, 2-Generate key, 3-Print key, 4-Back, 5-Exit"<<endl;
            cin>>count;
            if (count==4 or count ==5) count=count+10;
            else count=count+30;
            break;
        case 5:
            flag_cikl=0;
            count=0;
            break;
        case 11:  
            cout<<"Vvedite pos(0-3000): ";
            cin>>pos;
            AddAtPosition(hash,key,pos);
            pos=0;
            count=0;
            break;
        case 12:
            AddAtAll(hash, key);
            count=0;
            break;
        case 13:
            cout<<"Vvedite collichestvo ellementov (0-3000): ";
            cin>>pos;
            Hashfunction(hash,key,pos);
            pos=0;
            count=0;
            break;
        case 14:
            count=0;
            break;
        case 15:
            flag_cikl=false;
            count=0;
            break;
        case 21:
            cout<<"Vvedite pos(0-3000): ";
            cin>>pos;
            DeleteAtPosition(hash, pos);
            pos=0;
            count=0;
            break;
        case 22:
            DeleteAll(hash);
            count=0;
            break;
        case 31:
            standart_key(key);
            count=0;
            break;
        case 32:
            generate_key(key);
            count=0;
            break;
        case 33:
            cout<<"Key: "<<key<<endl;
            count=0;
            break;
        case 41:
            cout<<"Vvedite pos(0-3000): ";
            cin>>pos;
            cout<<"Hash["<<pos<<"] = "<<hash.massiv[pos].item<<endl;
            pos=0;
            count=0;
            break;
        case 42:
            PrintAll(hash);
            count=0;
            break;
        case 43:
            ExportCollisionsToCSV(hash);
            ExportCollisionsStats(hash);
            count=0;
            break;
        case 44:
            PrintCollisions(hash);
            count=0;
            break;
        default:
            cout<<"Necorrectniy vvod, povtorite vvod zanovo"<<endl;
            count=0;
            break;
        }
        cout<<endl;
    }
    return 0;
}