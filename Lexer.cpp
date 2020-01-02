#include <iostream>
#include "Lexer.h"
#include <vector>
#include <string.h>
#include <unordered_map>
#include "Command.h"
#include <fstream>
#include <regex>

vector<string> lexer(const string &file_name)
{
  vector<string> tokens;
  vector<string> vectorParams;
  fstream file;
  string line, updatedLine, subString, intermediate, tempStr = "";
  size_t indexCloser;
  unsigned long j;

  file.open(file_name, ios::in | ios::binary);
  if (!file.is_open())
  {
    throw "Error - Cannot open file " + file_name;
  }

  while (getline(file, line))
  {

    for (unsigned long i = 0; i < line.length(); i++)
    {
      if (line[i] == ' ')
      {
        continue;
      }
      if ((regex_match(string(1, line[i]), regex("[a-zA-Z]"))) || (regex_match(string(1, line[i]), regex("[_]"))))
      { //words or variables
        j = i;
        while ((regex_match(string(1, line[j]), regex("[a-zA-Z]"))) || (regex_match(string(1, line[j]), regex("[_]"))) || (regex_match(string(1, line[j]), regex("\\d"))))
        {
          j++;
        }
        if ((j - i) == 1)
        {
          tokens.emplace_back(string(1, line[i]));
          i = j - 1;
        }
        else
        {
          tokens.emplace_back(line.substr(i, j - i));
          i = j - 1;
        }
      }
      else if (regex_match(string(1, line[i]), regex("[0-9]")))
      { //a number
        j = i;
        while ((regex_match(string(1, line[j]), regex("[0-9]"))) || (regex_match(string(1, line[j]), regex("[.]"))))
        {
          j++;
        }
        if ((j - i) == 1)
        {
          tokens.emplace_back(string(1, line[i]));
          i = j - 1;
        }
        else
        { //a number with more than 1 char
          tokens.emplace_back(line.substr(i, j - i));
          i = j - 1;
        }
      }
      if (line[i] == '(')
      {
        indexCloser = i;
        while (line[indexCloser] != ')')
        {
          indexCloser += 1;
        }
        subString = line.substr((i + 1), (indexCloser - i - 1));
        int counterComa = 0;
        for (char c : subString)
        {
          if (c == ',')
          {
            counterComa += 1;
          }
        }
        if (counterComa >= 1)
        { //more that 1 param to the func
          stringstream check1(subString);
          while (getline(check1, intermediate, ','))
          { //tokenizing according to ','
            vectorParams.push_back(intermediate);
          }
          for (const string &item : vectorParams)
          {
            if ((item[0] == item[item.length() - 1]) && (item[0] == '"'))
            {
              tokens.emplace_back(item.substr(1, item.length() - 2));
            }
            else
            {
              tokens.emplace_back(item);
            }
          }
        }
        else
        { //no comas
          if ((subString[0] == subString[subString.length() - 1]) && (subString[0] == '"'))
          {
            tokens.emplace_back(subString.substr(1, subString.length() - 2));
          }
          else
          {
            tokens.emplace_back(subString);
          }
        }
        i = indexCloser + 1;
      }
      if (((line[i] == '-') && (line[i + 1] == '>')) || ((line[i] == '<') && (line[i + 1] == '-')))
      {
        tempStr += line[i];
        tempStr += line[i + 1];
        tokens.emplace_back(tempStr);
        tempStr = "";
        i += 1;
      }
      if (line[i] == '=')
      {
        tokens.emplace_back(string(1, line[i]));
      }
      if ((line[i] == '{') || (line[i] == '}'))
      {
        tokens.emplace_back(string(1, line[i]));
      }
      if (((line[i] == '<') && (line[i + 1] == '=')) || ((line[i] == '>') && (line[i + 1] == '=')) || (((line[i] == '!')) && (line[i + 1] == '=')) || ((line[i] == '=') && (line[i + 1] == '=')))
      {
        tempStr += line[i];
        tempStr += line[i + 1];
        tokens.emplace_back(tempStr);
        tempStr = "";
        i += 1;
      }
      else if (((line[i] == '<') && (line[i + 1] != '-')) || (((line[i] == '>')) && (line[i - 1] != '-')))
      {
        tokens.emplace_back(string(1, line[i]));
      }
      if (((line[i] == '+') || (line[i] == '-') || (line[i] == '*') || (line[i] == '/')) && (line[i + 1] != '>') && (line[i - 1] != '<'))
      {
        tokens.emplace_back(string(1, line[i]));
      }
    }
  }
  file.close();
  return tokens;
}