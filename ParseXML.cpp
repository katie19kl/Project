#include <stdio.h>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector> 

void parseXML();
using namespace std;

int main()
{
    parseXML();
}
/*
Reads XML and adds sim to vector simFromSim
*/
void parseXML()
{
    vector <string> simFromSim;
    string fileName = "generic_small.xml";
    ifstream in(fileName);
    string leftComp,rightComp;
            
    string leftStart = "<node>";
    string rightEnd = "</node>";
    int start, end, strLen;
    if (!in)
    {
        cout << "file was not found!!!!!!!!!!!!!!!!!!!!!!!!";
        return;
    }
    string line;
            int x = 0;

    while (in)
    {
        getline(in, line);

        line.erase(remove(line.begin(), line.end(), ' '), line.end());

        strLen = line.length();

        if (strLen > 8)
        {
            leftComp = line.substr(0, 6);
            leftComp.erase(remove(leftComp.begin(), leftComp.end(), '\t'), leftComp.end());


            rightComp = line.substr(strLen - 8, 8);
            rightComp = rightComp.erase(rightComp.length() - 1 );


            if ( leftComp == leftStart  && rightComp == rightEnd )
            {
                x+=1;

                simFromSim.push_back(line.substr(6, strLen - (leftStart.length() + rightEnd.length() + 1)));

                cout << line.substr(6, strLen - (leftStart.length() + rightEnd.length() + 1));
            }
        }

    }
    if (x != 36) {
        throw logic_error ( " is lack of var");
    }
    in.close();
    return;
}
