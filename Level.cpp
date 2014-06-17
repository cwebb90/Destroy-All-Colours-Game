/*Christopher Webb
Project PRJ254
Destroy All Colours Version 1
Level.cpp*/

#include <conio.h>
#include <iostream>
#include "Level.h"
using namespace std;

Level::Level(string filename, string filename2, string filename3, string filename4, string filename5, string filename6, int points_needed, int levelnumber, int time)
{
	m_filename = filename;
	m_filename2 = filename2;
	m_filename3 = filename3;
	m_filename4 = filename4;
	m_filename5 = filename5;
	m_filename6 = filename6;
	levelbitmap = al_load_bitmap(m_filename.c_str());
	usedbitmap = al_load_bitmap(m_filename2.c_str());
	combobitmap = al_load_bitmap(m_filename3.c_str());
	redbitmap = al_load_bitmap(m_filename4.c_str());
	bluebitmap = al_load_bitmap(m_filename5.c_str());
	yellowbitmap = al_load_bitmap(m_filename6.c_str());
	m_points_needed = points_needed;
	m_time = time;
	m_points_earned;
	m_combos_earned;
	m_levelnumber = levelnumber;
	m_needtoupdate = false;
	m_grid_layout.push_back("WWWWWWWWWW");
	m_grid_layout.push_back("W........W"); //player will spawn in this area, represented by an arrow.
	m_grid_layout.push_back("WWWWWWWWWW");
	m_grid_layout.push_back("W........W"); // balls will then be spawned here, two blocks below player.
	m_grid_layout.push_back("W........W"); // then balls will fall to the bottom of the level.
	m_grid_layout.push_back("W........W");
	m_grid_layout.push_back("W........W");
	m_grid_layout.push_back("W........W");
	m_grid_layout.push_back("W........W");
	m_grid_layout.push_back("W........W");
	m_grid_layout.push_back("W........W");
	m_grid_layout.push_back("W........W");
	m_grid_layout.push_back("W........W");
	m_grid_layout.push_back("W........W");
	m_grid_layout.push_back("WWWWWWWWWW");

}

int Level::getHeight()
{
	return m_grid_layout.size(); //vector.size() returns the amount of objects in the vector, in this case it will give us the height
}

int Level::getWidth()
{
	return m_grid_layout[0].length(); //string.length() returns the amount of characters in said string
}

int Level::getPointsNeeded()		
{
	return m_points_needed;
}

int Level::getCombosEarned()
{
	return m_combos_earned;
}

int Level::getPointsEarned()		
{
	return m_points_earned;
}

int Level::getLevelNumber()
{
	return m_levelnumber;
}

void Level::setLevelNumber(int levelnumber)
{
	m_levelnumber = levelnumber;
}

int Level::getTime()
{
	return m_time;
}

void Level::setTime(int time)
{
	m_time = time;
}

void Level::setPointsNeeded(int points)
{
	m_points_needed = points;
}

void Level::render()
{
	for(int h=0; h<getWidth(); h++)				//this method uses a nested loop to loop through element of the vector
	{												//at each coordinate a check is done to see what character is there
		for(int w=0; w<getHeight(); w++)				//dependant on what character is at those coordinates, a block will be drawn.
		{
			if(m_grid_layout[w][h]=='W')			//wall space
			{
				al_draw_bitmap(levelbitmap, h*al_get_bitmap_height(levelbitmap), w*al_get_bitmap_height(levelbitmap), 0);	
			}
			if(m_grid_layout[w][h]=='D')			//dead space
			{
				al_draw_bitmap(usedbitmap, h*al_get_bitmap_height(usedbitmap), w*al_get_bitmap_height(usedbitmap), 0);
			}
			if(m_grid_layout[w][h]=='C')			//combo space
			{
				al_draw_bitmap(combobitmap, h*al_get_bitmap_height(combobitmap), w*al_get_bitmap_height(combobitmap), 0);	
			}
			/*if(m_grid_layout[w][h]=='R')			//red ball space			these were used during development for testing purposes, not needed in final product
			{
				//al_draw_bitmap(redbitmap, h*al_get_bitmap_height(redbitmap), w*al_get_bitmap_height(redbitmap), 0);	
			}
			if(m_grid_layout[w][h]=='B')			//blue ball space
			{
				//al_draw_bitmap(bluebitmap, h*al_get_bitmap_height(bluebitmap), w*al_get_bitmap_height(bluebitmap), 0);	
			}
			if(m_grid_layout[w][h]=='Y')			//yellow ball space
			{
				//al_draw_bitmap(yellowbitmap, h*al_get_bitmap_height(yellowbitmap), w*al_get_bitmap_height(yellowbitmap), 0);	
			}*/
		}
	}
}

