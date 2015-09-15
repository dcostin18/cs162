#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/param.h>
#include "configfile.h"

configfile *cf;

int yylex(void);
int yyparse(void);
void parse_string(char *str);

void add_option(configsection *s, configoption op, index)
{
	configoption *tor = malloc(sizeof(configoption)*index+1);
	for(int i=0; i<index; i++)
	{
		tor[i] = s->options[i];
	}
	tor[index] = op;
	s->options=tor;
	s->numopts = index+1;

}

void addValueTo(configsection *s, char* name, int val)
{
	configoption *opts = s->options;
	int size = sizeof(opts)/sizeof(configoption);
	for(int i=0; i<size; i++)
	{
		if(strcmp(opts[i].name, name)!=0) opts[i].value = val;
	}
}

int main(int argc, char **argv)
{
	cf = malloc(sizeof(configfile));																																																																																																																																																																																																																																																																																																																																																																																																																																																																
	if(argc > 1)
	{
		for(int i=1; i<argc; ++i)
		{
			parse_string(argv[i]);
		}
	}
	else {yyparse();}

	printf("SECTION global\n-------\n");
	for(int i=0; i<cf->numsections; i++)
	{
		for(int x=0; x<cf->sections[i].numopts; x++)
		{
			printf("%s = %d\n", cf->sections[i].options[x]);
		}
		printf("\n-------\n");
	}

	exit(0);
}