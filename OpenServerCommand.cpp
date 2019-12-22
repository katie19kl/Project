#include "OpenServerCommand.h"
#include <stdio.h>
#include <sys/socket.h>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <thread>
#include <unordered_map>

#define PORT_TEMP 5400

using namespace std;

int OpenServerCommand::execute(vector<string> vectOfParam)
{

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

    char buffer[2048];
    //string buffer;
    int valread = read(client_socket, buffer, 2048);
    printf("%s\n", buffer);

    int i = 0, numOfValue = 0;
    string data;
    unordered_map<string, double> simGotValue; //add to member of server
    while (buffer[i] != '\n')
    {

        if (buffer[i] == ',')
        {
            //double num = stold(data);
            simGotValue.insert({this->orderedXML.at(numOfValue),stold(data)});
            numOfValue++;
            data.clear();
        
        }
        else
        {
            data.push_back(buffer[i]);
        }
        i++;
    }
    this->bindValue = simGotValue;
    return this->DILUG;
}
