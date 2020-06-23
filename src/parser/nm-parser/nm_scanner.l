%option noyywrap
%option yylineno

DIGIT   [0-9]+
ID      [a-zA-Z][a-zA-Z0-9_]*

%{
#include "nm_parser.tab.h"
%}

%%

#.*\n {}

network  { return NETWORK; }
facts  { return FACTS; }
assets  { return ASSETS; }
quality  { return QUALITY; }
topology  { return TOPOLOGY; }
tags { return TAGS; }

{DIGIT}+ { nmlval.string = strdup(yytext); return INT; }
{DIGIT}*"."{DIGIT}+ { nmlval.string = strdup(yytext); return FLOAT; }
{ID} { nmlval.string = strdup(yytext); return IDENTIFIER; }

"="	 { nmlval.string = strdup(yytext); return EQ; }
"<" { nmlval.string = strdup(yytext); return LT; }
">" { nmlval.string = strdup(yytext); return GT; }
">=" { nmlval.string = strdup(yytext); return GEQ; }
"<=" { nmlval.string = strdup(yytext); return LEQ; }
":="  { nmlval.string = strdup(yytext); return EQ; }
":"	 { nmlval.string = strdup(yytext); return COLON; }
";"	 { nmlval.string = strdup(yytext); return SEMI; }
","	 { nmlval.string = strdup(yytext); return COMMA; }
"."	 { nmlval.string = strdup(yytext); return PERIOD; }
"<->"  { nmlval.string = strdup(yytext); return BIDIR; }
"<!>" { nmlval.string = strdup(yytext); return NOTBIDIR; }
"<-" { nmlval.string = strdup(yytext); return ONEDIRBACK; }
"->"  { nmlval.string = strdup(yytext); return ONEDIR; }
"!>" { nmlval.string = strdup(yytext); return NOTONEDIR; }

[ \t\r\n]+ {}

. { return 1; }
