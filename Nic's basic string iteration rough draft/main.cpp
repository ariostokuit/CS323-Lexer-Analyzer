// Nicholas Webster
//
// CPSC 323-02
// Assignment 1

/*DELETE THIS COMMENT BEFORE FINAL SUBMISSION
  I wasn't able to compare str1[0] == SEPARATORS_LIST[i]. That requires
  overloading the == operator (I think) and I didn't feel like doing that.
  So I created the 'atZero' string and set it equal to the first
  character in the string. Pretty janky but it works. Feel free to edit it
*/

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

const vector<string> SEPARATORS_LIST = { "'", "(", ")", "[", "]", "{", "}", ",", ".", ":", ";", "!" };
const vector<string> OPERATOR_LIST = { "*", "+", "-", "=", "/", ">", "<", "%" };

void parseLetter(string &str, vector<string> &pL) {
  /*
    parseLetter checks for letters, numbers, and dollar signs.
    All three are valid for an identifier name.
    Once i+1 is not one of those three, it pushes the substring to the vector
      which was passed by reference.
    The FSM will later determie whether the string is a keyword or an identifier
  */
  for(int i=0; i<str.length(); i++) {
    if(isalpha(str[i+1]) || isdigit(str[i+1]) || str[i+1] == '$') {
      continue;
    } else {
      pL.push_back(str.substr(0, i+1));
      str.erase(0, i+1);
      return;
    }
  }
}

void parseNumber(string &str, vector<string> &pL) {
  /*
    parseNumber allows for digits and only ONE period.
    If there's more than one period, cout a warning, but continue to run.
    The FSM will later determine if it is a real or integer.
  */
  int periodCount = 0;

  for(int i=0; i<str.length(); i++) {
    if(isdigit(str[i+1])) {
      continue;
    } else if(str[i+1] == '.') {
      periodCount++;
      if(periodCount > 1) {cout << "\n\nWARNING: MORE THAN ONE PERIOD DETECTED!\n";}
    } else {
      pL.push_back(str.substr(0, i+1));
      str.erase(0, i+1);
      return;
    }
  }
}

vector<string> parse(string str1) {

  /*
    Create a string vector for the parsed elements and a string
      for the zero index of the string being parsed.
    Parse() will compare the zero index to the if statements.
    If the condition is met, the substring is pushed back to the string vector
      and the substring is erased from the string being parsed.
    Once erased, the zero index must be updated immediately for
      the next if condition.
  */

  vector<string> pList;
  string atZero;
  atZero.assign(str1, 0, 1);

  do {
  ////////// IF LETTER //////////
  if(isalpha(str1[0])) {
    parseLetter(str1, pList);
    atZero.assign(str1, 0, 1);
  }

  ////////// IF NUMBER //////////
  if(isdigit(str1[0])) {
    parseNumber(str1, pList);
    atZero.assign(str1, 0, 1);
  }

  ////////// IF WHITESPACE -> ERASE //////////
  if(isblank(str1[0])) {
    str1.erase(0, 1);
    atZero.assign(str1, 0, 1);
  }

  ////////// IF COMMENT -> ERASE ENTIRE COMMENT //////////
  if(str1[0] == '!') {
    for(int i = 1; i<str1.size(); i++) {
      if(str1[i] == '!') {
        str1.erase(0, i+1);
        atZero.assign(str1, 0, 1);
      }
    }
  }

  ////////// IF SEPARATOR //////////
  for(int i = 0; i<SEPARATORS_LIST.size(); i++) {
    if(atZero == SEPARATORS_LIST[i]) {
      pList.push_back(str1.substr(0, 1));
      str1.erase(0, 1);
      atZero.assign(str1, 0, 1);
    }
  }

  ////////// IF OPERATOR //////////
  for(int i = 0; i<OPERATOR_LIST.size(); i++) {
     if(atZero == OPERATOR_LIST[i]) {
      pList.push_back(str1.substr(0, 1));
      str1.erase(0, 1);
      atZero.assign(str1, 0, 1);
    }
  }

  } while(!str1.empty());

  return pList;
}

string readFile(string fname){
    string code, temp;
    ifstream myFile(fname);

    if(myFile.is_open()){ //open the file
      while(!myFile.eof()) //continue iterating until end of file
      {
        getline(myFile, temp); //store each line of code in a temp variable
        temp += " ";
        code += temp; //concatenate the code into one string
      }
    } else {
      return "Unable to open file\n"; //return an error that file is unable to open
    }
    return code;
}

int main() {

  vector<string> parsedList;
  string fileName = "Code.txt";
  string codeToParse = readFile(fileName);

  parsedList = parse(codeToParse);

  cout << "\nparsedList contains: \n\n";
  for(int i = 0; i<parsedList.size(); i++) {
      cout << parsedList[i] << "\n";
  }
  cout << "\nparsedList is size " << parsedList.size() << "\n\n";

  return 0;
}
