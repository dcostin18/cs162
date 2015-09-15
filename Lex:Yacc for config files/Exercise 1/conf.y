
%{
    // conf.y

#include <stdio.h>
#include <stdlib.h>

void yyerror(char *);
int yylex(void);

%}

%union {
    int val;
    char* name;
    char* strval;
}

%token GLOBAL_HEADER HOST_HEADER EOFTOK EOLN
%token<val> OPT_VAL
%token<name> OPT_ID

%start input

%%

input
    : lines EOFTOK            { YYACCEPT; }
    ;

lines
    :
    | lines line
    ;

line
    : OPT_ID '=' OPT_VAL EOLN        { printf("%s = %d\n",$1, $3); }
    | GLOBAL_HEADER EOLN       { printf("GLOBAL\n-----\n"); }
    | HOST_HEADER 
    | EOLN
    ;


%%

void yyerror(char *msg) {}
