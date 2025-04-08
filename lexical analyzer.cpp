
#include <iostream>
#include <string>
#include <cctype>

using namespace std;

int charClass;
string  lexeme;
char nextChar;
int token;
int nextToken;
string inputExpr;
size_t exprPos = 0;

void addChar();
void getChar();
void getNonBlank();
int lex();

const int LETTER = 0;
const int DIGIT = 1;
const int UNKNOWN = 99;
const int INT_LIT = 30;
const int IDENT = 40;
const int ASSIGN_OP = 50;
const int ADD_OP = 60;
const int SUB_OP = 70;
const int MULT_OP = 80;
const int DIV_OP = 85;
const int LEFT_PAREN = 88;
const int RIGHT_PAREN = 89;

int main() {
    cout << "Enter an arithmetic expression: ";
    getline(cin, inputExpr);

    getChar();
    do {
        lex();
    } while (nextToken != EOF && exprPos <= inputExpr.length());

    return 0;
}

int lookup(char ch) {
    switch (ch) {
    case '(':
        addChar();
        nextToken = LEFT_PAREN;
        break;
    case ')':
        addChar();
        nextToken = RIGHT_PAREN;
        break;
    case '+':
        addChar();
        nextToken = ADD_OP;
        break;
    case '-':
        addChar();
        nextToken = SUB_OP;
        break;
    case '*':
        addChar();
        nextToken = MULT_OP;
        break;
    case '/':
        addChar();
        nextToken = DIV_OP;
        break;
    default:
        addChar();
        nextToken = EOF;
        break;
    }
    return nextToken;
}

void addChar() {
    lexeme += nextChar;
}

void getChar() {
    if (exprPos < inputExpr.length()) {
        nextChar = inputExpr[exprPos++];
        if (isalpha(nextChar))
            charClass = LETTER;
        else if (isdigit(nextChar))
            charClass = DIGIT;
        else
            charClass = UNKNOWN;
    }
    else {
        charClass = EOF;
    }
}

void getNonBlank() {
    while (isspace(nextChar))
        getChar();
}

int lex() {
    lexeme.clear();
    getNonBlank();

    switch (charClass) {
    case LETTER:
        addChar();
        getChar();
        while (charClass == LETTER || charClass == DIGIT) {
            addChar();
            getChar();
        }
        nextToken = IDENT;
        break;

    case DIGIT:
        addChar();
        getChar();
        while (charClass == DIGIT) {
            addChar();
            getChar();
        }
        nextToken = INT_LIT;
        break;

    case UNKNOWN:
        lookup(nextChar);
        getChar();
        break;

    case EOF:
        nextToken = EOF;
        lexeme = "EOF";
        break;
    }

    cout << "Next token is: " << nextToken
        << ", Next lexeme is " << lexeme << endl;
    return nextToken;
}