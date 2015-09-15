%{
// conf.l

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "y.tab.h"

int yyparse();

%}

%option noyywrap

%x GLOBAL HOST

%%

<INITIAL>"host".* {
        BEGIN HOST;
        return HOST_HEADER;
    }

<INITIAL>"global {" {
        BEGIN GLOBAL;
        return GLOBAL_HEADER;
    }

<HOST>"ftproot" {
        yylval.name=strdup(yytext);
        return OPT_ID;
    }
<HOST>"exclude" {
        yylval.strval=strdup(yytext);
        return OPT_ID;
    }
<HOST>"max_out_bandwidth" {
        yylval.name=strdup(yytext);
        return OPT_ID;
    }
<HOST>[0-9]+\.?[0-9]* {
        yylval.val=atoi(yytext);
        return OPT_VAL;
    }
<HOST>(\/[a-z0-9]*)+ {
        yylval.strval=strdup(yytext);
        return OPT_VAL;
    }
<HOST>"};" {
        BEGIN INITIAL;
    }

<GLOBAL>"num_daemons" {
        yylval.name=strdup(yytext);
        return OPT_ID;
    }

<GLOBAL>"max_out_bandwidth" {
        yylval.name=strdup(yytext);
        return OPT_ID;
    }

<GLOBAL>"max_in_bandwidth" {
        yylval.name=strdup(yytext);
        return OPT_ID;
    }

<GLOBAL>^"etc"$ {
        yylval.strval=strdup(yytext);

        return OPT_ID;
    }

<GLOBAL>"hostkey" {
        yylval.strval=strdup(yytext);

        return OPT_ID;
    }

<GLOBAL>[0-9]+\.?[0-9]* {
        yylval.val=atoi(yytext);
        return OPT_VAL;
    }

<GLOBAL>"};" {
        BEGIN INITIAL;
    }

<INITIAL>.|\n {}

<<EOF>>         {   return EOFTOK; }

%%
