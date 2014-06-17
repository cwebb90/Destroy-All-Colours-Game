/*Christopher Webb
Project PRJ254
Destroy All Colours Version 1
Player.h */

#pragma once
#include <iostream>
#include <string>
#include "Entity.h"
#include "Level.h"

using namespace std;

class Player : public Entity
{
private:
	int m_points;			//Player will need to attain certain amount of points to complete the level.
	int ballwait;			//this variable will help slow the ball-dropping function, so the player does not drop balls too fast.
	int movecycle;

public:
	Player(int xpos, int ypos, string name, string filename, Level* level, int points);
	int getPoints();
	void setPoints(int points);
	void gainPoint();
	void dropBall();
	void playerLeft();
	void playerRight();
};
