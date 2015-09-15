%{
// conf.l

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "configfile.h"
#include "y.tab.h"

extern configfile *cf;

int yyparse();
int section_count=0;
int option_count=0;

%}

%option noyywrap

%x GLOBAL HOST VARIABLE

%%

<INITIAL>"host".* {
        option_count=0;
        section_count++;
        cf->numsections++;
        BEGIN HOST;
        return HOST_HEADER;
    }

<INITIAL>"global {" {
        BEGIN GLOBAL;
        return GLOBAL_HEADER;
    }

<GLOBAL>(%.*%) {
        BEGIN(variable);
        yyless(0);
    }

<HOST>(%.*%) {
        BEGIN(variable);
        yyless(0);
    }

<VARIABLE>(%.*%) {
        BEGIN(0);
        return(OPT_ID);
        BEGIN INITIAL;
    }

<HOST>"ftproot" {
        configsection s = cf->sections[section_count++];
        configoption *co = (configoption*) malloc(sizeof(configoption));
        co->name = strdup(yytext);
        add_option(&s, *co, option_count++);
        cf->sections[section_count]=s;
        yylval.name=strdup(yytext);
        return OPT_ID;
    }
<HOST>"exclude" {
        configsection s = cf->sections[section_count++];
        configoption *co = (configoption*) malloc(sizeof(configoption));
        co->name = strdup(yytext);
        add_option(&s, *co, option_count++);
        cf->sections[section_count]=s;
        yylval.name=strdup(yytext);
        return OPT_ID;
    }
<HOST>"max_out_bandwidth" {
        configsection s = cf->sections[section_count++];
        configoption *co = (configoption*) malloc(sizeof(configoption));
        co->name = strdup(yytext);
        add_option(&s, *co, option_count++);
        cf->sections[section_count]=s;
        yylval.name=strdup(yytext);
        return OPT_ID;
    }
<HOST>[0-9]+\.?[0-9]* {
        yylval.val=atoi(yytext);
        return OPT_VAL;
    }
<HOST>(\/[a-z0-9]+)+ {
        configsection s = cf->sections[section_count++];
        configoption *co = (configoption*) malloc(sizeof(configoption));
        co->name = strdup(yytext);
        add_option(&s, *co, option_count++);
        cf->sections[section_count]=s;
        yylval.name=strdup(yytext);
        return OPT_ID;
    }
<HOST>"};" {
        BEGIN INITIAL;
    }

<GLOBAL>"num_daemons" {
        configsection s = cf->sections[section_count++];
        configoption *co = (configoption*) malloc(sizeof(configoption));
        co->name = strdup(yytext);
        add_option(&s, *co, option_count++);
        cf->sections[section_count]=s;
        yylval.name=strdup(yytext);
        return OPT_ID;
    }

<GLOBAL>"max_out_bandwidth" {
        configsection s = cf->sections[section_count++];
        configoption *co = (configoption*) malloc(sizeof(configoption));
        co->name = strdup(yytext);
        add_option(&s, *co, option_count++);
        cf->sections[section_count]=s;
        yylval.name=strdup(yytext);
        return OPT_ID;
    }

<GLOBAL>"max_in_bandwidth" {
        configsection s = cf->sections[section_count++];
        configoption *co = (configoption*) malloc(sizeof(configoption));
        co->name = strdup(yytext);
        add_option(&s, *co, option_count++);
        cf->sections[section_count]=s;
        yylval.name=strdup(yytext);
        return OPT_ID;
    }

<GLOBAL>^"etc"$ {
        configsection s = cf->sections[section_count++];
        configoption *co = (configoption*) malloc(sizeof(configoption));
        co->name = strdup(yytext);
        add_option(&s, *co, option_count++);
        cf->sections[section_count]=s;
        yylval.name=strdup(yytext);
        return OPT_ID;
    }

<GLOBAL>"hostkey" {
        configsection s = cf->sections[section_count++];
        configoption *co = (configoption*) malloc(sizeof(configoption));
        co->name = strdup(yytext);
        add_option(&s, *co, option_count++);
        cf->sections[section_count]=s;
        yylval.name=strdup(yytext);
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

void parse_string(char *s) {
    char *str;
    asprintf(&str,"%s\n",s);
    YY_BUFFER_STATE bh = yy_scan_string(str);
    yyparse();
    yy_delete_buffer(bh);
    free(str);
}