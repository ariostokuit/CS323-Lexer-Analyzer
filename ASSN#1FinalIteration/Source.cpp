/************************************************************************
 * AUTHOR	  : Alex Mulvaney, Nicholas Webster, Ariosto Kuit
 * STUDENT ID : 888841160
 * ASN#1      : FSM Lexeme Token Generator
 * CLASS      : CPSC323 Compilers and Languages
 * SECTION    : MW 11:30am
 * DUE DATE   : Sept 28, 2019
 * *********************************************************************/

#include <vector>
#include <iomanip>
#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>
using namespace std;
// Global Constants
const vector<string> STATE_NAMES = { "initial state", "keyword", "identifier", "separator", "operator", "real", "Error state" };
const vector<string> KEYWORD_LIST = { "int", "float", "bool", "if", "else", "then", "endif", "while", "whileend", "do", "doend", "for", "forend", "input", "output", "and", "or" , "function" };
const vector<string> SEPARATORS_LIST = { "'", "(", ")", "[", "]", "{", "}", ",", ".", ":", ";", "!" };
const vector<string> OPERATOR_LIST = { "*", "+", "-", "=", "/", ">", "<", "%" };
// User Defined Types go here

// Prototypes go here
int lexerFSM(string testStr);
bool isLetter(char let);
bool isNum(char num);
bool isValidID(string strVal);
bool isValidReal(string strVal);
void lexerOutput(vector<string> aList);

vector<string> parse(string str1);
string readFile(string fname);

int main()
{
  vector<string> parsedList;
  string fileName = "Code.txt";
  string codeToParse = readFile(fileName);

  parsedList = parse(codeToParse);
  
  lexerOutput(parsedList);

	return 0;

}

/*************************************************************************
 * lexerFSM
 * -----------------------------------------------------------------------
 * This function is our FSM (in progress) where input: string (to be determined)
 * will be iteratively stepped through to determine what state (see STATE_NAMES)
 * this string belongs into, if it is an acceptable state
	->Return an int parallel to the STATE_NAMES vector
		(ex: "while" -> returns 1 : STATE_NAMES[1] = "keyword")
 *************************************************************************/
int lexerFSM(string testStr) {
	int currentState = 0;
	
	if (std::find(SEPARATORS_LIST.begin(), SEPARATORS_LIST.end(), testStr) != SEPARATORS_LIST.end()) {
		currentState = 3;	//STATE_NAMES[3] => "separator"
	}
	else if (std::find(OPERATOR_LIST.begin(), OPERATOR_LIST.end(), testStr) != OPERATOR_LIST.end()) {
		currentState = 4;
	}
	else if (std::find(KEYWORD_LIST.begin(), KEYWORD_LIST.end(), testStr) != KEYWORD_LIST.end()) {
		currentState = 1;
	}
	else if (isValidReal(testStr)) {
		currentState = 5;
	}
	else if (isValidID(testStr)) {
		currentState = 2;
	}
	else {
		currentState = 6;
	}
	
	return currentState;
}

/*************************************************************************
 * lexerOutput
 * -----------------------------------------------------------------------
 * HELPER FUNCTION to output the results of the lexerFSM
	->Return void
 *************************************************************************/
void lexerOutput(vector<string> aList) {
	ofstream outFile;
	stringstream ss;
	outFile.open("output.txt");


	// cout << "Tokens" << setw(19) << "Lexemes" << '\n';
	// cout << "----------------------------\n";
	ss << "Tokens" << setw(19) << "Lexemes" << '\n';
	ss << "----------------------------\n";
	for(int i = 0; i < aList.size(); i++) {
	  ss << left << setw(12) << STATE_NAMES[lexerFSM(aList[i])] << setw(6) << "=" << aList[i] << '\n';
  }
    cout << ss.str();
	outFile << ss.str();
	outFile.close();
}

/*************************************************************************
 * isValidID
 * -----------------------------------------------------------------------
 * HELPER FUNCTION to determine if an ID is valid syntax
 * valid syntax is as follows: MUST start with a letter, then can contain digits or $
	->Return boolean
 *************************************************************************/
bool isValidID(string strVal) {
	bool isValid = false;
	//initial check to see if the first char is a letter, following proper id syntax
	if (isLetter(strVal[0])) {
		for (int i = 1; i < strVal.length(); i++) {
			if (!isLetter(strVal[i]) &&
				!isNum(strVal[i]) &&
				(int)strVal[i] != 36) {
				//if the char is not a num, digit, or $ we break out of the loop not setting isValid to true
				isValid = false;
				break;
			}
			isValid = true;
		}
	}
	return isValid;

}

