#include <algorithm>
#include <cctype>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

/*
 * This program is the solution to Exercise 5 of Chapter 6 of PROGRAMMING.
 * Principles and Practice Using C++. 2nd edition.
 * The program is a simple English grammar recognizer that allows you to
 * recognize sentences of the form 
 * Sentence = <article> <noun> <verb>
 * Sentence = <Sentence> [union Sentence]
 */

// Sets described in Chapter 21.
set<string> conjunctions = {"and", "or", "but"};
set<string> nouns = {"birds", "fish", "c++"};
set<string> verbs = {"rules", "fly", "swim"};
set<string> articles = {"the"};

// We use this function to convert the letters in a word to lower case, so that
// we don't have to process capital and small letter words separately.
string strToLowerCopy(string const& str) {
  // We make a copy of the function argument because the string changes inside
  // the function, but we don't want the string passed to the function by
  // reference to change.
  string strCopy = str;

  // transform described in:
  // https://en.cppreference.com/w/cpp/algorithm/transform
  transform(strCopy.begin(), strCopy.end(), strCopy.begin(),
            [](unsigned char c) { return tolower(c); });
  return strCopy;
}

// Auxiliary Function. Determines whether the word is in the wordSet.
bool isStringInSet(string const& word, set<string> const& wordSet) {
  string lowerWord = strToLowerCopy(word);
  return wordSet.find(lowerWord) != wordSet.end();
}

bool isConjunction(string const& word) {
  return isStringInSet(word, conjunctions);
}

bool isNoun(string const& word) { return isStringInSet(word, nouns); }

bool isVerb(string const& word) { return isStringInSet(word, verbs); }

bool isArticle(string const& word) { return isStringInSet(word, articles); }

bool isNounWithArticle(vector<string> const& words) {
  // There should be 2 words: article and noun.
  if (words.size() < 2) return false;
  return isArticle(words[0]) && isNoun(words[1]);
}

bool isSimpleSentence(vector<string> const& words) {
  // There may be 2 or 3 words: noun and verb or article, noun and verb.
  switch (words.size()) {
    case 2:
      return isNoun(words[0]) && isVerb(words[1]);
    case 3:
      return isNounWithArticle({words[0], words[1]}) && isVerb(words[2]);
  }
  return false;
}

bool isSentence(string const& str) {
  if (str.length() < 2) return 0;

  // stringstream described in Chapter 23. It will help us to split str to
  // separate words.
  stringstream stream(str);
  vector<string> words;
  string word;
  bool sentenceFound = false;

  // While there words in string.
  while (stream >> word) {
    if (sentenceFound && isConjunction(word)) {
      words.clear();
      sentenceFound = false;
      continue;
    }
    words.push_back(word);
    if (words.size() > 1 && words.size() <= 3 && isSimpleSentence(words))
      sentenceFound = true;
    if (words.size() > 3) return false;
  }
  return sentenceFound;
}

int main() {
  string input;
  getline(cin, input);
  cout << boolalpha << isSentence(input);
  return 0;
}