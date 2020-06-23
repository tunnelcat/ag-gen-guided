%option noyywrap
%option yylineno

DIGIT   -?[0-9]+
ID      [a-zA-Z][a-zA-Z0-9_\.]*

%{
#include "xp_parser.tab.h"
%}

%%

#.*\n {}

exploit { xplval.string = strdup(yytext); return EXPLOIT; }
preconditions { xplval.string = strdup(yytext); return PRECONDITIONS; }
postconditions { xplval.string = strdup(yytext); return POSTCONDITIONS; }
quality  { xplval.string = strdup(yytext); return QUALITY; }
topology  { xplval.string = strdup(yytext); return TOPOLOGY; }
add { xplval.string = strdup(yytext); return ADD; }
insert { xplval.string = strdup(yytext); return INSERT; }
update { xplval.string = strdup(yytext); return UPDATE; }
delete { xplval.string = strdup(yytext); return DELETE; }
remove { xplval.string = strdup(yytext); return REMOVE; }

{DIGIT}+ { xplval.string = strdup(yytext); return INT; }
{DIGIT}*"."{DIGIT}+ { xplval.string = strdup(yytext); return FLOAT; }
{ID} { xplval.string = strdup(yytext); return IDENTIFIER; }

"(" { xplval.string = strdup(yytext); return LPAREN; }
")" { xplval.string = strdup(yytext); return RPAREN; }
"="	 { xplval.string = strdup(yytext); return EQ; }
"==" { xplval.string = strdup(yytext); return EQ; }
"!=" { xplval.string = strdup(yytext); return NEQ; }
"<" { xplval.string = strdup(yytext); return LT; }
">" { xplval.string = strdup(yytext); return GT; }
">=" { xplval.string = strdup(yytext); return GEQ; }
"<=" { xplval.string = strdup(yytext); return LEQ; }
":="  { xplval.string = strdup(yytext); return EQ; }
"<>" { xplval.string = strdup(yytext); return NEQ; }
"+=" { xplval.string = strdup(yytext); return PLUSEQ; }
"-=" { xplval.string = strdup(yytext); return SUBEQ; }
":"	 { xplval.string = strdup(yytext); return COLON; }
";"	 { xplval.string = strdup(yytext); return SEMI; }
","	 { xplval.string = strdup(yytext); return COMMA; }
"."	 { xplval.string = strdup(yytext); return PERIOD; }
"<->"  { xplval.string = strdup(yytext); return BIDIR; }
"<!>" { xplval.string = strdup(yytext); return NOTBIDIR; }
"->" { xplval.string = strdup(yytext); return ONEDIR; }
"<-" { xplval.string = strdup(yytext); return ONEDIRBACK; }
"!>" { xplval.string = strdup(yytext); return NOTONEDIR; }
[ \t\r\n]+ {}

. { return yytext[0]; }

%%
