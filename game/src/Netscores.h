#ifndef NETSCORES_H
#define NETSCORES_H

#include <string>

using namespace std;

#define NODE "127.0.0.1" // to be updated
#define SERVICE "5151"

class Netscores {
 public:

	Netscores();
	~Netscores();

	int dial(const char *, const char *);
	std::string getnetscore();
	int updatenetscores(const string &);

 private:
	int fd;

};

#endif
