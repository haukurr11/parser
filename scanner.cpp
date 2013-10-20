#include "scanner.h"
#include "lex.yy.cc"

Scanner::Scanner(SymbolTable* symbols, std::istream& input, std::ostream& output)
{
 m_symbolTable = symbols;
 m_lexer = new yyFlexLexer(&input,&output);
}
/*
Simply deletes the FlexLexer from memory
*/
Scanner::~Scanner()
{
  delete m_lexer;
}
/* 
Sets the TokenCode,DataType and OpType of the current Token
*/
void Scanner::setCurrentToken(TokenCode tc, DataType dt, OpType op)
{
  m_currentToken.setTokenCode(tc);
  m_currentToken.setDataType(dt);
  m_currentToken.setOpType(op);
}
/* 
Sets the TokenCode and DataType of the current Token
but also finds the given lexeme string in the symbol table
and connects it to the token.
If the entry is not found it is created and then set.
*/
void Scanner::setCurrentToken(TokenCode tc, DataType dt, const std::string& lexeme)
{
  m_currentToken.setTokenCode(tc);
  m_currentToken.setDataType(dt);
  SymbolTableEntry* ste = m_symbolTable->lookup(lexeme);
  if(ste == NULL)
    ste = m_symbolTable->insert(lexeme);
  m_currentToken.setSymTabEntry(ste);
  m_currentToken.setOpType(op_NONE);
}
/*
Returns the symbol table instance
*/
SymbolTable* Scanner::getSymbolTable(void)
{
  return m_symbolTable;
}
/*
Returns ands sets the next Token from the lexer
but skips whitespaces,tabs,newlines and comments
*/
Token* Scanner::nextToken(void)
{
  TokenCode tCode;
  std::string lex;
  do {
  tCode = static_cast<TokenCode>(m_lexer->yylex());
  } while(tCode == tc_SPACE || tCode == tc_COMMENT ||
         tCode == tc_NEWLINE || tCode == tc_TAB);
  lex = m_lexer->YYText();
  //Change the lexeme to lowercase(case insensitive)
  std::transform( lex.begin(), lex.end(), lex.begin(),::tolower );
  if(tCode == tc_ID || tCode == tc_NUMBER) {
    setCurrentToken(tCode,Type,lex); //add to symbol table
  }
  else {
    setCurrentToken(tCode,Type,Oper);
  }
  return &m_currentToken;
}
