/**
 * Dimitri Turovets & Keti Klinberg
*/
#include <iostream>
#include "Run.h"


int main(int argc, char *argv[]) {
    if (argc == 1)
    {
        std::cout << "Error - the file name was not given" << std::endl;
    }
    // running the procces  
    run(argv[1]);
    
    return 0;
}