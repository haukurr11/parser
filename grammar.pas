program ::= program id ;
            declarations
            subprogram_declarations
            compound_statement
            .

identifier_list ::= id identifier_list´
identifier_list´ ::=  , id identifier_list´ | ε

declarations ::= var identifier_list : type ; declarations | ε

type ::= standard_type | array [ num .. num ] of standard_type

standard_type ::= integer | real

subprogram_declarations ::= subprogram_declaration ; subprogram_declarations | ε

subprogram_declaration ::= subprogram_head declarations compound_statement

subprogram_head ::= function id arguments : standard_type ;
                  | procedure id arguments ;

arguments ::= ( parameter_list ) | ε

parameter_list ::= identifier_list : type parameter_list´
parameter_list´ ::= ; identifier_list : type parameter_list´ | ε

compound_statement ::= begin optional_statements end

optional_statements ::= statement_list | ε

statement_list ::= statement statement_list´
statement_list´ ::= ; statement statement_list´ | ε

statement ::= id statement´
            | compound_statement
            | if expression then statement else statement
            | while expression do statement
statement´ ::= assignop expression | [ expression ] assignop expression | ( expression_list ) | ε

variable ::= id variable´
variable´ ::= [ expression ] | ε

procedure_statement ::= id procedure_statement´
procedure_statement´ ::= ( expression_list ) | ε

expression_list ::= expression expression_list´
expression_list´ ::=  , expression expression_list´ | ε

expression ::= simple_expression expression´
expression´ ::= relop simple_expression | ε

simple_expression ::= term simple_expression´ | sign term simple_expression´
simple_expression´ ::= addop term simple_expression´ | ε

term ::= factor term´
term´ ::= mulop factor term´ | ε

factor ::= id factor´ | num | ( expression ) | not factor
factor´ ::= [ expression ] | ( expression_list) | ε

sign ::= + | -
