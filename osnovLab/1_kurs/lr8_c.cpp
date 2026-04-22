//c++
#include <iostream>
#include <fstream>
#include <cctype>
//c
#include <stdio.h>    
#include <ctype.h>
#include <clocale>
   
using namespace std;

bool is_glas(char c){
    c=tolower(c);
    return (c=='a'||c=='o'||c=='u'||c=='y'||c=='e'||c=='i');
}
int main_cpp(){
    ifstream input("./files/input_text.txt");
    ofstream output("./files/output_text.txt");
    
    if (!input.is_open() || !output.is_open()){
        cerr << "Oshibka otkritia files"<<endl;
        return 1;
    }

    char ch ='0';
    bool new_word =true;
    while (input.get(ch)){
        if (isalpha(ch)){
            if(new_word && is_glas(ch)){
                output.put(toupper(ch));
            }
            else output.put(ch);
            if (new_word)cout<<endl;
            new_word=false;
            cout<<ch;
        }
        else{
            output.put(ch);
            new_word=true;
        }
    }
    input.close();
    output.close();
    return 0;
}
int main_c(){
    FILE *input = fopen("./files/input_text.txt", "r");
    FILE *output = fopen("./files/output_text.txt", "w");
    
    if (!input || !output) {
        fprintf(stderr, "Oshibka otkritia files\n");
        return 1;
    }

    int ch;
    int new_word = 1;
    
    while ((ch = fgetc(input)) != EOF) {
        if (isalpha(ch)) {
            if (new_word && is_glas(ch))fputc(toupper(ch), output);
            else fputc(ch, output);
            if (new_word)printf("\n");
            new_word = 0;
            printf("%c",ch);
        }
        else {
            fputc(ch, output);
            new_word = 1;
        }
    }
    
    fclose(input);
    fclose(output);
    return 0;
}

int main (){
    bool flag =0;
    cout<<"Vvedite True esli hotite ispolzovat sposob resheny C, ili vvedite False esli hotite ispolzovat c++"<<endl;
    cin>>flag;
    if (flag) return main_c();
    else return main_cpp();
}
