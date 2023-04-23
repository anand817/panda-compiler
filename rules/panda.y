%code requires {
    #include <iostream>
    #include <string>
    #include <base/nodes.hpp>
    #include <variables/nodes.hpp>
    #include <functions/nodes.hpp>
    #include <expressions/nodes.hpp>
    #include <conditionals/nodes.hpp>
    #include <loop/nodes.hpp>
    #include <utils/nodes.hpp>
    #include <enums/type_enum.hpp>
    #include <enums/operation_enum.hpp>
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
    FunctionDeclarationNode*        functionDeclarationNode;
    FunctionCallNode*               functionCallNode;
    PrintNode*                      printNode;
    InputNode*                      inputNode;
    ReturnStatementNode*            returnStatementNode;
    IfNode*                         ifNode;
    ForNode*                        forNode;
    WhileNode*                      whileNode;
    BreakNode*                      breakNode;
    ContinueNode*                   continueNode;
    VariableList*                   variableList;
    ArgumentList*                   argumentList;
    ExpressionNode*                 expressionNode;
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
/* %token <token> CONST */
%token <token> IF
%token <token> ELSE
%token <token> FOR
%token <token> WHILE
%token <token> BREAK
%token <token> CONTINUE
%token <token> RETURN
%token <token> PRINT
%token <token> INPUT

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
%type <variableList>            variable_list param_list
%type <argumentList>            expression_list argument_list
%type <statementNode>           statement for_init_statement
%type <blockNode>               statement_block
%type <variableDeclarationNode> variable_declaration
%type <functionDeclarationNode> function_declaration function_header
%type <functionCallNode>        function_call
%type <printNode>               print
%type <inputNode>               input
%type <variableDefinitionNode>  variable_definition
%type <returnStatementNode>     return_statement
%type <breakNode>               break_statement
%type <continueNode>            continue_statement
%type <ifNode>                  if_statement unmatched_if_statement matched_if_statement
%type <forNode>                 for_header for_statement
%type <whileNode>               while_statement
%type <typeNode>                type
%type <identifierNode>          identifier
%type <expressionNode>          expression for_expression
%type <valueNode>               value
%type <token>                   '-' '+' '*' '/' '%' '&' '|' '^' '~' '!' '<' '>' '=' '(' ')' '{' '}' '[' ']' ',' ':' ';'


// associativity

%right      '='
%left       LOGICAL_OR
%left       LOGICAL_AND
%left       '|'
%left       '^'
%left       '&'
%left       EQUAL NOT_EQUAL
%left       LESS_EQUAL GREATER_EQUAL '<' '>'
%left       SHR SHL
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

program:                /* epsilon */                                                           { programmeRoot = new StatementList(); $$ = nullptr; }
       |                statement_list                                                          { programmeRoot = $1; $$ = nullptr; }
       ;


statement_list:         statement                                                               { $$ = new StatementList(); $$->push_back($1); }
              |         statement_list statement                                                { $$ = $1; $$->push_back($2); }
              |         statement_block                                                         { $$ = new StatementList(); $$->push_back($1); }
              |         statement_list statement_block                                          { $$ = $1; $$->push_back($2); }
              ;
statement_block:        '{' '}'                                                                 { $$ = new BlockNode(); }
               |        '{' statement_list '}'                                                  { $$ = new BlockNode(*$2); delete $2; }
               ;

statement:              ';'                                                                     { $$ = new StatementNode(); }
         |              variable_declaration ';'                                                { $$ = $1; }
         |              variable_definition ';'                                                 { $$ = $1; }
         |              function_declaration                                                    { $$ = $1; }
         |              if_statement                                                            { $$ = $1; }
         |              for_statement                                                           { $$ = $1; }
         |              while_statement                                                         { $$ = $1; }
         |              expression ';'                                                          { $$ = $1; }
         |              return_statement ';'                                                    { $$ = $1; }
         |              break_statement ';'                                                     { $$ = $1; }
         |              continue_statement ';'                                                  { $$ = $1; }
         ;

if_statement:           unmatched_if_statement                                                  { $$ = $1; }
            |           matched_if_statement                                                    { $$ = $1; }
            ;

unmatched_if_statement: IF '(' expression ')' statement_block %prec IF_UNMAT                    { $$ = new IfNode($3, $5); }
                      ;

matched_if_statement:   IF '(' expression ')' statement_block ELSE statement_block              { $$ = new IfNode($3, $5, $7); }
                    ;

while_statement:        WHILE '(' expression ')' statement_block                                { $$ = new WhileNode($3, $5); }
               ;


for_statement:          for_header statement_block                                              { $$ = $1; $$->assignBody($2); }
             ;

for_header:             FOR '(' for_init_statement ';' for_expression ';' for_expression ')'    { $$ = new ForNode($3, $5, $7, NULL); }
          ;

for_init_statement:     /* epsilon */                                                           { $$ = NULL; }
                  |     variable_definition                                                    { $$ = $1; }
                  |     expression                                                              { $$ = $1; }
                  ;

for_expression:         /* epsilon */                                                           { $$ = NULL; }
              |         expression                                                              { $$ = $1; }
              ;

return_statement:       RETURN expression                                                       { $$ = new ReturnStatementNode($2); }
                |       RETURN                                                                  { $$ = new ReturnStatementNode(); }
                ;

break_statement:        BREAK                                                                   { $$ = new BreakNode(); }
               ;

continue_statement:     CONTINUE                                                                { $$ = new ContinueNode(); }
                  ;

variable_declaration:   type identifier                                                         { $$ = new VariableDeclarationNode(*$1, *$2); delete $1; delete $2; }
                    ;

function_header:        type identifier '(' param_list ')'                                      { $$ = new FunctionDeclarationNode(*$1, *$2, *$4, NULL); delete $1; delete $2; delete $4; }
               ;

function_declaration:   function_header statement_block                                         { $$ = $1; $$->assignBody($2); }
                    ;

function_call:          identifier '(' argument_list ')'                                        { $$ = new FunctionCallNode(*$1, *$3); delete $1; delete $3; }
             ;

print:                  PRINT '(' argument_list ')'                                             { $$ = new PrintNode(*$3); delete $3; }
input:                  INPUT '(' argument_list ')'                                             { $$ = new InputNode(*$3); delete $3; }
    
param_list:             /* epsilon */                                                           { $$ = new VariableList(); }
          |             variable_list                                                           { $$ = $1; }
          ;

variable_list:          variable_declaration                                                    { $$ = new VariableList(); $$->push_back(*$1); delete $1; }
             |          variable_list ',' variable_declaration                                  { $$ = $1; $$->push_back(*$3); delete $3; }
             ;

argument_list:          /* epsilon */                                                           { $$ = new ArgumentList(); }
             |          expression_list                                                         { $$ = $1; }
             ;

expression_list:        expression                                                              { $$ = new ArgumentList(); $$->push_back($1); }
               |        expression_list ',' expression                                          { $$ = $1; $$->push_back($3); }
               ;

variable_definition:    type identifier '=' expression                                          { $$ = new VariableDefinitionNode(*$1, *$2, $4); delete $1; delete $2; } // $4 passed as a pointer
                   ;

expression:             expression '+' expression                                               { $$ = new BinaryExpressionNode($1, $3, BINARY_OPERATOR::ADD); }
          |             expression '-' expression                                               { $$ = new BinaryExpressionNode($1, $3, BINARY_OPERATOR::SUBTRACT); }
          |             expression '*' expression                                               { $$ = new BinaryExpressionNode($1, $3, BINARY_OPERATOR::MULTIPLY); }
          |             expression '/' expression                                               { $$ = new BinaryExpressionNode($1, $3, BINARY_OPERATOR::DIVIDE); }
          |             expression '=' expression                                               { $$ = new BinaryExpressionNode($1, $3, BINARY_OPERATOR::ASSIGN); }
          |             expression '%' expression                                               { $$ = new BinaryExpressionNode($1, $3, BINARY_OPERATOR::MODULUS); }
          |             expression '|' expression                                               { $$ = new BinaryExpressionNode($1, $3, BINARY_OPERATOR::OR); }
          |             expression LOGICAL_OR expression                                        { $$ = new BinaryExpressionNode($1, $3, BINARY_OPERATOR::LOGICAL_OR); }
          |             expression '&' expression                                               { $$ = new BinaryExpressionNode($1, $3, BINARY_OPERATOR::AND); }
          |             expression LOGICAL_AND expression                                       { $$ = new BinaryExpressionNode($1, $3, BINARY_OPERATOR::LOGICAL_AND); }
          |             expression '^' expression                                               { $$ = new BinaryExpressionNode($1, $3, BINARY_OPERATOR::XOR); }
          |             expression SHL expression                                               { $$ = new BinaryExpressionNode($1, $3, BINARY_OPERATOR::SHIFT_LEFT); }
          |             expression SHR expression                                               { $$ = new BinaryExpressionNode($1, $3, BINARY_OPERATOR::SHIFT_RIGHT); }
          |             expression '>' expression                                               { $$ = new BinaryExpressionNode($1, $3, BINARY_OPERATOR::GREATER); }
          |             expression GREATER_EQUAL expression                                     { $$ = new BinaryExpressionNode($1, $3, BINARY_OPERATOR::GREATER_EQUAL); }
          |             expression '<' expression                                               { $$ = new BinaryExpressionNode($1, $3, BINARY_OPERATOR::LESSER); }
          |             expression LESS_EQUAL expression                                        { $$ = new BinaryExpressionNode($1, $3, BINARY_OPERATOR::LESSER_EQUAL); }
          |             expression EQUAL expression                                             { $$ = new BinaryExpressionNode($1, $3, BINARY_OPERATOR::EQUAL); }
          |             expression NOT_EQUAL expression                                         { $$ = new BinaryExpressionNode($1, $3, BINARY_OPERATOR::NOT_EQUAL); }

          |             '+' expression %prec U_PLUS                                             { $$ = new UnaryExpressionNode($2, UNARY_OPERATOR::UNARY_PLUS); }
          |             '-' expression %prec U_MINUM                                            { $$ = new UnaryExpressionNode($2, UNARY_OPERATOR::UNARY_MINUS); }
          |             '~' expression                                                          { $$ = new UnaryExpressionNode($2, UNARY_OPERATOR::NOT); }
          |             '!' expression                                                          { $$ = new UnaryExpressionNode($2, UNARY_OPERATOR::LOGICAL_NOT); }

          |             INC expression %prec PRE_INC                                            { $$ = new UnaryExpressionNode($2, UNARY_OPERATOR::PRE_INCREMENT); }
          |             DEC expression %prec PRE_DEC                                            { $$ = new UnaryExpressionNode($2, UNARY_OPERATOR::PRE_DECREMENT); } 
          |             expression INC %prec SUF_INC                                            { $$ = new UnaryExpressionNode($1, UNARY_OPERATOR::POST_INCREMENT); }
          |             expression DEC %prec SUF_DEC                                            { $$ = new UnaryExpressionNode($1, UNARY_OPERATOR::POST_DECREMENT); }

          |             '(' expression ')'                                                      { $$ = $2; }
          |             function_call                                                           { $$ = $1; }
          |             print                                                                   { $$ = $1; }
          |             input                                                                   { $$ = $1; }
          |             identifier                                                              { $$ = new IdentifierExpressionNode(*$1); delete $1; }
          |             value                                                                   { $$ = new ExpressionNode(*$1); delete $1; }
          ;

value:                  INTEGER                                                                 { $$ = new ValueNode(INT_TYPE, $1.value); }
     |                  CHAR                                                                    { $$ = new ValueNode(CHAR_TYPE, $1.value); }
     |                  BOOL                                                                    { $$ = new ValueNode(BOOL_TYPE, $1.value); }
     |                  FLOAT                                                                   { $$ = new ValueNode(FLOAT_TYPE, $1.value); }
     |                  STRING                                                                  { $$ = new ValueNode(STRING_TYPE, $1.value); }
     ;

type:                   TYPE_INT                                                                { $$ = new TypeNode(INT_TYPE); }
    |                   TYPE_CHAR                                                               { $$ = new TypeNode(CHAR_TYPE); }
    |                   TYPE_BOOL                                                               { $$ = new TypeNode(BOOL_TYPE); }
    |                   TYPE_FLOAT                                                              { $$ = new TypeNode(FLOAT_TYPE); }
    |                   TYPE_STRING                                                             { $$ = new TypeNode(STRING_TYPE); }
    |                   TYPE_VOID                                                               { $$ = new TypeNode(VOID_TYPE); }
    ;

identifier:             IDENTIFIER                                                              { $$ = new IdentifierNode($1.value); }
          ;


%%

void yyerror(const char* s) {
    std::cout << "Error: " << s << std::endl;
}