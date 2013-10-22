#include "sourceline.h"
#include <iostream>

int LineError::getColumn()
{
  return m_column;
}

std::string LineError::getError()
{
  return m_errorMsg;
}

void LineError::set(int col, const std::string& err)
{
  m_column = col;
  m_errorMsg = err;
}

SourceLine::SourceLine()
{
  m_line = "";
  m_firstLexemeColumn = 0;
  m_lastLexemeColumn = 0;
  m_lineNo = 1;
}

void SourceLine::clearLine()
{
  m_line = "";
}

void SourceLine::printErrors()
{
  for(int i=0;i<m_errors.size();i++) {
    std::cout << m_errors[i].getError() << std::endl;
  }
}

void SourceLine::buildLine(const std::string& str)
{
  m_line += str;
  m_firstLexemeColumn = m_lastLexemeColumn+1;
  m_lastLexemeColumn += str.size();
}

void SourceLine::addError(const std::string& msg)
{
  LineError err;
  err.set(m_lastLexemeColumn, msg);
  m_errors.push_back(err);
}

bool SourceLine::hasError()
{
   return m_errors.size() != 0;
}

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

void SourceLine::newLine()
{
  m_lineNo++;
  m_firstLexemeColumn = 0;
  m_lastLexemeColumn = 0;
  m_errors.clear();
}
