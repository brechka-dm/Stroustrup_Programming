#include <iostream>
#include <set>

using namespace std;

const char INVALID_TOKEN = '_';

const set<char> specialSymbols = { '!', '~', '&', '^', '(', ')', 'L', '.'};

void error(string const& message) {
    cout << message << endl;
    exit(1);
}

class Token {
    char pKind = INVALID_TOKEN;

public:
    Token() : pKind(INVALID_TOKEN) {}
    explicit Token(char c) : pKind(c) {}
    char kind() const { return pKind; }
};

class TokenStream {
    bool pFull;
    Token pBuffer;

public:
    TokenStream() : pFull(false) {}
    Token get() {
        if (pFull) {
            pFull = false;
            return pBuffer;
        }

        char c;
        cin >> c;
        if (specialSymbols.find(c) != specialSymbols.end()) return Token(c);
        if (c >= 'a' && c <= 'z') return Token('L');
        error("Incorrect token: \"" + string(&c) + "\"");
        return Token();
    }

    void putback(Token const& t) {
        if (pFull) error("Token buffer is full. Unable o putback");
        pBuffer = t;
        pFull = true;
    }
};

TokenStream ts;

bool term2();

bool term() {
    Token t = ts.get();
    if (t.kind() == 'L') return true;
    ts.putback(t);
    return term2();
}

bool primaryTerm() {
    if (term()) return true;
    Token t = ts.get();
    if (t.kind() == '(') {
        bool isTerm = term();
        t = ts.get();
        return t.kind() == ')';
    }
    return false;
}

bool term0() {
    Token t = ts.get();
    switch (t.kind()) {
    case '~':
        return primaryTerm();
    case '!':
        return primaryTerm();
    }

    return false;
}

bool term1() {
    if (!term0()) return false;
    Token t = ts.get();
    if (t.kind() == '.')
    {
        ts.putback(t);
        return true;
    }
    if (t.kind() == '&') return term1();
    return false;
}

bool term2() {
    if (!term1()) return false;
    Token t = ts.get();
    if (t.kind() == '.') return true;
    if (t.kind() == '^') return term1();
    return false;
}

int main() {
    cout << boolalpha << term();
    return 0;
}