bool Level::isWall(int x, int y)																		
{																										
	if(m_grid_layout[y/al_get_bitmap_height(levelbitmap)][x/al_get_bitmap_height(levelbitmap)]=='W'
		||m_grid_layout[y/al_get_bitmap_height(levelbitmap)][x/al_get_bitmap_height(levelbitmap)]=='D'
		||m_grid_layout[y/al_get_bitmap_height(levelbitmap)][x/al_get_bitmap_height(levelbitmap)]=='C')	
	{
		return true;
	}
	else
		return false;
}

bool Level::isBall(int x, int y)																		
{																										
	if(m_grid_layout[y/al_get_bitmap_height(levelbitmap)][x/al_get_bitmap_height(levelbitmap)]=='R'
		||m_grid_layout[y/al_get_bitmap_height(levelbitmap)][x/al_get_bitmap_height(levelbitmap)]=='B'
		||m_grid_layout[y/al_get_bitmap_height(levelbitmap)][x/al_get_bitmap_height(levelbitmap)]=='Y')
	{
		return true;
	}
	else
		return false;
}

bool Level::isDeadpoint(int x, int y)	//unused due to design change																	

{																										
	if(m_grid_layout[y/al_get_bitmap_height(levelbitmap)][x/al_get_bitmap_height(levelbitmap)]=='D')
	{
		return true;
	}
	else
		return false;
}


void Level::createRedBall(int x, int y)//creates neccessary ball space on level
{
	int m_x = x/60;
	int m_y = y/60;

	m_grid_layout[m_y][m_x]='R';
}

void Level::createBlueBall(int x, int y)
{
	int m_x = x/60;
	int m_y = y/60;

	m_grid_layout[m_y][m_x]='B';
}

void Level::createYellowBall(int x, int y)
{
	int m_x = x/60;
	int m_y = y/60;

	m_grid_layout[m_y][m_x]='Y';
}

void Level::resetDeadpoints()
{
	for(int h=0; h<getWidth(); h++)				//this method uses a nested loop to loop through element of the vector
	{												//at each coordinate a check is done to see what character is there
		for(int w=0; w<getHeight(); w++)				//dependant on what character is at those coordinates, a block will be drawn.
		{
			if(m_grid_layout[w][h]=='D')					//this ended up being unused as balls no longer disappear
			{
				m_grid_layout[w][h]=',';
			}
		}
	}
	
}

void Level::resetpoint(int x, int y)		//unused due to design change
{
	int m_x = x/60;
	int m_y = y/60;

	m_grid_layout[m_y][m_x]='.';
}


bool Level::checkForWins()							//checks through level for combinations of colours and sets to deadpoints which can then be counted
{
	for(int h=0; h<getWidth(); h++)
	{												
		for(int w=0; w<getHeight(); w++)
		{
			if(m_grid_layout[w][h]=='R'				//vertical checks
					&& m_grid_layout[w+1][h]=='R'
					&& m_grid_layout[w+2][h]=='R'
					&& m_grid_layout[w+3][h]=='R')
				{
					m_grid_layout[w][h]='D';
					m_grid_layout[w+1][h]='D';
					m_grid_layout[w+2][h]='D';
					m_grid_layout[w+3][h]='D';
					return true;
					break;
				}
			else if(m_grid_layout[w][h]=='B'
					&& m_grid_layout[w-1][h]=='B'
					&& m_grid_layout[w-2][h]=='B'
					&& m_grid_layout[w-3][h]=='B')
			{
					m_grid_layout[w][h]='D';
					m_grid_layout[w-1][h]='D';
					m_grid_layout[w-2][h]='D';
					m_grid_layout[w-3][h]='D';
					return true;
					break;
			}
			else if(m_grid_layout[w][h]=='Y'
					&& m_grid_layout[w-1][h]=='Y'
					&& m_grid_layout[w-2][h]=='Y'
					&& m_grid_layout[w-3][h]=='Y')
			{
					m_grid_layout[w][h]='D';
					m_grid_layout[w-1][h]='D';
					m_grid_layout[w-2][h]='D';
					m_grid_layout[w-3][h]='D';
					return true;
					break;
			}
			else if(m_grid_layout[w][h]=='R'		//horizontal checks
					&& m_grid_layout[w][h-1]=='R'
					&& m_grid_layout[w][h-2]=='R'
					&& m_grid_layout[w][h-3]=='R')
				{
					m_grid_layout[w][h]='D';
					m_grid_layout[w][h-1]='D';
					m_grid_layout[w][h-2]='D';
					m_grid_layout[w][h-3]='D';
					return true;
					break;
				}
			else if(m_grid_layout[w][h]=='B'
					&& m_grid_layout[w][h-1]=='B'
					&& m_grid_layout[w][h-2]=='B'
					&& m_grid_layout[w][h-3]=='B')
				{
					m_grid_layout[w][h]='D';
					m_grid_layout[w][h-1]='D';
					m_grid_layout[w][h-2]='D';
					m_grid_layout[w][h-3]='D';
					return true;
					break;
				}
			else if(m_grid_layout[w][h]=='Y'
					&& m_grid_layout[w][h-1]=='Y'
					&& m_grid_layout[w][h-2]=='Y'
					&& m_grid_layout[w][h-3]=='Y')
				{
					m_grid_layout[w][h]='D';
					m_grid_layout[w][h-1]='D';
					m_grid_layout[w][h-2]='D';
					m_grid_layout[w][h-3]='D';
					return true;
					break;
				}	
		}
	}
	return false;
}

