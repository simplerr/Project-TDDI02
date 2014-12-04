#ifndef HIGHSCORE_H
#define HIGHSCORE_H

#include <vector>
#include <string>
#include "Netscores.h"
using namespace std;

struct scoremap {
	string level;
	float time;
	int score;
};

class Highscores
{
public:
    Highscores(string filename);
    ~Highscores();
    
	int init(string);
	void loadscores();
    void save();
    float getHighscoreTime(string level);
	int getHighscoreScore(string level);
    void updateHighscore(string level, float time, int score);

private:
    vector<scoremap> mHighscores;
    string mFilename;
	string netscores;
	Netscores *ns;
	bool net;
};

#endif
