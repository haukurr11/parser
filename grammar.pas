left recursive:
identifier_list ::= id ´identifier_list
´identifier_list ::=  , id ´identifier_list | ε
declarations ::= var identifier_list : type ; declarations | ε
subprogram_declarations ::= subprogram_declaration ; subprogram_declarations | ε
term ::= factor ´term
´term ::= mulop factor ´term | ε
simple_expression ::= term | sign term | simple_expression addop term
parameter_list ::= identifier_list : type | parameter_list ; identifier_list : type
expression_list ::= expression ´expression_list
´expression_list ::=  , expression ´expression_list | ε
statement_list ::= statement ´statement_list
´statement_list ::= statement_list ; statement ´statement_list | ε


non-left recursive:

program ::= program id ;
            declarations
            subprogram_declarations
            compound_statement
            .

type ::= standard_type | array [ num .. num ] of standard_type

standard_type ::= integer | real

subprogram_declaration ::= subprogram_head declarations compound_statement

subprogram_head ::= function id arguments : standard_type ;
                  | procedure id arguments ;

arguments ::= ( parameter_list ) | ε

compound_statement ::= begin optional_statements end

optional_statements ::= statement_list | ε

statement ::= variable assignop expression
            | procedure_statement
            | compound_statement
            | if expression then statement else statement
            | while expression do statement

variable ::= id | id [ expression ]

procedure_statement ::= id | id ( expression_list )

expression ::= simple_expression | simple_expression relop simple_expression

factor ::= variable | id ( expression_list ) | num | ( expression ) | not factor

sign ::= + | -
