#include "managed_pw.h"

managed_pw::managed_pw(std::string password)
{
    this->rawPassword = password;

    // Split password into chunks:
    int i = 0;
    while(i < password.size()){
        pwChunk newChunk;

        newChunk.content = password.substr(i, this->chunkSize);
        this->pwChunks.push_back(newChunk);
        i += this->chunkSize;
    }


}
