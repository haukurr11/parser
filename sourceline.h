// **************************************************************
// *                                                            *
// *    S O U R C E L I N E   (Header)                          *
// *                                                            *
// *    CLASSES:              SourceLine                        *
// *                                                            *
// **************************************************************

#ifndef  sourceline_h
#define  sourceline_h

#include <string>
#include <vector>

#define MAX_ERRORS_IN_LINE 10

class LineError
{
private:                        /* A class consisting of            */
  int          m_column;      /* the column number of the error   */
  std::string  m_errorMsg;    /* and the associated error message */
public:
  int         getColumn();
  std::string getError();
  void        set(int col, const std::string& err); /* Set column number and error */
};


class SourceLine {

private:
  std::string m_line;          // Characters in current line 
  int m_firstLexemeColumn;  // First column number of current lexeme
  int m_lastLexemeColumn;    // Last column number of current lexeme
  int m_lineNo;        // Line number in original source
  std::vector<LineError> m_errors;

  void clearLine();      // clears the line
  void printErrors();      // prints error messages in current line

public:
  SourceLine();

  void buildLine(const std::string& str);  // builds the line
  void addError(const std::string& msg);  // sets an error message
  bool hasError();            // has an error been recorded by this line 
  void printLine();            // prints the line and error messages in line if any
  void newLine();              // announces a new line in the input
};

#endif
