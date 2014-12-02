#include "Netscores.h"
#include <cstring>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>


Netscores::Netscores()
{
	;
}

Netscores::~Netscores()
{
	close(fd);
}

int Netscores::dial(const char *node, const char *service)
{
	struct addrinfo hints, *res;
	
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	if (getaddrinfo(node, service, &hints, &res) != 0)
		return -1;
	if ((fd = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) == -1)
		return -1;
	if (connect(fd, res->ai_addr, res->ai_addrlen) == -1)
		return -1;
	
	freeaddrinfo(res);

	return 0;
}

string Netscores::getnetscore()
{
	int n;
	char buf[2048];

	if ((n = recv(fd, buf, sizeof buf -1, 0)) == -1)
		return "error";

	buf[n] = '\0';
	string str = buf;

	return str;
}
