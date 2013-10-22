#include "parser.h"

Parser::Parser(std::istream& input, std::ostream& output)
{
  m_symbolTable = new SymbolTable();
  m_lexan = new Scanner(m_symbolTable,input,output);
  m_totalErrors = 0;
  getToken();
}

Parser::~Parser()
{
  delete m_lexan;
  delete m_symbolTable;
}

void Parser::parse()
{
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
  for(int i=0;i<sizeof list;i++) {
    if(list[i] == tc)
      return true;
  }
  return false;
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
  /*
  program ::= program id ;
              declarations
              subprogram_declarations
              compound_statement
              .
  */
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
  /*
  identifier_list ::= id identifier_list´
  */
  match(tc_ID);
  EntryList el;
  parseIdentifierListPrime(el);
}

void Parser::parseIdentifierListPrime(EntryList& idList)
{
  /*
  identifier_list´ ::=  , id identifier_list´ | ε
  */
  if(isNext(tc_COMMA)) {
    match(tc_COMMA);
    match(tc_ID);
    parseIdentifierListPrime(idList);
  }
}

void Parser::parseDeclarations()
{
  /*
  declarations ::= var identifier_list : type ; declarations | ε
  */
  EntryList el;
  if(isNext(tc_VAR)) {
    match(tc_VAR);
    EntryList el;
    parseIdentifierList(el);
    match(tc_COLON);
    parseType();
    match(tc_SEMICOL);
    parseDeclarations();
  }
}

void Parser::parseType()
{
  /*
  type ::= standard_type | array [ num .. num ] of standard_type
  */
  if(isNext(tc_INTEGER) || isNext(tc_REAL))
    parseStandardType();
  else {
    match(tc_ARRAY);
    match(tc_LBRACKET);
    match(tc_NUMBER);
    match(tc_DOTDOT);
    match(tc_NUMBER);
    match(tc_RBRACKET);
    match(tc_OF);
    parseStandardType();
  }
}

void Parser::parseStandardType()
{
  /*
  standard_type ::= integer | real
  */
  if(isNext(tc_INTEGER))
    match(tc_INTEGER);
  else if(isNext(tc_REAL))
    match(tc_REAL);
  else {
    std::cout << "error!\n";
    exit(0);
  }
}

void Parser::parseSubprogramDeclarations()
{
  /*
  subprogram_declarations ::= subprogram_declaration ; subprogram_declarations | ε
  */
  if(isNext(tc_FUNCTION) || isNext(tc_PROCEDURE)) {
    parseSubprogramDeclaration();
    match(tc_SEMICOL);
    parseSubprogramDeclarations();
  }
}

void Parser::parseSubprogramDeclaration()
{
  /*
  subprogram_declaration ::= subprogram_head declarations compound_statement
  */
  parseSubprogramHead();
  parseDeclarations();
  parseCompoundStatement();
}

void Parser::parseSubprogramHead()
{
  /*
  subprogram_head ::= function id arguments : standard_type ;
                  | procedure id arguments ;
  */
  if(isNext(tc_FUNCTION)) {
    match(tc_FUNCTION);
    match(tc_ID);
    parseArguments();
    match(tc_COLON);
    parseStandardType();
    match(tc_SEMICOL);
  }
  else if(isNext(tc_PROCEDURE)) {
    match(tc_PROCEDURE);
    match(tc_ID);
    parseArguments();
    match(tc_SEMICOL);
  }
  else {
    std::cout << "error!\n";
    exit(0);
  }
}

void Parser::parseArguments()
{
  /*
  arguments ::= ( parameter_list ) | ε
  */
  if(isNext(tc_LPAREN)) {
    match(tc_LPAREN);
    parseParameterList();
    match(tc_RPAREN);
  }
}

void Parser::parseParameterList()
{
  /*
  parameter_list ::= identifier_list : type parameter_list´
  */
  EntryList el;
  parseIdentifierList(el);
  match(tc_COLON);
  parseType();
  parseParameterListPrime();
}

void Parser::parseParameterListPrime()
{
  /*
  parameter_list´ ::= ; identifier_list : type parameter_list´ | ε
  */
  EntryList el;
  if(isNext(tc_SEMICOL)) {
    match(tc_SEMICOL);
    parseIdentifierList(el);
    match(tc_COLON);
    parseType();
    parseParameterListPrime();
  }
}

void Parser::parseCompoundStatement()
{
  /*
  compound_statement ::= begin optional_statements end
  */
  match(tc_BEGIN);
  parseOptionalStatements();
  match(tc_END);
}

void Parser::parseOptionalStatements()
{
  /*
  optional_statements ::= statement_list | ε
  */
  if(isNext(tc_ID) || isNext(tc_BEGIN)
  || isNext(tc_IF) || isNext(tc_WHILE))
    parseStatementList();
}

void Parser::parseStatementList()
{
  /*
  statement_list ::= statement statement_list´
  */
  parseStatement();
  parseStatementListPrime();
}

void Parser::parseStatementListPrime()
{
  /*
  statement_list´ ::= ; statement statement_list´ | ε
  */
  if(isNext(tc_SEMICOL)) {
    match(tc_SEMICOL);
    parseStatement();
    parseStatementListPrime();
  }
}

