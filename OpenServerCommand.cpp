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

mutex mtx;

int OpenServerCommand::execute(vector<string> vectOfParam, int indexCurr)
{
    int PORT_TEMP = stoi(vectOfParam.at(indexCurr + 1));

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

    cout << this_thread::get_id() << "  main thread id" << endl;
    //setThreadServer(client_socket);
    cout << "-----------------------------" << endl;

    //this->getServerThread()->detach();

/*    thread *threadServer = this->getServerThread();

    cout << "before" << endl;

    cout << threadServer->get_id() << "  new thread id" << endl;
    cout << this_thread::get_id() << "  main thread id" << endl;

    threadServer->join();
*/


    //getDataFromSim(client_socket);

    //////////////////////////////
    thread threadServer12(&OpenServerCommand::getDataFromSim, this, ref(client_socket));
    //threadServer12.detach();
    threadServer12.join();

    return this->DILUG;
}

void OpenServerCommand ::makeThreadConnect(int client_socket)
{
}

void OpenServerCommand ::setThreadServer(int client_socket)
{

    this->threadServer = new thread(&OpenServerCommand::getDataFromSim, this, ref(client_socket));
    cout << "thread was created " << endl;

    cout << this->threadServer->get_id() << " inside try getting" << endl;
}

void OpenServerCommand ::getDataFromSim(int client_socket)
{
    int x = 0;
    //this_thread::sleep_for(chrono::milliseconds(5000));
    unique_lock <mutex> unlck(mtx);
    while (true)
    {
        this_thread::sleep_for(chrono::milliseconds(50));
        
        cout << "-----------------------------" << endl;
        cout << this_thread::get_id() << "  id of thread while reading data" << endl;

        char buffer[2048];

        //string buffer;
        printf("------- before  reading # %d\n", x);
        //this_thread::sleep_for(chrono::milliseconds(500));
        int valread = read(client_socket, buffer, 2048);
        int valread1 = read(client_socket, buffer, 2048);
        cout << valread << " first read --from read int value" << endl;
        cout << valread1 << " second read -- from read int value" << endl;

        printf("-------  after reading # %d \n", x);

        for (int i = 0; i < 1024; i++)
        {
            this->check[i] = buffer[i];
        }
        
        cout << "-------------";
        cout << endl;
        printf("received data is |<%s>|\n", buffer);
        cout << "======================================================================="<<endl;

        updateSymbleTable(buffer);
        x++;
    }
}

void OpenServerCommand ::updateSymbleTable(char buffer[])
{
    int i = 0, numOfValue = 0;
    string data;
    while (buffer[i] != '\n')
    {

        if (buffer[i] == ',') /// ONly XML
        {
            //double num = stold(data);
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
    //////////////////////////////
}

unordered_map<string, double> *OpenServerCommand::getTable_XML_VAR()
{
    return this->bindValue;
}
