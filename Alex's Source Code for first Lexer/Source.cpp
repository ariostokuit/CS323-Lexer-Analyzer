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

int main()
{
	cout << STATE_NAMES[lexerFSM("int")];

	return 0;

}

/*************************************************************************
 * lexerFSM
 * -----------------------------------------------------------------------
 * This function is our FSM (in progress) where input: string (to be determined)
 * will be iteratively stepped through to determine what state (see STATE_NAMES)
 * this string belongs into, if it is an acceptable state
	->Return an int parallel to the STATE_NAMES vector
		(ex: "while" -> returns 1 : STATE_NAMES[1] = "id/keyword")
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
	
	return currentState;
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
