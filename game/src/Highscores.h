#pragma once
#include <map>
#include <string>
using namespace std;

class Highscores
{
public:
    Highscores(string filename);
    ~Highscores() {};
    
    void save();
    float getHighscore(string level);
    void updateHighscore(string level, float time);

private:
    map<string, float> mHighscores;
    string mFilename;
};
