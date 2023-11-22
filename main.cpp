#include <iostream>
#include <fstream>

using namespace std;

bool yes_or_no(string phrase){
    string answer;
    do{
        cout << phrase;
        getline(cin >> ws, answer);

        answer[0] = tolower(answer[0]);

    }while(answer != "y" && answer != "n");

    if(answer == "y"){
        return true;
    }
    return false;
}

bool is_formatting(char l){
    if(l == '\t' || l == '\n'){
        return true;
    }
    return false;
}

bool is_punctuation(char l){
    if(l == '.' || l == ',' || l == '!' || l == '?' || l == ':' || l == ';' || l == '(' || l == ')' || l == '[' || l == '/' || l == '"' || l == '-'){
        return true;
    }
    return false;
}

char better_toupper(char l){
    if(isalpha(l)){
        return toupper(l);
    }
    return l;
}

void print_file(string filename){
    ifstream file(filename);
    cout << file.rdbuf();
    file.close();

    return;
}

int main(){

    string filename, new_filename;
    int length;

    cout << "Script Initializer\nThis program creates a copy of a text file with only the initials of the original words.\n\n";
    cout << "Enter filename: ";
    getline(cin >> ws, filename);

    ifstream script(filename);

    if(script.is_open()){
        if(yes_or_no("\nRead file? (y/n): ")){
            print_file(filename);
        }

        cout << "\nEnter new filename: ";
        
        getline(cin >> ws, new_filename);

        ofstream new_script(new_filename);

        string working((istreambuf_iterator<char>(script)), istreambuf_iterator<char>());
        length = working.length();

        for(int i = 0; i < length; i++){
            if(is_punctuation(working[i]) || is_formatting(working[i])){
                new_script << working[i];
            }
            if(isalpha(working[i]) || working[i] == 39){
                new_script << better_toupper(working[i]);
                for(int j = 0; i + j < length; j++){
                    if(!isalpha(working[i + j]) && working[i + j] != 39){
                        i += j - 1;
                        break;
                    }
                }
            }
        }

        new_script.close();

        if(yes_or_no("\nRead new file? (y/n): ")){            
            print_file(new_filename);
        }      
    }
    else{
        cout << filename << "Cannot open file.\n";
    }

    script.close();

    return 0;
}