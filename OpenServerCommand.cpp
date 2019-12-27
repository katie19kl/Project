#include "OpenServerCommand.h"
#include <stdio.h>
#include <sys/socket.h>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <thread>
#include <unordered_map>
#include <mutex>

using namespace std;
//extern condition_variable cond_var;

//mutex mtx;

int OpenServerCommand::execute(vector<string> vectOfParam, int indexCurr)
{
    int foo;
    int PORT = stoi(vectOfParam.at(1));
    this->symboleTable->set_ServerRead(true);


    thread threadServerNew([&foo, this, PORT]() {
        this_thread::sleep_for(chrono::milliseconds(1000));
        cout << "in thread and its port";
        cout << PORT << endl;

        foo = createThread(PORT);
    });
    threadServerNew.detach();

    return this->DILUG;
}

int OpenServerCommand ::createThread(int PORT_TEMP)
{

    //int PORT_TEMP = 5400;
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1)
    {
        std::cerr << "Could not create a socket" << std::endl;
        return -1;
    }
    // we first need to create the sockaddr obj.
    sockaddr_in address; //in means IP4
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; //give me any IP allocated for my machine
    address.sin_port = htons(PORT_TEMP);

    //the actual bind command
    if (bind(socketfd, (struct sockaddr *)&address, sizeof(address)) == -1)
    {
        std::cerr << "Could not bind the socket to an IP" << std::endl;
        return -2;
    }
    //making socket listen to the port
    if (listen(socketfd, 5) == -1)
    { //can also set to SOMAXCON (max connections)
        std::cerr << "Error during listening command" << std::endl;
        return -3;
    }
    else
    {
        std::cout << "Server is now listening ..." << std::endl;
    }

    // accepting a client
    int client_socket = accept(socketfd, (struct sockaddr *)&address,
                               (socklen_t *)&address);

    if (client_socket == -1)
    {
        std::cerr << "Error accepting client" << std::endl;
        return -4;
    }
    cout<< "-----SERVER IS CONNECTED -----"<<endl;
    cout << client_socket << " to be send" << endl;
    this_thread::sleep_for(chrono::milliseconds(2000));
    cout << "received client socket ";
    cout << client_socket << endl;
    int x = 0;
    int checkOpt = 0;

    cout << "giving fora to main" << endl;
    this_thread::sleep_for(chrono::milliseconds(3000));
    cout << "I keep going" << endl;

    int out = 0;
    while (true)
    {
        this->symboleTable->set_ServerRead(true);

        printf("reading number %d\n", out);
        this_thread::sleep_for(chrono::milliseconds(10));
        out++;
        char buffer[2048];
        int valread = read(client_socket, buffer, 2048);

        cout << endl;
        printf("received data is |<%s>|\n", buffer);
        cout << "=======================================================================" << endl;

        this->symboleTable->set_ServerRead(false);
        SymboleTable::cv.notify_one();

        updateSymbleTable(buffer); ///to make save update in  single table.

        if (checkOpt == 0)
        {
            if (sizeof(buffer) > 0)
            {
                cout << "WE ARE GOINg TO KEEP MAIN ALIVE" << endl;
                this->symboleTable->set_FirstGiven(true); // => main can keep running
                checkOpt++;
                SymboleTable::cv.notify_one();
            }
        }

        this_thread::sleep_for(chrono::milliseconds(5));

        if (out == 20) // only checking
        {
            //break;
        }
    }
    return -1;
}

void OpenServerCommand ::updateSymbleTable(char buffer[])
{
    int i = 0, numOfValue = 0;
    string data;
    while (buffer[i] != '\n')
    {

        if (buffer[i] == ',') /// ONly XML
        {
            this->bindValue->insert({this->orderedXML.at(numOfValue), stold(data)});
            numOfValue++;
            data.clear();
        }
        else
        {
            data.push_back(buffer[i]);
        }
        i++;
    }
}

unordered_map<string, double> *OpenServerCommand::getTable_XML_VAR()
{
    return this->bindValue;
}
