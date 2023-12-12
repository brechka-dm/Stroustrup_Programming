#include <algorithm>
#include <cctype>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

set<string> conjunctions = {"and", "or", "but"};
set<string> nouns = {"birds", "fish", "c++"};
set<string> verbs = {"rules", "fly", "swim"};

string strToLowerCopy(string const& str) {
  string strCopy = str;
  transform(strCopy.begin(), strCopy.end(), strCopy.begin(),
            [](unsigned char c) { return tolower(c); });
  return strCopy;
}

bool isStringInSet(string const& word, set<string> const& wordSet) {
  string lowerWord = strToLowerCopy(word);
  return wordSet.find(lowerWord) != wordSet.end();
}

bool isConjunction(string const& word) {
  return isStringInSet(word, conjunctions);
}

bool isNoun(string const& word) { return isStringInSet(word, nouns); }

bool isVerb(string const& word) { return isStringInSet(word, verbs); }

bool isSimpleSentence(vector<string> const& words) {
  return isNoun(words[0]) && isVerb(words[1]);
}

bool isSentence(string const& str) {
  if (str.length() < 2) return 0;

  stringstream stream(str);
  vector<string> words;
  string word;
  bool sentenceFound = false;
  while (stream >> word) {
    if (sentenceFound && isConjunction(word)) {
      words.clear();
      sentenceFound = false;
      continue;
    }
    words.push_back(word);
    if (words.size() == 2) {
      if (isSimpleSentence(words)) sentenceFound = true;
      else return false;
    }
  }
  return sentenceFound;
}

int main() {
  string input;
  getline(cin, input);
  cout << isSentence(input);
  return 0;
}