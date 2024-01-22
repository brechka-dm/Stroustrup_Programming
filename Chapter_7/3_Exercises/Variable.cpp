#include "Variable.h"

#include <sstream>

#include "Error.h"

using std::string;
using std::stringstream;

Variable::Variable() : pName({}), pValue(0.0), pIsConst(false) {}

Variable::Variable(const string& name, double value, bool isConst)
    : pName(name), pValue(value), pIsConst(isConst) {}

void Variable::setValue(double value) {
  if (pIsConst)
    error((stringstream() << R"(")" << pName << R"(" is const.)").str());
  pValue = value;
}