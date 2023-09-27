#ifndef SVM_PARSER
#define SVM_PARSER

#include <string>
#include <unordered_map>
#include "svm.hh"

using namespace std;

class Token {
public:
  enum Type { ID=0, LABEL, NUM, EOL, ERR, END, PUSH, JMPEQ, JMPGT, JMPGE, JMPLT, JMPLE, GOTO, SKIP, POP, DUP, SWAP, ADD, SUB, MUL, DIV, STORE, LOAD, PRINT };
  static const char* token_names[24]; 
  Type type;
  string lexema;
  Token(Type);
  Token(Type, char c);
  Token(Type, const string source);
  static Instruction::IType tokenToIType(Token::Type tt);
   Instruction* parseInstruction();
  Instruction* parseNumericInstruction(const string& label, Token::Type ttype);
  Instruction* parseLabelInstruction(const string& label, Token::Type ttype);
};

std::ostream& operator << ( std::ostream& outs, const Token* tok );

class Scanner {
public:
  Scanner(string in_s);
  Token* nextToken();
  ~Scanner();
private:
  string input;
  int first, current;
  int state;
  unordered_map<string, Token::Type> reserved;
  char nextChar();
  void rollBack();
  void startLexema();
  void incrStartLexema();
  string getLexema();
  Token::Type checkReserved(string lexema);
};


class Parser {
private:
  Scanner* scanner;
  Token *current, *previous;
  bool match(Token::Type ttype);
  bool check(Token::Type ttype);
  bool advance();
  bool isAtEnd();
  Instruction* parseInstruction();
public:
  Parser(Scanner* scanner);
  SVM* parse();
};


#endif
