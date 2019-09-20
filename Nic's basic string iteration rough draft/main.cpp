// Nicholas Webster

#include <vector>
#include <iomanip>
#include <iostream>
#include <string>
#include <algorithm>
#include <ctype.h>

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
      str.erase(0, i+1);
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
      if(periodCount > 1) {cout << "WARNING: MORE THAN ONE PERIOD DETECTED!\n";}
    } else {
      pL.push_back(str.substr(0, i+1));
      str.erase(0, i+1);
      return;
    }
  }
}

vector<string> parse(string str1) {

  vector<string> pList;
  string atZero;
/*DELETE THIS COMMENT BEFORE FINAL SUBMISSION
  I wasn't able to compare str1[0] == SEPARATORS_LIST[i]. That requires
  overloading the == operator (I think) and I didn't feel like doing that.
  So I created the 'atZero' string and set it equal to the first
  character in the string. Pretty janky but it works. Feel free to edit it

  Also, if there is more than one period in a number entry, it will give a
  warning but continue to run. You can edit this if you like.
*/
  do {

  atZero.assign(str1, 0, 1);

  ////////// IF LETTER //////////
  if(isalpha(str1[0])) {
    parseLetter(str1, pList);
  }

  ////////// IF NUMBER //////////
  if(isdigit(str1[0])) {
    parseNumber(str1, pList);
  }

  ////////// IF WHITESPACE //////////
  if(str1[0] == ' ') {
    str1.erase(0, 1);
  }

  ////////// IF COMMENT //////////
  if(str1[0] == '!') {
    for(int i = 1; i<str1.size(); i++) {
      if(str1[i] == '!') {
        str1.erase(0, i+1);
      }
    }
  }

  ////////// IF SEPARATOR OR OPERATOR //////////
  for(int i = 0; i<SEPARATORS_LIST.size(); i++) {
    if(atZero == SEPARATORS_LIST[i]) {
      pList.push_back(str1.substr(0, 1));
      str1.erase(0, 1);
    } else if(atZero == OPERATOR_LIST[i]) {
      pList.push_back(str1.substr(0, 1));
      str1.erase(0, 1);
    }
  }

  } while(!str1.empty());

  return pList;
}

int main() {

  vector<string> parsedList;
  string a = "25.0 25.0.0 25.0 wljsdgl34234$sdf4$(fahr < upper) a = 23.00 whileend";

  parsedList = parse(a);

  cout << "parsedList contains: \n\n";
  for(int i = 0; i<parsedList.size(); i++) {
      cout << parsedList[i] << "\n";
  }
  cout << "\nparsedList is size " << parsedList.size() << "\n\n";

  return 0;
}
