program ::= program id ;
            declarations
            subprogram declarations
            compound statement
            .

identifier list ::= id | identifier list , id

declarations ::= declarations var identifier list : type ; | ε

type ::= standard type | array [ num .. num ] of standard type

standard type ::= integer | real

subprogram_declarations ::= subprogram declarations subprogram declaration ; | ε

subprogram declaration ::= subprogram head declarations compound statement

subprogram_head ::= function id arguments : standard type ;
                  | procedure id arguments ;

arguments ::= ( parameter list ) | ε

parameter list ::= identifier list : type | parameter list ; identifier list : type

compound_statement ::= begin optional statements end

optional statements ::= statement list | ε

statement list ::= statement | statement list ; statement

statement ::= variable assignop expression
            | procedure statement
            | compound statement
            | if expression then statement else statement
            | while expression do statement

variable ::= id | id [ expression ]

procedure statement ::= id | id ( expression list )

expression list ::= expression | expression list , expression

expression ::= simple expression | simple expression relop simple expression

simple expression ::= term | sign term | simple expression addop term

term ::= factor | term mulop factor

factor ::= variable | id ( expression list ) | num | ( expression ) | not factor

sign ::= + | -
