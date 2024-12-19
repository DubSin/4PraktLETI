#include <iostream>
#include <fstream>
#include <conio.h>
#include <cstring>
using namespace std;

unsigned string_length(char *S)
{
     unsigned L = 0;
     while (S[L]) 
          ++L;
     return L;

}
void vertical_output(char *str, int cur_size){
    for(int i=0; i<=cur_size; i++){
        if (str[i] == ' '){
            cout << '\n';
        }
        else{
            cout << str[i];
        }
        
    }
    cout << endl;
}

void partition_output(char *str, int start_pos, int end_pos){
    for(int i=start_pos; i<= end_pos; i++){
        cout << str[i];
    }
    cout << " ";
}

void ordered_output(char *str, int cur_size){
    bool is_alph = true;
    int start_pos = 0;
    for (int i=0; i<=cur_size; i++){
        if (str[i] == ' ' or i == cur_size){
            if (is_alph){
                partition_output(str, start_pos, i-1);
            }
            is_alph = true;
            start_pos = i + 1;
        } 
        else{
            if (!isalpha(str[i])){
            is_alph = false;
        }
        }
    }
    bool is_num = true;
    for (int i=0; i<=cur_size; i++){
        if (str[i] == ' ' or i == cur_size){
            if (is_num){
                partition_output(str, start_pos, i-1);
            }
            is_num = true;
            start_pos = i + 1;
        } 
        else{
            if (!isdigit(str[i])){
            is_num = false;
        }
        }
    }
    bool is_all = true, char_init = false, int_init = false;
    for (int i=0; i<=cur_size; i++){
        if (str[i] == ' ' or i == cur_size){
            if (is_all && char_init && int_init){
                partition_output(str, start_pos, i-1);
            }
            is_all = true;
            int_init = false, char_init = false;
            start_pos = i + 1;
        } 
        else{
            if (!isalnum(str[i])){
            is_all = false;
            }
            if (isalpha(str[i])){
                char_init = true;
            }
            if (isdigit(str[i])){
                int_init = true;
            }
        }
    }
}

int linear_search(char *str, char *substr, int str_legth, int sub_length) {
    int sub_count = 0;
    for (int i = 0; i <= str_legth - sub_length; i++) {
        int j;
        for (j = 0; j < sub_length; j++) {
            if (str[i + j] != substr[j])
                break;
        }
        
        if (j == sub_length) 
           sub_count++;
    }

    return sub_count; 
}

void computeLps(char* pattern, int* &lps) {
    int n = string_length(pattern);
    int len = 0;
    int i = 1;

    while (i < n) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}
int kmp(char* text, char* pattern) {
    int count = 0;
    int lps[100];
    int n = string_length(text);
    int m = string_length(pattern);
    int i = 0;
    int j = 0;

    while (i < n) {
        if (text[i] == pattern[j]) {
            i++;
            j++;
        }

        if (j == m) {
            count++;
            j = lps[j - 1];
        } else if (i < n && text[i] != pattern[j]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }

    return count;
}
void clear_string(char* str, int length){
    char cleaned_text[100]; 
    int j = 0;
    bool prev_space = false; 
    bool prev_punct = false; 
    for (int i = 0; i <= length; ++i) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
           cleaned_text[j++] = str[i] + ('a' - 'A'); 
        } else {
            cleaned_text[j++] = str[i];
        }

        
        if (cleaned_text[j - 1] == ' ') {
            if ( prev_space) {
                --j; 
            }
             prev_space = true;
        } else {
            prev_space = false; 
        }

        
        if (strchr(".,;:!?", cleaned_text[j - 1])) { 
            if (prev_punct) {
                --j; 
            }
            prev_punct = true;
        } else {
            prev_punct = false; 
        }
    }

    strcpy(str, cleaned_text);
}
int main() {
    char action = 's';
    int cur_str_size = 0;
    char char_arr[100];
    while (action != 'e')
    {
        cout << "Menu" << endl;
        cout << "1)Input string" << endl;
        cout << "2)Correct string" << endl;
        cout << "3)display first all words containing only letters, then words containing only numbers, and then words containing both letters and numbers" << endl;
        cout << "4)Display all words of the original sequence vertically on the screen." << endl;
        cout << "5) Find substring" << endl;
        cout << "Choose action: ";
        cin >> action;
        switch (action)
        {
        case '1':
        {
            char input_type;
            cout << "String or file (s/f): ";
            cin >> input_type;
            switch(input_type){
                case 'f':
                {
                    char file_name[50];
                    cout << "Input file name: ";
                    cin >> file_name;
                    ifstream file(file_name);
                    if(file.is_open()){
                        while(!file.eof()){
                            file.getline (char_arr, 100);
                        }
                    }
                    file.close();
                    cur_str_size = string_length(char_arr);
                    break;
                }
                case 's':
                    cout << "Input your string: " << endl;
                    cin.sync();
                    cin.getline(char_arr, 100);
                    cur_str_size = string_length(char_arr);
                    break;
            }
            break;
        }
        case '2':
        {
            clear_string(char_arr, cur_str_size);
            cout << char_arr;
            _getch();
            break;
        }
        case '3':
        ordered_output(char_arr, cur_str_size);
        _getch();
        break;
        case '4':
        {
            vertical_output(char_arr, cur_str_size);
            _getch();
            break;
        }
        case '5':
        {
            char algorithm_action;
            cout << "1)Linear algorithm \n2)KMP algorithm\n Choose your action: ";
            cin >> algorithm_action;
            int ans = 0;
            switch (algorithm_action)
            {
            case '1':
                {
                char substring[100];
                cout << "Input your substring: " << endl;
                cin.sync();
                cin.getline(substring, 100);
                int sub_ln = string_length(substring);
                ans = linear_search(char_arr, substring, cur_str_size, string_length(substring));
                break;
                }
            case '2':
            {
                char substring[100];
                cout << "Input your substring: " << endl;
                cin.sync();
                cin.getline(substring, 100);
                ans = kmp(char_arr, substring);
                break;
            }
            }
            cout << "Matches found: " << ans;
            _getch();
            break;
        }
        }
    system("cls");
    }
    system("pause");
    return 0;
}


