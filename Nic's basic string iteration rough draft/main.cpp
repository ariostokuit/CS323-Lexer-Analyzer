// Nicholas Webster

#include <iostream>
#include <string>

using namespace std;

string parse(string str1) {

  // Didn't feel like writing the input file function yet

  int indexStart = 0
  int indexEnd = 0;
  int count = 1;
  bool loopBreak = false;

  // ensure index[0] is a letter in this test case
  cout << "\nstr1[index] = " << str1[indexStart] << endl;

  if(isalpha(str1[indexStart]) && loopBreak == false) {
    for(int i=0; i<str1.length(); i++) {
      if(isalpha(str1[indexEnd+1]) && loopBreak==false) {
        indexEnd++;
        count++;
      } else {
        loopBreak = true;
        // all these cout statements are for testing
        cout << "indexStart is " << indexStart << endl;
        cout << "indexEnd is " << indexEnd << endl;
        cout << "count is " << count << endl;
        cout << "The substr is... " << str1.substr(indexStart, count) << endl;
        cout << "Deleting this substr from the string...\n";
        str1.erase(indexStart, count);
        cout << "New str1 is... " << str1;
        return str1;
      }
    }
  }

  //Can use the substr to pull the word from the str1.
  //From here, indexStart becomes indexEnd + 1. Rinse and repeat.
  //or...
  //return the str after removing the substr and use a while loop in main
  //    with the condition while(str!=empty)

  if(str1[indexStart] == '(' && ')') {
    cout << "seperator!\n";
    return str1;
  }

  if(isdigit(str1[indexStart])) {
    cout << "digit!\n";
    return str1;
  }

  if(isblank(str1[indexStart])) {
    cout << "blank!\n";
    return str1;
  }

}

int main() {

  string a = "while (fahr < upper) a = 23.00 whileend\n";
  string b = "(operator test case)\n";
  string c = "23 digit first test case\n";
  string d = " starts with a blank\n";

  cout << parse(a);
  cout << parse(b);
  cout << parse(c);
  cout << parse(d);

  return 0;
}
