#ifndef MANAGED_PW_H
#define MANAGED_PW_H
#include <string>
#include <vector>

struct pwChunk{
    std::string content;
    int visCounter = 0; // Visible characters from beginning
    int correctInputs = 0;  //Count of correct inputs by user
};

class managed_pw
{
public:
    managed_pw(std::string password = "");


    std::string getVisible();

    std::string rawPassword;
    int chunkSize = 5;

    std::vector<pwChunk> pwChunks;
};

#endif // MANAGED_PW_H
