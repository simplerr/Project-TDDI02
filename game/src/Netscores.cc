#include "Netscores.h"
#include <fstream>
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
	//close(fd);
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
	if (connect(fd, res->ai_addr, res->ai_addrlen) == -1) {
		close(fd);
		freeaddrinfo(res);
		return -1;

	}
	
	freeaddrinfo(res);

	return 0;
}

string Netscores::getnetscore()
{
	int n;
	char buf[2048];

	if (dial(NODE, SERVICE) != 0)
		return "error";
	if (send(fd, "ps", 2, 0) == -1)
		return "error";


	while ((n = recv(fd, buf, sizeof buf -1, 0)) < 0)
		;

	buf[n] = '\0';
	string str = buf;

	close(fd);
	return str;
}

int Netscores::updatenetscores(const string &file)
{
	if (dial(NODE, SERVICE) != 0)
		return -1;

	if (send(fd, "us", 2, 0) == -1)
		return -1;

	char c;
	string buf;
	ifstream f(file);
	
	if (!f)
		return -1;
	
	while (f.get(c))
		buf += c;

	f.close();

	if (send(fd, buf.c_str(), buf.size(), 0) == -1)
		return -1;

	close(fd);
	return 0;
}
