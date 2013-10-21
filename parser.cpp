#include "parser.h"

Parser::Parser(std::istream& input, std::ostream& output)
{
  m_symbolTable = new SymbolTable();
  m_lexan = new Scanner(m_symbolTable,input,output);
}

Parser::~Parser()
{
  delete m_lexan;
  delete m_symbolTable;
}

void Parser::parse()
{
  getToken();
  parseProgram();
}

SymbolTable* Parser::getSymbolTable()
{
  return m_symbolTable;
}

int Parser::totalErrors()
{
  return m_totalErrors;
}

bool Parser::tokenCodeIn(TokenCode tc, const TokenCode list[])
{

}

void Parser::recover(const TokenCode list[])
{
}

void Parser::getToken()
{
  m_currentToken = m_lexan->nextToken();
}

void Parser::match(TokenCode tc)
{
  if(getTokenCode() != tc) {
    std::cout << "error!";
    exit(0);
  }
  getToken();
}

void Parser::setError(const std::string& err)
{
}

void Parser::expectedTokenCode(TokenCode tc)
{
}

TokenCode Parser::getTokenCode()
{
  return m_currentToken->getTokenCode();
}

bool Parser::isNext(TokenCode tc)
{
  getToken();
  return tc == getTokenCode();
}

void Parser::parseProgram()
{
  match(tc_PROGRAM);
  match(tc_ID);
  match(tc_SEMICOL);
  parseDeclarations();
  parseSubprogramDeclarations();
  parseCompoundStatement();
  match(tc_DOT);
}

void Parser::parseIdentifierList(EntryList& idList)
{
  match(tc_ID);
}

void Parser::parseIdentifierListPrime(EntryList& idList)
{
}

void Parser::parseDeclarations()
{
  if(isNext(tc_VAR)) {
    parseIdentifierList();
    match(tc_COLON);
    parseType();
    match(tc_SEMICOL);
    parseParameterList();
  }
}

void Parser::parseType()
{
}

void Parser::parseStandardType()
{
}

void Parser::parseSubprogramDeclarations()
{
}

void Parser::parseSubprogramDeclaration()
{
}

void Parser::parseSubprogramHead()
{
}

void Parser::parseArguments()
{
}

void Parser::parseParameterList()
{
}

void Parser::parseParameterListPrime()
{
}

void Parser::parseCompoundStatement()
{
}

void Parser::parseOptionalStatements()
{
}

void Parser::parseStatementList()
{
}

void Parser::parseStatementListPrime()
{
}

void Parser::parseStatement()
{
}

void Parser::parseStatementPrime(SymbolTableEntry* prevEntry)
{
}

SymbolTableEntry* Parser::parseVariable()
{
}

SymbolTableEntry* Parser::parseVariablePrime(SymbolTableEntry* prevEntry)
{
}

void Parser::parseProcedureStatement()
{
}

void Parser::parseProcedureStatementPrime(SymbolTableEntry* prevEntry)
{
}

void Parser::parseExpressionList(SymbolTableEntry* prevEntry)
{
}

void Parser::parseExpressionListPrime(EntryList& expList)
{
}

SymbolTableEntry* Parser::parseExpression()
{
}

SymbolTableEntry* Parser::parseExpressionPrime(SymbolTableEntry* prevEntry)
{
}

SymbolTableEntry* Parser::parseSimpleExpression()
{
}

SymbolTableEntry* Parser::parseSimpleExpressionPrime(SymbolTableEntry* prevEntry)
{
}

SymbolTableEntry* Parser::parseTerm()
{
}

SymbolTableEntry* Parser::parseTermPrime(SymbolTableEntry* prevEntry)
{
}

SymbolTableEntry* Parser::parseFactor()
{
}

SymbolTableEntry* Parser::parseFactorPrime(SymbolTableEntry* prevEntry)
{
}

void Parser::parseSign()
{
  if(isNext(tc_ADDOP)){
    OpType op = m_currentToken->getOpType();
    if(op != op_PLUS || op != op_MINUS) {
      std::cout << "error!";
      exit(0);
      }
    match(tc_ADDOP);
  }
}

