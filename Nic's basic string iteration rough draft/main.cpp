// Nicholas Webster

#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<string> parse(string str1) {

  // Didn't feel like writing the input file function yet

  vector<string> pList;
  int indexStart = 0;
  int indexEnd = 0;
  bool loopBreak = false;

  // ensure index[0] is a letter in this test case
  cout << "\n\nstr1[index] = " << str1[indexStart] << endl;

  if(isalpha(str1[indexStart]) && loopBreak == false) {
    for(int i=0; i<str1.length(); i++) {
      if(isalpha(str1[indexEnd+1]) || isdigit(str1[indexEnd+1]) || str1[indexEnd+1] == '$' && loopBreak==false) {
        indexEnd++;
      } else {
        loopBreak = true;
        // all these cout statements are for testing
        cout << "indexStart is " << indexStart << endl;
        cout << "indexEnd is " << indexEnd << "\n\n";
        cout << "The substr is... " << str1.substr(indexStart, indexEnd+1) << endl;

        cout << "Adding substring to parsedList vector...\n";
        pList.push_back(str1.substr(indexStart, indexEnd+1));

        cout << "Deleting this substr from the string...\n";
        str1.erase(indexStart, indexEnd+1);
        cout << "New str1 is: " << str1 << "\n";
        return pList;
      }
    }
  }
  return pList;

  //Can use the substr to pull the word from the str1.
  //From here, indexStart becomes indexEnd + 1. Rinse and repeat.
  //
  // if(str1[indexStart] == '(' && ')') {
  //   cout << "seperator!\n";
  //   return str1;
  // }
  //
  // if(isdigit(str1[indexStart])) {
  //   cout << "digit!\n";
  //   return str1;
  // }
  //
  // if(isblank(str1[indexStart])) {
  //   cout << "blank!\n";
  //   return str1;
  // }

}

int main() {

  vector<string> parsedList;

  string a = "wljsdgl34234$sdf4$(fahr < upper) a = 23.00 whileend\n";
  string b = "(operator test case)\n";
  string c = "23 digit first test case\n";
  string d = " starts with a blank\n";

  parsedList = parse(a);
  // cout << parse(b);
  // cout << parse(c);
  // cout << parse(d);

  cout << "parsedList contains: ";
  cout << parsedList[0] << "\n\n";
  cout << "parsedList is size " << parsedList.size() << "\n\n";

  return 0;
}
