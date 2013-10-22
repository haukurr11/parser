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
  std::cout << m_currentToken->toString(m_currentToken) << " ";
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
  return tc == getTokenCode();
}

void Parser::parseProgram()
{
  std::cout << "[Program ";
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
  std::cout << " ]";
}

void Parser::parseIdentifierList(EntryList& idList)
{
  std::cout << "[IDList ";
  /*
  identifier_list ::= id identifier_list´
  */
  match(tc_ID);
  EntryList el;
  parseIdentifierListPrime(el);
  std::cout << " ]";
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
  std::cout << "[Declarations ";
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
  std::cout << " ]";
}

void Parser::parseType()
{
  std::cout << "[Type ";
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
  std::cout << " ]";
}

void Parser::parseStandardType()
{
  /*
  standard_type ::= integer | real
  */
  std::cout << "[StandardType ";
  if(isNext(tc_INTEGER))
    match(tc_INTEGER);
  else if(isNext(tc_REAL))
    match(tc_REAL);
  else {
    std::cout << "error!\n";
    exit(0);
  }
  std::cout << " ]";
}

void Parser::parseSubprogramDeclarations()
{
  /*
  subprogram_declarations ::= subprogram_declaration ; subprogram_declarations | ε
  */
  std::cout << "[SubProgramDeclarations ";
  if(isNext(tc_FUNCTION) || isNext(tc_PROCEDURE)) {
    parseSubprogramDeclaration();
    match(tc_SEMICOL);
    parseSubprogramDeclarations();
  }
  std::cout << " ]";
}

void Parser::parseSubprogramDeclaration()
{
  /*
  subprogram_declaration ::= subprogram_head declarations compound_statement
  */
  std::cout << "[SubProgramDeclaration ";
  parseSubprogramHead();
  parseDeclarations();
  parseCompoundStatement();
  std::cout << " ]";
}

void Parser::parseSubprogramHead()
{
  /*
  subprogram_head ::= function id arguments : standard_type ;
                  | procedure id arguments ;
  */
  std::cout << "[SubProgramHead ";
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
  std::cout << " ]";
}

void Parser::parseArguments()
{
  /*
  arguments ::= ( parameter_list ) | ε
  */
  std::cout << "[Arguments ";
  if(isNext(tc_LPAREN)) {
    match(tc_LPAREN);
    parseParameterList();
    match(tc_RPAREN);
  }
  std::cout << " ]";
}

void Parser::parseParameterList()
{
  /*
  parameter_list ::= identifier_list : type parameter_list´
  */
  std::cout << "[ParameterList ";
  EntryList el;
  parseIdentifierList(el);
  match(tc_COLON);
  parseType();
  parseParameterListPrime();
  std::cout << " ]";
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
  std::cout << "[CompoundStatement ";
  match(tc_BEGIN);
  parseOptionalStatements();
  match(tc_END);
  std::cout << " ]";
}

void Parser::parseOptionalStatements()
{
  /*
  optional_statements ::= statement_list | ε
  */
  std::cout << "[OptionalStatements ";
  if(isNext(tc_ID) || isNext(tc_BEGIN)
  || isNext(tc_IF) || isNext(tc_WHILE))
    parseStatementList();
  std::cout << " ]";
}

void Parser::parseStatementList()
{
  /*
  statement_list ::= statement statement_list´
  */
  std::cout << "[StatementList ";
  parseStatement();
  parseStatementListPrime();
  std::cout << " ]";
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
  std::cout << "[Statement ";
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
  std::cout << " ]";
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
  std::cout << "[Variable ";
  match(tc_ID);
  SymbolTableEntry* st;
  parseVariablePrime(st);
  std::cout << " ]";
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
  std::cout << "[Procedure ";
  match(tc_ID);
  SymbolTableEntry* st;
  parseProcedureStatementPrime(st);
  std::cout << " ]";
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
  std::cout << "[ExpressionList ";
  parseExpression();
  EntryList el;
  parseExpressionListPrime(el);
  std::cout << " ]";
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
  std::cout << "[Expression ";
  parseSimpleExpression();
  SymbolTableEntry* st;
  parseExpressionPrime(st);
  std::cout << " ]";
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
  std::cout << "[SimpleExpression ";
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
  std::cout << " ]";
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
  std::cout << "[Term ";
  parseFactor();
  SymbolTableEntry* st;
  parseTermPrime(st);
  std::cout << " ]";
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
  factor ::= id factor´ | num | ( expression ) | not factor
  */
  std::cout << "[Factor ";
  if(isNext(tc_ID)) {
    match(tc_ID);
    SymbolTableEntry* st;
    parseFactorPrime(st);
  }
  else if(isNext(tc_NUMBER)) {
    match(tc_NUMBER);
  }
  else if(isNext(tc_LPAREN)) {
    match(tc_LPAREN);
    parseExpression();
    match(tc_RPAREN);
  }
  else if(isNext(tc_NOT)) {
    match(tc_NOT);
    parseFactor();
  }
  else {
    std::cout << "ERROR!\n";
    exit(0);
  }
  std::cout << " ]";
}

SymbolTableEntry* Parser::parseFactorPrime(SymbolTableEntry* prevEntry)
{
  /*
  factor´ ::= [ expression ] | ( expression_list) | ε
  */
  if(isNext(tc_LBRACKET)) {
    match(tc_LBRACKET);
    parseExpression();
    match(tc_RBRACKET);
  }
  else if(isNext(tc_LPAREN)) {
    match(tc_LPAREN);
    parseExpressionList(prevEntry);
    match(tc_RPAREN);
  }
}

void Parser::parseSign()
{
  /*
  sign ::= + | -
  */
  std::cout << "[Sign ";
  if(isNext(tc_ADDOP)){
    OpType op = m_currentToken->getOpType();
    if(op != op_PLUS || op != op_MINUS) {
      std::cout << "error!";
      exit(0);
      }
    match(tc_ADDOP);
  }
  std::cout << " ]";
}

