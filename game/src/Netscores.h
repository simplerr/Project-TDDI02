#ifndef NETSCORES_H
#define NETSCORES_H

#include <string>

using namespace std;

class Netscores {
 public:

	Netscores();
	~Netscores();

	int dial(const char *, const char *);
	std::string getnetscore();

 private:
	int fd;

};

#endif
