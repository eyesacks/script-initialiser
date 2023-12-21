#include <iostream>
#include <fstream>

using namespace std;

bool yes_or_no(string phrase){//used in combination with an if statement for a simple way to implement a yes or no question for the user
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

bool is_formatting(char l){ //returns true if the given char is a tab or a newline
    if(l == '\t' || l == '\n'){
        return true;
    }
    return false;
}

bool is_punctuation(char l){ //returns true if the given char is one of the following characters
    if(l == '.' || l == ',' || l == '!' || l == '?' || l == ':' || l == ';' || l == '(' || l == ')' || l == '[' || l == '/' || l == '"' || l == '-'){
        return true;
    }
    return false;
}

char better_toupper(char l){ //checks if a char is a letter before making it uppercase
    if(isalpha(l)){
        return toupper(l);
    }
    return l;
}

void print_file(string filename){ //prints entire contents of a file
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

    ifstream script(filename); //opens user chosen file

    if(script.is_open()){
        if(yes_or_no("\nRead file? (y/n): ")){ //lets user preview their opened file
            print_file(filename);
        }

        cout << "\nEnter new filename: ";
        
        getline(cin >> ws, new_filename);

        ofstream new_script(new_filename); //creates new file

        string working((istreambuf_iterator<char>(script)), istreambuf_iterator<char>()); //copies contents of opened file into string
        length = working.length();

        for(int i = 0; i < length; i++){
            if(is_punctuation(working[i]) || is_formatting(working[i])){ //copies in punctuation and spacing
                new_script << working[i];
            }
            if(isalpha(working[i]) || isdigit(working[i]) || working[i] == 39){ //copies in the first letter of a word, and then skips to the end of the word so as to ignore the rest of the word's letters
                new_script << better_toupper(working[i]);
                for(int j = 0; i + j < length; j++){
                    if(!isalpha(working[i + j]) && working[i + j] != 39 && !isdigit(working[i + j])){
                        i += j - 1;
                        break;
                    }
                }
            }
        }

        new_script.close();

        if(yes_or_no("\nRead new file? (y/n): ")){ //lets user preview their new file
            print_file(new_filename);
        }      
    }
    else{ //case in which script.open() fails
        cout << filename << "Cannot open file.\n";
    }

    script.close();

    return 0;
}
