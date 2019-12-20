#include "ex1.h"
#include "Expression.h"
#include <stack>
#include <queue>
#include <map>
#include <iostream>
#include <bits/stdc++.h> 
#include <vector> 
#include "ParseHelper.h"

using namespace std;

void Interpreter:: interpret(string strFromOutside){

<<<<<<< Updated upstream
    //queue <int> queueNum;
=======

//Checks validity of var
bool varCheckStr(string &str, vector <Variable*> vec){
    string varStr;
    int size = vec.size();

        for (int i = 0;i<size ;i++){

            varStr = vec.at(i)->GetName();
            int index = 0;

            while (true)
            {
                index = str.find(varStr,index);

                if (index == (int)std::string::npos) {break;}

                if (vec.at(i)->calculate() < 0 && index != 0){
                    if (str.at(index-1) == '('){
                
                        str.replace(index, varStr.length(), to_string(vec.at(i)->calculate()));
                        index += varStr.length();
                    }
                    else if (str.at(index-1) == '+'){

                        str.replace(index-1, varStr.length()+1, to_string(vec.at(i)->calculate()));
                        index += varStr.length();

                    }
                    else if (str.at(index-1) == '-'){

                        str.replace(index-1, varStr.length()+1,"+" + to_string(abs(vec.at(i)->calculate())));
                        index += varStr.length();

                    }                    
                    else if (str.at(index-1) == '*'){
                        str.replace(index-1, varStr.length()+1,"*(-1*" + to_string(abs(vec.at(i)->calculate())) + ")");
                        index += varStr.length();

                    }
                    else if (str.at(index-1) == '/'){
                        str.replace(index-1, varStr.length()+1,"/(-1*" + to_string(abs(vec.at(i)->calculate())) + ")");
                        index += varStr.length();

                    }
                }    
                else {

                    str.replace(index, varStr.length(), to_string(vec.at(i)->calculate()));
                
                    index += varStr.length();
                }
            }
        }
    return true; 

}
//Checks validity of string
void checkString(string str){
    int countPar = 0;
    int size = str.length()-1;
    for (int i=0 ; i<size ; i++){

        if(isOperand(string(1,str.at(i))) && isOperand(string(1,str.at(i+1)))){
            throw "illegal math expression";
        }
        if (str.at(i) == '(' || str.at(i) == ')'){
            countPar++;
        }
    }
    if (str.at(str.length()-1) == '(' || str.at(str.length()-1) == ')'){
        countPar++;
    }
    if (countPar%2 == 1){
        throw "illegal math expression";
    }
    return;
}

Expression* Interpreter:: interpret(string strFromOutside){

>>>>>>> Stashed changes
    queue <string> queueOut;
    stack <string> stackOper;
    map <string,int>  mapPreced;

    mapPreced.insert({"+",1});
    mapPreced.insert({"-",2});
    mapPreced.insert({"*",3});
    mapPreced.insert({"/",3});


    int numStrLen = 0,temp = 0;
    string strParNum;
    string num;
    int flag = 0;
    string subStrWithoutLeft;
    int nextNum = 0;
    
    //
    string nextSub;

    delExterParant(strFromOutside);
<<<<<<< Updated upstream
    int stringSize = strFromOutside.length();
    char prevInStr;

=======
    stringSize = strFromOutside.length();

    //start parsing
>>>>>>> Stashed changes
    for (int i = 0; i < stringSize; i++){
        flag = 0;
        //////////////////First is minus
        if ( i > 0 ){
            prevInStr = strFromOutside.at(i-1);
        }
        if ((strFromOutside.at(i) == '-' && isdigit(strFromOutside.at(i+1)) && (i == 0 || prevInStr == '('))){
            int j = i;
            int counter = 0;
            while (isdigit(strFromOutside.at(j+1)))
            {
                counter++;
                j++;
            }// may advance i
            subStrWithoutLeft = strFromOutside.substr(i+1, strFromOutside.length() - i);
            strParNum = "-" + numberGet(subStrWithoutLeft);
            if (temp !=0){ // reg
                nextSub = strFromOutside.substr(strParNum.length() +temp - 1, // -1 is minus
                                                    strFromOutside.length() - strParNum.length() - temp + 1);
                nextNum = getNextNum(nextSub);
                temp += nextNum + strParNum.length() - 1;// minus minus sign
            }else {//at start
                nextSub = strFromOutside.substr(strParNum.length() +temp, // -1 is minus
                                                    strFromOutside.length() - strParNum.length() - temp + 1);
                nextNum = getNextNum(nextSub);
                temp += nextNum + strParNum.length();// minus minus sign                                                    
            }    
            
            flag = 1;
            i = j;
        }


        /////////////////////////////////

        // number 
        if ( temp <= i && !isOperand(string(1,strFromOutside.at(temp)))){
            subStrWithoutLeft = strFromOutside.substr(temp,strFromOutside.length() - temp);
            strParNum = numberGet(subStrWithoutLeft);
            
            nextSub = strFromOutside.substr(strParNum.length() +temp,
                                                strFromOutside.length() - strParNum.length() - temp);
            nextNum = getNextNum(nextSub);
            
            temp += nextNum + strParNum.length();
            flag = 1;
        

        // operand    
        }else if (flag!=1 && !isdigit(strFromOutside.at(i))) {

            strParNum = strFromOutside.at(i);
        //int num;
        }

        if (flag == 1) {// if it is numbers

            queueOut.push(strParNum);

        }else if (isOperand(strParNum)){ // if is operand

            if (!stackOper.empty()){
                while (mapPreced[stackOper.top()] > mapPreced[strParNum]){
                 
                    queueOut.push(stackOper.top());
                    stackOper.pop();
                    if (stackOper.empty()){
                        break;
                    }
                    //cout<<"--------"<<operand<<" STRING--------"<<endl;
                    //cout<<fromStack<<endl;
        
                    
            }
        }
        stackOper.push(strParNum);
        

        }else if (strParNum == "("){
            stackOper.push(strParNum);
        }else if (strParNum == ")"){

            while (stackOper.top() != "("){
                    
                    queueOut.push(stackOper.top());
                    stackOper.pop();
                    
                    //cout<<"--------"<<operand<<" STRING--------"<<endl;
                    
            }
            stackOper.pop();
        }


        
        //------------
        //Expression* exAfterAlgo = calcQueue(queueOut);
    }
    while (!stackOper.empty()){
        
            queueOut.push(stackOper.top());
            stackOper.pop();
            //cout<<"--------"<<operand<<" STRING--------"<<endl;

        }

    //calculateAfterShuntingYard___2(queueOut);
    cout<<"--------------"<<endl;
    calculateAfterShuntingYard(queueOut);


    return ;     

}
<<<<<<< Updated upstream



=======
//sets variables
>>>>>>> Stashed changes
void Interpreter::setVariables(string varFromUser){

    int amoutVar = amountOfVar(varFromUser) + 1;
    //vector<Variable*> *vectorVariables = new vector<Variable*>(amoutVar);

    vector<Variable*> vectorVariables;



    int placeEqual,placeDiff,i=0;

    while (amoutVar != i){
        placeEqual = varFromUser.find('=');
        placeDiff = varFromUser.find(';');
        
        string nameVar = varFromUser.substr(0,placeEqual);
        
        string toCheckNum = varFromUser.substr(placeEqual+1, placeDiff - 1 - placeEqual);

        if (failVarName(nameVar)){
            throw "user you are stupid, give normal data";

        }else if (true){

            int placeOfP = toCheckNum.find(".");
	        bool check;
	        string before = toCheckNum.substr(0,placeOfP);
	        string after  = toCheckNum.substr(placeOfP + 1,-1);
		    if (placeOfP != -1){
		        check = before_after(before,after);
	
	        }else {
	    	    check = is_number(after);

	        }
            if (check == false){
                throw "user you are stupid, give normal data";
            }
        }
        
        double varValue = stod(toCheckNum);
        varFromUser = varFromUser.substr(placeDiff+1, varFromUser.length());



        Variable* var = new Variable(nameVar,varValue);
        vectorVariables.push_back(var);
        //cout<<var->calculate()<<endl;
        //cout<<vectorVariables.size()<<endl;
        i++;   
        
    }


    this->vectorVariables = vectorVariables;
    this->printVec();
}