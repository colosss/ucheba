#include <iostream>
#include <fstream>
#include <cctype>

using namespace std;

bool is_glas(char c){
    c=tolower(c);
    return (c=='a'||c=='o'||c=='u'||c=='y'||c=='e'||c=='i');
}

int main (){
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
            new_word=false;
        }
        else{
            output.put(ch);
            new_word=true;
        }
    }
    input.close();
    output.close();

}
