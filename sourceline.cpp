#include "sourceline.h"
#include <iostream>
//Returns the member variable which stores column position.
int LineError::getColumn()
{.
  return m_column;
}
//Return the error message being stored in the member variable errorMsg.
std::string LineError::getError()
{
  return m_errorMsg;
}
//Sets the member variables to what was passed in as parameter.
void LineError::set(int col, const std::string& err)
{
  m_column = col;
  m_errorMsg = err;
}
//Constructor which sets the starting position for the error handling.
SourceLine::SourceLine()
{
  m_line = "";
  m_firstLexemeColumn = 0;
  m_lastLexemeColumn = 0;
  m_lineNo = 1;
}
//Clears the line by resetting the member variable line to an empty string.
void SourceLine::clearLine()
{
  m_line = "";
}
//Function which loops through the error list and writes them out to the console.
void SourceLine::printErrors()
{
  for(int i=0;i<m_errors.size();i++) {
    std::cout << m_errors[i].getError() << std::endl;
  }
}
//Function which sets the member variable line to the current line in the program and  
void SourceLine::buildLine(const std::string& str)
{
  m_line += str;
  m_firstLexemeColumn = m_lastLexemeColumn+1;
  m_lastLexemeColumn += str.size();
}
//Adds errors into the member list.
void SourceLine::addError(const std::string& msg)
{
  LineError err;
  err.set(m_lastLexemeColumn, msg);
  m_errors.push_back(err);
}
//Checks if the error list is empty or not.
bool SourceLine::hasError()
{
   return m_errors.size() != 0;
}
//Prints the line stored in the member variable to the console, gets the column number where the error was found and prints out the correct error message for it.
void SourceLine::printLine()
{
  std::cout << m_line << std::endl;
  for(int i=0;i<m_errors.size();i++) {
    for(int j=0;j<=m_errors[i].getColumn();j++){
      std::cout << " ";
    }
    std::cout << "^" << m_errors[i].getError() << std::endl;
  }
}
//Creates a new line for the error handling and clears all previous errors from the member list.
void SourceLine::newLine()
{
  m_lineNo++;
  m_firstLexemeColumn = 0;
  m_lastLexemeColumn = 0;
  m_errors.clear();
}
