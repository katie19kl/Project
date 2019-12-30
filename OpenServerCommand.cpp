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

//unique_lock<mutex> ul(SymboleTable::mut, defer_lock); // mutex.lock

int OpenServerCommand::execute(vector<string> vectOfParam, int indexCurr)
{
    int foo;
    int PORT = stoi(vectOfParam.at(1));

    this->symboleTable->set_ServerRead(true);

    thread threadServerNew([&foo, this, PORT]() {
        //this_thread::sleep_for(chrono::milliseconds(1000));
        //cout << "in thread and its port";
        //cout << PORT << endl;

        foo = createThread(PORT);
    });
    threadServerNew.detach();

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
    { ////

        //cout << checkClient->check_ClientSend() << " -- client in server " << endl;
        //    SymboleTable::cv.wait(ul, [checkClient] {
        //        return !checkClient->check_ClientSend();
        //    });

        //printf("reading number %d\n", out);
        //this_thread::sleep_for(chrono::milliseconds(10));
        out++;
        char buffer[2048];

        this->symboleTable->set_ServerRead(true);
        cout << "1 - *************************" << endl;

        cout << "2 - before reading" << endl;

        int valread = read(client_socket, buffer, 2048);

        printf("3- received data is |<%s>|\n", buffer);
        //cout << "after reading" << endl;

        //cout << endl;
        //cout << "before updating" << endl;
        //    updateSymbleTable(buffer);

        //    cout << "after updating" << endl;

        this->symboleTable->set_ServerRead(false);
        cout <<"4 -" <<symboleTable->check_ServerRead() << " check server is read in server" << endl;
        cout << " 5 - last before notifing" << endl;
        cout << "=======================================================================" << endl;

        SymboleTable::cv.notify_one();
        this_thread::sleep_for(chrono::microseconds(5));
        //cout << " server read inside a server " << this->symboleTable->check_ServerRead() << endl;

        if (checkOpt == 0)
        {
            if (sizeof(buffer) > 0)
            {
                //cout << "WE ARE GOINg TO KEEP MAIN ALIVE" << endl;
                this->symboleTable->set_FirstGiven(true); // => main can keep running
                checkOpt++;
                //                SymboleTable::cv.notify_all();
            }
        }

        //  this_thread::sleep_for(chrono::milliseconds(10));

        //this_thread::sleep_for(chrono::milliseconds(1000));
    }
    return -1;
}

void OpenServerCommand ::updateSymbleTable(char buffer[])
{
    int i = 0, numOfValue = 0;
    string data;
    /// 142 -157 --> updating table XML->VALUE
    unordered_map<string, Var *>::iterator it;
    cout << "before actual updating" << endl;
    int f = 0;
    //printf("%s",buffer);
    while (buffer[i] != '\n')
    {
        if (numOfValue == 36)
        {

            break;
        }

        f++;
        if (buffer[i] == ',') /// ONly XML
        {
            this->bindValue->insert({this->orderedXML.at(numOfValue), stold(data)});
            numOfValue++;
            data.clear();
            if (!this->symboleTable->get_SIM_ToVar()->empty()) // updating value in symbole table.
            {
                it = this->symboleTable->get_SIM_ToVar()->begin();
                while (it != this->symboleTable->get_SIM_ToVar()->end())
                {
                    if (it->first == this->orderedXML.at(numOfValue))
                    {
                        it->second->setValue(stold(data));
                        break;
                    }
                }
            }
        }
        else
        {
            data.push_back(buffer[i]);
        }
        i++;
    }
    cout << "after actual updating" << endl;

    //// update symbole table  XML_VAr-NAME
}

unordered_map<string, double> *OpenServerCommand::getTable_XML_VAR()
{
    return this->bindValue;
}
