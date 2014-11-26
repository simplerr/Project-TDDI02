#include "Highscores.h"
#include <iostream>
#include <fstream>

Highscores::Highscores(string filename)
{
    mFilename = filename;

    ifstream fin(filename);

    string level;
    float time;

    while(fin >> level >> time)
	mHighscores[level] = time;

    fin.close();
}

void Highscores::save()
{
    ofstream fout(mFilename);

    for(auto iter = mHighscores.begin(); iter != mHighscores.end(); iter++)
    {
	fout << (*iter).first << " " << (*iter).second << endl;
    }

    fout.close();
}

float Highscores::getHighscore(string level)
{
    return mHighscores[level];
}

void Highscores::updateHighscore(string level, float time)
{
    if(mHighscores[level] > time || mHighscores[level] == 0)
	mHighscores[level] = time;
}