void Level::checkForCombo()							//checks for specific shapes of specific colours
{
	for(int h=0; h<getWidth(); h++)					//after difficulty testing, changed to be made by any colours
	{												
		for(int w=0; w<getHeight(); w++)
		{
			if((m_grid_layout[w][h]=='R'				//shape 1, see logbook
					&& m_grid_layout[w-1][h]=='R'
					&& m_grid_layout[w][h-1]=='R'
					&& m_grid_layout[w-1][h-1]=='R') ||
					(m_grid_layout[w][h]=='B'				
					&& m_grid_layout[w-1][h]=='B'
					&& m_grid_layout[w][h-1]=='B'
					&& m_grid_layout[w-1][h-1]=='B') ||
					(m_grid_layout[w][h]=='Y'				
					&& m_grid_layout[w-1][h]=='Y'
					&& m_grid_layout[w][h-1]=='Y'
					&& m_grid_layout[w-1][h-1]=='Y') )
				{
					m_grid_layout[w][h]='C';
					m_grid_layout[w-1][h]='C';
					m_grid_layout[w][h-1]='C';
					m_grid_layout[w-1][h-1]='C';
				}
			if(m_grid_layout[w][h]=='R'				//shape 2, see logbook
					&& m_grid_layout[w+1][h]=='R'
					&& m_grid_layout[w+1][h+1]=='R'
					&& m_grid_layout[w+2][h+1]=='R')
			{
					m_grid_layout[w][h]='C';
					m_grid_layout[w+1][h]='C';
					m_grid_layout[w+1][h+1]='C';
					m_grid_layout[w+2][h+1]='C';
			}
			if(m_grid_layout[w][h]=='B'				//shape 3, see logbook
					&& m_grid_layout[w][h-1]=='B'
					&& m_grid_layout[w][h+1]=='B'
					&& m_grid_layout[w-1][h]=='B')
			{
					m_grid_layout[w][h]='C';
					m_grid_layout[w][h-1]='C';
					m_grid_layout[w][h+1]='C';
					m_grid_layout[w-1][h]='C';
			}
			if(m_grid_layout[w][h]=='Y'				//shape 4, see logbook
					&& m_grid_layout[w][h+1]=='Y'
					&& m_grid_layout[w-1][h]=='Y'
					&& m_grid_layout[w-2][h]=='Y')
			{
					m_grid_layout[w][h]='C';
					m_grid_layout[w][h+1]='C';
					m_grid_layout[w-1][h]='C';
					m_grid_layout[w-2][h]='C';
			}
		}
	}
}




void Level::update_deadpos()		//unused design change
{
	m_needtoupdate = true;
}

void Level::finished_update()		//unused design change
{
	m_needtoupdate = false;
}

bool Level::needstoupdate()			//unused design change
{
	return m_needtoupdate;
}

int Level::calculatepoints()
{
	m_points_earned=0;	//fixed looping issue
	for(int h=0; h<getWidth(); h++)				
	{											
		for(int w=0; w<getHeight(); w++)	//counts how many dead and combo points
		{									//and increments 1 for just colour and 2 for shape
			if(m_grid_layout[w][h]=='D')
			{
				m_points_earned++;				
			}
			else if(m_grid_layout[w][h]=='C')
			{
				m_points_earned+=2;
			}
		}
	}
	return m_points_earned;
}

int Level::calculatecombo()
{
	m_points_earned=0;				//unused, redundant as now in above method
	for(int h=0; h<getWidth(); h++)				
	{											
		for(int w=0; w<getHeight(); w++)		
		{
			if(m_grid_layout[w][h]=='C')
			{
				m_points_earned+=2;				
			}
		}
	}
	return m_points_earned;
}

void Level::timeminus()		//decrements time by one, used in conjunction with counter in main
{
	m_time--;
}

void Level::levelreset()	//resets all points in level, used when level is won
{
	m_points_earned=0;

	for(int h=0; h<getWidth(); h++)
	{												
		for(int w=0; w<getHeight(); w++)
		{
			if(	m_grid_layout[w][h]=='D'
				||m_grid_layout[w][h]=='C'
				||m_grid_layout[w][h]=='R'
				||m_grid_layout[w][h]=='B'
				||m_grid_layout[w][h]=='Y')
			{
				m_grid_layout[w][h]='.';
			}
		}

	}
}
