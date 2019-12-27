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

using namespace std;
//#define PORT 5402

int ConnectCommand::connectControlClient(string ip, int PORT)
{
    cout << "before try connect" << endl;

    this_thread::sleep_for(chrono::milliseconds(2000));

    cout << "ip is " << ip << endl;
    cout << "port is " << PORT << endl;

    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1)
    {
        //error
        std::cerr << "Could not create a socket" << std::endl;
        return -1;
    }

    //We need to create a sockaddr obj to hold address of server
    sockaddr_in address;          //in means IP4
    address.sin_family = AF_INET; //IP4
    if (ip == "127.0.0.1")
    {
        char cstr[ip.size() + 1];
        strcpy(cstr, ip.c_str());
        cout << cstr << "  ip in char *" << endl;

        address.sin_addr.s_addr = inet_addr(cstr); //the localhost address
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
        std::cout << "Client is now connected to server" << std::endl;
        this->symboleTable->set_ClientTryConnect(false);

        SymboleTable::cv.notify_one();
    }
    while (true)
    {
        this_thread::sleep_for(chrono::milliseconds(1000));

        cout << "client connection" << endl;
    }

    return 1;
}

int ConnectCommand ::execute(vector<string> vectOfParam, int indexCurr)
{
    cout<<"client get pareser data ---------------------";
    string ip = vectOfParam.at(3);
    int PORT_CLIENT = stoi(vectOfParam.at(4));
    cout<<ip<<PORT_CLIENT<<endl;
    int foo;

    //this->symboleTable->set_ClientTryConnect(true);

    thread clientConnect([&foo, ip, PORT_CLIENT, this]() {
        this_thread::sleep_for(chrono::milliseconds(1000));
        cout << "in thread CLIENT and its port ->";
        cout << PORT_CLIENT << endl;
        cout << "in thread CLIENT and its id ->";
        cout << ip << endl;

        foo = connectControlClient(ip, PORT_CLIENT);
    });

    clientConnect.detach();

    return this->DILUG;
}
