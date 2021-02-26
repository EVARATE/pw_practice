#include <iostream>

inline bool startsWith(std::string& str, std::string start){
    if(str.size() < start.size()){return false;}

    for(int i; i < start.size(); ++i){
        if(start[i] != str[i]){
            return false;
        }
    }
    return true;
}
