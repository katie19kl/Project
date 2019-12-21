//
// Created by katie on 21/12/2019.
//

#ifndef PROJECT__COMMAND_H_
#define PROJECT__COMMAND_H_

using namespace std;

class Command {

 public:
  virtual int execute() = 0;
  virtual ~Command() {};
};

#endif //PROJECT__COMMAND_H_
