#define _POSIX_SOURCE
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#include <stdlib.h>
#include <stdio.h>

void safelisten(int sfd, int backlog)
{
	if ( listen(sfd, backlog) == -1)
	{
		perror("listen()");
		exit(1);
	}
}

int safesocket()
{
	int sfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sfd == -1)
	{
		perror("socket()");
		exit(1);
	}
	return sfd;
}

void safebind(int sfd, struct sockaddr_in *saddrin)
{
	if ( bind(sfd, (struct sockaddr*) saddrin, sizeof (*saddrin)) == -1 )
	{
		perror("bind()");
		exit(1);
	}
}

int makelistensfd(short portnum, int backlog)
{
	struct sockaddr_in listenaddr;
	listenaddr.sin_family = AF_INET;
	listenaddr.sin_port = portnum;
	listenaddr.sin_addr.s_addr = INADDR_ANY;
	
	int sfd = safesocket();
	safebind(sfd, &listenaddr);
	safelisten(sfd, backlog);

	return sfd;
}

int safe_connect(const char hostname[], const char portnum[], int num_tries)
{
	for (int i = 0; i < num_tries; ++i)
	{
		struct addrinfo *r;
		if (getaddrinfo(hostname, portnum, NULL, &r) != 0)
		{
			printf("getaddrinfo() error\n");
			exit(1);
		}

		int sfd;
		for (; r != NULL; r = r->ai_next)
		{
			sfd = socket(r->ai_family, r->ai_socktype, r->ai_protocol);
			if (sfd == -1)
				continue;
			if (connect(sfd, r->ai_addr, r->ai_addrlen) == -1)
				continue;
			return sfd;
		}
	}
	printf("Something failed, ");
	perror("");
	exit(1);
}

