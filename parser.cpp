#include "parser.h"

bool Parser::tokenCodeIn(TokenCode tc, const TokenCode list[])
{
}

void Parser::recover(const TokenCode list[])
{
}

void Parser::getToken()
{
}

void Parser::match(TokenCode tc)
{
}

void Parser::setError(const std::string& err)
{
}

void Parser::expectedTokenCode(TokenCode tc)
{
}

TokenCode Parser::getTokenCode()
{
}

bool Parser::isNext(TokenCode tc)
{
}

void Parser::parseProgram()
{
}

void Parser::parseIdentifierList(EntryList& idList)
{
}

void Parser::parseIdentifierListPrime(EntryList& idList)
{
}

void Parser::parseDeclarations()
{
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
}

Parser::Parser(std::istream& input, std::ostream& output)
{
}

Parser::~Parser()
{
}

void Parser::parse()
{
}

SymbolTable* Parser::getSymbolTable()
{
}

int Parser::totalErrors()
{
}
