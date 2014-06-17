/*Christopher Webb
Project PRJ254
Destroy All Colours Version 1
Level.h */

#pragma once
#include <iostream>
#include <vector>
#include <allegro5/allegro_primitives.h>

using namespace std;

class Level
{
private:
	vector<string> m_grid_layout;		//2d vector of strings, will create level from this
	int m_points_needed;				// points required to finish level, can increase this as levels progress
	int m_points_earned;
	int m_combos_earned;
	int m_time;
	ALLEGRO_BITMAP* levelbitmap;		//bitmaps for the various different block types
	ALLEGRO_BITMAP* usedbitmap;
	ALLEGRO_BITMAP* combobitmap;
	ALLEGRO_BITMAP* redbitmap;
	ALLEGRO_BITMAP* bluebitmap;
	ALLEGRO_BITMAP* yellowbitmap;
	string m_filename;					//strings that can be taken in the constructor and then used in al_load_bitmap()
	string m_filename2;
	string m_filename3;
	string m_filename4;
	string m_filename5;
	string m_filename6;
	int m_levelnumber;
	bool m_needtoupdate;

public:
	Level(string filename, string filename2, string filename3, string filename4, string filename5, string filename6, int points_needed, int levelnumber, int time);		//arena constructor
	int getHeight();		
	int getWidth();
	int getPointsNeeded();
	void setPointsNeeded(int points);
	int getPointsEarned();
	int getCombosEarned();
	int getTime();
	void setTime(int time);
	int getLevelNumber();
	void setLevelNumber(int levelnumber);
	void render();
	bool isWall(int x, int y);			//collision checks
	bool isBall(int x, int y);
	bool isDeadpoint(int x, int y);
	void createRedBall(int x, int y);		//allows changing of array to represent balls
	void createBlueBall(int x, int y);
	void createYellowBall(int x, int y);
	bool checkForWins();
	void checkForCombo();
	void resetDeadpoints();
	void resetpoint(int x, int y);
	void update_deadpos();
	void finished_update();
	bool needstoupdate();
	int calculatepoints();
	int calculatecombo();
	void timeminus();
	void levelreset();
};
