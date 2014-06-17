/*Christopher Webb
Project PRJ254
Destroy All Colours Version 1
Ball.h*/

#pragma once
#include <iostream>
#include "Entity.h"
#include "Player.h"
using namespace std;

class Ball : public Entity
{
private:
	int m_issueNumber;
	char m_colour;
	bool m_Falling;
	bool m_Alive;
	bool m_Used;
	bool m_BallBelow;
	bool m_WallBelow;
	bool m_onDeadSpace;
	Player* m_player1;
public:
	Ball(int xpos, int ypos, string name, string filename, Level* level, int speed, int issueNumber, char colour, Player* player1);
	bool isFalling();
	bool isAlive();
	bool isUsed();
	bool isWallBelow();
	bool isBallBelow();
	bool isOnDeadSpace();
	void fallen();
	void Use();
	char getColour();
	void isnowRedBall();
	void isnowBlueBall();
	void isnowYellowBall();
	void ballKilled();
	void resetballpositions();
};
