#include <iostream>
#include "ParseXML.h"
#include "Main.h"
#include <string.h>
#include <unordered_map>
#include "Command.h"
#include "ChangeValue.h"
#include "IfCommand.h"
#include "LoopCommand.h"
#include "SleepCommand.h"
#include "PrintCommand.h"
#include "FuncParser.h"
#include "FuncCommand.h"
#include <fstream>
#include <regex>

int main(int argc, char *argv[]) {


  if (argc == 1) {
    cout << "Error - The file name wasn't given!" << endl;
    return 0;
  }

  vector <string> tokens = lexer(argv[1]);
  try {


    auto * fromTape = new unordered_map<string, Command*>();

    Var* var1 = new Var(3, "", "throttle",
        false, false, false);
    Var* var2 = new Var(5, "", "rudder",
        false, false, false);
    Var* var3 = new Var(1, "", "alt",
                        false, false, false);
    Var* var4 = new Var(90, "", "h0", false, false, false);
    Var* var5 = new Var(10, "", "heading",
                        false, false, false);
    Var* var6 = new Var(70, "", "roll",
                        false, false, false);
    Var* var7 = new Var(1, "", "aileron",
                        false, false, false);
    Var* var8 = new Var(1, "", "elevator",
                        false, false, false);
    Var* var9 = new Var(100, "", "pitch",
                        false, false, false);
    Var* var10 = new Var(-1, "", "breaks",
                        false, false, false);

    auto *name_to_var = new unordered_map<string, Var *>();
    name_to_var->insert({"throttle", var1});
    name_to_var->insert({"rudder", var2});
    name_to_var->insert({"alt", var3});
    name_to_var->insert({"h0", var4});
    name_to_var->insert({"heading", var5});
    name_to_var->insert({"roll", var6});
    name_to_var->insert({"aileron", var7});
    name_to_var->insert({"elevator", var8});
    name_to_var->insert({"pitch", var9});
    name_to_var->insert({"breaks", var10});

    SleepCommand sleep_command(name_to_var);
    fromTape->insert({"Sleep", &sleep_command});

    PrintCommand print_command(name_to_var);
    fromTape->insert({"Print", &print_command});

    ChangeValue change_value(name_to_var, 1);
    fromTape->insert({"changeValue", &change_value});

    FuncParser func_parser{};
    fromTape->insert({"funcParser", &func_parser});

    IfCommand if_command(fromTape, name_to_var, func_parser);
    fromTape->insert({"if", &if_command});

    LoopCommand loop_command(fromTape, name_to_var, func_parser);
    fromTape->insert({"while", &loop_command});

    FuncCommand func_command(name_to_var, fromTape, func_parser);
    fromTape->insert({"funcCommand", &func_command});


    parser(tokens, fromTape, name_to_var, func_parser);

    /*for (const string& item: tokens) {
      cout << item << endl;
    }*/
  } catch (const char * e) {
    cout << e << endl;
    return 0;
  }

  return 0;
}

