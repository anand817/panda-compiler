%{

#include <vector>
#include <string>
#include <iostream>
#include <parser.hpp>

using namespace std;

std::string literal;

void saveToken();
void saveLiteral();

%}

%s BLOCK_COMMENT
%s STRING_STATE



DIGIT               [0-9]
INTEGER             [0-9]+
FLOAT               (([0-9]*\.[0-9]+)|([0-9]+\.[0-9]*))
EXP                 ([eE][-+]?{INTEGER})
REAL                ({INTEGER}{EXP}|{FLOAT}{EXP}?)
LETTER              [a-zA-Z_]
IDENTIFIER          {LETTER}({LETTER}|{DIGIT})*
LINE_COMMENT        "//"(.)*

%%

<INITIAL>\n                                  ;
<INITIAL>\r                                  ;
<INITIAL>\t                                  ;
<INITIAL>" "                                 ;

<INITIAL>"int"                      return TYPE_INT;
<INITIAL>"float"                    return TYPE_FLOAT;
<INITIAL>"char"                     return TYPE_CHAR;
<INITIAL>"bool"                     return TYPE_BOOL;
<INITIAL>"void"                     return TYPE_VOID;
<INITIAL>"string"                   return TYPE_STRING;

<INITIAL>"if"                       return IF;
<INITIAL>"else"                     return ELSE;
<INITIAL>"for"                      return FOR;
<INITIAL>"while"                    return WHILE;
<INITIAL>"break"                    return BREAK;
<INITIAL>"continue"                 return CONTINUE;
<INITIAL>"return"                   return RETURN;
<INITIAL>"print"                    return PRINT;
<INITIAL>"input"                    return INPUT;

<INITIAL>"++"                       return INC;
<INITIAL>"--"                       return DEC;
<INITIAL>"=="                       return EQUAL;
<INITIAL>"!="                       return NOT_EQUAL;
<INITIAL>">="                       return GREATER_EQUAL;
<INITIAL>"<="                       return LESS_EQUAL;
<INITIAL>"&&"                       return LOGICAL_AND;
<INITIAL>"||"                       return LOGICAL_OR;
<INITIAL>[-+*/%&|^~!<>=(){}[\],:;]  return yytext[0];


<INITIAL>{INTEGER}                  saveToken(); return INTEGER;
<INITIAL>{REAL}                     saveToken(); return FLOAT;
<INITIAL>(\'.\')                    saveToken(); return CHAR;
<INITIAL>"true"                     saveToken(); return BOOL;
<INITIAL>"false"                    saveToken(); return BOOL;
<INITIAL>{IDENTIFIER}               saveToken(); return IDENTIFIER;

<INITIAL>{LINE_COMMENT}             ;// Ignore comments
<INITIAL>"/*"                       BEGIN BLOCK_COMMENT;
<BLOCK_COMMENT>"*/"                 BEGIN INITIAL;
<BLOCK_COMMENT>.                    ;// Ignore block comments

<INITIAL>"\""                       BEGIN STRING_STATE; literal = "";
<STRING_STATE>"\\n"                 literal += "\n";
<STRING_STATE>"\\t"                 literal += "\t";
<STRING_STATE>"\\\""                literal += "\"";
<STRING_STATE>"\""                  BEGIN INITIAL; saveLiteral(); return STRING;
<STRING_STATE>"\n"                  cout << "invalid string"; exit(1);
<STRING_STATE>.                     literal += *yytext;

<INITIAL>.                          return yytext[0];

%%

void saveToken(){
    yylval.token.value = strdup(yytext);
}

void saveLiteral(){
    yylval.token.value = literal.c_str();
}

int yywrap() {
    return 1;
}