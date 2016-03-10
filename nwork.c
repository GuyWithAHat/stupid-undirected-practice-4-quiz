#include "sockstuff.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINESIZE 4000
#define HOSTLENSIZE 400
#define MAXNUMTOKENS 400

void eat_spaces()
{
	char c;
	while (1)
	{
		c = getc(stdin);
		if (c != ' ' && c != '\t')
		{
			ungetc(c, stdin);
			return;
		}
	} 
}

char *getWord(char buf[])
{
	int bufindex = 0;
	char c = getc(stdin);

	for (; isalnum(c); c=getc(stdin), ++bufindex)
		buf[bufindex] = c;

	ungetc(c,stdin);
	eat_spaces();
	buf[bufindex] = '\0';
	
	return buf;
}

char *getToken(char *buf)
{
	sprintf(buf, "%s", "\0");
	char c;
	while ( (c = getc(stdin)) != EOF )
	{
		switch (c)
		{
			case ' ':
			case '\t':
				eat_spaces();
				break;
			case '\n':
				sprintf(buf, "%s", "\n");
				return buf;
			case ':':
				sprintf(buf, "%s", ":");
				return buf;
			default:
				ungetc(c, stdin);
				return getWord(buf);
		}
	}
}

/*
void connect_command()
{
	//nice stack size bro

	char hostname[MAXLINESIZE+1];
	hostname[MAXLINESIZE] = '\0';
	if ( strcmp(getToken(hostname), "\n") == 0)
	{
		printf("connect command must take a hostname:port. Try again\n");
		return;
	}

	char colon[MAXLINESIZE+1];
	colon[MAXLINESIZE] = '\0';
	if ( strcmp(getToken(colon), ":") != 0)
	{
		printf("connect command must take a hostname:port. Try again\n");
		return;
	}

	char portnum[MAXLINESIZE+1];
	portnum[MAXLINESIZE] = '\0';
	getToken(portnum);
	for (int i = 0; i < strlen(portnum); ++i)
	{
		if (!isdigit(portnum[i]))
		{
			printf("port number must be a number, lol\n");
			return;
		}
	}

	char next[MAXLINESIZE+1];
	next[MAXLINESIZE] = '\0';
	if (getToken(next) == "\n")
	{
		ungetc('\n', stdin);
	}
	printf("Hostname = %s\n", hostname);
	printf("Port number = %s\n", portnum);
	
	
}
*/

void parseLine()
{
	
	char *tokens[MAXNUMTOKENS+1];
	char line[MAXLINESIZE+1];
	char *lptr = line;
	
	tokens[0] = NULL;
	printf("$ ");
	fflush(stdout);
	for (int i = 0; strcmp(getToken(lptr), "\n") != 0 && i < MAXNUMTOKENS; ++i)
	{
		tokens[i] = lptr;
		tokens[i+1] = NULL;
		lptr += (strlen(lptr) + 1);
	}
	
	for (int i = 0; tokens[i] != NULL; ++i)
	{
		printf("%s\n", tokens[i]);
	}

	/*
	fflush(stdout);
	char buf[MAXLINESIZE];
	getToken(buf);
	if (strcmp(buf, "\n") == 0)
		return;
	else if (strcmp(buf, "connect") == 0)
		connect_command();
	else //command not recognized
		printf("%s: Not a command. Try again\n", buf);
	*/
}


int main()
{
	while (1)
		parseLine();
	return 0;
}
