%code requires {
    #include <iostream>
    #include <string>
    #include <base/nodes.hpp>
    #include <utils/nodes.hpp>
    using namespace std;
}

%code {
    // External functions & variables
    extern int yylex();
    // Functions prototypes
    void yyerror(const char* s);
    // Global variables
    StatementList* programmeRoot = nullptr;
}

// Symbol Types

%union {
    BlockNode*                      blockNode;
    TokenNode*                      tokenNode;
    ValueNode*                      valueNode;
    TypeNode*                       typeNode;
    StatementList*                  statementList;
    StatementNode*                  statementNode;
}

// Tokens Definition

// Data types
%token <typeNode> TYPE_INT
%token <typeNode> TYPE_FLOAT
%token <typeNode> TYPE_CHAR
%token <typeNode> TYPE_BOOL
%token <typeNode> TYPE_VOID
%token <typeNode> TYPE_STRING

// Keywords
%token <tokenNode> CONST
%token <tokenNode> IF
%token <tokenNode> ELSE
%token <tokenNode> FOR
%token <tokenNode> WHILE
%token <tokenNode> BREAK
%token <tokenNode> CONTINUE
%token <tokenNode> RETURN

// Operators
%token <tokenNode> INC
%token <tokenNode> DEC
%token <tokenNode> LOGICAL_AND
%token <tokenNode> LOGICAL_OR
%token <tokenNode> EQUAL
%token <tokenNode> NOT_EQUAL
%token <tokenNode> GREATER_EQUAL
%token <tokenNode> LESS_EQUAL

// Values
%token <valueNode> INTEGER
%token <valueNode> FLOAT
%token <valueNode> CHAR
%token <valueNode> BOOL
%token <valueNode> IDENTIFIER
%token <valueNode> STRING

// Non-terminal Symbols Types

%type <statementList>        program
%type <statementList>        statement_list
%type <statementNode>        statement
%type <blockNode>            statement_block
%type <tokenNode>            '-' '+' '*' '/' '%' '&' '|' '^' '~' '!' '<' '>' '=' '(' ')' '{' '}' '[' ']' ',' ':' ';'


// associativity

%right      '='
%left       LOGICAL_OR
%left       LOGICAL_AND
/* %left       '|' */
/* %left       '^' */
/* %left       '&' */
%left       EQUAL NOT_EQUAL
%left       LESS_EQUAL GREATER_EQUAL '<' '>'
/* %left       SHR SHL */
%left       '-' '+'
%left       '*' '/' '%'
%right      '!' '~'
%right      U_PLUS U_MINUM
%right      PRE_INC PRE_DEC
%left       SUF_INC SUF_DEC

%nonassoc   IF_UNMAT
%nonassoc   ELSE

%%

// Rules Section

program:            /* epsilon */                       { programmeRoot = new StatementList(); $$ = nullptr; }
       |            statement_list                      { programmeRoot = $1; $$ = nullptr; }
       ;


statement_list:     statement                           { $$ = new StatementList(); $$->push_back($1); }
              |     statement_list statement            { $$ = $1; $$->push_back($2); }
              |     statement_block                     { $$ = new StatementList(); $$->push_back($1); }
              |     statement_list statement_block      { $$ = $1; $$->push_back($2); }
              ;

statement_block:    '{' '}'                             { $$ = new BlockNode(); }
               |    '{' statement_list '}'              { $$ = new BlockNode(*$2); delete $2; }

statement:          ';'                                 { $$ = new StatementNode(); }


%%

void yyerror(const char* s) {
    
}