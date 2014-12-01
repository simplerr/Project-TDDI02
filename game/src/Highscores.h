#ifndef HIGHSCORE_H
#define HIGHSCORE_H

#include <vector>
#include <string>
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
    ~Highscores() {};
    
    void save();
    float getHighscoreTime(string level);
	int getHighscoreScore(string level);
    void updateHighscore(string level, float time, int score);

private:
    vector<scoremap> mHighscores;
    string mFilename;
};

#endif