vector <string> lexer(const string& file_name) {
  vector <string> tokens;
  vector<string> vectorParams;
  fstream file;
  string line, updatedLine, subString, intermediate, tempStr = "";
  size_t indexCloser;
  unsigned long j;

  file.open(file_name, ios:: in | ios:: binary);
  if (!file.is_open()) {
    throw "Error - Cannot open file " + file_name;
  }

  while (getline(file, line)) {

    for (unsigned long i = 0; i < line.length(); i++) {
      if(line[i] == ' ') {
        continue;
      }
      if((regex_match(string(1, line[i]), regex("[a-zA-Z]")))
      || (regex_match(string(1, line[i]), regex("[_]")))) { //words or variables
        j = i;
        while((regex_match(string(1, line[j]), regex("[a-zA-Z]")))
        || (regex_match(string(1, line[j]), regex("[_]")))
        || (regex_match(string(1, line[j]), regex("\\d")))) {
          j++;
        }
        if((j - i) == 1) {
          tokens.emplace_back(string(1, line[i]));
          i = j - 1;
        } else {
          tokens.emplace_back(line.substr(i, j - i));
          i = j - 1;
        }

      } else if (regex_match(string(1, line[i]), regex("[0-9]"))) { //a number
        j = i;
        while((regex_match(string(1, line[j]), regex("[0-9]")))
            || (regex_match(string(1, line[j]), regex("[.]")))) {
          j++;
        }
        if((j - i) == 1) {
          tokens.emplace_back(string(1, line[i]));
          i = j - 1;
        } else { //a number with more than 1 char
          tokens.emplace_back(line.substr(i, j - i));
          i = j - 1;
        }
      }
      if (line[i] == '(') {
        indexCloser = i;
        while (line[indexCloser] != ')') {
          indexCloser += 1;
        }
        subString = line.substr((i + 1), (indexCloser - i - 1));
        int counterComa = 0;
        for (char c : subString) {
          if (c == ',') {
            counterComa += 1;
          }
        }
        if (counterComa >= 1) { //more that 1 param to the func
          stringstream check1(subString);
          while(getline(check1, intermediate, ',')) { //tokenizing according to ','
            vectorParams.push_back(intermediate);
          }
          for (const string& item: vectorParams) {
            if((item[0] == item[item.length() - 1]) && (item[0] == '"')) {
              tokens.emplace_back(item.substr(1, item.length() - 2));
            } else {
              tokens.emplace_back(item);
            }
          }
        } else { //no comas
          if ((subString[0] == subString[subString.length() - 1]) && (subString[0] == '"')) {
            tokens.emplace_back(subString.substr(1, subString.length() - 2));
          } else {
            tokens.emplace_back(subString);
          }
        }
        i = indexCloser + 1;

      }
      if (((line[i] == '-') && (line[i + 1] == '>'))
      || ((line[i] == '<') && (line[i + 1] == '-'))) {
        tempStr += line[i];
        tempStr += line[i + 1];
        tokens.emplace_back(tempStr);
        tempStr = "";
        i += 1;
      }
      if ((line[i] == '=') && (line[i + 1]) != '=') {
        tokens.emplace_back(string(1, line[i]));
        if (line[i + 1] == ' ') {
          tokens.emplace_back(line.substr(i + 2, line.length() - i - 1));
        }
        else {
          tokens.emplace_back(line.substr(i + 1, line.length() - i - 1));
        }
        i = line.length() - 1;
      }
      if ((line[i] == '{') || (line[i] == '}')) {
        tokens.emplace_back(string(1, line[i]));
      }
      if (((line[i] == '<') && (line[i + 1] == '='))
          || ((line[i] == '>') && (line[i + 1] == '='))
          || (((line[i] == '!')) && (line[i + 1] == '='))
          || ((line[i] == '=') && (line[i + 1] == '='))) {
        tempStr += line[i];
        tempStr += line[i + 1];
        tokens.emplace_back(tempStr);
        tempStr = "";
        i += 1;
      } else if (((line[i] == '<') && (line[i + 1] != '-')) || (((line[i] == '>')) && (line[i - 1] != '-'))) {
        tokens.emplace_back(string(1, line[i]));
      }
      if (((line[i] == '+') || (line[i] == '-') || (line[i] == '*') || (line[i] == '/'))
      && (line[i + 1] != '>') && (line[i - 1] != '<')) {
        tokens.emplace_back(string(1, line[i]));
      }
    }
  }
  file.close();
  return tokens;
}


void parser(vector <string> tokens, unordered_map<string, Command*> * fromTape,
    unordered_map<string, Var*> * name_to_var, FuncParser& func_parser) {

  int i = 163; //change - since we are not using the first 3 commands(server, client, var creation)
  while (i < tokens.size()) {
    Command* c;

    //A specific command that is in the fromTape map(<string, Command*>)
    if (fromTape->find(tokens[i]) != fromTape->end()) {
      c = fromTape->find(tokens[i])->second;
      i += c->execute(tokens, i);

    } else {
      if (name_to_var->find(tokens[i]) != name_to_var->end()) {
        if (tokens[i + 1] == "=") { //of the type changeValue
          c = fromTape->find("changeValue")->second;
          i += c->execute(tokens, i);
        }

        //definition of a function
      } else if (tokens[i + 1].substr(0, 3) == "var") {
        c = fromTape->find("funcParser")->second;
        i += c->execute(tokens, i);

        //a name of a function that has been defined before - run the function
      } else if (func_parser.getFunctions().find(tokens[i]) != func_parser.getFunctions().end()) {
        c = fromTape->find("funcCommand")->second;
        i += c->execute(tokens, i);

      } else {
        throw "No such command exists!";
      }
    }
  }
}