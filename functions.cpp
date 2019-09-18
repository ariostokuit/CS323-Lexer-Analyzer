/*
* Ariosto Kuit
*
*
*/

#include <iostream>
#include <string>
#include <fstream>
using namespace std;
/*******************************************
*readFile() will read a text file from the main 
*and store the entire read file into a string and return that string
**********************************************/
string readFile(string fname){
    string code = "";
    string temp;
    ifstream myFile(fname);

    if(myFile.is_open()){ //open the file 
        while(!myFile.eof()) //continue iterating until end of file
        {
            getline(input,temp); //store each line of code in a temp variable
            code += temp; //concatenate the code into one string
        }
    }

    else
        return "Unable to open file\n"; //return an error that file is unable to open

    return code;
}