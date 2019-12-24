#include "ConnectCommand.h"
#include <sys/socket.h>
#include <string>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <bits/stdc++.h> 
#include <arpa/inet.h>

using namespace std;
#define PORT 5402

int ConnectCommand::connectControlClient(){

    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        //error
        std::cerr << "Could not create a socket"<<std::endl;
        return -1;
    }

    //We need to create a sockaddr obj to hold address of server
    sockaddr_in address; //in means IP4
    address.sin_family = AF_INET;//IP4
    address.sin_addr.s_addr = inet_addr("127.0.0.1");  //the localhost address
    address.sin_port = htons(PORT);
    //we need to convert our number (both port & localhost)
    // to a number that the network understands.

    // Requesting a connection with the server on local host with port 8081
    int is_connect = connect(client_socket, (struct sockaddr *)&address, sizeof(address));
    if (is_connect == -1) {
        std::cerr << "Could not connect to host server"<<std::endl;
        return -2;
    } else {
        std::cout<<"Client is now connected to server" <<std::endl;
        this->isConnected = true;
    }
    return 1;

}

int ConnectCommand :: sendToSimul(){
    string set = "set";
    string path;
    string toSend = set + "sim" + path +  "/n";
    char to_SEND [toSend.size()];
    strcpy (to_SEND, toSend.c_str());


    if (this->isConnected){

        int is_sent = send(this->clientSocket,to_SEND, toSend.size(), 0);
    }
    return 1;
}

int ConnectCommand ::execute(vector<string> vectOfParam, int indexCurr){
    
    /*
    if ge connectControlCLient=> call connect control
    */

    




    return this->DILUG;
}
