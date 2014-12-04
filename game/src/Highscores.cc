#include "Highscores.h"
#include <iostream>
#include <fstream>

Highscores::Highscores(string filename)
{
	ns = new Netscores;

	init(filename);
	loadscores();
}

Highscores::~Highscores()
{
	delete ns;
}

int Highscores::init(string filename)
{
	if ((netscores = ns->getnetscore()) == "error") {
		mFilename = filename;
		cerr << "Kunde inte ladda higscore från server. Laddar lokala highscores!\n";
		net = false;
		return -1;
	}

	mFilename = "nethighscores.txt";
	ofstream of(mFilename);
	if (!of) {
		mFilename = filename;
		cerr << "Kunde inte ladda higscore från server. Laddar lokala highscores!\n";
		net = false;
	}

	of << netscores;
	of.close();

	return 0;
}

void Highscores::loadscores()
{
	ifstream fin(mFilename);

	string level;
	float time;
	int score;

	while(fin >> level >> time >> score) {
		scoremap s;
		s.level = level;
		s.time = time;
		s.score = score;
		mHighscores.push_back(s);
	}
	
	fin.close();
}

void Highscores::save()
{
    ofstream fout(mFilename);
	
	if (fout.is_open())
	{
		for(unsigned int i = 0; i < mHighscores.size(); i++)
			fout << mHighscores.at(i).level << " " <<  mHighscores.at(i).time << " " << mHighscores.at(i).score << endl;
	}
	else
		std::cerr << "Could not open: " << mFilename << "\n";
    fout.close();
}

float Highscores::getHighscoreTime(string level)
{
	for (unsigned int i = 0; i < mHighscores.size(); i++)
		if (mHighscores.at(i).level == level)
			return mHighscores.at(i).time;
	
    return 0;
}

int Highscores::getHighscoreScore(string level)
{
	for (unsigned int i = 0; i < mHighscores.size(); i++)
		if (mHighscores.at(i).level == level)
			return mHighscores.at(i).score;
	
    return 0;
}



void Highscores::updateHighscore(string level, float time, int score)
{
	for (unsigned int i = 0; i < mHighscores.size(); i++) {
		
		if (mHighscores.at(i).level == level) {
		
			if (mHighscores.at(i).time > time || mHighscores.at(i).time == 0)
				mHighscores.at(i).time = time;
			if (mHighscores.at(i).score < score || mHighscores.at(i).score == 0)
				mHighscores.at(i).score = score;
			
			save();

			if (net) 
				if (ns->updatenetscores(mFilename) != 0)
					cerr << "error updating net scores\n";
			
			
			return;
		}

	}
    /*if(mHighscores[level] > time || mHighscores[level] == 0)
	  mHighscores[level] = time;*/
}
