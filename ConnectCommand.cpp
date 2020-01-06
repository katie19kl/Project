#include "ConnectCommand.h"
#include <sys/socket.h>
#include <string>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <bits/stdc++.h>
#include <arpa/inet.h>
#include <condition_variable>
#include <mutex>
#include <cstring>
#include <sstream>

#include "Ex1.h"

std::mutex mutClient;
std::condition_variable cvClient;

bool was_connected = false;

using namespace std;

int ConnectCommand::connectControlClient(string ip, int PORT)
{
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1)
    {
        //error
        std::cerr << "Could not create a socket" << std::endl;
        return -1;
    }
    this->symboleTable->setClientSocket(client_socket);
    // wanna change value to know where to send

    //We need to create a sockaddr obj to hold address of server
    sockaddr_in address;          //in means IP4
    address.sin_family = AF_INET; //IP4
    if (ip == "127.0.0.1")
    {
        char *temp = new char[ip.size() + 1];
        strcpy(temp, ip.c_str());
        address.sin_addr.s_addr = inet_addr(temp); //the localhost address
    }
    address.sin_port = htons(PORT);
    //we need to convert our number (both port & localhost)
    // to a number that the network understands.

    // Requesting a connection with the server on local host with port 8081

    int is_connect = connect(client_socket, (struct sockaddr *)&address, sizeof(address));
    if (is_connect == -1)
    {
        std::cerr << "Could not connect to host server" << std::endl;
        return -2;
    }
    else
    {
        was_connected = true;
        cvClient.notify_one();
    }
    while (true)
    {
        // keeping connection
    }

    return 1;
}

int ConnectCommand ::execute(vector<string> vectOfParam, int indexCurr)
{
    string ip = vectOfParam.at(indexCurr + 1);

    string portCalc = vectOfParam.at(indexCurr + 2);
    string portBliSpace, intermediate;

    stringstream check1(portCalc);
    while (getline(check1, intermediate, ' '))
    {                                 //tokenizing according to ' '
        portBliSpace += intermediate; //creating the exp without spaces
    }

    auto *interpreter = new Interpreter();
    interpreter->setSymbolTable(this->symboleTable->get_NameVar_ToVar());

    double value = interpreter->interpret(portBliSpace)->calculate();

    int PORT_CLIENT = int(value);

    thread clientConnect([ip, PORT_CLIENT, this]() {
        this_thread::sleep_for(chrono::milliseconds(1000));
        connectControlClient(ip, PORT_CLIENT);
    });

    clientConnect.detach();
    // wait for connecting
    std::unique_lock<std::mutex> lk(mutClient);
    cvClient.wait(lk, [] { return was_connected; });

    return this->DILUG;
}
