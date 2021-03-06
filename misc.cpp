#include <iostream>

inline bool startsWith(std::string& str, std::string start){
    if(str.size() < start.size()){return false;}

    for(int i = 0; i < (int)start.size(); ++i){
        if(start[i] != str[i]){
            return false;
        }
    }
    return true;
}
