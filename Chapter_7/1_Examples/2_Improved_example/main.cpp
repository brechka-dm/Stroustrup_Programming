#include "Token.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

const string WELCOME_STRING =
    "Welcome to the calculator program!\n"
    "Please enter expressions containing floating point numbers.\n"
    "You can use \"+\", \"-\", \"*\", \"/\", \"!\" and \"(\", \")\" to create "
    "expression.\n"
    "Press \"=\" to get answer.\n"
    "Press \"q\" to exit program.";

double declaration() {
  Token t = ts.get();
  if (t.kind != name) error("\"name\" is expected in declaration");
  string varName = t.name;
  Token t2 = ts.get();
  if (t2.kind != '=') error("\"=\" missed in declaration of \"varName\"");
  double d = expression();
  defineName(varName, d);
  return d;
}

double statement() {
  Token t = ts.get();
  switch (t.kind) {
    case let:
      return declaration();
    default:
      ts.putback(t);
      return expression();
  }
}

void calculate() {
  while (cin) {
    try {
      cout << PROMPT;
      Token t = ts.get();
      while (t.kind == ANSWER_INSTRUCTION) t = ts.get();
      if (t.kind == EXIT_INSTRUCTION) return;
      ts.putback(t);
      cout << "=" << statement() << endl;
    } catch (exception& e) {
      cerr << e.what() << endl;
      cleanUpMess();
    }
  }
}

int main() {
  double val = 0;

  cout << WELCOME_STRING << endl;

  while (cin) {
    try {
      defineName("pi", 3.1415926535);
      defineName("e", 2.7182818284);
      calculate();
      return 0;
    } catch (exception& e) {
      cerr << e.what() << endl;
      return 1;
    } catch (...) {
      cerr << "exception \n";
      return 2;
    }
  }
  return 0;
}