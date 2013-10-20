#include "token.h"
/*
The Token class main objective is to get or set the TokenCode,
DataType or OpType of lexemes which have been inserted into a
Symbol Table.
*/

/*
Simply initializes the member variable which holds the symbol
table entry.
*/
Token::Token(void)
{
 m_symtabEntry = NULL;
}
/*
Deletes the instance of symbol table entry.
*/
Token::~Token()
{
  delete m_symtabEntry;
}
/*
Returns the TokenCode of a lexeme.
*/
TokenCode Token::getTokenCode(void) const
{
  return m_tokenCode;
}
/*
Returns the DataType of a lexeme.
*/
DataType Token::getDataType(void) const
{
  return m_dataType;
}
/*
Returns the OpType of a lexeme.
*/
OpType  Token::getOpType(void) const
{
  return m_opType;
}
/*
Returns the symbol table entry of a lexeme.
*/
SymbolTableEntry* Token::getSymTabEntry(void) const
{
  return m_symtabEntry;
}
/*
Sets the TokenCode parameter of a lexeme to what was indicated in the parameter.
*/
void Token::setTokenCode(const TokenCode tc)
{
   m_tokenCode = tc;
}
/*
Sets the DataType of the lexeme to what was indicated in the parameter.
*/
void Token::setDataType(const DataType dt)
{
   m_dataType = dt;
}
/*
Sets the OpType of the lexeme to what was indicated in the parameter.
*/
void Token::setOpType(const OpType op)
{
  m_opType = op;
}
/*
Sets the symbol table entry to what was indicated in the parameter.
*/
void Token::setSymTabEntry(SymbolTableEntry* entry)
{
  m_symtabEntry = entry;
}
/*
Returns the OpType as a string object.
*/
std::string Token::opTypeToString(void)
{
  return CodeOpToString(m_opType);
}
/*
Returns the TokenCode as a string object.
*/
std::string Token::tokenCodeToString(void)
{
  std::string tk = TokenCodeToString(m_tokenCode);
  if( m_tokenCode == tc_NUMBER || m_tokenCode == tc_ID ) {
    tk += ("(" + m_symtabEntry->lexeme + ")");
  }
  else if( m_opType != op_NONE && m_dataType == dt_OP ) {
    tk += ("(" + OpTypeToString(m_opType) + ")");
  }
  return tk;
}
