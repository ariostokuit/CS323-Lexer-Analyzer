// Nicholas Webster

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
    All three are valid for a variable name.
    Once i+1 is not one of those three, it pushes the substring to the vector
      which was passed by reference.
    The FSM will later determie whether the string is a keyword or variable name
  */
  for(int i=0; i<str.length(); i++) {
    if(isalpha(str[i+1]) || isdigit(str[i+1]) || str[i+1] == '$') {
      continue;
    } else {
      pL.push_back(str.substr(0, i+1));
      cout << "\n\nDeleting letter: " << str.substr(0, i+1);
      str.erase(0, i+1);
      cout << "\nReturning to parse() funct\n";
      return;
    }
  }
}

void parseNumber(string &str, vector<string> &pL) {
  /*
    parseNumber allows for digits and only ONE period.
    If there's more than 1 period, cout warning and continue running.
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
      cout << "\n\nDeleting number: " << str.substr(0, i+1);
      str.erase(0, i+1);
      return;
    }
  }
}

vector<string> parse(string str1) {

  vector<string> pList;
  string atZero;
  string newLineCheck;
/*DELETE THIS COMMENT BEFORE FINAL SUBMISSION
  I wasn't able to compare str1[0] == SEPARATORS_LIST[i]. That requires
  overloading the == operator (I think) and I didn't feel like doing that.
  So I created the 'atZero' string and set it equal to the first
  character in the string. Pretty janky but it works. Feel free to edit it

  Also, if there is more than one period in a number entry, it will give a
  warning but continue to run. You can edit this if you like.
*/
  do {

  cout << "\nAssigning new atZero\n";
  atZero.assign(str1, 0, 1);
  newLineCheck.assign(str1, 0, 2);

  ////////// IF LETTER //////////
  if(isalpha(str1[0])) {
    parseLetter(str1, pList);
    cout << "\nDone deleting letter";
  }

  ////////// IF NUMBER //////////
  if(isdigit(str1[0])) {
    parseNumber(str1, pList);
    cout << "\nDone deleting number";
  }

  ////////// IF WHITESPACE //////////
  if(str1[0] == ' ') {
    cout << "\n\nDeleting ws " << str1.substr(0, 1);
    str1.erase(0, 1);
    cout << "\nDone deleting ws";
  }

  ////////// IF COMMENT //////////
  if(str1[0] == '!') {
    for(int i = 1; i<str1.size(); i++) {
      if(str1[i] == '!') {
        cout << "\n\nDeleting comment: " << str1.substr(0, i+1);
        str1.erase(0, i+1);
      }
    }
    cout << "\nDone deleting comment";
  }

  ////////// IF NEWLINE //////////
  // if(newLineCheck == '\n') {
  //   str1.erase(0, 2);
  //   cout << "\nDone deleting comment!\n";
  // }

  ////////// IF SEPARATOR OR OPERATOR //////////
  for(int i = 0; i<SEPARATORS_LIST.size(); i++) {
    if(atZero == SEPARATORS_LIST[i]) {
      pList.push_back(str1.substr(0, 1));
      cout << "\n\nDeleting sep: " << str1.substr(0, 1);
      str1.erase(0, 1);
      cout << "\nDone deleting sep";
    } else if(atZero == OPERATOR_LIST[i]) {
      pList.push_back(str1.substr(0, 1));
      cout << "\n\nDeleting op: " << str1.substr(0, 1) << "\n\n";
      str1.erase(0, 1);
      cout << "\nDone deleting op";
    }
  }

  } while(!str1.empty());

  return pList;
}

string readFile(string fname){
    string code = "";
    string temp;
    ifstream myFile(fname);

    if(myFile.is_open()){ //open the file
      while(!myFile.eof()) //continue iterating until end of file
      {
        getline(myFile,temp,'\0'); //store each line of code in a temp variable
        code += temp; //concatenate the code into one string
      }
    } else {
      return "Unable to open file\n"; //return an error that file is unable to open
    }
    return code;
}

int main() {

  string file = "Code.txt";
  string code = readFile(file);
  cout << code;

  vector<string> parsedList;
  string a = "gl34234$sdf4$(fahr < upper) a = 23.00 whileend";
  //delete this^^
  parsedList = parse(code);

  cout << "\nparsedList contains: \n";
  for(int i = 0; i<parsedList.size(); i++) {
      cout << parsedList[i] << "\n";
  }
  cout << "\nparsedList is size " << parsedList.size() << "\n\n";

  return 0;
}
