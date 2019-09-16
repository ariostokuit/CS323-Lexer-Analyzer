//
//  main.cpp
//  LexerAnalysisCS362
//
//  Created by Ariosto Kuit, Alex, Nick Webster on 9/16/19.
//  Copyright © 2019 Ariosto Kuit. All rights reserved.
//

#include <iostream>
#include <string>
using namespace std;

int global_string_index = 0;
const int OPERATOR_SIZE = 10;
const char OPERATORS[OPERATOR_SIZE] = {"+","-","=","%","*","/"};


//will return a string containing the entire code
string readFile(string textFile){
    string code;
    
    return code;
}

//will parse the code into separator tokens
string parse(string str1){
    
    string temp = ""; //parsed string
    
    if(str1[global_string_index] == ' '){global_string_index++;} // an empty blank space
    
    //test if part of string is a letter
    if(isalpha(str1[global_string_index]))
    {
        while(global_string_index < str1.length())
        {
            if(isalpha(str1[global_string_index]))
            {
                temp = temp + str1[global_string_index];
                global_string_index++;
            }
            else
                break; //stop the loop
        }
        return temp; //return the valid string
    }
    
    //test if the string position is a separator
    if(str1[global_string_index] == '(' || str1[global_string_index] == ')')
    {
        temp += str1[global_string_index];
        global_string_index++;
        return temp;
    }
   
    //test if the string position is an operator
    if(!isalpha(str1[global_string_index]))
    {
        int i = 0;
        while(i < OPERATOR_SIZE)
        {
            if(str1[global_string_index] == OPERATORS[i])
            {
                temp += OPERATORS[i];
                global_string_index++;
                return temp;
            }
            else
                i++;
        }
    }
    
    //test if position is a numberic string
    if(isdigit(str1[global_string_index]))
    {
        temp += str1[global_string_index];
        global_string_index++;
        while(isdigit(str1[global_string_index]) || str1[global_string_index] == '.')
        {
            temp+=str1[global_string_index];
            global_string_index++;
        }
        return temp; //return the numeric string
    }
    
    return temp;
}



int main(int argc, const char * argv[]) {
   
    
    
    return 0;
}