/*************************************************************************
 * isValidReal
 * -----------------------------------------------------------------------
 * HELPER FUNCTION to determine if a REAL number is valid syntax
 * valid syntax is as follows: must start with a digit, and can contain one '.' for float values
	->Return boolean
 *************************************************************************/
bool isValidReal(string strVal) {
	bool isValid = false;
	bool containsPeriod = false;
	//initial check to see if the real starts with a digit
	if (isNum(strVal[0])) {
		for (int i = 1; i < strVal.length(); i++)
		{
			//if the index pointed to is a '.' then set the flag that its a float
			if ((int)strVal[i] == 46 && !containsPeriod) {
				containsPeriod = true;
				i++;
			}
			//if the index is a '.' but already contains one then not a valid real
			//also if it reads a non digit, beside the period then it is also not a real
			if (((int)strVal[i] != 46 && !isNum(strVal[i])) ||
				((int)strVal[i] == 46 && containsPeriod)) {
				isValid = false;
				break;
			}
			
			isValid = true;
		}
	}
	return isValid;

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
    /*
      Checks for letters, numbers, and dollar signs.
      All three are valid for an identifier name.
      Once i+1 is not one of those three, it pushes the substring to the vector
        which was passed by reference.
      The FSM will later determine whether the string is
        a keyword or an identifier
    */
    for(int i=0; i<str1.length(); i++) {
      if(isalpha(str1[i+1]) || isdigit(str1[i+1]) || str1[i+1] == '$') {
        continue;
      } else {
        pList.push_back(str1.substr(0, i+1));
        str1.erase(0, i+1);
        break;
      }
    }
    atZero.assign(str1, 0, 1);
  }

  ////////// IF NUMBER //////////
  if(isdigit(str1[0])) {
  /* Allows for digits and only ONE period.
     If there's more than one period, output a warning and continue to run.
     The FSM will later determine if it is a real or integer. */
    int periodCount = 0;

    for(int i=0; i<str1.length(); i++) {
      if(isdigit(str1[i+1])) {
        continue;
      } else if(str1[i+1] == '.') {
        periodCount++;
        if(periodCount > 1) {cout << "\n\nWARNING: MORE THAN ONE PERIOD DETECTED!\n";}
      } else {
        pList.push_back(str1.substr(0, i+1));
        str1.erase(0, i+1);
        break;
      }
    }
    atZero.assign(str1, 0, 1);
  }

  ////////// IF WHITESPACE //////////
  if(isblank(str1[0])) {
    // All whitespaces are erased and the zero index is reassigned
    str1.erase(0, 1);
    atZero.assign(str1, 0, 1);
  }

  ////////// IF COMMENT //////////
  if(str1[0] == '!') {
    // Entire comments are erased and the zero index is reassigned
    for(int i = 1; i<str1.size(); i++) {
      if(str1[i] == '!') {
        str1.erase(0, i+1);
        atZero.assign(str1, 0, 1);
      }
    }
  }

  ////////// IF SEPARATOR //////////
  for(int i = 0; i<SEPARATORS_LIST.size(); i++) {
  /* Add seperator to the vector and erase from the string. Reassign zero index.
     For this assignment, all possible separators are single characters.
      example: "<<" is not yet accounted for. */
    if(atZero == SEPARATORS_LIST[i]) {
      pList.push_back(str1.substr(0, 1));
      str1.erase(0, 1);
      atZero.assign(str1, 0, 1);
    }
  }

  ////////// IF OPERATOR //////////
  for(int i = 0; i<OPERATOR_LIST.size(); i++) {
  /* Add operator to the vector and erase from the string. Reassign zero index.
     For this assignment, all possible operators are single characters.
      example: "==" is not yet accounted for. */
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

/*************************************************************************
 * isLetter
 * -----------------------------------------------------------------------
 * HELPER FUNCTION to determine if a character is a letter
	->Return boolean
 *************************************************************************/
bool isLetter(char let) {
	bool isLet = false;
	//if the letter is within the aschii parameters for the english alpha
	//then change isLet to true
	if (((int)let >= 65 && (int)let <= 90) ||
		((int)let >= 97 && (int)let <= 122)) {
		isLet = true;
	}
	return isLet;
}
/*************************************************************************
 * isNum
 * -----------------------------------------------------------------------
 * HELPER FUNCTION to determine if a character is a number
	->Return boolean
 *************************************************************************/
bool isNum(char num) {
	bool isNum = false;
	if ((int)num >= 48 && (int)num <= 57) {
		isNum = true;
	}
	return isNum;
}
