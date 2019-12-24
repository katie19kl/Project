#ifndef Var_H
#define Var_H

#include <string>

class Var
    {
    private:
        double value;
        std::string sim;
        std::string varName;
        bool bind_From_Sim = false;
        bool bind_IN_Sim = false;
        bool is_binding = true;
        


    public:
        Var(double value1, std::string sim1, std::string varName1,
            bool bind_From_Sim1,
            bool bind_IN_Sim1,bool is_binding1)
        {
            this->value = value1;
            this->sim = sim1;
            this->varName = varName1;
            this->bind_From_Sim = bind_From_Sim1;
            this->bind_IN_Sim = bind_IN_Sim1;
            this->is_binding = is_binding1;
        }
        double getValue()
        {
            return this->value;
        }
        std::string getSim()
        {
            return this->sim;
        }
        std::string getVarName()
        {
            return this->varName;
        }
        bool bindINServer()
        {
            return this->bind_IN_Sim;
        }
        bool bindFromServer()
        {
            return this->bind_From_Sim;
        }
    };

#endif