%code requires {
    #include <iostream>
    #include <string>
    #include <base/nodes.hpp>
    #include <variables/nodes.hpp>
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
    TokenNode                       token; // not a pointer
    BlockNode*                      blockNode;
    ValueNode*                      valueNode;
    IdentifierNode*                 identifierNode;
    TypeNode*                       typeNode;
    StatementList*                  statementList;
    StatementNode*                  statementNode;
    VariableDeclarationNode*        variableDeclarationNode;
    VariableDefinitionNode*         variableDefinitionNode;
}

// Tokens Definition

// Data types
%token <token> TYPE_INT
%token <token> TYPE_FLOAT
%token <token> TYPE_CHAR
%token <token> TYPE_BOOL
%token <token> TYPE_VOID
%token <token> TYPE_STRING

// Keywords
%token <token> CONST
%token <token> IF
%token <token> ELSE
%token <token> FOR
%token <token> WHILE
%token <token> BREAK
%token <token> CONTINUE
%token <token> RETURN

// Operators
%token <token> INC
%token <token> DEC
%token <token> LOGICAL_AND
%token <token> LOGICAL_OR
%token <token> EQUAL
%token <token> NOT_EQUAL
%token <token> GREATER_EQUAL
%token <token> LESS_EQUAL

// Values
%token <token> INTEGER
%token <token> FLOAT
%token <token> CHAR
%token <token> BOOL
%token <token> STRING
%token <token> IDENTIFIER

// Non-terminal Symbols Types

%type <statementList>           program
%type <statementList>           statement_list
%type <statementNode>           statement
%type <blockNode>               statement_block
%type <variableDeclarationNode> variable_declaration
%type <variableDefinitionNode>  variable_definition
%type <typeNode>                type
%type <identifierNode>          identifier
%type <typeNode>                
%type <token>            '-' '+' '*' '/' '%' '&' '|' '^' '~' '!' '<' '>' '=' '(' ')' '{' '}' '[' ']' ',' ':' ';'


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

program:                /* epsilon */                       { programmeRoot = new StatementList(); $$ = nullptr; }
       |                statement_list                      { programmeRoot = $1; $$ = nullptr; }
       ;


statement_list:         statement                           { $$ = new StatementList(); $$->push_back($1); }
              |         statement_list statement            { $$ = $1; $$->push_back($2); }
              |         statement_block                     { $$ = new StatementList(); $$->push_back($1); }
              |         statement_list statement_block      { $$ = $1; $$->push_back($2); }
              ;

statement_block:        '{' '}'                             { $$ = new BlockNode(); }
               |        '{' statement_list '}'              { $$ = new BlockNode(*$2); delete $2; }

statement:              ';'                                 { $$ = new StatementNode(); }
         |              variable_declaration                { $$ = $1 }
         |              variable_definition                 { $$ = $1 }

variable_declaration:   type identifier ';'                 { $$ = new VariableDeclarationNode(*$1, *$2); delete $1; delete $2; }

variable_definition:    type identifier '=' 


%%

void yyerror(const char* s) {
    
}