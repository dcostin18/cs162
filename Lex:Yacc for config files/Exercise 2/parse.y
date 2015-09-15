
%{
    // conf.y

#include <stdio.h>
#include <stdlib.h>
#include "configfile.h"

extern configfile *cf;

void yyerror(char *);
int yylex(void);
int count=0;

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
    : OPT_ID '=' OPT_VAL EOLN        { addValueTo(&cf->sections[count++], $1, $3); }
    | GLOBAL_HEADER EOLN       
    | HOST_HEADER               { count++; }
    | EOLN
    ;


%%

void yyerror(char *msg) {}
