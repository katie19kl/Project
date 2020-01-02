#include "OpenServerCommand.h"
#include <stdio.h>
#include <sys/socket.h>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <thread>
#include <unordered_map>

#include <mutex>
#include <condition_variable>

std::mutex mutSer;
std::condition_variable cvSer;

bool was_accepted = false;
using namespace std;

int OpenServerCommand::execute(vector<string> vectOfParam, int indexCurr)
{
    int foo;
    int PORT = stoi(vectOfParam.at(1));

    thread threadServerNew([&foo, this, PORT]() {
        //this_thread::sleep_for(chrono::milliseconds(1000));
        //cout << "in thread and its port";
        //cout << PORT << endl;

        foo = createThread(PORT);
    });
    threadServerNew.detach();

    std::unique_lock<std::mutex> lk(mutSer);

    cvSer.wait(lk, [] { return was_accepted; });

    cout << "step before returning to main" << endl;
    return this->DILUG;
}

int OpenServerCommand ::createThread(int PORT_TEMP)
{
    cout << this_thread::get_id() << " is new  thread !!!  " << endl;

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
        std::cout << "-------Server is now listening ..." << std::endl;
    }

    // accepting a client
    int client_socket = accept(socketfd, (struct sockaddr *)&address,
                               (socklen_t *)&address);

    was_accepted = true;
    cout << "before notifing" << endl;
    cvSer.notify_one();

    if (client_socket == -1)
    {
        std::cerr << "Error accepting client" << std::endl;
        return -4;
    }
    cout << "------------  SERVER IS CONNECTED --------------" << endl;
    int x = 0;
    int checkOpt = 0;

    //cout << "giving fora to main" << endl;;
    //cout << "I keep going" << endl;

    SymboleTable *checkClient = this->symboleTable;

    int out = 0;
    while (true)
    {

        out++;
        char buffer[2048];

        /*   cout << "1 - *************************" << endl;

        cout << "2 - before reading" << endl;
*/
        int valread = read(client_socket, buffer, 2048);

    //    printf("3- received data is |<%s>|\n", buffer);

        this->symboleTable->change_SymbolTable(buffer, "server");

    //    cout << "here lemata is data===============================================" << endl;

        // cout << "after updating" << endl;
    }
    return -1;
}