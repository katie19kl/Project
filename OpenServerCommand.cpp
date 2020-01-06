#include "OpenServerCommand.h"
#include <stdio.h>
#include <sys/socket.h>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <thread>
#include <unordered_map>
#include <sstream>
#include <mutex>
#include <condition_variable>
#include "Ex1.h"
#include <string>

std::mutex mutSer;
std::condition_variable cvSer;
// flag to condition var to keep going to main
bool was_accepted = false;
using namespace std;
// executing server tafkid


int OpenServerCommand::execute(vector<string> vectOfParam, int indexCurr)
{
    string portCalc = vectOfParam.at(indexCurr + 1);
    string portBliSpace, intermediate;

    stringstream check1(portCalc);
    while (getline(check1, intermediate, ' '))
    {                                 //tokenizing according to ' '
        portBliSpace += intermediate; //creating the exp without spaces
    }

    auto *interpreter = new Interpreter();
    interpreter->setSymbolTable(this->symboleTable->get_NameVar_ToVar());

    double value = interpreter->interpret(portBliSpace)->calculate();

    int PORT = int(value);

    thread threadServerNew([this, PORT]() {
        createThread(PORT);
    });
    threadServerNew.detach();
    //waiting till server was conencted
    std::unique_lock<std::mutex> lk(mutSer);

    cvSer.wait(lk, [] { return was_accepted; });

    return this->DILUG;
}
// Creating server thread to start receiving givens
int OpenServerCommand ::createThread(int PORT_TEMP)
{
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1)
    {
        std::cerr << "Could not create a socket" << std::endl;
        return -1;
    }
    this->socket_ToClose = socketfd;
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
    // accepting a client
    int client_socket = accept(socketfd, (struct sockaddr *)&address, (socklen_t *)&address);
    // tell to keep running to main
    was_accepted = true;
    cvSer.notify_one();

    if (client_socket == -1)
    {
        std::cerr << "Error accepting client" << std::endl;
        return -4;
    }// reading data from simulator
    while (true)
    {
        char buffer[2048];
        read(client_socket, buffer, 2048);
        // update symbole table inside programm
        this->symboleTable->change_SymbolTable(buffer, "server");
    }
    return -1;
}

// closing the socket
void OpenServerCommand :: closeSocket(){
    if (this->socket_ToClose != -1){
        close (socket_ToClose);
    }
}