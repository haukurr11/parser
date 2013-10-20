program ::= program id ;
            declarations
            subprogram_declarations
            compound statement
            .

identifier ::= id identifier_list'
'identifier ::= empty string | , id identifier_list'

declarations ::= declarations var identifier_list : type ; | ε

type ::= standard type | array [ num .. num ] of standard type

standard type ::= integer | real

subprogram_declarations ::= subprogram_declarations subprogram declaration ; | ε

subprogram declaration ::= subprogram head declarations compound statement

subprogram_head ::= function id arguments : standard type ;
                  | procedure id arguments ;

arguments ::= ( parameter list ) | ε

parameter list ::= identifier_list : type | parameter list ; identifier_list : type

compound_statement ::= begin optional statements end

optional statements ::= statement_list | ε

statement_list ::= statement | statement_list ; statement

statement ::= variable assignop expression
            | procedure_statement
            | compound statement
            | if expression then statement else statement
            | while expression do statement

variable ::= id | id [ expression ]

procedure_statement ::= id | id ( expression_list )

expression_list ::= expression | expression_list , expression

expression ::= simple expression | simple expression relop simple expression

simple expression ::= term | sign term | simple expression addop term

term ::= factor | term mulop factor

factor ::= variable | id ( expression_list ) | num | ( expression ) | not factor

sign ::= + | -
