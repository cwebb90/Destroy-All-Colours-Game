/*Christopher Webb
Project PRJ254
Final Project
Ball.cpp*/

#include "Ball.h"
#include "Player.h"

Ball::Ball(int xpos, int ypos, string name, string filename, Level* level, int speed, int issueNumber, char colour, Player* player1)  : Entity(xpos, ypos, name, filename, level, speed)
{
	m_issueNumber = issueNumber;
	m_colour = colour;
	m_Falling = true;
	m_Alive = true;
	m_Used = false;
	m_player1 = player1;
	m_level = level;
	m_WallBelow = false;
	m_BallBelow = false;
	m_onDeadSpace = false;
}

bool Ball::isFalling()
{	
	return m_Falling;
}

bool Ball::isAlive()
{
	return m_Alive;
}

bool Ball::isUsed()
{
	return m_Used;
}

char Ball::getColour()
{
	return m_colour;
}

void Ball::Use()				//sets used to true, can then call down on it,
{								//sets its x and y to below the players position
	m_Used = true;				
	m_xpos = m_player1->getX();
	m_ypos = m_player1->getY()+120;
}

void Ball::fallen()
{
	m_Falling=false;
}

void Ball::isnowRedBall()	//updates level array to balls
{
	int x = m_xpos;
	int y = m_ypos + Entity_height;

	m_level->createRedBall(x,y);
}

void Ball::isnowBlueBall()
{
	int x = m_xpos;
	int y = m_ypos + Entity_height;

	m_level->createBlueBall(x,y);
}

void Ball::isnowYellowBall()
{
	int x = m_xpos;
	int y = m_ypos + Entity_height;

	m_level->createYellowBall(x,y);
}

bool Ball::isBallBelow()
{
	if(m_level->isBall(m_xpos,m_ypos + Entity_height +1)==true || m_level->isBall(m_xpos + Entity_width -1, m_ypos + Entity_height +1)==true)
	{
		m_BallBelow=true;
	}
	return m_BallBelow;
}

bool Ball::isWallBelow()
{
	if(m_level->isWall(m_xpos,m_ypos + Entity_height +1)==true || m_level->isWall(m_xpos + Entity_width -1, m_ypos + Entity_height +1)==true)
	{
		m_WallBelow=true;
	}
	return m_WallBelow;
}

bool Ball::isOnDeadSpace()
{
	if(m_level->isDeadpoint(m_xpos+ Entity_height/2, m_ypos + Entity_height/2)==true || m_level->isDeadpoint(m_xpos + Entity_width/2, m_ypos + Entity_height/2)==true)
	{
		m_onDeadSpace=true;
	}
	return m_onDeadSpace;
}

void Ball::ballKilled()
{
	m_Alive=false;
}

void Ball::resetballpositions()	//resets all ball related variables, used when level is won
{
	m_xpos = m_player1->getX();
	m_ypos = m_player1->getY()+120;
	m_Falling = true;
	m_Alive = true;
	m_Used = false;
	m_WallBelow = false;
	m_BallBelow = false;
	m_onDeadSpace = false;
}
