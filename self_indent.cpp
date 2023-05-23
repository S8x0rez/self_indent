#include <bits/stdc++.h>
#include <fstream>
#include <string>
#include <regex>

using namespace std;

int main(int argc, char *argv[]){
    char *file_name = argv[1];
    ifstream ifs(file_name);
    ofstream ofs("tmp.cpp");
    
    string str;
    int ind_count = 0;
    int ws_count, tab_count;
    int tab_size = 2;
    bool flag = false;
    
    regex re0(R"(\}$)");
    regex re00(R"(\}.*else.*$)");
    regex re000(R"(^\}.*;$)");
    regex re1(R"(if.*\(.*\)$)");
    regex re2(R"(else$)");
    regex re3(R"(for.*\(.*\)$)");
    regex re4(R"(\{$)");
    regex re5(R"(\{.*\}$)");

    if(ifs.fail()){
        cerr << "Failed to open file." << "\n";
        return -1;
    }
    while(getline(ifs, str)){
        

        // Convert 'indentation' to 'tab key'
        ws_count = 0;
        tab_count = 0;
        for(int i = 0;i < str.size();i++){
            if(str[i] ==' ') ws_count++;
            else break;

            if(ws_count % tab_size == 0){
                i -= tab_size - 1;
                str.erase(i, tab_size);
                str.insert(i, "\t");
                tab_count++;
            }
        }

        if((str[0] == '/' && str[1] == '/') || str[0] == '#' || str[0] == ' ') {
            ofs << str << "\n";
            continue;
        }

        // count 'tab key','}'
        for(int i = 0;i < str.size();i++){
            if(str[i] == '\t') tab_count++;
        }
        if(regex_search(str, re0) || regex_search(str, re00) || regex_search(str, re000)) ind_count--;

        if(flag){
            if(!(ind_count < tab_count))str.insert(0, "\t");
            flag = false;
        }

        if(regex_search(str, re1) || regex_search(str, re2) || regex_search(str, re3)) flag = true;
        
        // insert 'tab key'
        for(int j = 0;j < ind_count - tab_count;j++){
            str.insert(0, "\t");
        }
        
        // count '{'
        if(regex_search(str, re4) || regex_search(str, re5) ) ind_count++;

        // Trim trailing whitespace
        for(int i = str.size() -1 ;i >= 0;i--){
            if(str[i] == ' ' || str[i] == '\t') str.erase(i);
            else break;
        }

        ofs << str << "\n";
    }

    ifs.close();
    ofs.close();

    remove(file_name);
    rename("tmp.cpp", file_name);


    return 0;
}
