# Ex3_FlightInterpreter

The Ex3_FlightInterpreter is a C++ project, used as an interpreter of a given code. It is responsible for flying a flight simulator, in the virtual space of the FlightGear software. Moreover, this project is being used as both server, that the flight simulator can connect to, and a client which updates the simulator with new data.

## Installation

Download the zip file of the project from the following [link](https://github.com/katie19kl/Project/tree/FINAL_1.6.2020) in the github website(The branch called "Final_1.6.2020"), by pressing on the green button "clone or download".

All the files needed to run the program are in this folder.


## Running the project

First, unzip the file.

Now we can compile the project files with the following command in the commandline(terminal):

```bash
g++ -std=c++14 *.cpp -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -o a.out -pthread
```

Now, that an execution file a.out is created, we can run the program, while also passing the name of the txt file containing the code we interpret. For example:

```bash
./a.out fly.txt
```

After running the program, we also run the FlightGear simulator(or the python script that simulates the flightGear's simulator actions).

## Comments

Our program runs perfectly with both the python script "fake_server.py" and the FlightGear simulator. In the simulator we see that the plane flies without any problem, and the parsing and execution of the code in text file provided is indeed finished.

