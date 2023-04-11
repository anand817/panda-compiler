DIGIT [0-9]
NUMBER {DIGIT}+
FLOAT ({DIGIT}*\.{DIGIT}*)
EXP ([eE][+-]?{NUMBER})
REAL ({NUMBER}{EXP}|{FLOAT}{EXP})
LETTER [a-zA-Z_]
IDENTIFIER {LETTER}({LETTER}|{DIGIT})*
LINE_COMMENT "//"(.)*

%x MULTILINE_COMMENT
%x STRING

%%
[\n\r\t ] ;

"int" ECHO ;
"char" ECHO ;
"float" ECHO ;
"string" ECHO ;
"bool" ECHO ;
"void" ECHO ;
"auto" ECHO ;

"if" ECHO ;
"else" ECHO ;

"while" ECHO ;
"do" ECHO ;

"for" ECHO ;

"continue" ECHO ;
"break" ECHO ;
"return" ECHO ;

{LINE_COMMENT} ;
{NUMBER} ECHO ;
{FLOAT} ECHO ;
{REAL} ECHO ;
{IDENTIFIER} ECHO ;

\" BEGIN STRING;
<STRING>\" BEGIN INITIAL;
<STRING>. ECHO ;

"/*" BEGIN MULTILINE_COMMENT;
<MULTILINE_COMMENT>"*/" BEGIN INITIAL;
<MULTILINE_COMMENT>(.|\n) ;

. ECHO ;

%%

int yywrap(){
    return 1;
}
