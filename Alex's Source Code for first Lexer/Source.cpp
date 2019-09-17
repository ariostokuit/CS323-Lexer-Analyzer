/************************************************************************
 * AUTHOR	  : Alex Mulvaney
 * STUDENT ID : 888841160
 * ASN#1      : FSM Lexeme Token Generator
 * CLASS      : CPSC323 Compilers and Languages
 * SECTION    : MW 11:30am
 * DUE DATE   : Sept 21, 2019 (first iteration for extra credit)
 * *********************************************************************/

#include <vector>
#include <iomanip>
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
// Global Constants
const vector<string> STATE_NAMES = { "initial state", "keyword", "id", "separator", "operator", "real", "Error state" };
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

int main()
{
	cout << STATE_NAMES[lexerFSM("23.0.0")] << endl;

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
