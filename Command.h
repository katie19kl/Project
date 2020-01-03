#ifndef Command_H
#define Command_H

#include <stdio.h>
#include <string>
#include <vector>

class Command
{
public:
    virtual int execute(std::vector <std::string>, int ) = 0; 
};

#endif