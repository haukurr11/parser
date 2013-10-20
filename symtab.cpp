#include "symtab.h"
/*
Symbol Table class
Able to insert lexemes into a symbol table and lookup these different lexemes
using pointers.
*/
SymbolTable::SymbolTable(void)
{

}
/*
The Deconstructer iterates through the symbol table and deletes the entries
*/
SymbolTable::~SymbolTable(void)
{
  EntryList::iterator it = m_table.begin();
  for(; it != m_table.end(); ++it) {
    delete *it;
  }
}
/*
The insert function creates a new instace of a SymbolTableEntry into
a pointer which points to the lexeme in the parameter. It pushes this
lexeme into the table, and then returns it.
*/
SymbolTableEntry* SymbolTable::insert(const std::string lexeme)
{
  SymbolTableEntry* ste = new SymbolTableEntry();
  ste->lexeme = lexeme;
  m_table.push_back(ste);
  return ste;
}
/*
The lookup function creates an iterator which begins at the front of
the table, and iterates through it until it finds the lexeme which 
was taken in as a parameter.
*/
SymbolTableEntry* SymbolTable::lookup(const std::string& lexeme)
{
  EntryList::iterator it = m_table.begin();
  for(;it != m_table.end(); ++it) {
    if( (*it)->lexeme == lexeme )
      return *it;
  }
  return NULL;
}