void Parser::parseStatement()
{
  /*
  statement ::= id statement´
              | compound_statement
              | if expression then statement else statement
              | while expression do statement
  */
  if(isNext(tc_ID)) {
    match(tc_ID);
    SymbolTableEntry* st;
    parseStatementPrime(st);
  }
  else if(isNext(tc_BEGIN)) {
    parseCompoundStatement();
  }
  else if(isNext(tc_IF)) {
    match(tc_IF);
    parseExpression();
    match(tc_THEN);
    parseStatement();
    match(tc_ELSE);
    parseStatement();
  }
  else if(isNext(tc_WHILE)) {
    match(tc_WHILE);
    parseExpression();
    match(tc_DO);
    parseStatement();
  }
  else {
    std::cout << "error!\n";
    exit(0);
  }
}

void Parser::parseStatementPrime(SymbolTableEntry* prevEntry)
{
  /*
  statement´ ::= assignop expression | [ expression ] assignop expression | ( expression_list ) | ε
  */
  if(isNext(tc_ASSIGNOP)) {
    match(tc_ASSIGNOP);
    parseExpression();
  }
  else if(isNext(tc_LBRACKET)) {
    match(tc_LBRACKET);
    parseExpression();
    match(tc_RBRACKET);
    match(tc_ASSIGNOP);
    parseExpression();
  }
  else if(isNext(tc_LPAREN)) {
    match(tc_LPAREN);
    parseExpressionList(prevEntry);
    match(tc_RPAREN);
  }
}

SymbolTableEntry* Parser::parseVariable()
{
  /*
  variable ::= id variable´
  */
  match(tc_ID);
  SymbolTableEntry* st;
  parseVariablePrime(st);
}

SymbolTableEntry* Parser::parseVariablePrime(SymbolTableEntry* prevEntry)
{
  /*
  variable´ ::= [ expression ] | ε
  */
  if(isNext(tc_LBRACKET)) {
    match(tc_LBRACKET);
    parseExpression();
    match(tc_RBRACKET);
  }
}

void Parser::parseProcedureStatement()
{
  /*
  procedure_statement ::= id procedure_statement´
  */
  match(tc_ID);
  SymbolTableEntry* st;
  parseProcedureStatementPrime(st);
}

void Parser::parseProcedureStatementPrime(SymbolTableEntry* prevEntry)
{
  /*
  procedure_statement´ ::= ( expression_list ) | ε
  */
  if(isNext(tc_LPAREN)){
    parseExpressionList(prevEntry);
    match(tc_RPAREN);
  }
}

void Parser::parseExpressionList(SymbolTableEntry* prevEntry)
{
  /*
  expression_list ::= expression expression_list´
  */
  parseExpression();
  EntryList el;
  parseExpressionListPrime(el);
}

void Parser::parseExpressionListPrime(EntryList& expList)
{
  /*
  expression_list´ ::=  , expression expression_list´ | ε
  */
  if(isNext(tc_COMMA)){
    match(tc_COMMA);
    parseExpression();
    parseExpressionListPrime(expList);
  }
}

SymbolTableEntry* Parser::parseExpression()
{
  /*
  expression ::= simple_expression expression´
  */
  parseSimpleExpression();
  SymbolTableEntry* st;
  parseExpressionPrime(st);
}

SymbolTableEntry* Parser::parseExpressionPrime(SymbolTableEntry* prevEntry)
{
  /*
  expression´ ::= relop simple_expression | ε
  */
  if(isNext(tc_RELOP)) {
    match(tc_RELOP);
    parseSimpleExpression();
  }
}

SymbolTableEntry* Parser::parseSimpleExpression()
{
  /*
  simple_expression ::= term simple_expression´ | sign term simple_expression´
  */
  SymbolTableEntry* st;
  if(isNext(tc_ID)) {
    parseTerm();
    parseSimpleExpressionPrime(st);
  }
  else if(isNext(tc_ADDOP)) {
    parseSign();
    parseTerm();
    parseSimpleExpressionPrime(st);
  }
  else {
    std::cout << "error!\n";
    exit(0);
  }
}

SymbolTableEntry* Parser::parseSimpleExpressionPrime(SymbolTableEntry* prevEntry)
{
  /*
  simple_expression´ ::= addop term simple_expression´ | ε
  */
  if(isNext(tc_ADDOP)) {
    match(tc_ADDOP);
    parseTerm();
    parseSimpleExpressionPrime(prevEntry);
  }
}

SymbolTableEntry* Parser::parseTerm()
{
  /*
  term ::= factor term´
  */
  parseFactor();
  SymbolTableEntry* st;
  parseTermPrime(st);
}

SymbolTableEntry* Parser::parseTermPrime(SymbolTableEntry* prevEntry)
{
  /*
  term´ ::= mulop factor term´ | ε
  */
  if(isNext(tc_MULOP)) {
    parseFactor();
    parseTermPrime(prevEntry);
  }
}

SymbolTableEntry* Parser::parseFactor()
{
  /*
  factor ::= variable | id ( expression_list ) | num | ( expression ) | not factor
  */
}

SymbolTableEntry* Parser::parseFactorPrime(SymbolTableEntry* prevEntry)
{
}

void Parser::parseSign()
{
  /*
  sign ::= + | -
  */
  if(isNext(tc_ADDOP)){
    OpType op = m_currentToken->getOpType();
    if(op != op_PLUS || op != op_MINUS) {
      std::cout << "error!";
      exit(0);
      }
    match(tc_ADDOP);
  }
}

